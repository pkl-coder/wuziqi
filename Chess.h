#pragma once
#include<graphics.h>
#include<vector>
#include"tools.h"
using namespace std;
//��ʾ����λ��
struct ChessPos {
	int row;
	int col;

	ChessPos(int r=0,int c=0):row(r),col(c){ }
};

typedef enum {
	CHESS_WHITE = -1,
	CHESS_BLACK = 1
}chess_kind_t;

class Chess
{
public:
	//���̵ĳ�ʼ��
	void init();
	//�ж�ָ�������Ƿ���Ч�����浽pos;
	bool clickBoard(int x, int y, ChessPos* pos);

	void chessDown(ChessPos *pos, chess_kind_t kind);

	int getGradeSize();//��ȡ���̵Ĵ�С

	//��ȡָ��λ���Ǻ��壬���ǰ��壬���ǿհ�
	int getChessData(ChessPos* pos);
	int getChessData(int row, int col);
	bool checkOver();//��������Ƿ����

	Chess(int gradeSize, int marginX, int marginY, float ChessSize);
private:
	IMAGE chessWhiteImg;
	IMAGE chessBlackImg;
	
	int gradeSize;//���̵Ĵ�С(13,15,17,19)
	int margin_x;//��߾ࣻ
	int margin_y;//�ϱ߾�;
	float chessSize;//���Ӵ�С��

	//�洢��ǰ��ֵ����ӷֲ����� 0���հף�1�����ӣ�-1������
	vector<vector<int> > chessMap;//

	//��ʾ���ڸ�˭����
	bool playerFlag;//true:�ú����ߣ�

	void updateGameMap(ChessPos* pos);

	bool checkWin();//�����Ӯ

	ChessPos lastPos;//������ӵ��λ��
};

