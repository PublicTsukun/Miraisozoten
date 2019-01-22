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
#define RENAME_CURSOLE_TEX	("data/TEXTURE/UI//���U���g/���O���.png")
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
#define CURSOLE_TEX		("data/TEXTURE/UI//���U���g/�������̓J�[�\��.png")
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

#define FLASH_TIME		(0.05f)

// ����{�^��
//*****************************************************************************
// �\���̒�`
//*****************************************************************************
// �J�[�\���ʒu��enum
typedef enum
{
	KEYBOARD,
	PLAYER_NAME,
	NAME_FINISH
}CURSOLE_POSITION;



//*****************************************************************************
// ����[�΂�ւ񂷂�
//*****************************************************************************

int namechar;
int lastchar;		// ���[������Ă������łȂ񂾂����I
int name_status;	// ���݂̏��
RANKDATA	rankdatawk[1];
CURSOLE		cursolewk;
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

// �_�łɎg��
float flash_count;
bool flash_count_switch;

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
int flash_score;			// �_�ł���suko

//*************************************************************************
// �v���g�^�C�v�錾(cpp���ł̂ݎg�p������
//*************************************************************************
void move_cursole(void);
void Flash_Tex(int no);
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
	//name_enter = SaveRankingSort(99999);	// �X�R�A�������N�C���������H


	SAVERANKING *rankinfo = GetSaveRanking(0);
	for (int i = 0; i < 5; i++,rankinfo++)
	{// 236
		ranking[i].rank.Init(NAME_SCORE_SIZE + 40.0f, NAME_SCORE_POS_Y + ((NAME_SCORE_SIZE * 2)*i), NAME_SCORE_SIZE, NAME_SCORE_SIZE);
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


	//// ���O������
	//for (int i = 0; i < NAMEMAX; i++)
	//{
	//	rankdata[0].namechar[i] = EMPTY_NO;	// �S�Ă������l��
	//}

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
	flash_count_switch = false;

	// �X�e�[�^�X��������Ԃ�
	name_status = BEGIN;

	// �J�[�\���������ʒu��
	cursolewk.pos.x = 0;
	cursolewk.pos.y = 0;
	namechar = 0;							// ���͍ϕ���
											// �摜�̏�����
	cursole.Init(CURSOLE_POS_X, Y_TEST + CURSOLE_POS_Y, CURSOLE_WIDTH, CURSOLE_HEIGHT, CURSOLE_TEX);
	mojiban.Init(MOJIBAN_POS_X, Y_TEST + MOJIBAN_POS_Y, MOJIBAN_WIDTH, MOJIBAN_HEIGHT, MOJIBAN_TEX);
	char_cursole.Init(RENAME_CURSOLE_POS_X, Y_TEST + RENAME_CURSOLE_POS_Y, RENAME_CURSOLE_WIDTH, RENAME_CURSOLE_HEIGHT, RENAME_CURSOLE_TEX);
	haikei.Init(SCREEN_CENTER_X, SCREEN_CENTER_Y, HAIKEI_WIDTH, HAIKEI_HEIGHT, HAIKEI_TEX);
	name_set.Init(SCREEN_CENTER_X, Y_TEST + KETTEI_Y, 160.0, 80.0, "data/TEXTURE/UI/�����Ă�.png");	//X���W�~2�ɍX�ɕ�������������
	//haikei_logo.Init

	// �J�E���g�Z�b�g
	flash_count = 1.0f;

	flash_score = 0;

	for (int i = 0;i<5;i++)
	{
		select_moji[i].Init(SENTAKUMOJI_POS_X + ((SENTAKUMOJI_WIDTH * 2)*i), Y_TEST + SENTAKUMOJI_POS_Y, SENTAKUMOJI_WIDTH, SENTAKUMOJI_HEIGHT, SENTAKUMOJI_TEX);
	}
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
		ranking[i].rank.Release();
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
	{	


		// �������牺�֐��ɂ��Ă킯�邩���H
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
				int numnum;
				numnum = rankdata[0].namechar[i][0] * 10 + rankdata[0].namechar[i][1];
				select_moji[i].SetTexture(numnum, 10, 10);	//������ �܂��߂̐�X ��3 �܂��߂̐�Y
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
				cursole.SetStatus(CURSOLE_POS_X + ((CURSOLE_WIDTH*CURSOLE_SPACE)*cursolewk.pos.x), Y_TEST + CURSOLE_POS_Y + ((CURSOLE_HEIGHT*CURSOLE_SPACE)*cursolewk.pos.y), CURSOLE_WIDTH, CURSOLE_HEIGHT);
				break;
			}
			case PLAYER_NAME:
			{	// �J�[�\���̃T�C�Y�ƈʒu��ς��邾���ł悭�ˁH
				//cursole.SetStatus(SENTAKUMOJI_POS_X + ((RENAME_CURSOLE_WIDTH * 2)*rankdata[0].name_position), Y_TEST + RENAME_CURSOLE_POS_Y, RENAME_CURSOLE_WIDTH, RENAME_CURSOLE_HEIGHT);
				break;
			}
			case NAME_FINISH:
			{	// �J�[�\����\�����Ȃ�
				cursole.SetStatus(-100, -100, 0.0, 0.0);
				break;
			}
			}
		}
		else
		{
			//cursole_change();
		}
		cursole.SetVertex(D3DXCOLOR(1.0f, 1.0f, 1.0f, fabs(sinf(flash_count)) + 0.3f));
		cursole.Draw();
	}
	break;

	case NAME_SELECT_END:
	{

	}
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
	if (GetKeyboardTrigger(DIK_8))
	{
		name_enter = !name_enter;
	}

	// �t���O��true�Ȃ疼�O���͂n�j
	if (name_status != NAME_SELECT_END && name_enter == true && GetKeyboardTrigger(DIK_0) || IsButtonTriggered(BUTTON_UP))
	{
		name_status = NAME_SELECT;
	}
	else if (name_enter == false && GetKeyboardTrigger(DIK_0) || IsButtonTriggered(BUTTON_UP))
	{
		PlaySE(DECIDE);
		Scene::SetScene(SCENE_TITLE);
	}


	switch (name_status)
	{
	case NAME_SELECT:
	{
		if (cursole_status != NAME_FINISH)
		{	// ����{�^���ɃJ�[�\�������Ȃ�(�L�[�{�[�h)
			// �J�[�\���ړ�

				move_cursole();


			// �����Ղ�ς���(�J�[�\���ړ����͎��s�ł��Ȃ��j
			if (GetKeyboardTrigger(DIK_X) || IsButtonTriggered(LSTICK_RIGHT | LSTICK_LEFT) && cursolechanging == false)
			{
				char_type = !char_type;
				// �J�[�\���ʒu�̏�����
				cursolewk.pos.x = 0;
				cursolewk.pos.y = 0;
			}

			// �J�[�\���̈ʒu��ς���(�����Ձ̖��O��)
		}
		else
		{	// �ȉ��A����{�^���ɂ���ۂ̏���(name_status = NAME_FINISH)
			if (GetKeyboardTrigger(DIK_2) || IsButtonTriggered(BUTTON_DOWN))
			{	// �܂����肵�Ȃ���
				rankdata[0].selected[namechar - 1] = false;	// ���͕����̃t���O���I�t��
				rankdata[0].namechar[namechar-1][0] = 0;
				rankdata[0].namechar[namechar-1][1] = 0;// �������̓t���O������(���̈ʒu�ցj
				namechar--;									// ���ݓ��͒��̕����������炷��
				//rankdata[0].name_position = namechar - 1;
				cursole_status = KEYBOARD;
			}
			// ����{�^���ɃJ�[�\�������݂��Ă���L�L�[�������ꂽ�ꍇ
			if (GetKeyboardTrigger(DIK_L) || IsButtonTriggered(BUTTON_UP))
			{

				for (int i = 0; i < NAMEMAX; i++)
				{
					Enter_the_no(CheckRank(GetScore()),i, rankdata[0].namechar[i][0], rankdata[0].namechar[i][1]);
				}

				// �f�[�^�o��
				WriteSaveRankingCsv();
				// �ă��[�h
				//LoadSaveRankingCsv();
				// �����L���O��
				name_status = NAME_SELECT_END;
			}
		}

	}
	break;
	case NAME_SELECT_END:
	{
		if ((GetKeyboardTrigger(DIK_0) || IsButtonTriggered(BUTTON_UP)))// �X�̃{�^�����k����
		{
			PlaySE(DECIDE);
			Scene::SetScene(SCENE_TITLE);
		}
	}
//defalt:
	break;
	}

	Flash_Tex(0);
	// �_��
	
}


//********************************************************************
// void move_cursole(void)
// �������͏���(�����Ղ��ړ����ĂȂ߂��i�[
//********************************************************************
void move_cursole(void)
{
	RANKDATA *rankdata = &rankdatawk[0];
	if (GetKeyboardTrigger(DIK_W) || IsButtonTriggered(LSTICK_UP))
	{
		cursolewk.pos.y--;
		if (char_type == HIRAGANA && cursolewk.pos.y < 0)
		{
			cursolewk.pos.y = MOJIBAN_MASUMAX_Y;
		}
		else if(char_type!=HIRAGANA && cursolewk.pos.y <0)
		{
			cursolewk.pos.y = 2;	// �A���t�@�x�b�g�ő傽�Ă܂�
		}
	}
	else if (GetKeyboardTrigger(DIK_S) || IsButtonTriggered(LSTICK_DOWN))
	{	// �����L�[�������ꂽ
		cursolewk.pos.y++;
		// �`�F�b�N
		if (char_type == HIRAGANA && cursolewk.pos.y > MOJIBAN_MASUMAX_Y)
		{
			cursolewk.pos.y = 0;
		}
		else if (char_type != HIRAGANA && cursolewk.pos.y >2)
		{
			cursolewk.pos.y = 0;
		}
	}
	else if (GetKeyboardTrigger(DIK_D) || IsButtonTriggered(LSTICK_RIGHT))
	{
		// �E�L�[
		cursolewk.pos.x++;
		// �`�F�b�N
		if (cursolewk.pos.x >MOJIBAN_MASUMAX_X)
		{
			cursolewk.pos.x = 0;
		}
	}
	else if (GetKeyboardTrigger(DIK_A) || IsButtonTriggered(LSTICK_LEFT))
	{
		// ���L�[
		cursolewk.pos.x--;
		// �`�F�b�N
		if (cursolewk.pos.x < 0)
		{
			cursolewk.pos.x = MOJIBAN_MASUMAX_X;
		}
	}

	// �����̍폜(�s�v�ȏꍇ�폜���肢���܂�(����))
	if (GetKeyboardTrigger(DIK_BACKSPACE) || IsButtonTriggered(BUTTON_DOWN) )
	{	// ���O���̓t���O�̍폜
		//select_moji[namechar - 1].Release();	//�e�N�X�`�����
		rankdata[0].selected[namechar - 1] = false;	// ���͕����̃t���O���I�t��
		rankdata[0].namechar[namechar-1][0] = 0;		// �������̓t���O������(���̈ʒu�ցj
		rankdata[0].namechar[namechar-1][1] = 0;
		namechar--;									// ���ݓ��͒��̕����������炷��
		//rankdata[0].name_position = namechar - 1;

	}


	// ����L�[�����͂��ꂽ�ꍇ���̃J�[�\���ʒu�̕������i�[
	if (GetKeyboardTrigger(DIK_SPACE) || IsButtonTriggered(BUTTON_UP))
	{
		//if (namechar < NAMEMAX)
		{
			// ���ɑI������Ă���ꍇ�㏑������

			/*else*/ if (namechar < NAMEMAX)
			{
				// �w��ʒu
				// 1�t���O��true��
				rankdata[0].selected[namechar] = true;

				// �����ŕ������i�[
				if (char_type == HIRAGANA)
				{
					rankdata[0].namechar[namechar][0] = (int)cursolewk.pos.y;
					rankdata[0].namechar[namechar][1] = (int)cursolewk.pos.x;
				}
				else
				{
					rankdata[0].namechar[namechar][0] = (int)cursolewk.pos.y + 5;
					rankdata[0].namechar[namechar][1] = (int)cursolewk.pos.x;
				}
				//	����̌���ɂ����5�����ڂ����͂��ꂽ�ꍇ
				if (rankdata[0].selected[NAMEMAX - 1] == true)
				{
					cursole_status = NAME_FINISH;
				}
				
				//select_moji[namechar].SetTexture(1, 10, 10);	//������ �܂��߂̐�X ��3 �܂��߂̐�Y
				// �󔒕����̏ꍇ�̏���(�󔒕������͂ł��邩�킩��Ȃ��̂ŕۗ�)

				// �������͂��ꂽ�̂Ō��ݓ��͒��̖��O�����Z
			}
			if (namechar < NAMEMAX)
			{
				namechar++;
				//rankdata[0].name_position = namechar;

			}
		}




	}
	PrintDebugProcess("namechar %d", namechar);

}


//********************************************************************
// void Flash_Tex(int no)
// �e�N�X�`���̓_�ŁI
// �����@int �߂�l �Ȃ�
//********************************************************************
void Flash_Tex(int no)
{
	//if (flash_count_switch == false)
	//{	// ���Y
	//	flash_count -= (FLASH_TIME / 60.0f);
	//	if (flash_count < 0.0f)
	//	{
	//		flash_count = 0.0f;
	//		flash_count_switch = true;
	//	}
	//}
	//else
	//{
	//	flash_count += (FLASH_TIME / 60.0);
	//	if (flash_count > 1.0f)
	//	{
	//		flash_count = 1.0f;
	//		flash_count_switch = false;
	//	}
	//}
	flash_count += FLASH_TIME;
	if (name_enter == true && name_status == BEGIN || name_status == NAME_SELECT_END)
	{	// �v���C���[�̃X�R�A�ƃ����L���O�̃X�R�A���r����H
		int player_score = GetScore();
		SAVERANKING *rankinfo = GetSaveRanking(0);
		for (int i = 0; i < 5;i++, rankinfo++)
		{
			if (player_score == rankinfo->score)
			{
				flash_score = i;
			}
		}
		for (int t = 0; t < 5; t++)
		{
			ranking[flash_score].name[t].SetVertex(D3DXCOLOR(1.0f, 1.0f, 1.0f, fabs(sinf(flash_count)) + 0.3f));
			ranking[flash_score].score[t].SetVertex(D3DXCOLOR(1.0f, 1.0f, 1.0f, fabs(sinf(flash_count)) + 0.3f));
		}


	}
	else
	{	// �L�[�{�[�h�Ȃǂ��\������Ă���
		if (cursole_status == NAME_FINISH)
		{
			name_set.SetVertex(D3DXCOLOR(1.0f,1.0f,1.0f,fabs(sinf(flash_count)) +0.3f));
		}
		else
		{
 			cursole.SetVertex(D3DXCOLOR(1.0f, 1.0f, 1.0f,fabs(sinf(flash_count)) +0.3f));
		}
	}
}


// �t�@�C���ǂ݂���
// �Ƃ肠����
/*
���ʁ@�P�Q�R�S�T�U�V�W�X�P�O













*/