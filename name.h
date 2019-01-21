//***************************************************************************************:
// name.h
// ����� �҂̂�������
//******************************************************************************************:
#ifndef _NAME_H_
#define _NAME_H_

#include "Library/Input.h"
#include "Library/ObjectBase2D.h"

// �łӂ�����
#define NAMEMAX	(5)

// �\����
typedef enum
{	// ���݂̏��
	BEGIN = 0,		// �������
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
�ǂ����ǂ�
*******************************************************************************/

//class Rankdata
typedef struct
{
	long long x;
	long long y;
	Vector2 pos;
}CURSOLE;

typedef struct
{
	int name[5][2];	// ���[�U�[��
	int score;		// �X�R�A
	int namechar[NAMEMAX][2];
	// �����Ց��쎞�̃J�[�\��
	bool selected[NAMEMAX];
}RANKDATA;

void Update_Name(void);
HRESULT InitName(void);
void UninitName(void);
void DrawName(void);


#endif

/*
�X�R�A���\������Ă���
�����L���O�����ꍇ����������
�{�^���N���b�N�H�ŃL�[�{�[�h���������͉�ʂ��ł�
�������͂��I������Ɠ��͕����������Ă镔���ɏo��


�ύX
nameenter�폜


*/