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


//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define ENEMY_HP			(2)
#define ENEMY_SCOREBONUS	(1)
#define ENEMY_GAUGEBONUS	(50)
#define ENEMY_D_SCOREBONUS	(10)
#define ENEMY_D_GAUGEBONUS	(200)

#define ENEMY_COLI_LEN		(24.0f)
#define ENEMY_COLI_HEI		(24.0f)
#define ENEMY_COLI_WID		(5.0f)

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
enum E_TEX
{
	E_TEX_CHILD = 0,
	E_TEX_MAID,
	E_TEX_OTAKU,

	E_TEX_MAX,
};

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void CollisionEnemyRE(void);
void DamageDealEnemyRE(int Eno, int Vno);
void ResetEnemyRE(void);

void SetType(int ENo, int type);
void SetPos(int ENo, float x, float y, float z);
void SetAppear(int ENo, int time);
void SetParameter00(void);
void SetParameter01(void);

void TestEnemyRE(void);
void TrapFactory(int apr, int num);

//*****************************************************************************
// グローバル変数
//*****************************************************************************
char *FileEnemy[] =
{
	"data/TEXTURE/character/01_01_child.png",
	"data/TEXTURE/character/01_02_maid.png",
	"data/TEXTURE/character/01_03_otaku.png",
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

		(e + i)->hp = ENEMY_HP;

		EnemyRE[i].Init((e + i)->pos, size);
		EnemyRE[i].LoadTexture(FileEnemy[0]);

	}

	ResetYouDefeated();

	//(e + 1)->pos = Vector3(-400.0f, 150.0f, -50.0f);
	//(e + 2)->pos = Vector3(-200.0f, 50.0f, 50.0f);

	SetParameter00();

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

	TestEnemyRE();


	for (int i = 0; i < ENEMY_MAX; i++)
	{
		if ((e + i)->use == TRUE)
		{
			// 衝突判定
			CollisionEnemyRE();

			// 更新処理（位置、回転）
			EnemyRE[i].LoadObjectStatus((e + i)->pos, (e + i)->rot);
			
			// タイマーカウントアップ
			(e + i)->timer++;

		}
	}

	PrintDebugProcess("撃破数: %d\n", YOUDEFEATED);
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

				// 弾消滅
				VanishVoiceten(j);

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
	if ((e + Eno)->hp <= 0)
	{
		VanisnEnenyRE(Eno);
	}
	else
	{
		// テクスチャ変更
		EnemyRE[Eno].ChangeTexture(0, 1, 1, 2);

		// スコアアップ
		AddScore(ENEMY_SCOREBONUS);

		// ゲージアップ
		AddGage(ENEMY_GAUGEBONUS);
	}

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

	//================================
	// ボーナス
	//================================
	// スコアアップ
	AddScore(ENEMY_D_SCOREBONUS);

	// ゲージアップ
	AddGage(ENEMY_D_GAUGEBONUS);

	SetYouDefeated(1);
}

//=============================================================================
// 全部クリア
//=============================================================================
void VanisnAllEnenyRE(void)
{
	ENEMY *e = GetEnemyRE(0);

	for (int i = 0; i < ENEMY_MAX; i++)
	{
		// 消滅
		(e + i)->use = FALSE;

		// 初期化
		(e + i)->hp = ENEMY_HP;
		(e + i)->timer = 0;

	}

}

//=============================================================================
// パラメータ設定
//=============================================================================
void SetEnemyRE(int StageNO)
{
	ENEMY *e = GetEnemyRE(0);

	switch (StageNO)
	{
	case 0:
		break;
	case 1:
		break;
	case 2:
		break;
	default:
		break;
	}

}

//=============================================================================
// 登場
//=============================================================================
void EnemyREOnStage(int no)
{
	ENEMY *e = GetEnemyRE(0);

	(e + no)->use = TRUE;
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
// パラメータ設定（ここで調整）
//============================================================================='
void SetParameter00(void)
{
	//int ENo;	// エネミー番号

	//int apr;	// 出現タイミング
	//int type;	// 0 - E_TEX_MAX
	//float x;	// -280 - 280
	//float z;	// 0 - 600

	////================================//================================
	//ENo = 0;					// 指定
	//apr = 30;
	//type = rand() % E_TEX_MAX;



	//SetType(ENo, type);	// 種類設定
	//SetPos(ENo, -260, 100, 0);	// 位置設定
	//SetAppear(ENo, apr);			// 出現タイミング設定
	////================================

	srand((unsigned)time(NULL));

	TrapFactory(30, 4);
	TrapFactory(60, 2);


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
	EnemyRE[ENo].LoadObjectStatus((e + 0)->pos, (e + 0)->rot);

}

//=============================================================================
// 出現タイミング設定
//============================================================================='
void SetAppear(int ENo, int time)
{
	ENEMY *e = GetEnemyRE(0);

	(e + ENo)->apr = time;
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

				type = rand() % E_TEX_MAX;
				SetType(j, type);		// 種類設定

				x = float(rand() % 560 - 280);
				z = float(rand() % 600);
				SetPos(j, x, 100, z);	// 位置設定
				break;
			}
		}
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

	PrintDebugProcess("pos: %f %f %f\n", e->pos.x, e->pos.y, e->pos.z);
	PrintDebugProcess("pos: %f %f %f\n", (e + 1)->pos.x, (e + 1)->pos.y, (e + 1)->pos.z);
	PrintDebugProcess("pos: %f %f %f\n", (e + 2)->pos.x, (e + 2)->pos.y, (e + 2)->pos.z);

}



