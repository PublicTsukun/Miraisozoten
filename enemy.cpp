//=============================================================================
//
//木村担当分　workenemy.cpp
//　一年の時にやったmain.cppと同じやり方で
// 
// ・編集 : [2018/11/11 - 初]
//   >> 本番用に書き換えました
//=============================================================================

//必須インクルード
#include <windows.h>
#include "enemy.h"


//木村担当分インクルード

// 初担当分インクルード
#include "HitCheck.h"

// 定数定義
#define ENEMY_MAX (16)
#define ENEMY_SIZE_X (100)
#define ENEMY_SIZE_Y (100)


// クラス設計
Dx9Texture CEnemy::EnemyTexture[ENEMYTYPE_MAX];

void CEnemy::ChangeTexture(float side)
{
	VERTEX_3D *pVtx;

	// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
	VtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// 頂点座標の設定
	pVtx[0].uv = Vector2(side        * 0.5f, 0.0f);
	pVtx[1].uv = Vector2(side        * 0.5f, 0.0f);
	pVtx[2].uv = Vector2(side + 1.0f * 0.5f, 1.0f);
	pVtx[3].uv = Vector2(side + 1.0f * 0.5f, 1.0f);

	// 頂点データをアンロックする
	VtxBuff->Unlock();
}
void CEnemy::Move(Vector3 v)
{
	this->Position += v;
}
inline void CEnemy::CheckHit(Vector3 pos, Vector3 box, int atk)
{
	if (Collision::AABB(pos - box, pos + box,
		this->Position - Vector3(this->Size.x, this->Size.y, this->Size.x) * this->Scale,
		this->Position + Vector3(this->Size.x, this->Size.y, this->Size.x) * this->Scale))
	{
		this->HP -= atk;
	}

	if (this->HP <= 0)
	{
		this->ChangeTexture(1);
	}
}

//グローバル宣言
CEnemy *EnemyList[ENEMY_MAX] = { NULL };

//=============================================================================
//初期化処理
//=============================================================================
HRESULT InitENEMY(void)
{
	for (int i = 0; i < ENEMY_MAX; i++)
	{
		EnemyList[i] = NULL;
	}
	for (int i = 0; i < ENEMYTYPE_MAX; i++)
	{
		CEnemy::EnemyTexture[i].LoadTexture(EnemyTextureName[i]);
	}

	return S_OK;
}

//=============================================================================
//終了処理　※記載場所注意
//=============================================================================
void UninitENEMY(void)
{
	for (int i = 0; i < ENEMY_MAX; i++)
	{
		Dx9SafeRelease(EnemyList[i]);
	}
	for (int i = 0; i < ENEMYTYPE_MAX; i++)
	{
		CEnemy::EnemyTexture[i].Release();
	}

}

//=============================================================================
//更新処理
//=============================================================================
void UpdateENEMY(void)
{

}

//=============================================================================
//描画処理
//=============================================================================
void DrawENEMY(void)
{
	for (int i = 0; i < ENEMY_MAX; i++)
	{
		if (EnemyList[i] != NULL)
		{
			EnemyList[i]->Draw();
		}
	}
}

//=============================================================================
// エネミー追加処理
//=============================================================================
int SetEnemy(ENEMYTYPE type, int hp, Vector3 pos)
{
	for (int i = 0; i < ENEMY_MAX; i++)
	{
		if (EnemyList[i] == NULL)
		{
			EnemyList[i] = new CEnemy;
			EnemyList[i]->Init(pos, Vector2(ENEMY_SIZE_X, ENEMY_SIZE_Y));
			EnemyList[i]->LoadTexture(CEnemy::EnemyTexture[type]);
			EnemyList[i]->ChangeTexture(0);
			return i;
		}
	}
	return -1;
}

//=============================================================================
// エネミー削除処理 (当たり判定)
//=============================================================================
void CheckHit(Vector3 pos, Vector2 box, int atk)
{
	for (int i = 0; i < ENEMY_MAX; i++)
	{
		EnemyList[i]->CheckHit(pos, Vector3(box.x, box.y, box.x), atk);
	}
}

//=============================================================================
// エネミー取得関数
//=============================================================================
CEnemy *GetEnemy(int handle)
{
	return EnemyList[handle];
}

