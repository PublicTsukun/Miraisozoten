#include "StageSwitch.h"
#include "StageManager.h"
#include "Library\ObjectBase2D.h"
#include "Library/MultiRendering.h" 


//写真テクスチャ作成用
#include "enemy.h"
#include "field.h"
#include "voiceten.h"


class C2DTextureMove :public C2DObject
{
public:
	void SetPosition(Vector2 pos)
	{
		Position = pos;
	}
	void MovePosition(Vector2 pos)
	{
		Position += pos;
	}
	Vector2 GetPosition(void)
	{
		return Position;
	}
};
class SSwitchPhoto
{
public:
	C2DTextureMove HwiteFade;
	C2DTextureMove PausePhoto;
	RenderBuffer PhotoTex;


	float FadeAlpha;
	float PhotoAlpha;

	int FadeTimer;
	int PhotoTimer;
};


C2DObject SSwitchBg;
SSwitchPhoto Photo;

void InitStageSwitch(void)
{
	SSwitchBg.Init(SCREEN_CENTER_X, SCREEN_CENTER_Y, SCREEN_CENTER_X, SCREEN_CENTER_Y, "data/TEXTURE/UI/ステージ移行背景.png");

	Photo.HwiteFade.Init(SCREEN_CENTER_X, SCREEN_CENTER_Y, SCREEN_CENTER_X, SCREEN_CENTER_Y);
	Photo.HwiteFade.SetVertex(0x00ffffff);
	Photo.PausePhoto.Init(SCREEN_CENTER_X, SCREEN_CENTER_Y, RS_X(0.8 / 2), RS_Y(0.8 / 2));
	Photo.PausePhoto.SetVertex(0x00ffffff);
	Photo.PhotoTex.Init(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_WIDTH, SCREEN_HEIGHT, D3DFMT_X8R8G8B8);

}

void UninitStageSwitch(void)
{
	SSwitchBg.Release();
	Photo.PhotoTex.Release();
}

void DrawStageSwitch(void)
{
	SSwitchBg.Draw();

	//写真用テクスチャ作成
	Photo.PhotoTex.BeginDraw();
	DrawENEMY();
	DrawField();
	DrawVoiceten();
	Photo.PhotoTex.EndDraw();
	//写真用テクスチャ作成終了
	Photo.HwiteFade.Draw();
	Photo.PausePhoto.Draw(Photo.PhotoTex.GetTexture());
}

void UpdateStageSwitch(void)
{
	Photo.PausePhoto.SetPosition(Photo.HwiteFade.GetPosition());

	Photo.FadeAlpha += 0.2f;
	Photo.HwiteFade.SetVertex(D3DXCOLOR(1.0f, 1.0f, 1.0f, Photo.FadeAlpha));

	if (Photo.FadeAlpha >= 1.0f)
	{
		Photo.PhotoAlpha += 0.1f;
		Photo.PausePhoto.SetVertex(D3DXCOLOR(1.0f, 1.0f, 1.0f, Photo.PhotoAlpha));
	}
}