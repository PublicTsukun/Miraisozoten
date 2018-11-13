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
	char name[256];	// ���[�U�[��
	int score;		// �X�R�A
	long long namechar[NAMEMAX];
	long long  cursole_X;
	long long  cursole_Y;
}RANKDATA;


void Update_Name(void);
HRESULT InitName(void);
void UninitName(void);
void DrawName(void);


#endif

