#include <iostream>
#include <malloc.h>
#include <conio.h>
#include <string.h>
#include <fstream>
#define max 50
#define True 1
#define False 0

using namespace std;

struct typeinfo{
	char nama[30], obat[100];
	int umur;
};

typedef struct node *typeptr;
struct node{
	typeinfo info;
	typeptr next;
};
typeptr akhirstack, awalstack;
typeptr qdepan, qbelakang;

void menu();
void tambahantrian();
void lihatantrian();
void layaniantrian();
void lihatriwayat();

void buatqueue();
int queuekosong();
void enqueue(typeinfo IB);
void dequeue();
void cetakqueue();

void buatstack();
int stackkosong();
void push(typeinfo IB);
void pop();
void cetakstack();

void masukfile();
void keluarfile();
void writestack();
void readstack();
string stringreplace(string x);
string stringreverse(string x);

int pilih, angka;
char ulang='y';

int main(){
	buatstack();
	buatqueue();
	do{
		menu();
		switch(pilih){
		 	case 1:
		 		tambahantrian();
		 	break;
		 	case 2:
		 		lihatantrian();
		 	break;
		 	case 3:
		 		layaniantrian();
		 	break;
		 	case 4:
		 		lihatriwayat();
		 	break;
		 	case 0:
	            return 0;
	        break;
		 	default:
		 		cout << "Salah input!\n";
		 	break;
		}
		cout << "\nKembali ke menu utama? (y/n) : "; cin >> ulang;
	} while(ulang=='y' || ulang=='Y');
	cout << endl;
	system("pause");
}

void menu(){
	system("cls");
	cout << "==============================\n";
	cout << "|       Antrian Apotek       |\n";
	cout << "==============================\n";
	cout << "1. Tambah Antrian\n";
	cout << "2. Lihat Antrian\n";
	cout << "3. Layani Antrian\n";
	cout << "4. Lihat Riwayat Antrian\n";
	cout << "0. Exit\n";
	cout << "Pilih: "; cin >> pilih;
}

void buatstack(){
	typeptr NS;

 	NS = NULL;
 	awalstack = NS;
 	akhirstack = awalstack;
}

int stackkosong(){
	if(awalstack==NULL){
		return true;
	} else{
		return false;
	}
}

void tambahantrian(){
	typeinfo antre;
	int banyakantre;

	qdepan = NULL;
	keluarfile();
	cout << "\n==============================\n";
	cout << "| Tambah Data Antrian Apotek |\n";
	cout << "==============================\n";

	cout << "Nama\t: "; cin.getline(antre.nama, 30); cin.getline(antre.nama, 30); fflush(stdin);
	cout << "Umur\t: "; cin >> antre.umur; fflush(stdin);
	cout << "Obat\t: "; cin.getline(antre.obat, 100); fflush(stdin);

	enqueue(antre);
	masukfile();
}

void lihatantrian(){
	qdepan = NULL;
	keluarfile();
	cout << "\n==============================\n";
	cout << "|       Daftar Antrian       |\n";
	cout << "==============================\n";
	cetakqueue();
}

void layaniantrian(){
	char layani;

	qdepan = NULL;
	akhirstack = NULL;
	awalstack = NULL;
	keluarfile();
	readstack();
	cout << "\n==============================\n";
	cout << "|       Layani Antrian       |\n";
	cout << "==============================\n";

	if (queuekosong()){
		cout << "\nBelum ada antrian!\n";
	} else{
		cout << "\nNama : " << qdepan->info.nama << endl;
		cout << "Umur : " << qdepan->info.umur << endl;
		cout << "Obat : " << qdepan->info.obat << endl;

		cout << "\nLayani antrian? (y/n): "; cin >> layani;
		if (layani == 'y'){
			dequeue();
			cout << "\nAntrian dihapus!\n";
			// cout << "Tersisa " << antrian << " antrian.\n";
		} else{
			cout << "\nAntrian belum dilayani!\n";
		}
	}
	masukfile();
	writestack();
}

void lihatriwayat(){
	akhirstack = NULL;
	awalstack = NULL;
	readstack();
	cout << "\n==============================\n";
	cout << "|       Riwayat Antrian      |\n";
	cout << "==============================\n\n";
	cetakstack();
}

void buatqueue(){
	qdepan = (node *) malloc(sizeof(node));
 	qdepan = NULL;
 	qbelakang = qdepan;
}

int queuekosong(){
 	if(qdepan==NULL){
		return true;
 	} else{
		return false;
 	}
}

void enqueue(typeinfo IB){
	typeptr NB;

 	NB = (node *) malloc(sizeof(node));
 	NB->info = IB;

 	if (qdepan==NULL){
 		qdepan = NB;
 	} else{
 		qbelakang->next = NB;
 	}

 	qbelakang = NB;
 	qbelakang->next=NULL;
}

void dequeue(){
 	typeptr hapus;

 	if (queuekosong()){
 		cout << "\nTidak ada antrian!\n";
 	} else{
 		hapus = qdepan;
		qdepan = hapus->next;
		push(hapus->info);
		free(hapus);
	}
}

void cetakqueue(){
 	typeptr bantu;
 	int x = 0;

	if(queuekosong()){
		cout << "\nTidak ada antrian!\n";
	} else{
		bantu = qdepan;
		do{
			++x;
			cout << "\nAntrian ke-" << x << endl;
			cout << "\tNama : " << bantu->info.nama << endl;
			cout << "\tUmur : " << bantu->info.umur << endl;
			cout << "\tObat : " << bantu->info.obat << endl;
			bantu = bantu->next;
		} while(bantu!=NULL);
	}
}

void push(typeinfo IB){
	typeptr NS;

 	NS = (node *) malloc(sizeof(node));
 	NS->info = IB;

 	if (awalstack==NULL){
 		awalstack = NS;
 	} else{
 		akhirstack->next = NS;
 	}

 	akhirstack = NS;
 	akhirstack->next = NULL;
}

void pop(){
	typeptr hapus, bantu;

 	if (stackkosong()){
 		cout << "\nTidak ada riwayat antrian!\n";
	} else{
 		bantu = awalstack;
		hapus = akhirstack;

		if (hapus==awalstack){
			awalstack = NULL;
		} else{
			while(bantu->next->next!=NULL){
 				bantu=bantu->next;
				akhirstack = bantu;
				akhirstack->next = NULL;
			}
		}
		free(hapus);
	}
}

void cetakstack(){
	typeptr depan, bantu;
	char hapus;
	int riwayat = 0;

 	if (stackkosong()){
 		cout << "\nTidak ada riwayat antrian!\n";
 	} else{
 		depan = akhirstack;
		do{
			++riwayat;
			cout << "Data riwayat " << riwayat;
			if(depan!=awalstack){
				cout << "\n\tNama\t: " << depan->info.nama << endl;
				cout << "\tUmur\t: " << depan->info.umur << endl;
				cout << "\tObat\t: " << depan->info.obat << endl;
				bantu = awalstack;
				while(bantu->next!=depan){
					bantu=bantu->next;
				}
				depan = bantu;
			} else{
				cout << "\n\tNama\t: " << depan->info.nama << endl;
				cout << "\tUmur\t: " << depan->info.umur << endl;
				cout << "\tObat\t: " << depan->info.obat << endl;
				break;
			}
			cout << endl;
		} while(depan!= NULL);
 	}
}

void masukfile(){
	ofstream myfile;
	typeinfo antre;

	myfile.open("1_DaftarAntrian.txt");
	string ubah;
	typeptr bantu;
	bantu = qdepan;
	while(bantu!=NULL){
		antre = bantu->info;
		myfile << strcpy(antre.nama, stringreplace(antre.nama).c_str()) << "\n" << antre.umur << "\n" << antre.obat << "\n";
		bantu = bantu->next;
	}
	myfile.close();
}

void keluarfile(){
	ifstream myfile("1_DaftarAntrian.txt");
	typeinfo antre;

	if(myfile.is_open()){
		myfile >> strcpy(antre.nama, stringreverse(antre.nama).c_str()) >> antre.umur >> strcpy(antre.obat, stringreverse(antre.obat).c_str());

		while(myfile.eof()==0){
			strcpy(antre.nama, stringreverse(antre.nama).c_str());
			enqueue(antre);
			myfile >> strcpy(antre.nama, stringreverse(antre.nama).c_str()) >> antre.umur >> strcpy(antre.obat, stringreverse(antre.obat).c_str());
		}
		myfile.close();
	}
}

void writestack(){
	ofstream myfile;
	typeinfo antre;

	myfile.open("2_RiwayatAntrian.txt");
	string ubah;
	typeptr bantu, cetak;
	cetak = akhirstack;
	do{
		antre = cetak->info;
		if(cetak!=awalstack){
			myfile << strcpy(antre.nama, stringreplace(antre.nama).c_str()) << "\n" << antre.umur << "\n" << strcpy(antre.obat, stringreplace(antre.obat).c_str()) << "\n";
			bantu = awalstack;
			while(bantu->next!=cetak){
				bantu=bantu->next;
			}
			cetak = bantu;
		} else{
			myfile << strcpy(antre.nama, stringreplace(antre.nama).c_str()) << "\n" << antre.umur << "\n" << strcpy(antre.obat, stringreplace(antre.obat).c_str()) << "\n";
			break;
		}
	} while(cetak!= NULL);
	myfile.close();
}

void readstack(){
	ifstream myfile("2_RiwayatAntrian.txt");
	typeinfo antre;

	if(myfile.is_open()){
		myfile >> strcpy(antre.nama, stringreverse(antre.nama).c_str()) >> antre.umur >> strcpy(antre.obat, stringreplace(antre.obat).c_str());

		while(myfile.eof()==0){
			strcpy(antre.nama, stringreverse(antre.nama).c_str());
			push(antre);
			myfile >> strcpy(antre.nama, stringreverse(antre.nama).c_str()) >> antre.umur >> strcpy(antre.obat, stringreplace(antre.obat).c_str());
		}
		myfile.close();
	}
}

string stringreplace(string x){
	for (int i = 0; x[i]; i++){
		if(x[i]==' '){
			x.replace(i,1,1,'_');
		}
	}
	return x;
}

string stringreverse(string x){
	for (int i = 0; x[i]; i++){
		if(x[i]=='_'){
			x.replace(i,1,1,' ');
		}
	}
	return x;
}
