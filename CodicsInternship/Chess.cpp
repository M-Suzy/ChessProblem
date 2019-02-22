#include "pch.h"
#include "Chess.h"


Chess::Chess(vector<pair<int, char>> positions)
{
	b_king.v = positions[0].first; b_king.h = positions[0].second;
	w_king.v = positions[1].first; w_king.h = positions[1].second;
	w_queen.v = positions[2].first; w_queen.h = positions[2].second;
	w_knight.v = positions[3].first; w_knight.h = positions[3].second;
	w_bishop.v = positions[4].first; w_bishop.h = positions[4].second;
	setKingsMoves();
	setQueenMoves();
	setBishopMoves();
	setKnightMoves();
}

Chess::~Chess(){}

void Chess::setKingsMoves()
{
	for (int i = b_king.v - 1; i <= b_king.v + 1; i++) {
		for (int j = b_king.h - 1; j <= b_king.h + 1; j++) {
			if (i < 8 && j < 8 && i>-1 && j>-1 && !(i==b_king.v && j==b_king.h))
				b_king.moves.push_back(make_pair(i, j));
		}
	}
	for (int i = w_king.v - 1; i <= w_king.v + 1; i++) {
		for (int j = w_king.h - 1; j <= w_king.h + 1 && !(IsObstacle(w_king, i, j)); j++) {
			if (i < 8 && j < 8 && i>-1 && j>-1 && !(i == w_king.v && j == w_king.h))
				w_king.moves.push_back(make_pair(i, j));
		}
	}
}

void Chess::setQueenMoves()
{
	//upward
	for (int i = w_queen.v + 1; (i < 8 && !(IsObstacle(w_queen, i, w_queen.h))); i++)
	w_queen.moves.push_back(make_pair(i, w_queen.h));
	// just left
	for (int j = w_queen.h - 1; (j >= 0 && !(IsObstacle(w_queen, w_queen.v, j))); j--)
		w_queen.moves.push_back(make_pair(w_queen.v, j));
	// down
	for (int i = w_queen.v - 1; (i >= 0 && !(IsObstacle(w_queen, i, w_queen.h))); i--)
		w_queen.moves.push_back(make_pair(i, w_queen.h));
	//right
	for (int k = w_queen.h + 1; (k < 8 && IsObstacle(w_queen, w_queen.v, k)); k++)
            w_queen.moves.push_back(make_pair(w_queen.v, k));
	//diagonally  downleft, downright
	for (int i = w_queen.v + 1, j = w_queen.h - 1; i < 8 && j >= 0 && !(IsObstacle(w_queen, i, j)); i++, j--) 
			w_queen.moves.push_back(make_pair(i, j));
	for (int i = w_queen.v + 1, k = w_queen.h + 1; i < 8 && k < 8 && !(IsObstacle(w_queen, w_queen.v, k)); i++, k++) 
			w_queen.moves.push_back(make_pair(i, k));
	// diagonally up left, up right
	for (int i = w_queen.v - 1, j = w_queen.h - 1; i >= 0 && j >= 0 && !(IsObstacle(w_queen, i, j)); i--, j--) 
			w_queen.moves.push_back(make_pair(i, j));
	for (int i = w_queen.v - 1, k = w_queen.h + 1; i >= 0 && k < 8 && !(IsObstacle(w_queen, i, k)); i--, k++)
		w_queen.moves.push_back(make_pair(i, k));
}
void Chess::setBishopMoves()
{
	for (int i = w_bishop.v - 1, j = w_bishop.h - 1; i >= 0 && j >= 0 && !(IsObstacle(w_bishop, i, j)); i--, j--) 
			w_bishop.moves.push_back(make_pair(i, j));
	for (int i = w_bishop.v - 1, k = w_bishop.h + 1; i >= 0 && k<8 && !(IsObstacle(w_bishop, i, k)); i--, k++)
			w_bishop.moves.push_back(make_pair(i, k));
	for (int i = w_bishop.v - 1, j = w_bishop.h + 1; i < 8 && j >= 0 && !(IsObstacle(w_bishop, i, j)); i++, j--)
		w_bishop.moves.push_back(make_pair(i, j));
	for (int i = w_bishop.v + 1, k = w_bishop.h + 1; i < 8 && k < 8 && !(IsObstacle(w_bishop, i, k)); i++, k++)
		w_bishop.moves.push_back(make_pair(i, k));
}
void Chess::setKnightMoves()
{
	int X[8] = { 2, 1, -1, -2, -2, -1, 1, 2 };
	int Y[8] = { 1, 2, 2, 1, -1, -2, -2, -1 };
	for (int i = 0; i < 8; i++) 
	{
    if (w_knight.v + X[i]<8 && w_knight.v + X[i]>-1 && w_knight.h + Y[i]<8 && w_knight.h + Y[i]>-1) 
		if (!(IsObstacle(w_knight, w_knight.v + X[i], w_knight.h + Y[i]))) {
			w_knight.moves.push_back(make_pair(w_knight.v + X[i], w_knight.h + Y[i]));
		}
		else { break; }
	}
}
bool Chess::Is_CheckMate()
{ 
	if (isCheck()) {
		pair<int, int> bk;
		pair<int, int> zz = make_pair(0, 0);
		for (int i = 0; i < b_king.moves.size(); i++) {
			bk = b_king.moves[i];
			if(find(w_queen.moves.begin(), w_queen.moves.end(), make_pair(b_king.v, b_king.h)) != w_queen.moves.end())
			for (vector <pair <int, int> >::iterator it = w_queen.moves.begin(); it != w_queen.moves.end(); it++) {
				if (*it == bk) {
					bk = zz;
					break;
				}
			}
			if (bk != zz) {
				for (vector <pair <int, int> >::iterator it = w_bishop.moves.begin(); it != w_bishop.moves.end(); it++) {
					if (*it == bk) {
						bk = zz;
						break;
					}
				}
			}
			if (bk != zz) {
				for (vector <pair <int, int> >::iterator it = w_knight.moves.begin(); it != w_knight.moves.end(); it++) {
					if ((*it == bk)) {
						bk == zz;
						break;
					}
				}
			}
			if (bk != zz) {
				for (vector <pair <int, int> >::iterator it = w_king.moves.begin(); it != w_king.moves.end(); it++) {
					if (*it == bk) {
						bk = zz;
						break;
					}
				}
			}
			if (bk == zz) b_king.moves.erase(b_king.moves.begin() + i);
		}
		if (b_king.moves.empty()) return true;
	}
	return false;
}

bool Chess::IsObstacle(Stone st, int x, int y)
{
	if (st.v == w_queen.v && st.h == w_queen.h) {
	if ((x == w_king.v && y == w_king.h) || (x == w_knight.v && y == w_knight.h) || (x == w_bishop.v && y == w_bishop.h))
			return true;
	}
	if (st.v == w_knight.v && st.h == w_knight.h) {
		if ((x == w_king.v && y == w_king.h) || (x == w_queen.v && y == w_queen.h) || (x == w_bishop.v && y == w_bishop.h))
			return true;
	}
	if (st.v == w_bishop.v && st.h == w_bishop.h) {
		if ((x == w_king.v && y == w_king.h) || (x == w_knight.v && y == w_knight.h) || (x == w_queen.v && y == w_queen.h))
			return true;
	}
		return false;
}

bool Chess::isCheck()
{
if (find(w_queen.moves.begin(), w_queen.moves.end(), make_pair(b_king.v, b_king.h)) != w_queen.moves.end()) return true;
if (find(w_knight.moves.begin(), w_knight.moves.end(), make_pair(b_king.v, b_king.h)) != w_knight.moves.end()) return true;
if (find(w_bishop.moves.begin(), w_bishop.moves.end(), make_pair(b_king.v, b_king.h)) != w_bishop.moves.end()) return true;
return false;
}
