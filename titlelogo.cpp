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
#include "GameSound.h"


//=============================================================================
// �}�N����`
//=============================================================================
#define	TEXTURE_TITLE		"data/TEXTURE/UI/�^�C�g��/�^�C�g���w�i.jpg"// �ǂݍ��ރe�N�X�`���̃t�@�C����
#define	TEXTURE_LOGO_NAME	"data/TEXTURE/UI/�^�C�g��/�^�C�g��.png"		// �ǂݍ��ރ^�C�g�����S�̃t�@�C����
#define START_BUTTON		"data/TEXTURE/UI/�^�C�g��/�ڂ���������Ă�.png"			// �ǂݍ��ރX�^�[�g�{�^���̃t�@�C����
#define SINGLE_LOGO			"data/TEXTURE/UI/�^�C�g��/�ЂƂ�ł�����.png"				// �ǂݍ��ނP�l�p���[�h���S�̃t�@�C����
#define MULTI_LOGO			"data/TEXTURE/UI/�^�C�g��/�ӂ���ł�����.png"			// �ǂݍ��ނQ�l�p���[�h���S�t�@�C����
#define RANKING_LOGO		"data/TEXTURE/UI/�^�C�g��/��񂫂�.png"			// �ǂݍ��ރ����L���O���S�̃t�@�C����
#define CURSOR_LOGO			"data/TEXTURE/UI/�^�C�g��/�J�[�\��.png"	// �ǂݍ��ރJ�[�\�����S�̃t�@�C����

//#define	TITLE_LOGO_WIDTH		(1000)		// �^�C�g�����S�̕�640
//#define	TITLE_LOGO_HEIGHT		(300)		// �^�C�g�����S�̍���640

#define	START_POS_X				(450*SCREEN_SCALE)		// �X�^�[�g�{�^���̈ʒu(X���W)
#define	START_POS_Y				(640*SCREEN_SCALE)		// �X�^�[�g�{�^���̈ʒu(Y���W)
#define	START_WIDTH				(390*SCREEN_SCALE)		// �X�^�[�g�{�^���̕�
#define	START_HEIGHT			(90*SCREEN_SCALE)		// �X�^�[�g�{�^���̍���

#define	SINGLE_POS_X			(450*SCREEN_SCALE)		// �P�l�p���[�h���S�̈ʒu(X���W)
#define	SINGLE_POS_Y			(180*SCREEN_SCALE)		// �P�l�p���[�h���S�̈ʒu(Y���W)
#define	SINGLE_WIDTH			(312*SCREEN_SCALE)		// �P�l�p���[�h���S�̕�
#define	SINGLE_HEIGHT			(72*SCREEN_SCALE)		// �P�l�p���[�h���S����

#define	MULTI_POS_X				(450*SCREEN_SCALE)		// 2�l�p���[�h���S�̈ʒu(X���W)
#define	MULTI_POS_Y				(380*SCREEN_SCALE)		// 2�l�p���[�h���S�̈ʒu(Y���W)
#define	MULTI_WIDTH				(320*SCREEN_SCALE)		// 2�l�p���[�h���S�̕�
#define	MULTI_HEIGHT			(72*SCREEN_SCALE)		// 2�l�p���[�h���S����

#define	RANKING_POS_X			(450*SCREEN_SCALE)		// �����L���O���S�̈ʒu(X���W)
#define	RANKING_POS_Y			(580*SCREEN_SCALE)		// �����L���O���S�̈ʒu(Y���W)
#define	RANKING_WIDTH			(312*SCREEN_SCALE)		// �����L���O���S�̕�
#define	RANKING_HEIGHT			(72*SCREEN_SCALE)		// �����L���O���S����

#define	CURSOR1_POS_X			(MULTI_POS_X-MULTI_WIDTH-60)		// �J�[�\�����S�̈ʒu(X���W)
#define	CURSOR1_POS_Y			(240*SCREEN_SCALE)		// �J�[�\�����S�̈ʒu(Y���W)
#define	CURSOR2_POS_X			(MULTI_POS_X+MULTI_WIDTH+60)		// �J�[�\�����S�̈ʒu(X���W)
#define	CURSOR2_POS_Y			(240*SCREEN_SCALE)		// �J�[�\�����S�̈ʒu(Y���W)
#define	CURSOR_WIDTH			(80*SCREEN_SCALE)		// �J�[�\�����S�̕�
#define	CURSOR_HEIGHT			(80*SCREEN_SCALE)		// �J�[�\�����S����


#define	COUNT_APPERA_START		(30*60)		// �X�^�[�g�{�^���o���܂ł̎��� �b*�t���[��
#define	INTERVAL_DISP_START		(60)		// �X�^�[�g�{�^���_�ł̎���

#define	COUNT_WAIT_DEMO			(60 * 5)	// �f���܂ł̑҂�����

#define TITLE_SOUND_MAX				(4)

//=============================================================================
// �v���g�^�C�v�錾
//=============================================================================
void SetScale(int no);

//=============================================================================
// �O���[�o���ϐ�
//=============================================================================
C2DObject titlebg;		//�^�C�g���w�i
C2DObject titlename;	//�^�C�g���l�[��
C2DObject startbutton;	//�X�^�[�g�{�^��
C2DObject singlemode;	//�V���O�����[�h
C2DObject multimode;	//�}���`���[�h
C2DObject rankingmode;	//�����L���O
C2DObject cursor[2];		//�J�[�\��
bool pop;				//pop�̏�����
int position;			//�J�[�\���̈ʒu�@position�̐錾
int x;

int flagCount;

float	ButtonAlpha;

const char *MenuBgTex[] = {
	"data/TEXTURE/UI/�^�C�g��/���j���[���_��.png",
	"data/TEXTURE/UI/�^�C�g��/���j���[���_��.png",
	"data/TEXTURE/UI/�^�C�g��/���j���[���_��.png",
};


const Vector2 MenuBgPos[] = {
	Vector2(SINGLE_POS_X,SINGLE_POS_Y),
	Vector2(MULTI_POS_X,MULTI_POS_Y),
	Vector2(RANKING_POS_X,RANKING_POS_Y)
};

const Vector2 MenuBgSize[] = {
	Vector2(SINGLE_WIDTH+100,SINGLE_HEIGHT+20),
	Vector2(MULTI_WIDTH+92,MULTI_HEIGHT+20),
	Vector2(RANKING_WIDTH+100,RANKING_HEIGHT+20)
};

C2DObject MenuBg[3];

float Scale[3] = { 1.0f,1.0f,1.0f };


//=============================================================================
// ����������
//=============================================================================
HRESULT InitTitlelogo(void)
{
	pop = true;
	x = 0;
	flagCount = 0;

	titlebg.Init(SCREEN_CENTER_X, SCREEN_CENTER_Y, SCREEN_WIDTH/2, SCREEN_HEIGHT/2, TEXTURE_TITLE);
	titlename.Init(SCREEN_CENTER_X, SCREEN_CENTER_Y-60, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, TEXTURE_LOGO_NAME);

	startbutton.Init(START_POS_X, START_POS_Y, START_WIDTH, START_HEIGHT, START_BUTTON);
	singlemode.Init(SINGLE_POS_X, SINGLE_POS_Y, SINGLE_WIDTH, SINGLE_HEIGHT, SINGLE_LOGO);
	multimode.Init(MULTI_POS_X, MULTI_POS_Y, MULTI_WIDTH, MULTI_HEIGHT, MULTI_LOGO);
	rankingmode.Init(RANKING_POS_X, RANKING_POS_Y, RANKING_WIDTH, RANKING_HEIGHT, RANKING_LOGO);

	cursor[0].Init(CURSOR1_POS_X, CURSOR1_POS_Y, CURSOR_WIDTH, CURSOR_HEIGHT, CURSOR_LOGO);
	cursor[1].Init(CURSOR2_POS_X, CURSOR2_POS_Y, CURSOR_WIDTH, CURSOR_HEIGHT, CURSOR_LOGO);

	for (int i = 0; i < 3; i++)
	{
		MenuBg[i].Init(MenuBgPos[i].x, MenuBgPos[i].y, MenuBgSize[i].x, MenuBgSize[i].y, MenuBgTex[i]);
	}
	
	ButtonAlpha = 0.0f;
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

	cursor[0].Release();
	cursor[1].Release();

	for (int i = 0; i < 3; i++)
	{
		MenuBg[i].Release();
	}


}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawTitlelogo(void)
{
		titlebg.Draw();

		//�X�^�[�g�{�^�����\������Ă����Ԃ�Enter�������ƃ��j���[���\�������
		if (pop == true)
		{
			startbutton.Draw();
			titlename.Draw();
		}

		if (pop == false)
		{
			for (int i = 0; i < 3; i++)
			{
				MenuBg[i].Draw();
			}

			singlemode.Draw();
			multimode.Draw();
			rankingmode.Draw();
			cursor[0].Draw();
			cursor[1].Draw();

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



		//�����͂ŃJ�[�\�������Ɉړ�
		if (GetKeyboardTrigger(DIK_DOWN))
		{
			x = x + 1;
			flagCount = 0;//�J�E���g���Z�b�g
			PlaySE(CURSOL);

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
			PlaySE(CURSOL);

		}

		//�J�[�\������ԏ�ɂ����ԂŁ����͂���ƈ�ԉ��ɖ߂�
		if (x < 0)
		{
			x = CURSORMAX - 1;
		}

		//�f�o�b�O�\��
		PrintDebugProcess("x : (%d)\n", x);
	}
	switch (x)//�J�[�\���̍��W�Ɋe���[�h���S�̂x���W�����킹��
	{
	case SINGLE:
	{
		cursor[0].SetStatus(CURSOR1_POS_X, SINGLE_POS_Y+50, CURSOR_WIDTH, CURSOR_HEIGHT);
		cursor[1].SetStatus(CURSOR2_POS_X, SINGLE_POS_Y+50, CURSOR_WIDTH, CURSOR_HEIGHT);
		break;
	}

	case MULTI:
	{
		cursor[0].SetStatus(CURSOR1_POS_X, MULTI_POS_Y+50, CURSOR_WIDTH, CURSOR_HEIGHT);
		cursor[1].SetStatus(CURSOR2_POS_X, MULTI_POS_Y+50, CURSOR_WIDTH, CURSOR_HEIGHT);
		break;
	}

	case RANKING:
	{
		cursor[0].SetStatus(CURSOR1_POS_X, RANKING_POS_Y+50, CURSOR_WIDTH, CURSOR_HEIGHT);
		cursor[1].SetStatus(CURSOR2_POS_X, RANKING_POS_Y+50, CURSOR_WIDTH, CURSOR_HEIGHT);
		break;
	}
	default:
		break;
	}
	SetScale(x);

	for (int i = 0; i < 2; i++)
	{
		cursor[i].SetTexture(x,3,1);
	}

	cursor[1].SetVertex();
	cursor[0].SetVertex(0, Vector2((1.0f / 3.0f)*(x + 1), 0.0f));
	cursor[0].SetVertex(1, Vector2((1.0f / 3.0f)*x, 0.0f));
	cursor[0].SetVertex(2, Vector2((1.0f / 3.0f)*(x + 1), 1.0f));
	cursor[0].SetVertex(3, Vector2((1.0f / 3.0f)*x, 1.0f));


	//�Q�[����ʂɈڍs
	if (GetKeyboardTrigger(DIK_RETURN)&& pop == false)
	{

		PlaySE(DECIDE);

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
		PlaySE(MODE);
	}


	ButtonAlpha += 0.06;
	startbutton.SetVertex(D3DXCOLOR(1.0f, 1.0f, 1.0f, fabs(sinf(ButtonAlpha)) + 0.3f));
}

void SetScale(int no)
{
	for (int i = 0; i < 3; i++)
	{
		if (i == no)
		{
			Scale[i] += 0.02f;

			if (Scale[i] >= 1.0f)
			{
				Scale[i] = 1.0f;
			}
		}
		else
		{
			Scale[i] -= 0.01f;
		
			if (Scale[i] <= 0.8f)
			{
				Scale[i] = 0.8f;
			}
		
		}
		PrintDebugProcess("Scale[%d] %f\n", i, Scale[i]);
	}



		singlemode.SetStatus(Scale[0],0.0f);
		multimode.SetStatus(Scale[1], 0.0f);
		rankingmode.SetStatus(Scale[2], 0.0f);
		MenuBg[0].SetStatus(Scale[0], 0.0f);
		MenuBg[1].SetStatus(Scale[1], 0.0f);
		MenuBg[2].SetStatus(Scale[2], 0.0f);

	
}