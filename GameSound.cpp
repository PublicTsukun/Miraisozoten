//===============================================================
//�Q�[���T�E���h����
//==============================================================
#include "GameSound.h"
#include "Library\Sound.h"
#include "SceneManager.h"
#include "Library\DebugProcess.h"
#include "Library\Input.h"

#include "StageManager.h"

class BGM : public DirectSound
{
public:
	void FadeVolume(int flag);
};

BGM SoundBGM[BGM_MAX];
DirectSound SoundSE[SE_MAX];


int		BGMVolume;
int		SEVolume;

//�t�@�C���z��̍쐬�@���w�b�_�[��enum�Ə��Ԃ����킹�邱�ƁiPlay��Stop�ɉe�����o��j
const char *BGMFile[BGM_MAX]=
{
	"data/BGM/�^�C�g���E���U���g�E�����L���O��ʉ��� (2).wav",
	"data/BGM/�H�t���X�e�[�W����.wav",
	"data/BGM/�A�����J�X�e�[�WBGM���.wav",
	"data/BGM/�F���X�e�[�W����.wav",
	"data/BGM/���C�u�n�E�X�X�e�[�W�����i�{�[�i�X�j.wav",
	"data/BGM/�^�C�g���E���U���g�E�����L���O��ʉ��� (2).wav",
};

const char *SEFile[SE_MAX] =
{
	"data/SE/�I���J�[�\���ړ����i���j���[�I���E���O����etc�j.wav",
	"data/SE/����{�^�����i�^�C�g����ʁE���j���[��ʁE���O�ŏI���莞�E���ǂ�A��߂Ƃ����������Ƃ����j.wav",
	"data/SE/�Q�[���X�^�[�g��.wav",
	"data/SE/�J�E���g��_1.wav",
	"data/SE/�J�E���g��_2.wav",
	"data/SE/�J�E���g��_3.wav",
	"data/SE/�Q�[���Z�b�g��.wav",
	"data/SE/�{�C�X�e�����ˉ�.wav",
	"data/SE/���U���g�X�R�A�W�v���i�������Ђ����獂���œ����Ă鎞�̉��j.wav",
	"data/SE/���U���g�X�R�A�m�艹�i�������S�Ċm�肵���������̉��j.wav",
	"data/SE/�I�i�l�K�e�B�u�Ȑl�j�����C�ɂȂ�����_�ʏ�_.wav",
	"data/SE/�^�C�g����ʂ��烁�j���[��ʂɂ������Ƃ��i���[�h��I��łˁI���j.wav",
	"data/SE/�J�[�e��.wav",
	"data/SE/�{�[�i�X�Q�[�W�����܂������i1�i�K�E2�i�K�ځj.wav",
	"data/SE/�{�[�i�X�Q�[�W��MAX�ɂȂ������̉�.wav",
	"data/SE/�^�C�g���ɖ߂�Ƃ��̉��i�����L���O�̌�E�I�v�V��������^�C�g�����ǂ�I����j.wav",
	"data/SE/�����L���O���܎��i���߂łƂ��I���j.wav",
	"data/SE/1�����Ƃ̃X�R�A�m�艹.wav",
	"data/SE/�I���J�E���g�̉�.wav",
	"data/SE/������������.wav",
};

//=============================================================================
//������
//=============================================================================

HRESULT InitGameSound(void)
{


	for (int i = 0; i < BGM_MAX; i++)
	{
		SoundBGM[i].Volume = BGM_VOLUME_MIN;
		SoundBGM[i].LoadSound(BGMFile[i]);
	}

	for (int i = 0; i < SE_MAX; i++)
	{
		SoundSE[i].LoadSound(SEFile[i]);
	}
	SoundSE[SHOOT_BULLET].SetVolume();

	BGMVolume = BGM_VOLUME_MAX;
	SEVolume = SE_VOLUME_MAX;

	return S_OK;
}

//=============================================================================
//�I������
//=============================================================================

void UninitGameSound(void)
{
	for (int i = 0; i < BGM_MAX; i++)
	{
		SoundBGM[i].Release();
	}


	for (int i = 0; i < SE_MAX; i++)
	{
		SoundSE[i].Release();
	}

}

//=============================================================================
//SE�Đ�
//=============================================================================
void PlaySE(int no)
{
	SoundSE[no].Play(E_DS8_FLAG_NONE, 0);
}
//=============================================================================
//BGM�Đ�
//=============================================================================
void PlayBGM(int no)
{
	SoundBGM[no].Play(E_DS8_FLAG_LOOP, 0);
}


//=============================================================================
//SE��~
//=============================================================================
void StopSE(int no)
{
	SoundSE[no].Stop();
}
//=============================================================================
//BGM��~
//=============================================================================
void StopBGM(int no)
{
	SoundBGM[no].Stop();
}


//=============================================================================
//SE���ʃ`�F�b�N
//=============================================================================
long VolumeCheckSE(void)
{
	return SEVolume;
}

//=============================================================================
//BGM���ʃ`�F�b�N
//=============================================================================
long VolumeCheckBGM(void)
{
	return BGMVolume;
}


//=============================================================================
//SE�Đ��m�F
//=============================================================================
bool PlayCheckSE(int no)
{
	return SoundSE[no].CheckPlaying();
}

//=============================================================================
//BGM�Đ��m�F
//=============================================================================
bool PlayCheckBGM(int no)
{
	return SoundBGM[no].CheckPlaying();
}

//=============================================================================
//BGM�t�F�[�h����
//=============================================================================
void BGM::FadeVolume(int flag)
{
	//true=�t�F�[�h�C���@false=�t�F�[�h�A�E�g
	switch (flag)
	{
	case SOUND_FADE_IN:
		if (this->Volume == BGM_VOLUME_MIN)
		{
			this->Play(E_DS8_FLAG_LOOP, 0);
		}

		if (this->Volume < BGMVolume)
		{
			this->Volume += VOLUME_CONTROL_UP;
			if (this->Volume >= BGMVolume)
			{
				this->Volume = BGMVolume;
			}
		}

		break;

	case SOUND_FADE_OUT:
		if (this->Volume > BGM_VOLUME_MIN)
		{
			this->Volume -= VOLUME_CONTROL_DOWN;
			if (this->Volume <= BGM_VOLUME_MIN)
			{
				this->Volume = BGM_VOLUME_MIN;
			}
		}

		break;

	case SOUND_FADE_HALF:
		if (this->Volume > BGM_VOLUME_HALF)
		{
			this->Volume -= VOLUME_CONTROL_DOWN;
			if (this->Volume <= BGM_VOLUME_HALF)
			{
				this->Volume = BGM_VOLUME_HALF;
			}
		}

		break;

	}
	this->SetVolume();
}

//=============================================================================
//BGM�A�b�v�f�[�g����
//=============================================================================
void UpdateGameSound(void)
{
	STAGE *stage = GetStage();

	switch (Scene::SetScene(SCENE_MAX))
	{
	case SCENE_TITLE:
		SoundBGM[TITLE].FadeVolume(SOUND_FADE_IN);
		SoundBGM[GAME_AKIBA].FadeVolume(SOUND_FADE_OUT);
		SoundBGM[GAME_AMERICA].FadeVolume(SOUND_FADE_OUT);
		SoundBGM[GAME_SPACE].FadeVolume(SOUND_FADE_OUT);
		SoundBGM[GAME_BONUS].FadeVolume(SOUND_FADE_OUT);
		SoundBGM[RESULT].FadeVolume(SOUND_FADE_OUT);
		break;

	case SCENE_GAME:
		switch (stage->no)
		{
		case 0:
			SoundBGM[TITLE].FadeVolume(SOUND_FADE_OUT);
			SoundBGM[GAME_AKIBA].FadeVolume(SOUND_FADE_IN);
			SoundBGM[GAME_SPACE].FadeVolume(SOUND_FADE_OUT);
			SoundBGM[GAME_AMERICA].FadeVolume(SOUND_FADE_OUT);
			SoundBGM[GAME_BONUS].FadeVolume(SOUND_FADE_OUT);
			SoundBGM[RESULT].FadeVolume(SOUND_FADE_OUT);
			break;
		case 1:
			SoundBGM[TITLE].FadeVolume(SOUND_FADE_OUT);
			SoundBGM[GAME_AKIBA].FadeVolume(SOUND_FADE_OUT);
			SoundBGM[GAME_SPACE].FadeVolume(SOUND_FADE_OUT);
			SoundBGM[GAME_AMERICA].FadeVolume(SOUND_FADE_IN);
			SoundBGM[GAME_BONUS].FadeVolume(SOUND_FADE_OUT);
			SoundBGM[RESULT].FadeVolume(SOUND_FADE_OUT);
			break;
		case 2:
			SoundBGM[TITLE].FadeVolume(SOUND_FADE_OUT);
			SoundBGM[GAME_AKIBA].FadeVolume(SOUND_FADE_OUT);
			SoundBGM[GAME_SPACE].FadeVolume(SOUND_FADE_IN);
			SoundBGM[GAME_AMERICA].FadeVolume(SOUND_FADE_OUT);
			SoundBGM[GAME_BONUS].FadeVolume(SOUND_FADE_OUT);
			SoundBGM[RESULT].FadeVolume(SOUND_FADE_OUT);
			break;
		case 3:
			SoundBGM[TITLE].FadeVolume(SOUND_FADE_OUT);
			SoundBGM[GAME_AKIBA].FadeVolume(SOUND_FADE_OUT);
			SoundBGM[GAME_SPACE].FadeVolume(SOUND_FADE_OUT);
			SoundBGM[GAME_AMERICA].FadeVolume(SOUND_FADE_OUT);
			SoundBGM[GAME_BONUS].FadeVolume(SOUND_FADE_IN);
			SoundBGM[RESULT].FadeVolume(SOUND_FADE_OUT);
			break;

		}
		break;

	case SCENE_PAUSE:
		SoundBGM[TITLE].FadeVolume(SOUND_FADE_OUT);
		SoundBGM[GAME_AKIBA].FadeVolume(SOUND_FADE_HALF);
		SoundBGM[GAME_SPACE].FadeVolume(SOUND_FADE_HALF);
		SoundBGM[GAME_AMERICA].FadeVolume(SOUND_FADE_HALF);
		SoundBGM[GAME_BONUS].FadeVolume(SOUND_FADE_HALF);
		SoundBGM[RESULT].FadeVolume(SOUND_FADE_OUT);
		break;

	case SCENE_RESULT:
		SoundBGM[TITLE].FadeVolume(SOUND_FADE_OUT);
		SoundBGM[GAME_AKIBA].FadeVolume(SOUND_FADE_OUT);
		SoundBGM[GAME_SPACE].FadeVolume(SOUND_FADE_OUT);
		SoundBGM[GAME_AMERICA].FadeVolume(SOUND_FADE_OUT);
		SoundBGM[GAME_BONUS].FadeVolume(SOUND_FADE_OUT);
		SoundBGM[RESULT].FadeVolume(SOUND_FADE_IN);
		break;
	}

	for (int i = 0; i < BGM_MAX; i++)
	{
		if (SoundBGM[i].Volume <= BGM_VOLUME_MIN)
		{
			SoundBGM[i].Stop();
		}
	}
	PrintDebugProcess("\nTITLE%d  ", SoundBGM[TITLE].Volume);
	PrintDebugProcess("%d\n", PlayCheckBGM(TITLE));
	PrintDebugProcess("GAME AKIBA%d  ", SoundBGM[GAME_AKIBA].Volume);
	PrintDebugProcess("%d\n", PlayCheckBGM(GAME_AKIBA));
	PrintDebugProcess("GAME SPACE%d  ", SoundBGM[GAME_SPACE].Volume);
	PrintDebugProcess("%d\n", PlayCheckBGM(GAME_SPACE));
	PrintDebugProcess("GAME AMERICA%d  ", SoundBGM[GAME_AMERICA].Volume);
	PrintDebugProcess("%d\n", PlayCheckBGM(GAME_AMERICA));
	PrintDebugProcess("GAME BONUS%d  ", SoundBGM[GAME_BONUS].Volume);
	PrintDebugProcess("%d\n", PlayCheckBGM(GAME_BONUS));
	PrintDebugProcess("RESULT%d  ", SoundBGM[RESULT].Volume);
	PrintDebugProcess("%d\n", PlayCheckBGM(RESULT));

}

//===================================================================
//SE����
//==================================================================
void SEVolumeTurning(void)
{
	if (GetKeyboardPress(DIK_RIGHT) || IsButtonPressed(LSTICK_RIGHT))
	{
		SEVolume += 100;
		if (SEVolume > SE_VOLUME_MAX)
		{
			SEVolume = SE_VOLUME_MAX;
		}
	}

	if (GetKeyboardPress(DIK_LEFT) || IsButtonPressed(LSTICK_LEFT))
	{
		SEVolume -= 100;
		if (SEVolume < SE_VOLUME_MIN)
		{
			SEVolume = SE_VOLUME_MIN;
		}
	}
		for (int i = 0; i < SE_MAX; i++)
		{
			SoundSE[i].Volume = SEVolume;
			SoundSE[i].SetVolume();
		}
		PrintDebugProcess("SE���� %d", SEVolume);
}


//===================================================================
//BGM����
//==================================================================
void BGMVolumeTurning(void)
{
	if (GetKeyboardPress(DIK_RIGHT) || IsButtonPressed(LSTICK_RIGHT))
	{
		BGMVolume += 100;
		if (BGMVolume > BGM_VOLUME_MAX)
		{
			BGMVolume = BGM_VOLUME_MAX;
		}
	}

	if (GetKeyboardPress(DIK_LEFT) || IsButtonPressed(LSTICK_LEFT))
	{
		BGMVolume -= 100;
		if (BGMVolume < BGM_VOLUME_MIN+100)
		{
			BGMVolume = BGM_VOLUME_MIN+100;
		}
	}

	for (int i = 0; i < BGM_MAX; i++)
	{
		SoundBGM[i].Volume = BGMVolume;
		SoundBGM[i].SetVolume();
	}
	PrintDebugProcess("BGM���� %d", BGMVolume);

}