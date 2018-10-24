//=============================================================================
//
//�R�{�S�����@workYamamoto.h
//
//=============================================================================
#ifndef _WORKYAMAMOTO_H_
#define _WORKYAMAMOTO_H_

#define NAMEMAX	(5)
/*****************************************************************************
�ǂ����ǂ�
*******************************************************************************/

//class Rankdata
typedef struct
{
	char name[256];	// ���[�U�[��
	int score;		// �X�R�A
	int namechar[NAMEMAX];
	int cursole_X;
	int cursole_Y;
}RANKDATA;


//=============================================================================
//�v���g�^�C�v�錾
//=============================================================================
HRESULT InitWorkYamamoto(void);
void UninitWorkYamamoto(void);
void UpdateWorkYamamoto(void);
void DrawWorkYamamoto(void);
void Initname(void);

void pinokkimon(void);
int jyureimon(void);

// �L�[�{�[�h(�^��)
HRESULT InitInput(HINSTANCE hInst, HWND hWnd);
void UninitInput(void);
void UpdateInput(void);

bool GetKeyboardPress(int nKey);
bool GetKeyboardTrigger(int nKey);
bool GetKeyboardRepeat(int nKey);
bool GetKeyboardRelease(int nKey);

#endif


//**********************************************
// �A��
//*********************************************
/*
�t�@�C���`���@csv
�f�[�^�L�q�@name score
1�s���Ƃ�݂���
*/