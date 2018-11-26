//=============================================================================
//
// ���͏��� [input.cpp]
//
//=============================================================================
#include "Input.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	NUM_KEY_MAX			(256)


// game pad�p�ݒ�l
#define DEADZONE		(1000)			// �e����10%�𖳌��]�[���Ƃ���
#define RANGE_MAX		 RANGE_VALUE	// �L���͈͂̍ő�l
#define RANGE_MIN		-RANGE_VALUE	// �L���͈͂̍ŏ��l (*�����p��)


//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************

HRESULT InitKeyboard(HINSTANCE hInst, HWND hWnd);
void UninitKeyboard(void);
HRESULT UpdateKeyboard(void);

HRESULT InitializeMouse(HINSTANCE hInst, HWND hWindow); // �}�E�X�̏�����
void UninitMouse();						// �}�E�X�̏I������
HRESULT UpdateMouse();					// �}�E�X�̍X�V����

//HRESULT InitializePad(void);			// �p�b�h������
//BOOL CALLBACK SearchPadCallback(LPDIDEVICEINSTANCE lpddi, LPVOID);	// �p�b�h�����R�[���o�b�N
void UpdatePad(void);
void UninitPad(void);

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************

//---------------------- �L�[�{�[�h (keyboard)
LPDIRECTINPUT8			g_pDInput = NULL;					// IDirectInput8�C���^�[�t�F�[�X�ւ̃|�C���^
LPDIRECTINPUTDEVICE8	g_pDIDevKeyboard = NULL;			// IDirectInputDevice8�C���^�[�t�F�[�X�ւ̃|�C���^(�L�[�{�[�h)
BYTE					g_keyState[NUM_KEY_MAX];			// �L�[�{�[�h�̏�Ԃ��󂯎�郏�[�N
BYTE					g_keyStateTrigger[NUM_KEY_MAX];		// �L�[�{�[�h�̏�Ԃ��󂯎�郏�[�N
BYTE					g_keyStateRepeat[NUM_KEY_MAX];		// �L�[�{�[�h�̏�Ԃ��󂯎�郏�[�N
BYTE					g_keyStateRelease[NUM_KEY_MAX];		// �L�[�{�[�h�̏�Ԃ��󂯎�郏�[�N
int						g_keyStateRepeatCnt[NUM_KEY_MAX];	// �L�[�{�[�h�̃��s�[�g�J�E���^

//-------------------------- �}�E�X (mouse)
LPDIRECTINPUTDEVICE8 pMouse = NULL;	// mouse

DIMOUSESTATE2	mouseState;			// �}�E�X�̃_�C���N�g�ȏ��
DIMOUSESTATE2	mouseTrigger;		// �����ꂽ�u�Ԃ���ON

POINT			s_MouseCursor;		// �}�E�X�J�[�\���̐�Έʒu(�X�N���[��)�̎擾

//-------------------------- �Q�[���p�b�h (game pad)

LPDIRECTINPUTDEVICE8	pGamePad[GAMEPADMAX] = {NULL,NULL,NULL,NULL};// �p�b�h�f�o�C�X

DWORD		padState[GAMEPADMAX];		// �p�b�h���i�����Ή��j
DWORD		padTrigger[GAMEPADMAX];
Vector3		padGyro[GAMEPADMAX];
D3DXVECTOR2	padLsRoll[GAMEPADMAX];		// ���X�e�B�b�N�̓|���
D3DXVECTOR2	padRsRoll[GAMEPADMAX];		// �E�X�e�B�b�N�̓|���
bool		padNowUseSide = true;		// ���ݎg�p���Ă���(true = �� : false = �E)
int			padCount = 0;				// ���o�����p�b�h�̐�

//=============================================================================
// ���͏����̏�����
//=============================================================================
HRESULT InitInput(HINSTANCE hInst, HWND hWnd)
{
	HRESULT hr;

	if(!g_pDInput)
	{
		// DirectInput�I�u�W�F�N�g�̍쐬
		hr = DirectInput8Create(hInst, DIRECTINPUT_VERSION,
									IID_IDirectInput8, (void**)&g_pDInput, NULL);
	}

	// �L�[�{�[�h�̏�����
	InitKeyboard(hInst, hWnd);

 	// �}�E�X�̏�����
	InitializeMouse(hInst, hWnd);
	
	// �p�b�h�̏�����
	InitializePad();

	return S_OK;
}

//=============================================================================
// ���͏����̏I������
//=============================================================================
void UninitInput(void)
{
	// �L�[�{�[�h�̏I������
	UninitKeyboard();

	// �}�E�X�̏I������
	UninitMouse();

	// �p�b�h�̏I������
	UninitPad();

	if(g_pDInput)
	{
		g_pDInput->Release();
		g_pDInput = NULL;
	}
}

//=============================================================================
// ���͏����̍X�V����
//=============================================================================
void UpdateInput(void)
{
	// �L�[�{�[�h�̍X�V
	UpdateKeyboard();
	
	// �}�E�X�̍X�V
	UpdateMouse();
	
	// �p�b�h�̍X�V
	UpdatePad();

}

//=============================================================================
// �L�[�{�[�h�̏�����
//=============================================================================
HRESULT InitKeyboard(HINSTANCE hInst, HWND hWnd)
{
	HRESULT hr;

	// �f�o�C�X�I�u�W�F�N�g���쐬
	hr = g_pDInput->CreateDevice(GUID_SysKeyboard, &g_pDIDevKeyboard, NULL);
	if(FAILED(hr) || g_pDIDevKeyboard == NULL)
	{
		MessageBox(hWnd, "�L�[�{�[�h���˂��I", "�x���I", MB_ICONWARNING);
		return hr;
	}

	// �f�[�^�t�H�[�}�b�g��ݒ�
	hr = g_pDIDevKeyboard->SetDataFormat(&c_dfDIKeyboard);
	if(FAILED(hr))
	{
		MessageBox(hWnd, "�L�[�{�[�h�̃f�[�^�t�H�[�}�b�g��ݒ�ł��܂���ł����B", "�x���I", MB_ICONWARNING);
		return hr;
	}

	// �������[�h��ݒ�i�t�H�A�O���E���h����r�����[�h�j
	hr = g_pDIDevKeyboard->SetCooperativeLevel(hWnd, (DISCL_FOREGROUND | DISCL_NONEXCLUSIVE));
	if(FAILED(hr))
	{
		MessageBox(hWnd, "�L�[�{�[�h�̋������[�h��ݒ�ł��܂���ł����B", "�x���I", MB_ICONWARNING);
		return hr;
	}

	// �L�[�{�[�h�ւ̃A�N�Z�X�����l��(���͐���J�n)
	g_pDIDevKeyboard->Acquire();

	return S_OK;
}

//=============================================================================
// �L�[�{�[�h�̏I������
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
// �L�[�{�[�h�̍X�V
//=============================================================================
HRESULT UpdateKeyboard(void)
{
	HRESULT hr;
	BYTE keyStateOld[256];

	// �O��̃f�[�^��ۑ�
	memcpy(keyStateOld, g_keyState, NUM_KEY_MAX);

	// �f�o�C�X����f�[�^���擾
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
		// �L�[�{�[�h�ւ̃A�N�Z�X�����擾
		g_pDIDevKeyboard->Acquire();
	}

	return S_OK;
}

//=============================================================================
// �L�[�{�[�h�̃v���X��Ԃ��擾
//=============================================================================
bool GetKeyboardPress(int key)
{
	return (g_keyState[key] & 0x80) ? true : false;
}

//=============================================================================
// �L�[�{�[�h�̃g���K�[��Ԃ��擾
//=============================================================================
bool GetKeyboardTrigger(int key)
{
	return (g_keyStateTrigger[key] & 0x80) ? true : false;
}

//=============================================================================
// �L�[�{�[�h�̃��s�[�g��Ԃ��擾
//=============================================================================
bool GetKeyboardRepeat(int key)
{
	return (g_keyStateRepeat[key] & 0x80) ? true : false;
}

//=============================================================================
// �L�[�{�[�h�̃����|�X��Ԃ��擾
//=============================================================================
bool GetKeyboardRelease(int key)
{
	return (g_keyStateRelease[key] & 0x80) ? true : false;
}


//=============================================================================
// �}�E�X�֌W�̏���
//=============================================================================
// �}�E�X�̏�����
HRESULT InitializeMouse(HINSTANCE hInst,HWND hWindow)
{
	HRESULT result;
	// �f�o�C�X�쐬
	result = g_pDInput->CreateDevice(GUID_SysMouse,&pMouse,NULL);
	if(FAILED(result) || pMouse==NULL)
	{
		MessageBox(hWindow,"No mouse","Warning",MB_OK | MB_ICONWARNING);
		return result;
	}
	// �f�[�^�t�H�[�}�b�g�ݒ�
	result = pMouse->SetDataFormat(&c_dfDIMouse2);
	if(FAILED(result))
	{
		MessageBox(hWindow,"Can't setup mouse","Warning",MB_OK | MB_ICONWARNING);
		return result;
	}
	// ���̃A�v���Ƌ������[�h�ɐݒ�
	result = pMouse->SetCooperativeLevel(hWindow, (DISCL_FOREGROUND | DISCL_NONEXCLUSIVE));
	if(FAILED(result))
	{
		MessageBox(hWindow,"Mouse mode error","Warning",MB_OK | MB_ICONWARNING);
		return result;
	}
	
	// �f�o�C�X�̐ݒ�
	DIPROPDWORD prop;
	
	prop.diph.dwSize = sizeof(prop);
	prop.diph.dwHeaderSize = sizeof(prop.diph);
	prop.diph.dwObj = 0;
	prop.diph.dwHow = DIPH_DEVICE;
	prop.dwData = DIPROPAXISMODE_REL;		// �}�E�X�̈ړ��l ���Βl

	result = pMouse->SetProperty(DIPROP_AXISMODE,&prop.diph);
	if(FAILED(result))
	{
		MessageBox(hWindow,"Mouse property error","Warning",MB_OK | MB_ICONWARNING);
		return result;	
	}
	
	// �A�N�Z�X���𓾂�
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

	// �O��̒l�ۑ�
	DIMOUSESTATE2 lastMouseState = mouseState;
	// �f�[�^�擾
	result = pMouse->GetDeviceState(sizeof(mouseState), &mouseState);
	if (SUCCEEDED(result))
	{
		mouseTrigger.lX = mouseState.lX;
		mouseTrigger.lY = mouseState.lY;
		mouseTrigger.lZ = mouseState.lZ;
		// �}�E�X�̃{�^�����
		for (int i = 0; i < 8; i++)
		{
			mouseTrigger.rgbButtons[i] = ((lastMouseState.rgbButtons[i] ^
				mouseState.rgbButtons[i]) & mouseState.rgbButtons[i]);
		}
	}
	else	// �擾���s
	{
		// �A�N�Z�X���𓾂Ă݂�
		result = pMouse->Acquire();
	}

	//�}�E�X�̌��݂̍��W���擾����
	GetCursorPos(&s_MouseCursor);

	return result;
}

//----------------------------------------------
// ���{�^���̏��
//----------------------------------------------
//----����----
BOOL IsMouseLeftPressed(void)
{
	return (BOOL)(mouseState.rgbButtons[0] & 0x80);	// �����ꂽ�Ƃ��ɗ��r�b�g������
}
//----�g���K�[----
BOOL IsMouseLeftTriggered(void)
{
	return (BOOL)(mouseTrigger.rgbButtons[0] & 0x80);
}
//----------------------------------------------
// �E�{�^���̏��
//----------------------------------------------
//----����----
BOOL IsMouseRightPressed(void)
{
	return (BOOL)(mouseState.rgbButtons[1] & 0x80);
}
//----�g���K�[----
BOOL IsMouseRightTriggered(void)
{
	return (BOOL)(mouseTrigger.rgbButtons[1] & 0x80);
}
//----------------------------------------------
// ���{�^���̏��
//----------------------------------------------
//----����----
BOOL IsMouseCenterPressed(void)
{
	return (BOOL)(mouseState.rgbButtons[2] & 0x80);
}
//----�g���K�[----
BOOL IsMouseCenterTriggered(void)
{
	return (BOOL)(mouseTrigger.rgbButtons[2] & 0x80);
}
//----------------------------------------------
// �}�E�X�̃_�C���N�g���
//----------------------------------------------
//------------------ (�ړ���)
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
//------------------ (���W)
POINT GetMousePoint(void)
{
	return s_MouseCursor;
}


//=============================================================================
// �Q�[���p�b�h�֌W�̏���
//=============================================================================
//---------------------------------------- �R�[���o�b�N�֐�
BOOL CALLBACK SearchGamePadCallback(LPDIDEVICEINSTANCE lpddi, LPVOID )
{
	HRESULT result;

	result = g_pDInput->CreateDevice(lpddi->guidInstance, &pGamePad[padCount++], NULL);
	return DIENUM_CONTINUE;	// ���̃f�o�C�X���

}
//---------------------------------------- ������
HRESULT InitializePad(void)			// �p�b�h������
{
	HRESULT		result;
	int			i;

	padCount = 0;
	// �W���C�p�b�h��T��
	g_pDInput->EnumDevices(DI8DEVCLASS_GAMECTRL,
		(LPDIENUMDEVICESCALLBACK)SearchGamePadCallback,
		NULL,
		DIEDFL_ATTACHEDONLY);
	// �Z�b�g�����R�[���o�b�N�֐����A�p�b�h�𔭌������������Ă΂��B

	for (i = 0; i < padCount; i++) {
		// �W���C�X�e�B�b�N�p�̃f�[�^�E�t�H�[�}�b�g��ݒ�
		result = pGamePad[i]->SetDataFormat(&c_dfDIJoystick);
		if (FAILED(result))
			return false; // �f�[�^�t�H�[�}�b�g�̐ݒ�Ɏ��s

		// ���[�h��ݒ�i�t�H�A�O���E���h����r�����[�h�j
//		result = pGamePad[i]->SetCooperativeLevel(hWindow, DISCL_NONEXCLUSIVE | DISCL_FOREGROUND);
//		if ( FAILED(result) )
//			return false; // ���[�h�̐ݒ�Ɏ��s

		// ���̒l�͈̔͂�ݒ�
		// X���AY���̂��ꂼ��ɂ��āA�I�u�W�F�N�g���񍐉\�Ȓl�͈̔͂��Z�b�g����B
		// (max-min)�́A�ő�10,000(?)�B(max-min)/2�������l�ɂȂ�B
		// ����傫������΁A�A�i���O�l�ׂ̍��ȓ�����߂炦����B(�p�b�h�̐��\�ɂ��)
		DIPROPRANGE				diprg;
		ZeroMemory(&diprg, sizeof(diprg));
		diprg.diph.dwSize = sizeof(diprg);
		diprg.diph.dwHeaderSize = sizeof(diprg.diph);
		diprg.diph.dwHow = DIPH_BYOFFSET;
		diprg.lMin = -RANGE_MAX; //* /=RANGE_MIN
		diprg.lMax = RANGE_MAX;
		// X���͈̔͂�ݒ�
		diprg.diph.dwObj = DIJOFS_X;
		pGamePad[i]->SetProperty(DIPROP_RANGE, &diprg.diph);
		// Y���͈̔͂�ݒ�
		diprg.diph.dwObj = DIJOFS_Y;
		pGamePad[i]->SetProperty(DIPROP_RANGE, &diprg.diph);
		// Z���͈̔͂�ݒ�
		diprg.diph.dwObj = DIJOFS_Z;
		pGamePad[i]->SetProperty(DIPROP_RANGE, &diprg.diph);
		// X��]�͈̔͂�ݒ�
		diprg.diph.dwObj = DIJOFS_RX;
		pGamePad[i]->SetProperty(DIPROP_RANGE, &diprg.diph);
		// Y��]�͈̔͂�ݒ�
		diprg.diph.dwObj = DIJOFS_RY;
		pGamePad[i]->SetProperty(DIPROP_RANGE, &diprg.diph);
		// Z��]�͈̔͂�ݒ�
		diprg.diph.dwObj = DIJOFS_RZ;
		pGamePad[i]->SetProperty(DIPROP_RANGE, &diprg.diph);
		// Slider�͈̔͂�ݒ�
		diprg.diph.dwObj = DIJOFS_SLIDER(0);
		pGamePad[i]->SetProperty(DIPROP_RANGE, &diprg.diph);
		diprg.diph.dwObj = DIJOFS_SLIDER(1);
		pGamePad[i]->SetProperty(DIPROP_RANGE, &diprg.diph);


		// �e�����ƂɁA�����̃]�[���l��ݒ肷��B
		// �����]�[���Ƃ́A��������̔����ȃW���C�X�e�B�b�N�̓����𖳎�����͈͂̂��ƁB
		// �w�肷��l�́A10000�ɑ΂��鑊�Βl(2000�Ȃ�20�p�[�Z���g)�B
		DIPROPDWORD				dipdw;
		dipdw.diph.dwSize = sizeof(DIPROPDWORD);
		dipdw.diph.dwHeaderSize = sizeof(dipdw.diph);
		dipdw.diph.dwHow = DIPH_BYOFFSET;
		dipdw.dwData = DEADZONE;
		//X���̖����]�[����ݒ�
		dipdw.diph.dwObj = DIJOFS_X;
		pGamePad[i]->SetProperty(DIPROP_DEADZONE, &dipdw.diph);
		//Y���̖����]�[����ݒ�
		dipdw.diph.dwObj = DIJOFS_Y;
		pGamePad[i]->SetProperty(DIPROP_DEADZONE, &dipdw.diph);
		//Z���̖����]�[����ݒ�
		dipdw.diph.dwObj = DIJOFS_Z;
		pGamePad[i]->SetProperty(DIPROP_DEADZONE, &dipdw.diph);
		//X��]�̖����]�[����ݒ�
		dipdw.diph.dwObj = DIJOFS_RX;
		pGamePad[i]->SetProperty(DIPROP_DEADZONE, &dipdw.diph);
		//Y��]�̖����]�[����ݒ�
		dipdw.diph.dwObj = DIJOFS_RY;
		pGamePad[i]->SetProperty(DIPROP_DEADZONE, &dipdw.diph);

		//�W���C�X�e�B�b�N���͐���J�n
		pGamePad[i]->Acquire();
	}

	padNowUseSide = true;

	return true;

}
//------------------------------------------- �I������
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

//------------------------------------------ �X�V
void UpdatePad(void)
{
	HRESULT			result;
	DIJOYSTATE2		dijs;
	int				i;

	for (i = 0; i < padCount; i++)
	{
		DWORD lastPadState;
		lastPadState = padState[i];
		padState[i] = 0x00000000l;	// ������

		result = pGamePad[i]->Poll();	// �W���C�X�e�B�b�N�Ƀ|�[����������
		if (FAILED(result)) {
			result = pGamePad[i]->Acquire();
			while (result == DIERR_INPUTLOST)
				result = pGamePad[i]->Acquire();
		}

		result = pGamePad[i]->GetDeviceState(sizeof(DIJOYSTATE), &dijs);	// �f�o�C�X��Ԃ�ǂݎ��
		if (result == DIERR_INPUTLOST || result == DIERR_NOTACQUIRED) {
			result = pGamePad[i]->Acquire();
			while (result == DIERR_INPUTLOST)
				result = pGamePad[i]->Acquire();
		}

		// �R�Q�̊e�r�b�g�ɈӖ����������A�{�^�������ɉ����ăr�b�g���I���ɂ���
		//* y-axis (Lforward)
		if (dijs.lY < 0)				padState[i] |= LSTICK_UP;
		//* y-axis (Lbackward)
		if (dijs.lY > 0)				padState[i] |= LSTICK_DOWN;
		//* x-axis (Lleft)
		if (dijs.lX < 0)				padState[i] |= LSTICK_LEFT;
		//* x-axis (Lright)
		if (dijs.lX > 0)				padState[i] |= LSTICK_RIGHT;

		//* �{�^��00
		if (dijs.rgbButtons[0] & 0x80)		padState[i] |= BUTTON_00;
		//* �{�^��01
		if (dijs.rgbButtons[1] & 0x80)		padState[i] |= BUTTON_01;
		//* �{�^��02
		if (dijs.rgbButtons[2] & 0x80)		padState[i] |= BUTTON_02;
		//* �{�^��03
		if (dijs.rgbButtons[3] & 0x80)		padState[i] |= BUTTON_03;
		//* �{�^��04
		if (dijs.rgbButtons[4] & 0x80)		padState[i] |= BUTTON_04;
		//* �{�^��05
		if (dijs.rgbButtons[5] & 0x80)		padState[i] |= BUTTON_05;
		//* �{�^��06
		if (dijs.rgbButtons[6] & 0x80)		padState[i] |= BUTTON_06;
		//* �{�^��07
		if (dijs.rgbButtons[7] & 0x80)		padState[i] |= BUTTON_07;
		//* �{�^��08
		if (dijs.rgbButtons[8] & 0x80)		padState[i] |= BUTTON_08;
		//* �{�^��09
		if (dijs.rgbButtons[9] & 0x80)		padState[i] |= BUTTON_09;
		//* �{�^��10
		if (dijs.rgbButtons[10] & 0x80)		padState[i] |= BUTTON_10;
		//* �{�^��11
		if (dijs.rgbButtons[11] & 0x80)		padState[i] |= BUTTON_11;
		//* �{�^��12
		if (dijs.rgbButtons[12] & 0x80)		padState[i] |= BUTTON_12;
		//* �{�^��13
		if (dijs.rgbButtons[13] & 0x80)		padState[i] |= BUTTON_13;
		//* �{�^��14
		if (dijs.rgbButtons[14] & 0x80)		padState[i] |= BUTTON_14;
		//* �{�^��15
		if (dijs.rgbButtons[15] & 0x80)		padState[i] |= BUTTON_15;

		if (dijs.rgbButtons[13] & 0x80)
		{
			padNowUseSide = true;
		}
		else if (dijs.rgbButtons[12] & 0x80)
		{
			padNowUseSide = false;
		}

		// ���E�̃W���C�R���ɑΉ�������
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

		// Trigger�ݒ�
		padTrigger[i] = ((lastPadState ^ padState[i])	// �O��ƈ���Ă���
			& padState[i]);					// ��������ON�̂��

		/* �W���C���f�[�^�̕ۑ� */
		padGyro[i] = Vector3((float)dijs.rglSlider[0], (float)dijs.rglSlider[1], (float)dijs.lRz);

		// Roll�ݒ�
//		padLsRoll[i] = D3DXVECTOR2(dijs.lX / (float)(RANGE_MAX), -(dijs.lY / (float)(RANGE_MAX)));
//		padRsRoll[i] = D3DXVECTOR2(dijs.lRx / (float)(RANGE_MAX), dijs.lRy / (float)(RANGE_MAX));
	}
	//PrintDebugProcess("l   : (%ld)(%ld)(%ld)\n", dijs.lX, dijs.lY, dijs.lZ);
	//PrintDebugProcess("lR  : (%ld)(%ld)(%ld)\n", dijs.lRx, dijs.lRy, dijs.lRz);
	//PrintDebugProcess("rS  : (%ld)(%ld)\n", dijs.rglSlider[0], dijs.rglSlider[1]);
	//PrintDebugProcess("�\���L�[ : (%ld)", dijs.rgdwPOV[0]);
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
//----------------------------------------------- ����
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
	{// -�����Ă���͓̂��͒l�Ɖ�ʕ��������킹�邽��
		return Vector3(padGyro[0].x, padGyro[0].y, -padGyro[0].z);
	}
	return Vector3(-padGyro[1].x, padGyro[1].y, -padGyro[1].z);
}

