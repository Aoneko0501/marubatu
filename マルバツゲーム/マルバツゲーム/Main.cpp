// 三項演算子を用いたマルバツゲームを作る

#include<iostream>
using namespace std;

struct Board{
public:
	void Clear();//盤面を初期化
	void Show();//盤面を表示
	void Set(int n,bool turn);//盤面にセット
	int Check(); //勝敗判定
protected:
	int nBorad[9];//盤面 (0):空マス,(1):自マス,(2):敵マス
};



void PlayerTurn(); //プレイヤー
void EnemyTurn();//敵
void gameResult(); //結果発表

bool bGameSet = false;
bool bTurn = true; //(true):プレイヤー,(false):COM


Board board;

int main(void){

	board.Clear();

	do{
		PlayerTurn();
		if (board.Check()){ bGameSet = true;  break; }
		EnemyTurn();
		if (board.Check()){ bGameSet = true; break; }
	}while (!bGameSet);

	gameResult();

	return 0;
}

void PlayerTurn()
{
	int nSelect = 0;
	cout << "あなたのターンです。\nどの位置を選択しますか？(1~9)" << endl;
	board.Show();

	cin >> nSelect;
	if (nSelect =< 0 || nSelect => 10 ){
		nSelect = 0;
		cout << "\a(1~9)のいずれかを入力してください。" << endl;
		cin >> nSelect;
	}

	board.Set(nSelect,bTurn);
}

//盤面を初期化する
void Board::Clear(){
	for (int i = 0; i < 9; i++){
		nBorad[i] = 0;
	}
}

//指定された箇所にセットする。
void Board::Set(int n,bool turn)
{


	if (turn){ //プレイヤー

	}
	else{  //COM

	}
}