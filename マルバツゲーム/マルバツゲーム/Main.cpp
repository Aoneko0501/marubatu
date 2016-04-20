// 三項演算子を用いたマルバツゲームを作る

#include<iostream>
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
	int Set(int n,bool turn); //盤面にセット
	int Check(); //勝敗判定
protected:
	State nBorad[9];//盤面 
};

void PlayerTurn(); //プレイヤー
void EnemyTurn();//敵
void gameResult(); //結果発表

bool bGameSet = false;
Turn T = PLAYER; //プレイヤー,COM
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
	}while (!bGameSet);

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
	while (nSelect <= 0||nSelect >= 10){
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
	cout << "COMのターンです。"  << endl;
	cout << "COMは" << nSelect << "番を選択しました。" << endl;
	board.Set(nSelect, T);
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
	if (nBorad[n-1] == MARU || nBorad[n-1] == BATSU){
		cout << "残念ながらそこには置けません。" << endl;
		return 1;
	}

	if (T == PLAYER){ //プレイヤー
		nBorad[n-1] = MARU;
	}
	else{  //COM
		nBorad[n-1] = BATSU;
	}
	return 0;
}