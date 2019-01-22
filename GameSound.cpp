//===============================================================
//ゲームサウンド処理
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

//ファイル配列の作成　※ヘッダーのenumと順番を合わせること（PlayやStopに影響が出る）
const char *BGMFile[BGM_MAX]=
{
	"data/BGM/タイトル・リザルト・ランキング画面音源 (2).wav",
	"data/BGM/秋葉原ステージ音源.wav",
	"data/BGM/アメリカステージBGM候補.wav",
	"data/BGM/宇宙ステージ音源.wav",
	"data/BGM/ライブハウスステージ音源（ボーナス）.wav",
	"data/BGM/タイトル・リザルト・ランキング画面音源 (2).wav",
};

const char *SEFile[SE_MAX] =
{
	"data/SE/選択カーソル移動音（メニュー選択・名前入力etc）.wav",
	"data/SE/決定ボタン音（タイトル画面・メニュー画面・名前最終決定時・もどる、やめとくを押したとき等）.wav",
	"data/SE/ゲームスタート音.wav",
	"data/SE/カウント音_1.wav",
	"data/SE/カウント音_2.wav",
	"data/SE/カウント音_3.wav",
	"data/SE/ゲームセット音.wav",
	"data/SE/ボイステン発射音.wav",
	"data/SE/リザルトスコア集計音（数字がひたすら高速で動いてる時の音）.wav",
	"data/SE/リザルトスコア確定音（数字が全て確定しきった時の音）.wav",
	"data/SE/的（ネガティブな人）が元気になった音_通常点.wav",
	"data/SE/タイトル画面からメニュー画面にいったとき（モードを選んでね！音）.wav",
	"data/SE/カーテン.wav",
	"data/SE/ボーナスゲージがたまった音（1段階・2段階目）.wav",
	"data/SE/ボーナスゲージがMAXになった時の音.wav",
	"data/SE/タイトルに戻るときの音（ランキングの後・オプションからタイトルもどる選択後）.wav",
	"data/SE/ランキング入賞時（おめでとう！音）.wav",
	"data/SE/1桁ごとのスコア確定音.wav",
	"data/SE/終了カウントの音.wav",
	"data/SE/すごいすごい.wav",
};

//=============================================================================
//初期化
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
//終了処理
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
//SE再生
//=============================================================================
void PlaySE(int no)
{
	SoundSE[no].Play(E_DS8_FLAG_NONE, 0);
}
//=============================================================================
//BGM再生
//=============================================================================
void PlayBGM(int no)
{
	SoundBGM[no].Play(E_DS8_FLAG_LOOP, 0);
}


//=============================================================================
//SE停止
//=============================================================================
void StopSE(int no)
{
	SoundSE[no].Stop();
}
//=============================================================================
//BGM停止
//=============================================================================
void StopBGM(int no)
{
	SoundBGM[no].Stop();
}


//=============================================================================
//SE音量チェック
//=============================================================================
long VolumeCheckSE(void)
{
	return SEVolume;
}

//=============================================================================
//BGM音量チェック
//=============================================================================
long VolumeCheckBGM(void)
{
	return BGMVolume;
}


//=============================================================================
//SE再生確認
//=============================================================================
bool PlayCheckSE(int no)
{
	return SoundSE[no].CheckPlaying();
}

//=============================================================================
//BGM再生確認
//=============================================================================
bool PlayCheckBGM(int no)
{
	return SoundBGM[no].CheckPlaying();
}

//=============================================================================
//BGMフェード処理
//=============================================================================
void BGM::FadeVolume(int flag)
{
	//true=フェードイン　false=フェードアウト
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
//BGMアップデート処理
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
//SE調整
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
		PrintDebugProcess("SE音量 %d", SEVolume);
}


//===================================================================
//BGM調整
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
	PrintDebugProcess("BGM音量 %d", BGMVolume);

}