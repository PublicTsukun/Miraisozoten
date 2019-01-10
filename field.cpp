//=============================================================================
//
// �t�B�[���h���� [field.cpp]
//
//=============================================================================
#include "field.h"
#include "Library/ObjectBase3D.h"
#include "Library\Input.h"
#include "Library\DebugProcess.h"


class Wall : public C3DPolygonObject
{
public:

	void MoveWallZ(float move)
	{
		this->Position.z += move;
		this->SetVertex();
	}
	void MoveWallY(float move)
	{
		this->Position.y += move;
		this->SetVertex();
	}

	void MoveWallX(float move)
	{
		this->Position.x += move;
		this->SetVertex();
	}

	void SizeWallX(float move)
	{
		this->Size.x += move;
		this->SetVertex();
	}
	void SizeWallY(float move)
	{
		this->Size.y += move;
		this->SetVertex();
	}

	void Print(void)
	{
		PrintDebugProcess("\n�w�i���\n", this->Position.x, this->Position.y, this->Position.z);
		PrintDebugProcess("POSITION X[%f]Y[%f]Z[%f]\n", this->Position.x, this->Position.y, this->Position.z);
		PrintDebugProcess("SIZE X[%f]Y[%f]\n\n", this->Size.x, this->Size.y);
	}

};

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
Wall wall[3];	//�Ǘp

const Vector2 wallSize = Vector2(WALL_SIZE_X, WALL_SIZE_Y);

const Vector3 wallPos = Vector3(WALL_POS_X, WALL_POS_Y, WALL_POS_Z);

C3DPolygonObject LiveWall[WALL_LIVE_NUM_X*WALL_LIVE_NUM_Y];
const Vector3 LivewallPos = Vector3(WALL_POS_X - (LIVEWALL_SIZE_X * 2 * (WALL_LIVE_NUM_X / 2)),
									WALL_POS_Y + (LIVEWALL_SIZE_Y * 2 * (WALL_LIVE_NUM_Y / 2)),
									WALL_POS_Z);

const char *WallTex[] =
{
	"data/TEXTURE/�X�e�[�W/�A�L�o/�o�b�N.png",
	"data/TEXTURE/�X�e�[�W/�A�L�o/�~�b�h.png",
	"data/TEXTURE/�X�e�[�W/�A�L�o/�t�����g.png",
	"data/TEXTURE/�X�e�[�W/�A�����J/�o�b�N.jpg",
	"data/TEXTURE/�X�e�[�W/�A�����J/�~�b�h.png",
	"data/TEXTURE/�X�e�[�W/�A�����J/�t�����g.png",
	"data/TEXTURE/�X�e�[�W/�F��/�o�b�N.jpg",
	"data/TEXTURE/�X�e�[�W/�F��/�~�b�h.png",
	"data/TEXTURE/�X�e�[�W/�F��/�t�����g.png",
};

Dx9Texture LiveTex[2];
//=============================================================================
// ����������
//=============================================================================
HRESULT InitField(void)
{

	wall[0].Init(wallPos, wallSize);
	wall[1].Init(wallPos, wallSize);
	wall[1].Init(Vector3(wallPos.x, wallPos.y, 2600 * 0.75 - 600), wallSize*0.75);
	wall[2].Init(Vector3(wallPos.x, wallPos.y, 2600 * 0.5 - 600), wallSize*0.5);

	SetFeildTex(0);

		Vector3 Pos;
		Vector2 Size;

	for (int i = 0; i < WALL_LIVE_NUM_X*WALL_LIVE_NUM_Y; i++)
	{
		Pos.x = LivewallPos.x + LIVEWALL_SIZE_X*2*(i%WALL_LIVE_NUM_X);
		Pos.y = LivewallPos.y - LIVEWALL_SIZE_Y*2*(i / WALL_LIVE_NUM_X);
		Pos.z = LivewallPos.z;

		Size.x = LIVEWALL_SIZE_X;
		Size.y = LIVEWALL_SIZE_Y;
		LiveWall[i].Init(Pos, Size);
		LiveWall[i].LoadTextureStatus(Size.x, Size.y, 1.0f, WALL_LIVE_NUM_X, WALL_LIVE_NUM_Y, 1);
		LiveWall[i].SetTexture(i, WALL_LIVE_NUM_X, WALL_LIVE_NUM_X);

	}

	return S_OK;
}


//=============================================================================
//
//===============================================================================
void LoadFieldTex(void)
{
	LiveTex[0].LoadTexture("data/TEXTURE/UI/���U���g/�肴��Ɣw�i.png");
	LiveTex[1].LoadTexture("data/TEXTURE/UI/���U���g/�肴��Ɣw�i.png");

	for (int i = 0; i < WALL_LIVE_NUM_X*WALL_LIVE_NUM_Y; i++)
	{
		LiveWall[i].LoadTexture(LiveTex[0]);
	}
}

void ReleaseTex(void)
{
	for (int i = 0; i < 3; i++)
	{
		wall[i].Release();
	}
	LiveTex[0].Release();
	LiveTex[1].Release();
}
//=============================================================================
// �I������
//=============================================================================
void UninitField(void)
{

	for (int i = 0; i < 3; i++)
	{
		wall[i].ReleaseVertex();
	}

	for (int i = 0; i < WALL_LIVE_NUM_X*WALL_LIVE_NUM_Y; i++)
	{
		LiveWall[i].ReleaseVertex();
	}

}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawField(void)
{

	for (int i = 0; i < 3; i++)
	{
		wall[i].Draw();
	}

	for (int i = 0; i < WALL_LIVE_NUM_X*WALL_LIVE_NUM_Y; i++)
	{
		LiveWall[i].Draw();
	}


}

void UpdateField(void)
{

	//�ǂ������Ƀ��C�g����
}


void SetFeildTex(int StageNo)
{
	wall[0].LoadTexture(WallTex[StageNo*3+0]);
	wall[1].LoadTexture(WallTex[StageNo*3+1]);
	wall[2].LoadTexture(WallTex[StageNo*3+2]);
	
}