//***************************************************************************************:
// name.h
// 製作者 ぴのっきもん
//******************************************************************************************:
#ifndef _NAME_H_
#define _NAME_H_

#include "Library/Input.h"


// でふぁいん
#define NAMEMAX	(5)

/*****************************************************************************
どさいどん
*******************************************************************************/

//class Rankdata
typedef struct
{
	char name[256];	// ユーザー名
	int score;		// スコア
	long long namechar[NAMEMAX];
	long long  cursole_X;
	long long  cursole_Y;
}RANKDATA;


void Update_Name(void);
HRESULT InitName(void);
void UninitName(void);
void DrawName(void);


#endif

