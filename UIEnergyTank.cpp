#include "UIEnergyTank.h"

static Vector2 vtsBack = Vector2( 7, 16);
static Vector2 vtsTank = Vector2(10, 20);

Dx9Texture CEnergyTankUI::texTank;
Dx9Texture CEnergyTankUI::texVolume;
Dx9Texture CEnergyTankUI::texVoiceTen;

void CEnergyTankUI::Initialize()
{
	texTank.LoadTexture("data/TEXTURE/UI/タンク/ボイスタンク2.png");
	texVolume.LoadTexture("data/TEXTURE/UI/タンク/ボイスゲージ.png");
	texVoiceTen.LoadTexture("data/TEXTURE/UI/タンク/ボイスゲージ枠.png");
}
void CEnergyTankUI::Uninitialize()
{
	texTank.Release();
	texVolume.Release();
	texVoiceTen.Release();
}

void CEnergyTankUI::Init(float posX, float posY, float sizX, float sizY, float value)
{
	this->Position = Vector2(posX, posY);
	this->Size = Vector2(sizX, sizY);
	this->MaxValue = value;

	this->Back.Init(posX, posY, vtsBack.x * sizX, vtsBack.y * sizY);
	this->Back.SetVertex(0xFF888888L);

	this->Liquid.Init(posX, posY, vtsBack.x * sizX, vtsBack.y * sizY);
	this->Liquid.SetVertex(0xFF00FFFFL);

	this->Tank.Init(     posX, posY, vtsTank.x * sizX, vtsTank.y * sizY);
	this->Volume.Init(   posX, posY, vtsTank.x * sizX, vtsTank.y * sizY);
	this->VoiceTen.Init( posX, posY, vtsTank.x * sizX, vtsTank.y * sizY);

}

void CEnergyTankUI::SetValue(float value)
{
	this->Back.SetStatus(     this->Position, Vector2(vtsBack.x * this->Size.x, vtsBack.y * this->Size.y));
	this->Liquid.SetStatus(   this->Position, Vector2(vtsBack.x * this->Size.x, vtsBack.y * this->Size.y));
	this->Tank.SetStatus(     this->Position, Vector2(vtsTank.x * this->Size.x, vtsTank.y * this->Size.y));
	this->Volume.SetStatus(   this->Position, Vector2(vtsTank.x * this->Size.x, vtsTank.y * this->Size.y));
	this->VoiceTen.SetStatus( this->Position, Vector2(vtsTank.x * this->Size.x, vtsTank.y * this->Size.y));

	float cor = (this->MaxValue - value) / this->MaxValue;
	this->Liquid.SetVertex(0, Vector3(this->Position.x - vtsBack.x * this->Size.x, this->Position.y - vtsBack.y * this->Size.y + (cor * vtsBack.y * this->Size.y * 2.0f), 0));
	this->Liquid.SetVertex(1, Vector3(this->Position.x + vtsBack.x * this->Size.x, this->Position.y - vtsBack.y * this->Size.y + (cor * vtsBack.y * this->Size.y * 2.0f), 0));

	const float vtgPos[8] = {
		1.0f,
		0.78f,
		0.665f,
		0.56f,
		0.44f,
		0.322f,
		0.22f,
		0.0f
	};
	const float sta = this->MaxValue * 140.0f / 1000.0f;
	int rate;
	if (value < sta * 1)      rate = 0;
	else if (value < sta * 2) rate = 1;
	else if (value < sta * 3) rate = 2;
	else if (value < sta * 4) rate = 3;
	else if (value < sta * 5) rate = 4;
	else if (value < sta * 6) rate = 5;
	else if (value < sta * 7) rate = 6;
	else                      rate = 7;

	this->Volume.SetVertex(0, Vector3(this->Position.x - vtsTank.x * this->Size.x, (this->Position.y - vtsTank.y * this->Size.y) + (vtsTank.y * this->Size.y * 2.0f) * vtgPos[rate], 0));
	this->Volume.SetVertex(1, Vector3(this->Position.x + vtsTank.x * this->Size.x, (this->Position.y - vtsTank.y * this->Size.y) + (vtsTank.y * this->Size.y * 2.0f) * vtgPos[rate], 0));
	this->Volume.SetTexture(0, 0.0f, vtgPos[rate]);
	this->Volume.SetTexture(1, 1.0f, vtgPos[rate]);
}

void CEnergyTankUI::Draw()
{
	this->Back.Draw();
	this->Liquid.Draw();
	this->Tank.Draw(texTank);
	this->Volume.Draw(texVolume);
	this->VoiceTen.Draw(texVoiceTen);
}

