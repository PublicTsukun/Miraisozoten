//***************************************************************************************:
// name.h
// ����� �҂̂�������
//******************************************************************************************:
#ifndef _NAME_H_
#define _NAME_H_

#include "Library/Input.h"
// �łӂ�����
#define NAMEMAX	(5)
// �����΂�
#define MOJIBAN_TEX		("data/TEXTURE/mojiban.png")
#define MOJIBAN_POS_X	(0.0)
#define MOJIBAN_POS_Y	(0.0)
#define MOJIBAN_WIDTH	(50.0)
#define MOJIBAN_HEIGHT	(100.0)
// �J�[�\��
#define CURSOLE_TEX		("data/TEXTURE/�J�[�\��")
#define CURSOLE_POS_X	(0.0)
#define CURSOLE_POS_Y	(0.0)
#define CURSOLE_WIDTH	(10.0)
#define CURSOLE_HEIGHT	(10.0)

/*****************************************************************************
�ǂ����ǂ�
*******************************************************************************/

//class Rankdata
typedef struct
{
	char name[256];	// ���[�U�[��
	int score;		// �X�R�A
	int namechar[NAMEMAX];
	int cursole_X;
	int cursole_Y;
}RANKDATA;


void Update_Name(void);
int get_char(void);
void InitName(void);




// ���̏���
#endif