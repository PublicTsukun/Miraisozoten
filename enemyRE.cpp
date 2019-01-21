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

#include "DefeatCounter.h"

#include "EffectVH.h"
#include "EffectFB.h"

#include "S-Editor.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define ENEMY_COLI_LEN		(36.0f)	// 当たり判定 x
#define ENEMY_COLI_HEI		(24.0f)	// 当たり判定 y
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
void TrapFactory03(int no, int apr);

void TF_Type(int no);
void TF_Pos(int no);

//=================
// 演出
//=================
void DefeatEnemyREEfx(int no);

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
	"data/TEXTURE/Character/08_ufo.png",
	"data/TEXTURE/Character/06_astronaut.png",
	"data/TEXTURE/Character/07_alien.png",
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

		(e + i)->posData = -1;

		(e + i)->timer = 0;

		(e + i)->apr = -1;

		(e + i)->type = 0;

		(e + i)->hp = 0;

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

			// 撃破エフェクト
			if ((e + i)->status == E_STATUS_DEFEATED)
			{
				DefeatEnemyREEfx(i);
			}

		}
	}

	// 衝突判定
	CollisionEnemyRE();
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
	STAGE *stage = GetStage();

	if (stage->status == STAGE_STATUS_NORMAL)
	{
		// 衝突範囲設定(1)
		const float len = ENEMY_COLI_LEN;
		const float hei = ENEMY_COLI_HEI;
		const float wid = ENEMY_COLI_WID;

		for (int i = 0; i < ENEMY_MAX; i++, e++)
		{
			if (e->use == FALSE) continue;
			if (e->status != E_STATUS_NORMAL) continue;
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

					// エフェクト発生
					CallEffectVH(v->pos);

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

	if ((e + Eno)->status == E_STATUS_NORMAL)
	{
		// ダメージ計算
		(e + Eno)->hp -= (v + Vno)->atk;

		// HP修正
		if ((e + Eno)->hp < 0)
		{
			(e + Eno)->hp = 0;
		}

		// 撃破判定
		if ((e + Eno)->hp <= 0)
		{
			DefeatEnemyRE(Eno);
		}
	}

}

//=============================================================================
// 撃破処理
//=============================================================================
void DefeatEnemyRE(int no)
{
	ENEMY *enemy = GetEnemyRE(no);
	DefeatCounter *DefeatCounter = GetDefeatCounter(0);

	// 状態変更
	enemy->status = E_STATUS_DEFEATED;

	// タイマー再設定
	enemy->timer = 0;

	// テクスチャ変更
	//EnemyRE[no].ChangeTexture(0, 1, 1, 2);

	// 音声
	PlaySE(VIGOR);

	// スコアアップ
	AddScore(enemy->score);

	// ボーナスゲージアップ
	AddGage(int(enemy->bonus));

	// 撃破数カウントアップ
	(DefeatCounter + enemy->type)->CountUp();

}

//=============================================================================
// 消滅
//=============================================================================
void VanisnEnenyRE(int no)
{
	ENEMY *e = GetEnemyRE(0);
	EnemyPosData *ePosData = GetEnemyPosData(0);
	STAGE *stage = GetStage();

	// 消滅
	(e + no)->use = FALSE;

	(ePosData + ((e + no)->posData))->SetUse(false);
	(e + no)->posData = -1;

	// 再生成
	TrapFactory03(no, stage->timer);

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

	time += ENEMY_SPAWN_DELAY_01;

	for (int i = 0; i < ENEMY_MAX; i++, time += ENEMY_SPAWN_DELAY_02)
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

	(e + no)->use = TRUE;
	(e + no)->status = E_STATUS_NORMAL;
}

//=============================================================================
// クリア（ステージ遷移の演出）
//=============================================================================
void ClearAllEnemyRE(void)
{
	ENEMY *enemy = GetEnemyRE(0);

	for (int i = 0; i < ENEMY_MAX; i++)
	{
		if ((enemy + i)->status == E_STATUS_NORMAL)
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
	EnemyPosData *ePosData = GetEnemyPosData(0);

	for (int i = 0; i < ENEMYPOS_MAX; i++)
	{
		(ePosData + i)->SetUse(false);
	}
}

//=============================================================================
// エネミー生成
//============================================================================='
void TrapFactory03(int no, int apr)
{
	ENEMY *enemy = GetEnemyRE(no);

	EnemyHP *EnemyHP = GetEnemyHP(no);
	Vector3 tempPos;
	
	// 回転
	enemy->rot.y = 0.0;

	// 出現タイミング
	enemy->apr = apr;

	// タイマー
	enemy->timer = 0;

	// タイプ
	TF_Type(no);

	// 位置
	TF_Pos(no);

	// パーツ・HPゲージ
	//// 画像設定
	SetEnemyHP(no);
	//// 位置調整
	tempPos = enemy->pos;
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
		if (temp == 5) e->type = E_TYPE_CHILD;
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
		if (temp == 7) e->type = E_TYPE_JK;
		if (temp == 8) e->type = E_TYPE_AA;
		if (temp == 9) e->type = E_TYPE_AMERICAN;
		break;

	case STAGE_03_SPACE:
		temp = int(rand() % 10);
		if (temp == 0) e->type = E_TYPE_ASTRONAUT;
		if (temp == 1) e->type = E_TYPE_ASTRONAUT;
		if (temp == 2) e->type = E_TYPE_ASTRONAUT;
		if (temp == 3) e->type = E_TYPE_ALIEN;
		if (temp == 4) e->type = E_TYPE_UFO;
		if (temp == 5) e->type = E_TYPE_UFO;
		if (temp == 6) e->type = E_TYPE_UFO;
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
	e->bonus = EnemyDB->GetBonus();
	
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

	e->posData = tempP;

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
// 撃破エフェクト
//=============================================================================
void DefeatEnemyREEfx(int no)
{
	ENEMY *enemy = GetEnemyRE(no);

	const int animeStart = 0;
	const int animeEnd = 18;
	const int efxStart = 0;

	if (enemy->status == E_STATUS_DEFEATED)
	{
		// アニメーション
		if (enemy->timer >= animeStart &&
			enemy->timer < animeEnd)
		{
			// 回転
			enemy->rot.y += (360 / animeEnd) * (D3DX_PI / 180);

			// 角度修正
			if (enemy->rot.y >= 90 * (D3DX_PI / 180))
			{
				enemy->rot.y = -(90 * (D3DX_PI / 180));
			}
		}

		if (enemy->timer == animeEnd)
		{
			// 角度修正
			enemy->rot.y = 0;
		}
		
		// エフェクト発生
		if (enemy->timer == efxStart)
		{
			CallEffectFB(enemy->pos);
		}

		// テクスチャ変更（指定の時間で発生）
		if (enemy->timer == int(animeEnd / 2))
		{
			EnemyRE[no].ChangeTexture(0, 1, 1, 2);
		}

		if (GetFiver() == FALSE)
		{
			if (enemy->timer >= ENEMY_DEFEAT_DELAY)
			{
				VanisnEnenyRE(no);
			}
		}
		else if (GetFiver() == TRUE)
		{
			if (enemy->timer >= ENEMY_DEFEAT_FEVER)
			{
				VanisnEnenyRE(no);
			}
		}

		// タイマーカウントアップ
		enemy->timer++;
	}

}

//=============================================================================
// テスト用
//============================================================================='
void TesterAtkEnemyRE(void)
{
	ENEMY *e = GetEnemyRE(0);

	// ダメージ計算
	if ((e + 0)->status == E_STATUS_NORMAL)
	{
		(e + 0)->hp -= 4;

		// HP修正
		if ((e + 0)->hp < 0)
		{
			(e + 0)->hp = 0;
		}

		// 撃破判定
		if ((e + 0)->hp <= 0)
		{
			DefeatEnemyRE(0);
		}

	}
}