#include "EffectVoicetenHit.h"
#include "Library/DebugProcess.h"


//static bool BlendMode = true;
static int  EffectLifeTime = 15;

Dx9Texture EffectVoicetenHit::texA;
Dx9Texture EffectVoicetenHit::texB;
Dx9Texture EffectVoicetenHit::texC;


void EffectVoicetenHit::PolygonA::Set(Vector3 pos, float rng)
{
	float s = rng / (10.0f * ((float)(Random(100, 200)) / 100.0f));
	//s = rng / 10.0f;
	this->Size = Vector2(s, s);
	this->Scale = 1.0f;
	this->SetVertex();
	float t = DegToRad(Random(0, 180));
	float p = DegToRad(Random(0, 360) - 180);
	float r = (float)Random(((int)rng / 4), (int)rng / 2);
	this->Position.x = r * sinf(t) * cosf(p);
	this->Position.y = r * cosf(t);
	this->Position.z = r * sinf(t) * sinf(p);
	this->Position += pos;
}
void EffectVoicetenHit::PolygonA::Go(Vector3 pos, int count)
{
	this->Position += (pos - this->Position) / (float)(count + 1);
	this->Scale -= (1.0f / (float)(EffectLifeTime * 2));
}

void EffectVoicetenHit::PolygonB::Draw(Vector3 wPos)
{
	LPDIRECT3DDEVICE9 pDevice = Direct3D::GetD3DDevice();
	D3DXMATRIX mtxScl, mtxRot, mtxTranslate, mtxWorld;

	// ���e�X�g��L����
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);		// ON
	pDevice->SetRenderState(D3DRS_ALPHAREF, 10);				// ��r���郿�̒l
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);	// ����(GREATER : ��Ȃ�)

	// ���C���e�B���O�؂�ւ�
	DWORD light;
	pDevice->GetRenderState(D3DRS_LIGHTING, &light);
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	// ���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&mtxWorld);

	// �}�g���b�N�X�̐���
	// ���s�ړ��𔽉f
	D3DXMatrixTranslation(&mtxTranslate, Position.x, Position.y, Position.z);
	D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxTranslate);

	// ��]�𔽉f (���� : y, x, z�̏�)
	D3DXMatrixRotationYawPitchRoll(&mtxRot, Rotation.y, Rotation.x, Rotation.z);
	D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxRot);

	// ���s�ړ��𔽉f
	D3DXMatrixTranslation(&mtxTranslate, wPos.x, wPos.y, wPos.z);
	D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxTranslate);

	// ���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &mtxWorld);

	// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���Ƀo�C���h
	pDevice->SetStreamSource(0, VtxBuff, 0, sizeof(VERTEX_3D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, Texture);

	// �|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, RECT_NUM_POLYGON);

	// ���C���e�B���O����
	pDevice->SetRenderState(D3DRS_LIGHTING, light);

	// ���e�X�g�𖳌���
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
}
void EffectVoicetenHit::PolygonB::Set(Vector3 pos, float rng, int m)
{
	float r = (float)Random(((int)rng / (4 * m)), (int)rng / (2 * m));// 2 = �T�C�Y����
	this->Size = Vector2(r / 30.0f, r);
	this->Position = Vector3(0, r, 0);
	this->Rotation.x = DegToRad(Random(0, 360));
	this->Rotation.y = DegToRad(Random(0, 360));
	this->Rotation.z = DegToRad(Random(0, 360));
	this->Color = 0xFFFFFFFFL;
	this->SetVertex(this->Color);
}
void EffectVoicetenHit::PolygonB::Motion(int count)
{
	this->Color = 0x00FFFFFFL;
	if (count)
		this->Color |= ((DWORD)((255.0f * ((float)count / (float)EffectLifeTime)))) << 24;
	this->SetVertex(this->Color);
}

void EffectVoicetenHit::PolygonC::Set(Vector3 pos, float rng)
{
	this->Scale = 0.3f;
	this->Size = Vector2(rng / 2.0f, rng / 2.0f);
	this->Position = pos;
	this->Rotation.x = DegToRad(Random(0, 360));
	this->Rotation.y = DegToRad(Random(0, 360));
	this->Rotation.z = DegToRad(Random(0, 360));
	this->Color = 0xFFFFFFFFL;
	this->SetVertex(this->Color);
}
void EffectVoicetenHit::PolygonC::Motion(int count)
{
	this->Scale += ((float)EffectLifeTime / 400.0f) * ((float)count / (float)EffectLifeTime);
	this->Color = 0x00FFFFFFL;
	if (count)
		this->Color |= ((DWORD)((255.0f * ((float)count / (float)EffectLifeTime)))) << 24;
	this->SetVertex(this->Color);
}

void EffectVoicetenHit::Initialize()
{
	//texA.LoadTexture("data/TEXTURE/�G�t�F�N�g/texA.png");
	//texB.LoadTexture("data/TEXTURE/�G�t�F�N�g/texB.png");
	//texC.LoadTexture("data/TEXTURE/�G�t�F�N�g/texC.png");
}
void EffectVoicetenHit::Uninitialize()
{
	//texA.Release();
	//texB.Release();
	//texB.Release();
}

int EffectVoicetenHit::Init()
{
	for (int i = 0; i < EVH_PolygonANumber ; i++)
	{
		this->Note[i].MakeVertex();
		this->Note[i].LoadTexture(texA);
	}
	for (int i = 0; i < EVH_PolygonBNumber ; i++)
	{
		this->Line[i].MakeVertex();
		this->Line[i].LoadTexture(texB);
	}
	for (int i = 0; i < EVH_PolygonCNumber ; i++)
	{
		this->Waka[i].MakeVertex();
		this->Waka[i].LoadTexture(texC);
	}
	this->Position = Vector3();
	this->Range = 10.0f;
	this->Counter = 0;

	return 0;
}

int EffectVoicetenHit::Update()
{
	if (Counter <= 0)
		return 1;
	else
		this->Counter--;

	for (int i = 0; i < EVH_PolygonANumber ; i++)
	{
		this->Note[i].Go(this->Position, this->Counter);
	}
	for (int i = 0; i < EVH_PolygonBNumber ; i++)
	{
		this->Line[i].Motion(this->Counter);
	}
	for (int i = 0; i < EVH_PolygonCNumber ; i++)
	{
		this->Waka[i].Motion(this->Counter);
	}

	return 0;
}

void EffectVoicetenHit::Draw(bool mode)
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

		/* �`�� */
		for (int i = 0; i < EVH_PolygonANumber ; i++)
		{
			this->Note[i].Draw(DRAWSTATE_BILLBOARD, "ST");
		}
		for (int i = 0; i < EVH_PolygonBNumber ; i++)
		{
			this->Line[i].Draw(Position);
		}
		for (int i = 0; i < EVH_PolygonCNumber ; i++)
		{
			this->Waka[i].Draw(DRAWSTATE_OFFLIGHTING, "SRT");
		}

		/* ���� */
		pDevice->SetRenderState(D3DRS_CULLMODE, cull);
		pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, blend);
		pDevice->SetRenderState(D3DRS_BLENDOP, op);
		pDevice->SetRenderState(D3DRS_SRCBLEND, bSRC);
		pDevice->SetRenderState(D3DRS_DESTBLEND, bDEST);
	}
}

void EffectVoicetenHit::Uninit()
{
	for (int i = 0; i < EVH_PolygonANumber ; i++)
	{
		this->Note[i].ReleaseVertex();
	}
	for (int i = 0; i < EVH_PolygonBNumber ; i++)
	{
		this->Line[i].ReleaseVertex();
	}
	for (int i = 0; i < EVH_PolygonCNumber ; i++)
	{
		this->Waka[i].ReleaseVertex();
	}
}

void EffectVoicetenHit::Call(Vector3 pos, float rng)
{
	this->Position = pos;
	this->Range = rng;
	this->Counter = EffectLifeTime;

	for (int i = 0; i < EVH_PolygonANumber ; i++)
	{
		this->Note[i].Set(pos, rng);
	}
	for (int i = 0; i < EVH_PolygonBNumber ; i++)
	{
		this->Line[i].Set(pos, rng, (i % 10 == 0) ? 1 : 2);
	}
	for (int i = 0; i < EVH_PolygonCNumber ; i++)
	{
		this->Waka[i].Set(pos, rng);
	}
}

int EffectVoicetenHit::CheckState()
{
	return this->Counter < 0 ? 0 : this->Counter;
}

int *GetEffectVHTime()
{
	return &EffectLifeTime;
}

//bool ChangeVHBlendMode(bool mode)
//{
//	if (mode)
//		BlendMode = BlendMode ? false : true;
//	return BlendMode;
//}
