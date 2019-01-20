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


//*********************************************************
// ������
#define NEXT_CHAR		(91)	// ����L�[
#define Y_TEST			(-100)	// �����悤
//********************************************************

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


// �w�i�摜and���S
#define HAIKEI_TEX		("data/TEXTURE/UI/���U���g/�肴��Ɣw�i.png")
#define HAIKEI_WIDTH	(SCREEN_WIDTH/2)		//  ��
#define HAIKEI_HEIGHT	(SCREEN_HEIGHT/2)
#define HAIKEI_ROGO		("data/TEXTURE/UI/�肴���.png")
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// �����Ղ̕\���ʒu�����ɃJ�[�\���ʒu�����߂Ă��܂��B
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// �����΂�
#define MOJIBAN_TEX		("data/TEXTURE/UI/���U���g/�܏\���v���O�����\�L�p.png")
#define MOJIBAN_WIDTH	(400.0)
#define MOJIBAN_HEIGHT	(200.0)
#define MOJIBAN_POS_X	(SCREEN_CENTER_X)						// CENTER_X�w��Ŏ����I�ɐ^�񒆂ɕ\�����Ă����(Draw?)
#define MOJIBAN_POS_Y	(SCREEN_CENTER_Y + MOJIBAN_HEIGHT/2)
// �����Ղ̍ő�}�X��
#define MOJIBAN_MASUMAX_X	(9)
#define MOJIBAN_MASUMAX_Y	(4)


// �����΂�Q(�I�����ꂽ�������o���Ƃ��Ɏg����j
#define SENTAKUMOJI_TEX		("data/TEXTURE/UI/���U���g/�܏\���v���O�����\�L�p.png")
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




// �J�[�\���ړ��b��
#define CHANGE_TIME	(1)

//�@����B�Py���W
#define KETTEI_Y	(740)

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

// �����L���O�̖��O
#define NAME_TEX		("data/TEXTURE/UI/���U���g/�܏\���v���O�����\�L�p.png")
#define NAME_WIDTH	(70.0)
#define NAME_HEIGHT	(70.0)
#define NAME_POS_X	(SCREEN_CENTER_X-(SENTAKUMOJI_WIDTH*4))//(SCREEN_CENTER_X)						// CENTER_X�w��Ŏ����I�ɐ^�񒆂ɕ\�����Ă����(Draw?)
#define NAME_POS_Y	(170.0f) //(SCREEN_CENTER_Y)
#define RANKING_NO	(5)		// �����L���O��ʂɕ\������閼�O�̐�


// �Ԋu�����p
#define NAME_MAX_NO (5)
#define SCORE_MAX_NO (5)
#define NAME_POS_X (210.0)
#define NAME_POS_Y (70.0)
#define NAME_SCORE_POS_Y (150)		// ���O�ƃX�R�A�͓�������
#define NAME_SPACE_01	(50)
#define NAME_SCORE_SIZE (50)


// ����{�^��
//*****************************************************************************
// �\���̒�`
//*****************************************************************************
// �J�[�\���ʒu��enum
typedef enum
{
	KEYBOARD,
	PLAYER_NAME,
	FINISH
}CURSOLE_POSITION;



//*****************************************************************************
// ����[�΂�ւ񂷂�
//*****************************************************************************

int namechar;
int lastchar;		// ���[������Ă������łȂ񂾂����I
int name_status;	// ���݂̏��
RANKDATA	rankdatawk[1];

C2DObject cursole;
C2DObject char_cursole;		// ���O�̕����������J�[�\��
C2DObject mojiban;			// �Ђ炪�ȗp������
C2DObject alphabet;
C2DObject select_moji[CHAR_MAX];		// �΂΁[��Ƃ����悤�̂��
C2DObject haikei;
C2DObject haiki_logo;
C2DObject name_set;						// ����{�^��

RANKING ranking[5];
Dx9Texture ranktex[5];


bool char_type;
#define HIRAGANA (0)
#define ABC (1)

bool name_flag;	// �����Ղɂ��邩���O�ɂ��邩(true��������)
int cursole_status;	// �J�[�\���������Ă�ꏊ(name_flag�Ɠ�������)
bool moving;	// �ړ����؂̃t���O
bool name_enter;	// �����L���O�ɓ����Ă邩�̃t���O true�Ȃ疼�O���͏����𓮂���

					//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
					// �J�[�\���ύX�֘A
					//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
					//#define CHANGE

int		cursole_update(CHANGE_TIME * 60);
int		timedayo;
bool cursolechanging;	// �J�[�\���ύX���؂̃t���E
bool pos_rockon;	// �ڕW���W����ς݂�
					//float taeget_x, target_y;
float movesize_X, movesize_Y;
float target_x, target_y;	// �J�[�\���ړ��p�@�ڕW�ʒu�ƌ��݈ʒu�̍��W
bool finish_flag;			// �������͏I��邩�ǂ����̃t���O

							//*************************************************************************
							// �v���g�^�C�v�錾(cpp���ł̂ݎg�p������
							//*************************************************************************
void move_cursole(void);
void move_cursole_alpha(void);
void name_char_select(void);
void cursole_change(void);
void Draw_ranking(int hoge);
//*************************************************************************
// HRESULT Initname(void)
// �������͂̏�����
//*************************************************************************
HRESULT InitName(void)
{
	RANKDATA *rankdata = &rankdatawk[0];

	//
	ranktex[0].LoadTexture("data/TEXTURE/UI/���U���g/1st.png");
	ranktex[1].LoadTexture("data/TEXTURE/UI/���U���g/2nd.png");
	ranktex[2].LoadTexture("data/TEXTURE/UI/���U���g/3rd.png");
	ranktex[3].LoadTexture("data/TEXTURE/UI/���U���g/4th.png");
	ranktex[4].LoadTexture("data/TEXTURE/UI/���U���g/5th.png");

	// �ǂݍ���
	LoadSaveRankingCsv();

	// �X�R�A�擾
	int player_score = GetScore();
	name_enter = SaveRankingSort(player_score);	// �X�R�A�������N�C���������H


	SAVERANKING *rankinfo = GetSaveRanking(0);
	for (int i = 0; i < 5; i++,rankinfo++)
	{
		ranking[i].rank.Init(NAME_SCORE_SIZE + 40, NAME_SCORE_POS_Y + ((NAME_SCORE_SIZE * 2)*i), NAME_SCORE_SIZE, NAME_SCORE_SIZE);
		ranking[i].rank.LoadTexture(ranktex[rankinfo->rank-1]);
		for (int t = 0; t < 5; t++)
		{	// �X�R�A�`��
			ranking[i].score[t].Init(NAME_POS_X + ((NAME_SCORE_SIZE*2)*(NAME_MAX_NO+(t))), NAME_SCORE_POS_Y +((NAME_SCORE_SIZE*2)*i), NAME_SCORE_SIZE, NAME_SCORE_SIZE);
			ranking[i].score[t].LoadTexture("data/TEXTURE/UI/�X�R�A����.png");
			int num;
			num = (rankinfo->score / (int)(pow(10, 5-t-1)));
			num %= 10;
			ranking[i].score[t].SetNumber(num);
		}

		// ���O�`��
		for (int agmon = 0; agmon < NAME_MAX_NO; agmon++)
		{
			ranking[i].name[agmon].Init(NAME_POS_X+((NAME_SCORE_SIZE*2)*agmon), NAME_SCORE_POS_Y +((NAME_SCORE_SIZE*2)*i), NAME_SCORE_SIZE, NAME_SCORE_SIZE);
			ranking[i].name[agmon].LoadTexture(NAME_TEX);
			int gabmon = rankinfo->name[agmon][0]*10+rankinfo->name[agmon][1];
			ranking[i].name[agmon].SetTexture(gabmon, 10, 10);
		}
	}


	// ���O������
	for (int i = 0; i < NAMEMAX; i++)
	{
		rankdata[0].namechar[i] = EMPTY_NO;	// �S�Ă������l��
	}

	timedayo = 0;
	// �e�t���O������
	for (int i = 0; i < NAMEMAX; i++)
	{
		rankdata[0].selected[i] = false;
	}
	name_flag = true;
	cursole_status = KEYBOARD;	// �L�[�{�[�h��
	char_type = HIRAGANA;
	pos_rockon = false;
	cursolechanging = false;
	name_enter = false;

	// �X�e�[�^�X��������Ԃ�
	name_status = BEGIN;

	// �J�[�\���������ʒu��
	rankdata[0].cursole_X = 0;
	rankdata[0].cursole_Y = 0;
	namechar = 0;							// ���͍ϕ���
											// �摜�̏�����
	cursole.Init(CURSOLE_POS_X, Y_TEST + CURSOLE_POS_Y, CURSOLE_WIDTH, CURSOLE_HEIGHT, CURSOLE_TEX);
	mojiban.Init(MOJIBAN_POS_X, Y_TEST + MOJIBAN_POS_Y, MOJIBAN_WIDTH, MOJIBAN_HEIGHT, MOJIBAN_TEX);
	char_cursole.Init(RENAME_CURSOLE_POS_X, Y_TEST + RENAME_CURSOLE_POS_Y, RENAME_CURSOLE_WIDTH, RENAME_CURSOLE_HEIGHT, RENAME_CURSOLE_TEX);
	haikei.Init(SCREEN_CENTER_X, SCREEN_CENTER_Y, HAIKEI_WIDTH, HAIKEI_HEIGHT, HAIKEI_TEX);
	name_set.Init(SCREEN_CENTER_X, Y_TEST + KETTEI_Y, 160.0, 80.0, "data/TEXTURE/UI/�����Ă�.png");	//X���W�~2�ɍX�ɕ�������������
	//haikei_logo.Init


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
	name_set.Release();
	for (int i = 0; i < 5; i++)
	{
		for (int t = 0; t < 5; t++)
		{
			ranking[i].name[t].Release();
			ranking[i].score[t].Release();
		}
		ranktex[i].Release();
	}
	for (int i = 0; i < CHAR_MAX; i++)
	{
		select_moji[i].Release();
	}
	//
	/*
	*/
	haikei.Release();
}


//*************************************************************
// �`�揈��
//**************************************************************
void DrawName(void)
{
	RANKDATA *rankdata = &rankdatawk[0];


	haikei.Draw();			// �w�i�摜

	switch (name_status)
	{
		// ���O���͂ɓ����Ă���ꍇ�̕`��
	case NAME_SELECT:
	{	// �������牺�֐��ɂ��Ă킯�邩���H
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
		// �i�[���������o��
		for (int i = 0; i < NAME_MAX; i++)
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
		// ����{�^��(��x�ł��������ő�܂œ��͂��ꂽ�ꍇ�\��
		if (rankdata[0].selected[NAME_MAX - 1] == true)
		{
			name_set.Draw();
		}
		

		// �J�[�\���`��
		// �΂����Ă邩��
		//cursolechanging = false;
		if (cursolechanging == false)
		{
			// �J�[�\���̕\���ʒu��ύX����

			// name_flagn�ŕς��
			switch (cursole_status)
			{
			case KEYBOARD:
			{	// ������
				cursole.Init(CURSOLE_POS_X + ((CURSOLE_WIDTH*CURSOLE_SPACE)*rankdata[0].cursole_X), Y_TEST + CURSOLE_POS_Y + ((CURSOLE_HEIGHT*CURSOLE_SPACE)*rankdata[0].cursole_Y), CURSOLE_WIDTH, CURSOLE_HEIGHT, CURSOLE_TEX);
				break;
			}
			case PLAYER_NAME:
			{	// �J�[�\���̃T�C�Y�ƈʒu��ς��邾���ł悭�ˁH
				cursole.Init(SENTAKUMOJI_POS_X + ((RENAME_CURSOLE_WIDTH * 2)*rankdata[0].name_position), Y_TEST + RENAME_CURSOLE_POS_Y, RENAME_CURSOLE_WIDTH, RENAME_CURSOLE_HEIGHT, RENAME_CURSOLE_TEX);
				break;
			}
			case FINISH:
			{	// �J�[�\����\�����Ȃ�
				cursole.Init(-100, -100, 0.0, 0.0);
				break;
			}
			}
		}
		else
		{
			cursole_change();
		}
		cursole.Draw();
	}
	break;

	default:
		// �����L���O�`��p�̊֐��c
		for (int i = 0; i < 5; i++)
		{
			ranking[i].rank.Draw();
			for (int t = 0; t < 5; t++)
			{
				ranking[i].name[t].Draw();
				ranking[i].score[t].Draw();
			}
		}
		break;
	}
}


//***************************************************************************
// void Update_name(void)
// �X�V�����@���O�����̃A�b�v�f�[�g
// �W�����C�����l�ɑ���Ȃ����̂��ĉ���������
//***************************************************************************
void Update_Name(void)
{
	RANKDATA *rankdata = &rankdatawk[0];
	name_enter = true;
	// �t���O��true�Ȃ疼�O���͂n�j
	if (name_enter == true && GetKeyboardTrigger(DIK_0))
	{
		if (name_status == NAME_SELECT)
		{
			name_status = BEGIN;
		}
		else
		{
			name_status = NAME_SELECT;
		}
	}



	switch (name_status)
	{
	case NAME_SELECT:
	{
		if (cursole_status != FINISH)
		{	// ����{�^���ɃJ�[�\�������Ȃ�
			// �J�[�\���ړ�
			if (name_flag == true)
			{
				move_cursole();
			}
			else
			{	// �����Ոړ�����
				name_char_select();
			}


			// �������͂̏I��(�m��)
			if (GetKeyboardTrigger(DIK_Z))
			{
				int player_score = GetScore();
				// �����܂��͂��炩�Ȃ�������
				long long name_number = (rankdata[0].namechar[0] * 100000000) + (rankdata[0].namechar[1] * 1000000) + (rankdata[0].namechar[2] * 10000) + (rankdata[0].namechar[3] * 100) + rankdata[0].namechar[4];
				WriteSaveRankingCsv();
			}

			// �����Ղ�ς���(�J�[�\���ړ����͎��s�ł��Ȃ��j
			if (GetKeyboardTrigger(DIK_X) && cursolechanging == false)
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
		else
		{	// �ȉ��A����{�^���ɂ���ۂ̏���
			if (GetKeyboardTrigger(DIK_2))
			{
				cursole_status = KEYBOARD;
			}
			// ����{�^���ɃJ�[�\�������݂��Ă���L�L�[�������ꂽ�ꍇ
			if (GetKeyboardTrigger(DIK_L))
			{	// �f�[�^�o��
				WriteSaveRankingCsv();
				// �ă��[�h
				LoadSaveRankingCsv();
				// �����L���O��
				name_status = BEGIN;
			}
		}

	}
	break;
defalt:
	break;
	}

	// test �Z�[�u�����L���O�쐬
	if (GetKeyboardTrigger(DIK_LSHIFT))
	{
	//	WriteSaveRankingCsv();
	}
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
		select_moji[namechar - 1].Release();	//�e�N�X�`�����
		rankdata[0].selected[namechar - 1] = false;	// ���͕����̃t���O���I�t��
		rankdata[0].namechar[namechar] = 00;		// �������̓t���O������(���̈ʒu�ցj
		namechar--;									// ���ݓ��͒��̕����������炷��
		rankdata[0].name_position = namechar - 1;

	}


	// ����L�[�����͂��ꂽ�ꍇ���̃J�[�\���ʒu�̕������i�[
	if (GetKeyboardTrigger(DIK_SPACE))
	{
		//if (namechar < NAMEMAX)
		{
			// ���ɑI������Ă���ꍇ�㏑������
			//if (rankdata[0].selected[rankdata[0].name_position] == true)
			{ // �㏑������

			 // // �����ŕ������i�[
				//if (char_type == HIRAGANA)
				//{
				//	rankdata[0].namechar[rankdata[0].name_position] = rankdata[0].cursole_X + (rankdata[0].cursole_Y * 10);
				//}
				//else
				//{
				//	rankdata[0].namechar[rankdata[0].name_position] = rankdata[0].cursole_X + ((rankdata[0].cursole_Y + 5) * 10);
				//}
				//// �e�N�X�`���̃Z�b�g
				//select_moji[rankdata[0].name_position].Init(SENTAKUMOJI_POS_X + ((SENTAKUMOJI_WIDTH * 2)*rankdata[0].name_position), SENTAKUMOJI_POS_Y, SENTAKUMOJI_WIDTH, SENTAKUMOJI_HEIGHT, SENTAKUMOJI_TEX);
				////select_moji[namechar].SetTexture(1, 10, 10);	//������ �܂��߂̐�X ��3 �܂��߂̐�Y
				//// �󔒕����̏ꍇ�̏���(�󔒕������͂ł��邩�킩��Ȃ��̂ŕۗ�)

				//// �������͂��ꂽ�̂Ō��ݓ��͒��̖��O�����Z
				//if (namechar < NAMEMAX)
				//{
				//	//rankdata[0].name_position = namechar;
				//	//namechar++;
				//}
			}
			/*else*/ if (namechar < NAMEMAX)
			{
				// �w��ʒu
				// 1�t���O��true��
				rankdata[0].selected[namechar] = true;

				// �����ŕ������i�[
				if (char_type == HIRAGANA)
				{
					rankdata[0].namechar[namechar] = rankdata[0].cursole_X + (rankdata[0].cursole_Y * 10);
				}
				else
				{
					rankdata[0].namechar[namechar] = rankdata[0].cursole_X + ((rankdata[0].cursole_Y + 5) * 10);
				}
				// �e�N�X�`���̃Z�b�g
				select_moji[namechar].Init(SENTAKUMOJI_POS_X + ((SENTAKUMOJI_WIDTH * 2)*namechar), Y_TEST + SENTAKUMOJI_POS_Y, SENTAKUMOJI_WIDTH, SENTAKUMOJI_HEIGHT, SENTAKUMOJI_TEX);
				
				//	����̌���ɂ����5�����ڂ����͂��ꂽ�ꍇ
				if (rankdata[0].selected[NAMEMAX - 1] == true)
				{
					cursole_status = FINISH;
				}
				
				//select_moji[namechar].SetTexture(1, 10, 10);	//������ �܂��߂̐�X ��3 �܂��߂̐�Y
				// �󔒕����̏ꍇ�̏���(�󔒕������͂ł��邩�킩��Ȃ��̂ŕۗ�)

				// �������͂��ꂽ�̂Ō��ݓ��͒��̖��O�����Z
			}
			if (namechar < NAMEMAX)
			{
				namechar++;
				rankdata[0].name_position = namechar;

			}
		}




	}
					PrintDebugProcess("namechar %d", namechar);

}

//********************************************************************
// void name_char_select
// ���O�ҏW�����I�I�I�I
// ���͍ς݂̖��O���J�[�\���ړ�����ꍇ�@�X�J���O���C������������������
//********************************************************************
void name_char_select(void)
{
	RANKDATA *rankdata = &rankdatawk[0];

	if (namechar < NAMEMAX)
	{
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
			if (rankdata[0].name_position >= namechar + 1)
			{
				rankdata[0].name_position = 0;
			}
		}
	}
	else
	{
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
			if (rankdata[0].name_position >= namechar+1)
			{
				rankdata[0].name_position = 0;
			}
		}
	}

}

//********************************************************************
// void move_cursole_alpha(void)
// �����Ղ̃T�C�Y�Ȃǂ��ς���Ă������̊֐�
// �g��Ȃ����Ȃ̂ō폜�\��
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
		rankdata[0].namechar[namechar] = rankdata[0].cursole_X + (rankdata[0].cursole_Y + 5 * 10);

		// �e�N�X�`���̃Z�b�g
		select_moji[namechar].Init(SENTAKUMOJI_POS_X + ((SENTAKUMOJI_WIDTH * 2)*namechar), Y_TEST + SENTAKUMOJI_POS_Y, SENTAKUMOJI_WIDTH, SENTAKUMOJI_HEIGHT, SENTAKUMOJI_TEX);
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
// ���܂����������ɂ��̂܂܂Ԃ������E�Ǝv��������ǒ����Ȃ��������߂�
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
				cursole_status = KEYBOARD;
			}
			else
			{	// �����Ղ��疼�O����
				if (rankdata[0].name_position >= NAMEMAX)
				{
					rankdata[0].name_position = NAMEMAX - 1;
				}
				// �����Ղ̎�ނɂ���Ĉʒu�������K�v�Ȃ̂ňʒu��ۑ�
				// ���݂̃J�[�\���ʒu�Ɩ��O���̈ʒu�̋������o���΂���
				target_x = (SENTAKUMOJI_POS_X + ((RENAME_CURSOLE_WIDTH * 2)*rankdata[0].name_position) - (CURSOLE_POS_X + ((CURSOLE_WIDTH*CURSOLE_SPACE)*rankdata[0].cursole_X)));
				target_y = RENAME_CURSOLE_POS_Y - (CURSOLE_POS_Y + ((CURSOLE_HEIGHT*CURSOLE_SPACE)*rankdata[0].cursole_Y));
				//	����T�C�Y�Ȃ񂾂��ǂ��c����H
				// ���O���Ƀ|�W�V�����ړ�
				cursole_status = PLAYER_NAME;
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
		cursole.Init(SENTAKUMOJI_POS_X + ((RENAME_CURSOLE_WIDTH * 2)*rankdata[0].name_position) + (target_x*timedayo), Y_TEST + RENAME_CURSOLE_POS_Y + (target_y*timedayo), RENAME_CURSOLE_WIDTH - (movesize_X*timedayo), RENAME_CURSOLE_HEIGHT - (movesize_Y*timedayo), RENAME_CURSOLE_TEX);
	}
	else
	{	// �����Ղ��疼�O����
		cursole.Init(CURSOLE_POS_X + ((CURSOLE_WIDTH*CURSOLE_SPACE)*rankdata[0].cursole_X) + (target_x*timedayo), Y_TEST + CURSOLE_POS_Y + ((CURSOLE_HEIGHT*CURSOLE_SPACE)*rankdata[0].cursole_Y) + (target_y*timedayo), CURSOLE_WIDTH + (movesize_X*timedayo), CURSOLE_HEIGHT + (movesize_Y*timedayo), CURSOLE_TEX);
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

//********************************************************************
// Draw_ranking(int hoge)
// �����L���O�̕\�������ł��Aint�^hoge�ɂ���Ė��O�̓_�łȂǂ��s���܂��B
//********************************************************************
void Draw_ranking(int hoge)
{
	RANKDATA *rankdata = &rankdatawk[0];
	// C2Dobject Init�ŏ������@Draw�ŕ`��
	for (int i = 0; i < RANKING_NO; i++)
	{
		//ranking[i].Init((NAME_POS_X + ((NAME_WIDTH * 2)*rankdata[0].name_position), NAME_POS_Y, NAME_WIDTH, NAME_HEIGHT, NAME_TEX));
	}
}



// �t�@�C���ǂ݂���
// �Ƃ肠����
/*
���ʁ@�P�Q�R�S�T�U�V�W�X�P�O













*/