#include <iostream>
#include "Cube.h"
#include <fstream>
#include <vector>
#include <queue>
#include <list>
using namespace std;
queue<Cube> cubeQueue;
vector<Cube> checkCube;
queue<vector<int>> movesQueue;
	// front, back, left, right, up, down, front_, back_, left_, right_, up_, down_
	// 0      1     2     3      4   5     6       7      8      9       10   11
bool canMove(int i, vector<int>& k) {
	if (k.size() == 0) return true;
	if ((i - 6) == k.back() || (i + 6) == k.back()) return false;
	if (k.size() > 1 && k[k.size()-2] == i && k[k.size()-1] == i) return false;
	return true;
}
int maxMoves = 30;
string movesArr[] = { "f", "b", "l", "r", "u", "d", "f'", "b'", "l'", "r'", "u'", "d'" };
/*void solve(Cube cbr, vector<int> mv, int mvc) {
	if (mvc >= maxMoves) { return; }
	Cube cbn[12];
	cout << mvc << endl;
	bool rotated[12] = { 0,0,0,0,0,0,0,0,0,0,0,0 };
	vector<vector<int>> s;
	s.reserve(12);
	for (int i = 0; i < 12; i++) {
		s.push_back(mv);
		if (canMove(i, mv)) {
			rotated[i] = 1;
			cbn[i] = cbr;
			cbn[i].rotate(i);
			s[i].push_back(i);
		}
	}
	for (int i = 0; i < 12; i++) {
		if (!rotated[i]) continue;
		if (cbn[i].check()) {
			if (maxMoves > mvc)
				maxMoves = mvc;
			cout << endl << mvc << endl;
			for (int i = 0; i < mv.size(); i++) {
				cout << movesArr[mv[i]] << ' ';
			}
			cout << endl;
			return;
		}
	}
	for (int i = 0; i < 12; i++)
		if (rotated[i])
			solve(cbn[i], s[i], mvc + 1);
}
*/
int maxCount = 0;
int minS = 1000;
void solve() {
	int s = 0;
	while (!cubeQueue.empty()) {
		if (maxCount < movesQueue.front().size()) {
			cout << movesQueue.front().size() << ' ' << movesQueue.size() << endl;
			maxCount = movesQueue.front().size();
			checkCube.clear();
		}
		if (cubeQueue.front().check(s)) {
			cout << movesQueue.front().size() << endl;
			for (int i = 0; i < movesQueue.front().size(); i++) {
				cout << movesArr[movesQueue.front()[i]] << ' ';
			}
			cout << endl;
			return;
		}
		else {
			//cout << movesQueue.front().size() << '\n' << movesQueue.size() << endl;
			if (s < minS) minS = s;
			if (s > minS + 5 || movesQueue.front().size() > maxMoves) {
				movesQueue.pop(); cubeQueue.pop();// cout << minS << ' ' << s << endl << "popped\n";
			continue; }
			for (int i = 0; i < 12; i++) {
				if (canMove(i, movesQueue.front())) {
					Cube temp = cubeQueue.front();
					temp.rotate(i);
					bool found = 0;
					for (auto j = checkCube.begin(); j != checkCube.end(); j++) {
						if (*j == temp) {
							found = 1;
							break;
						}
					}
					if (!found) {
						vector<int> newMoves;
						newMoves = movesQueue.front();
						newMoves.push_back(i);
						cubeQueue.push(temp);
						checkCube.push_back(temp);
						movesQueue.push(newMoves);
					}
				}
			}
			movesQueue.pop();
			cubeQueue.pop();
		}
	}
}
int main() {
	Cube cb;
	cb.input();
	cb.right();
	cb.up();
	cb.right_();
	cb.up_();
	for (int i = 0; i < 6; i++) {
		cb.print(i);
	}
	vector<int> k;
	cubeQueue.push(cb);
	checkCube.push_back(cb);
	movesQueue.push(k);
	solve();
	return 0;
}