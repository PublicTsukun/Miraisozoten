//=============================================================================
//
// ローディング画面処理 <Loading.cpp>
//
//=============================================================================
#include "Loading.h"
#include "Common.h"
#include "Direct3D.h"
#include "Input.h"
#include "Fade.h"


#define LOADING_TEX_BACK "data/TEXTURE/SCENE/LoadBack.jpg"
#define LOADING_TEX_GAGE "data/TEXTURE/SCENE/LoadBox.jpg"
#define LOADING_TEX_TEXT "data/TEXTURE/SCENE/load.png"


//----初期化--------
void CNowLoading::Init()
{
	Back.LoadTexture(LOADING_TEX_BACK);
	Text.Init(RelativeSX(0.8f), RelativeSY(0.8f), 200, 10, LOADING_TEX_TEXT);
}

//----終了--------
void CNowLoading::Uninit(void)
{
	Back.Release();
	Text.Release();
}

//----更新--------
void CNowLoading::Progress(int per)
{
	/* 更新 */
	float percent = (float)per / 100.0f;

	/* 描画 */
	LPDIRECT3DDEVICE9 pDevice = Direct3D::GetD3DDevice();

	// バックバッファ＆Ｚバッファのクリア
	pDevice->Clear(0, NULL, (D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER), D3DCOLOR_RGBA(0x66, 0x88, 0xFF, 0xFF), 1.0f, 0);

	// Direct3Dによる描画の開始
	if (SUCCEEDED(pDevice->BeginScene()))
	{

		Back.Draw();
		Text.Draw();

		// Direct3Dによる描画の終了
		pDevice->EndScene();
	}

	// バックバッファとフロントバッファの入れ替え
	pDevice->Present(NULL, NULL, NULL, NULL);
}


