#pragma once
#include <iostream>
#include <vector>
using namespace std;
class Node {
public:
	// front, back, left, right, up, down
	// 0      1     2     3      4   5
	vector<char> tempSides = { 'w', 'y', 'r', 'o', 'g', 'b' };
	Node() {
		sides.resize(7);
		for (int i = 0; i < 6; i++) {
			//sides[i] = 'a' + i;
			sides[i] = 'n';
		}
		id = 0;
	}
	Node(int k) {
		sides.resize(7);
		for (int i = 0; i < 6; i++) {
			//sides[i] = 'a' + i;
			sides[i] = 'n';
		}
		id = k;
	}
	void setFront(char k) {
		sides[0] = k;
	}
	char front() {
		return sides[0];
	}
	void setBack(char k) {
		sides[1] = k;
	}
	char back() {
		return sides[1];
	}
	void setLeft(char k) {
		sides[2] = k;
	}
	char left() {
		return sides[2];
	}
	void setRight(char k) {
		sides[3] = k;
	}
	char right() {
		return sides[3];
	}
	void setUp(char k) {
		sides[4] = k;
	}
	char up() {
		return sides[4];
	}
	void setDown(char k) {
		sides[5] = k;
	}
	char down() {
		return sides[5];
	}
	// rotations
	void rotateUp() {
		// front -> up -> back -> down
		// 0 -> 4 -> 1 -> 5 
		vector<char> temp;
		temp = sides;
		sides[0] = temp[5];
		sides[4] = temp[0];
		sides[1] = temp[4];
		sides[5] = temp[1];
	}
	void rotateDown() {
		for (int i = 0; i < 3; i++)
			rotateUp();
	}
	void rotateRight() {
		// front -> right -> back -> left
		// 0 -> 3 -> 1 -> 2
		vector<char> temp;
		temp = sides;
		sides[0] = temp[2];
		sides[3] = temp[0];
		sides[1] = temp[3];
		sides[2] = temp[1];
	}
	void rotateLeft() {
		for (int i = 0; i < 3; i++) {
			rotateRight();
		}
	}
	void rotateFront() {
		// up -> right -> down -> left
		// 4 -> 3 -> 5 -> 2
		vector<char> temp;
		temp = sides;
		sides[4] = temp[2];
		sides[3] = temp[4];
		sides[5] = temp[3];
		sides[2] = temp[5];
	}
	void rotateFront_() {
		for (int i = 0; i < 3; i++) {
			rotateFront();
		}
	}

	void print() {
		string namesArr[] = { "front", "back", "left", "right", "up", "down" };
		for (int i = 0; i < 6; i++) {
			cout << namesArr[i] << ": " << sides[i] << endl;
		}
	}
	friend bool operator == (const Node & a, const Node & b);
	friend bool operator != (const Node& a, const Node& b);
	int id;
private:
	vector<char> sides;
};
inline
bool operator == (const Node& a, const Node& b) {
	for (int i = 0; i < 6; i++) {
		if (a.sides[i] != b.sides[i])
			return 0;
	}
	return 1;
//	return a.id == b.id;
}
inline
bool operator != (const Node& a, const Node& b) {
	return !(a == b);
}

class Cube
{
public:
	// front, back, left, right, up, down, front_, back_, left_, right_, up_, down_
	// 0      1     2     3      4   5     6       7      8      9       10   11
	friend bool operator==(const Cube& a, const Cube& b);
	friend bool operator!=(const Cube& a, const Cube& b);
	void rotate(int k) {
		if (k == 0) front();
		else if (k == 1) back();
		else if (k == 2) left();
		else if (k == 3) right();
		else if (k == 4) up();
		else if (k == 5) down();
		else if (k == 6) front_();
		else if (k == 7) back_();
		else if (k == 8) left_();
		else if (k == 9) right_();
		else if (k == 10) up_();
		else if (k == 11) down_();
	}
	Cube() {
		int o = 0;
		arr.resize(3);
		for (int i = 0; i < 3; i++) {
			arr[i].resize(3);
			for (int j = 0; j < 3; j++) {
				arr[i][j].resize(3);
				for (int k = 0; k < 3; k++) {
					arr[i][j][k] = Node(o++);
				}
			}
		}
	}
	void input() {
		cout << "Hold cube with white in front and red in left\n";
		cout << "Enter the front(white) \n";
		char x;
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				cin >> x;
				arr[i][j][0].setFront(x);
			}
		}
		cout << "Enter the back(yellow) \n";
		for (int i = 0; i < 3; i++) {
			for (int j = 2; j >= 0; j--) {
				cin >> x;
				arr[i][j][2].setBack(x);
			}
		}
		cout << "Enter the left(red)\n";
		for (int i = 0; i < 3; i++) {
			for (int k = 2; k >= 0; k--) {
				cin >> x;
				arr[i][0][k].setLeft(x);
			}
		}
		cout << "Enter the rigth(orange)\n";
		for (int i = 0; i < 3; i++) {
			for (int k = 0; k < 3; k++) {
				cin >> x;
				arr[i][2][k].setRight(x);
			}
		}
		cout << "Enter the up(green)\n";
		for (int k = 2; k >= 0; k--) {
			for (int j = 0; j < 3; j++) {
				cin >> x;
				arr[0][j][k].setUp(x);
			}
		}
		cout << "Enter the down(blue)\n";
		for (int k = 0; k < 3; k++) {
			for (int j = 0; j < 3; j++) {
				cin >> x;
				arr[2][j][k].setDown(x);
			}
		}
	}
	bool check(int& k) {
		k = 0;
		// check all sides
		// front
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				if (arr[i][j][0].front() != 'w')
					k++;
			}
		}
		// back
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				if (arr[i][j][2].back() != 'y')
					k++;
			}
		}
		// left
		for (int i = 0; i < 3; i++) {
			for (int k = 0; k < 3; k++) {
				if (arr[i][0][k].left() != 'r')
					k++;
			}
		}
		// right
		for (int i = 0; i < 3; i++) {
			for (int k = 0; k < 3; k++) {
				if (arr[i][2][k].right() != 'o')
					k++;
			}
		}
		// up
		for (int j = 0; j < 3; j++) {
			for (int k = 0; k < 3; k++) {
				if (arr[0][j][k].up() != 'g')
					k++;
			}
		}
		// down
		for (int j = 0; j < 3; j++) {
			for (int k = 0; k < 3; k++) {
				if (arr[2][j][k].down() != 'b')
					k++;
			}
		}
		return k == 0;
	}

	// front, back, left, right, up, down
	// 0      1     2     3      4   5
	void print() {
		string namesArr[] = { "front", "back", "left", "right", "up", "down" };
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				for (int k = 0; k < 3; k++) {
					cout << arr[i][j][k].id << ' ';
				}
				cout << endl;
			}
			cout << endl;
		}
	}
	// front, back, left, right, up, down
	// 0      1     2     3      4   5
	void print(int s) {
		if (s == 0) {
			cout << "Front\n";
			for (int i = 0; i < 3; i++) {
				for (int j = 0; j < 3; j++) {
					cout << arr[i][j][0].front();
					cout << ' ';
				}
				cout << endl;
			}
		}
		else if (s == 1) {
			cout << "Back\n";
			for (int i = 0; i < 3; i++) {
				for (int j = 2; j >= 0; j--) {
					cout << arr[i][j][2].back();
					cout << ' ';
				}
				cout << endl;
			}
		}
		else if (s == 2) {
			cout << "Left\n";
			for (int i = 0; i < 3; i++) {
				for (int k = 2; k >= 0; k--) {
					cout << arr[i][0][k].left();
					cout << ' ';
				}
				cout << endl;
			}
		}
		else if (s == 3) {
			cout << "Right\n";
			for (int i = 0; i < 3; i++) {
				for (int k = 0; k < 3; k++) {
					cout << arr[i][2][k].right();
					cout << ' ';
				}
				cout << endl;
			}
		}
		else if (s == 4) {
			cout << "Up\n";
			for (int k = 2; k >= 0; k--) {
				for (int j = 0; j < 3; j++) {
					cout << arr[0][j][k].up();
					cout << ' ';
				}
				cout << endl;
			}
		}
		else if (s == 5) {
			cout << "Down\n";
			for (int k = 0; k < 3; k++) {
				for (int j = 0; j < 3; j++) {
					cout << arr[2][j][k].down();
					cout << ' ';
				}
				cout << endl;
			}
		}
	}
	// white, red, green -> 0, 0, 0 corner
	// blue, yellow, orange	-> 2, 2, 2 corner
	void up() {
		vector<vector<vector<Node>>> tmp;
		tmp = arr;
		// i1 = j
		// j1 = 2-i
		for (int j = 0; j < 3; j++) {
			for (int k = 0; k < 3; k++) {
				tmp[0][j][k].rotateLeft();
				arr[0][k][2 - j] = tmp[0][j][k];
				//cout << 0 << ' ' << k << ' ' << 2 - j << " to " << 0 << ' ' << j << ' ' << k << endl;
			}
		}
	}
	void up_() {
		vector<vector<vector<Node>>> tmp;
		tmp = arr;
		// i1 = 2-j
		// j1 = i
		for (int j = 0; j < 3; j++) {
			for (int k = 0; k < 3; k++) {
				arr[0][2 - k][j] = tmp[0][j][k];
				arr[0][2 - k][j].rotateRight();
			}
		}

	}
	void down() {
		vector<vector<vector<Node>>> tmp;
		tmp = arr;
		for (int j = 0; j < 3; j++) {
			for (int k = 0; k < 3; k++) {
				arr[2][2 - k][j] = tmp[2][j][k];
				arr[2][2 - k][j].rotateRight();
			}
		}
	}
	void down_() {
		vector<vector<vector<Node>>> tmp;
		tmp = arr;
		for (int j = 0; j < 3; j++) {
			for (int k = 0; k < 3; k++) {
				arr[2][k][2 - j] = tmp[2][j][k];
				arr[2][k][2 - j].rotateLeft();
			}
		}
	}
	void right() {
		vector<vector<vector<Node>>> tmp;
		tmp = arr;
		for (int i = 0; i < 3; i++) {
			for (int k = 0; k < 3; k++) {
				arr[k][2][2 - i] = tmp[i][2][k];
				arr[k][2][2 - i].rotateUp();
			}
		}
	}
	void right_() {
		vector<vector<vector<Node>>> tmp;
		tmp = arr;
		for (int i = 0; i < 3; i++) {
			for (int k = 0; k < 3; k++) {
				arr[2 - k][2][i] = tmp[i][2][k];
				arr[2 - k][2][i].rotateDown();
			}
		}
		
	}
	void left() {
		vector<vector<vector<Node>>> tmp;
		tmp = arr;
		for (int i = 0; i < 3; i++) {
			for (int k = 0; k < 3; k++) {
				arr[2 - k][0][i] = tmp[i][0][k];
				arr[2 - k][0][i].rotateDown();
			}
		}
	}
	void left_() {
		vector<vector<vector<Node>>> tmp;
		tmp = arr;
		for (int i = 0; i < 3; i++) {
			for (int k = 0; k < 3; k++) {
				arr[k][0][2-i] = tmp[i][0][k];
				arr[k][0][2 - i].rotateUp();
			}
		}
	}
	void front() {
		vector<vector<vector<Node>>> tmp;
		tmp = arr;
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				arr[j][2 - i][0] = tmp[i][j][0];
				arr[j][2 - i][0].rotateFront();
			}
		}
	}
	void front_() {
		vector<vector<vector<Node>>> tmp;
		tmp = arr;
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				arr[2 - j][i][0] = tmp[i][j][0];
				arr[2 - j][i][0].rotateFront_();
			}
		}
	}
	void back() {
		vector<vector<vector<Node>>> tmp;
		tmp = arr;
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				arr[2 - j][i][2] = tmp[i][j][2];
				arr[2 - j][i][2].rotateFront_();

			}
		}
	}
	void back_(){
		vector<vector<vector<Node>>> tmp;
		tmp = arr;
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				arr[j][2 - i][2] = tmp[i][j][2];
				arr[j][2 - i][2].rotateFront();
			}
		}
	}

private:
	vector<vector<vector<Node>>> arr;
};
inline
bool operator==(const Cube& a, const Cube& b) {
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			for (int k = 0; k < 3; k++) {
				if (a.arr[i][j][k] != b.arr[i][j][k]) return false;
			}
		}
	}
	return true;
}
inline
bool operator!=(const Cube& a, const Cube& b) {
	return !(a == b);
}
