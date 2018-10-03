/*
	PROGRAMMA ELABORAZIONE DATI - PROGETTO OPENOISE
	Sviluppato da Carlo Zambaldo (carlo.zambaldo@gmail.com)
	Liceo Girolamo Fracastoro, Verona, Italia

	Il programma deve:
	- aprire tutti i files in una directory (nella cartella FILES)
	- fare la media e varianza dei valori letti da files
	- dare un giudizio sulla qualita'  della strada
	- salvare un file (Risultati.txt) con i valori calcolati

	IL PRESENTE PROGRAMMA FUNZIONA ANCHE SENZA IL FILE "NomiFiles.txt"
	(Da compilare con Eclipse per mac)

*/
// NOTA: LEGGE 3 FILE IN PIU' (/.. , /. E /DS_Storage)

// ATTENZIONE! LE DIRECTORIES POTREBBERO VARIARE A SECONDA DEL PC !!!

#include <math.h>
#include <iostream>
#include <fstream>
#include <string>
#include <dirent.h>

using namespace std;

int main(){
	double num=0.0, media=0.0, varianza=0.0;
	int counter=0, o=0;
	char N[5], yy[]="FILES/"; // IN CASO NON DOVESSE TROVARE LA DIRECTORY CAMBIARE QUESTI
	string str, giudizio;

	ofstream scrivi;
	scrivi.open("Risultati.txt", ios::out);
	ifstream leggi;


	// APRO TUTTI I FILE CONTENUTI NELLA CARTELLA FILES
    struct dirent **namelist;
    int n;
    n = scandir("src/FILES", &namelist, 0, alphasort);
    if (n < 0){
        perror("scandir");
    	cout<<"An Error has occurred!";
    	exit(1);
    }else {
        while((n--)) {
        	o++;
        	strcpy(yy, "FILES/"); // resetto la stringa yy             // IN CASO NON DOVESSE FUNZIONARE CAMBIARE QUESTO
			strcat(yy,(namelist[n]->d_name)); // "scr/FILES/" + nomefile
			cout<<"Sto operando su: "<<yy<<" ... ";
			leggi.open(yy, ios::in);
			if (!leggi){
				cout<<"Unable to open file!"<<endl;
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
			scrivi<<"FILE No "<<o<<": '"<<yy<<"'. I valori:"<<endl;
			scrivi<<"Media Rumore: "<<media<<" dB"<<endl;
			scrivi<<"Varianza: "<<varianza<<endl;
			scrivi<<"Qualita' della strada: "<<giudizio<<endl<<endl;
			cout<<"Fine."<<endl;

			// TORNO SU
			media=0.0;
			varianza=0.0;
			counter=0;
			leggi.close();
			free(namelist[n]);
        }
	}


	// CHIUSURA DEL PROGRAMMA
	cout<<endl<<"Ho salvato tutti i risultati sul file 'Risultati.txt'."<<endl;
	free(namelist);
	scrivi.close();
	system("PAUSE");
	return 0;
}



