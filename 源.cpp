/*
������־
1.������Ŀ
2.�����Ŀ�Ŀ�ܣ������Щ�ࣩ





*/
#include<iostream>
#include "AI.h"
#include"Chess.h"
#include"ChessGame.h"
#include"Man.h"


int main(void) {
	Man man;

	Chess chess(13,44,43,67.3);

	AI ai;

	ChessGame game(&man,&ai,&chess);

	game.play();

	return 0;
}