#pragma once
#include <vector>
#include <utility>
using namespace std;
struct Stone 
{
	int v, h; //vertical & horizontal position
	vector<pair<int, int>> moves;
};
class Chess
{
public:
	Chess(vector<pair<int, char>> positions);
	~Chess();
	Stone b_king, w_king, w_queen, w_bishop, w_knight; 
	void setKingsMoves();
	void setQueenMoves();
	void setBishopMoves();
	void setKnightMoves();
	bool Is_CheckMate();
	bool IsObstacle(Stone st, int x, int y);
	bool isCheck();
};

