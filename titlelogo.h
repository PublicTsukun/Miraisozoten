//=============================================================================
//
// �^�C�g������ [title.h]
//
//=============================================================================
#ifndef _TITLELOGO_H_
#define _TITLELOGO_H_

#include "Library/Math.h"
#include <Windows.h>

enum cursor { SINGLE,MULTI,RANKING,CURSORMAX };
//=============================================================================
//�v���g�^�C�v�錾
//=============================================================================
HRESULT InitTitlelogo(void);
void UninitTitlelogo(void);
void DrawTitlelogo(void);
void UpdateTitlelogo(void);
#endif
