//=============================================================================
//
// �p�����[�^�Ǘ� [S-Editor.h]
// Author : �v�F��
//
//=============================================================================
#ifndef _SEDITOR_INCLUDE_H_
#define _SEDITOR_INCLUDE_H_

#include "Library/Vector.h"
#include <d3dx9.h>
#include <Windows.h>
#include "timer.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************

// ���ˏ��v����
#define VOICETEN_SHOT_VOL		(ENERGY_MIN)	

// Voiceten Type ���ʐݒ�
#define VOICETEN_TYPE_VOL_01	(ENERGY_CORD * 3)

// Voiceten Type ���ʐݒ�
#define VOICETEN_TYPE_VOL_02	(ENERGY_CORD * 6)

// �Ԋu�œG�𐶐��iframe�j
#define ENEMY_SPAWN_DELAY_01	(60)

// �Ԋu�œG�𐶐��iframe�j
#define ENEMY_SPAWN_DELAY_02	(120)

// �Ԋu�œG���Đ����iframe�j
#define ENEMY_DEFEAT_DELAY		(120)

// �Ԋu�œG���Đ����i�t�B�[�o�[��ԁj�iframe�j
#define ENEMY_DEFEAT_FEVER		(ENEMY_DEFEAT_DELAY / 2)

// �X�e�[�W�ő厞�ԁiframe�j
#define STAGE_TIME				(START_TIME * 60)

// �X�e�[�W01�N���A�����i���j���j
#define STAGE_NORMA_01			(10)

// �X�e�[�W02�N���A�����i���j���j
#define STAGE_NORMA_02			(25)

// �����G�t�F�N�g�̑傫��
#define EFX_SIZE_HIT			(96.0f)

// ���j�G�t�F�N�g�̑傫��
#define EFX_SIZE_DEFEAT			(96.0f)

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************

#endif