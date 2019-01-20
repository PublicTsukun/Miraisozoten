#include "StageSwitch.h"
#include "StageManager.h"
#include "Library\ObjectBase2D.h"
#include "Library/MultiRendering.h" 
#include "Library\DebugProcess.h"
#include "Library\Input.h"
#include "timer.h"

//写真テクスチャ作成用
#include "field.h"
#include "voiceten.h"
#include "enemyRE.h"


class C2DTextureMove :public C2DObject
{
public:
	void SetPosition(Vector2 pos)
	{
		Position = pos;
		SetVertex();
	}
	void MovePosition(Vector2 pos)
	{
		Position += pos;
		SetVertex();
	}
	Vector2 GetPosition(void)
	{
		return Position;
	}
	void MoveSize(Vector2 size)
	{
		Size += size;
		SetVertex();
	}
};
class SSwitchPhoto
{
public:
	C2DTextureMove HwiteFade;
	C2DTextureMove PausePhoto;
	RenderBuffer PhotoTex;


	float FadeAlpha;//白いほうのα
	float PhotoAlpha;//写真の方のα

	int FadeTimer;//フェードタイマー
	int PhotoTimer;//写真タイマー

	float Scale;
	float Ang;

	bool Photof;
};


C2DTextureMove SSwitchBg[3];
bool BgUsef;
int BgTimer;
int ChangeTime;
SSwitchPhoto Photo;

void InitStageSwitch(void)
{
	SSwitchBg[0].Init(SCREEN_CENTER_X, SCREEN_CENTER_Y, SCREEN_CENTER_X, SCREEN_CENTER_Y, "data/TEXTURE/ステージ/移行画面/背景.png");
	SSwitchBg[1].Init(SCREEN_CENTER_X, SCREEN_CENTER_Y, SCREEN_CENTER_X, SCREEN_CENTER_Y, "data/TEXTURE/ステージ/移行画面/キャラ.png");
	SSwitchBg[2].Init(631.0f, 283.0f, 300*SCREEN_SCALE, 300* SCREEN_SCALE, "data/TEXTURE/ステージ/移行画面/移行.png");
	SSwitchBg[2].SetTexture(2, 3, 1);
	BgUsef = false;
	BgTimer = 0;
	ChangeTime = 0;

	Photo.HwiteFade.Init(SCREEN_CENTER_X, SCREEN_CENTER_Y, SCREEN_CENTER_X, SCREEN_CENTER_Y);
	Photo.HwiteFade.SetVertex(0x00ffffff);
	Photo.PausePhoto.Init(SCREEN_CENTER_X, SCREEN_CENTER_Y, RS_X(0.9 / 2), RS_Y(0.9 / 2));
	Photo.PausePhoto.SetVertex(0x00ffffff);


	Photo.PhotoTex.Init(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_WIDTH, SCREEN_HEIGHT, D3DFMT_X8R8G8B8);

	Photo.FadeAlpha = 0.0f;
	Photo.PhotoAlpha = 0.0f;
	Photo.FadeTimer = 0;
	Photo.PhotoTimer = 0;
	Photo.Scale = 1.0f;
	Photo.Ang = 0.0f;
	Photo.Photof = false;
}

void UninitStageSwitch(void)
{
	SSwitchBg[0].Release();
	SSwitchBg[1].Release();
	SSwitchBg[2].Release();
	Photo.PhotoTex.Release();

}

void DrawStageSwitch(void)
{
	if (BgUsef)
	{
		SSwitchBg[0].Draw();

		SSwitchBg[2].Draw();
		SSwitchBg[1].Draw();
	}
	//写真用テクスチャ作成
	Photo.PhotoTex.BeginDraw();
	DrawField();
	DrawVoiceten();
	DrawEnemyRE();
	Photo.PhotoTex.EndDraw();
	//写真用テクスチャ作成終了
	Photo.HwiteFade.Draw();
	Photo.PausePhoto.Draw(Photo.PhotoTex.GetTexture());
}


void UpdateStageSwitch(void)
{
	if (GetKeyboardTrigger(DIK_RSHIFT))
	{
		CameraShutter(0);
	}
	else if (GetKeyboardTrigger(DIK_LSHIFT))
	{
		UseBoard(0);
	}


	if (Photo.Photof)//写真演出
	{
		Photo.PausePhoto.SetPosition(Photo.HwiteFade.GetPosition());


		Photo.FadeAlpha += 0.2f;
		Photo.HwiteFade.SetVertex(D3DXCOLOR(1.0f, 1.0f, 1.0f, Photo.FadeAlpha));


		if (Photo.FadeAlpha >= 1.0f)
		{
			Photo.PhotoAlpha += 0.03f;
			Photo.PausePhoto.SetVertex(D3DXCOLOR(1.0f, 1.0f, 1.0f, Photo.PhotoAlpha));
		}

		if (Photo.PhotoAlpha >= 1.0f)
		{
			Photo.PhotoTimer++;
			BgUsef = true;
		}

		if (Photo.PhotoTimer >= 30)
		{
			Photo.Scale -= 0.04f;

			if (Photo.Scale <= 0.5f)
			{
				Photo.Scale = 0.5f;
			}
			Photo.HwiteFade.SetStatus(Photo.Scale, Photo.Ang);
			Photo.PausePhoto.SetStatus(Photo.Scale, Photo.Ang);
		}

		if (Photo.PhotoTimer >= 90)
		{
			Photo.HwiteFade.MovePosition(Vector2(50.0f, -50.0f));
			Photo.HwiteFade.SetStatus(Photo.Scale, Photo.Ang);
			Photo.PausePhoto.SetStatus(Photo.Scale, Photo.Ang);

		}


	}

	if (BgUsef)
	{
		BgTimer++;
	}
	if (BgTimer >= ChangeTime)
	{
		SSwitchBg[0].MovePosition(Vector2(0, -100));
		SSwitchBg[1].MovePosition(Vector2(0, -100));
		SSwitchBg[2].MovePosition(Vector2(0, -100));

		if (SSwitchBg[0].GetPosition().y < -SCREEN_HEIGHT)
		{
			BgUsef = false;
		}
	}
}


void CameraShutter(int stagenum)
{
	SSwitchBg[0].SetPosition(Vector2(SCREEN_CENTER_X, SCREEN_CENTER_Y));
	SSwitchBg[1].SetPosition(Vector2(500.0f*SCREEN_SCALE, SCREEN_CENTER_Y));
	SSwitchBg[2].SetPosition(Vector2(491.0f*SCREEN_SCALE, 283.0f*SCREEN_SCALE));
	SSwitchBg[2].SetTexture(stagenum, 3, 1);
	BgTimer = 0;
	BgUsef = false;
	ChangeTime = 150;


	Photo.HwiteFade.SetPosition(Vector2(SCREEN_CENTER_X, SCREEN_CENTER_Y));
	Photo.HwiteFade.SetVertex(0x00ffffff);
	Photo.PausePhoto.SetPosition(Vector2(SCREEN_CENTER_X, SCREEN_CENTER_Y));
	Photo.PausePhoto.SetVertex(0x00ffffff);

	Photo.FadeAlpha = 0.0f;
	Photo.PhotoAlpha = 0.0f;
	Photo.FadeTimer = 0;
	Photo.PhotoTimer = 0;
	Photo.Scale = 1.0f;
	Photo.Ang = 0.0f;
	Photo.Photof = true;
	Photo.HwiteFade.SetStatus(Photo.Scale, Photo.Ang);
	Photo.PausePhoto.SetStatus(Photo.Scale, Photo.Ang);
	TimerSet(STOP);
}

void UseBoard(int stagenum)
{
	SSwitchBg[0].SetPosition(Vector2(SCREEN_CENTER_X, SCREEN_CENTER_Y));
	SSwitchBg[1].SetPosition(Vector2(500.0f*SCREEN_SCALE, SCREEN_CENTER_Y));
	SSwitchBg[2].SetPosition(Vector2(491.0f*SCREEN_SCALE, 283.0f*SCREEN_SCALE));
	SSwitchBg[2].SetTexture(stagenum, 3, 1);
	BgTimer = 0;
	BgUsef = true;
	ChangeTime = 60;
}