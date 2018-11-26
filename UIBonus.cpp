//=============================================================================
//
// フィールド処理 [field.cpp]
//
//=============================================================================
#include "UIBonus.h"
#include "Library/ObjectBase2D.h"
#include "Library/Common.h"
#include "Library\Input.h"
#include "Library\DebugProcess.h"
#include "Library\Color.h"
#include "timer.h"
#include "GameSound.h"

//*****************************************************************************
// グローバル変数
//*****************************************************************************
UI2DPercentGauge	BonusGage;	//ボーナスゲージ
C2DObject			Voiceten[3];
C2DObject			GageEff;

int		gagenum = 0;
float	gageper = 0.0f;
int		gagelong = 0;
bool fiverf = false;


const Vector2 FirstPos = Vector2(169.0f*SCREEN_SCALE, BONUSGAGE_POS_Y+10.0f*SCREEN_SCALE);
const Vector2 SecondPos = Vector2(295.0f*SCREEN_SCALE, BONUSGAGE_POS_Y);
const Vector2 ThirdPos = Vector2(420.0f*SCREEN_SCALE, BONUSGAGE_POS_Y-10.0f*SCREEN_SCALE);

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitUIBonus(void)
{
	BonusGage.Init(TEX_BONUSGAGEFRAME, TEX_BONUSGAGE);
	BonusGage.Init(BONUSGAGE_POS_X, BONUSGAGE_POS_Y, BONUSGAGE_SIZE_X, BONUSGAGE_SIZE_Y);



	Vector2 pos;
	pos = FirstPos;
	Voiceten[0].Init(pos.x, pos.y, 40 * SCREEN_SCALE, 40 * SCREEN_SCALE, TEX_GAGEVOICETEN);
	pos = SecondPos;
	Voiceten[1].Init(pos.x, pos.y, 40 * SCREEN_SCALE, 40 * SCREEN_SCALE, TEX_GAGEVOICETEN);
	pos = ThirdPos;
	Voiceten[2].Init(pos.x, pos.y, 40 * SCREEN_SCALE, 40 * SCREEN_SCALE, TEX_GAGEVOICETEN);

	GageEff.Init(GAGE_EFF_POS_X, GAGE_EFF_POS_Y, GAGE_EFF_SIZE_X, GAGE_EFF_SIZE_Y, TEX_GAGEEFF);

	gagenum = 0;
	gageper = 0.0f;
	gagelong = 0;
	fiverf = false;

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitUIBonus(void)
{
	BonusGage.Uninit();

	for (int i = 0; i < 3; i++)
	{
		Voiceten[i].Release();
	}

	GageEff.Release();
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawUIBonus(void)
{
	GageEff.Draw();

	BonusGage.Draw();

	for (int i = 0; i < 3; i++)
	{
		Voiceten[i].Draw();
	}
}

float effa=0.0f;
//=============================================================================
// 更新処理
//=============================================================================
void UpdateUIBonus(void)
{
	if (StateTimer() == COUNT)
	{

		if (GetKeyboardPress(DIK_9) && fiverf == false)
		{
			AddGage(50);//９が押されているときはゲージを伸ばす
		}
		//else
		{
			AddGage(-1);//ゲージを縮める

			if (fiverf == true)
			{
				AddGage(-1);//フィーバー状態ならもっと減らす
			}
		}

		if (GetKeyboardTrigger(DIK_8) && gagenum == 3)
		{
			fiverf = true;
		}
	}
		PrintDebugProcess("フラグ%d", gagenum);


		if (GetKeyboardTrigger(DIK_0))//0が押されたら
		{
			gagenum--;//フラグをひとつ前に
		}

		BonusGage.Update(gageper);//ゲージの更新

		for (int i = 0; i < 3; i++)//ボイステンの更新処理
		{
			Voiceten[i].SetVertex(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f));//基本はαを0.2に

			if (i <= gagenum - 1 || fiverf == true)//もしゲージがたまっていたら
			{
				Voiceten[i].SetVertex(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));//貯まったところまでボイステンを光らせる
			}
			Voiceten[i].SetTexture(i, 3, 1);

		}

	
		float cor;

		cor = (BONUSGAGE_SIZE_Y * 2) / (tanf(POS_COR_ANG));//調整値の産出

		Vector3 pos;
		Vector3 poseff;

		pos.x = BONUSGAGE_POS_X + ((BONUSGAGE_SIZE_X) * 2 * gageper) + cor;//X座標は調整
		pos.y = BONUSGAGE_POS_Y - (BONUSGAGE_SIZE_Y);//Yはそのまま
		pos.z = 0.0f;
		BonusGage.Gage.SetVertex(1, pos);//頂点1の調整
		poseff.x = GAGE_EFF_POS_X + ((GAGE_EFF_SIZE_X)) + cor*1.6f;
		poseff.y = BONUSGAGE_POS_Y - (GAGE_EFF_SIZE_Y);//Yはそのまま
		poseff.z = 0.0f;
		GageEff.SetVertex(1, poseff);//頂点1の調整

		pos.x = BONUSGAGE_POS_X + cor;//Xを再調整
		BonusGage.Gage.SetVertex(0, pos);//頂点0を調整
		poseff.x = GAGE_EFF_POS_X - ((GAGE_EFF_SIZE_X)) + cor*1.6f;
		poseff.z = 0.0f;
		GageEff.SetVertex(0, poseff);//頂点1の調整

		pos.x = BONUSGAGE_POS_X + ((BONUSGAGE_SIZE_X) * 2) + cor;//X座標は調整
		pos.y = BONUSGAGE_POS_Y - (BONUSGAGE_SIZE_Y);//Yはそのまま
		BonusGage.Frame.SetVertex(1, pos);//頂点1の調整

		pos.x = BONUSGAGE_POS_X + cor;//Xを再調整
		BonusGage.Frame.SetVertex(0, pos);//頂点0を調整


		if (gagenum == 3 || fiverf == true)
		{
			effa += 0.06f;
			GageEff.SetVertex(D3DXCOLOR(1.0f, 0.0f, 1.0f, fabs(sinf(effa)) + 0.2f));
		}
		else
		{
			GageEff.SetVertex(D3DXCOLOR(1.0f, 0.0f, 1.0f, 0.0f));
		}
		BonusGage.Gage.SetTexture(1, gageper, 0.0f);//テクスチャ座標を割合に応じて設定
		BonusGage.Gage.SetTexture(3, gageper, 1.0f);
	}



//=============================================================================
//ゲージ加算関数
//=============================================================================
void AddGage(int no)
{

	if (no < 0)//noがマイナスの場合
	{
		if (fiverf == false)//フィーバー状態でなければ
		{
			PrintDebugProcess("%f ", VALUE_MAX * 3 * 0.33f);
			if ((float)(gagelong + no) > (float)(VALUE_MAX*gagenum*0.333)
				&&gagenum!=0 && gagenum!=3)//一定ポイントを上回っていれば
			{
				gagelong += no;//加算
			}
			else if (gagenum == 0)
			{
				gagelong += no;
			}
		}
		else
		{
			gagelong += no;//フィーバー状態なら問答無用で加算

		}
	}
	else
	{
		if (fiverf == false)//フィーバー状態でなければ
		{
			if ((int)(((gagelong + no)/(float)VALUE_MAX) / 0.333f) > (int)(((gagelong) / (float)VALUE_MAX) / 0.333f))
			{
				gagenum++;
				if (gagenum < 3)
				{
					PlaySE(GAGE_1ST2ND);
				}
				else if (gagenum >= 3)
				{
					PlaySE(GAGE_LAST);
				}
			}

			gagelong += no;//プラスでも問答無用で加算
		}
	}
	gageper = gagelong / (float)VALUE_MAX;//最大と現在の長さから割合の算出

	if (gageper >= LAST_GAGE)//100%以上なら
	{
		gageper = LAST_GAGE;//100%に調整して
		gagelong = VALUE_MAX;
		gagenum = 3;
		//fiverf = true;//フィーバー状態に移行
	}
	else if (gageper <= 0.0f)//0%以下なら
	{
		gageper = 0.0f;//0%に調整して
		gagelong = 0;
		fiverf = false;//フィーバー状態終了
		gagenum = 0;
	}
	PrintDebugProcess("フィーバー状態　[%d]\n", fiverf);
	PrintDebugProcess("gageper [%d]\n", gagelong);
}

//=============================================================================
//フィーバー状態取得関数
//=============================================================================
bool GetFiver(void)
{
	return fiverf;
}

//=============================================================================
// 取得関数
//=============================================================================
int GetGauge(void)
{
	return gagenum;
}