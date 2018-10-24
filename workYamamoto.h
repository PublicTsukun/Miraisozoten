//=============================================================================
//
//山本担当分　workYamamoto.h
//
//=============================================================================
#ifndef _WORKYAMAMOTO_H_
#define _WORKYAMAMOTO_H_

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


//=============================================================================
//プロトタイプ宣言
//=============================================================================
HRESULT InitWorkYamamoto(void);
void UninitWorkYamamoto(void);
void UpdateWorkYamamoto(void);
void DrawWorkYamamoto(void);
void Initname(void);

void pinokkimon(void);
int jyureimon(void);

// キーボード(真顔)
HRESULT InitInput(HINSTANCE hInst, HWND hWnd);
void UninitInput(void);
void UpdateInput(void);

bool GetKeyboardPress(int nKey);
bool GetKeyboardTrigger(int nKey);
bool GetKeyboardRepeat(int nKey);
bool GetKeyboardRelease(int nKey);

#endif


//**********************************************
// 連絡
//*********************************************
/*
ファイル形式　csv
データ記述　name score
1行ごとよみこみ
*/