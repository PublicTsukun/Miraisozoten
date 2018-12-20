#ifndef _EFFECT_VOICETENHIT_H_INCLUDE_
#define _EFFECT_VOICETENHIT_H_INCLUDE_


#include "Library/ObjectBase3D.h"


constexpr int EVH_PolygonANumber = 4;
constexpr int EVH_PolygonBNumber = 40;
constexpr int EVH_PolygonCNumber = 2;

class EffectVoicetenHit
{
	class PolygonA : public C3DPolygonObject
	{
	public:
		void Set(Vector3 pos, float rng);
		void Go(Vector3 pos, int count);
		inline int MakeVertex()
		{
			return C3DPolygonObject::MakeVertex();
		}
	};

	class PolygonB : public C3DPolygonObject
	{
		DxColor Color;
	public:
		void Draw(Vector3 wPos);

		void Set(Vector3 pos, float rng, int m);
		void Motion(int count);
		inline int MakeVertex()
		{
			return C3DPolygonObject::MakeVertex();
		}
	};

	class PolygonC : public C3DPolygonObject
	{
		DxColor Color;
	public:
		void Set(Vector3 pos, float rng);
		void Motion(int count);
		inline int MakeVertex()
		{
			return C3DPolygonObject::MakeVertex();
		}
	};

private:
	static Dx9Texture texA;
	static Dx9Texture texB;
	static Dx9Texture texC;

public:
	static void Initialize();
	static void Uninitialize();

private:
	PolygonA Note[EVH_PolygonANumber ];
	PolygonB Line[EVH_PolygonBNumber ];
	PolygonC Waka[EVH_PolygonCNumber ];
	Vector3 Position;	// �G�t�F�N�g�����ʒu
	float   Range;		// �G�t�F�N�g�����͈�
	int     Counter;	// �G�t�F�N�g��������

public:
	int Init();
	int Update();
	void Draw(bool mode = true);
	void Uninit();

	void Call(Vector3 pos, float rng);
	int  CheckState();

};

/* �e�X�g�p */
int *GetEffectVHTime();
//bool ChangeVHBlendMode(bool mode);


#endif // !_EFFECT_VOICETENHIT_H_INCLUDE_
