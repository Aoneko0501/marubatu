// 三項演算子を用いたマルバツゲームを作る

#define _CRT_SECURE_NO_WARNINGS 1

#include<iostream>
#include<windows.h>
#include<stdlib.h>
#include<string>
#include<string.h>
#include<sstream>

using namespace std;

enum State{
	NONE, //空マス(0)
	MARU, //プレイヤー(1)
	BATSU //敵マス(2)
};

enum Turn{
	PLAYER,
	ENEMY
};

struct Board{
public:
	void Clear(); //盤面を初期化
	void Show(); //盤面を表示
	int Set(int n, Turn turn); //盤面にセット
	int Check(); //勝敗判定
protected:
	State nBoard[9];//盤面 
	char cBoard[9];
};

void PlayerTurn(); //プレイヤー
void EnemyTurn();//敵
void gameResult(); //結果発表

bool bGameSet = false;
static Turn T = PLAYER; //プレイヤー,COM
bool is_End = true;


Board board;

int main(void){
	// 盤面を初期化する
	board.Clear();

	//勝敗が決まるまで無限ループ
	do{
		PlayerTurn();
		//	if (board.Check()){ bGameSet = true;  break; }
		EnemyTurn();
		//	if (board.Check()){ bGameSet = true; break; }
	} while (!bGameSet);

	//gameResult(); //結果発表

	return 0;
}

//プレイヤーの処理
void PlayerTurn()
{
	T = PLAYER;
	int nSelect = 0;
	cout << "あなたのターンです。\nどの位置を選択しますか？(1~9)" << endl;
	board.Show();

	cin >> nSelect;
	while (nSelect <= 0 || nSelect >= 10){
		nSelect = 0;
		cout << "\a(1~9)のいずれかを入力してください。" << endl;
		cin >> nSelect;
	}

	while (board.Set(nSelect, T) == 1){
		cout << "1~9のいずれかを入力してください。" << endl;
		cin >> nSelect;
	}
}

//COM側の処理
void EnemyTurn(){
	T = ENEMY;
	int nSelect = 5;
	cout << "COMのターンです。" << endl;
	Sleep(3000);
	cout << "COMは" << nSelect << "番を選択しました。" << endl;
	board.Set(nSelect, T);
}

//盤面を初期化する
void Board::Clear(){
	string s;
	for (int i = 0; i < 9; i++){
		nBoard[i] = NONE;
	}
}

//盤面を表示
void Board::Show(){
	string s;
	for (int i = 0; i < 9; i++){
		switch (nBoard[i]){
		case NONE:
			s = to_string(i+1);
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


	cout << cBoard[0] << "｜" << cBoard[1] << "｜" << cBoard[2] << endl;
	cout << "-" << "＋" << "-" << "＋" << "-" << endl;
	cout << cBoard[3] << "｜" << cBoard[4] << "｜" << cBoard[5] << endl;
	cout << "-" << "＋" << "-" << "＋" << "-" << endl;
	cout << cBoard[6] << "｜" << cBoard[7] << "｜" << cBoard[8] << endl;
}

//n番目にセットする。
int Board::Set(int n, Turn turn)
{
	

	if (nBoard[n - 1] == MARU || nBoard[n - 1] == BATSU){
		cout << "残念ながらそこには置けません。" << endl;
		return 1;
	}

	if (T == PLAYER){ //プレイヤー
		nBoard[n - 1] = MARU;
	}
	else{  //COM
		nBoard[n - 1] = BATSU;
	}
	return 0;
}