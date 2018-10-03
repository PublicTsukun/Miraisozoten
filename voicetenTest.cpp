//=============================================================================
//
// voicetenèàóù [voicetenTest.cpp]
// Author : ëvïFË¡
//
//=============================================================================
#include "voicetenTest.h"
#include "voiceten.h"
#include "Library\Input.h"

#include "Library/ObjectBase3D.h"

//=============================================================================
// voiceten Launcher
//=============================================================================
void TestVL(void)
{
	if (GetKeyboardTrigger(DIK_J))
	{
		SetVoiceten(
			Vector3(400.0f, 300.0f, 400.0f),
			Vector3(000.0f, 300.0f, 400.0f));
	}
}