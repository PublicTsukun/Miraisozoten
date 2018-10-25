//=============================================================================
//
// voiceten���� [voiceten.h]
// Author : �v�F��
//
//=============================================================================
#ifndef _VOICETEN_INCLUDE_H_
#define _VOICETEN_INCLUDE_H_

#include "Library/Vector.h"
#include <Windows.h>
#include <d3dx9.h>

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define VOICETEN_MAX (128)	// voiceten�ő吔

//*****************************************************************************
// �\���̒�`
//*****************************************************************************
typedef struct
{	
	bool use;		// �g�p���Ă��邩�ǂ���
	Vector3 pos;	// �ʒu
	Vector3 rot;	// ��]

	int timer;		// �^�C�}�[

	Vector3 start;	// ���ˈʒu
	Vector3 tgt;	// �ڕW�ʒu
	double dist;	// ���B���v����

	int dura;		// ���B���v����

	Vector3 nor;	// ���B���v�����̐��K��
	double vel;		// ���x

	float hei;		// ���E���x



} VOICETEN;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void InitVoiceten(void);
void UninitVoiceten(void);
void UpdateVoiceten(void);
void DrawVoiceten(void);

VOICETEN *GetVoiceten(int no);

void SetVoiceten(Vector3 Self, Vector3 Tgt);
void VanishVoiceten(int no);

#endif