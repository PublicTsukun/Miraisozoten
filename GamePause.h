#ifndef _GAMEPAUSE_H_INCLUDE_
#define _GAMEPAUSE_H_INCLUDE_


typedef enum GAMEPAUSERESULT
{
	BACKGAME = 0,
	BACKTITLE,
	GAMEPAUSERESULT_MAX
}GPR;


namespace GamePause
{
	void Init();
	GPR  Update();
	void Draw();
	void Uninit();
};

#endif // !_GAMEPAUSE_H_INCLUDE_
