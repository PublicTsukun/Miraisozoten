//=============================================================================
//
// enemy処理・改 [enemyRE.cpp]
// Author : 宋彦霖
//
//=============================================================================
#include "enemyRE.h"

#include "Library/ObjectBase3D.h"
#include "HitCheck.h"

#include "Library/DebugProcess.h"
#include "voiceten.h"
#include "score.h"
#include "UIBonus.h"

#include "Library\Input.h"

#include <time.h>

#include "GameSound.h"

#include "StageManager.h"


//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define ENEMY_HP			(2)		// 初期化用
#define ENEMY_SCOREBONUS	(1)
#define ENEMY_GAUGEBONUS	(50)
#define ENEMY_D_SCOREBONUS	(10)
#define ENEMY_D_GAUGEBONUS	(200)

#define ENEMY_COLI_LEN		(48.0f)	// 当たり判定 x
#define ENEMY_COLI_HEI		(48.0f)	// 当たり判定 y
#define ENEMY_COLI_WID		(10.0f)	// 当たり判定 z

//*****************************************************************************
// クラス定義
//*****************************************************************************
class CEnemyRE : public C3DPolygonObject
{
public:
	void ChangeTexture(float row, float col, float rowMax, float colMax);
	void SetTexture(void);
	void ChangeTexture(void);
	void ResetTexture(void);
};

void CEnemyRE::ChangeTexture(float row, float col, float rowMax, float colMax)
{
	const float rowN = (1.0f / rowMax);		// 行を等分に分ける
	const float colN = (1.0f / colMax);		// 列を等分に分ける

	VERTEX_3D *pVtx;

	// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
	VtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// 頂点座標の設定
	pVtx[0].uv = Vector2(col * colN			, row * rowN);
	pVtx[1].uv = Vector2((col + 1) * colN	, row * rowN);
	pVtx[2].uv = Vector2(col * colN			, ((row + 1) * rowN));
	pVtx[3].uv = Vector2((col + 1) * colN	, ((row + 1) * rowN));

	// 頂点データをアンロックする
	VtxBuff->Unlock();
}

void CEnemyRE::SetTexture(void)
{
	CEnemyRE::ChangeTexture(0, 0, 1, 2);
}

void CEnemyRE::ChangeTexture(void)
{
	CEnemyRE::ChangeTexture(0, 1, 1, 2);
}

void CEnemyRE::ResetTexture(void)
{
	CEnemyRE::SetTexture();
}

//*****************************************************************************
// 列挙型
//*****************************************************************************
enum E_TYPE
{
	E_TYPE_CHILD = 0,
	E_TYPE_MAID,
	E_TYPE_OTAKU,

	E_TYPE_MAX,
};

enum E_STATUS
{
	E_STATUS_NULL = 0,
	E_STATUS_NORMAL,
	E_STATUS_DEFEATED,

	E_STATUS_MAX,
};

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void CollisionEnemyRE(void);
void DamageDealEnemyRE(int Eno, int Vno);

void SetType(int ENo, int type);
void SetPos(int ENo, float x, float y, float z);
bool SetPosCheckX(float x);

void SetParameter00(void);
void SetParameter01(void);

void TestEnemyRE(void);

//=================
// エネミー生成
//=================
void TrapFactory(int apr, int num);
void TrapFactory02(int apr, int num);
void TrapFactory03(int apr);

void TFType(int no);
void TFPos(int no);


void CheckUptime(int no);

//*****************************************************************************
// グローバル変数
//*****************************************************************************
char *FileEnemy[] =
{
	"data/TEXTURE/character/01_01_child.png",
	"data/TEXTURE/character/01_02_maid.png",
	"data/TEXTURE/character/01_03_otaku.png",
};

// Enemy HP Database、E_TYPEに対応
int EnemyHp[] =
{
	5,		// CHILD
	50,		// MAID
	15,		// OTAKU
};

ENEMY EnemyREWk[ENEMY_MAX];		// ワーク
CEnemyRE EnemyRE[ENEMY_MAX];

int YOUDEFEATED;



//=============================================================================
// 初期化処理
//=============================================================================
void InitEnemyRE(void)
{
	ENEMY *e = GetEnemyRE(0);

	// 初期化用変数
	const Vector2 size = Vector2(96, 96);

	// 全パラメータ初期化
	for (int i = 0; i < ENEMY_MAX; i++)
	{
		(e + i)->use = FALSE;
		(e + i)->pos = Vector3(0.0f, 0.0f, 0.0f);
		(e + i)->rot = Vector3(0.0f, 0.0f, 0.0f);

		(e + i)->timer = 0;
		(e + i)->ptn = 0;

		(e + i)->apr = -1;

		(e + i)->type = 0;

		(e + i)->hp = ENEMY_HP;

		(e + i)->status = 0;

		(e + i)->score = 0;

		EnemyRE[i].Init((e + i)->pos, size);
		EnemyRE[i].LoadTexture(FileEnemy[0]);

	}

	ResetYouDefeated();

	//SetParameter00();
	SetParameter01();

}

//=============================================================================
// 終了処理
//=============================================================================
void UninitEnemyRE(void)
{
	for (int i = 0; i < ENEMY_MAX; i++)
	{
		EnemyRE[i].Release();
	}

}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateEnemyRE(void)
{
	ENEMY *e = GetEnemyRE(0);

#ifdef _DEBUG

	TestEnemyRE();

	PrintDebugProcess("撃破数: %d\n", YOUDEFEATED);




#endif

			// 衝突判定
			CollisionEnemyRE();

	for (int i = 0; i < ENEMY_MAX; i++)
	{
		if ((e + i)->use == TRUE)
		{
			// 更新処理（位置、回転）
			EnemyRE[i].LoadObjectStatus((e + i)->pos, (e + i)->rot);
			
			// タイマーカウントアップ
			(e + i)->timer++;

			// 稼働時間検査
			CheckUptime(i);

			switch ((e + i)->status)
			{
			case E_STATUS_NULL:
				break;

			case E_STATUS_NORMAL:

				// 衝突判定
				//CollisionEnemyRE();
				break;

			case E_STATUS_DEFEATED:

				// アニメーション
				break;

			default:
				break;

			}


		}
	}

	PrintDebugProcess("00: %f\n", (e + 0)->pos.x);
	PrintDebugProcess("01: %f\n", (e + 1)->pos.x);
	PrintDebugProcess("02: %f\n", (e + 2)->pos.x);
	PrintDebugProcess("03: %f\n", (e + 3)->pos.x);
	PrintDebugProcess("04: %f\n", (e + 4)->pos.x);
	PrintDebugProcess("05: %f\n", (e + 5)->pos.x);
	PrintDebugProcess("06: %f\n", (e + 6)->pos.x);
	PrintDebugProcess("07: %f\n", (e + 7)->pos.x);
	PrintDebugProcess("08: %f\n", (e + 8)->pos.x);
	PrintDebugProcess("09: %f\n", (e + 9)->pos.x);

}

//=============================================================================
// 描画処理
//=============================================================================
void DrawEnemyRE(void)
{
	ENEMY *e = GetEnemyRE(0);

	for (int i = 0; i < ENEMY_MAX; i++)
	{
		if ((e + i)->use == TRUE)
		{
			EnemyRE[i].Draw();
		}

	}
}

//=============================================================================
// 取得
//=============================================================================
ENEMY *GetEnemyRE(int no)
{
	return (&EnemyREWk[no]);
}

//=============================================================================
// 衝突判定
//=============================================================================
void CollisionEnemyRE(void)
{
	VOICETEN *v = GetVoiceten(0);
	ENEMY *e = GetEnemyRE(0);

	// 衝突範囲設定(1)
	const float len = ENEMY_COLI_LEN;
	const float hei = ENEMY_COLI_HEI;
	const float wid = ENEMY_COLI_WID;

	for(int i = 0; i < ENEMY_MAX; i++, e++)
	{
		if (e->use == FALSE) continue;
		v = GetVoiceten(0);

		for (int j = 0; j < VOICETEN_MAX; j++, v++)
		{
			if (v->use == FALSE) continue;

			// 衝突範囲設定(2)
			Vector3 vA1 = v->pos;
			Vector3 vA2 = v->pos;
			Vector3 vB1 = e->pos;
			Vector3 vB2 = e->pos;

			vA1.x = v->pos.x - len;		// 左
			vA1.y = v->pos.y + hei;		// 上
			vA1.z = v->pos.z - wid;		// 前

			vA2.x = v->pos.x + len;		// 右
			vA2.y = v->pos.y - hei;		// 下
			vA2.z = v->pos.z + wid;		// 奥

			vB1.x = e->pos.x - len;		// 左
			vB1.y = e->pos.y + hei;		// 上
			vB1.z = e->pos.z - wid;		// 前

			vB2.x = e->pos.x + len;		// 右
			vB2.y = e->pos.y - hei;		// 下
			vB2.z = e->pos.z + wid;		// 奥

			// チェック
			if ((vA2.x > vB1.x)
				&& (vB2.x > vA1.x)
				&& (vA2.y < vB1.y)
				&& (vB2.y < vA1.y)
				&& (vA2.z > vB1.z)
				&& (vB2.z > vA1.z)
				)
			{
				// ダメージ計算
				DamageDealEnemyRE(i, j);


				if (e->status == E_STATUS_NORMAL)
				{
					// 弾消滅
					VanishVoiceten(j);
				}

			}

		}
		
	}

}

//=============================================================================
// ダメージ計算
//=============================================================================
void DamageDealEnemyRE(int Eno, int Vno)
{
	VOICETEN *v = GetVoiceten(0);
	ENEMY *e = GetEnemyRE(0);

	// ダメージ計算
	(e + Eno)->hp -= (v + Vno)->atk;

	// 撃破判定
	if ((e + Eno)->hp <= 0 &&
		(e + Eno)->status == E_STATUS_NORMAL)
	{
		DefeatEnemyRE(Eno);
	}
	else
	{
#ifdef _DEBUG
		// スコアアップ
		AddScore(ENEMY_SCOREBONUS);
#endif
		// ゲージアップ
		AddGage(ENEMY_GAUGEBONUS);

	}

}

//=============================================================================
// 撃破処理
//=============================================================================
void DefeatEnemyRE(int no)
{
	ENEMY *e = GetEnemyRE(0);
	STAGE *s = GetStage();

	// 状態変更
	(e + no)->status = E_STATUS_DEFEATED;

	// タイマー再設定
	(e + no)->timer = 0;

	// テクスチャ変更
	EnemyRE[no].ChangeTexture(0, 1, 1, 2);

	// 音声
	PlaySE(VIGOR);

	// スコアアップ
	AddScore((e + no)->score);

	// ゲージアップ
	AddGage(ENEMY_D_GAUGEBONUS);

	// 撃破数カウントアップ
	SetYouDefeated(1);

	// 再生成
	TrapFactory02((s->timer + 120), (e + no)->type);

}

//=============================================================================
// 消滅
//=============================================================================
void VanisnEnenyRE(int no)
{
	ENEMY *e = GetEnemyRE(0);

	// 消滅
	(e + no)->use = FALSE;

	// 初期化
	(e + no)->hp = ENEMY_HP;
	(e + no)->timer = 0;
	(e + no)->status = E_STATUS_NORMAL;
}

//=============================================================================
// 全部クリア
//=============================================================================
void VanisnAllEnenyRE(void)
{
	ENEMY *e = GetEnemyRE(0);
	STAGE *s = GetStage();

	for (int i = 0; i < ENEMY_MAX; i++)
	{
		if ((e + i)->use == FALSE) continue;

		(e + i)->hp -= 32767;

		// 撃破判定
		if ((e + i)->hp <= 0 &&
			(e + i)->status == E_STATUS_NORMAL)
		{
			DefeatEnemyRE(i);
		}


	}

}

//=============================================================================
// 登場
//=============================================================================
void EnemyREOnStage(int no)
{
	ENEMY *e = GetEnemyRE(0);

	(e + no)->use = TRUE;
	(e + no)->status = E_STATUS_NORMAL;
}

//=============================================================================
// 撃破数取得
//=============================================================================
int GetYouDefeated(void)
{
	return YOUDEFEATED;
}

//=============================================================================
// 撃破数設定
//=============================================================================
void SetYouDefeated(int value)
{
	YOUDEFEATED += value;
}

//=============================================================================
// 撃破数リセット
//=============================================================================
void ResetYouDefeated(void) 
{
	SetYouDefeated(0);
}

//=============================================================================
// パラメータ設定
//============================================================================='
void SetParameter00(void)
{
	//TrapFactory02(60, 0);
	//TrapFactory02(90, 1);
	//TrapFactory02(120, 2);
	//TrapFactory02(150, 0);
	//TrapFactory02(180, 2);
	//TrapFactory02(210, 0);
	//TrapFactory02(240, 1);
	//TrapFactory02(270, 2);
	//TrapFactory02(300, 0);
	//TrapFactory02(330, 2);


	ENEMY *e = GetEnemyRE(0);

	int i = 0;
	float j = -280.0f;
	float z1 = 0.0f;

	SetType(i, E_TYPE_OTAKU);
	SetPos(i, j, 100, z1);
	(e + i)->apr = 0;
	i++; j += 100.0f;
	

	SetType(i, E_TYPE_OTAKU);
	SetPos(i, j, 100, z1);
	(e + i)->apr = 0;
	i++; j += 100.0f;

	SetType(i, E_TYPE_OTAKU);
	SetPos(i, j, 100, z1);
	(e + i)->apr = 0;
	i++; j += 100.0f;

	SetType(i, E_TYPE_OTAKU);
	SetPos(i, j, 100, z1);
	(e + i)->apr = 0;
	i++; j += 100.0f;

	SetType(i, E_TYPE_OTAKU);
	SetPos(i, j, 100, z1);
	(e + i)->apr = 0;
	i++; j += 100.0f;

	SetType(i, E_TYPE_OTAKU);
	SetPos(i, j, 100, z1);
	(e + i)->apr = 0;
	i++; j += 100.0f;

	SetType(i, E_TYPE_OTAKU);
	SetPos(i, j, 100, z1);
	(e + i)->apr = 0;
	i++; j += 100.0f;

	z1 = 100.0f;
	j = -280.0f;

	SetType(i, E_TYPE_OTAKU);
	SetPos(i, j, 100, z1);
	(e + i)->apr = 0;
	i++; j += 100.0f;


	SetType(i, E_TYPE_OTAKU);
	SetPos(i, j, 100, z1);
	(e + i)->apr = 0;
	i++; j += 100.0f;

	//SetType(i, E_TYPE_OTAKU);
	//SetPos(i, j, 100, z1);
	//(e + i)->apr = 0;
	i++; j += 100.0f;

	//SetType(i, E_TYPE_OTAKU);
	//SetPos(i, j, 100, z1);
	//(e + i)->apr = 0;
	i++; j += 100.0f;

	//SetType(i, E_TYPE_OTAKU);
	//SetPos(i, j, 100, z1);
	//(e + i)->apr = 0;
	i++; j += 100.0f;

	SetType(i, E_TYPE_OTAKU);
	SetPos(i, j, 100, z1);
	(e + i)->apr = 0;
	i++; j += 100.0f;

	SetType(i, E_TYPE_OTAKU);
	SetPos(i, j, 100, z1);
	(e + i)->apr = 0;
	i++; j += 100.0f;

	z1 = 200.0f;
	j = -280.0f;

	SetType(i, E_TYPE_OTAKU);
	SetPos(i, j, 100, z1);
	(e + i)->apr = 0;
	i++; j += 100.0f;

	//SetType(i, E_TYPE_OTAKU);
	//SetPos(i, j, 100, z1);
	//(e + i)->apr = 0;
	i++; j += 100.0f;

	//SetType(i, E_TYPE_OTAKU);
	//SetPos(i, j, 100, z1);
	//(e + i)->apr = 0;
	i++; j += 100.0f;

	//SetType(i, E_TYPE_OTAKU);
	//SetPos(i, j, 100, z1);
	//(e + i)->apr = 0;
	i++; j += 100.0f;

	//SetType(i, E_TYPE_OTAKU);
	//SetPos(i, j, 100, z1);
	//(e + i)->apr = 0;
	i++; j += 100.0f;

	//SetType(i, E_TYPE_OTAKU);
	//SetPos(i, j, 100, z1);
	//(e + i)->apr = 0;
	i++; j += 100.0f;

	SetType(i, E_TYPE_OTAKU);
	SetPos(i, j, 100, z1);
	(e + i)->apr = 0;
	i++; j += 100.0f;

	z1 = 300.0f;
	j = -280.0f;

	//SetType(i, E_TYPE_OTAKU);
	//SetPos(i, j, 100, z1);
	//(e + i)->apr = 0;
	i++; j += 100.0f;

	SetType(i, E_TYPE_OTAKU);
	SetPos(i, j, 100, z1);
	(e + i)->apr = 0;
	i++; j += 100.0f;

	SetType(i, E_TYPE_OTAKU);
	SetPos(i, j, 100, z1);
	(e + i)->apr = 0;
	i++; j += 100.0f;

	SetType(i, E_TYPE_OTAKU);
	SetPos(i, j, 100, z1);
	(e + i)->apr = 0;
	i++; j += 100.0f;

	SetType(i, E_TYPE_OTAKU);
	SetPos(i, j, 100, z1);
	(e + i)->apr = 0;
	i++; j += 100.0f;

	SetType(i, E_TYPE_OTAKU);
	SetPos(i, j, 100, z1);
	(e + i)->apr = 0;
	i++; j += 100.0f;

	//SetType(i, E_TYPE_OTAKU);
	//SetPos(i, j, 100, z1);
	//(e + i)->apr = 0;
	i++; j += 100.0f;

	z1 = 400.0f;
	j = -280.0f;

	SetType(i, E_TYPE_OTAKU);
	SetPos(i, j, 100, z1);
	(e + i)->apr = 0;
	i++; j += 100.0f;

	//SetType(i, E_TYPE_OTAKU);
	//SetPos(i, j, 100, z1);
	//(e + i)->apr = 0;
	i++; j += 100.0f;

	//SetType(i, E_TYPE_OTAKU);
	//SetPos(i, j, 100, z1);
	//(e + i)->apr = 0;
	i++; j += 100.0f;

	//SetType(i, E_TYPE_OTAKU);
	//SetPos(i, j, 100, z1);
	//(e + i)->apr = 0;
	i++; j += 100.0f;

	//SetType(i, E_TYPE_OTAKU);
	//SetPos(i, j, 100, z1);
	//(e + i)->apr = 0;
	i++; j += 100.0f;

	//SetType(i, E_TYPE_OTAKU);
	//SetPos(i, j, 100, z1);
	//(e + i)->apr = 0;
	i++; j += 100.0f;

	SetType(i, E_TYPE_OTAKU);
	SetPos(i, j, 100, z1);
	(e + i)->apr = 0;
	i++; j += 100.0f;

	z1 = 500.0f;
	j = -280.0f;

	SetType(i, E_TYPE_OTAKU);
	SetPos(i, j, 100, z1);
	(e + i)->apr = 0;
	i++; j += 100.0f;

	//SetType(i, E_TYPE_OTAKU);
	//SetPos(i, j, 100, z1);
	//(e + i)->apr = 0;
	i++; j += 100.0f;

	//SetType(i, E_TYPE_OTAKU);
	//SetPos(i, j, 100, z1);
	//(e + i)->apr = 0;
	i++; j += 100.0f;

	//SetType(i, E_TYPE_OTAKU);
	//SetPos(i, j, 100, z1);
	//(e + i)->apr = 0;
	i++; j += 100.0f;

	//SetType(i, E_TYPE_OTAKU);
	//SetPos(i, j, 100, z1);
	//(e + i)->apr = 0;
	i++; j += 100.0f;

	//SetType(i, E_TYPE_OTAKU);
	//SetPos(i, j, 100, z1);
	//(e + i)->apr = 0;
	i++; j += 100.0f;

	SetType(i, E_TYPE_OTAKU);
	SetPos(i, j, 100, z1);
	(e + i)->apr = 0;
	i++; j += 100.0f;

	z1 = 600.0f;
	j = -280.0f;

	//SetType(i, E_TYPE_OTAKU);
	//SetPos(i, j, 100, z1);
	//(e + i)->apr = 0;
	i++; j += 100.0f;

	SetType(i, E_TYPE_OTAKU);
	SetPos(i, j, 100, z1);
	(e + i)->apr = 0;
	i++; j += 100.0f;

	SetType(i, E_TYPE_OTAKU);
	SetPos(i, j, 100, z1);
	(e + i)->apr = 0;
	i++; j += 100.0f;

	SetType(i, E_TYPE_OTAKU);
	SetPos(i, j, 100, z1);
	(e + i)->apr = 0;
	i++; j += 100.0f;

	SetType(i, E_TYPE_OTAKU);
	SetPos(i, j, 100, z1);
	(e + i)->apr = 0;
	i++; j += 100.0f;

	SetType(i, E_TYPE_OTAKU);
	SetPos(i, j, 100, z1);
	(e + i)->apr = 0;
	i++; j += 100.0f;

	//SetType(i, E_TYPE_OTAKU);
	//SetPos(i, j, 100, z1);
	//(e + i)->apr = 0;
	i++; j += 100.0f;

	//float z2 = 600.0f;

	//SetType(7, E_TYPE_OTAKU);
	//SetPos(7, -280, 100, z2);
	//(e + 7)->apr = 0;

	//SetType(8, E_TYPE_OTAKU);
	//SetPos(8, -180, 100, z2);
	//(e + 8)->apr = 0;

	//SetType(9, E_TYPE_OTAKU);
	//SetPos(9, -80, 100, z2);
	//(e + 9)->apr = 0;

	//SetType(10, E_TYPE_OTAKU);
	//SetPos(10, 20, 100, z2);
	//(e + 10)->apr = 0;

	//SetType(11, E_TYPE_OTAKU);
	//SetPos(11, 120, 100, z2);
	//(e + 11)->apr = 0;

	//SetType(12, E_TYPE_OTAKU);
	//SetPos(12, 220, 100, z2);
	//(e + 12)->apr = 0;

	//SetType(13, E_TYPE_OTAKU);
	//SetPos(13, 320, 100, z2);
	//(e + 13)->apr = 0;



}

//=============================================================================
// パラメータ設定（ここで調整）
//============================================================================='
void SetParameter01(void)
{
	TrapFactory02(60, 0);
	TrapFactory02(90, 1);
	TrapFactory02(120, 2);
	TrapFactory02(150, 0);
	TrapFactory02(180, 2);
	TrapFactory02(210, 0);
	TrapFactory02(240, 1);
	TrapFactory02(270, 2);
	TrapFactory02(300, 0);
	TrapFactory02(330, 2);
}

//=============================================================================
// テクスチャタイプ設定
//============================================================================='
void SetType(int ENo, int type)
{
	ENEMY *e = GetEnemyRE(0);

	EnemyRE[ENo].LoadTexture(FileEnemy[type]);
	EnemyRE[ENo].SetTexture();

}

//=============================================================================
// 位置設定
//============================================================================='
void SetPos(int ENo, float x, float y, float z)
{
	ENEMY *e = GetEnemyRE(0);

	(e + ENo)->pos = Vector3(x, y, z);
	EnemyRE[ENo].LoadObjectStatus((e + ENo)->pos, (e + ENo)->rot);

}

bool SetPosCheckX(float x)
{
	ENEMY *e = GetEnemyRE(0);

	float v = 40.0f;
	bool check = FALSE;

	for (int i = 0; i < ENEMY_MAX; i++)
	{
		if ((e + i)->use == TRUE)
		{
			if (x <= ((e + i)->pos.x + v) &&
				x >= ((e + i)->pos.x - v)
				)
			{
				check = TRUE;
				break;
			}
			
		}
	}

	return check;
}

//=============================================================================
// エネミー生成（応急措置）
//============================================================================='
void TrapFactory(int apr, int num)
{
	ENEMY *e = GetEnemyRE(0);

	int type;
	float x;
	float z;

	// 未使用のオブジェクトを捜す
	for (int i = 0; i < num; i++)
	{
		for (int j = 0; j < ENEMY_MAX; j++)
		{
			if ((e + j)->apr == -1)
			{
				(e + j)->apr = apr;

				// 種類設定
				type = rand() % E_TYPE_MAX;
				SetType(j, type);		

				// 位置設定
				x = float(rand() % 560 - 280);
				z = float(rand() % 600);
				SetPos(j, x, 100, z);	

				// HP設定
				switch (type)
				{
				case E_TYPE_CHILD:
					(e + j)->hp = EnemyHp[E_TYPE_CHILD];
					(e + j)->score = 500;
					break;
				case E_TYPE_MAID:
					(e + j)->hp = EnemyHp[E_TYPE_MAID];
					(e + j)->score = 100;
					break;
				case E_TYPE_OTAKU:
					(e + j)->hp = EnemyHp[E_TYPE_OTAKU];
					(e + j)->score = 1000;
					break;
				default:
					(e + j)->hp = ENEMY_HP;
					break;
				}

				break;
			}
		}
	}

}

//=============================================================================
// エネミー生成（応急措置）
//============================================================================='
void TrapFactory02(int apr, int num)
{
	ENEMY *e = GetEnemyRE(0);

	float x = 0.0f;
	float z = 0.0f;

	// 未使用のオブジェクトを捜す
		for (int j = 0; j < ENEMY_MAX; j++)
		{
			if ((e + j)->apr == -1)
			{
				(e + j)->apr = apr;

				// 種類設定
				(e + j)->type = num;
				SetType(j, (e + j)->type);

				// 位置設定
				x = float(rand() % 560 - 280);
				z = float(rand() % 600);
				SetPos(j, x, 100, z);

				// HP設定
				switch ((e + j)->type)
				{
				case E_TYPE_CHILD:
					(e + j)->hp = EnemyHp[E_TYPE_CHILD];
					(e + j)->score = 500;
					break;
				case E_TYPE_MAID:
					(e + j)->hp = EnemyHp[E_TYPE_MAID];
					(e + j)->score = 100;
					break;
				case E_TYPE_OTAKU:
					(e + j)->hp = EnemyHp[E_TYPE_OTAKU];
					(e + j)->score = 1000;
					break;
				default:
					(e + j)->hp = ENEMY_HP;
					(e + j)->score = 0;
					break;
				}

				break;
			}
	}

}


//=============================================================================
// 稼働時間検査
//============================================================================='
void CheckUptime(int no)
{
	ENEMY *e = GetEnemyRE(0);

	int Uptime = -1;

	switch ((e + no)->status)
	{
	case 0:
		break;
	case E_STATUS_NORMAL:
		break;
	case E_STATUS_DEFEATED:
		Uptime = 120;

		if ((e + no)->timer >= Uptime)
		{
			VanisnEnenyRE(no);
		}

		break;
	default:
		break;
	}




}

//=============================================================================
// テスト用
//============================================================================='
void TestEnemyRE(void)
{
	ENEMY *e = GetEnemyRE(0);

	float vel = 10.0f;

	if (GetKeyboardPress(DIK_NUMPAD8))
	{
		e->pos.z += vel;
	}


	if (GetKeyboardPress(DIK_NUMPAD5))
	{
		e->pos.z -= vel;

	}

	if (GetKeyboardPress(DIK_NUMPAD4))
	{
		e->pos.x -= vel;

	}

	if (GetKeyboardPress(DIK_NUMPAD6))
	{
		e->pos.x += vel;

	}

	if (GetKeyboardPress(DIK_NUMPAD7))
	{
		e->pos.y -= vel;
	}

	if (GetKeyboardPress(DIK_NUMPAD9))
	{
		e->pos.y += vel;
	}

	if (GetKeyboardPress(DIK_NUMPAD3))
	{
		e->rot.y += 0.2f;
	}


	//if (GetKeyboardPress(DIK_NUMPAD3))
	//{
	//	tx->rot.y += 6 * (D3DX_PI / 180);
	//}

	//if (tx->rot.y >= 90 * (D3DX_PI / 180))
	//{
	//	tx->rot.y = -(90 * (D3DX_PI / 180));
	//}

	// 0 -> 90	-90 -> 90   -90 > 0
	// 90 180 90
	// 360 / vel = time
	// if time rot = 0


	PrintDebugProcess("pos: %f %f %f\n", e->pos.x, e->pos.y, e->pos.z);
	PrintDebugProcess("pos: %f %f %f\n", (e + 1)->pos.x, (e + 1)->pos.y, (e + 1)->pos.z);
	PrintDebugProcess("pos: %f %f %f\n", (e + 2)->pos.x, (e + 2)->pos.y, (e + 2)->pos.z);

}



