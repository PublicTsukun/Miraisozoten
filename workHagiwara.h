//=============================================================================
//
//萩原担当分　workHagiwara.h
//はぎわらなほ
//=============================================================================
#ifndef _WORKHAGIWARA_H_
#define _WORKHAGIWARA_H_
#include "windows.h"
#include "d3dx9.h"
#include <tchar.h>
#include <stdio.h>

// 頂点フォーマット( 頂点座標[2D] / 反射光 / テクスチャ座標 )
#define	FVF_VERTEX_2D	(D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1)
#define	NUM_VERTEX		(4)	// 頂点数
#define NUM_POLYGON		(2)

//=============================================================================
//構造体定義
//=============================================================================

// 上記頂点フォーマットに合わせた構造体を定義
typedef struct
{
	D3DXVECTOR3 vtx;		// 頂点座標
	float rhw;				// テクスチャのパースペクティブコレクト用
	D3DCOLOR diffuse;		// 反射光
	D3DXVECTOR2 tex;		// テクスチャ座標
} SC_VERTEX_2D;

//=============================================================================
//プロトタイプ宣言
//=============================================================================
HRESULT InitWorkHagiwara(void);
void UninitWorkHagiwara(void);
void UpdateWorkHagiwara(void);
void DrawWorkHagiwara(void);

#endif