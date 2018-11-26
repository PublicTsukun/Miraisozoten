//=============================================================================
//
// �t�B�[���h���� [field.cpp]
//
//=============================================================================
#ifndef _START_COUNT_
#define _START_COUNT_


#include <Windows.h>
#include "Library/Common.h"

#define STARTCOUNT_TEX		"data/TEXTURE/UI/�X�R�A����.png"

#define STARTLOGO_TEX		"data/TEXTURE/UI/�����[��.png"



HRESULT InitStartCount(void);
void UninitStartCount(void);
void DrawStartCount(void);
void UpdateStartCount(void);

void SetStartCount(int no);
bool CheckLogoUse(void);
bool CheckCountActive(void);


#endif

