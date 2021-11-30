#include <iostream>
#include <malloc.h>
#include <conio.h>
#include <string.h>
#include <fstream>

using namespace std;

struct typeinfo{
	char nama[30], dokter[30], obat[30];
	int umur;
}

typedef struct typenode *typeptr;
struct node{
	typeinfo info;
	typeptr next;
};
typeptr top, bottom;
typeptr qdepan, qbelakang;

int pil, jml;
char loop='y';

void menu();
void tambah();
void layani();
void lihatdata();
void antriansukses();

void buatstack();
int stackkosong();
void push(typeinfo IB);
void pop();
void cetakstack();
void stackcek(typeinfo data);

void buatqueue();
int queuekosong();
void enqueue(typeinfo IB);
void dequeue();
void cetakqueue();
void queuecek(typeinfo data);

void masukfile();
void keluarfile();
void writestack();
void readstack();

int pil, nobuku, jml;
char loop='y';

int main(){
	buatqueue();
	buatstack();
	do{
		menu();
		switch(pil){
			case 1 :
				tambah();
			break;
			case 2 :
				layani();
			break;
			case 3 :
				lihatantrian();
			break;
			case 4 :
				antriansukses();
			break;
			case 5 :
				system("pause");
				exit(0);
			break;
			default :
				cout << "Salah input!\n";
		}
		cout << "\nKembali ke menu? (y/n) : "; cin >> loop;
	} while(loop=='y' || loop=='Y');
	return(0);
}

void menu(){
	system("cls");
	cout << "==================================\n";
	cout << "| MENU                           |\n";
	cout << "==================================\n";
	cout << "1. Tambah Antrian\n";
	cout << "2. Layani Antrian\n";
	cout << "3. Lihat Data Antrian\n";
	cout << "4. Lihat Antrian yang Sudah di Layani\n";
	cout << "5. Exit\n";
	cout << "\nPilihan : "; cin >> pil;
}

void tambah(){
	typeinfo data;
	int antrian;

	qdepan = NULL;
	keluarfile();
	cout << "\n=============================\n";
	cout << "| Tambah Data Antrian Apotek |\n";
	cout << "\n=============================\n";
	cout << "Nama\t: "; cin >> getline(data.nama, 30); fflush(stdin);
	cout << "Umur\t: "; cin >> data.umur; fflush(stdin);
	cout << "Dokter\t: "; cin >> getline(data.dokter, 30); fflush(stdin);
	cout << "Obat\t: "; cin >> getline(data.obat, 30); fflush(stdin);

	if(queuecek){
		cout << "\nData sudah masuk dalam antrian!\n";
	} else if(stackcek){
		cout << "\nData antrian sudah dilayani!\n";
	} else{
		enqueue(data);
		antrian = cetakantrian();
		cout << "\nAntrian ke-" << antrian << endl;
	}
	cout << endl;
	masukfile();
}

void layani(){
	
}