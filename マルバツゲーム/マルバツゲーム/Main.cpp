// 三項演算子を用いたマルバツゲームを作る

#include<iostream>
using namespace std;

enum State{
	NONE, //空マス(0)
	PLAYER, //プレイヤー(1)
	ENEMY //敵マス(2)
};

struct Board{
public:
	void Clear(); //盤面を初期化
	void Show(); //盤面を表示
	int Set(int n,bool turn); //盤面にセット
	int Check(); //勝敗判定
protected:
	State nBorad[9];//盤面 
};

void PlayerTurn(); //プレイヤー
void EnemyTurn();//敵
void gameResult(); //結果発表

bool bGameSet = false;
bool Turn = true; //(true):プレイヤー,(false):COM
bool is_End = true;


Board board;

int main(void){
	// 盤面を初期化する
	board.Clear();

	//勝敗が決まるまで無限ループ
	do{
		PlayerTurn();
	//	if (board.Check()){ bGameSet = true;  break; }
	//	EnemyTurn();
	//	if (board.Check()){ bGameSet = true; break; }
	}while (!bGameSet);

	//gameResult(); //結果発表

	return 0;
}

//プレイヤーの処理
void PlayerTurn()
{
	int nSelect = 0;
	cout << "あなたのターンです。\nどの位置を選択しますか？(1~9)" << endl;
	board.Show();

	cin >> nSelect;
	while (nSelect <= 0||nSelect >= 10){
		nSelect = 0;
		cout << "\a(1~9)のいずれかを入力してください。" << endl;
		cin >> nSelect;
	}

	while (board.Set(nSelect, Turn) == 1){
		cout << "1~9のいずれかを入力してください。" << endl;
		cin >> nSelect;
	}
}

//COM側の処理
void EnemyTurn(){
	int nSelect = 0;
	cout << "COMのターンです。" << endl;



	board.Set(nSelect, Turn);
}

//盤面を初期化する
void Board::Clear(){
	for (int i = 0; i < 9; i++){
		nBorad[i] = NONE;
	}
}

//盤面を表示
void Board::Show(){
	cout << nBorad[0] <<"｜" << nBorad[1]<< "｜"<< nBorad[2]<<endl;
	cout << "-" << "＋" << "-" << "＋" << "-" << endl;
	cout << nBorad[3] << "｜" << nBorad[4] << "｜" << nBorad[5] << endl;
	cout << "-" << "＋" << "-" << "＋" << "-" << endl;
	cout << nBorad[6] << "｜" << nBorad[7] << "｜" << nBorad[8] << endl;
}

//n番目にセットする。
int Board::Set(int n,bool turn)
{
	if (nBorad[n-1] == PLAYER || nBorad[n-1] == ENEMY){
		cout << "そこには置けません。" << endl;
		return 1;
	}

	if (turn){ //プレイヤー
		nBorad[n-1] = PLAYER;
	}
	else{  //COM
		nBorad[n-1] = ENEMY;
	}
	return 0;
}