//=============================================================================
//
//�����S�����@workHagiwara.h
//�͂����Ȃ�
//=============================================================================
#ifndef _WORKHAGIWARA_H_
#define _WORKHAGIWARA_H_
#include "windows.h"
#include "d3dx9.h"
#include <tchar.h>
#include <stdio.h>

// ���_�t�H�[�}�b�g( ���_���W[2D] / ���ˌ� / �e�N�X�`�����W )
#define	FVF_VERTEX_2D	(D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1)
#define	NUM_VERTEX		(4)	// ���_��
#define NUM_POLYGON		(2)

//=============================================================================
//�\���̒�`
//=============================================================================

// ��L���_�t�H�[�}�b�g�ɍ��킹���\���̂��`
typedef struct
{
	D3DXVECTOR3 vtx;		// ���_���W
	float rhw;				// �e�N�X�`���̃p�[�X�y�N�e�B�u�R���N�g�p
	D3DCOLOR diffuse;		// ���ˌ�
	D3DXVECTOR2 tex;		// �e�N�X�`�����W
} SC_VERTEX_2D;

//=============================================================================
//�v���g�^�C�v�錾
//=============================================================================
HRESULT InitWorkHagiwara(void);
void UninitWorkHagiwara(void);
void UpdateWorkHagiwara(void);
void DrawWorkHagiwara(void);

#endif