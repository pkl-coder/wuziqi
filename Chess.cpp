#include "Chess.h"
#include<mmsystem.h>
#include<cmath>
#pragma comment(lib,"winmm.lib")
#include<conio.h>

Chess::Chess(int gradeSize, int marginX, int marginY, float chessSize)
{
	this->gradeSize = gradeSize;
	this->margin_x = marginX;
	this->margin_y = marginY;
	this->chessSize = chessSize;
	playerFlag = CHESS_BLACK;

	for (int i = 0; i < gradeSize; i++) {
		vector<int> row;
		for (int j = 0; j < gradeSize; j++) {
			row.push_back(0);
		}
		chessMap.push_back(row);
	}
}

void Chess::updateGameMap(ChessPos* pos)
{
	lastPos = *pos;
	chessMap[pos->row][pos->col] = playerFlag ? CHESS_BLACK : CHESS_WHITE;
	playerFlag = !playerFlag;
}




void Chess::init()
{
	//������Ϸ����
	initgraph(897, 895);

	loadimage(0,"res/����2.jpg");
	//���ſ�ʼ��ʾ��
	mciSendString("play res/start.wav", 0, 0, 0);

	//���غ���Ͱ���ͼƬ
	loadimage(&chessBlackImg, "res/black.png",chessSize, chessSize,true);
	loadimage(&chessWhiteImg, "res/white.png",chessSize, chessSize,true);

	//�������
	for (int i = 0; i < gradeSize; i++) {
		for (int j = 0; j < gradeSize; j++) {
			chessMap[i][j] = 0;

		}
	}
	playerFlag = true;
}

bool Chess::clickBoard(int x, int y, ChessPos* pos)
{
	bool ret = false;

	int col = (x - margin_x) / chessSize;
	int row = (y - margin_y) / chessSize;

	int leftTopPosX = margin_x + chessSize * col;
	int leftTopPosY = margin_y + chessSize * row;
	int offset = chessSize * 0.4;

	int len;

	do {
		//���Ͻǵ��ж�
		len = sqrt((x - leftTopPosX) * (x - leftTopPosX) + (y - leftTopPosY) * (y - leftTopPosY));

		if (len < offset) {
			pos->row = row;
			pos->col = col;
			if (chessMap[pos->row][pos->col] == 0) {
				ret = true;
			}
			break;
		}
		
		//���Ͻ��ж�
		 int x2 = leftTopPosX + chessSize;
		 int y2 = leftTopPosY;
		len = sqrt((x - x2) * (x - x2) + (y - y2) * (y - y2));
		if (len < offset) {
			pos->row = row;
			pos->col = col+1;
			if (chessMap[pos->row][pos->col] == 0) {
				ret = true;
			}
			break;
		}
		//���½��ж�
		 x2 = leftTopPosX;
		 y2 = leftTopPosY + chessSize;
		len = sqrt((x - x2) * (x - x2) + (y - y2) * (y - y2));
		if (len < offset) {
			pos->row = row+1;
			pos->col = col;
			if (chessMap[pos->row][pos->col] == 0) {
				ret = true;
			}
			break;
		}
		//���½��ж�
		 x2 = leftTopPosX + chessSize;
		 y2 = leftTopPosY + chessSize;
		len = sqrt((x - x2) * (x - x2) + (y - y2) * (y - y2));
		if (len < offset) {
			pos->row = row + 1;
			pos->col = col + 1;
			if (chessMap[pos->row][pos->col] == 0) {
				ret = true;
			}
			break;
		}
	} while (0);

	return ret;	
}

void Chess::chessDown(ChessPos* pos, chess_kind_t kind)
{
	mciSendString("play res/down7.wav", 0, 0, 0);
	int x = margin_x + chessSize * pos->col - 0.5 * chessSize;
	int y = margin_y + chessSize * pos->row - 0.5 * chessSize;
	
	if (kind == CHESS_WHITE) {
		putimagePNG(x, y, &chessWhiteImg);

	}
	else {
		putimagePNG(x, y, &chessBlackImg);
	}
	updateGameMap(pos); 
}

int Chess::getGradeSize()
{
	return gradeSize;
}

int Chess::getChessData(ChessPos* pos)
{
	return chessMap[pos->row][pos->col];
}

int Chess::getChessData(int row, int col)
{
	return chessMap[row][col];
}

bool Chess::checkWin()
{
	// ����б���ִ������ÿ����������ݵ�ǰ�����������5�����ӣ���һ�ַ��Ͼ���Ӯ
	// ˮƽ����
	int row = lastPos.row;
	int col = lastPos.col;

	for (int i = 0; i < 5; i++)
	{
		// ����5��������ƥ��4���ӣ�20�����
		if (col - i >= 0 &&
			col - i + 4 < gradeSize &&
			chessMap[row][col - i] == chessMap[row][col - i + 1] &&
			chessMap[row][col - i] == chessMap[row][col - i + 2] &&
			chessMap[row][col - i] == chessMap[row][col - i + 3] &&
			chessMap[row][col - i] == chessMap[row][col - i + 4])
			return true;
	}

	// ��ֱ����(��������4��)
	for (int i = 0; i < 5; i++)
	{
		if (row - i >= 0 &&
			row - i + 4 < gradeSize &&
			chessMap[row - i][col] == chessMap[row - i + 1][col] &&
			chessMap[row - i][col] == chessMap[row - i + 2][col] &&
			chessMap[row - i][col] == chessMap[row - i + 3][col] &&
			chessMap[row - i][col] == chessMap[row - i + 4][col])
			return true;
	}

	// ��/"����
	for (int i = 0; i < 5; i++)
	{
		if (row + i < gradeSize &&
			row + i - 4 >= 0 &&
			col - i >= 0 &&
			col - i + 4 < gradeSize &&
			// ��[row+i]�У���[col-i]�����ӣ������Ϸ�����4�����Ӷ���ͬ
			chessMap[row + i][col - i] == chessMap[row + i - 1][col - i + 1] &&
			chessMap[row + i][col - i] == chessMap[row + i - 2][col - i + 2] &&
			chessMap[row + i][col - i] == chessMap[row + i - 3][col - i + 3] &&
			chessMap[row + i][col - i] == chessMap[row + i - 4][col - i + 4])
			return true;
	}

	// ��\�� ����
	for (int i = 0; i < 5; i++)
	{
		// ��[row+i]�У���[col-i]�����ӣ������·�����4�����Ӷ���ͬ
		if (row - i >= 0 &&
			row - i + 4 < gradeSize &&
			col - i >= 0 &&
			col - i + 4 < gradeSize &&
			chessMap[row - i][col - i] == chessMap[row - i + 1][col - i + 1] &&
			chessMap[row - i][col - i] == chessMap[row - i + 2][col - i + 2] &&
			chessMap[row - i][col - i] == chessMap[row - i + 3][col - i + 3] &&
			chessMap[row - i][col - i] == chessMap[row - i + 4][col - i + 4])
			return true;
	}

	return false;
}

bool Chess::checkOver()
{
	if (checkWin()) {
		Sleep(2000);
		if (playerFlag==false) {
			//��Ӯ��
			mciSendString("play res/����.mp3", 0, 0, 0);
			loadimage(0, "res/ʤ��.jpg");
		}
		else {
			mciSendString("play res/ʧ��.mp3", 0, 0, 0);
			loadimage(0, "res/ʧ��.jpg");
		}
		_getch();//��ͣ
		return true;
	}
	
	return false;

	


	
}

