// CodicsInternship.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include "pch.h"
#include "Chess.h"
#include <iostream>
#include <string>
#include <set>
using namespace std;

bool validPos(int x, int y) {
	if (x < 8 && x >= 0 && y >= 'a' && y <= 'h') return true;
	return false;
}
bool isDuplicate(vector<pair<int, char>> pos, pair<int, char> x) {
	if (find(pos.begin(), pos.end(), x) != pos.end()) return true;
    return false;
}
bool isKingAroundKing(int bx, char by, int wx, int wy) {

	for (int i = bx - 1; i <= bx + 1 && i; i++) {
		for (int j = int(by); j <= int(by) + 1; j++) {
			if (i == wx && wy == j)
				return true;
		}
	}
	return false;
}
void main()
{
	vector<pair<int, char>> positions;
	string stones[] = {"Black King", "White King", "White Queen", "White Knight", "White Bishop" };
	int x; char y;
	cout << "--Attention---" << endl;
	cout << "Please enter vertical position starting from 0 not 1 and horizontal line with lower case letters" << endl;
	cout << "--------------" << endl;
	for (int i = 0; i < 5; i++) {
		cout << "Enter position of " + stones[i] << endl;
		cout << "vertical: "; cin >> x;
		cout << "horizontal: "; cin >> y;
		while (!validPos(x, y)) {
			cin.clear();
			cout << "You have entered out of board position" << endl;
			cout << "vertical: "; cin >> x;
			cout << "horizontal: "; cin >> y;
		}
		if (i == 1) {
			while (isKingAroundKing(positions[0].first, positions[0].second, x, y-97)) {
				cin.clear();
				cout << "You can't put 2 Kings near each other" << endl;
				cout << "vertical: "; cin >> x;
				cout << "horizontal: "; cin >> y;
			}
		}
		if (i > 1) {
			while (isDuplicate(positions, make_pair(x, y-97))) {
				cin.clear();
				cout << "This place is already occupied, try another position" << endl;
				cout << "vertical: "; cin >> x;
				cout << "horizontal: "; cin >> y;
			}
		}
		positions.push_back(make_pair(x, y-97));
	}
	Chess table(positions);
		cout << ((table.Is_CheckMate()) ? "You got checkmate!" : "Not checkmate");
		//delete table;
		//return 0;
	
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
