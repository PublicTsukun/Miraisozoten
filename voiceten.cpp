//=============================================================================
//
// voiceten処理 [voiceten.cpp]
// Author : 宋彦霖
//
//=============================================================================
#include "voiceten.h"

#include "Library/ObjectBase3D.h"

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void UpdateVoiMove(void);
float DirectionCalc(D3DXVECTOR3 Self, D3DXVECTOR3 Tgt);

//*****************************************************************************
// グローバル変数
//*****************************************************************************
VOICETEN VoicetenWk[VOICETEN_MAX];		// ワーク

char *FileVoiceten[] =
{
	"data/作業/テスト画像02.jpg",
};

C3DPolygonObject Voiceten[VOICETEN_MAX];

//=============================================================================
// 初期化処理
//=============================================================================
void InitVoiceten(void)
{
	VOICETEN *v = GetVoiceten(0);

	const Vector2 size = Vector2(48, 48);

	for (int i = 0; i < VOICETEN_MAX; i++)
	{
		(v + i)->use = FALSE;
		(v + i)->pos = Vector3(0.0f, 0.0f, 0.0f);
		(v + i)->rot = Vector3(0.0f, 0.0f, 0.0f);

		(v + i)->vel = 4.0f;

		(v + i)->timer = 0;

		(v + i)->start = Vector3(0.0f, 0.0f, 0.0f);
		(v + i)->tgt = Vector3(0.0f, 0.0f, 0.0f);
		(v + i)->dura = 60;

		(v + i)->nor = Vector3(0.0f, 0.0f, 0.0f);

		Voiceten[i].Init((v + i)->pos, size);
		Voiceten[i].LoadTexture(FileVoiceten[0]);
		
	}
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitVoiceten(void)
{
	for (int i = 0; i < VOICETEN_MAX; i++)
	{
		Voiceten[i].Release();
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateVoiceten(void)
{
	VOICETEN *v = GetVoiceten(0);

	UpdateVoiMove();

	for (int i = 0; i < VOICETEN_MAX; i++)
	{
		if ((v + i)->use == TRUE)
		{
			// 更新処理（位置、回転）
			Voiceten[i].LoadObjectStatus((v + i)->pos, (v + i)->rot);

			// タイマー　カウントアップ
			(v + i)->timer++;

			// 消滅
			VanishVoiceten(i);
		}
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawVoiceten(void)
{
	VOICETEN *v = GetVoiceten(0);

	for (int i = 0; i < VOICETEN_MAX; i++)
	{
		if ((v + i)->use == TRUE)
		{
			Voiceten[i].Draw();
		}

	}
}

//=============================================================================
// 取得
//=============================================================================
VOICETEN *GetVoiceten(int no)
{
	return (&VoicetenWk[no]);
}

//=============================================================================
// 移動
//=============================================================================
void UpdateVoiMove(void)
{
	VOICETEN *v = GetVoiceten(0);

	for (int i = 0; i < VOICETEN_MAX; i++)
	{
		if ((v + i)->use == TRUE)
		{
			//// 一般
			//(v + i)->pos.x -= sinf((v + i)->rot.y) * (v + i)->vel;
			//(v + i)->pos.z -= cosf((v + i)->rot.y) * (v + i)->vel;

			// 目標指定
			(v + i)->pos.x += (v + i)->nor.x;
			(v + i)->pos.z += (v + i)->nor.z;

			// 飛行高度
			(v + i)->pos.y =
				((v + i)->vel * (v + i)->timer) - 
				(0.5 * 0.15 * (v + i)->timer * (v + i)->timer);

		}

	}
}

//=============================================================================
// 設置
//=============================================================================
void SetVoiceten(Vector3 Self, Vector3 Tgt)
{
	VOICETEN *v = GetVoiceten(0);

	// 未使用のオブジェクトを捜す
	// 使用スイッチオン
	for (int i = 0; i < VOICETEN_MAX; i++)
	{
		if ((v + i)->use == FALSE)
		{
			// 到達所要距離の正規化
			(v + i)->nor = Tgt - Self / float((v + i)->dura);

			// 飛行高度の正規化

			(v + i)->pos = Self;

			(v + i)->use = TRUE;

			break;
		}
	}

}

//=============================================================================
// 消滅
//=============================================================================
void VanishVoiceten(int no)
{
	VOICETEN *v = GetVoiceten(0);

	if ((v + no)->timer >= (v + no)->dura)
	{
		// 消滅
		(v + no)->use = FALSE;

		// 初期化
		(v + no)->timer = 0;
	}
}