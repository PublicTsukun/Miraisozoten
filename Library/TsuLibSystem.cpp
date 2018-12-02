#include "TsuLibSystem.h"
#include "WindowClass.h"
#include "Direct3D.h"
#include "Input.h"
#include "Sound.h"
#include "DebugProcess.h"


HRESULT TSULibrarySystem::Initialize(HINSTANCE hInstance)
{
	// ウィンドウ初期化
	if (FAILED(WindowClass::Init(hInstance)))
		return -1;

	// グラフィックス初期化(Direct3D)
	if (FAILED(Direct3D::Init(WindowClass::GetHWnd(), TRUE)))
		return -1;

	// インプット初期化
	if (FAILED(InitInput(WindowClass::GetHInstance(), WindowClass::GetHWnd())))
		return -1;

	// サウンド初期化
	if (FAILED(DirectSound::Init(WindowClass::GetHWnd())))
		return -1;

	// デバッグ表示の初期化
	InitDebugProcess();

	return S_OK;
}

void TSULibrarySystem::Uninitialize()
{
	WindowClass::Uninit();	// ウィンドウ終了
	Direct3D::Uninit();		// グラフィックス終了(Direct3D)
	UninitInput();			// 入力の終了処理
	DirectSound::Uninit();	// サウンド終了処理
	UninitDebugProcess();	// デバッグ表示処理の終了処理

}



