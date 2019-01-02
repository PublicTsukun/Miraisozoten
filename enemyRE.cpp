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

#include "EnemyDB.h"
#include "EnemyPosData.h"
#include "EnemyHP.h"

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
//=================
// 衝突判定、撃破
//=================
void CollisionEnemyRE(void);
void DamageDealEnemyRE(int Eno, int Vno);
void DefeatEnemyRE(int no);
void VanisnEnenyRE(int no);

//=================
// 生成
//=================
void SetParameter01(void);

void TrapFactory03(int no, int apr);

void TF_Type(int no);
void TF_Pos(int no);

//=================
// 演出
//=================
void CheckUptime(int no);

//*****************************************************************************
// グローバル変数
//*****************************************************************************
char *FileEnemy[] =
{
	"data/TEXTURE/Character/00_child.png",
	"data/TEXTURE/Character/01_maid.png",
	"data/TEXTURE/Character/02_otaku.png",
	"data/TEXTURE/Character/03_aa.png",
	"data/TEXTURE/Character/04_jk.png",
	"data/TEXTURE/Character/05_american.png",
	"data/TEXTURE/Character/06_astronaut.png",
	"data/TEXTURE/Character/07_alien.png",
	"data/TEXTURE/Character/08_ufo.png",
};

// ワーク
ENEMY EnemyREWk[ENEMY_MAX];		
CEnemyRE EnemyRE[ENEMY_MAX];

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
		(e + i)->pos = Vector3(0.0f, float(size.y / 2), 0.0f);
		(e + i)->rot = Vector3(0.0f, 0.0f, 0.0f);

		(e + i)->timer = 0;

		(e + i)->apr = -1;

		(e + i)->type = 0;

		(e + i)->hp = ENEMY_HP;

		(e + i)->status = 0;

		(e + i)->score = 0;

		EnemyRE[i].Init((e + i)->pos, size);
	}
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
				CollisionEnemyRE();
				break;

			case E_STATUS_DEFEATED:

				// アニメーション
				break;

			default:
				break;

			}
		}
	}
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

	// HP修正
	if ((e + Eno)->hp < 0)
	{
		(e + Eno)->hp = 0;
	}
	
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

	// 再生成
	TrapFactory03(no, s->timer + 120);

}

//=============================================================================
// 消滅
//=============================================================================
void VanisnEnenyRE(int no)
{
	ENEMY *e = GetEnemyRE(0);
	EnemyPosData *ePosData = GetEnemyPosData(0);

	// 消滅
	(e + no)->use = FALSE;
	(ePosData + no)->SetUse(false);

	// 初期化
	(e + no)->timer = 0;
	(e + no)->apr = -1;
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
// 設置
//=============================================================================
void SetEnemyRE(int time)
{
	ENEMY *enemy = GetEnemyRE(0);

	time += 60;

	for (int i = 0; i < ENEMY_MAX; i++, time += 120)
	{
		TrapFactory03(i, time);
	}
}

//=============================================================================
// 登場
//=============================================================================
void EnemyREOnStage(int no)
{
	ENEMY *e = GetEnemyRE(0);
	EnemyHP *EnemyHP = GetEnemyHP(0);

	(e + no)->use = TRUE;
	(e + no)->status = E_STATUS_NORMAL;

	(EnemyHP + no)->Enable();
}

//=============================================================================
// クリア（ステージ遷移の演出）
//=============================================================================
void ClearAllEnemyRE(void)
{
	ENEMY *enemy = GetEnemyRE(0);

	for (int i = 0; i < ENEMY_MAX; i++)
	{
		if ((enemy + i)->status = E_STATUS_NORMAL)
		{
			(enemy + i)->use = FALSE;
			(enemy + i)->status = E_STATUS_NULL;
		}
	}

}

//=============================================================================
// パラメータリセット
//=============================================================================
void ResetAllEnemyRE(void)
{
	for (int i = 0; i < ENEMY_MAX; i++)
	{
		VanisnEnenyRE(i);
	}
}

//=============================================================================
// パラメータ設定
//============================================================================='
void SetParameter01(void)
{
	int i = 0;
	int j = 60;

	TrapFactory03(i, j); i++; j += 30;
	TrapFactory03(i, j); i++; j += 30;
	TrapFactory03(i, j); i++; j += 30;
	TrapFactory03(i, j); i++; j += 30;
	TrapFactory03(i, j); i++; j += 30;

	TrapFactory03(i, j); i++; j += 30;
	TrapFactory03(i, j); i++; j += 30;
	TrapFactory03(i, j); i++; j += 30;
	TrapFactory03(i, j); i++; j += 30;
	TrapFactory03(i, j);
}

//=============================================================================
// エネミー生成
//============================================================================='
void TrapFactory03(int no, int apr)
{
	// 出現タイミング
	ENEMY *e = GetEnemyRE(no);
	e->apr = apr;

	// タイプ
	TF_Type(no);

	// 位置
	TF_Pos(no);

	// パーツ・HPゲージ
	EnemyHP *EnemyHP = GetEnemyHP(no);
	Vector3 tempPos = e->pos;
	//// 位置調整
	tempPos.x += -32.0f;
	tempPos.y += -88.0f;
	//// 位置設定
	EnemyHP->LoadObjectStatus(tempPos);

}

//=============================================================================
// エネミー生成：タイプ設定
//============================================================================='
void TF_Type(int no)
{
	ENEMY *e = GetEnemyRE(no);
	EnemyDB *EnemyDB = GetEnemyDB(0);
	STAGE *s = GetStage();
	int stage = s->no;
	int temp = -1;

	// タイプ設定
	switch (stage)
	{
	case STAGE_01_AKIBA:
		temp = int(rand() % 10);
		if (temp == 0) e->type = E_TYPE_CHILD;
		if (temp == 1) e->type = E_TYPE_CHILD;
		if (temp == 2) e->type = E_TYPE_CHILD;
		if (temp == 3) e->type = E_TYPE_CHILD;
		if (temp == 4) e->type = E_TYPE_CHILD;
		if (temp == 5) e->type = E_TYPE_MAID;
		if (temp == 6) e->type = E_TYPE_MAID;
		if (temp == 7) e->type = E_TYPE_OTAKU;
		if (temp == 8) e->type = E_TYPE_OTAKU;
		if (temp == 9) e->type = E_TYPE_OTAKU;
		break;

	case STAGE_02_USA:
		temp = int(rand() % 10);
		if (temp == 0) e->type = E_TYPE_AA;
		if (temp == 1) e->type = E_TYPE_AA;
		if (temp == 2) e->type = E_TYPE_AA;
		if (temp == 3) e->type = E_TYPE_AA;
		if (temp == 4) e->type = E_TYPE_AA;
		if (temp == 5) e->type = E_TYPE_JK;
		if (temp == 6) e->type = E_TYPE_JK;
		if (temp == 7) e->type = E_TYPE_AMERICAN;
		if (temp == 8) e->type = E_TYPE_AMERICAN;
		if (temp == 9) e->type = E_TYPE_AMERICAN;
		break;

	case STAGE_03_SPACE:
		temp = int(rand() % 10);
		if (temp == 0) e->type = E_TYPE_ASTRONAUT;
		if (temp == 1) e->type = E_TYPE_ASTRONAUT;
		if (temp == 2) e->type = E_TYPE_ASTRONAUT;
		if (temp == 3) e->type = E_TYPE_ASTRONAUT;
		if (temp == 4) e->type = E_TYPE_ASTRONAUT;
		if (temp == 5) e->type = E_TYPE_ALIEN;
		if (temp == 6) e->type = E_TYPE_ALIEN;
		if (temp == 7) e->type = E_TYPE_UFO;
		if (temp == 8) e->type = E_TYPE_UFO;
		if (temp == 9) e->type = E_TYPE_UFO;
		break;

	default:
		break;
	}

	// テクスチャ設定
	EnemyRE[no].LoadTexture(FileEnemy[e->type]);
	EnemyRE[no].SetTexture();

	// パラメータ設定
	EnemyDB = GetEnemyDB(e->type);
	e->hp = EnemyDB->GetHP();
	e->score = EnemyDB->GetScore();
	
}

//=============================================================================
// エネミー生成：出現位置設定
//============================================================================='
void TF_Pos(int no)
{
	ENEMY *e = GetEnemyRE(no);
	EnemyPosData *ePosData = GetEnemyPosData(0);

	// 位置設定
	int valueP = ENEMYPOS_MAX;
	int tempP = -1;

	do
	{
		tempP = (rand() % valueP);
		ePosData = GetEnemyPosData(tempP);
	} while (ePosData->GetUse() == true);

	e->pos.x = ePosData->GetPosX();
	e->pos.z = ePosData->GetPosZ();
	ePosData->SetUse(true);

	// 微調整
	const int value = 20;
	float tempX = float(rand() % value) - (value / 2);
	float tempZ = float(rand() % value) - (value / 2);
	e->pos.x += tempX;
	e->pos.z += tempZ;

	// 反映
	EnemyRE[no].LoadObjectStatus(e->pos, e->rot);
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
