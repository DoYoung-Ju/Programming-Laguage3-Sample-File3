#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <iomanip>
#include <Windows.h>
#include <fstream>
#include <vector>
using namespace std;

class Student //class 및 function 설계 박진우(각자 맞은 부분 표시 예시)
{
	int num;
	string name;
	int score_k;
	int score_e;
	int score_m;
	int sum_s;
	//double avr_s;
	int rank_k;
	int rank_e;
	int rank_m;
public:
	Student() {
		num = 0, name = "honggildong", score_k = 0, score_e = 0, score_m = 0;
		sum_s = 0, /*avr_s = 0, */rank_k = 1, rank_e = 1, rank_m = 1;
	}
	Student(int n_n, string NN, int s_k, int s_e, int s_m, int s, /*double a, */int r_k, int r_e, int r_m)
	{
		num = n_n, name = NN, score_k = s_k, score_e = s_e, score_m = s_m;
		rank_k = r_k, rank_e = r_e, rank_m = r_m;
	};
	
	void showmenu();
	void gotoxy(int x, int y);
	void set_name();
	void set_score();

	void input_data();
	void find_data();
	void output_data();
	void fix_data();
	friend bool operator<(Student a, Student b); // 연산자 < 중복함수
	friend void operator>>(istream& in, Student& a);
	friend void operator<<(ostream& out, Student& a);

};

inline void operator<<(ostream& out, Student& a)
{
	out << a.num << " " << a.name << " " << a.score_k << " " << a.score_e << " " << a.score_m << " " << a.sum_s << " " /*<< a.avr_s */<< a.rank_k << " " << a.rank_e << " " << a.rank_m << endl;
}

inline void operator>>(istream& in, Student& a)
{
	in >> a.num >> a.name >> a.score_k >> a.score_e >> a.score_m >> a.sum_s /*>> a.avr_s */>> a.rank_k >> a.rank_e >> a.rank_m;
}

void Student::showmenu() {
	int sel;
	srand(time(NULL));
	do {
		//gotoxy(0, 0);
		cout << "1.Data input" << endl;
		cout << "2.Data search" << endl;
		cout << "3.Data output" << endl;
		cout << "4.Update data" << endl;
		cout << endl;
		cout << "0.End of task" << endl;

		cout << "Required[ ]";

		gotoxy(9, 6); cin >> sel;

		system("cls"); //clear screen
	} while (sel < 0 || sel>4);
	if (sel == 0)
		exit(0);
	else {
		cout << sel << "번 메뉴입니다." << endl;
		switch (sel) {
		case 1: input_data(); break;
		case 2: find_data(); break;
		case 3: output_data(); break;
		case 4: fix_data(); break; //자료 수정 함수가 필요함
		}//메뉴 선택 조건문
	}
}
void Student::gotoxy(int x, int y) {
	COORD pos = { (short)x,(short)y }; //x, y 좌표 설정
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos); //커서 설정
}
void Student::set_name() {
	string fn[] = { "홍","정","김","이","박" };
	string sn[] = { "도현", "현수","주화","수현","영수" };
	//srand(time(NULL));
	name = fn[rand() % 5] + sn[rand() % 5];//이름 랜덤 생성하기 기초
}
void Student::set_score() { //  한꺼번에 클래스 변수 변경
	score_k = rand() % 101;
	score_e = rand() % 101;
	score_m = rand() % 101;
	sum_s = score_k + score_e + score_m;
	/*avr_s = (score_k + score_e + score_m) / 3.0;*/
}


void Student::input_data() {
	ofstream fout("info.bin", ios::binary);
	int n = 10;
	//fout.write((char*)&n, sizeof(n)); //자료 수 만큼 읽어 오기
	fout << n << endl;
	Student* info = new Student[n];
	for (int i = 0; i < n; i++) {//한꺼번에 클래스 변수 변경
		info[i].num = i + 1;
		info[i].set_name();
		info[i].set_score();
	}
	for (int i = 0; i < n; i++) //과목별 순위 매기기
		for (int j = 0; j < n; j++) {
			if (info[i].score_k < info[j].score_k)
				info[i].rank_k++;
		}
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++) {
			if (info[i].score_e < info[j].score_e)
				info[i].rank_e++;
		}
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++) {
			if (info[i].score_m < info[j].score_m)
				info[i].rank_m++;
		}
	sort(info, info + 10);
	for (int i = 0; i < n; i++) {
		fout << info[i];
	}
	delete[] info;
	fout.close();
}
void Student::find_data() // 통궈칭 설계
{
	ifstream fin("info.bin", ios::binary);
	int n = 10;
	int i = 0;
	string key;
	cout << "Please enter a name to find：" << endl;
	cin >> key;
	//fin.read((char*)&n, sizeof(n));// 자료수 만큼 읽기오기
	//Student* info = new Student[n];
	//fin.read((char*)info, n * sizeof(Student));
	//for (i = 0; i < n && info[i].name != key; ++i);
	//if (info[i].name == key) {}
	fin >> n;
	Student* info = new Student[n];
	for (int i = 0; i < n; i++) {
		fin >> info[i];
	}
	while (i < n)
	{
		if (info[i].name == key) {
			printf("%2d", info[i].num);
			cout << "번호" << " " << "학생이름" << " " << "	  국어" << " " << " 영어" << " " << " 수학" << " "
				<< "합계" << " " /*<< "평균" << " " */<< "수학순위" << " " << "영어순위" << " " << "국어순위" << endl;
			cout << "    " << info[i].name << setw(8) << info[i].score_k << setw(6) << info[i].score_e << setw(6)
				<< info[i].score_m << setw(5) << info[i].sum_s << /*setw(5) << info[i].avr_s << */setw(6) << info[i].rank_m << setw(9)
				<< info[i].rank_e << setw(9) << info[i].rank_k << endl;
			break;
		}
		++i;
	}
	if (i == 10) {
		cout << "unknown." << endl;
	}
	delete[] info;
	fin.close();

}
void Student::output_data()
{
	ifstream fin("info.bin", ios::binary);
	int n = 10;
	//fin.read((char*)&n, sizeof(n));// 자료수 만큼 읽기오기
	//Student* info = new Student[n];
	//fin.read((char*)info, n * sizeof(Student));//한꺼번에 클래스 배열 쓰기
	fin >> n;
	Student* info = new Student[n];
	for (int i = 0; i < n; i++) {
		fin >> info[i];
	}
	//간격을 일정하게 맞춰야 함
	cout << "번호" << " " << "학생이름" << " " << "	  국어" << " " << " 영어" << " " << " 수학" << " "
		<< "합계" << " " /*<< "평균" << " " */ << "수학순위" << " " << "영어순위" << " " << "국어순위" << endl;
	for (int i = 0; i < n; i++) {
		printf("%2d", info[i].num);
		cout << "    " << info[i].name << setw(8) << info[i].score_k << setw(6) << info[i].score_e << setw(6)
			<< info[i].score_m << setw(5) << info[i].sum_s << /*setw(5) << info[i].avr_s << */setw(6) << info[i].rank_m << setw(9)
			<< info[i].rank_e << setw(9) << info[i].rank_k << endl;
	}
	delete[] info;
	fin.close();
}
/*
int idx = 0;
int searchOthers = 0;
int cache[101][101];

bool checkMatching(vector<char>& target, string& word, int tp, int wp) {
	int& ret = cache[tp][wp];
	if (ret != -1) return ret;
	// tp: 현재 target의 몇번째 문자를 검사 중인지
	// wp: 현재 word의 몇번째 문자를 검사 중인지
	while (tp < target.size() && wp < word.size() && (target[tp] == '?' || target[tp] == word[wp])) {
		// ?일 때
		// 문자가 서로 같을 때
		// 아직 target과 word 둘 다 끝까지 안봤을 때
		tp++; wp++;
	}
	if (tp == target.size())
		return wp == word.size();
	if (target[tp] == '*') {
		for (int i = 0; i <= word.size() - wp; i++) {
			if (checkMatching(target, word, tp + 1, wp + i))
				return true;
		}
	}
	return false;
}
*/
void Student::fix_data()//김규형 설계(통쿼칭 코드 부분참조함)
{
	ifstream fin("info.bin", ios::binary);
	ofstream fout("info.bin", ios::binary);
	int n = 10;
	int i = 0;
	int set_num[10] = { 0 };
	int a = 0;//set_num에 중복되는 이름 저장
	int num;
	int cont = 0;
	int change=0;
	string key;
	string sub;
	string newn;
	cout << "Please enter a name to find：" << endl;
	cin >> key;
	fin.read((char*)&n, sizeof(n));// 자료수 만큼 읽어오기
	Student* info = new Student[n];
	fin.read((char*)info, n * sizeof(Student));
	//for (i = 0; i < n && info[i].name != key; ++i);
	//if (info[i].name == key) {}
	fin >> n;
	Student* strcpy_info = new Student[n];
	for (int i = 0; i < n; i++) {
		fin >> info[i];
	}
	while (i < n)
	{
		if (info[i].name == key) {
			set_num[a] = i;
			a++;
			break;
		}
		++i;
	}
	if (i == 10) {
		cout << "unknown." << endl;
	}
	for (int i = 0; i < a; i++)
	{
		cout << a + 1 << " 번 학생" << endl;
		cout << "Student number" << " " << "name" << "Mandarin achievement" << " " << "English achievement" << " " << "Mathematics achievement" << " "
			<< "Total score" << " " << "Mathematical ranking" << " " << "English ranking" << " " << "Mandarin ranking" << endl;
		cout << info[set_num[i]].num << " " << info[set_num[i]].name << " " << info[set_num[i]].score_k << " " << info[set_num[i]].score_e << " "
			<< info[set_num[i]].score_m << " " << info[set_num[i]].sum_s << " " << info[set_num[i]].rank_m << " " << info[set_num[i]].rank_e << " "
			<< info[set_num[i]].rank_k << endl;

	}
	do {
		do {
			cout << "수정할 학생의 번호를 입력하십시오: ";
			cin >> num;
			num = num - 1;
			if (num > a || num < 0)
			{
				cout << "없는 번호입니다. 다시 입력하십시오";

			}
			else
			{
				break;
			}

		} while (1 == 0);
		cout << "수정할 내용을 입력하십시오";
		cin >> sub;
		if (sub == "Student number")
		{
			cout << "새 번호를 입력하십시오 ";
			cin >> change;
			info[set_num[num]].num = change;
		}
		else if (sub == "name")
		{
			cout << "새 이름을 입력하십시오: ";
			cin >> newn;
			info[set_num[num]].name = change;
		}
		else if (sub == "Mandarin achievement")
		{
			cout << "새 국어 성적을 입력하십시오: ";
			cin >> change;
			info[set_num[num]].score_k = change;
		}
		else if (sub == "English achievement")
		{
			cout << "새 영어성적을 입력하십시오: ";
			cin >> change;
			info[set_num[num]].score_e = change;
		}
		else if (sub == "Mathematics achievement")
		{
			cout << "새 수학성적을 입력하십시오: ";
			cin >> change;
			info[set_num[num]].score_m = change;
		}
		else
		{
			cout << "wrong input";
		}

		cout << "계속 수정하겠다면 1번을, 아니라면 0번을 입력하십시오";
		cin >> cont;
		if (cont == 0)
		{
			sort(info, info + 10);
			for (int i = 0; i < n; i++) {
				fout << info[i];
			}
		}

	} while (cont == 1);
	delete[] info;
	fin.close();
	fout.close();
}
bool operator<(Student a, Student b) {
	if (a.rank_k == b.rank_k) {
		if (a.rank_e == b.rank_e)
			return a.rank_m < b.rank_m;
		else
			return a.rank_e < b.rank_e;
	}
	else
		return a.rank_k < b.rank_k; //국어 ,수학,영어 순위 순으로 정렬
}
