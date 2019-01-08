//=============================================================================
//
// �����L���O���� [ranking.h]
// Author : �����ޕ�
//
//=============================================================================
#ifndef _SAVE_RANKING_H_
#define _SAVE_RANKING_H_
#include "workHagiwara.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define RANKING_CSV		_T("data/EXCEL_DATA/ranking.csv")	// �T���v���p�摜
#define RANKING_MAX			(6)								// �X�R�A�̍ő�l
#define BUFC_MAX			(1024)							// �X�R�A�̍ő�l
#define NAME_MAX			(5)								// ���O�̍ő�l

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class SAVERANKING
{
public:
	int			id;
	int			rank;
	int			score;
	int			name[NAME_MAX][2];//���O�ۑ��p[��������][0->�q���@1->�ꉹ]
};

//*****************************************************************************
// �񋓌^
//*****************************************************************************

enum
{
	RANKING_CSV_ID = 0,		// ID
	RANKING_CSV_RANK,		// ����
	RANKING_CSV_SCORE,		// �X�R�A
	RANKING_CSV_NAME,		//���O
	RANKING_CSV_MAX,
};

enum
{	// ����
	FIRST = 0,		//1��
	SECOND,			//2��
	THIRD,			//3��
	FOURTH,			//4��
	FIFTH,			//5��
	SIXTH,			//6��
};

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
SAVERANKING *GetSaveRanking(int no);
int GetSaveRankingCnt(void);
void WriteSaveRankingCsv(void);
void LoadSaveRankingCsv(void);
void DebugRank(void);
bool SaveRankingSort(int score);

#endif