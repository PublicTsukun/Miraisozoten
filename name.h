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
	long long x;
	long long y;
}CURSOLE;

typedef struct
{
	char name[256];	// ユーザー名
	int score;		// スコア
	long long namechar[NAMEMAX];
	// 文字盤操作時のカーソル
	long long  cursole_X;
	long long  cursole_Y;
	int name_position;
	CURSOLE name_cursole;
	bool selected[NAMEMAX];
}RANKDATA;


void Update_Name(void);
HRESULT InitName(void);
void UninitName(void);
void DrawName(void);


#endif

