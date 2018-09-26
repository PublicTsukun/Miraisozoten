//=============================================================================
//
// voiceten処理 [voiceten.h]
// Author : 宋彦霖
//
//=============================================================================
#ifndef _VOICETEN_INCLUDE_H_
#define _VOICETEN_INCLUDE_H_

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
	bool use;	// 使用しているかどうか
	float vel;	// 速度

} VOICETEN;

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void InitVoiceten(void);
void UninitVoiceten(void);
void UpdateVoiceten(void);
void DrawVoiceten(void);

VOICETEN *GetVoiceten(int no);

void SetVoiceten(D3DXVECTOR3 Self, D3DXVECTOR3 Tgt);
void VanishVoiceten(int no);

#endif