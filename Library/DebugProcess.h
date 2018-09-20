//=============================================================================
//
// �f�o�b�O�\������ [DebugProcess.h]
//
//=============================================================================
#ifndef __DEBUGPROCESS_INCLUDE_H__
#define __DEBUGPROCESS_INCLUDE_H__


#define _CRT_SECURE_NO_WARNINGS		// warning�h�~


#include <Windows.h>

//*****************************************************************************
// �}�N����`
//*****************************************************************************


//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitDebugProcess(void);
void UninitDebugProcess(void);
void UpdateDebugProcess(void);
void DrawDebugProcess(void);

void PrintDebugProcess(const char *fmt,...);


#endif