#pragma once
#include"Man.h"
#include"AI.h"
#include"Chess.h"
class ChessGame
{
public:
	void play();//��ʼ�Ծ֣�
	ChessGame(Man* man, AI* ai, Chess* chess);
	//������ݳ�Ա
private:
	Man *man;
	AI *ai;
	Chess *chess;
};

