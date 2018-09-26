//=============================================================================
//
// タイトル画面処理 [title.cpp]
//
//=============================================================================
#include "title.h"
#include "Library/Input.h"
#include "Library/Fade.h"
#include "Library/ObjectBase2D.h"


//ワークのインクルード
#include "workHagiwara.h"
#include "workKimura.h"
#include "workSato.h"
#include "workSon.h"
#include "workTsu.h"
#include "workUtsugi.h"
#include "workYamaguchi.h"
#include "workYamamoto.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************


//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************


//*****************************************************************************
// グローバル変数
//*****************************************************************************


//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitTitle(void)
{
	InitWorkHagiwara();
	InitWorkKimura();
	InitWorkSato();
	InitWorkSon();
	InitWorkTsu();
	InitWorkUtsugi();
	InitWorkYamaguchi();
	InitWorkYamamoto();



	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitTitle(void)
{
	UninitWorkHagiwara();
	UninitWorkKimura();
	UninitWorkSato();
	UninitWorkSon();
	UninitWorkTsu();
	UninitWorkUtsugi();
	UninitWorkYamaguchi();
	UninitWorkYamamoto();

}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateTitle(void)
{
	UpdateWorkHagiwara();
	UpdateWorkKimura();
	UpdateWorkSato();
	UpdateWorkSon();
	UpdateWorkTsu();
	UpdateWorkUtsugi();
	UpdateWorkYamaguchi();
	UpdateWorkYamamoto();

}

//=============================================================================
// 描画処理
//=============================================================================
void DrawTitle(void)
{
	DrawWorkHagiwara();
	DrawWorkKimura();
	DrawWorkSato();
	DrawWorkSon();
	DrawWorkTsu();
	DrawWorkUtsugi();
	DrawWorkYamaguchi();
	DrawWorkYamamoto();

}

