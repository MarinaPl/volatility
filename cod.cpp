#include <iostream>
#include <fstream>
#include <string> 
#include <algorithm>
#include <iomanip> 


using namespace std;






int main(){
	int N , j, k; 
	float m, q, sigma_l, sigma_h;
	string s1, s2;

	fstream file;
	file.open("input.txt");
	file >> N;
	file.close();
	//s1 = '0';

	ofstream file2("output.txt");
	//���� ��� 2^N ����������
	/*for (int i = 0; i < N;  i++) {
		s1 = s1 + '0';
	}*/
//������� �� �� �����!!!! ����� �� � ������������������, � �������� ���� ������
	


	/*for (int i = 0; i < N; i++) {
		s1 = s1 + '0';

		file2 << s1 << endl;
	}
	*/

	file2.close();


}