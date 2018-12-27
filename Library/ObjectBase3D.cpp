#include "ObjectBase3D.h"
#include "Direct3D.h"
#include "Matrix.h"
#include "Camera.h"
#include <math.h>


/* 最基底クラス */
_ObjectBase3D::_ObjectBase3D()
{
	this->Texture = NULL;
	this->VtxBuff = NULL;
}

void _ObjectBase3D::LoadTexture(const char *texture)
{
	this->Texture.LoadTexture(texture);
}
void _ObjectBase3D::LoadTexture(LPDx3DTex9 texture)
{
	Texture = texture;
}
void _ObjectBase3D::Release()
{
	this->Texture.Release();
	if (VtxBuff != NULL)
	{	// 頂点の開放
		VtxBuff->Release();
		VtxBuff = NULL;
	}
}
void _ObjectBase3D::ReleaseVertex()
{
	if (VtxBuff != NULL)
	{	// 頂点の開放
		VtxBuff->Release();
		VtxBuff = NULL;
	}
}


/* 3D板ポリ */
//----コンストラクタ--------
C3DPolygonObject::C3DPolygonObject()
{
	Texture = NULL;		// テクスチャへのポインタ
	VtxBuff = NULL;		// 頂点バッファインターフェースへのポインタ

	Position = Vector3(0.0f, 0.0f, 0.0f);	// 位置座標
	Rotation = Vector3(0.0f, 0.0f, 0.0f);	// 回転角度
	Size = Vector2(0.0f, 0.0f);				// ポリゴンサイズ
	Scale = 1.0f;								// サイズ倍率

	TexPattern_X = 1;		// テクスチャパターン（横）
	TexPattern_Y = 1;		// テクスチャパターン（縦）
	AnimeCount = 0;			// アニメーションカウント
	AnimePattern = 0;		// 現在のアニメーションパターン番号
	ChangeAnimeTime = 0;	// アニメーション切り替え待時間
}

//----初期化--------
void C3DPolygonObject::Init(float posX, float posY, float posZ, float sizX, float sizY)
{
	this->Position = Vector3(posX, posY, posZ);
	this->Size = Vector2(sizX, sizY);
	this->MakeVertex();
}
void C3DPolygonObject::Init(Vector3 pos, Vector2 size)
{
	this->Position = pos;
	this->Size = size;
	this->MakeVertex();
}
void C3DPolygonObject::Init(Vector3 pos, Vector3 rot, Vector2 size)
{
	this->Position = pos;
	this->Rotation = rot;
	this->Size = size;
	this->MakeVertex();
}

//----描画処理--------
void C3DPolygonObject::Draw(UINT state, const char* order)
{
	LPDIRECT3DDEVICE9 pDevice = Direct3D::GetD3DDevice();
	D3DXMATRIX mtxRot, mtxTranslate, mtxWorld;

	// αテストを有効に
	if (!(state & DRAWSTATE_OFFALPHATEST))
	{
		pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);		// ON
		pDevice->SetRenderState(D3DRS_ALPHAREF, 128);				// 比較するαの値
		pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);	// 条件(GREATER : 大なり)
	}

	// ラインティング切り替え
	DWORD light;
	pDevice->GetRenderState(D3DRS_LIGHTING, &light);
	if ((state & DRAWSTATE_BILLBOARD) ||
		(state & DRAWSTATE_OFFLIGHTING))
	{
		pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
	}

	// ワールドマトリックスの初期化
	D3DXMatrixIdentity(&mtxWorld);

	// マトリックスの生成
	if ((state & DRAWSTATE_BILLBOARD))
	{
		// ビューマトリックスを取得
		D3DXMATRIX mtxView = GetMtxView();

		/* ポリゴンを正面に向ける (逆行列を作る 圧倒的に速い/拡張性に欠ける) */
		mtxWorld._11 = mtxView._11;
		mtxWorld._12 = mtxView._21;
		mtxWorld._13 = mtxView._31;
		mtxWorld._21 = mtxView._12;
		mtxWorld._22 = mtxView._22;
		mtxWorld._23 = mtxView._32;
		mtxWorld._31 = mtxView._13;
		mtxWorld._32 = mtxView._23;
		mtxWorld._33 = mtxView._33;
		CreateMatrix(&mtxWorld, Scale, Vector3(), Position, order);
	}
	else
	{
		CreateMatrix(&mtxWorld, Scale, Rotation, Position, order);
	}

	// ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &mtxWorld);

	// 頂点バッファをデバイスのデータストリームにバインド
	pDevice->SetStreamSource(0, VtxBuff, 0, sizeof(VERTEX_3D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_3D);

	// テクスチャの設定
	pDevice->SetTexture(0, Texture);

	// ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, RECT_NUM_POLYGON);

	// ラインティング復元
	pDevice->SetRenderState(D3DRS_LIGHTING, light);

	// αテストを無効に
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);

}

//----頂点作成--------
int C3DPolygonObject::MakeVertex(void)
{
	// オブジェクトの頂点バッファを生成
	if (FAILED(Direct3D::GetD3DDevice()->CreateVertexBuffer(sizeof(VERTEX_3D) * RECT_NUM_VERTEX,	// 頂点データ用に確保するバッファサイズ(バイト単位)
		D3DUSAGE_WRITEONLY,		// 頂点バッファの使用法　
		FVF_VERTEX_3D,			// 使用する頂点フォーマット
		D3DPOOL_MANAGED,		// リソースのバッファを保持するメモリクラスを指定
		&VtxBuff,				// 頂点バッファインターフェースへのポインタ
		NULL)))					// NULLに設定
	{
		return 1;
	}

	{//頂点バッファの中身を埋める
		VERTEX_3D *pVtx;

		// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
		VtxBuff->Lock(0, 0, (void**)&pVtx, 0);

		// 頂点座標の設定
		pVtx[0].coord = Vector3(-Size.x,  Size.y, 0.0f);
		pVtx[1].coord = Vector3( Size.x,  Size.y, 0.0f);
		pVtx[2].coord = Vector3(-Size.x, -Size.y, 0.0f);
		pVtx[3].coord = Vector3( Size.x, -Size.y, 0.0f);

		// 法線の設定
		pVtx[0].normal = Vector3(0.0f, 0.0f, -1.0f);
		pVtx[1].normal = Vector3(0.0f, 0.0f, -1.0f);
		pVtx[2].normal = Vector3(0.0f, 0.0f, -1.0f);
		pVtx[3].normal = Vector3(0.0f, 0.0f, -1.0f);

		// 反射光の設定
		pVtx[0].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		// テクスチャ座標の設定
		pVtx[0].uv = Vector2(0.0f, 0.0f);
		pVtx[1].uv = Vector2(1.0f, 0.0f);
		pVtx[2].uv = Vector2(0.0f, 1.0f);
		pVtx[3].uv = Vector2(1.0f, 1.0f);

		// 頂点データをアンロックする
		VtxBuff->Unlock();
	}

	return 0;
}

//----頂点座標設定--------
void C3DPolygonObject::SetVertex(void)
{
	{//頂点バッファの中身を埋める
		VERTEX_3D *pVtx;

		// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
		VtxBuff->Lock(0, 0, (void**)&pVtx, 0);

		// 頂点座標の設定
		pVtx[0].coord = Vector3(-Size.x, Size.y, 0.0f);
		pVtx[1].coord = Vector3(Size.x, Size.y, 0.0f);
		pVtx[2].coord = Vector3(-Size.x, -Size.y, 0.0f);
		pVtx[3].coord = Vector3(Size.x, -Size.y, 0.0f);

		// 頂点データをアンロックする
		VtxBuff->Unlock();
	}
}
void C3DPolygonObject::SetVertex(D3DXCOLOR color)
{
	{//頂点バッファの中身を埋める
		VERTEX_3D *pVtx;

		// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
		VtxBuff->Lock(0, 0, (void**)&pVtx, 0);

		// 頂点座標の設定
		pVtx[0].coord = Vector3(-Size.x, Size.y, 0.0f);
		pVtx[1].coord = Vector3(Size.x, Size.y, 0.0f);
		pVtx[2].coord = Vector3(-Size.x, -Size.y, 0.0f);
		pVtx[3].coord = Vector3(Size.x, -Size.y, 0.0f);

		// 反射光の設定
		pVtx[0].diffuse = color;
		pVtx[1].diffuse = color;
		pVtx[2].diffuse = color;
		pVtx[3].diffuse = color;

		// 頂点データをアンロックする
		VtxBuff->Unlock();
	}
}

void C3DPolygonObject::SetTexture(int num, int ix, int iy)
{
	{//頂点バッファの中身を埋める
		VERTEX_3D *pVtx;

		// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
		VtxBuff->Lock(0, 0, (void**)&pVtx, 0);

		int x = num % ix;
		int y = num / ix;
		float sizeX = 1.0f / ix;
		float sizeY = 1.0f / iy;
		pVtx[0].uv = Vector2((float)(x)* sizeX, (float)(y)* sizeY);
		pVtx[1].uv = Vector2((float)(x)* sizeX + sizeX, (float)(y)* sizeY);
		pVtx[2].uv = Vector2((float)(x)* sizeX, (float)(y)* sizeY + sizeY);
		pVtx[3].uv = Vector2((float)(x)* sizeX + sizeX, (float)(y)* sizeY + sizeY);
		// 頂点データをアンロックする
		VtxBuff->Unlock();
	}
}


//----テクスチャ情報書き込み--------
void C3DPolygonObject::LoadTextureStatus(float sizX, float sizY, float scale, int ptnX, int ptnY, int time)
{
	Size = Vector2(sizX, sizY);
	Scale = scale;
	TexPattern_X = ptnX;
	TexPattern_Y = ptnY;
	ChangeAnimeTime = time;
}
void C3DPolygonObject::LoadTextureStatus(float sizX, float sizY, float scale)
{
	Size = Vector2(sizX, sizY);
	Scale = scale;
	TexPattern_X = 1;
	TexPattern_Y = 1;
	ChangeAnimeTime = 1;
}

//----オブジェクト情報--------
void C3DPolygonObject::LoadObjectStatus(Vector3 pos)
{
	this->Position = pos;
}
void C3DPolygonObject::LoadObjectStatus(Vector3 pos, Vector3 rot)
{
	this->Position = pos;
	this->Rotation = rot;
}


/* 3D立方体 */
//----コンストラクタ--------
C3DCubeObject::C3DCubeObject()
{
	this->Texture = NULL;
	this->Position = Vector3(0.0f, 0.0f, 0.0f);
	this->Rotation = Vector3(0.0f, 0.0f, 0.0f);
	this->Size = Vector3(0.0f, 0.0f, 0.0f);
}
void C3DCubeObject::LoadTexture(const char *texture)
{
	this->Texture.LoadTexture(texture);
}
void C3DCubeObject::Release()
{
	this->Texture.Release();
}

//----初期化------
int  C3DCubeObject::Init(Vector3 pos, Vector3 rot, Vector3 size)
{
	this->Position = Vector3( pos.x,  pos.y,  pos.z);
	this->Rotation = Vector3( rot.x,  rot.y,  rot.z);
	this->Size     = Vector3(size.x, size.y, size.z);
	return this->MakeVertex();
}
int  C3DCubeObject::Init(Vector3 pos, Vector3 size)
{
	this->Position = Vector3( pos.x,  pos.y,  pos.z);
	this->Size     = Vector3(size.x, size.y, size.z);
	return this->MakeVertex();
}
int  C3DCubeObject::Init(Vector3 pos, Vector3 rot, float size)
{
	this->Position = Vector3(pos.x, pos.y, pos.z);
	this->Rotation = Vector3(rot.x, rot.y, rot.z);
	this->Size     = Vector3( size,  size,  size);
	return this->MakeVertex();
}
int  C3DCubeObject::Init(Vector3 pos, float size)
{
	this->Position = Vector3(pos.x, pos.y, pos.z);
	this->Size     = Vector3( size,  size,  size);
	return this->MakeVertex();
}

//----頂点作成--------
int  C3DCubeObject::MakeVertex()
{
	Face[0][0].coord    = Vector3(-1.0f,  1.0f, -1.0f);//-Z
	Face[0][1].coord    = Vector3( 1.0f,  1.0f, -1.0f);
	Face[0][2].coord    = Vector3(-1.0f, -1.0f, -1.0f);
	Face[0][3].coord    = Vector3( 1.0f, -1.0f, -1.0f);
	Face[0][0].normal = Vector3( 0.0f,  0.0f, -1.0f);
	Face[0][1].normal = Vector3( 0.0f,  0.0f, -1.0f);
	Face[0][2].normal = Vector3( 0.0f,  0.0f, -1.0f);
	Face[0][3].normal = Vector3( 0.0f,  0.0f, -1.0f);

	Face[1][0].coord    = Vector3( 1.0f,  1.0f, -1.0f);//X
	Face[1][1].coord    = Vector3( 1.0f,  1.0f,  1.0f);
	Face[1][2].coord    = Vector3( 1.0f, -1.0f, -1.0f);
	Face[1][3].coord    = Vector3( 1.0f, -1.0f,  1.0f);
	Face[1][0].normal = Vector3( 1.0f,  0.0f,  0.0f);
	Face[1][1].normal = Vector3( 1.0f,  0.0f,  0.0f);
	Face[1][2].normal = Vector3( 1.0f,  0.0f,  0.0f);
	Face[1][3].normal = Vector3( 1.0f,  0.0f,  0.0f);

	Face[2][0].coord    = Vector3( 1.0f,  1.0f,  1.0f);//Z
	Face[2][1].coord    = Vector3(-1.0f,  1.0f,  1.0f);
	Face[2][2].coord    = Vector3( 1.0f, -1.0f,  1.0f);
	Face[2][3].coord    = Vector3(-1.0f, -1.0f,  1.0f);
	Face[2][0].normal = Vector3( 0.0f,  0.0f,  1.0f);
	Face[2][1].normal = Vector3( 0.0f,  0.0f,  1.0f);
	Face[2][2].normal = Vector3( 0.0f,  0.0f,  1.0f);
	Face[2][3].normal = Vector3( 0.0f,  0.0f,  1.0f);

	Face[3][0].coord    = Vector3(-1.0f,  1.0f,  1.0f);//-X
	Face[3][1].coord    = Vector3(-1.0f,  1.0f, -1.0f);
	Face[3][2].coord    = Vector3(-1.0f, -1.0f,  1.0f);
	Face[3][3].coord    = Vector3(-1.0f, -1.0f, -1.0f);
	Face[3][0].normal = Vector3(-1.0f,  0.0f,  0.0f);
	Face[3][1].normal = Vector3(-1.0f,  0.0f,  0.0f);
	Face[3][2].normal = Vector3(-1.0f,  0.0f,  0.0f);
	Face[3][3].normal = Vector3(-1.0f,  0.0f,  0.0f);

	Face[4][0].coord    = Vector3(-1.0f,  1.0f,  1.0f);//Y
	Face[4][1].coord    = Vector3( 1.0f,  1.0f,  1.0f);
	Face[4][2].coord    = Vector3(-1.0f,  1.0f, -1.0f);
	Face[4][3].coord    = Vector3( 1.0f,  1.0f, -1.0f);
	Face[4][0].normal = Vector3( 0.0f,  1.0f,  0.0f);
	Face[4][1].normal = Vector3( 0.0f,  1.0f,  0.0f);
	Face[4][2].normal = Vector3( 0.0f,  1.0f,  0.0f);
	Face[4][3].normal = Vector3( 0.0f,  1.0f,  0.0f);

	Face[5][0].coord    = Vector3(-1.0f, -1.0f, -1.0f);//-Y
	Face[5][1].coord    = Vector3( 1.0f, -1.0f, -1.0f);
	Face[5][2].coord    = Vector3(-1.0f, -1.0f,  1.0f);
	Face[5][3].coord    = Vector3( 1.0f, -1.0f,  1.0f);
	Face[5][0].normal = Vector3( 0.0f, -1.0f,  0.0f);
	Face[5][1].normal = Vector3( 0.0f, -1.0f,  0.0f);
	Face[5][2].normal = Vector3( 0.0f, -1.0f,  0.0f);
	Face[5][3].normal = Vector3( 0.0f, -1.0f,  0.0f);

	for (int iCnt = 0; iCnt < 6; iCnt++)
	{
		Face[iCnt][0].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		Face[iCnt][1].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		Face[iCnt][2].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		Face[iCnt][3].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		Face[iCnt][0].uv = Vector2(0.1f, 0.1f);
		Face[iCnt][1].uv = Vector2(0.9f, 0.1f);
		Face[iCnt][2].uv = Vector2(0.1f, 0.9f);
		Face[iCnt][3].uv = Vector2(0.9f, 0.9f);
	}

	return 0;
}

//----描画処理--------
void C3DCubeObject::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice = Direct3D::GetD3DDevice();
	D3DXMATRIX mtxScl, mtxRot, mtxTranslate, mtxWorld;

	// αテスト設定
	//if (AlphaTestSwitch(0))
	{
		// αテストを有効に
		pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);		// ON
		pDevice->SetRenderState(D3DRS_ALPHAREF, 125/*ALPHA_TEST_VALUE*/);	// 比較するαの値
		pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);	// 条件 (D3DCMP_GREATER)
	}

	// ラインティングを無効にする (ライトを当てると変になる)
	//pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	// ワールドマトリックスの初期化
	D3DXMatrixIdentity(&mtxWorld);

	// サイズを反映
	D3DXMatrixScaling(&mtxScl, Size.x, Size.y, Size.z);
	D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxScl);

	// 回転を反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, Rotation.y, Rotation.x, Rotation.z);
	D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxRot);

	// 移動を反映
	D3DXMatrixTranslation(&mtxTranslate, Position.x, Position.y, Position.z);
	D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxTranslate);

	// ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &mtxWorld);

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_3D);

	// テクスチャの設定
	pDevice->SetTexture(0, Texture);

	// ポリゴンの描画
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, RECT_NUM_POLYGON, Face[0], sizeof(VERTEX_3D));
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, RECT_NUM_POLYGON, Face[1], sizeof(VERTEX_3D));
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, RECT_NUM_POLYGON, Face[2], sizeof(VERTEX_3D));
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, RECT_NUM_POLYGON, Face[3], sizeof(VERTEX_3D));
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, RECT_NUM_POLYGON, Face[4], sizeof(VERTEX_3D));
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, RECT_NUM_POLYGON, Face[5], sizeof(VERTEX_3D));

	// ラインティングを有効に戻す
	//pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);

	// αテストを無効に
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);

}


/* モデル読み込みテスト *///*
C3DXModel::C3DXModel()
{
	// 情報の初期化
	Position = Vector3();
	Rotation = Vector3();
	Scale = 1.0f;

	// モデル関係の初期化
	Texture = NULL;
	Mesh = NULL;
	BuffMat = NULL;
	NumMat = 0;
}

int C3DXModel::Init(const char *filePath)
{
	// 情報の初期化
	Position = Vector3();
	Rotation = Vector3();
	Scale    = 1.0f;

	// モデル関係の初期化
	Texture = NULL;
	Mesh    = NULL;
	BuffMat = NULL;
	NumMat  = 0;

	// xファイルの読み込み
	if (FAILED(D3DXLoadMeshFromX(filePath,
		D3DXMESH_SYSTEMMEM,
		Direct3D::GetD3DDevice(),
		NULL,
		&BuffMat,
		NULL,
		&NumMat,
		&Mesh)))
	{
		return 1;
	}
	return 0;
}

void C3DXModel::Draw()
{
	LPDIRECT3DDEVICE9 pDevice = Direct3D::GetD3DDevice();
	D3DXMATERIAL *pD3DXMat;
	D3DMATERIAL9 matDef;

	/* モデルの描画 */
	// 現在のマテリアルを取得
	pDevice->GetMaterial(&matDef);

	// マテリアル情報に対するポインタを取得
	pD3DXMat = (D3DXMATERIAL*)BuffMat->GetBufferPointer();

	for (int i = 0; i < (int)NumMat; i++)
	{
		// マテリアル設定
		pDevice->SetMaterial(&pD3DXMat[i].MatD3D);

		// テクスチャの設定
		pDevice->SetTexture(0, Texture);

		// 描画
		Mesh->DrawSubset(i);
	}

	pDevice->SetMaterial(&matDef);	// マテリアルを元に戻す
}

void C3DXModel::Uninit()
{
	if (Texture != NULL)
	{// テクスチャの開放
		Texture->Release();
		Texture = NULL;
	}

	// 3Dプレイヤーの解放
	if (Mesh != NULL)
	{// メッシュの開放
		Mesh->Release();
		Mesh = NULL;
	}

	if (BuffMat != NULL)
	{// マテリアルの開放
		BuffMat->Release();
		BuffMat = NULL;
	}
}

