//=============================================================================
//
// voiceten処理 [voiceten.h]
// Author : 宋彦霖
//
//=============================================================================
#ifndef _VOICETEN_INCLUDE_H_
#define _VOICETEN_INCLUDE_H_

#include "Library/Vector.h"
#include <Windows.h>
#include <d3dx9.h>

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define VOICETEN_MAX (128)	// voiceten最大数

//*****************************************************************************
// 構造体定義
//*****************************************************************************
typedef struct
{	
	bool use;		// 使用しているかどうか
	Vector3 pos;	// 位置
	Vector3 rot;	// 回転

	int timer;		// タイマー

	Vector3 start;	// 発射位置
	Vector3 tgt;	// 目標位置
	double dist;	// 到達所要距離

	int dura;		// 到達所要時間

	Vector3 nor;	// 到達所要距離の正規化
	double vel;		// 速度

	float hei;		// 限界高度



} VOICETEN;

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void InitVoiceten(void);
void UninitVoiceten(void);
void UpdateVoiceten(void);
void DrawVoiceten(void);

VOICETEN *GetVoiceten(int no);

void SetVoiceten(Vector3 Self, Vector3 Tgt);
void VanishVoiceten(int no);

#endif