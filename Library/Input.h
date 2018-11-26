//=============================================================================
//
// 入力処理 [input.h]
//
//=============================================================================
#ifndef __INPUT_INCLUDE_H__
#define __INPUT_INCLUDE_H__


#define DIRECTINPUT_VERSION (0x0800)	// 警告対策
#include <dinput.h>
#include <d3dx9math.h>
#include <Windows.h>
#include <tchar.h>
#pragma comment (lib, "dinput8.lib")
#include "Vector.h"


//*****************************************************************************
// マクロ定義
//*****************************************************************************
// プログラム分けするときに使う
#define USE_KEYBOARD	// 宣言するとキーボードで操作可能になる
#define USE_MOUSE		// 宣言するとマウスで操作可能になる
#define USE_PAD			// 宣言するとパッドで操作可能になる

/* マウス表示状態 */
// 制御
#define MOUSE_SET_CENTER	SetCursorPos((int)LAST_GAME_SCREEN_CENTER_X, (int)LAST_GAME_SCREEN_CENTER_Y)

/* GamePad */
#define RANGE_VALUE (1000)	// 有効範囲（絶対値）

/* game pad情報 */
#define LSTICK_UP		0x00000001l	// スティック上(.IY<0)
#define LSTICK_DOWN		0x00000002l	// スティック下(.IY>0)
#define LSTICK_LEFT		0x00000004l	// スティック左(.IX<0)
#define LSTICK_RIGHT	0x00000008l	// スティック右(.IX>0)
#define BUTTON_LEFT		0x00000010l	// Yボタン(.rgbButtons[0]&0x80)
#define BUTTON_UP		0x00000020l	// Xボタン(.rgbButtons[1]&0x80)
#define BUTTON_DOWN		0x00000040l	// Bボタン(.rgbButtons[2]&0x80)
#define BUTTON_RIGHT	0x00000080l	// Aボタン(.rgbButtons[3]&0x80)
#define BUTTON_SR		0x00000100l	// SRボタン(.rgbButtons[4]&0x80)
#define BUTTON_SL		0x00000200l	// SLボタン(.rgbButtons[5]&0x80)
#define BUTTON_RorL		0x00000400l	// RorLボタン(.rgbButtons[6]&0x80)
#define BUTTON_ZRorZL	0x00000800l	// ZRorZLボタン(.rgbButtons[7]&0x80)
#define BUTTON_08		0x00001000l	// NULL(.rgbButtons[8]&0x80)
#define BUTTON_PM		0x00002000l	// 記号(+ro-)ボタン(.rgbButtons[9]&0x80)
#define BUTTON_STICK	0x00004000l	// スティックボタン(.rgbButtons[10]&0x80)
#define BUTTON_11		0x00008000l	// NULL(.rgbButtons[11]&0x80)
#define BUTTON_HOME		0x00010000l	// ホームボタン(.rgbButtons[12]&0x80)
#define GAMEPADMAX		4			// 同時に接続するジョイパッドの最大数をセット


//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitInput(HINSTANCE hInst, HWND hWnd);
void UninitInput(void);
void UpdateInput(void);

//---------------------------- keyboard
bool GetKeyboardPress(int nKey);
bool GetKeyboardTrigger(int nKey);
bool GetKeyboardRepeat(int nKey);
bool GetKeyboardRelease(int nKey);

//---------------------------- mouse
BOOL IsMouseLeftPressed(void);      // 左クリックした状態
BOOL IsMouseLeftTriggered(void);    // 左クリックした瞬間
BOOL IsMouseRightPressed(void);     // 右クリックした状態
BOOL IsMouseRightTriggered(void);   // 右クリックした瞬間
BOOL IsMouseCenterPressed(void);    // 中クリックした状態
BOOL IsMouseCenterTriggered(void);  // 中クリックした瞬間
long GetMouseX(void);               // マウスがX方向に動いた相対値
long GetMouseY(void);               // マウスがY方向に動いた相対値
long GetMouseZ(void);               // マウスホイールが動いた相対値
POINT GetMousePoint(void);          // マウスの座標

//---------------------------- game pad
BOOL IsButtonPressed(int padNo, DWORD button);
BOOL IsButtonTriggered(int padNo, DWORD button);
D3DXVECTOR2 GetLStickVolume(int padNo);
D3DXVECTOR2 GetRStickVolume(int padNo);
Vector3 GetGyro(int no);

HRESULT InitializePad(void);			// パッド初期化

#endif