#include <iostream>
using namespace std;
int liczba_uczni;
int liczba_cukierkow;
int a;
int b;

int main()
{
	cout << "Ile masz osob w klasie?: ";
	cin >> liczba_uczni;
	cout << "Ile masz cukierkow?: ";
	cin >> liczba_cukierkow;
	a = liczba_cukierkow / (liczba_uczni-1);
	cout << "Dla kazdego ucznia bedzie przypadac " << a << " cukierkow." << endl;
	b = liczba_cukierkow % liczba_uczni;
	cout << "Zostanie Ci " << b << " cukierkow.";
}