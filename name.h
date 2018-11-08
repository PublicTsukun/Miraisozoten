//***************************************************************************************:
// name.h
// 製作者 ぴのっきもん
//******************************************************************************************:
#ifndef _NAME_H_
#define _NAME_H_

#include "Library/Input.h"
// でふぁいん
#define NAMEMAX	(5)
// もじばんだ
#define MOJIBAN_TEX		("data/TEXTURE/mojiban.png")
#define MOJIBAN_POS_X	(0.0)
#define MOJIBAN_POS_Y	(0.0)
#define MOJIBAN_WIDTH	(50.0)
#define MOJIBAN_HEIGHT	(100.0)
// カーソル
#define CURSOLE_TEX		("data/TEXTURE/カーソル")
#define CURSOLE_POS_X	(0.0)
#define CURSOLE_POS_Y	(0.0)
#define CURSOLE_WIDTH	(10.0)
#define CURSOLE_HEIGHT	(10.0)

/*****************************************************************************
どさいどん
*******************************************************************************/

//class Rankdata
typedef struct
{
	char name[256];	// ユーザー名
	int score;		// スコア
	int namechar[NAMEMAX];
	int cursole_X;
	int cursole_Y;
}RANKDATA;


void Update_Name(void);
int get_char(void);
void InitName(void);




// 仮の処理
#endif