//=============================================================================
//
// 入力処理 [input.cpp]
//
//=============================================================================
#include "Input.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	NUM_KEY_MAX			(256)


// game pad用設定値
#define DEADZONE		(1000)			// 各軸の10%を無効ゾーンとする
#define RANGE_MAX		 RANGE_VALUE	// 有効範囲の最大値
#define RANGE_MIN		-RANGE_VALUE	// 有効範囲の最小値 (*上より代用中)


//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************

HRESULT InitKeyboard(HINSTANCE hInst, HWND hWnd);
void UninitKeyboard(void);
HRESULT UpdateKeyboard(void);

HRESULT InitializeMouse(HINSTANCE hInst, HWND hWindow); // マウスの初期化
void UninitMouse();						// マウスの終了処理
HRESULT UpdateMouse();					// マウスの更新処理

//HRESULT InitializePad(void);			// パッド初期化
//BOOL CALLBACK SearchPadCallback(LPDIDEVICEINSTANCE lpddi, LPVOID);	// パッド検査コールバック
void UpdatePad(void);
void UninitPad(void);

//*****************************************************************************
// グローバル変数
//*****************************************************************************

//---------------------- キーボード (keyboard)
LPDIRECTINPUT8			g_pDInput = NULL;					// IDirectInput8インターフェースへのポインタ
LPDIRECTINPUTDEVICE8	g_pDIDevKeyboard = NULL;			// IDirectInputDevice8インターフェースへのポインタ(キーボード)
BYTE					g_keyState[NUM_KEY_MAX];			// キーボードの状態を受け取るワーク
BYTE					g_keyStateTrigger[NUM_KEY_MAX];		// キーボードの状態を受け取るワーク
BYTE					g_keyStateRepeat[NUM_KEY_MAX];		// キーボードの状態を受け取るワーク
BYTE					g_keyStateRelease[NUM_KEY_MAX];		// キーボードの状態を受け取るワーク
int						g_keyStateRepeatCnt[NUM_KEY_MAX];	// キーボードのリピートカウンタ

//-------------------------- マウス (mouse)
LPDIRECTINPUTDEVICE8 pMouse = NULL;	// mouse

DIMOUSESTATE2	mouseState;			// マウスのダイレクトな状態
DIMOUSESTATE2	mouseTrigger;		// 押された瞬間だけON

POINT			s_MouseCursor;		// マウスカーソルの絶対位置(スクリーン)の取得

//-------------------------- ゲームパッド (game pad)

LPDIRECTINPUTDEVICE8	pGamePad[GAMEPADMAX] = {NULL,NULL,NULL,NULL};// パッドデバイス

DWORD		padState[GAMEPADMAX];		// パッド情報（複数対応）
DWORD		padTrigger[GAMEPADMAX];
Vector3		padGyro[GAMEPADMAX];
D3DXVECTOR2	padLsRoll[GAMEPADMAX];		// 左スティックの倒状態
D3DXVECTOR2	padRsRoll[GAMEPADMAX];		// 右スティックの倒状態
bool		padNowUseSide = true;		// 現在使用している(true = 左 : false = 右)
int			padCount = 0;				// 検出したパッドの数

//=============================================================================
// 入力処理の初期化
//=============================================================================
HRESULT InitInput(HINSTANCE hInst, HWND hWnd)
{
	HRESULT hr;

	if(!g_pDInput)
	{
		// DirectInputオブジェクトの作成
		hr = DirectInput8Create(hInst, DIRECTINPUT_VERSION,
									IID_IDirectInput8, (void**)&g_pDInput, NULL);
	}

	// キーボードの初期化
	InitKeyboard(hInst, hWnd);

 	// マウスの初期化
	InitializeMouse(hInst, hWnd);
	
	// パッドの初期化
	InitializePad();

	return S_OK;
}

//=============================================================================
// 入力処理の終了処理
//=============================================================================
void UninitInput(void)
{
	// キーボードの終了処理
	UninitKeyboard();

	// マウスの終了処理
	UninitMouse();

	// パッドの終了処理
	UninitPad();

	if(g_pDInput)
	{
		g_pDInput->Release();
		g_pDInput = NULL;
	}
}

//=============================================================================
// 入力処理の更新処理
//=============================================================================
void UpdateInput(void)
{
	// キーボードの更新
	UpdateKeyboard();
	
	// マウスの更新
	UpdateMouse();
	
	// パッドの更新
	UpdatePad();

}

//=============================================================================
// キーボードの初期化
//=============================================================================
HRESULT InitKeyboard(HINSTANCE hInst, HWND hWnd)
{
	HRESULT hr;

	// デバイスオブジェクトを作成
	hr = g_pDInput->CreateDevice(GUID_SysKeyboard, &g_pDIDevKeyboard, NULL);
	if(FAILED(hr) || g_pDIDevKeyboard == NULL)
	{
		MessageBox(hWnd, "キーボードがねぇ！", "警告！", MB_ICONWARNING);
		return hr;
	}

	// データフォーマットを設定
	hr = g_pDIDevKeyboard->SetDataFormat(&c_dfDIKeyboard);
	if(FAILED(hr))
	{
		MessageBox(hWnd, "キーボードのデータフォーマットを設定できませんでした。", "警告！", MB_ICONWARNING);
		return hr;
	}

	// 協調モードを設定（フォアグラウンド＆非排他モード）
	hr = g_pDIDevKeyboard->SetCooperativeLevel(hWnd, (DISCL_FOREGROUND | DISCL_NONEXCLUSIVE));
	if(FAILED(hr))
	{
		MessageBox(hWnd, "キーボードの協調モードを設定できませんでした。", "警告！", MB_ICONWARNING);
		return hr;
	}

	// キーボードへのアクセス権を獲得(入力制御開始)
	g_pDIDevKeyboard->Acquire();

	return S_OK;
}

//=============================================================================
// キーボードの終了処理
//=============================================================================
void UninitKeyboard(void)
{
	if(g_pDIDevKeyboard)
	{
		g_pDIDevKeyboard->Release();
		g_pDIDevKeyboard = NULL;
	}
}

//=============================================================================
// キーボードの更新
//=============================================================================
HRESULT UpdateKeyboard(void)
{
	HRESULT hr;
	BYTE keyStateOld[256];

	// 前回のデータを保存
	memcpy(keyStateOld, g_keyState, NUM_KEY_MAX);

	// デバイスからデータを取得
	hr = g_pDIDevKeyboard->GetDeviceState(sizeof(g_keyState), g_keyState);
	if(SUCCEEDED(hr))
	{
		for(int cnt = 0; cnt < NUM_KEY_MAX; cnt++)
		{
			g_keyStateTrigger[cnt] = (keyStateOld[cnt] ^ g_keyState[cnt]) & g_keyState[cnt];
			g_keyStateRelease[cnt] = (keyStateOld[cnt] ^ g_keyState[cnt]) & ~g_keyState[cnt];
			g_keyStateRepeat[cnt] = g_keyStateTrigger[cnt];

			if(g_keyState[cnt])
			{
				g_keyStateRepeatCnt[cnt]++;
				if(g_keyStateRepeatCnt[cnt] >= 20)
				{
					g_keyStateRepeat[cnt] = g_keyState[cnt];
				}
			}
			else
			{
				g_keyStateRepeatCnt[cnt] = 0;
				g_keyStateRepeat[cnt] = 0;
			}
		}
	}
	else
	{
		// キーボードへのアクセス権を取得
		g_pDIDevKeyboard->Acquire();
	}

	return S_OK;
}

//=============================================================================
// キーボードのプレス状態を取得
//=============================================================================
bool GetKeyboardPress(int key)
{
	return (g_keyState[key] & 0x80) ? true : false;
}

//=============================================================================
// キーボードのトリガー状態を取得
//=============================================================================
bool GetKeyboardTrigger(int key)
{
	return (g_keyStateTrigger[key] & 0x80) ? true : false;
}

//=============================================================================
// キーボードのリピート状態を取得
//=============================================================================
bool GetKeyboardRepeat(int key)
{
	return (g_keyStateRepeat[key] & 0x80) ? true : false;
}

//=============================================================================
// キーボードのリリ－ス状態を取得
//=============================================================================
bool GetKeyboardRelease(int key)
{
	return (g_keyStateRelease[key] & 0x80) ? true : false;
}


//=============================================================================
// マウス関係の処理
//=============================================================================
// マウスの初期化
HRESULT InitializeMouse(HINSTANCE hInst,HWND hWindow)
{
	HRESULT result;
	// デバイス作成
	result = g_pDInput->CreateDevice(GUID_SysMouse,&pMouse,NULL);
	if(FAILED(result) || pMouse==NULL)
	{
		MessageBox(hWindow,"No mouse","Warning",MB_OK | MB_ICONWARNING);
		return result;
	}
	// データフォーマット設定
	result = pMouse->SetDataFormat(&c_dfDIMouse2);
	if(FAILED(result))
	{
		MessageBox(hWindow,"Can't setup mouse","Warning",MB_OK | MB_ICONWARNING);
		return result;
	}
	// 他のアプリと協調モードに設定
	result = pMouse->SetCooperativeLevel(hWindow, (DISCL_FOREGROUND | DISCL_NONEXCLUSIVE));
	if(FAILED(result))
	{
		MessageBox(hWindow,"Mouse mode error","Warning",MB_OK | MB_ICONWARNING);
		return result;
	}
	
	// デバイスの設定
	DIPROPDWORD prop;
	
	prop.diph.dwSize = sizeof(prop);
	prop.diph.dwHeaderSize = sizeof(prop.diph);
	prop.diph.dwObj = 0;
	prop.diph.dwHow = DIPH_DEVICE;
	prop.dwData = DIPROPAXISMODE_REL;		// マウスの移動値 相対値

	result = pMouse->SetProperty(DIPROP_AXISMODE,&prop.diph);
	if(FAILED(result))
	{
		MessageBox(hWindow,"Mouse property error","Warning",MB_OK | MB_ICONWARNING);
		return result;	
	}
	
	// アクセス権を得る
	pMouse->Acquire();
	return result;
}
//---------------------------------------------------------
void UninitMouse()
{
	if(pMouse)
	{
		pMouse->Unacquire();
		pMouse->Release();
		pMouse = NULL;
	}

}
//-----------------------------------------------------------
HRESULT UpdateMouse()
{
	HRESULT result;

	// 前回の値保存
	DIMOUSESTATE2 lastMouseState = mouseState;
	// データ取得
	result = pMouse->GetDeviceState(sizeof(mouseState), &mouseState);
	if (SUCCEEDED(result))
	{
		mouseTrigger.lX = mouseState.lX;
		mouseTrigger.lY = mouseState.lY;
		mouseTrigger.lZ = mouseState.lZ;
		// マウスのボタン状態
		for (int i = 0; i < 8; i++)
		{
			mouseTrigger.rgbButtons[i] = ((lastMouseState.rgbButtons[i] ^
				mouseState.rgbButtons[i]) & mouseState.rgbButtons[i]);
		}
	}
	else	// 取得失敗
	{
		// アクセス権を得てみる
		result = pMouse->Acquire();
	}

	//マウスの現在の座標を取得する
	GetCursorPos(&s_MouseCursor);

	return result;
}

//----------------------------------------------
// 左ボタンの状態
//----------------------------------------------
//----押下----
BOOL IsMouseLeftPressed(void)
{
	return (BOOL)(mouseState.rgbButtons[0] & 0x80);	// 押されたときに立つビットを検査
}
//----トリガー----
BOOL IsMouseLeftTriggered(void)
{
	return (BOOL)(mouseTrigger.rgbButtons[0] & 0x80);
}
//----------------------------------------------
// 右ボタンの状態
//----------------------------------------------
//----押下----
BOOL IsMouseRightPressed(void)
{
	return (BOOL)(mouseState.rgbButtons[1] & 0x80);
}
//----トリガー----
BOOL IsMouseRightTriggered(void)
{
	return (BOOL)(mouseTrigger.rgbButtons[1] & 0x80);
}
//----------------------------------------------
// 中ボタンの状態
//----------------------------------------------
//----押下----
BOOL IsMouseCenterPressed(void)
{
	return (BOOL)(mouseState.rgbButtons[2] & 0x80);
}
//----トリガー----
BOOL IsMouseCenterTriggered(void)
{
	return (BOOL)(mouseTrigger.rgbButtons[2] & 0x80);
}
//----------------------------------------------
// マウスのダイレクト情報
//----------------------------------------------
//------------------ (移動量)
long GetMouseX(void)
{
	return mouseState.lX;
}
long GetMouseY(void)
{
	return mouseState.lY;
}
long GetMouseZ(void)
{
	return mouseState.lZ;
}
//------------------ (座標)
POINT GetMousePoint(void)
{
	return s_MouseCursor;
}


//=============================================================================
// ゲームパッド関係の処理
//=============================================================================
//---------------------------------------- コールバック関数
BOOL CALLBACK SearchGamePadCallback(LPDIDEVICEINSTANCE lpddi, LPVOID )
{
	HRESULT result;

	result = g_pDInput->CreateDevice(lpddi->guidInstance, &pGamePad[padCount++], NULL);
	return DIENUM_CONTINUE;	// 次のデバイスを列挙

}
//---------------------------------------- 初期化
HRESULT InitializePad(void)			// パッド初期化
{
	HRESULT		result;
	int			i;

	padCount = 0;
	// ジョイパッドを探す
	g_pDInput->EnumDevices(DI8DEVCLASS_GAMECTRL,
		(LPDIENUMDEVICESCALLBACK)SearchGamePadCallback,
		NULL,
		DIEDFL_ATTACHEDONLY);
	// セットしたコールバック関数が、パッドを発見した数だけ呼ばれる。

	for (i = 0; i < padCount; i++) {
		// ジョイスティック用のデータ・フォーマットを設定
		result = pGamePad[i]->SetDataFormat(&c_dfDIJoystick);
		if (FAILED(result))
			return false; // データフォーマットの設定に失敗

		// モードを設定（フォアグラウンド＆非排他モード）
//		result = pGamePad[i]->SetCooperativeLevel(hWindow, DISCL_NONEXCLUSIVE | DISCL_FOREGROUND);
//		if ( FAILED(result) )
//			return false; // モードの設定に失敗

		// 軸の値の範囲を設定
		// X軸、Y軸のそれぞれについて、オブジェクトが報告可能な値の範囲をセットする。
		// (max-min)は、最大10,000(?)。(max-min)/2が中央値になる。
		// 差を大きくすれば、アナログ値の細かな動きを捕らえられる。(パッドの性能による)
		DIPROPRANGE				diprg;
		ZeroMemory(&diprg, sizeof(diprg));
		diprg.diph.dwSize = sizeof(diprg);
		diprg.diph.dwHeaderSize = sizeof(diprg.diph);
		diprg.diph.dwHow = DIPH_BYOFFSET;
		diprg.lMin = -RANGE_MAX; //* /=RANGE_MIN
		diprg.lMax = RANGE_MAX;
		// X軸の範囲を設定
		diprg.diph.dwObj = DIJOFS_X;
		pGamePad[i]->SetProperty(DIPROP_RANGE, &diprg.diph);
		// Y軸の範囲を設定
		diprg.diph.dwObj = DIJOFS_Y;
		pGamePad[i]->SetProperty(DIPROP_RANGE, &diprg.diph);
		// Z軸の範囲を設定
		diprg.diph.dwObj = DIJOFS_Z;
		pGamePad[i]->SetProperty(DIPROP_RANGE, &diprg.diph);
		// X回転の範囲を設定
		diprg.diph.dwObj = DIJOFS_RX;
		pGamePad[i]->SetProperty(DIPROP_RANGE, &diprg.diph);
		// Y回転の範囲を設定
		diprg.diph.dwObj = DIJOFS_RY;
		pGamePad[i]->SetProperty(DIPROP_RANGE, &diprg.diph);
		// Z回転の範囲を設定
		diprg.diph.dwObj = DIJOFS_RZ;
		pGamePad[i]->SetProperty(DIPROP_RANGE, &diprg.diph);
		// Sliderの範囲を設定
		diprg.diph.dwObj = DIJOFS_SLIDER(0);
		pGamePad[i]->SetProperty(DIPROP_RANGE, &diprg.diph);
		diprg.diph.dwObj = DIJOFS_SLIDER(1);
		pGamePad[i]->SetProperty(DIPROP_RANGE, &diprg.diph);


		// 各軸ごとに、無効のゾーン値を設定する。
		// 無効ゾーンとは、中央からの微少なジョイスティックの動きを無視する範囲のこと。
		// 指定する値は、10000に対する相対値(2000なら20パーセント)。
		DIPROPDWORD				dipdw;
		dipdw.diph.dwSize = sizeof(DIPROPDWORD);
		dipdw.diph.dwHeaderSize = sizeof(dipdw.diph);
		dipdw.diph.dwHow = DIPH_BYOFFSET;
		dipdw.dwData = DEADZONE;
		//X軸の無効ゾーンを設定
		dipdw.diph.dwObj = DIJOFS_X;
		pGamePad[i]->SetProperty(DIPROP_DEADZONE, &dipdw.diph);
		//Y軸の無効ゾーンを設定
		dipdw.diph.dwObj = DIJOFS_Y;
		pGamePad[i]->SetProperty(DIPROP_DEADZONE, &dipdw.diph);
		//Z軸の無効ゾーンを設定
		dipdw.diph.dwObj = DIJOFS_Z;
		pGamePad[i]->SetProperty(DIPROP_DEADZONE, &dipdw.diph);
		//X回転の無効ゾーンを設定
		dipdw.diph.dwObj = DIJOFS_RX;
		pGamePad[i]->SetProperty(DIPROP_DEADZONE, &dipdw.diph);
		//Y回転の無効ゾーンを設定
		dipdw.diph.dwObj = DIJOFS_RY;
		pGamePad[i]->SetProperty(DIPROP_DEADZONE, &dipdw.diph);

		//ジョイスティック入力制御開始
		pGamePad[i]->Acquire();
	}

	padNowUseSide = true;

	return true;

}
//------------------------------------------- 終了処理
void UninitPad(void)
{
	for (int i=0 ; i<GAMEPADMAX ; i++) {
		if ( pGamePad[i] )
		{
			pGamePad[i]->Unacquire();
			pGamePad[i]->Release();
		}
	}

}

//------------------------------------------ 更新
void UpdatePad(void)
{
	HRESULT			result;
	DIJOYSTATE2		dijs;
	int				i;

	for (i = 0; i < padCount; i++)
	{
		DWORD lastPadState;
		lastPadState = padState[i];
		padState[i] = 0x00000000l;	// 初期化

		result = pGamePad[i]->Poll();	// ジョイスティックにポールをかける
		if (FAILED(result)) {
			result = pGamePad[i]->Acquire();
			while (result == DIERR_INPUTLOST)
				result = pGamePad[i]->Acquire();
		}

		result = pGamePad[i]->GetDeviceState(sizeof(DIJOYSTATE), &dijs);	// デバイス状態を読み取る
		if (result == DIERR_INPUTLOST || result == DIERR_NOTACQUIRED) {
			result = pGamePad[i]->Acquire();
			while (result == DIERR_INPUTLOST)
				result = pGamePad[i]->Acquire();
		}

		// ３２の各ビットに意味を持たせ、ボタン押下に応じてビットをオンにする
		//* y-axis (Lforward)
		if (dijs.lY < 0)				padState[i] |= LSTICK_UP;
		//* y-axis (Lbackward)
		if (dijs.lY > 0)				padState[i] |= LSTICK_DOWN;
		//* x-axis (Lleft)
		if (dijs.lX < 0)				padState[i] |= LSTICK_LEFT;
		//* x-axis (Lright)
		if (dijs.lX > 0)				padState[i] |= LSTICK_RIGHT;

		//* ボタン00
		if (dijs.rgbButtons[0] & 0x80)		padState[i] |= BUTTON_00;
		//* ボタン01
		if (dijs.rgbButtons[1] & 0x80)		padState[i] |= BUTTON_01;
		//* ボタン02
		if (dijs.rgbButtons[2] & 0x80)		padState[i] |= BUTTON_02;
		//* ボタン03
		if (dijs.rgbButtons[3] & 0x80)		padState[i] |= BUTTON_03;
		//* ボタン04
		if (dijs.rgbButtons[4] & 0x80)		padState[i] |= BUTTON_04;
		//* ボタン05
		if (dijs.rgbButtons[5] & 0x80)		padState[i] |= BUTTON_05;
		//* ボタン06
		if (dijs.rgbButtons[6] & 0x80)		padState[i] |= BUTTON_06;
		//* ボタン07
		if (dijs.rgbButtons[7] & 0x80)		padState[i] |= BUTTON_07;
		//* ボタン08
		if (dijs.rgbButtons[8] & 0x80)		padState[i] |= BUTTON_08;
		//* ボタン09
		if (dijs.rgbButtons[9] & 0x80)		padState[i] |= BUTTON_09;
		//* ボタン10
		if (dijs.rgbButtons[10] & 0x80)		padState[i] |= BUTTON_10;
		//* ボタン11
		if (dijs.rgbButtons[11] & 0x80)		padState[i] |= BUTTON_11;
		//* ボタン12
		if (dijs.rgbButtons[12] & 0x80)		padState[i] |= BUTTON_12;
		//* ボタン13
		if (dijs.rgbButtons[13] & 0x80)		padState[i] |= BUTTON_13;
		//* ボタン14
		if (dijs.rgbButtons[14] & 0x80)		padState[i] |= BUTTON_14;
		//* ボタン15
		if (dijs.rgbButtons[15] & 0x80)		padState[i] |= BUTTON_15;

		if (dijs.rgbButtons[13] & 0x80)
		{
			padNowUseSide = true;
		}
		else if (dijs.rgbButtons[12] & 0x80)
		{
			padNowUseSide = false;
		}

		// 左右のジョイコンに対応させる
		if (padNowUseSide)
		{
			if (dijs.rgbButtons[0] & 0x80)	padState[i] |= BUTTON_DOWN;
			if (dijs.rgbButtons[1] & 0x80)	padState[i] |= BUTTON_UP;
			if (dijs.rgbButtons[2] & 0x80)	padState[i] |= BUTTON_RIGHT;
			if (dijs.rgbButtons[3] & 0x80)	padState[i] |= BUTTON_LEFT;
		}
		else
		{
			if (dijs.rgbButtons[0] & 0x80)	padState[i] |= BUTTON_LEFT;
			if (dijs.rgbButtons[1] & 0x80)	padState[i] |= BUTTON_UP;
			if (dijs.rgbButtons[2] & 0x80)	padState[i] |= BUTTON_DOWN;
			if (dijs.rgbButtons[3] & 0x80)	padState[i] |= BUTTON_RIGHT;
		}

		// Trigger設定
		padTrigger[i] = ((lastPadState ^ padState[i])	// 前回と違っていて
			& padState[i]);					// しかも今ONのやつ

		/* ジャイロデータの保存 */
		padGyro[i] = Vector3((float)dijs.rglSlider[0], (float)dijs.rglSlider[1], (float)dijs.lRz);

		// Roll設定
//		padLsRoll[i] = D3DXVECTOR2(dijs.lX / (float)(RANGE_MAX), -(dijs.lY / (float)(RANGE_MAX)));
//		padRsRoll[i] = D3DXVECTOR2(dijs.lRx / (float)(RANGE_MAX), dijs.lRy / (float)(RANGE_MAX));
	}
	//PrintDebugProcess("l   : (%ld)(%ld)(%ld)\n", dijs.lX, dijs.lY, dijs.lZ);
	//PrintDebugProcess("lR  : (%ld)(%ld)(%ld)\n", dijs.lRx, dijs.lRy, dijs.lRz);
	//PrintDebugProcess("rS  : (%ld)(%ld)\n", dijs.rglSlider[0], dijs.rglSlider[1]);
	//PrintDebugProcess("十字キー : (%ld)", dijs.rgdwPOV[0]);
	//PrintDebugProcess("(%ld)", dijs.rgdwPOV[1]);
	//PrintDebugProcess("(%ld)", dijs.rgdwPOV[2]);
	//PrintDebugProcess("(%ld)\n", dijs.rgdwPOV[3]);
	//PrintDebugProcess("lV  : (%ld)(%ld)(%ld)\n", dijs.lVX, dijs.lVY, dijs.lVZ);
	//PrintDebugProcess("lVR : (%ld)(%ld)(%ld)\n", dijs.lVRx, dijs.lVRy, dijs.lVRz);
	//PrintDebugProcess("rVS : (%ld)(%ld)\n", dijs.rglVSlider[0], dijs.rglVSlider[1]);
	//PrintDebugProcess("lA  : (%ld)(%ld)(%ld)\n", dijs.lAX, dijs.lAY, dijs.lAZ);
	//PrintDebugProcess("lAR : (%ld)(%ld)(%ld)\n", dijs.lARx, dijs.lARy, dijs.lARz);
	//PrintDebugProcess("rAS : (%ld)(%ld)\n", dijs.rglASlider[0], dijs.rglASlider[1]);
	//PrintDebugProcess("lF  : (%ld)(%ld)(%ld)\n", dijs.lFX, dijs.lFY, dijs.lFZ);
	//PrintDebugProcess("lFR : (%ld)(%ld)(%ld)\n", dijs.lFRx, dijs.lFRy, dijs.lFRz);
	//PrintDebugProcess("rFS : (%ld)(%ld)\n", dijs.rglFSlider[0], dijs.rglFSlider[1]);
	//PrintDebugProcess("\n");

}
//----------------------------------------------- 検査
BOOL IsButtonPressed(DWORD button)
{
	return (button & padState[padNowUseSide ? 0 : 1]);
}
BOOL IsButtonTriggered(DWORD button)
{
	return (button & padTrigger[padNowUseSide ? 0 : 1]);
}

Vector3 GetGyro()
{
	if (padNowUseSide)
	{// -がついているのは入力値と画面方向を合わせるため
		return Vector3(padGyro[0].x, padGyro[0].y, -padGyro[0].z);
	}
	return Vector3(-padGyro[1].x, padGyro[1].y, -padGyro[1].z);
}

