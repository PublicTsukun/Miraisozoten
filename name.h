//***************************************************************************************:
// name.h
// 製作者 ぴのっきもん
//******************************************************************************************:
#ifndef _NAME_H_
#define _NAME_H_

#define NAMEMAX	(5)
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


void enter_name(void);
int get_char(void);
void Initname(void);




// 仮の処理
#endif