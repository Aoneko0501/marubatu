// �O�����Z�q��p�����}���o�c�Q�[�������

#define _CRT_SECURE_NO_WARNINGS 1

#include<iostream>
#include<windows.h>
#include<stdlib.h>
#include<string>
#include<string.h>
#include<sstream>
#include<time.h>

inline void InitRand()
{
	srand((unsigned int)time(NULL));
}


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
void Auto();

bool bGameSet = false;
static Turn T = PLAYER; //�v���C���[,COM

int Result = 0;
int Dice();
int Count = 0;

bool Game = true;
char str;


Board board;

int main(void) {
	// �Ֆʂ�����������
	while(Game) {
		InitRand();
		board.Clear();

		//���s�����܂�܂Ŗ������[�v
		do {
			//PlayerTurn();
			Auto();
			board.Show();
			Result = board.Check();
			if (Result == 1 || Result == 3) { bGameSet = true; break; }
			EnemyTurn();
			board.Show();
			Result = board.Check();
			if (Result == 2) { bGameSet = true; break; }

		} while (!bGameSet);

		gameResult(Result); //���ʔ��\
		board.Show();
		printf("������x�H(y/n)");
		cin >> str;
		if (tolower(str) == 'n')Game = false; 

	}
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
	int nSelect;
	cout << "COM�̃^�[���ł��B" << endl;
	//Sleep(1500);

	nSelect = Dice();

	while (nSelect <= 0 || nSelect >= 10) {
		nSelect = 0;
		//cout << "\a(1~9)�̂����ꂩ����͂��Ă��������B" << endl;
		nSelect = Dice();
	}

	while (board.Set(nSelect, T) == 1) {
		//cout << "1~9�̂����ꂩ����͂��Ă��������B" << endl;
		nSelect = Dice();
	}
	cout << "COM��" << nSelect << "�Ԃ�I�����܂����B" << endl;
}

void Auto()
{
	T = PLAYER;
	int nSelect;
	cout << "AUTO�̃^�[���ł��B" << endl;
	//Sleep(1500);

	nSelect = Dice();

	while (nSelect <= 0 || nSelect >= 10) {
		nSelect = 0;
		//cout << "\a(1~9)�̂����ꂩ����͂��Ă��������B" << endl;
		nSelect = Dice();
	}

	while (board.Set(nSelect, T) == 1) {
		//cout << "1~9�̂����ꂩ����͂��Ă��������B" << endl;
		nSelect = Dice();
	}
	cout << "AUTO��" << nSelect << "�Ԃ�I�����܂����B" << endl;
}

//�Ֆʂ�����������
void Board::Clear() {
	string s;
	bGameSet = false;
	Count = 0;
	Result = 0;
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

int Dice() {
	return rand() % 9 + 1;
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
	int point_P = 0;
	int point_E = 0;
	int mark = 0;

	//������
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			switch (nBoard[mark]) {
			case MARU:
				point_P++;
				if (point_P == 3)return 1;
				break;
			case BATSU:
				point_E++;
				if (point_E == 3)return 2;
				break;
			default:
				point_P = 0;
				point_E = 0;
				break;
			}
			mark++;
			printf("%d:%d\n", mark, point_P);
		}
		point_P = 0;
		point_E = 0;
	}
	point_P = 0;
	point_E = 0;
	mark = 0;

	//�c����

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			switch (nBoard[mark]) {
			case MARU:
				point_P++;
				if (point_P == 3)return 1;
				break;
			case BATSU:
				point_E++;
				if (point_E == 3)return 2;
				break;
			default:
				point_P = 0;
				point_E = 0;
				break;
			}
			mark = mark + 3;
		}
		mark = i + 1;
		point_P = 0;
		point_E = 0;
	}
	point_P = 0;
	point_E = 0;
	mark = 0;

	// �΂߉E��
	for (int i = 0; i < 3; i++) {
		switch (nBoard[mark]) {
		case MARU:
			point_P++;
			if (point_P == 3)return 1;
			mark = mark + 4;
			break;
		case BATSU:
			point_E++;
			if (point_E == 3)return 2;
			mark = mark + 4;
			break;
		default:
			point_P = 0;
			point_E = 0;
			mark = mark + 4;
			break;
		}
	}

	point_P = 0;
	point_E = 0;
	mark = 2;
	// �΂߉E��
	for (int i = 0; i < 3; i++) {
		switch (nBoard[mark]) {
		case MARU:
			point_P++;
			if (point_P == 3)return 1;
			mark = mark + 2;
			break;
		case BATSU:
			point_E++;
			if (point_E == 3)return 2;
			mark = mark + 2;
			break;
		default:
			point_P = 0;
			point_E = 0;
			mark = mark + 2;
			break;
		}
	}
	printf("%d�^�[����\n", Count+1);
	Count++;
	if (Count == 9) return 3;

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