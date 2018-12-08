//=============================================================================
//
// �����L���O���� [ranking.cpp]
// Author : �����ޕ�
//
//=============================================================================
#define _CRT_SECURE_NO_WARNINGS

#include "workHagiwara.h"
#include "saveranking.h"
#include <stdio.h>
#include <stdlib.h>
#include "Library/ObjectBase2D.h"
#include <windows.h>
#include "Library/DebugProcess.h"
#include "Library/Input.h"
#include "Library/Math.h"

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void SaveRankingSort();
int Compare(const void *p, const void *q);

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
//RANKING2DObject        SaveRanking2D;
SAVERANKING			rankingWk[RANKING_MAX];				// �����L���O�i�[���[�N
int				rankCnt;							// �ǂݍ��񂾃����L���O�̐�
//BUF				bufWk[BUFC_MAX];

//=============================================================================
// �����L���O����
//=============================================================================
void SaveRanking(int score,long long name_num)
{
	// ID�̍ő�l�𒊏o����
	int max = rankingWk[0].id;	// id�ő�l�i�[�p
	for (int i = 1; i < RANKING_MAX-1 ; i++)
	{
		if (max < rankingWk[i].id)max = rankingWk[i].id;
	}

	//�C���ӏ��P
	//��������̏�����6�ʂł͂Ȃ�5�ʂɍs��
	//5�ʂ��X�R�A�������ꍇ�݂̂��̊֐����Ă΂�邽��

	// �X�R�A���擾(�ꎞ�I�ɃX�R�A��6�ʂɂ���)
	rankingWk[SIXTH].score = score;//6�ʂ̃X�R�A�ɍ���̃X�R�A���Ԃ�����
	rankingWk[SIXTH].id = max + 1;//ID�͍ő�
	for (int i = NAME_MAX - 1; i > 0; i--)
	{
		rankingWk[SIXTH].name[i][1] = name_num % 10;
		name_num /= 10;
		rankingWk[SIXTH].name[i][0] = name_num % 10;
		name_num /= 10;
	}

	//�C���ӏ��Q
	//if���͕s�v
	//5�ʂ��X�R�A�������ꍇ�݂̂��̊֐����Ă΂�邽��

	// �X�R�A�����Ƃ�5�ʂ̃X�R�A�Ɣ�r���A5�ʂ̃X�R�A���Ⴏ��΃����L���O�X�V���Ȃ�
	if (rankingWk[SIXTH].score >= rankingWk[FIFTH].score)
	{	
		SaveRankingSort();
		WriteSaveRankingCsv();
	}
	// �����L���O�̕\��
	SAVERANKING *ranking = &rankingWk[0];	// �|�C���^�[��������
	PrintDebugProcess("ID�\�� : (%d)\n", ranking->id);
	PrintDebugProcess("�����N�\�� : (%d)\n", ranking->rank);
	PrintDebugProcess("�X�R�A�\�� : (%d)\n", ranking->score);
}


//=============================================================================
// �����L���O�pcsv�t�@�C���ǂݍ��ݏ���
//=============================================================================
void LoadSaveRankingCsv(void)
{
	FILE *fp;							
	char buf[BUFC_MAX];					// �ꎞ�ۑ��p(��s)
	char *tkn[RANKING_CSV_MAX];			// �ꎞ�ۑ��p(���������z��)
	SAVERANKING *ranking = &rankingWk[0];	// �|�C���^�[��������
	int skip = 1;						// �s�����w�肵�Ĕ�΂�(�ŏ���1�s)
	rankCnt = 0;						// �J�E���^������

	if ((fp = fopen(RANKING_CSV, "r")) != NULL)
	{
		// �t�@�C���̏I���܂ł���Ԃ��ǂݍ���
		while (fgets(buf, BUFC_MAX, fp) != NULL)
		{	// �J���}�ŕ���
			for (int i = 0;i < RANKING_CSV_MAX; i++)
			{
				if(i == 0)
				{
					tkn[i] = strtok(buf, ",");
				}
				else
				{
					tkn[i] = strtok(NULL, ",");
				}
			}
			// �w�肵���s�����΂�
			if (skip > 0)
			{
				skip--;
				continue;
			}
			// char��int�ɕϊ�����
			ranking->id = atoi(tkn[RANKING_CSV_ID]);//���_�̎��Ɏg��
			ranking->rank = atoi(tkn[RANKING_CSV_RANK]);//����
			ranking->score = atoi(tkn[RANKING_CSV_SCORE]);//�X�R�A

			long long name_num = atoll(tkn[RANKING_CSV_NAME]);

			for (int i = 0;i < NAME_MAX ;i++)
			{
				ranking->name[NAME_MAX - i - 1][1] = name_num % 10;
				name_num /= 10;
				ranking->name[NAME_MAX - i - 1][0] = name_num % 10;
				name_num /= 10;
			}
			rankCnt++;	//�ǂݍ��ݐ��J�E���g
			ranking++;	//���̃f�[�^��
		}
		fclose(fp);
	}
}

//=============================================================================
// �����L���O�̎擾
//=============================================================================
SAVERANKING *GetSaveRanking(int no)
{
	return &rankingWk[no];
}
//=============================================================================
// �ǂݍ��񂾐��擾�֐�
//=============================================================================
int GetSaveRankingCnt(void)
{
	return (rankCnt);
}
//=============================================================================
// �����L���O�pcsv�t�@�C���������ݏ���
//=============================================================================
void WriteSaveRankingCsv(void)
{
	FILE *fp;
	SAVERANKING*ranking = &rankingWk[0];			//�|�C���^��������

		// csv�t�@�C���㏑��
	if ((fp = fopen(RANKING_CSV, "w")) != NULL)//�������ݗp
	{
		// 1�s�ڂ��o��
		fprintf(fp, "id .rank,score ,name\n");
		// �e�f�[�^���J���}��؂�ŏo��
		for (int i = 0;i < RANKING_MAX - 1;i++, ranking++)
		{	//3�ʂ܂ł̃f�[�^����������
			fprintf(fp, "%3d,%4d,%6d,", ranking->id, ranking->rank, ranking->score);
			for (int i = 0;i < NAME_MAX;i++)
			{
				fprintf(fp, "%d%d", ranking->name[i][0], ranking->name[i][1]);
			}
			fprintf(fp, "\n");
		}
		fclose(fp);
	}
	
}
//=============================================================================
// �����L���O�X�V����(�\�[�g)
//=============================================================================
void SaveRankingSort()
{
	SAVERANKING *ranking = &rankingWk[0];					// �|�C���^�[��������
	int num = sizeof rankingWk / sizeof(SAVERANKING);		// �v�f�������߂�
	qsort(rankingWk, num, sizeof(SAVERANKING), Compare);	// �N�C�b�N�\�[�g

	// ���ʂ��X�V
	for (int i = 0; i < RANKING_MAX; i++, ranking++)
	{
		ranking->rank = i + 1;

		if (i >= 1)
		{
			if (rankingWk[i].score == rankingWk[i - 1].score)
			{
				rankingWk[i].rank = rankingWk[i - 1].rank;
			}
		}
	}
}
//============================================================================
// ��r�֐�����(�~���\�[�g)
//=============================================================================
int Compare(const void *p, const void *q)
{
	// �X�R�A�Ŕ�r
	int n = ((SAVERANKING*)q)->score - ((SAVERANKING*)p)->score;
	// �X�R�A�������������ꍇ
	if (n == 0)
	{	// id�̒l���傫���ق�����ʂɂ���
		int m = ((SAVERANKING*)q)->id - ((SAVERANKING*)p)->id;
		return m;
	}
	
	// int�^�I�[�o�[�t���[�Ώ�
	//if ((RANKING*)q > (RANKING*)p) return -1;
	//if ((RANKING*)q < (RANKING*)p) return 1;
	return n;
}
void DebugRank(void)
{
	SAVERANKING *ranking = &rankingWk[0];
	PrintDebugProcess("���O�P : (%d)(%d)\n", ranking->name[0][0], ranking->name[0][1]);
	PrintDebugProcess("���O�Q : (%d)(%d)\n", ranking->name[1][0], ranking->name[1][1]);
	PrintDebugProcess("���O�R : (%d)(%d)\n", ranking->name[2][0], ranking->name[2][1]);
	PrintDebugProcess("���O�S : (%d)(%d)\n", ranking->name[3][0], ranking->name[3][1]);
	PrintDebugProcess("���O�T : (%d)(%d)\n", ranking->name[4][0], ranking->name[4][1]);
}

