//=============================================================================
//
// メイン処理 [main.cpp]
//
//=============================================================================
#include "Library/Common.h"
#include "Library/TsuLibSystem.h"
#include "Library/WindowClass.h"
#include "Library/Direct3D.h"
#include "Library/FPSManager.h"
#include "Library/Input.h"
#include "Library/Sound.h"
#include "Library/Fade.h"
#include "Library/Camera.h"
#include "Library/Light.h"
#include "Library/DebugProcess.h"
#include "FadeCurtain.h"
#include "SceneManager.h"


//****************************************************************
// マクロ定義
//****************************************************************
#define CLASS_NAME  "hal2018FCEgameApplication"	// ウインドウのクラス名
#define WINDOW_NAME "ふぉるてっしも！"	// ウインドウのキャプション名


//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT Init(void);
void Uninit(void);
void Update(void);
void Draw(void);


//*****************************************************************************
// グローバル変数:
//*****************************************************************************
bool DispDebug = true;	// デバッグ表示ON/OFF


//=============================================================================
// メイン関数
//=============================================================================
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);	// 無くても良いけど、警告が出る（未使用宣言）
	UNREFERENCED_PARAMETER(lpCmdLine);		// 無くても良いけど、警告が出る（未使用宣言）

	// TSUシステムを初期化
	if (FAILED(TsuSystem::Initialize(hInstance)))
		return -1;

	// その他初期化
	if (FAILED(Init()))
		return -1;

	//フレームカウント初期化
	timeBeginPeriod(1);	// 分解能設定
	FPSManager::Init();	// FPS制御

	/* メッセージループ */
	while (1)
	{
		if (WindowClass::CheckMessage())
			break;

		if (FPSManager::FramerateControl())
		{
			PrintDebugProcess("FPS : %f    ", FPSManager::DisplayFPS(FPS_NORMAL));
			PrintDebugProcess("SCENE : ");
			switch (Scene::SetScene(SCENE_MAX))
			{
			case SCENE_TITLE:   PrintDebugProcess("Title\n");       break;
			case SCENE_GAME:    PrintDebugProcess("Game\n");        break;
			case SCENE_PAUSE:   PrintDebugProcess("Pause\n");       break;
			case SCENE_RESULT:  PrintDebugProcess("Result\n");      break;
			case SCENE_MAX:     PrintDebugProcess("処理中...\n");   break;
			case SCENE_END:     PrintDebugProcess("終了処理です(表示されないはずだよ)\n");   break;
			}

			switch (Scene::GetFadeState())
			{
			case CLOSS:
				if (Scene::UpdateFade())
				{
					Scene::SetScene(SCENE_GAME);
				}
				break;
			case OPEN:
				if (Scene::UpdateFade())
				{
					Scene::SetFadeState(SLEEP);
				}
				break;
			case SLEEP:
				Update();	// 更新処理
				break;
			}
			Draw();		// 描画処理
		}
	}

	Uninit();					// その他終了処理
	TsuSystem::Uninitialize();	// TSUシステムを初期化

	timeEndPeriod(1);	// 分解能を戻す

	return 0;
}


//=============================================================================
// 初期化処理
//=============================================================================
HRESULT Init()
{
	// フェード
	CSFade::MakeVertex();
	FadeCurtain::Init();

	// タイトルシーンにセット
	Scene::SetScene(SCENE_TITLE, false);

	// カメラ
	InitCamera();

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void Uninit(void)
{
	// フェード
	FadeCurtain::Uninit();

	Scene::SetScene(SCENE_END);

}

//=============================================================================
// 更新処理
//=============================================================================
void Update(void)
{
	// 入力の更新処理
	UpdateInput();

	// カメラの更新処理
	UpdateCamera(Vector3());

	if (GetKeyboardTrigger(DIK_F3))
	{// デバッグ表示ON/OFF
		DispDebug = DispDebug ? false : true;
	}

	// シーンの更新
	Scene::Update();

	// フェード処理の更新
	CSFade::Update();

}

//=============================================================================
// 描画処理
//=============================================================================
void Draw(void)
{
	// バックバッファ＆Ｚバッファのクリア
	Direct3D::GetD3DDevice()->Clear(0, NULL, (D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER),
		D3DCOLOR_RGBA(0x66, 0x88, 0xFF, 0xFF), 1.0f, 0);

	// Direct3Dによる描画の開始
	if (SUCCEEDED(Direct3D::GetD3DDevice()->BeginScene()))
	{
		// カメラ
		SetCamera();

		// シーンの描画
		Scene::Draw();

		// フェード描画
		CSFade::Draw();

		// デバッグ表示の描画処理
		if (DispDebug)
		{
			DrawDebugProcess();
		}

		// Direct3Dによる描画の終了
		Direct3D::GetD3DDevice()->EndScene();
	}

	// バックバッファとフロントバッファの入れ替え
	Direct3D::GetD3DDevice()->Present(NULL, NULL, NULL, NULL);
}


