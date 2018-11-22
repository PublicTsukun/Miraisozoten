#define _CRT_SECURE_NO_WARNINGS

#include "Library/DebugProcess.h"
#include "MicTest.h"
#include <stdio.h>
#include <Windows.h>
#include <tchar.h>
#include <time.h>
#include <math.h>
#include <dsound.h>
#include <mmsystem.h>
#pragma comment (lib, "winmm.lib")
#pragma comment (lib, "DSound.lib")


LPDIRECTSOUNDCAPTURE g_pDSCapture = NULL;// DirectSoundCaptureDevice�I�u�W�F�N�g
LPDIRECTSOUNDCAPTUREBUFFER g_pDSBCapture = NULL;// DirectSoundCaptureBuffer�I�u�W�F�N�g
DSCBUFFERDESC dscbd;// DirectSound Capture Buffer DESC �L���v�`�� �o�b�t�@���L�q����\���́B 


DWORD dwNextCaptureOffset = 0;	// ���̓ǂݍ��݊J�n�ʒu���i�[����ϐ��B
DWORD dwReadPos;				// �ǂݍ��݉\�J�[�\���̃J�����g�|�W
DWORD dwCapturePos;				// �L���v�`���J�[�\���̃J�����g�|�W
void* pbCaptureData = NULL;	// �ǂݍ��ވ�ڂ̃u���b�N�̃|�C���^ 
DWORD dwCaptureLength;		// �ǂݍ��ވ�ڂ̃u���b�N�̒���
void* pbCaptureData2 = NULL;// �ǂݍ��ނQ�ڂ̃u���b�N�̃|�C���^ 
DWORD dwCaptureLength2;		// �ǂݍ��ނQ�ڂ̃u���b�N�̒���
UINT  dwDataWorte;
LONG  lLockSize;	// �o�b�t�@����ǂݍ��ރT�C�Y

short data1, data2;

WAVEFORMATEX wfx = { 
	WAVE_FORMAT_PCM,// wFormatTag�AWave�̃t�H�[�}�b�g
	1,				// nChannels�@���m�����P�@�X�e���I�Q�i�f�[�^�Z�b�g�̎�ށj
	48000,			// nSamplesPerSec�@1�b������̃T���v����
	48000 * 1,		// mAvgBytesPerSec�A1�b������̃o�C�g���BnSamplesPerSec��nBlockAlign�B
	1,				// nBlockAlign �P�T���v���̃o�C�g���BnChannels�~wBitsPerSample���W
	8,				// wBitsPerSample�@1�T���v��������̃r�b�g���B�W���P�U
	0 };			// cbSize�@��ɂO
// �P����PCM��WAVE�f�[�^���`�B
// wFormatTag�AWave�̃t�H�[�}�b�g
// nChannels�@���m�����P�@�X�e���I�Q�i�f�[�^�Z�b�g�̎�ށj
// nSamplesPerSec�@1�b������̃T���v����
// mAvgBytesPerSec�A1�b������̃o�C�g���BnSamplesPerSec��nBlockAlign�B
// nBlockAlign �P�T���v���̃o�C�g���BnChannels�~wBitsPerSample���W�@�W�E�E�E�W�r�b�g=�P�o�C�g
// wBitsPerSample�@1�T���v��������̃r�b�g���B�W���P�U
// cbSize�@��ɂO

int MicTestInit()
{
	// Initialize COM 
	CoInitialize(NULL);

	// Create IDirectSoundCapture8 using the default capture device
	DirectSoundCaptureCreate8(NULL, &g_pDSCapture, NULL);

	dscbd.dwSize = sizeof(DSCBUFFERDESC);
	dscbd.dwFlags = 0;
	dscbd.dwBufferBytes = wfx.nAvgBytesPerSec * 1;	// �����ŃL���v�`���o�b�t�@�̃T�C�Y��ݒ肵�Ă���B
													// ����̗�ł́A1�b�ԕ��̗e�ʃo�b�t�@�B
	dscbd.dwReserved = 0;
	dscbd.lpwfxFormat = &wfx;
	dscbd.dwFXCount = 0;
	dscbd.lpDSCFXDesc = NULL;


	g_pDSCapture->CreateCaptureBuffer(&dscbd, &g_pDSBCapture, NULL);
	// �o�b�t�@�̍쐬�I��

	// �L���v�`���o�b�t�@�X�^�[�g�B
	g_pDSBCapture->Start(DSCBSTART_LOOPING);
	// ���̖��߂ŃI�[�f�B�I�f�o�C�X���͉̂������͂�
	// �J�n���A�������ɏ������ݏo���B�������A���i�K�ł́A�܂����̃������ɃA�N�Z�X
	// ���邱�Ƃ͂ł��Ȃ��B

	return 0;
}

void MicTestUninit()
{
	// �L���v�`���o�b�t�@�X�g�b�v
	g_pDSBCapture->Stop();

	// �I�u�W�F�N�g�̃����[�X�B�܂��ADirectSound�I�u�W�F�N�g�̌�n���B
	g_pDSBCapture->Release();
	g_pDSBCapture = NULL;
	g_pDSCapture->Release();
	g_pDSCapture = NULL;

	CoUninitialize();
}

short MicTest()
{
	// �L���v�`���J�[�\���Ɠǂݍ��݉\�J�[�\���̃J�����g�|�W�V���������B
	g_pDSBCapture->GetCurrentPosition(&dwCapturePos, &dwReadPos);

	/*  */

	// �ǂݍ��݃J�[�\���̒����̃f�[�^�݂̂�ǂݍ������B
	g_pDSBCapture->Lock(dwReadPos, 1,
		&pbCaptureData, &dwCaptureLength,
		&pbCaptureData2, &dwCaptureLength2,
		NULL);

	data1 = *((short*)pbCaptureData);

	// 32639 : 7f7f : 0111 1111 0111 1111
	// 32640 : 7f80 : 0111 1111 1000 0000
	//-32640 : 8080 : 1000 0000 1000 0000
	//-32384 : 8180 : 1000 0001 1000 0000
	//const short L1 = 0x7FFF; //  127
	//const short L2 = 0x8000; //  128
	//const short L3 = 0x0180; // -32768

	short val = (data1 < 0) ? (-data1 - 32768) : (32767 - data1);

	// ���b�N�̉���
	g_pDSBCapture->Unlock(pbCaptureData, dwCaptureLength,
		pbCaptureData2, dwCaptureLength2);

	return val;
}

void MicReStart()
{
	g_pDSBCapture->Stop();

	if (g_pDSBCapture != NULL)
	{
		g_pDSBCapture->Release();
		g_pDSBCapture = NULL;
	}
	if (g_pDSCapture != NULL)
	{
		g_pDSCapture->Release();
		g_pDSCapture = NULL;
	}

	DirectSoundCaptureCreate8(NULL, &g_pDSCapture, NULL);
	g_pDSCapture->CreateCaptureBuffer(&dscbd, &g_pDSBCapture, NULL);
	g_pDSBCapture->Start(DSCBSTART_LOOPING);
}


