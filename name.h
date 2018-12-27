//***************************************************************************************:
// name.h
// 製作者 ぴのっきもん
//******************************************************************************************:
#ifndef _NAME_H_
#define _NAME_H_

#include "Library/Input.h"
#include "Library/ObjectBase2D.h"

// でふぁいん
#define NAMEMAX	(5)

// 構造体
typedef enum
{	// 現在の状態
	BEGIN = 0,		// 初期状態
	RANKIN,
	NAME_SELECT,
	NAME_SELECT_MAX

}NAME_SELECT_STATUS;

typedef struct
{
	C2DObject name[5];
	C2DObject rank;
	UI2DNumber score[5];
}RANKING;


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

/*
スコアが表示されている
ランキングした場合文字が光る
ボタンクリック？でキーボード＆文字入力画面がでる
文字入力を終了すると入力文字が光ってる部分に出る


変更
nameenter削除


*/