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
void UpdateVoiMoveY(int no);

//*****************************************************************************
// グローバル変数
//*****************************************************************************
VOICETEN VoicetenWk[VOICETEN_MAX];		// ワーク

char *FileVoiceten[] =
{
	"data/作業/voiceten00.png",
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

		(v + i)->vel = 2.0f;

		(v + i)->timer = 0;

		(v + i)->start = Vector3(0.0f, 0.0f, 0.0f);
		(v + i)->tgt = Vector3(0.0f, 0.0f, 0.0f);
		(v + i)->dura = 60;

		(v + i)->nor = Vector3(0.0f, 0.0f, 0.0f);

		(v + i)->atk = 1;

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
			//VanishVoiceten(i);
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
			(v + i)->pos.y += (v + i)->nor.y;
			(v + i)->pos.z += (v + i)->nor.z;

			UpdateVoiMoveY(i);

		}
	}
}

//=============================================================================
// 移動Y
//=============================================================================
void UpdateVoiMoveY(int no)
{
	VOICETEN *v = GetVoiceten(0);

	// 高さ調整用
	const float value = 20.0;

	// 闇
	// 処理時間 60 / 段落 20 = 3.0
	// ベジェ曲線 4ポイント (0, 0) (2, 8) (4, 8) (8, 8) Y軸だけ使用

	if (((v + no)->timer) >= 0 && ((v + no)->timer) < 3) { (v + no)->pos.y +=   float((1.14 - 0)    / 3.0 * value); }
	if (((v + no)->timer) >= 3 && ((v + no)->timer) < 6) { (v + no)->pos.y +=   float((2.16 - 1.14) / 3.0 * value); }
	if (((v + no)->timer) >= 6 && ((v + no)->timer) < 9) { (v + no)->pos.y +=   float((3.06 - 2.16) / 3.0 * value); }
	if (((v + no)->timer) >= 9 && ((v + no)->timer) < 12) { (v + no)->pos.y +=  float((3.84 - 3.06) / 3.0 * value); }
	if (((v + no)->timer) >= 12 && ((v + no)->timer) < 15) { (v + no)->pos.y += float((4.50 - 3.84) / 3.0 * value); }
	if (((v + no)->timer) >= 15 && ((v + no)->timer) < 18) { (v + no)->pos.y += float((5.04 - 4.50) / 3.0 * value); }
	if (((v + no)->timer) >= 18 && ((v + no)->timer) < 21) { (v + no)->pos.y += float((5.46 - 5.04) / 3.0 * value); }
	if (((v + no)->timer) >= 21 && ((v + no)->timer) < 24) { (v + no)->pos.y += float((5.76 - 5.46) / 3.0 * value); }
	if (((v + no)->timer) >= 24 && ((v + no)->timer) < 27) { (v + no)->pos.y += float((5.94 - 5.76) / 3.0 * value); }
	if (((v + no)->timer) >= 27 && ((v + no)->timer) < 30) { (v + no)->pos.y += float((6.0 - 5.94)  / 3.0 * value); }

	if (((v + no)->timer) >= 30 && ((v + no)->timer) < 33) { (v + no)->pos.y += float((5.94 - 6.0)  / 3.0 * value); }
	if (((v + no)->timer) >= 33 && ((v + no)->timer) < 36) { (v + no)->pos.y += float((5.76 - 5.94) / 3.0 * value); }
	if (((v + no)->timer) >= 36 && ((v + no)->timer) < 39) { (v + no)->pos.y += float((5.46 - 5.76) / 3.0 * value); }
	if (((v + no)->timer) >= 39 && ((v + no)->timer) < 42) { (v + no)->pos.y += float((5.04 - 5.46) / 3.0 * value); }
	if (((v + no)->timer) >= 42 && ((v + no)->timer) < 45) { (v + no)->pos.y += float((4.50 - 5.04) / 3.0 * value); }
	if (((v + no)->timer) >= 45 && ((v + no)->timer) < 48) { (v + no)->pos.y += float((3.84 - 4.50) / 3.0 * value); }
	if (((v + no)->timer) >= 48 && ((v + no)->timer) < 51) { (v + no)->pos.y += float((3.06 - 3.84) / 3.0 * value); }
	if (((v + no)->timer) >= 51 && ((v + no)->timer) < 54) { (v + no)->pos.y += float((2.16 - 3.06) / 3.0 * value); }
	if (((v + no)->timer) >= 54 && ((v + no)->timer) < 57) { (v + no)->pos.y += float((1.14 - 2.16) / 3.0 * value); }
	if (((v + no)->timer) >= 57 && ((v + no)->timer) < 60) { (v + no)->pos.y += float((0.0 - 1.14)  / 3.0 * value); }

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
			// 到達所要距離
			(v + i)->dist =
				sqrt(
					pow((Tgt.x - Self.x), 2) +
					pow((Tgt.y - Self.y), 2) +
					pow((Tgt.z - Self.z), 2)
					);

			// 到達所要距離の正規化
			(v + i)->nor = (Tgt - Self) / float((v + i)->dura);

			// 速度
			(v + i)->vel =
				sqrt(
					pow(((v + i)->nor.x), 2) +
					pow(((v + i)->nor.y), 2) +
					pow(((v + i)->nor.z), 2)
					);

			(v + i)->pos = Self;
			Voiceten[i].LoadObjectStatus((v + i)->pos);

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

	//if ((v + no)->timer >= (v + no)->dura)
	//{

	//}

	// 消滅
	(v + no)->use = FALSE;

	// 初期化
	(v + no)->pos = Vector3(0.0f, 0.0f, 0.0f);
	(v + no)->nor = Vector3(0.0f, 0.0f, 0.0f);
	(v + no)->timer = 0;

	Voiceten[no].LoadObjectStatus((v + no)->pos);

}