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
};

void CEnemyRE::ChangeTexture(float row, float col, float rowMax, float colMax)
{
	const float rowN = (1.0f / rowMax);		// 行を等分に分ける
	const float colN = (1.0f / colMax);		// 列を等分に分ける

	VERTEX_3D *pVtx;

	// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
	VtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// 頂点座標の設定
	pVtx[0].uv = Vector2(col * colN, row * rowN);
	pVtx[1].uv = Vector2((col + 1) * colN, row * rowN);
	pVtx[2].uv = Vector2(col * colN, ((row + 1) * rowN));
	pVtx[3].uv = Vector2((col + 1) * colN, ((row + 1) * rowN));

	// 頂点データをアンロックする
	VtxBuff->Unlock();
}

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void CollisionEnemyRE(void);
void DamageDealEnemyRE(int Eno, int Vno);
void ResetEnemyRE(void);

//*****************************************************************************
// グローバル変数
//*****************************************************************************
ENEMY EnemyREWk[ENEMY_MAX];		// ワーク

char *FileEnemy[] =
{
	"data/作業/boss.png",
	"data/作業/tttt.png",
};

CEnemyRE EnemyRE[ENEMY_MAX];

int YOUDEFEATED;



//=============================================================================
// 初期化処理
//=============================================================================
void InitEnemyRE(void)
{
	ENEMY *e = GetEnemyRE(0);

	// 初期化用変数
	const Vector2 size = Vector2(48, 48);

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

	// 個別パラメータ設定
	//(e + 0)->use = TRUE;
	//(e + 0)->pos = Vector3(-300.0f, 100.0f, 0.0f);

	//(e + 1)->use = TRUE;
	//(e + 1)->pos = Vector3(-400.0f, 150.0f, -50.0f);
	//EnemyRE[1].LoadTexture(FileEnemy[1]);

	//(e + 2)->use = TRUE;
	//(e + 2)->pos = Vector3(-200.0f, 50.0f, 50.0f);
	//EnemyRE[2].LoadTexture(FileEnemy[1]);

	(e + 0)->apr = 30;
	(e + 0)->pos = Vector3(-300.0f, 100.0f, 0.0f);
	EnemyRE[0].LoadObjectStatus((e + 0)->pos, (e + 0)->rot);
	EnemyRE[0].LoadObjectStatus((e + 0)->pos, (e + 0)->rot);
	EnemyRE[0].ChangeTexture(0, 0, 2, 2);

	(e + 1)->apr = 60;
	(e + 1)->pos = Vector3(-400.0f, 150.0f, -50.0f);
	EnemyRE[1].LoadTexture(FileEnemy[1]);
	EnemyRE[1].LoadObjectStatus((e + 1)->pos, (e + 1)->rot);
	EnemyRE[1].ChangeTexture(0, 0, 2, 2);


	(e + 2)->apr = 90;
	(e + 2)->pos = Vector3(-200.0f, 50.0f, 50.0f);
	EnemyRE[2].LoadTexture(FileEnemy[1]);
	EnemyRE[2].LoadObjectStatus((e + 2)->pos, (e + 2)->rot);
	EnemyRE[2].ChangeTexture(0, 0, 2, 2);



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
		EnemyRE[Eno].ChangeTexture(1, 0, 2, 2);

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
