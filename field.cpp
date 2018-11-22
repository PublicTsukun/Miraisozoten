//=============================================================================
//
// フィールド処理 [field.cpp]
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
		PrintDebugProcess("\nPOSITION X[%f]Y[%f]Z[%f]\n", this->Position.x, this->Position.y, this->Position.z);
		PrintDebugProcess("SIZE X[%f]Y[%f]\n\n", this->Size.x, this->Size.y);
	}

};

//*****************************************************************************
// グローバル変数
//*****************************************************************************
Wall wall[3];	//壁用

const Vector2 wallSize = Vector2(WALL_SIZE_X, WALL_SIZE_Y);

const Vector3 wallPos = Vector3(WALL_POS_X, WALL_POS_Y, WALL_POS_Z);



const char *WallTex[] =
{
	"data/TEXTURE/ステージ/アキバ/バック.png",
	"data/TEXTURE/ステージ/アキバ/ミッド.png",
	"data/TEXTURE/ステージ/アキバ/フロント.png",
};
//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitField(void)
{

	wall[0].Init(wallPos, wallSize);
	wall[1].Init(wallPos, wallSize);
	wall[2].Init(wallPos, wallSize);

	wall[0].LoadTexture(WallTex[0]);
	wall[1].LoadTexture(WallTex[1]);
	wall[2].LoadTexture(WallTex[2]);

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitField(void)
{

	for (int i = 0; i < 3; i++)
	{
		wall[i].Release();
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawField(void)
{

	for (int i = 0; i < 3; i++)
	{
		wall[i].Draw();
	}


}

void UpdateField(void)
{

	//if (GetKeyboardPress(DIK_UP))
	//{
	//	wall[0].MoveWallZ(10.0f);
	//}
	//if (GetKeyboardPress(DIK_DOWN))
	//{
	//	wall[0].MoveWallZ(-10.0f);
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
	//	wall[0].MoveWallY(-10.0f);
	//}
	//if (GetKeyboardPress(DIK_E))
	//{
	//	wall[0].MoveWallY(10.0f);
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


