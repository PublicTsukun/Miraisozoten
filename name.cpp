//*****************************************************::
// name.cpp
// ����� ���邿�イ
//*******************************************************

//�R�{�S�����C���N���[�h
#include "name.h"
#include <stdio.h>
#include "saveranking.h"
#include "score.h"
// ���C�u����
#include "Library/ObjectBase2D.h"
#include "Library/Common.h"
#include "Library/Input.h"
#include "Library/DebugProcess.h"


//*********************************************************
// Define
//*********************************************************

// ������
#define MOJI_Y_MAX		(5)		// 5�s�H
#define MOJI_X_MAX		(10)	// 10��H

#define ALPHA_Y_MAX		(2)
#define ALPHA_X_MAX		(13)

// ���̐���
#define SPACE_ENTRY		(710)	// �X�y�[�X���͗p
#define EMPTY_NO		(99)	// �����͂�(�����l)

// ����
// 48+26
#define CHARS_MAX		(74)

// �Ƃ��ׂȂ�����
#define NO_ENTRY		(100)		// ���������͂���Ă��Ȃ�
#define BACK_CHAR		(101)		// �߂�{�^���������ꂽ

// �`�B�p
#define KEY_IRETEKUDASAI	(777)


//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// �����Ղ̕\���ʒu�����ɃJ�[�\���ʒu�����߂Ă��܂��B
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// �����΂�
#define MOJIBAN_TEX		("data/�e�X�g�p�摜/�����{�[�h.jpg")
#define MOJIBAN_WIDTH	(400.0)
#define MOJIBAN_HEIGHT	(200.0)
#define MOJIBAN_POS_X	(SCREEN_CENTER_X)						// CENTER_X�w��Ŏ����I�ɐ^�񒆂ɕ\�����Ă����(Draw?)
#define MOJIBAN_POS_Y	(SCREEN_CENTER_Y + MOJIBAN_HEIGHT/2)
// �����Ղ̍ő�}�X��
#define MOJIBAN_MASUMAX_X	(9)
#define MOJIBAN_MASUMAX_Y	(4)


// �����΂�Q(�I�����ꂽ�������o���Ƃ��Ɏg����j
#define SENTAKUMOJI_TEX		("data/�e�X�g�p�摜/�����{�[�h.jpg")
#define SENTAKUMOJI_WIDTH	(70.0)
#define SENTAKUMOJI_HEIGHT	(70.0)
#define SENTAKUMOJI_POS_X	(SCREEN_CENTER_X-(SENTAKUMOJI_WIDTH*4))//(SCREEN_CENTER_X)						// CENTER_X�w��Ŏ����I�ɐ^�񒆂ɕ\�����Ă����(Draw?)
#define SENTAKUMOJI_POS_Y	(170.0f) //(SCREEN_CENTER_Y)

// �����C���p�̃J�[�\��(���͍ςݕ����ɏd�˂ĕ\�����Ă܂�)
#define RENAME_CURSOLE_TEX	("data/�e�X�g�p�摜/�e�X�g�p�摜3.png")
#define RENAME_CURSOLE_WIDTH	(70.0)
#define RENAME_CURSOLE_HEIGHT	(70.0)
#define RENAME_CURSOLE_POS_X	(SCREEN_CENTER_X-(SENTAKUMOJI_WIDTH*4))//(SCREEN_CENTER_X)						// CENTER_X�w��Ŏ����I�ɐ^�񒆂ɕ\�����Ă����(Draw?)
#define RENAME_CURSOLE_POS_Y	(170.0f) //(SCREEN_CENTER_Y)

// �ő�܂ŕ��������͂���Ă��Ȃ��Ƃ��̃T�[�N��



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// �ȉ��̒l�͘M��Ȃ������c

//***************************************************
// �J�[�\���֘A
//***************************************************
#define CURSOLE_TEX		("data/�e�X�g�p�摜/�e�X�g�p�摜.png")
#define CURSOLE_SPACE	(2)					// ���̃}�X�Ɉړ����邽�߂ɃJ�[�\����X,Y�ɂ�����l
#define CURSOLE_WIDTH	(MOJIBAN_WIDTH/10)			// �����Ղ�10�����~10�����Ȃ̂�
#define CURSOLE_HEIGHT	(MOJIBAN_HEIGHT/5)
// �u���v�������ʒu��
#define CURSOLE_POS_X	(SCREEN_CENTER_X-CURSOLE_WIDTH - (CURSOLE_WIDTH*CURSOLE_SPACE*4))
#define CURSOLE_POS_Y	((MOJIBAN_POS_Y) - (CURSOLE_HEIGHT*4))// - (CURSOLE_WIDTH*CURSOLE_SPACE))

// �����Ղł͂Ȃ��I�𕶎������������΂���
#define CHOISE_CURSOLE_TEX ("data/�e�X�g�p�摜/�ق�.png")	// �����g��Ȃ��H
#define CHOISE_CURSOLE_SPACE	(2)					// ���̃}�X�Ɉړ����邽�߂ɃJ�[�\����X,Y�ɂ�����l
#define CHOISE_CURSOLE_WIDTH	(MOJIBAN_WIDTH/10)			// �����Ղ�10�����~10�����Ȃ̂�
#define CHOISE_CURSOLE_HEIGHT	(MOJIBAN_HEIGHT/5)

#define CHOISE_CURSOLE_POS_X	(SCREEN_CENTER_X-CURSOLE_WIDTH - (CURSOLE_WIDTH*CURSOLE_SPACE*4))
#define CHOISE_CURSOLE_POS_Y	((MOJIBAN_POS_Y) - (CURSOLE_HEIGHT*4))// - (CURSOLE_WIDTH*CURSOLE_SPACE))






//*****************************************************************************
// ����[�΂�ւ񂷂�
//*****************************************************************************
int namechar;
int lastchar;		// ���[������Ă������łȂ񂾂����I

RANKDATA	rankdatawk[1];

C2DObject cursole;
C2DObject char_cursole;		// ���O�̕����������J�[�\��
C2DObject mojiban;			// �Ђ炪�ȗp������
C2DObject alphabet;
C2DObject moji[CHAR_MAX];
C2DObject select_moji[CHAR_MAX];		// �΂΁[��Ƃ����悤�̂��

bool char_type;
#define HIRAGANA (0)
#define ABC (1)

bool name_flag;	// �����Ղɂ��邩���O�ɂ��邩(true��������)

bool moving;	// �ړ����؂̃t���O

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// �J�[�\���ύX�֘A
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//#define CHANGE
#define CHANGE_TIME	(2)
int		cursole_update(CHANGE_TIME * 60);
int		timedayo;
bool cursolechanging;	// �J�[�\���ύX���؂̃t���E
bool pos_rockon;	// �ڕW���W����ς݂�
//float taeget_x, target_y;
float movesize_X, movesize_Y;
float target_x, target_y;	// �J�[�\���ړ��p�@�ڕW�ʒu�ƌ��݈ʒu�̍��W


//*************************************************************************
// �v���g�^�C�v�錾(cpp���ł̂ݎg�p������
//*************************************************************************
void move_cursole(void);
void move_cursole_alpha(void);
void name_char_select(void);
void cursole_change(void);
//*************************************************************************
// HRESULT Initname(void)
// �������͂̏�����
//*************************************************************************
HRESULT InitName(void)
{
	RANKDATA *rankdata = &rankdatawk[0];
	// ���O������
	for (int i = 0; i < NAMEMAX; i++)
	{
		rankdata[0].namechar[i] = EMPTY_NO;	// �S�Ă������l��
	}

	timedayo = 0;
	// �t���O������
	for (int i = 0; i < NAMEMAX; i++)
	{
		rankdata[0].selected[i] = false;
	}
	name_flag = true;
	char_type = HIRAGANA;
	pos_rockon = false;
	cursolechanging = false;

	// �J�[�\���������ʒu��
	rankdata[0].cursole_X = 0;
	rankdata[0].cursole_Y = 0;
	namechar = 0;							// ���͍ϕ���
	// �摜�̏�����
	cursole.Init(CURSOLE_POS_X,CURSOLE_POS_Y,CURSOLE_WIDTH,CURSOLE_HEIGHT,CURSOLE_TEX);
	mojiban.Init(MOJIBAN_POS_X, MOJIBAN_POS_Y, MOJIBAN_WIDTH, MOJIBAN_HEIGHT, MOJIBAN_TEX);
	char_cursole.Init(RENAME_CURSOLE_POS_X, RENAME_CURSOLE_POS_Y, RENAME_CURSOLE_WIDTH, RENAME_CURSOLE_HEIGHT, RENAME_CURSOLE_TEX);


	return S_OK;
}

//**********************************************************
// �I������
//**********************************************************
void UninitName(void)
{
	// �e�摜���
	char_cursole.Release();
	cursole.Release();
	mojiban.Release();
	alphabet.Release();
	for (int i = 0; i < CHAR_MAX;i++)
	{
		moji[i].Release();
		select_moji[i].Release();
	}
	//
	/*
	*/
}

	
//*************************************************************
// �`�揈��
//**************************************************************
void DrawName(void)
{
	RANKDATA *rankdata = &rankdatawk[0];


	if (char_type == HIRAGANA)
	{
		mojiban.SetTexture(0, 1, 2);
		mojiban.Draw();
	}
	else
	{
		mojiban.SetTexture(1, 1, 2);
		mojiban.Draw();
	}


	//char_cursole.Init(CURSOLE_POS_X + ((CURSOLE_WIDTH*CURSOLE_SPACE)*rankdata[0].cursole_X), CURSOLE_POS_Y + ((CURSOLE_HEIGHT*CURSOLE_SPACE)*rankdata[0].cursole_Y), CURSOLE_WIDTH, CURSOLE_HEIGHT, CURSOLE_TEX);
	//char_cursole.Draw();


	//select_moji[0].SetTexture(1, 10, 10);
	//select_moji[0].Draw();

	// �i�[���������o��
	for (int i = 0; i < NAMEMAX; i++)
	{
		// selected��true�Ȃ�e�N�X�`���\��
		if (rankdata[0].selected[i] == true)
		{
			// �e�N�X�`���̃Z�b�g
			//select_moji[namechar].Init(SENTAKUMOJI_POS_X + ((SENTAKUMOJI_WIDTH)*namechar), SENTAKUMOJI_POS_Y, SENTAKUMOJI_WIDTH, SENTAKUMOJI_HEIGHT, SENTAKUMOJI_TEX);
			select_moji[i].SetTexture(rankdata[0].namechar[i], 10, 10);	//������ �܂��߂̐�X ��3 �܂��߂̐�Y
			select_moji[i].Draw();
		}
	}

	// �J�[�\���`��
	// �΂����Ă邩��
	//cursolechanging = false;
	if (cursolechanging == false)
	{
		// name_flagn�ŕς��
		if (name_flag == true)
		{	// ������
			cursole.Init(CURSOLE_POS_X + ((CURSOLE_WIDTH*CURSOLE_SPACE)*rankdata[0].cursole_X), CURSOLE_POS_Y + ((CURSOLE_HEIGHT*CURSOLE_SPACE)*rankdata[0].cursole_Y), CURSOLE_WIDTH, CURSOLE_HEIGHT, CURSOLE_TEX);
		}
		else
		{	// �J�[�\���̃T�C�Y�ƈʒu��ς��邾���ł悭�ˁH
			cursole.Init(SENTAKUMOJI_POS_X + ((RENAME_CURSOLE_WIDTH * 2)*rankdata[0].name_position), RENAME_CURSOLE_POS_Y, RENAME_CURSOLE_WIDTH, RENAME_CURSOLE_HEIGHT, RENAME_CURSOLE_TEX);

		}
	}
	else
	{
		cursole_change();
	}
	cursole.Draw();

}


//*******************************************************:::

//**************************************************************************:
// void Update_name(void)
// �X�V�����@���O�����̃A�b�v�f�[�g
// �W�����C�����l�ɑ���Ȃ����̂��ĉ���������
//***************************************************************************

/*
�������̗͂���
�\���L�[�ŃJ�[�\���̈ړ�
A�őI��B�Ŗ߂�
���炩�̃L�[�Ŗ��O�̊m��
���O��5�����Ƃ���
*/

void Update_Name(void)
{
	RANKDATA *rankdata = &rankdatawk[0];

	// �J�[�\���ړ�
	if(name_flag == true)
	{
		move_cursole();
	}
	else
	{	// �����Ոړ�����
		name_char_select();
	}


	// �������͂̏I��
	if (GetKeyboardTrigger(DIK_Z))
	{
		int player_score = GetScore();
		// �����܂��͂��炩�Ȃ�������
		long long name_number = (rankdata[0].namechar[0] * 100000000) + (rankdata[0].namechar[1] * 1000000) + (rankdata[0].namechar[2] * 10000) + (rankdata[0].namechar[3] * 100) + rankdata[0].namechar[4];
		SaveRanking(player_score,name_number);
	}

	// ���͍ς݂̕������J�[�\���ňړ�
	if (GetKeyboardTrigger(DIK_LEFT))
	{
		if (namechar != 0)
		{
			namechar--;
		}
		rankdata[0].namechar[namechar] = EMPTY_NO;
		rankdata[0].selected[namechar] = false;
	}

	// �����Ղ�ς����
	if (GetKeyboardTrigger(DIK_X))
	{
		char_type = !char_type;
		// �J�[�\���ʒu�̏�����
		rankdata[0].cursole_X = 0;
		rankdata[0].cursole_Y = 0;
	}

	// �J�[�\���̈ʒu��ς���(�����Ձ̖��O��)
	// �Ă�����𕶎����͂܂œ������Ȃ��悤�ɂ���΂悭�ˁH
	if (namechar != 0)
	{
		if (GetKeyboardTrigger(DIK_C))
		{
			if (cursolechanging == false)
			{
				name_flag = !name_flag;
				// rankdata[0].cursole_Y * 10

				if (name_flag == true)
				{
					// name_flag��true�ɂȂ����ꍇ�A�����Ղ��\�������̂ŃJ�[�\�����ς��
					rankdata[0].cursole_X = rankdata[0].namechar[rankdata[0].name_position] % 10;
					rankdata[0].cursole_Y = (rankdata[0].namechar[rankdata[0].name_position] / 10) % 10;
					// �����͂̏ꍇ
					if (rankdata[0].namechar[rankdata[0].name_position] == EMPTY_NO)
					{
						rankdata[0].cursole_X = 0;
						rankdata[0].cursole_Y = 0;
					}
					// ���������͂��ꂽ�����������ՂƈႤ�ꍇ(�u���v�Ȃ̂ɕ����Ղ��A���t�@�x�b�g��������)�����Ղ�Ή����镨�ɕς��Ă�����
					long long agumon_X = rankdata[0].namechar[rankdata[0].name_position] % 10;			// X���W
					long long agumon_Y = (rankdata[0].namechar[rankdata[0].name_position] / 10) % 10;	// Y���W

					if (char_type == HIRAGANA && agumon_Y > MOJIBAN_MASUMAX_Y)
					{
						char_type = !char_type;			// �����ՕύX
					}
					else if (char_type == ABC && agumon_Y <= MOJIBAN_MASUMAX_Y)
					{
						char_type = !char_type;
					}

				}
				cursolechanging = true;
			}
		}
	}
	// 00�����@01����
	//select_moji[0].SetTexture(1,10,10);
}


//********************************************************************
// void move_cursole(void)
// �������͏���(�����Ղ��ړ����ĂȂ߂��i�[
//********************************************************************
void move_cursole(void)
{
	RANKDATA *rankdata = &rankdatawk[0];
	if (GetKeyboardTrigger(DIK_W))
	{
		rankdata[0].cursole_Y--;
		if (rankdata[0].cursole_Y < 0)
		{
			rankdata[0].cursole_Y = MOJIBAN_MASUMAX_Y;
		}
	}
	else if (GetKeyboardTrigger(DIK_S))
	{	// �����L�[�������ꂽ
		rankdata[0].cursole_Y++;
		// �`�F�b�N
		if (rankdata[0].cursole_Y > MOJIBAN_MASUMAX_Y)
		{
			rankdata[0].cursole_Y = 0;
		}
	}
	else if (GetKeyboardTrigger(DIK_D))
	{
		// �E�L�[
		rankdata[0].cursole_X++;
		// �`�F�b�N
		if (rankdata[0].cursole_X >MOJIBAN_MASUMAX_X)
		{
			rankdata[0].cursole_X = 0;
		}
	}
	else if (GetKeyboardTrigger(DIK_A))
	{
		// ���L�[
		rankdata[0].cursole_X--;
		// �`�F�b�N
		if (rankdata[0].cursole_X < 0)
		{
			rankdata[0].cursole_X = MOJIBAN_MASUMAX_X;
		}
	}

	// �����̍폜(�s�v�ȏꍇ�폜���肢���܂�(����))
	if (GetKeyboardTrigger(DIK_BACKSPACE))
	{	// ���O���̓t���O�̍폜
		select_moji[namechar-1].Release();
		rankdata[0].selected[namechar-1] = false;
		namechar--;
		rankdata[0].name_position = namechar;

	}
	// ����L�[�����͂��ꂽ�ꍇ���̃J�[�\���ʒu�̕������i�[
	if (GetKeyboardTrigger(DIK_SPACE) && namechar<NAMEMAX)
	{
		// 1�t���O��true��
		rankdata[0].selected[namechar] = true;

		// �����ŕ������i�[
		if (char_type == HIRAGANA)
		{
			rankdata[0].namechar[namechar] = rankdata[0].cursole_X + (rankdata[0].cursole_Y * 10);
		}
		else
		{
			rankdata[0].namechar[namechar] = rankdata[0].cursole_X + ((rankdata[0].cursole_Y+5) * 10);
		}
		// �e�N�X�`���̃Z�b�g
		select_moji[namechar].Init(SENTAKUMOJI_POS_X + ((SENTAKUMOJI_WIDTH * 2)*namechar), SENTAKUMOJI_POS_Y, SENTAKUMOJI_WIDTH, SENTAKUMOJI_HEIGHT, SENTAKUMOJI_TEX);
		//select_moji[namechar].SetTexture(1, 10, 10);	//������ �܂��߂̐�X ��3 �܂��߂̐�Y
		// �󔒕����̏ꍇ�̏���(�󔒕������͂ł��邩�킩��Ȃ��̂ŕۗ�)

		// �������͂��ꂽ�̂Ō��ݓ��͒��̖��O�����Z
		if (namechar < NAMEMAX)
		{
			rankdata[0].name_position = namechar;
			namechar++;
		}
	}
	// �㏑������(�����ɏ����K�v�͂���̂��낤���c)
	//if()
}

//********************************************************************
// void name_char_select
// ���O�ҏW�����I�I�I�I
// ���͍ς݂̖��O���J�[�\���ړ�����ꍇ�@�X�J���O���C������������������
//********************************************************************
void name_char_select(void)
{
	RANKDATA *rankdata = &rankdatawk[0];

	if (GetKeyboardTrigger(DIK_A))
	{
		rankdata[0].name_position--;
		if (rankdata[0].name_position < 0)
		{
			rankdata[0].name_position = namechar;
		}
	}
	else if (GetKeyboardTrigger(DIK_D))
	{
		rankdata[0].name_position++;
		if (rankdata[0].name_position >= namechar)
		{
			rankdata[0].name_position = 0;
		}
	}
}

//********************************************************************
// void move_cursole_alpha(void)
// �����Ղ̃T�C�Y�Ȃǂ��ς���Ă������̊֐�
// �g�p���Ȃ��ꍇ�폜
//********************************************************************
void move_cursole_alpha(void)
{
	RANKDATA *rankdata = &rankdatawk[0];
	if (GetKeyboardTrigger(DIK_W))
	{
		rankdata[0].cursole_Y--;
		if (rankdata[0].cursole_Y < 0)
		{
			rankdata[0].cursole_Y = MOJIBAN_MASUMAX_Y;
		}
	}
	else if (GetKeyboardTrigger(DIK_S))
	{	// �����L�[�������ꂽ
		rankdata[0].cursole_Y++;
		// �`�F�b�N
		if (rankdata[0].cursole_Y > MOJIBAN_MASUMAX_Y)
		{
			rankdata[0].cursole_Y = 0;
		}
	}
	else if (GetKeyboardTrigger(DIK_D))
	{
		// �E�L�[
		rankdata[0].cursole_X++;
		// �`�F�b�N
		if (rankdata[0].cursole_X >MOJIBAN_MASUMAX_X)
		{
			rankdata[0].cursole_X = 0;
		}
	}
	else if (GetKeyboardTrigger(DIK_A))
	{
		// ���L�[
		rankdata[0].cursole_X--;
		// �`�F�b�N
		if (rankdata[0].cursole_X < 0)
		{
			rankdata[0].cursole_X = MOJIBAN_MASUMAX_X;
		}
	}
	// ����L�[�����͂��ꂽ�ꍇ���̃J�[�\���ʒu�̕������i�[
	if (GetKeyboardTrigger(DIK_SPACE) && namechar<NAMEMAX)
	{
		// 1�t���O��true��
		rankdata[0].selected[namechar] = true;
		// �����ŕ������i�[
		rankdata[0].namechar[namechar] = rankdata[0].cursole_X + (rankdata[0].cursole_Y+5 * 10);

		// �e�N�X�`���̃Z�b�g
		select_moji[namechar].Init(SENTAKUMOJI_POS_X + ((SENTAKUMOJI_WIDTH * 2)*namechar), SENTAKUMOJI_POS_Y, SENTAKUMOJI_WIDTH, SENTAKUMOJI_HEIGHT, SENTAKUMOJI_TEX);
		//select_moji[namechar].SetTexture(1, 10, 10);	//������ �܂��߂̐�X ��3 �܂��߂̐�Y
		// �󔒕����̏ꍇ�̏���(�󔒕������͂ł��邩�킩��Ȃ��̂ŕۗ�)
		if (namechar < NAMEMAX)
		{
			namechar++;
		}
	}
}


//********************************************************************
// cursole_change
// �����Ձ`���O�Ԃōs���������
// ��΃o�O�邩��֐��ɂ��܂���
// ���܂����������ɂ��̂܂܂Ԃ�������
//********************************************************************
void cursole_change(void)
{
	RANKDATA *rankdata = &rankdatawk[0];
	// �ڕW�n�_�����܂��ĂȂ��ꍇ�A�����̌v�Z
	if (pos_rockon == false)
	{
		
		{ // �����ʒu�̂܂܂̏ꍇ�ȉ��̏����͍s��Ȃ�
		// ���O���I���ʒu�̕������擾
			long long agumon_X = rankdata[0].namechar[rankdata[0].name_position] % 10;			// X���W
			long long agumon_Y = (rankdata[0].namechar[rankdata[0].name_position] / 10) % 10;	// Y���W

			// ���̕��򂢂�H
			if (name_flag == true)
			{	// ���O���當���Ղ�
				// �A���t�@�x�b�g�̏ꍇ�ʒu�������K�v
				if (agumon_Y > MOJIBAN_MASUMAX_Y)
				{
					agumon_Y -= 5;	// �}�X�ڂ̍��������Ђ��Ă�
					rankdata[0].cursole_Y -= 5;
				}
				// �����Ղ��p��̏ꍇ
				if (char_type == ABC)
				{
				}
				target_x = (CURSOLE_POS_X + ((CURSOLE_WIDTH*CURSOLE_SPACE)*rankdata[0].cursole_X)) - (SENTAKUMOJI_POS_X + ((RENAME_CURSOLE_WIDTH * 2)*rankdata[0].name_position));
				target_y = (CURSOLE_POS_Y + ((CURSOLE_HEIGHT*CURSOLE_SPACE)*agumon_Y)) - RENAME_CURSOLE_POS_Y;
			}
			else
			{	// �����Ղ��疼�O����
				// �����Ղ̎�ނɂ���Ĉʒu�������K�v�Ȃ̂ňʒu��ۑ�
				// ���݂̃J�[�\���ʒu�Ɩ��O���̈ʒu�̋������o���΂���
				target_x = (SENTAKUMOJI_POS_X + ((RENAME_CURSOLE_WIDTH * 2)*rankdata[0].name_position) - (CURSOLE_POS_X + ((CURSOLE_WIDTH*CURSOLE_SPACE)*rankdata[0].cursole_X)));
				target_y = RENAME_CURSOLE_POS_Y - (CURSOLE_POS_Y + ((CURSOLE_HEIGHT*CURSOLE_SPACE)*rankdata[0].cursole_Y));
				//	����T�C�Y�Ȃ񂾂��ǂ��c����H
			}
			target_x = target_x / cursole_update;
			target_y = target_y / cursole_update;
			movesize_X = (RENAME_CURSOLE_WIDTH - CURSOLE_WIDTH) / cursole_update;
			movesize_Y = (RENAME_CURSOLE_HEIGHT - CURSOLE_HEIGHT) / cursole_update;
			pos_rockon = true;
		}
	}
	if (name_flag == true)
	{	// ���O�̂���當���Ղ�
		cursole.Init(SENTAKUMOJI_POS_X + ((RENAME_CURSOLE_WIDTH * 2)*rankdata[0].name_position) + (target_x*timedayo), RENAME_CURSOLE_POS_Y + (target_y*timedayo), RENAME_CURSOLE_WIDTH-(movesize_X*timedayo), RENAME_CURSOLE_HEIGHT-(movesize_Y*timedayo), RENAME_CURSOLE_TEX);
	}
	else
	{	// �����Ղ��疼�O����
		cursole.Init(CURSOLE_POS_X + ((CURSOLE_WIDTH*CURSOLE_SPACE)*rankdata[0].cursole_X) + (target_x*timedayo), CURSOLE_POS_Y + ((CURSOLE_HEIGHT*CURSOLE_SPACE)*rankdata[0].cursole_Y) + (target_y*timedayo), CURSOLE_WIDTH+(movesize_X*timedayo), CURSOLE_HEIGHT+(movesize_Y*timedayo), CURSOLE_TEX);
	}

	timedayo++;
	if (timedayo >= cursole_update)
	{
		//name_flag = !name_flag;
		timedayo = 0;
		cursolechanging = false;
		pos_rockon = false;
	}
}

