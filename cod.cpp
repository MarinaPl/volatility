#include <iostream>
#include <fstream>
#include <string> 
#include <algorithm>
#include <iomanip> 
#include <vector>
#include <cstdlib>

using namespace std;
int N;
float m, q, sigma_l, sigma_h;
vector<int> ans;

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
}


	/*
	void fill(int n, string s) {
	if (n == 0) {
		file2 << s << endl;
	}
	else {
		fill(n - 1, s + "0");
		fill(n - 1, s + "1");
	}*/

//	file2.close();


int main() {
	fstream file;
	file.open("input.txt");
	file >> N;
	file.close();
	fill(N);
	return 0;
	//заполнили промежуточный файл всеми комбинациями, теперь нужно из него вытащить каждый 0 и 1 в коэфф.
}



 