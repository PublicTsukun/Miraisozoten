#include "TsuLibSystem.h"
#include "WindowClass.h"
#include "Direct3D.h"
#include "Input.h"
#include "Sound.h"
#include "DebugProcess.h"


HRESULT TSULibrarySystem::Initialize(HINSTANCE hInstance)
{
	// �E�B���h�E������
	if (FAILED(WindowClass::Init(hInstance)))
		return -1;

	// �O���t�B�b�N�X������(Direct3D)
	if (FAILED(Direct3D::Init(WindowClass::GetHWnd(), TRUE)))
		return -1;

	// �C���v�b�g������
	if (FAILED(InitInput(WindowClass::GetHInstance(), WindowClass::GetHWnd())))
		return -1;

	// �T�E���h������
	if (FAILED(DirectSound::Init(WindowClass::GetHWnd())))
		return -1;

	// �f�o�b�O�\���̏�����
	InitDebugProcess();

	return S_OK;
}

void TSULibrarySystem::Uninitialize()
{
	WindowClass::Uninit();	// �E�B���h�E�I��
	Direct3D::Uninit();		// �O���t�B�b�N�X�I��(Direct3D)
	UninitInput();			// ���͂̏I������
	DirectSound::Uninit();	// �T�E���h�I������
	UninitDebugProcess();	// �f�o�b�O�\�������̏I������

}



