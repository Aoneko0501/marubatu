// �O�����Z�q��p�����}���o�c�Q�[�������

#include<iostream>
using namespace std;

struct Board{
public:
	void Clear();//�Ֆʂ�������
	void Show();//�Ֆʂ�\��
	void Set(int n,bool turn);//�ՖʂɃZ�b�g
	int Check(); //���s����
protected:
	int nBorad[9];//�Ֆ� (0):��}�X,(1):���}�X,(2):�G�}�X
};



void PlayerTurn(); //�v���C���[
void EnemyTurn();//�G
void gameResult(); //���ʔ��\

bool bGameSet = false;
bool bTurn = true; //(true):�v���C���[,(false):COM


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
	cout << "���Ȃ��̃^�[���ł��B\n�ǂ̈ʒu��I�����܂����H(1~9)" << endl;
	board.Show();

	cin >> nSelect;
	if (nSelect =< 0 || nSelect => 10 ){
		nSelect = 0;
		cout << "\a(1~9)�̂����ꂩ����͂��Ă��������B" << endl;
		cin >> nSelect;
	}

	board.Set(nSelect,bTurn);
}

//�Ֆʂ�����������
void Board::Clear(){
	for (int i = 0; i < 9; i++){
		nBorad[i] = 0;
	}
}

//�w�肳�ꂽ�ӏ��ɃZ�b�g����B
void Board::Set(int n,bool turn)
{


	if (turn){ //�v���C���[

	}
	else{  //COM

	}
}