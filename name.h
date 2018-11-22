//***************************************************************************************:
// name.h
// ����� �҂̂�������
//******************************************************************************************:
#ifndef _NAME_H_
#define _NAME_H_

#include "Library/Input.h"


// �łӂ�����
#define NAMEMAX	(5)

/*****************************************************************************
�ǂ����ǂ�
*******************************************************************************/

//class Rankdata
typedef struct
{
	long long x;
	long long y;
}CURSOLE;

typedef struct
{
	char name[256];	// ���[�U�[��
	int score;		// �X�R�A
	long long namechar[NAMEMAX];
	// �����Ց��쎞�̃J�[�\��
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

