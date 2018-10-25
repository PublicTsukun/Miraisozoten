//=============================================================================
//
// message box���� [messageBox.h]
// Author : �v�F��
//
//=============================================================================
#ifndef _MESSAGEBOX_INCLUDE_H_
#define _MESSAGEBOX_INCLUDE_H_

#include "Library/Vector.h"
#include <Windows.h>
#include <d3dx9.h>

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define MESSAGEBOX_MAX (1)		// �ő吔
#define MESSAGEBOX_EFX_MAX (1)	// �ő吔

//*****************************************************************************
// �\���̒�`
//*****************************************************************************
typedef struct
{
	bool use;		// �g�p���Ă��邩�ǂ���

	Vector2 pos;	// �ʒu

	float len;		// ����
	float wid;		// ����

	bool efx;		

} MESSAGEBOX;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void InitMessageBox(void);
void UninitMessageBox(void);
void DrawMessagebox(void);
void UpdateMessageBox(void);

void SetMessageboxEfxOn(int no);
void SetMessageboxEfxOff(int no);

MESSAGEBOX *GetMessageBox(int no);
MESSAGEBOX *GetMessageBoxEfx(int no);


#endif