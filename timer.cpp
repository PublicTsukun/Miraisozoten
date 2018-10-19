//=============================================================================
//
// フィールド処理 [field.cpp]
//
//=============================================================================
#include "field.h"
#include "Library/ObjectBase3D.h"



//*****************************************************************************
// グローバル変数
//*****************************************************************************
C3DPolygonObject ground;	//床用
C3DPolygonObject wall[4];	//壁用
C3DPolygonObject ceiling;	//天井用

const Vector3 groundPos = Vector3(GROUND_POS_X, GROUND_POS_Y, GROUND_POS_Z);
const Vector2 groundSize = Vector2(GROUND_SIZE_X, GROUND_SIZE_X);
const Vector3 groundRot = Vector3(GROUND_ROT, 0.0f, 0.0f);

const Vector2 wallSize = Vector2(WALL_SIZE_X, WALL_SIZE_Y);

const Vector3 LwallPos = Vector3(LEFTWALL_POS_X, LEFTWALL_POS_Y, LEFTWALL_POS_Z);
const Vector3 LwallRot = Vector3(0.0f, LEFTWALL_ROT, 0.0f);

const Vector3 RwallPos = Vector3(RIGHTWALL_POS_X, RIGHTWALL_POS_Y, RIGHTWALL_POS_Z);
const Vector3 RwallRot = Vector3(0.0f, RIGHTWALL_ROT, 0.0f);

const Vector3 BwallPos = Vector3(BACKWALL_POS_X, BACKWALL_POS_Y, BACKWALL_POS_Z);

const Vector3 ceilingPos = Vector3(CEILING_POS_X, CEILING_POS_Y, CEILING_POS_Z);
const Vector2 ceilingSize = Vector2(CEILING_SIZE_X, CEILING_SIZE_Y);
const Vector3 ceilingRot = Vector3(CEILING_ROT, 0.0f, 0.0f);

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitField(void)
{

	ground.Init(groundPos, groundRot, groundSize);
	ground.LoadTexture("data/作業/床.jpg");

	wall[0].Init(LwallPos, LwallRot, wallSize);
	wall[0].LoadTexture("data/作業/西.jpg");
	wall[1].Init(RwallPos, RwallRot, wallSize);
	wall[1].LoadTexture("data/作業/東.jpg");
	wall[2].Init(BwallPos, wallSize);
	wall[2].LoadTexture("data/作業/北.jpg");
	wall[3].Init(Vector3(0, 1000, 0), Vector3(0, PI, 0), Vector2(1000, 1000));
	wall[3].LoadTexture("data/作業/南.jpg");

	ceiling.Init(ceilingPos, ceilingRot, ceilingSize);
	ceiling.LoadTexture("data/作業/天井.jpg");

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitField(void)
{
	ground.Release();

	for (int i = 0; i < 4; i++)
	{
		wall[i].Release();
	}

	ceiling.Release();
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawField(void)
{
	ground.Draw();

	for (int i = 0; i < 4; i++)
	{
		wall[i].Draw();
	}

	ceiling.Draw();

}


