// �O�����Z�q��p�����}���o�c�Q�[�������

#include<iostream>
using namespace std;

enum State{
	NONE, //��}�X(0)
	MARU, //�v���C���[(1)
	BATSU //�G�}�X(2)
};

enum Turn{
	PLAYER,
	ENEMY
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
Turn T = PLAYER; //�v���C���[,COM
bool is_End = true;


Board board;

int main(void){
	// �Ֆʂ�����������
	board.Clear();

	//���s�����܂�܂Ŗ������[�v
	do{
		PlayerTurn();
	//	if (board.Check()){ bGameSet = true;  break; }
		EnemyTurn();
	//	if (board.Check()){ bGameSet = true; break; }
	}while (!bGameSet);

	//gameResult(); //���ʔ��\

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
	while (nSelect <= 0||nSelect >= 10){
		nSelect = 0;
		cout << "\a(1~9)�̂����ꂩ����͂��Ă��������B" << endl;
		cin >> nSelect;
	}

	while (board.Set(nSelect, T) == 1){
		cout << "1~9�̂����ꂩ����͂��Ă��������B" << endl;
		cin >> nSelect;
	}
}

//COM���̏���
void EnemyTurn(){
	T = ENEMY;
	int nSelect = 5;
	cout << "COM�̃^�[���ł��B"  << endl;
	cout << "COM��" << nSelect << "�Ԃ�I�����܂����B" << endl;
	board.Set(nSelect, T);
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
	if (nBorad[n-1] == MARU || nBorad[n-1] == BATSU){
		cout << "�c�O�Ȃ��炻���ɂ͒u���܂���B" << endl;
		return 1;
	}

	if (T == PLAYER){ //�v���C���[
		nBorad[n-1] = MARU;
	}
	else{  //COM
		nBorad[n-1] = BATSU;
	}
	return 0;
}