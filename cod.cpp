#include <iostream>
#include <fstream>
#include <string> 
#include <algorithm>
#include <iomanip> 
#include <vector>
#include <cstdlib>
#include <bitset> 
#include <climits> 
#include <cmath> 


using namespace std;
int N,N1;
float m, q, sigma_l, sigma_h;
vector < vector<int> > p;//матрица переходных вероятностей probability
vector < vector<int> >  koef; //-+1
vector<int> vol;//волатильность  - все возможные сигмы


void fill(int n) {
	int k1 = pow(2, n);  //2^N
	ofstream file2("output.txt");
	
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
		//file2 << k3<< endl;		
	}
	file2.close();

	//до этого момента работает

ifstream file3;
file3.open("output.txt");
ofstream file4("fuck.txt");  //для проверки - его потом дропнуть
//заполняем матрицу +-1
	for (int i = 0; i < k1; i++) {
		//разделение на две части - чтобы убрать косяк с нулем
		if (i < pow(2, n - 1)) {
			for (int j = 0; j < n; j++) {
				char s1;
				file3 >> s1;
				if (s1 == '1')
					koef[i][j] = 1;
					//file4 << 1;
				if (s1 == '0')
					koef[i][j] = -1;
					//file4 << -1;
				file4 << koef[i][j];
			}
		}
		else {
			for (int j = 0; j < n; j++) {
				char s1;
				file3 >> s1;
				if (s1 == '1')
					koef[i][j] = 1;
					//file4 << 1;
				if (s1 == '0')
					koef[i][j] = -1;
					//file4 << -1;
				file4 << koef[i][j];
			}
			file3.ignore();
			
		}
		//file3 >> endl;
		file4 << endl;
	}

	file3.close();
	
}



int main() {
	ifstream file;
	file.open("input.txt");
	file >> N;
	file.close();

	//выделение памяти под векторы
	p = vector < vector<int> >(N, vector<int>(N, 0));
    koef = vector < vector<int> >(pow(2, N), vector<int>(N, 0)); //сама матрица - выделение памяти
	vol = vector<int>(N);

	fill(N); 
	//

	return 0;
	
}



 