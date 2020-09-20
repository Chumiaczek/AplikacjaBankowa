//includes to add libraries
#include <iostream>
#include <stdio.h>
#include <cstdlib>
#include <conio.h>
#include <windows.h>
#include <fstream>
#include <string>
#include <algorithm>
using namespace std;
string pin, PIN;
char wybor;
int ilosc_wplata, ilosc_wyplata;
int status;

//defining that there are other processes
void menu();
int main();

//process that checks if your pin is right
void jaki_pin()
{
	//opening txt file
	fstream plik;
	plik.open("pin.txt", ios::in);
	//checking if file exists
	if(plik.good() == false)
	{
		cout << "Podany plik nie istnieje!";
		exit(0);
	}
	//getting info from txt lines
	string linia;
	while (getline(plik, linia))
	{
		pin = linia;
	}
	//closing files
	plik.close();
	int i = 1;
	//asking for pin from user
	cout << "Podaj numer PIN: ";
	cin >> PIN;
	//checking if pin is right, if not, than give 2 more tries and locks app
	if (PIN == pin)
	{
		cout << "Poprawny numer PIN!";
	}
	else
	{
		while (i <= 2)
		{
			cout << "Niepoprawny PIN! Sprobuj ponownie"<<endl;
			cout << "Podaj numer PIN: ";
			cin >> PIN;
			if (PIN == pin)
			{
				cout << "Poprawny numer PIN!";
				i = 4;
			}
			else
			{
				i++;
			}
		}
	}
	//locking app
	if(i==3)
	{
		cout << endl << "Kod pin podany trzykrotnie niepoprawnie, zablokowano karte na 5 minut" << endl;
		Sleep(300000);
		cout << "Otwórz program ponownie!";
		exit(0);
	}

}

//process for deposits
void wplata()
{
	//clearing terminal window
	system("cls");
	string linia;
	//asking for how much do user want to deposit
	cout << "Ile chcesz wplacic: ";
	cin >> ilosc_wplata;
	//opening txt file
	fstream plik;
	plik.open("saldo.txt", ios::in);
	//checking if file exists
	if (plik.good() == false)
	{
		cout << "Podany plik nie istnieje!";
		exit(0);
	}
	//getting line from txt file
	while (getline(plik, linia))
	{
		status = atoi(linia.c_str());
	}
	//closing file
	plik.close();
	//adding the value from file value of deposit
	status = status + ilosc_wplata;

	//opening txt file and assigning new value
	plik.open("saldo.txt", ios::out);
	plik << status << endl;
	plik.close();

	//getting user back to menu
	cout << "Pomyslnie wplacono sume, za 3 sekundy nastapi przeniesienie do menu glownego.";
	Sleep(3000);
	menu();
}

//process for withdraw
void wyplata()
{
	int i = 0;
	//clearing terminal window
	system("cls");
	string linia;
	//opening txt file
	fstream plik;
	plik.open("saldo.txt", ios::in);
	//checking if file exists
	if (plik.good() == false)
	{
		cout << "Podany plik nie istnieje!";
		exit(0);
	}
	//geting line from txt code
	while (getline(plik, linia))
	{
		status = atoi(linia.c_str());
	}
	plik.close();

	//asking for how much does user want to withdraw
	cout << endl <<"Ile chcesz wyplacic: ";
	cin >> ilosc_wyplata;
	//if you want to withdraw more than you have, or you trying to withdraw less than 10zl, it will block user from it
	while (i <= 2)
	{
		if(ilosc_wyplata<10)
		{
			cout << "Ilosc wyplaconych pieniedzy jest mniejsza niz 10zl, prosimy sprobowac ponownie";
			Sleep(3000);
			wyplata();
		}
		else if (ilosc_wyplata > status)
		{
			cout << "Zadana wartosc jest wieksza niz twoje saldo konta, prosimy sprobowac ponownie";
			Sleep(3000);
			wyplata();
		}
		else
		{
			i = 3;
		}
	}
	cout <<endl<< "Trwa przetwarzanie platnosci...";
	//lowering the value of your account with how much does user wants to withdraw
	status = status - ilosc_wyplata;
	plik.open("saldo.txt", ios::out);
	plik << status << endl;
	plik.close();

	//getting back to menu
	Sleep(3000);
	cout << endl << "Platnosc zostala pomyslnie przetworzona! Pieniadze zostaly wyplacone!" << endl << "Za 3 sekundy nastapi powrot do menu!";
	Sleep(3000);
	menu();

}
//transaction proccess
void transfer()
{
	int kwota;
	int n = 0;
	//clearing terminal window
	system("cls");
	string nr_karty;
	string linia;
	//opening txt file
	fstream plik;
	plik.open("saldo.txt", ios::in);
	//checking if file exists
	if (plik.good() == false)
	{
		cout << "Podany plik nie istnieje!";
		exit(0);
	}
	//geting line from txt file and converting it to int
	while (getline(plik, linia))
	{
		status = atoi(linia.c_str());
	}
	plik.close();
	
	//asking for card number
	cout << "Podaj numer karty: ";
	cin >> nr_karty;
	//checking how long is this number, if less than 16 chars, it will not let it go
	int length = nr_karty.length();
	if (length < 16 || length > 16)
	{
		cout << endl << "Numer karty jest za krotki, sprobuj ponownie!";
		transfer();
	}
	//asking for how much money user wants to give
	while (n <= 2)
	{
		cout <<endl<< "Podaj ile pieniedzy chcesz przelac: ";
		cin >> kwota;
		//checking if you own that much money
		if (kwota > status)
		{
			cout << "Saldo konta jest mniejsze niz podana kwota, prosze sprobowac ponownie!";
			n++;
		}
		else
			n = 4;
	}
	if (n == 3)
	{
		//after 3 wrong times, it will logout
		cout << "Wykorzystano limit prob, za 3 sekundy nastapi wylogowanie!";
		Sleep(3000);
		main();
	}
	cout << "Trwa przetwarzanie transakcji...";
	Sleep(3000);
	//lowering the value of your account by what you give
	status = status - kwota;
	//opening txt file and assinging  new value
	plik.open("saldo.txt", ios::out);
	plik << status << endl;
	plik.close();
	//ading the transaction history to card, by to who you gave it and how much did you gave him
	plik.open("transakcje.txt", ios::out | ios::app);
	plik << nr_karty << "   ";
	plik << kwota<<endl;
	plik.close();
	//getting back to menu
	cout<<endl<<"Platnosc zostala pomyslnie przetworzona! Pieniadze zostaly przelane!" << endl << "Za 3 sekundy nastapi powrot do menu!";
	Sleep(3000);
	menu();
}
//checking how much money you own
void saldo()
{
	string linia;
	//clearing terminal windows
	system("cls");
	//opening txt file
	fstream plik;
	plik.open("saldo.txt", ios::in);
	//checking if file exists
	if (plik.good() == false)
	{
		cout << "Podany plik nie istnieje!";
		exit(0);
	}
	//getting line from txt and converting it to int
	while (getline(plik, linia))
	{
		status = atoi(linia.c_str());
	}
	plik.close();
	//giving user the amount of account
	cout << "Twoje saldo wynosi " << status << "zl.";
	//back to menu button
	cout << endl << endl << "1. Powrot do menu";
	wybor = _getch();
	switch (wybor)
	{
	case '1':
	{
		menu();
	}
	break;
	}

}
//main menu
void menu()
{
	//clearing terminal windows
	system("cls");
	//menu scheme
	cout << endl << endl << "MENU GLOWNE" << endl;
	cout << "-----------------" << endl;
	cout << "1. Wplata" << endl;
	cout << "2. Wyplata" << endl;
	cout << "3. Transfer" << endl;
	cout << "4. Saldo" << endl;
	cout << "5. Koniec" << endl << endl;
	//menu buttons, assinging to them right processes
	wybor = _getch();

	switch (wybor)
	{
	case '1':
	{
		wplata();
	}
	break;
	case '2':
	{
		wyplata();
	}
	break;
	case '3':
	{
		transfer();
	}
	break;
	case '4':
	{
		saldo();
	}
	break;
	case '5':
	{
		exit(0);
	}
	break;
	}
}

//main process
int main()
{
	//Welcoming user to bank
	cout << "Witaj w banku!"<<endl;
	//using proccess to check PIN
	jaki_pin();
	Sleep(3000);
	//directing to menu
	menu();

	return 0;
}
