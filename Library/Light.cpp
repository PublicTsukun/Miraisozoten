//=============================================================================
//
// ライト処理 <Light.cpp>
//
//=============================================================================
#include "Light.h"


//----コンストラクタ--------
Dx9Light::Dx9Light()
{
	this->Type      = D3DLIGHT_DIRECTIONAL;
	this->Diffuse   = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	this->Specular  = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	this->Ambient   = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	this->Position  = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	this->Direction = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	this->Range     = 0.0f;
	this->Falloff   = 0.0f;
	this->Attenuation0 = 0.0f;
	this->Attenuation1 = 0.0f;
	this->Attenuation2 = 0.0f;
	this->Theta = 0.0f;
	this->Phi   = 0.0f;
}

//----オーバーロード--------
Dx9Light::operator D3DLIGHT9() const
{
	return this->DxState;
}

//----ライトを登録＆有効--------
void Dx9Light::SetLight(int no, bool enable)
{
	LPDIRECT3DDEVICE9 pDevice = Direct3D::GetD3DDevice();

	// ライトをレンダリングパイプラインに設定
	pDevice->SetLight(no, &this->DxState);

	// ライトの設定
	if (enable)
		pDevice->LightEnable(no, TRUE);
}

