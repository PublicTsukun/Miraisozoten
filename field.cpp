//=============================================================================
//
// フィールド処理 [field.cpp]
//
//=============================================================================
#include "field.h"
#include "Library/ObjectBase3D.h"
#include "Library\Light.h"
#include "Library\Input.h"
#include "Library\DebugProcess.h"

#include "StageManager.h"
#include "UIBonus.h"

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

	void SetWall(Vector3 pos)
	{
		this->Position = pos;
		this->SetVertex();
	}

	Vector3 GetWallPos(void)
	{
		return this->Position;
	}

	void Print(void)
	{
		PrintDebugProcess("\n背景情報\n", this->Position.x, this->Position.y, this->Position.z);
		PrintDebugProcess("POSITION X[%f]Y[%f]Z[%f]\n", this->Position.x, this->Position.y, this->Position.z);
		PrintDebugProcess("SIZE X[%f]Y[%f]\n\n", this->Size.x, this->Size.y);
	}

};

//*****************************************************************************
// グローバル変数
//*****************************************************************************
Wall wall[3];	//壁用

const Vector2 wallSize = Vector2(WALL_SIZE_X, WALL_SIZE_Y);

const Vector3 wallPos = Vector3(WALL_POS_X, WALL_POS_Y, WALL_POS_Z);

Wall LiveWall[WALL_LIVE_NUM_X*WALL_LIVE_NUM_Y];
//Wall LiveWallFront;
const Vector3 LivewallPos = Vector3(WALL_POS_X - (LIVEWALL_SIZE_X * 2 * (WALL_LIVE_NUM_X / 2))+ LIVEWALL_SIZE_X,
									WALL_POS_Y + (LIVEWALL_SIZE_Y * 2 * (WALL_LIVE_NUM_Y / 2))-LIVEWALL_SIZE_Y,
									WALL_POS_Z);

bool LiveWallUse;

const char *WallTex[] =
{
	"data/TEXTURE/ステージ/アキバ/バック.jpg",
	"data/TEXTURE/ステージ/アキバ/ミッド.png",
	"data/TEXTURE/ステージ/アキバ/フロント.png",
	"data/TEXTURE/ステージ/アメリカ/バック.jpg",
	"data/TEXTURE/ステージ/アメリカ/ミッド.png",
	"data/TEXTURE/ステージ/アメリカ/フロント.png",
	"data/TEXTURE/ステージ/宇宙/バック.jpg",
	"data/TEXTURE/ステージ/宇宙/ミッド.png",
	"data/TEXTURE/ステージ/宇宙/フロント.png",
};

Dx9Texture LiveTex[2];

/* ライト */
Dx9Light BackLight;		// 環境光を当てる
Dx9Light SpotLight[6];	// スポットライト
Vector3  SpotVec[6];	// スポット先の座標
float    LCurve = 0.0f;						// カーブ値
float    LR = 0.0f, LG = 0.0f, LB = 0.0f;	// 色
bool     LFlg = true;						// 色用

//=============================================================================
// 初期化処理
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
		Pos.x = LivewallPos.x + LIVEWALL_SIZE_X * 2 * (i % WALL_LIVE_NUM_X);
		Pos.y = LivewallPos.y - LIVEWALL_SIZE_Y * 2 * (i / WALL_LIVE_NUM_X) - WALL_SIZE_Y * 2;
		Pos.z = LivewallPos.z;

		Size.x = LIVEWALL_SIZE_X;
		Size.y = LIVEWALL_SIZE_Y;
		LiveWall[i].Init(Pos, Size);
		LiveWall[i].LoadTextureStatus(Size.x, Size.y, 1.0f, WALL_LIVE_NUM_X, WALL_LIVE_NUM_Y, 1);
		LiveWall[i].SetTexture(i, WALL_LIVE_NUM_X, WALL_LIVE_NUM_Y);

	}
//	LiveWallFront.Init(WALL_POS_X, WALL_POS_Y - WALL_SIZE_Y * 2, WALL_POS_Z, WALL_SIZE_X, WALL_SIZE_Y);


	LiveWallUse = false;

	/* ライト */
	/* バックライト(環境光) */
	BackLight.Direction = Vector3(0, 0, 1);
	BackLight.Diffuse = D3DXCOLOR(0.1f, 0.1f, 0.1f, 1.0f);
	BackLight.SetLight(0);

	/* スポットライト */
	for (int i = 0; i < 5; i++)
	{
		SpotLight[i].Type = D3DLIGHT_SPOT;
		SpotLight[i].Position = Vector3((float)i * 600.0f - 1200.0f, 200.0f, 0.0f);
		SpotLight[i].Range = 2100.0f;
		SpotLight[i].Falloff = 2.0f;
		SpotLight[i].Attenuation0 = 0.5f;
		SpotLight[i].Attenuation1 = 0.0001f;
		SpotLight[i].Theta = DegToRad(10);
		SpotLight[i].Phi = DegToRad(20);
	}

	return S_OK;
}


//=============================================================================
//
//===============================================================================
void LoadFieldTex(void)
{
	LiveTex[0].LoadTexture("data/TEXTURE/ステージ/ライブステージ/バック.jpg");
//	LiveTex[1].LoadTexture("data/TEXTURE/ステージ/ライブステージ/フロント.png");

	for (int i = 0; i < WALL_LIVE_NUM_X*WALL_LIVE_NUM_Y; i++)
	{
		LiveWall[i].LoadTexture(LiveTex[0]);
	}
//	LiveWallFront.LoadTexture(LiveTex[1]);

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
// 終了処理
//=============================================================================
void UninitField(void)
{

	for (int i = 0; i < 3; i++)
	{
		wall[i].ReleaseVertex();
	}


}

//=============================================================================
// 描画処理
//=============================================================================
void DrawField(void)
{

	if (!LiveWallUse || !GetFiver())
	{
		for (int i = 0; i < 3; i++)
		{
			wall[i].Draw();
		}
	}

	if (GetFiver() || LiveWallUse)
	{
		Direct3D::GetD3DDevice()->SetRenderState(D3DRS_LIGHTING, TRUE);

		//DWORD blend;
		//DWORD op;
		//DWORD bSRC;
		//DWORD bDEST;

		for (int i = 0; i < WALL_LIVE_NUM_X*WALL_LIVE_NUM_Y; i++)
		{
			LiveWall[i].Draw();
		}

		//Direct3D::GetD3DDevice()->GetRenderState(D3DRS_ALPHABLENDENABLE, &blend);
		//Direct3D::GetD3DDevice()->GetRenderState(D3DRS_BLENDOP, &op);
		//Direct3D::GetD3DDevice()->GetRenderState(D3DRS_SRCBLEND, &bSRC);
		//Direct3D::GetD3DDevice()->GetRenderState(D3DRS_DESTBLEND, &bDEST);

		//Direct3D::GetD3DDevice()->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
		//Direct3D::GetD3DDevice()->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
		//Direct3D::GetD3DDevice()->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
		
//		LiveWallFront.Draw();

		//Direct3D::GetD3DDevice()->SetRenderState(D3DRS_ALPHABLENDENABLE, blend);
		//Direct3D::GetD3DDevice()->SetRenderState(D3DRS_BLENDOP, op);
		//Direct3D::GetD3DDevice()->SetRenderState(D3DRS_SRCBLEND, bSRC);
		//Direct3D::GetD3DDevice()->SetRenderState(D3DRS_DESTBLEND, bDEST);

		Direct3D::GetD3DDevice()->SetRenderState(D3DRS_LIGHTING, FALSE);
	}
}

void UpdateField(void)
{

	if (GetFiver())
	{
		if (LiveWall[0].GetWallPos().y < LivewallPos.y)
		{
			for (int i = 0; i < WALL_LIVE_NUM_X*WALL_LIVE_NUM_Y; i++)
			{
				LiveWall[i].MoveWallY(WALL_CHANGE_SPEED);
			}
//			LiveWallFront.MoveWallY(WALL_CHANGE_SPEED);
			for (int i = 0; i < 3; i++)
			{
				wall[i].MoveWallY(WALL_CHANGE_SPEED * (1 - 0.25f*i));
			}
		}
		else
		{
			Vector3 Pos;
			for (int i = 0; i < WALL_LIVE_NUM_X*WALL_LIVE_NUM_Y; i++)
			{

				Pos.x = LivewallPos.x + LIVEWALL_SIZE_X * 2 * (i % WALL_LIVE_NUM_X);
				Pos.y = LivewallPos.y - LIVEWALL_SIZE_Y * 2 * (i / WALL_LIVE_NUM_X);
				Pos.z = LivewallPos.z;

				LiveWall[i].SetWall(Pos);
			}
			Pos.x = WALL_POS_X;
			Pos.y = WALL_POS_Y;
			Pos.z = WALL_POS_Z;
//			LiveWallFront.SetWall(Pos);

			LiveWallUse = true;
		}
		LiveWall[0].Print();
	}
	else
	{
		if (LiveWall[0].GetWallPos().y > LivewallPos.y - WALL_SIZE_Y * 2)
		{
			for (int i = 0; i < WALL_LIVE_NUM_X*WALL_LIVE_NUM_Y; i++)
			{
				LiveWall[i].MoveWallY(-WALL_CHANGE_SPEED);
			}
//			LiveWallFront.MoveWallY(-WALL_CHANGE_SPEED);
			for (int i = 0; i < 3; i++)
			{
				wall[i].MoveWallY(-WALL_CHANGE_SPEED * (1 - 0.25f*i));
			}
		}
		else
		{
			Vector3 Pos;
			for (int i = 0; i < WALL_LIVE_NUM_X*WALL_LIVE_NUM_Y; i++)
			{

				Pos.x = LivewallPos.x + LIVEWALL_SIZE_X * 2 * (i % WALL_LIVE_NUM_X);
				Pos.y = LivewallPos.y - LIVEWALL_SIZE_Y * 2 * (i / WALL_LIVE_NUM_X) - WALL_SIZE_Y * 2;;
				Pos.z = LivewallPos.z;

				LiveWall[i].SetWall(Pos);
			}
			wall[0].SetWall(Vector3(wallPos.x, wallPos.y, wallPos.z));
			wall[1].SetWall(Vector3(wallPos.x, wallPos.y, 2600 * 0.75 - 600));
			wall[2].SetWall(Vector3(wallPos.x, wallPos.y, 2600 * 0.5 - 600));

			LiveWallUse = false;
		}
		LiveWall[0].Print();
	}


	//良い感じにライト処理
	STAGE *stage = GetStage();

	if (stage->status == STAGE_STATUS_NORMAL ||
		stage->status == STAGE_STATUS_END)
	{

		/* スポットライト */
		// 方向操作
		LCurve += 0.1f;
		for (int i = 0; i < 5; i++)
		{
			SpotVec[i].y = (i % 2) ? sinf(LCurve) : -sinf(LCurve);
		}

		// 色操作
		if (LFlg)
		{
			if (LR < 1.0f) LR += 0.05f;
			else if (LG < 1.0f) LG += 0.05f;
			else if (LB < 1.0f) LB += 0.05f;
			else               LFlg = false;
		}
		else
		{
			if (LB > 0.5f) LB -= 0.05f;
			else if (LG > 0.2f) LG -= 0.05f;
			else if (LR > 0.0f) LR -= 0.05f;
			else               LFlg = true;
		}

		// 反映
		Vector3 vec;
		for (int i = 0; i < 5; i++)
		{
			SpotLight[i].Diffuse = D3DXCOLOR(LR, LG, LB, 1.0f);
			SpotLight[i].Direction = Vector3(0, SpotVec[i].y / 3.0f, 1);
			SpotLight[i].SetLight(i + 1);
		}
	}
}


void SetFeildTex(int StageNo)
{
	wall[0].LoadTexture(WallTex[StageNo*3+0]);
	wall[1].LoadTexture(WallTex[StageNo*3+1]);
	wall[2].LoadTexture(WallTex[StageNo*3+2]);
	
}