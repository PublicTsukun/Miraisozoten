#include "EffectFeelBetter.h"
#include "Library/DebugProcess.h"


//static bool BlendMode = true;
static int  EffectLifeTime = 80;

Dx9Texture EffectFeelBetter::texA;

void EffectFeelBetter::PolygonA::Set(Vector3 pos, float rng)
{
	float s = rng / (10.0f * ((float)(Random(100, 200)) / 100.0f));
	//s = rng / 10.0f;
	this->Size = Vector2(s, s);
	this->Scale = 1.0f;
	float t = DegToRad(Random(0, 360));
	this->Position = pos;
	this->KineticEnergy.x = rng * ((float)Random(0, 200) / 100.0f - 1.0f);
	//this->KineticEnergy.y = rng * ((float)Random(50, 75) / 100.0f);
	this->KineticEnergy.y = 0.0f;
	this->KineticEnergy.z = rng * ((float)Random(0, 200) / 100.0f - 1.0f);
	this->KineticEnergy = this->KineticEnergy.Normalized();
	this->Speed = rng / 10.0f * ((float)Random(50, 100) / 100.0f);
	this->Color = 0x00FFFFFF;
	this->Color |= (Random(0xAA, 0xFF)) << 24;
	this->SetVertex(this->Color);
}

void EffectFeelBetter::PolygonA::Motion()
{
	this->Speed -= this->Speed * 0.125f;
	this->KineticEnergy.y += 0.05f;
	this->Position += this->KineticEnergy * this->Speed;
	int a = this->Color >> 24;
	a -= 255 / EffectLifeTime + 1;
	if (a < 0) a = 0;
	this->Color &= 0x00FFFFFF;
	this->Color |= a << 24;
	this->SetVertex(this->Color);
}

void EffectFeelBetter::Initialize()
{
	texA.LoadTexture("data/TEXTURE/�G�t�F�N�g/texA.png");
}

void EffectFeelBetter::Uninitialize()
{
	texA.Release();
}

int EffectFeelBetter::Init()
{
	for (int i = 0; i < EFB_PolygonANumber; i++)
	{
		this->Note[i].MakeVertex();
		this->Note[i].LoadTexture(texA);
	}
	this->Position = Vector3();
	this->Range = 10.0f;
	this->Counter = 0;

	return 0;
}

int EffectFeelBetter::Update()
{
	if (Counter <= 0)
		return 1;
	else
		this->Counter--;

	for (int i = 0; i < EFB_PolygonANumber; i++)
	{
		this->Note[i].Motion();
	}

	return 0;
}

void EffectFeelBetter::Draw(bool mode)
{
	if (this->Counter)
	{
		LPDIRECT3DDEVICE9 pDevice = Direct3D::GetD3DDevice();
		DWORD cull;
		DWORD blend;
		DWORD op;
		DWORD bSRC;
		DWORD bDEST;
		/* ����Ԃ�ۑ� */
		pDevice->GetRenderState(D3DRS_CULLMODE, &cull);
		pDevice->GetRenderState(D3DRS_ALPHABLENDENABLE, &blend);
		pDevice->GetRenderState(D3DRS_BLENDOP, &op);
		pDevice->GetRenderState(D3DRS_SRCBLEND, &bSRC);
		pDevice->GetRenderState(D3DRS_DESTBLEND, &bDEST);

		/* �X�e�[�^�X�ύX */
		pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);	// ���ʃJ�����O��Off
		if (mode)
		{
			pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);	// �u�����h���[�h��ON
			pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);	// �u�����h���[�h�����Z��
			pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);	// SRC(�`��\�葤)�𔼓�������
			pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);	// DEST(�`��ςݑ�)�����̂܂ܕ`��
		}

		/* ���e�X�g�ݒ� */
		pDevice->SetRenderState(D3DRS_ALPHAREF, 1);					// ��r���郿�̒l
		pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);	// ����(GREATER : ��Ȃ�)

		/* �`�� */
		for (int i = 0; i < EFB_PolygonANumber; i++)
		{
			pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);	// ������Off�ɂȂ邽��On�ɂ���
			this->Note[i].Draw(DRAWSTATE_BILLBOARD | DRAWSTATE_OFFALPHATEST, "ST");
		}

		/* ���� */
		pDevice->SetRenderState(D3DRS_CULLMODE, cull);
		pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, blend);
		pDevice->SetRenderState(D3DRS_BLENDOP, op);
		pDevice->SetRenderState(D3DRS_SRCBLEND, bSRC);
		pDevice->SetRenderState(D3DRS_DESTBLEND, bDEST);
	}
}

void EffectFeelBetter::Uninit()
{
	for (int i = 0; i < EFB_PolygonANumber; i++)
	{
		this->Note[i].ReleaseVertex();
	}
}

void EffectFeelBetter::Call(Vector3 pos, float rng)
{
	this->Position = pos;
	this->Range = rng;
	this->Counter = EffectLifeTime;

	for (int i = 0; i < EFB_PolygonANumber; i++)
	{
		this->Note[i].Set(pos, rng);
	}
}

int EffectFeelBetter::CheckState()
{
	return this->Counter < 0 ? 0 : this->Counter;
}

int *GetEffectFBTime()
{
	return &EffectLifeTime;
}

//bool ChangeFBBlendMode(bool mode)
//{
//	if (mode)
//		BlendMode = BlendMode ? false : true;
//	return BlendMode;
//}
