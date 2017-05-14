#include <iostream>
#include <fstream>
#include <string> 
#include <algorithm>
#include <iomanip> 
#include <vector>
#include <cstdlib>
#include <climits> 
#include <cmath> 

using namespace std;
int N,N1;
float m,S, K, q, sigma_l, sigma_h;
vector < vector<float> > p;//������� ���������� ������������ probability
vector < vector<int> >  koef; //-+1
vector<float> vol;//�������������  - ��� ��������� �����

void read_task() {
	ifstream file;
	file.open("input.txt");
	file >> N >> m >> S >> K >> sigma_l >> sigma_h;
	//��������� ������ ��� ������� � �������
	p = vector < vector<float> >(N, vector<float>(N, 0));
	koef = vector < vector<int> >(pow(2, N), vector<int>(N, 0));
	vol = vector<float>(N);
	//������ ������� ���������� ������������
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++) {
			file >> p[i][j];
		}
	file.close();
}

void fill_koef(int n) {
	int k1 = pow(2, n);  //2^N
	ofstream file2("output1.txt");
	
	for (int i = 0; i < k1; i++) {
		int j = i;
		int k3 = 0;
		file2.fill('0'); 
		while (j != 0)
		{	
			file2 << j % 2;
			j /= 2;
			k3++;
		}
		file2 << setw(N - k3);
		file2 << j << endl;
	}
	file2.close();

ifstream file3;
file3.open("output1.txt");
//��������� ������� +-1
	for (int i = 0; i < k1; i++) {
		//���������� �� ��� ����� - ����� ������ ����� � �����
		if (i < pow(2, n - 1)) {
			for (int j = 0; j < n; j++) {
				char s1;
				file3 >> s1;
				if (s1 == '1')
					koef[i][j] = 1;
				if (s1 == '0')
					koef[i][j] = -1;
			}
		}
		else {
			for (int j = 0; j < n; j++) {
				char s1;
				file3 >> s1;
				if (s1 == '1')
					koef[i][j] = 1;
				if (s1 == '0')
					koef[i][j] = -1;
			}
			file3.ignore();		
		}
	}
	file3.close();	
}
//������ ��������������
void fill_vol(float s1, float s2) {
	float h = (s2 - s1) / (N - 1);
	vol[0] = s1;
	for (int i = 1; i < N;  i++) {
		vol[i] = vol[i - 1] + i*h;
	}
}
//������� ���������� ��������� - ����� ����� ���� ����
float f(float x) {
	double res = x - K;
	res = max(res, 0.0);
	return res;
}
//������ ���.��������
/*
void calculation (vector <float> vol){
	float m1 = m + 1;
	float n = 1 / (pow(2, N));
	float Expectancy = ;

}
*/


int main() {
	read_task();//������� ��� ��� ����� �� �����
	fill_koef(N); //�������
	fill_vol(sigma_l, sigma_h); //������ ��������������
	calculation(vol); //���������� ���������� + ������ ���������� � ����

	return 0;
}



 