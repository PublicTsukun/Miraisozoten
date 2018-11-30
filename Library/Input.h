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
#define BUTTON_00		0x00000010l	// (.rgbButtons[0]&0x80)
#define BUTTON_01		0x00000020l	// (.rgbButtons[1]&0x80)
#define BUTTON_02		0x00000040l	// (.rgbButtons[2]&0x80)
#define BUTTON_03		0x00000080l	// (.rgbButtons[3]&0x80)
#define BUTTON_04		0x00000100l	// (.rgbButtons[4]&0x80)
#define BUTTON_05		0x00000200l	// (.rgbButtons[5]&0x80)
#define BUTTON_06		0x00000400l	// (.rgbButtons[6]&0x80)
#define BUTTON_07		0x00000800l	// (.rgbButtons[7]&0x80)
#define BUTTON_08		0x00001000l	// (.rgbButtons[8]&0x80)
#define BUTTON_09		0x00002000l	// (.rgbButtons[9]&0x80)
#define BUTTON_10		0x00004000l	// (.rgbButtons[10]&0x80)
#define BUTTON_11		0x00008000l	// (.rgbButtons[11]&0x80)
#define BUTTON_12		0x00010000l	// (.rgbButtons[12]&0x80)
#define BUTTON_13		0x00020000l	// (.rgbButtons[13]&0x80)
#define BUTTON_14		0x00040000l	// (.rgbButtons[14]&0x80)
#define BUTTON_15		0x00080000l	// (.rgbButtons[15]&0x80)
#define GAMEPADMAX		4			// 同時に接続するジョイパッドの最大数をセット

#define BUTTON_LEFT		0x00100000l	// Y or < ボタン    ( 3 : 0 )(L : R)
#define BUTTON_UP		0x00200000l	// X or ^ ボタン    ( 1 : 1 )
#define BUTTON_DOWN		0x00400000l	// B or v ボタン    ( 0 : 2 )
#define BUTTON_RIGHT	0x00800000l	// A or > ボタン    ( 2 : 3 )
#define BUTTON_SR		0x01000000l	// SRボタン         ( 4 : 4 )
#define BUTTON_SL		0x02000000l	// SLボタン         ( 5 : 5 )
#define BUTTON_RxL		0x04000000l	// R or L ボタン    ( 6 : 6 )
#define BUTTON_ZRxZL	0x08000000l	// ZR or ZL ボタン  ( 7 : 7 )
#define BUTTON_PxM		0x10000000l	// + or - ボタン    ( 8 : 9 )
#define BUTTON_STICK	0x20000000l	// スティックボタン ( 11 : 10 )
#define BUTTON_HOME		0x40000000l	// ホームボタン     ( 13 : 12 )

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
BOOL IsButtonPressed(DWORD button, int no = -1);
BOOL IsButtonTriggered(DWORD button, int no = -1);
Vector3 GetGyro();
int  GetGamePad();

HRESULT InitializePad(void);			// パッド初期化

#endif