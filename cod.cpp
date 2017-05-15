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
int N;
float m,S, K, q, sigma_l, sigma_h;
vector < vector<float> > p;//матрица переходных вероятностей probability
vector < vector<int> >  koef; //-+1
vector<int> ind;  //вспомогательный для всех возможных волатильностей
vector<float> vol;//волатильность  - все возможные сигмы
vector <float> help; //чтобы облегчить себе жизнь при подсчете матожидания

void read_task() {
	ifstream file;
	file.open("input.txt");
	file >> N >> m >> S >> K >> sigma_l >> sigma_h;
	//выделение памяти под векторы и матрицы
	p = vector < vector<float> >(N, vector<float>(N, 0));
	koef = vector < vector<int> >(pow(2, N), vector<int>(N, 0));
	ind = vector<int>(N);
	vol = vector<float>(N);
	//чтение матрицы переходных вероятностей
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
//заполняем матрицу +-1
	for (int i = 0; i < k1; i++) {
		//разделение на две части - чтобы убрать косяк с нулем
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
//вектор волатильностей
void fill_vol(float s1, float s2) {
	float h = (s2 - s1) / (N - 1);
	vol[0] = s1;
	for (int i = 1; i < N;  i++) {
		vol[i] = vol[i - 1] + i*h;
	}
}
//перебираем все векторы волатильностей - шаманство, тут именно индексы   - 	comb(N, 0); - вызов
void comb(int n, int t){
	ofstream f2("fuck.txt");

	if (t == n){
		for (int i = 0; i < n; i++)
			f2 << ind[i] << " ";
		f2 << endl;
		return;
	}
	for (int i = 1; i <= n; i++){
		ind[t] = i;
		comb(n, t + 1);
	}
}
//функция нахождения максимума - чтобы проще было жить
float f(float x) {
	double res = x - K;
	res = max(res, 0.0);
	return res;
}
//расчет мат.ожидания
void calculation (vector <float> vol){
	int N1 = pow(2, N);
	float m1 = m + 1;
	float st = 1.0 / N1;

	ofstream f2("output2.txt");
	help = vector<float>(N1, 1);

	for (int i = 0; i < N1; i++) {
		float current;
		for (int j = 0; j < N; j++) {
			current = (m1 + vol[j] * koef[i][j]);
			help[i] *= S * current; 
		}
	}
	float sum = 0;
	for (int i = 0; i < N1; i++) {
		help[i] = f(help[i]);
		sum += help[i];
		f2 << help[i] << ' ' ;
	}
	f2 <<  endl << sum << endl << st;
	float Expectancy = st * sum;
	f2 << endl << Expectancy;
}

int main() {
	read_task();//считали все что могли из файла
	fill_koef(N); //матрица
	fill_vol(sigma_l, sigma_h); //вектор волатильностей
	calculation(vol); //собственно вычисления + запись результата в файл
	comb(N, 0);
	system("pause");
	return 0;
}



 