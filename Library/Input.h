//=============================================================================
//
// ���͏��� [input.h]
//
//=============================================================================
#ifndef __INPUT_INCLUDE_H__
#define __INPUT_INCLUDE_H__


#define DIRECTINPUT_VERSION (0x0800)	// �x���΍�
#include <dinput.h>
#include <d3dx9math.h>
#include <Windows.h>
#include <tchar.h>
#pragma comment (lib, "dinput8.lib")
#include "Vector.h"


//*****************************************************************************
// �}�N����`
//*****************************************************************************
// �v���O������������Ƃ��Ɏg��
#define USE_KEYBOARD	// �錾����ƃL�[�{�[�h�ő���\�ɂȂ�
#define USE_MOUSE		// �錾����ƃ}�E�X�ő���\�ɂȂ�
#define USE_PAD			// �錾����ƃp�b�h�ő���\�ɂȂ�

/* �}�E�X�\����� */
// ����
#define MOUSE_SET_CENTER	SetCursorPos((int)LAST_GAME_SCREEN_CENTER_X, (int)LAST_GAME_SCREEN_CENTER_Y)

/* GamePad */
#define RANGE_VALUE (1000)	// �L���͈́i��Βl�j

/* game pad��� */
#define LSTICK_UP		0x00000001l	// �X�e�B�b�N��(.IY<0)
#define LSTICK_DOWN		0x00000002l	// �X�e�B�b�N��(.IY>0)
#define LSTICK_LEFT		0x00000004l	// �X�e�B�b�N��(.IX<0)
#define LSTICK_RIGHT	0x00000008l	// �X�e�B�b�N�E(.IX>0)
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
#define GAMEPADMAX		4			// �����ɐڑ�����W���C�p�b�h�̍ő吔���Z�b�g

#define BUTTON_LEFT		0x00100000l	// Y or < �{�^��    ( 3 : 0 )(L : R)
#define BUTTON_UP		0x00200000l	// X or ^ �{�^��    ( 1 : 1 )
#define BUTTON_DOWN		0x00400000l	// B or v �{�^��    ( 0 : 2 )
#define BUTTON_RIGHT	0x00800000l	// A or > �{�^��    ( 2 : 3 )
#define BUTTON_SR		0x01000000l	// SR�{�^��         ( 4 : 4 )
#define BUTTON_SL		0x02000000l	// SL�{�^��         ( 5 : 5 )
#define BUTTON_RxL		0x04000000l	// R or L �{�^��    ( 6 : 6 )
#define BUTTON_ZRxZL	0x08000000l	// ZR or ZL �{�^��  ( 7 : 7 )
#define BUTTON_PxM		0x10000000l	// + or - �{�^��    ( 8 : 9 )
#define BUTTON_STICK	0x20000000l	// �X�e�B�b�N�{�^�� ( 11 : 10 )
#define BUTTON_HOME		0x40000000l	// �z�[���{�^��     ( 13 : 12 )

//*****************************************************************************
// �v���g�^�C�v�錾
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
BOOL IsMouseLeftPressed(void);      // ���N���b�N�������
BOOL IsMouseLeftTriggered(void);    // ���N���b�N�����u��
BOOL IsMouseRightPressed(void);     // �E�N���b�N�������
BOOL IsMouseRightTriggered(void);   // �E�N���b�N�����u��
BOOL IsMouseCenterPressed(void);    // ���N���b�N�������
BOOL IsMouseCenterTriggered(void);  // ���N���b�N�����u��
long GetMouseX(void);               // �}�E�X��X�����ɓ��������Βl
long GetMouseY(void);               // �}�E�X��Y�����ɓ��������Βl
long GetMouseZ(void);               // �}�E�X�z�C�[�������������Βl
POINT GetMousePoint(void);          // �}�E�X�̍��W

//---------------------------- game pad
BOOL IsButtonPressed(DWORD button, int no = -1);
BOOL IsButtonTriggered(DWORD button, int no = -1);
Vector3 GetGyro();
int  GetGamePad();

HRESULT InitializePad(void);			// �p�b�h������

#endif