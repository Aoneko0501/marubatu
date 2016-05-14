// �O�����Z�q��p�����}���o�c�Q�[�������

#define _CRT_SECURE_NO_WARNINGS 1

#include<iostream>
#include<windows.h>
#include<stdlib.h>
#include<string>
#include<string.h>
#include<sstream>

using namespace std;

enum State {
	NONE, //��}�X(0)
	MARU, //�v���C���[(1)
	BATSU //�G�}�X(2)
};

enum Turn {
	PLAYER,
	ENEMY
};

struct Board {
public:
	void Clear(); //�Ֆʂ�������
	void Show(); //�Ֆʂ�\��
	int Set(int n, Turn turn); //�ՖʂɃZ�b�g
	int Check(); //���s����
protected:
	State nBoard[9];//�Ֆ� 
	char cBoard[9];
};

void PlayerTurn(); //�v���C���[
void EnemyTurn();//�G
void gameResult(int res); //���ʔ��\

bool bGameSet = false;
static Turn T = PLAYER; //�v���C���[,COM
bool is_End = true;

int Result = 0;


Board board;

int main(void) {
	// �Ֆʂ�����������
	board.Clear();

	//���s�����܂�܂Ŗ������[�v
	do {
		PlayerTurn();
		if (board.Check() != 0) { bGameSet = true; Result = 1;  break; }
		//EnemyTurn();
		//if (board.Check() != 0){ bGameSet = true; Result = 2; break; }
	} while (!bGameSet);

	gameResult(Result); //���ʔ��\
	board.Show();
	return 0;
}

//�v���C���[�̏���
void PlayerTurn()
{
	T = PLAYER;
	int nSelect = 0;
	cout << "���Ȃ��̃^�[���ł��B\n�ǂ̈ʒu��I�����܂����H(1~9)" << endl;
	board.Show();

	cin >> nSelect;
	while (nSelect <= 0 || nSelect >= 10) {
		nSelect = 0;
		cout << "\a(1~9)�̂����ꂩ����͂��Ă��������B" << endl;
		cin >> nSelect;
	}

	while (board.Set(nSelect, T) == 1) {
		cout << "1~9�̂����ꂩ����͂��Ă��������B" << endl;
		cin >> nSelect;
	}
}

//COM���̏���
void EnemyTurn() {
	T = ENEMY;
	int nSelect = 8;
	cout << "COM�̃^�[���ł��B" << endl;
	Sleep(3000);
	cout << "COM��" << nSelect << "�Ԃ�I�����܂����B" << endl;
	board.Set(nSelect, T);
}

//�Ֆʂ�����������
void Board::Clear() {
	string s;
	for (int i = 0; i < 9; i++) {
		nBoard[i] = NONE;
	}
}

//�Ֆʂ�\��
void Board::Show() {
	string s;
	for (int i = 0; i < 9; i++) {
		switch (nBoard[i]) {
		case NONE:
			s = to_string(i + 1);
			strcpy(&cBoard[i], s.c_str());
			break;
		case MARU:
			strcpy(&cBoard[i], "o");
			break;
		case BATSU:
			strcpy(&cBoard[i], "x");
			break;
		}
	}


	cout << cBoard[0] << "�b" << cBoard[1] << "�b" << cBoard[2] << endl;
	cout << "-" << "�{" << "-" << "�{" << "-" << endl;
	cout << cBoard[3] << "�b" << cBoard[4] << "�b" << cBoard[5] << endl;
	cout << "-" << "�{" << "-" << "�{" << "-" << endl;
	cout << cBoard[6] << "�b" << cBoard[7] << "�b" << cBoard[8] << endl;
}

//n�ԖڂɃZ�b�g����B
int Board::Set(int n, Turn turn)
{


	if (nBoard[n - 1] == MARU || nBoard[n - 1] == BATSU) {
		cout << "�c�O�Ȃ��炻���ɂ͒u���܂���B" << endl;
		return 1;
	}

	if (T == PLAYER) { //�v���C���[
		nBoard[n - 1] = MARU;
	}
	else {  //COM
		nBoard[n - 1] = BATSU;
	}
	return 0;
}

//���s����
int Board::Check()
{
	int point = 0;
	int mark = 0;

	//������
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			switch (nBoard[mark]) {
			case MARU:
				point++;
				if (point == 3)return 1;
				break;
			case BATSU:
				point = point + 2;
				if (point == 6)return 2;
				break;
			default:
				point = 0;
			}
			mark++;
		}
		point = 0;
	}
	point = 0;
	mark = 0;

	//�c����

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			switch (nBoard[mark]) {
			case MARU:
				point++;
				if (point == 3)return 1;
				break;
			case BATSU:
				point = point + 2;
				if (point == 6)return 2;
				break;
			default:
				point = 0;
			}
			mark = mark + 3;
		}
		mark = i + 1;
		point = 0;
	}
	point = 0;
	mark = 0;

	// �΂߉E��
	for (int i = 0; i < 3; i++) {
		switch (nBoard[mark]) {
		case MARU:
			point++;
			if (point == 3)return 1;
			mark = mark + 4;
			break;
		case BATSU:
			point = point + 2;
			if (point == 6)return 2;
			mark = mark + 4;
			break;
		default:
			point = 0;
			mark = mark + 4;
			break;
		}
	}

	point = 0;
	mark = 2;
	// �΂߉E��
	for (int i = 0; i < 3; i++) {
		switch (nBoard[mark]) {
		case MARU:
			point++;
			if (point == 3)return 1;
			mark = mark + 2;
			break;
		case BATSU:
			point = point + 2;
			if (point == 6)return 2;
			mark = mark + 2;
			break;
		default:
			point = 0;
			mark = mark + 2;
		}
	}

	return 0;
}

void gameResult(int res) {

	if (res == 1) {
		printf("�v���C���[�̏����ł��B\n");
	}
	else if (res == 2) {
		printf("COM�̏����ł��B\n");
	}
	else {
		printf("���������ł��B\n");
	}
}