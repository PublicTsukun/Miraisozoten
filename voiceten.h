//=============================================================================
//
// voiceten���� [voiceten.h]
// Author : �v�F��
//
//=============================================================================
#ifndef _VOICETEN_INCLUDE_H_
#define _VOICETEN_INCLUDE_H_

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
	bool use;	// �g�p���Ă��邩�ǂ���
	float vel;	// ���x

} VOICETEN;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void InitVoiceten(void);
void UninitVoiceten(void);
void UpdateVoiceten(void);
void DrawVoiceten(void);

VOICETEN *GetVoiceten(int no);

void SetVoiceten(D3DXVECTOR3 Self, D3DXVECTOR3 Tgt);
void VanishVoiceten(int no);

#endif