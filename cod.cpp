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
vector<float> vol;//волатильность  - все возможные сигмы
vector <float> help; //чтобы облегчить себе жизнь при подсчете матожидания
vector<int> p_s;
vector<float> A; //вектор коэффициентов, которые сравниваем в конце
vector<float> Expectancy;
vector<float> A1; //вспомогательный вектор для расчета A[i]
vector<float> sum_vec;
//вспомогательные данные для перебора всех возможных векторов волатильности
int h;
vector<int> ind;
vector<int> ind_true;

vector<float> vol_help;


void read_task() {
	ifstream file_in;
	file_in.open("input.txt");
	file_in >> N >> m >> S >> K >> sigma_l >> sigma_h;
	//выделение памяти под векторы и матрицы
	p = vector < vector<float> >(N, vector<float>(N, 0));
	koef = vector < vector<int> >(pow(2, N), vector<int>(N, 0));
	A = vector <float>(N);
	A1 = vector <float>(pow(N, N)); //ветор, состоящий из произведений переходных вероятностей - каждой цепочке будет соответствовать свой коэф-т
	Expectancy = vector <float>(pow(N, N));
	ind = vector<int>(100000);
	ind_true = vector<int>(100000);
	vol = vector<float>(N);
	vol_help = vector<float>(N);
	sum_vec = vector <float>(N);

	//чтение матрицы переходных вероятностей
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++) {
			file_in >> p[i][j];
		}
	file_in.close();
}

void fill_koef(int n) {
	int k1 = pow(2, n);  //2^N
	ofstream file2("output1.txt");  //удалять нельзя - колдунство с 1 и -1
	
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

//вектор волатильностей (sigma_l...sigma_h)
void fill_vol(float s1, float s2) {
	float h = (s2 - s1) / (N - 1);
	vol[0] = s1;
	for (int i = 1; i < N;  i++) {
		vol[i] = vol[i - 1] + h;
	}
}
//перебираем все векторы волатильностей - шаманство, тут именно индексы   - 	comb(N, 0); - вызов
ofstream file("output111.txt"); //вспомогательный файл - нужен, чтобы потом из него считывать индексы... тут от 1 до N,  запомнить - чтобы вычитать 1!!!!!!
void comb(int n, int t) {
	if (t == n) {
		for (int i = 0; i < n; i++) {
			ind_true[h] = ind[i]; ++h;
			file << ind[i] << " ";
		}
		file << endl;
		return;
	}
	for (int i = 1; i <= n; i++) {
		ind[t] = i;
		comb(n, t + 1);
	}
}

void comb_true() {
	comb(N, 0);
	int c = 0;
	for (int i = 0; i < h; ++i) {
		if (c < N)
			 ++c;
		else 
			c = 1;
	}	
	file.close();
}

//функция нахождения максимума - чтобы проще было жить
float f(float x) {
	double res = x - K;
	res = max(res, 0.0);
	return res;
}


//перебираем все векторы волатильности и тут же расчет мат.ожидания и определяем наши коэф-ты А[i]
ofstream f2("output2.txt");

void calculation(vector <float> v) {
	int NN = pow(N, N);
	int N_1 = pow(N, N - 1);
	int s;
	int N1 = pow(2, N);
	float m1 = m + 1;
	float st = 1.0 / N1;
	help = vector<float>(N1);
	p_s = vector<int>(N);
	
	ifstream file_help;
	ofstream  ff("fu.txt");
	ofstream  fil("control.txt");
	ofstream  file_out("output.txt");
	file_help.open("output111.txt");
	A1.assign(pow(N, N), 1);
	
	for (int i = 0; i < NN; i++) {

		for (int j = 0; j < N; j++) {
			file_help >> s;
			vol_help[j] = v[s - 1];
			ff << vol_help[j] << ' ';
			p_s[j] = s - 1;

		}
		ff << endl;
		//отдельно считаем коэф=ты так как знаем в каком порядке рассматриваются наши векторы!!!!  

		for (int t = 1; t < N; t++) {
			A1[i] *= p[p_s[t]][p_s[t - 1]];
		}

		//построили вектор волатильности и теперь с ним работаем
		help.assign(N1, 1);
		for (int i1 = 0; i1 < N1; i1++) {
			float current;
			for (int j1 = 0; j1 < N; j1++) {
				current = (m1 + vol_help[j1] * koef[i1][j1]);
				help[i1] *= current;
			}	
		}

		float sum = 0;
		for (int i2 = 0; i2 < N1; i2++) {
			help[i2] = f(S * help[i2]); //находим максимум "поэлеметно"
			sum += help[i2];
			f2 << help[i2] << ' ';
		}

		f2 << endl << sum << endl;
		Expectancy[i] = st * sum;
		f2 << endl << Expectancy[i] << endl << endl;
	}

	//печать для проверки
	for (int k =0; k < pow(N,N);k++)
		fil << A1[k] <<' ';
	fil << endl;
	for (int k = 0; k < pow(N, N); k++)
		fil << Expectancy[k] << ' ';
	fil << endl;
	for (int k = 0; k < pow(N, N); k++)
		fil << A1[k] * Expectancy[k] << ' ';
	fil << endl;

	//осталось вывести сам вектор А и найти в нем минимум и максимум - используем файл ибо проще
	ofstream  ff_help("f_h.txt");

	int k_h = 0;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N_1; j++) {
			A[i] += A1[j + k_h] * Expectancy[j + k_h];
		}
		k_h += N_1;
		ff_help << A[i] << ' ';
	}


	float max_A = *max_element(A.begin(), A.end());
	float min_A = *min_element(A.begin(), A.end());
	//подумать над итератором, чтобы вернуть номер мин и мах элемента

	auto it_max = max_element(A.begin(), A.end());
	auto it_min = min_element(A.begin(), A.end());

	file_out << "max" << ' ' << max_A << endl;
	int it_i = 0;
	for (auto it = A.begin(); it < A.end(); it++) {
		if (it == it_max) file_out << it_i << endl;
		it_i++;
	}

	file_out << "min" << ' ' << min_A << endl;
    it_i = 0;
	for (auto it = A.begin(); it < A.end(); it++) {
		if (it == it_min) file_out << it_i << endl;
		it_i++;
	}
	
	file_help.close(); //нужен, удалять нельзя - "кодовый замок outut111" 
	ff.close();  //можно удалять fu смотрим на все возможные векторы вол.
	fil.close(); //control можно удалить, но красивенько смотрим что вообще происходит
	file_out.close(); // ВЫВОД
	ff_help.close(); //можно удалять - только для печати A[i] -- "f_h"
	f2.close(); //тоже можно удалить - для красоты и контроля output2

}

int main() {
	read_task();//считали все что могли из файла
	fill_koef(N); //матрица
	fill_vol(sigma_l, sigma_h); //вектор волатильностей
	comb_true(); //все возможные векторы волатильностей пока что индексы
	calculation(vol); //перебираем векторы + считаем h от всех вариантов (sigma_1.....sigma_n)

	system("pause");
	return 0;
}