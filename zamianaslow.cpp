//////////////////////// MATEUSZ GABRYEL NR INDEKSU 181329 ///////////////////////////////////////////////
#include <algorithm>
#include <cctype>
#include <fstream>
#include <iostream>
#include <string>
//////////////////////////////////////////////////////////////////////////////////////////////////////////
using namespace std;
//////////////////////////////////////// MAIN ////////////////////////////////////////////////////////////
int main() {
	//setlocale(LC_ALL, "pl-PL.UTF-8");
	
	string linia;
	string tekst_do_zamiany;
	string tekst_do_zamiany_lowercase;
	
	string NazwaPliku_1;
	string NazwaPliku_2;
	string NazwaPliku_3;
	
	cout<<"-----------------------------------------------------"<<endl;
	cout<<"          Mateusz Gabryel nr indeksu: 181329         "<<endl;
	cout<<"-----------------------------------------------------"<<endl;
	cout<<"Podaj nazw\251 pliku z pocz\245tkowym tekstem: "<<endl;
	cin >>NazwaPliku_1;
	cout<<"-----------------------------------------------------"<<endl;
	cout<<"Podaj nazw\251 pliku ze s\210owami do zamiany: "<<endl;
	cin >> NazwaPliku_2;
	cout<<"-----------------------------------------------------"<<endl;
	cout<<"Podaj nazw\251 pliku po zamianie s\210\242w:   "<<endl;
	cin >> NazwaPliku_3;
	cout<<"-----------------------------------------------------"<<endl;

	fstream plikDoOdczytu;
	fstream plikDoZamiany;
	fstream plikDoZapisu;
	
//////////////////////////////// WCZYTYWANIE PLIKU, Z POCZATKOWYM TEKSTEM ////////////////////////////////
	plikDoOdczytu.open(NazwaPliku_1, ios::in);
	while (!plikDoOdczytu.eof()) {
		getline(plikDoOdczytu, linia);
		tekst_do_zamiany=tekst_do_zamiany+linia + "\n";		// "\n" = zlamanie linii w "notatniku".
	}
	plikDoOdczytu.close();
//////////////////////////////////////////////////////////////////////////////////////////////////////////

	tekst_do_zamiany_lowercase = tekst_do_zamiany;          // Zamiana tekstu na wszystkie male litery, aby ujednolicic.
	
	transform(tekst_do_zamiany_lowercase.begin(), tekst_do_zamiany_lowercase.end(), tekst_do_zamiany_lowercase.begin(),
		[](unsigned char c) { return tolower(c); });

	int ilosc_wierszy = 0;

////////////////////////////// WCZYTYWANIE PLIKU ZE S£OWAMI DO ZAMIANY ///////////////////////////////////

	plikDoZamiany.open(NazwaPliku_2, ios::in);
	while (!plikDoZamiany.eof()) {				       // Zliczenie ilosci wierszy -> ilosc slow do zamiany.
		getline(plikDoZamiany, linia);				   // Ilosc wierszy = ilosc slow do zamiany.
		ilosc_wierszy++;
	}
	
	plikDoZamiany.seekg(0);							   // Powrot na poczatek pliku.

	string **tab = new string*[ilosc_wierszy + 1];     // Stworzenie dynamicznej tablicy do mapowania, 
	for (int i = 0; i <= ilosc_wierszy; i++) {		   // zamiany slow.
		tab[i] = new string[2];
	}

	int	i = 0;										   
	while (!plikDoZamiany.eof()) {					   // Wczytanie slow do zamiany do tablicy.
		getline(plikDoZamiany, linia);
		
		if (linia.length() > 0) {					   
			transform(linia.begin(), linia.end(), linia.begin(),	// Zamiana wszystkich liter
				[](unsigned char c) { return tolower(c); });		// na male litery.
			tab[i][0] = linia.substr(0, linia.find(" "));									  // Przypisanie pierwszej kolumny.
			tab[i][1] = linia.substr(linia.find(" ") + 1, linia.length() - linia.find(" "));  // Przypisanie drugiej kolumny.
			i++;
		}
	}
	plikDoZamiany.close();							   // Zamkniecie pliku.
	
////////////////////////////////////// WYSZUKIWANIE I ZAMIANA SLOW ///////////////////////////////////////

	int indeks;
	string slowo;
	string slowoPoZamianie;
	
	for (int x=0; x<=ilosc_wierszy; x++) {
		slowo = tab[x][0];
		slowoPoZamianie = tab[x][1];
		if (slowo.length() > 0) {
			indeks = tekst_do_zamiany_lowercase.find(slowo);  	// Pobranie pozycji pierwszego wystapienia szukanego slowa.
			if(indeks !=string::npos){
				if(isupper(tekst_do_zamiany[indeks])){			// Sprawdzenie czy jest mala czy wielka litera.
					slowoPoZamianie = " ";						// "Wyczyszczenie" zmiennej.
					slowoPoZamianie[0] = toupper(tab[x][1][0]); // Pierwszy znak w X slowie, o komorce [x][1].
					slowoPoZamianie.append(tab[x][1].substr(1, tab[x][1].length()-1)); // Dopisanie pozostalej czesci X slowie.
				}
				
				tekst_do_zamiany_lowercase.replace(indeks, tab[x][0].length(), tab[x][1]);	// Zamiana slow: odkad,dokad,
				tekst_do_zamiany.replace(indeks, slowo.length(), slowoPoZamianie);			// na co.
				
				do
				{		
					indeks = tekst_do_zamiany_lowercase.find(slowo, indeks + slowo.length()); // Pobranie pozycji pozostalych
					if(indeks !=string::npos){												  // wystapien i wykonanie czynnosci. 
						
						if(isupper(tekst_do_zamiany[indeks])){
							slowoPoZamianie = " ";
							slowoPoZamianie[0] = toupper(tab[x][1][0]);
							slowoPoZamianie.append(tab[x][1].substr(1, tab[x][1].length() - 1));
						}
						tekst_do_zamiany_lowercase.replace(indeks, tab[x][0].length(), tab[x][1]);
						tekst_do_zamiany.replace(indeks, slowo.length(), slowoPoZamianie);
					}
					
				} while (indeks !=string::npos); 
			}
		}
	}

////////////////////////////////////// ZAPISYWANIE DO NOWEGO PLIKU ///////////////////////////////////////
	plikDoZapisu.open(NazwaPliku_3,ios::out);
	plikDoZapisu<<tekst_do_zamiany;											// Wczytanie zmiennej do pliku.
	plikDoZapisu.close();
//////////////////////////////////////////////////////////////////////////////////////////////////////////
	cout<<"+++++++++++++++++++++++++++++++++++++++++++++++++++++"<<endl;
	cout<<"-----------------------------------------------------"<<endl;
	cout<<"           Zamiana zosta\210a zako\344czona,         "<<endl;
	cout<<"     Otw\242rz sw\242j plik o nazwie: "<<NazwaPliku_3<<","<<endl;
	cout<<"               aby zobaczy\206 zmiany.               "<<endl;
	cout<<"-----------------------------------------------------"<<endl;
	cout<<"+++++++++++++++++++++++++++++++++++++++++++++++++++++"<<endl;
	cout<<"-----------------------------------------------------"<<endl;
//////////////////////////////////////////////////////////////////////////////////////////////////////////
	return 0;
}
