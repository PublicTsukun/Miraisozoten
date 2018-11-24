#include "FadeCurtain.h"
#include "Library/Common.h"
#include "Library/Math.h"

constexpr int Partition[FADE_CURTAIN_STATE_MAX] = { 54, 56 };
constexpr int FadeSpeed[FADE_CURTAIN_STATE_MAX] = { 1, 2 };
constexpr const char *TexturePath[FADE_CURTAIN_STATE_MAX] = {
	"data/TEXTURE/UI/カーテン開.png",
	"data/TEXTURE/UI/カーテン閉.png"
};


Dx9Texture FadeCurtain::Texture[FADE_CURTAIN_STATE_MAX];

int FadeCurtain::Init()
{
	Texture[0].LoadTexture(TexturePath[0]);
	Texture[1].LoadTexture(TexturePath[1]);
	return 0;
}

void FadeCurtain::Uninit()
{
	Texture[0].Release();
	Texture[1].Release();
}


FadeCurtain::FadeCurtain()
{
	this->State = SLEEP;
	this->TextureNumber = 0;
	this->Timer = 0;
	this->MakeVertex(SCREEN_CENTER_X, SCREEN_CENTER_Y, SCREEN_CENTER_X, SCREEN_CENTER_Y);
}

int FadeCurtain::Update()
{
	if (this->State != SLEEP)
	{
		this->Timer++;

		int s = (Partition[this->State] / 10) * (Partition[this->State] % 10);
		if ( (this->TextureNumber < s) && 
			!(this->Timer % FadeSpeed[this->State]) )
		{
			this->SetTexture(this->TextureNumber++,	// 引数で渡した後にインクリメント
				Partition[this->State] / 10,		// 横の分割数を計算
				Partition[this->State] % 10);		// 縦の分割数を計算
		}

		if (this->TextureNumber >= s)
			return 1;
	}

	return 0;
}

inline void FadeCurtain::Draw()
{
	if (this->State != SLEEP)
		this->ObjectBase2D::Draw(Texture[this->State]);
}

void FadeCurtain::SetFade(FADE_CURTAIN_STATE state)
{
	this->State = state;
	this->TextureNumber = 0;
	this->Timer = 0;
	if (this->State != SLEEP)
		this->SetTexture(0, Partition[this->State] / 10, Partition[this->State] % 10);
}

