#include <iostream>
#include <fstream>
#include <string> 
#include <algorithm>
#include <iomanip> 
#include <vector>
using namespace std;
int N;
float m, q, sigma_l, sigma_h;
vector<int> ans;

void fill(int n, string s) {
	ofstream file2("output.txt");
	if (n == 0) {
		file2 << s << endl;
	}
	else {
		fill(n - 1, s + "0");
		fill(n - 1, s + "1");
	}
	file2.close();	
}


int main() {
	fstream file;
	file.open("input.txt");
	file >> N;
	file.close();
	fill(N, "");

}

/*

void main() {
	int j, K;
	string s1, s2;

	fstream file;
	file.open("input.txt");
	file >> N;
	file.close();

	ofstream file2("output.txt");
	
	/*s1 = '0';

	for (int i = 0; i < N; i++) {
		s1 = s1 + '0';
		file2 << s1 << endl;
	}
	*/

/*
	for (int i = 0; i < N; i++) {
		j = i;
		while (j > 0)
		{
			file2 << setw(2) << setfill('0') << j % 2;
			j /= 2 ;
		}
		file2 <<  endl;
}

	file2.close();


}

*/