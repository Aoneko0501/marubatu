// �O�����Z�q��p�����}���o�c�Q�[�������

#include<iostream>
using namespace std;

enum State{
	NONE, //��}�X(0)
	PLAYER, //�v���C���[(1)
	ENEMY //�G�}�X(2)
};

struct Board{
public:
	void Clear(); //�Ֆʂ�������
	void Show(); //�Ֆʂ�\��
	int Set(int n,bool turn); //�ՖʂɃZ�b�g
	int Check(); //���s����
protected:
	State nBorad[9];//�Ֆ� 
};

void PlayerTurn(); //�v���C���[
void EnemyTurn();//�G
void gameResult(); //���ʔ��\

bool bGameSet = false;
bool Turn = true; //(true):�v���C���[,(false):COM
bool is_End = true;


Board board;

int main(void){
	// �Ֆʂ�����������
	board.Clear();

	//���s�����܂�܂Ŗ������[�v
	do{
		PlayerTurn();
	//	if (board.Check()){ bGameSet = true;  break; }
	//	EnemyTurn();
	//	if (board.Check()){ bGameSet = true; break; }
	}while (!bGameSet);

	//gameResult(); //���ʔ��\

	return 0;
}

//�v���C���[�̏���
void PlayerTurn()
{
	int nSelect = 0;
	cout << "���Ȃ��̃^�[���ł��B\n�ǂ̈ʒu��I�����܂����H(1~9)" << endl;
	board.Show();

	cin >> nSelect;
	while (nSelect <= 0||nSelect >= 10){
		nSelect = 0;
		cout << "\a(1~9)�̂����ꂩ����͂��Ă��������B" << endl;
		cin >> nSelect;
	}

	while (board.Set(nSelect, Turn) == 1){
		cout << "1~9�̂����ꂩ����͂��Ă��������B" << endl;
		cin >> nSelect;
	}
}

//COM���̏���
void EnemyTurn(){
	int nSelect = 0;
	cout << "COM�̃^�[���ł��B" << endl;



	board.Set(nSelect, Turn);
}

//�Ֆʂ�����������
void Board::Clear(){
	for (int i = 0; i < 9; i++){
		nBorad[i] = NONE;
	}
}

//�Ֆʂ�\��
void Board::Show(){
	cout << nBorad[0] <<"�b" << nBorad[1]<< "�b"<< nBorad[2]<<endl;
	cout << "-" << "�{" << "-" << "�{" << "-" << endl;
	cout << nBorad[3] << "�b" << nBorad[4] << "�b" << nBorad[5] << endl;
	cout << "-" << "�{" << "-" << "�{" << "-" << endl;
	cout << nBorad[6] << "�b" << nBorad[7] << "�b" << nBorad[8] << endl;
}

//n�ԖڂɃZ�b�g����B
int Board::Set(int n,bool turn)
{
	if (nBorad[n-1] == PLAYER || nBorad[n-1] == ENEMY){
		cout << "�����ɂ͒u���܂���B" << endl;
		return 1;
	}

	if (turn){ //�v���C���[
		nBorad[n-1] = PLAYER;
	}
	else{  //COM
		nBorad[n-1] = ENEMY;
	}
	return 0;
}