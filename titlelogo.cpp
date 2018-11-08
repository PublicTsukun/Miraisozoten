//=============================================================================
//
// �^�C�g������ [title.cpp]
//
//=============================================================================
#include "titlelogo.h"
#include "Library/ObjectBase2D.h"
#include "Library/Common.h"
#include "Library/Input.h"
#include "Library/DebugProcess.h"
#include "SceneManager.h"
//=============================================================================
// �}�N����`
//=============================================================================
#define	TEXTURE_TITLE		"data/TEXTURE/sgf01a201501112200.jpg"// �ǂݍ��ރe�N�X�`���̃t�@�C����
#define	TEXTURE_LOGO_NAME	"data/TEXTURE/toumeititle.png"		// �ǂݍ��ރ^�C�g�����S�̃t�@�C����
#define START_BUTTON		"data/TEXTURE/start.jpg"			// �ǂݍ��ރX�^�[�g�{�^���̃t�@�C����
#define SINGLE_LOGO			"data/TEXTURE/soro.jpg"				// �ǂݍ��ނP�l�p���[�h���S�̃t�@�C����
#define MULTI_LOGO			"data/TEXTURE/mauti.jpg"			// �ǂݍ��ނQ�l�p���[�h���S�t�@�C����
#define RANKING_LOGO		"data/TEXTURE/ranking.jpg"			// �ǂݍ��ރ����L���O���S�̃t�@�C����
#define CURSOR_LOGO			"data/TEXTURE/toumeiyazirusi.png"	// �ǂݍ��ރJ�[�\�����S�̃t�@�C����

#define	TITLE_LOGO_NAMEPOS_X	(SCREEN_CENTER_X)		// �^�C�g�����S�̈ʒu(X���W)320
#define	TITLE_LOGO_NAMEPOS_Y	(RelativeSY(0.25f))		// �^�C�g�����S�̈ʒu(Y���W)40
#define TITLE_LOGO_NAMESX		(RelativeSX(0.75f)/2)	//�^�C�g�����S�̃T�C�Y(X���W)
#define TITLE_LOGO_NAMESY		(RelativeSY(0.3f)/2)	//�^�C�g�����S�̃T�C�Y(Y���W)
//#define	TITLE_LOGO_WIDTH		(1000)		// �^�C�g�����S�̕�640
//#define	TITLE_LOGO_HEIGHT		(300)		// �^�C�g�����S�̍���640

#define	START_POS_X				(400*SCREEN_SCALE)		// �X�^�[�g�{�^���̈ʒu(X���W)
#define	START_POS_Y				(400*SCREEN_SCALE)		// �X�^�[�g�{�^���̈ʒu(Y���W)
#define	START_WIDTH				(480*SCREEN_SCALE)		// �X�^�[�g�{�^���̕�
#define	START_HEIGHT			(120*SCREEN_SCALE)		// �X�^�[�g�{�^���̍���

#define	SINGLE_POS_X			(400*SCREEN_SCALE)		// �P�l�p���[�h���S�̈ʒu(X���W)
#define	SINGLE_POS_Y			(240*SCREEN_SCALE)		// �P�l�p���[�h���S�̈ʒu(Y���W)
#define	SINGLE_WIDTH			(70*SCREEN_SCALE)		// �P�l�p���[�h���S�̕�
#define	SINGLE_HEIGHT			(70*SCREEN_SCALE)		// �P�l�p���[�h���S����

#define	MULTI_POS_X				(400*SCREEN_SCALE)		// 2�l�p���[�h���S�̈ʒu(X���W)
#define	MULTI_POS_Y				(400*SCREEN_SCALE)		// 2�l�p���[�h���S�̈ʒu(Y���W)
#define	MULTI_WIDTH				(70*SCREEN_SCALE)		// 2�l�p���[�h���S�̕�
#define	MULTI_HEIGHT			(70*SCREEN_SCALE)		// 2�l�p���[�h���S����

#define	RANKING_POS_X			(400*SCREEN_SCALE)		// �����L���O���S�̈ʒu(X���W)
#define	RANKING_POS_Y			(500*SCREEN_SCALE)		// �����L���O���S�̈ʒu(Y���W)
#define	RANKING_WIDTH			(70*SCREEN_SCALE)		// �����L���O���S�̕�
#define	RANKING_HEIGHT			(70*SCREEN_SCALE)		// �����L���O���S����

#define	CURSOR_POS_X			(250*SCREEN_SCALE)		// �J�[�\�����S�̈ʒu(X���W)
#define	CURSOR_POS_Y			(240*SCREEN_SCALE)		// �J�[�\�����S�̈ʒu(Y���W)
#define	CURSOR_WIDTH			(50*SCREEN_SCALE)		// �J�[�\�����S�̕�
#define	CURSOR_HEIGHT			(20*SCREEN_SCALE)		// �J�[�\�����S����

#define	COUNT_APPERA_START		(60*60)		// �X�^�[�g�{�^���o���܂ł̎��� �b*�t���[��
#define	INTERVAL_DISP_START		(60)		// �X�^�[�g�{�^���_�ł̎���

#define	COUNT_WAIT_DEMO			(60 * 5)	// �f���܂ł̑҂�����

//=============================================================================
// �v���g�^�C�v�錾
//=============================================================================

//=============================================================================
// �O���[�o���ϐ�
//=============================================================================
C2DObject titlebg;		//�^�C�g���w�i
C2DObject titlename;	//�^�C�g���l�[��
C2DObject startbutton;	//�X�^�[�g�{�^��
C2DObject singlemode;	//�V���O�����[�h
C2DObject multimode;	//�}���`���[�h
C2DObject rankingmode;	//�����L���O
C2DObject cursor;		//�J�[�\��
bool pop;				//pop�̏�����
int position;			//�J�[�\���̈ʒu�@position�̐錾
int x;

int flagCount;
//=============================================================================
// ����������
//=============================================================================
HRESULT InitTitlelogo(void)
{
	pop = true;
	x = 0;
	flagCount = 0;

	titlebg.Init(SCREEN_CENTER_X, SCREEN_CENTER_Y, SCREEN_WIDTH/2, SCREEN_HEIGHT/2, TEXTURE_TITLE);
	titlename.Init(TITLE_LOGO_NAMEPOS_X, TITLE_LOGO_NAMEPOS_Y, TITLE_LOGO_NAMESX, TITLE_LOGO_NAMESY, TEXTURE_LOGO_NAME);
	startbutton.Init(START_POS_X, START_POS_Y, START_WIDTH, START_HEIGHT, START_BUTTON);
	singlemode.Init(SINGLE_POS_X, SINGLE_POS_Y, SINGLE_WIDTH, SINGLE_HEIGHT, SINGLE_LOGO);
	multimode.Init(MULTI_POS_X, MULTI_POS_Y, MULTI_WIDTH, MULTI_HEIGHT, MULTI_LOGO);
	rankingmode.Init(RANKING_POS_X, RANKING_POS_Y, RANKING_WIDTH, RANKING_HEIGHT, RANKING_LOGO);
	cursor.Init(CURSOR_POS_X, CURSOR_POS_Y, CURSOR_WIDTH, CURSOR_HEIGHT, CURSOR_LOGO);
	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitTitlelogo(void)
{
		titlebg.Release();
		titlename.Release();
		startbutton.Release();
		singlemode.Release();
		multimode.Release();
		rankingmode.Release();
		cursor.Release();
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawTitlelogo(void)
{
		titlebg.Draw();
		titlename.Draw();

		//�X�^�[�g�{�^�����\������Ă����Ԃ�Enter�������ƃ��j���[���\�������
		if (pop == true)
		{
			startbutton.Draw();
		}

		if (pop == false)
		{
			singlemode.Draw();
			multimode.Draw();
			rankingmode.Draw();
			cursor.Draw();
		}
}


//=============================================================================
// �X�V����
//=============================================================================
void UpdateTitlelogo(void)
{

	if (pop == false)//�I����ʂ̎�
	{
		flagCount++;//�J�E���g��i�߂�
		if (flagCount >= COUNT_APPERA_START)//�����J�E���g�����ɒB������
		{
			pop = true;//�X�^�[�g�{�^���ɖ߂�
			flagCount = 0;//�J�E���g���Z�b�g
			x = 0;//���͏��
		}
		PrintDebugProcess("flagCount: (%d)\n", flagCount);

	}

	//�����͂ŃJ�[�\�������Ɉړ�
	if (GetKeyboardTrigger(DIK_DOWN))
	{
		x = x + 1;
		flagCount = 0;//�J�E���g���Z�b�g
	}

	//�J�[�\������ԉ��ɂ����ԂŁ����͂���ƈ�ԏ�ɖ߂�
	if (x >= CURSORMAX)
	{
		x = 0;
	}

	//�����͂ŃJ�[�\������Ɉړ�
	if (GetKeyboardTrigger(DIK_UP))
	{
		x = x - 1;
		flagCount = 0;//�J�E���g���Z�b�g
	}

	//�J�[�\������ԏ�ɂ����ԂŁ����͂���ƈ�ԉ��ɖ߂�
	if (x < 0)
	{
		x = CURSORMAX-1;
	}
	
	//�f�o�b�O�\��
	PrintDebugProcess("x : (%d)\n", x);

	switch (x)//�J�[�\���̍��W�Ɋe���[�h���S�̂x���W�����킹��
	{
	case SINGLE:
	{
		cursor.SetStatus(CURSOR_POS_X, SINGLE_POS_Y, CURSOR_WIDTH, CURSOR_HEIGHT);
		break;
	}

	case MULTI:
	{
		cursor.SetStatus(CURSOR_POS_X, MULTI_POS_Y, CURSOR_WIDTH, CURSOR_HEIGHT);
		break;
	}

	case RANKING:
	{
		cursor.SetStatus(CURSOR_POS_X, RANKING_POS_Y, CURSOR_WIDTH, CURSOR_HEIGHT);
		break;
	}
	default:
		break;
	}
	cursor.SetVertex();//�|���S���𔽉f

	//�Q�[����ʂɈڍs
	if (GetKeyboardTrigger(DIK_RETURN)&& pop == false)
	{
		if(x == SINGLE)
		{
			Scene::SetScene(SCENE_GAME);
		}

		else if (x == MULTI)
		{
			Scene::SetScene(SCENE_GAME);
		}

		//���U���g(�����L���O)��ʂɈڍs
		else if (x == RANKING)
		{
			Scene::SetScene(SCENE_RANKING);
		}
	}

	else if (GetKeyboardTrigger(DIK_RETURN) && pop == true)
	{
		pop = false;
	}

}
