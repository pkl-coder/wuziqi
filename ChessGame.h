#pragma once
#include"Man.h"
#include"AI.h"
#include"Chess.h"
class ChessGame
{
public:
	void play();//开始对局；
	ChessGame(Man* man, AI* ai, Chess* chess);
	//添加数据成员
private:
	Man *man;
	AI *ai;
	Chess *chess;
};

