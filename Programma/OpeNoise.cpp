/*
	PROGRAMMA ELABORAZIONE DATI - PROGETTO OPENOISE
	Sviluppato da Carlo Zambaldo (carlo.zambaldo@gmail.com)
	Liceo Girolamo Fracastoro, Verona, Italia

	Il programma deve:
	- aprire 51 files leggendo il nome da un file (NomiFiles.txt)
	- fare la media e la varianza dei valori letti dai files
	- salvare un file con i nomi delle strade e valori di rumore associato

*/

// ATTENZIONE! LE DIRECTORIES POTREBBERO VARIARE A SECONDA DEL PC !!!

#include <math.h>
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

//#define R 300    //numero righe del file std 	(SOPPRESSO: OGNI FILE HA LA SUA LUNGHEZZA)
//#define NF 51    // numero di files			(SOPPRESSO: IL NUMERO DEI FILES VIENE DETERMINATO DAL PROGRAMMA)
//#define LenS 45  // lunghezza nome strada		( INUTILE )
#define LenR 100 // lunghezza di una riga

int main(){
	double num=0.0, media=0.0, varianza=0.0;
	int counter=0;
	char N[5], xx[LenR];
	string str, giudizio;

	ifstream nomiFile;
	nomiFile.open("NomiFiles.txt", ios::in);
	ofstream scrivi;
	scrivi.open("Risultati.txt", ios::out);
	ifstream leggi;

	int o=0;

	// APRO TUTTI I FILE CONTENUTI NEL FILE nomiFile.txt UNO AD UNO
	while(nomiFile>>xx){
		o++;
		cout<<"Sto operando su: "<<xx<<" ... ";
		leggi.open(xx, ios::in);
	    if (!leggi) {
	        cout << "Unable to open file!";
	        exit(1); // terminate with error
	    }

	    // LEGGO DA FILE I DATI E FACCIO LA SOMMA DI TUTTO
		while(getline(leggi, str)){
			getline(leggi, str);
			N[0]=str[20]; N[1]=str[21]; N[2]=str[22]; N[3]=str[23]; N[4]=0;
			num=atof(N);
			media+=num;
			counter++;
		}
		leggi.close();
		leggi.open(yy, ios::in);
		leggi>>str;
	    // CALCOLO MEDIA, VARIANZA E GIUDIZIO DELLA STRADA
	    media/=counter;

		for(int i=0; i<counter; i++)
			getline(leggi, str);
			N[0]=str[20]; N[1]=str[21]; N[2]=str[22]; N[3]=str[23]; N[4]=0;
			num=atof(N);
			varianza+=pow((num-media),2.0);
		varianza/=counter;
		varianza=sqrt(varianza);

		if(media<50) giudizio="Molto Buona";
		else if(media<62) giudizio="Buona";
		else if(media<75) giudizio="Scarsa";
		else if(media<100) giudizio="Pessima";

		// STAMPO SU FILE
		scrivi<<"FILE No "<<o<<": '"<<xx<<"'. I valori:"<<endl;
		scrivi<<"Media Rumore: "<<media<<" dB"<<endl;
		scrivi<<"Varianza: "<<varianza<<endl;
		scrivi<<"Qualita'  della strada: "<<giudizio<<endl<<endl;
		cout<<"Fine."<<endl;

		// TORNO SU
		media=0.0;
		varianza=0.0;
		counter=0;
		leggi.close();
	}


	// CHIUSURA DEL PROGRAMMA
	cout<<endl<<"Ho salvato tutti i risultati sul file 'Risultati.txt'."<<endl;
	nomiFile.close();
	scrivi.close();
	return 0;
}


