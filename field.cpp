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

Dx9Texture LiveTex;
//=============================================================================
// ����������
//=============================================================================
HRESULT InitField(void)
{

	wall[0].Init(wallPos, wallSize);
	//wall[1].Init(wallPos, wallSize);
	wall[1].Init(Vector3(wallPos.x, wallPos.y, 2600 * 0.75 - 600), wallSize*0.75);
	wall[2].Init(Vector3(wallPos.x, wallPos.y, 2600 * 0.5 - 600), wallSize*0.5);


	for (int i = 0; i < WALL_LIVE_NUM_X*WALL_LIVE_NUM_Y; i++)
	{
		Vector3 Pos;
		Pos.x = LivewallPos.x + LIVEWALL_SIZE_X*2*(i%WALL_LIVE_NUM_X);
		Pos.y = LivewallPos.y - LIVEWALL_SIZE_Y*2*(i / WALL_LIVE_NUM_X);
		Pos.z = LivewallPos.z;

		Vector2 Size;
		Size.x = LIVEWALL_SIZE_X;
		Size.y = LIVEWALL_SIZE_Y;
		LiveWall[i].Init(Pos, Size);
		LiveWall[i].LoadTexture(LiveTex);
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
	wall[0].LoadTexture(WallTex[0]);
	wall[1].LoadTexture(WallTex[1]);
	wall[2].LoadTexture(WallTex[2]);

	LiveTex.LoadTexture("data/TEXTURE/UI/���U���g/�肴��Ɣw�i.png");

}

void ReleaseTex(void)
{
	for (int i = 0; i < 3; i++)
	{
		wall[i].Release();
	}
	LiveTex.Release();
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
		//LiveWall[i].Draw();
	}


}

void UpdateField(void)
{
	//wall[1].Print();

	//if (GetKeyboardPress(DIK_UP))
	//{
	//	wall[1].MoveWallZ(1.0f);
	//}
	//if (GetKeyboardPress(DIK_DOWN))
	//{
	//	wall[1].MoveWallZ(-1.0f);
	//}
	//if (GetKeyboardPress(DIK_LEFT))
	//{
	//	wall[0].MoveWallX(-10.0f);
	//}
	//if (GetKeyboardPress(DIK_RIGHT))
	//{
	//	wall[0].MoveWallX(10.0f);
	//}
	//
	//if (GetKeyboardPress(DIK_Q))
	//{
	//	wall[1].MoveWallY(-1.0f);
	//}
	//if (GetKeyboardPress(DIK_E))
	//{
	//	wall[1].MoveWallY(1.0f);
	//}
	//
	//if (GetKeyboardPress(DIK_W))
	//{
	//	wall[0].SizeWallY(10.0f);
	//}
	//if (GetKeyboardPress(DIK_A))
	//{
	//	wall[0].SizeWallX(-10.0f);
	//}
	//if (GetKeyboardPress(DIK_S))
	//{
	//	wall[0].SizeWallY(-10.0f);
	//}
	//if (GetKeyboardPress(DIK_D))
	//{
	//	wall[0].SizeWallX(10.0f);
	//}
	//wall[0].Print();
}


void SetFeildTex(int StageNo)
{
	wall[0].LoadTexture(WallTex[StageNo*3+0]);
	wall[1].LoadTexture(WallTex[StageNo*3+1]);
	wall[2].LoadTexture(WallTex[StageNo*3+2]);
	
}