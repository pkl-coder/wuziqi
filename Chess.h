#pragma once
#include<graphics.h>
#include<vector>
#include"tools.h"
using namespace std;
//表示落子位置
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
	//棋盘的初始化
	void init();
	//判断指定坐标是否有效并保存到pos;
	bool clickBoard(int x, int y, ChessPos* pos);

	void chessDown(ChessPos *pos, chess_kind_t kind);

	int getGradeSize();//获取棋盘的大小

	//获取指定位置是黑棋，还是白棋，还是空白
	int getChessData(ChessPos* pos);
	int getChessData(int row, int col);
	bool checkOver();//检查棋盘是否结束

	Chess(int gradeSize, int marginX, int marginY, float ChessSize);
private:
	IMAGE chessWhiteImg;
	IMAGE chessBlackImg;
	
	int gradeSize;//棋盘的大小(13,15,17,19)
	int margin_x;//左边距；
	int margin_y;//上边距;
	float chessSize;//棋子大小；

	//存储当前棋局的棋子分布数据 0；空白，1：黑子，-1；白子
	vector<vector<int> > chessMap;//

	//表示现在该谁下棋
	bool playerFlag;//true:该黑子走；

	void updateGameMap(ChessPos* pos);

	bool checkWin();//检查输赢

	ChessPos lastPos;//最近落子点的位置
};

