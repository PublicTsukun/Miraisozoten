//=============================================================================
//
// ���C������ [main.cpp]
//
//=============================================================================
#include "Library/Common.h"
#include "Library/TsuLibSystem.h"
#include "Library/WindowClass.h"
#include "Library/Direct3D.h"
#include "Library/FPSManager.h"
#include "Library/Input.h"
#include "Library/Sound.h"
#include "Library/Fade.h"
#include "Library/Camera.h"
#include "Library/Light.h"
#include "Library/DebugProcess.h"
#include "FadeCurtain.h"
#include "SceneManager.h"


//****************************************************************
// �}�N����`
//****************************************************************
#define CLASS_NAME  "hal2018FCEgameApplication"	// �E�C���h�E�̃N���X��
#define WINDOW_NAME "�ӂ���Ă������I"	// �E�C���h�E�̃L���v�V������


//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT Init(void);
void Uninit(void);
void Update(void);
void Draw(void);


//*****************************************************************************
// �O���[�o���ϐ�:
//*****************************************************************************
bool DispDebug = true;	// �f�o�b�O�\��ON/OFF


//=============================================================================
// ���C���֐�
//=============================================================================
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);	// �����Ă��ǂ����ǁA�x�����o��i���g�p�錾�j
	UNREFERENCED_PARAMETER(lpCmdLine);		// �����Ă��ǂ����ǁA�x�����o��i���g�p�錾�j

	// TSU�V�X�e����������
	if (FAILED(TsuSystem::Initialize(hInstance)))
		return -1;

	// ���̑�������
	if (FAILED(Init()))
		return -1;

	//�t���[���J�E���g������
	timeBeginPeriod(1);	// ����\�ݒ�
	FPSManager::Init();	// FPS����

	/* ���b�Z�[�W���[�v */
	while (1)
	{
		if (WindowClass::CheckMessage())
			break;

		if (FPSManager::FramerateControl())
		{
			PrintDebugProcess("FPS : %f    ", FPSManager::DisplayFPS(FPS_NORMAL));
			PrintDebugProcess("SCENE : ");
			switch (Scene::SetScene(SCENE_MAX))
			{
			case SCENE_TITLE:   PrintDebugProcess("Title\n");       break;
			case SCENE_GAME:    PrintDebugProcess("Game\n");        break;
			case SCENE_PAUSE:   PrintDebugProcess("Pause\n");       break;
			case SCENE_RESULT:  PrintDebugProcess("Result\n");      break;
			case SCENE_MAX:     PrintDebugProcess("������...\n");   break;
			case SCENE_END:     PrintDebugProcess("�I�������ł�(�\������Ȃ��͂�����)\n");   break;
			}

			switch (Scene::GetFadeState())
			{
			case CLOSS:
				if (Scene::UpdateFade())
				{
					Scene::SetScene(SCENE_GAME);
				}
				break;
			case OPEN:
				if (Scene::UpdateFade())
				{
					Scene::SetFadeState(SLEEP);
				}
				break;
			case SLEEP:
				Update();	// �X�V����
				break;
			}
			Draw();		// �`�揈��
		}
	}

	Uninit();					// ���̑��I������
	TsuSystem::Uninitialize();	// TSU�V�X�e����������

	timeEndPeriod(1);	// ����\��߂�

	return 0;
}


//=============================================================================
// ����������
//=============================================================================
HRESULT Init()
{
	// �t�F�[�h
	CSFade::MakeVertex();
	FadeCurtain::Init();

	// �^�C�g���V�[���ɃZ�b�g
	Scene::SetScene(SCENE_TITLE, false);

	// �J����
	InitCamera();

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void Uninit(void)
{
	// �t�F�[�h
	FadeCurtain::Uninit();

	Scene::SetScene(SCENE_END);

}

//=============================================================================
// �X�V����
//=============================================================================
void Update(void)
{
	// ���͂̍X�V����
	UpdateInput();

	// �J�����̍X�V����
	UpdateCamera(Vector3());

	if (GetKeyboardTrigger(DIK_F3))
	{// �f�o�b�O�\��ON/OFF
		DispDebug = DispDebug ? false : true;
	}

	// �V�[���̍X�V
	Scene::Update();

	// �t�F�[�h�����̍X�V
	CSFade::Update();

}

//=============================================================================
// �`�揈��
//=============================================================================
void Draw(void)
{
	// �o�b�N�o�b�t�@���y�o�b�t�@�̃N���A
	Direct3D::GetD3DDevice()->Clear(0, NULL, (D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER),
		D3DCOLOR_RGBA(0x66, 0x88, 0xFF, 0xFF), 1.0f, 0);

	// Direct3D�ɂ��`��̊J�n
	if (SUCCEEDED(Direct3D::GetD3DDevice()->BeginScene()))
	{
		// �J����
		SetCamera();

		// �V�[���̕`��
		Scene::Draw();

		// �t�F�[�h�`��
		CSFade::Draw();

		// �f�o�b�O�\���̕`�揈��
		if (DispDebug)
		{
			DrawDebugProcess();
		}

		// Direct3D�ɂ��`��̏I��
		Direct3D::GetD3DDevice()->EndScene();
	}

	// �o�b�N�o�b�t�@�ƃt�����g�o�b�t�@�̓���ւ�
	Direct3D::GetD3DDevice()->Present(NULL, NULL, NULL, NULL);
}


