#include <iostream>
#include <malloc.h>
#include <conio.h>
#include <string.h>
#include <fstream>

using namespace std;

struct typeinfo{
	char nama[30], obat[30];
	int umur;
};

typedef struct node *typeptr;
struct node{
	typeinfo info;
	typeptr next;
};
typeptr top, bottom;
typeptr qdepan, qbelakang;

void menu();
void tambah();
void layani();
void lihatantrian();
void antriansukses();

void buatstack();
int stackkosong();
void push(typeinfo IB);
void pop();
void cetakstack();
int stackcek(typeinfo data);

void buatqueue();
int queuekosong();
void enqueue(typeinfo IB);
void dequeue();
void cetakqueue();
int cetakantrian();
int queuecek(typeinfo data);

void masukfile();
void keluarfile();
void writestack();
void readstack();
string stringreplace(string x);
string stringreverse(string x);

int pil, jml;
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
	cout << "\n==============================\n";
	cout << "| Tambah Data Antrian Apotek |\n";
	cout << "==============================\n";
	cout << "Nama\t: "; cin.getline(data.nama, 30); fflush(stdin);
	cout << "Umur\t: "; cin >> data.umur; fflush(stdin);
	cout << "Obat\t: "; cin.getline(data.obat, 30); fflush(stdin);

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
	qdepan = NULL;
	bottom = NULL;
	top = NULL;
	keluarfile();
	readstack();
	cout << "\n====================\n";
	cout << "| Melayani Antrian |\n";
	cout << "====================\n";
	if(queuekosong()){
		cout << "\nTidak ada antrian!\n";
	} else{
		cout << "\nNama\t: " << qdepan->info.nama << endl;
		cout << "Umur\t: " << qdepan->info.umur << endl;
		cout << "Obat\t: " << qdepan->info.obat << endl;
		dequeue();
	}
	cout << "\nAntrian berhasil dilayani!\n";
	masukfile();
	writestack();
}

void lihatantrian(){
	qdepan = NULL;
	keluarfile();
	cout << "\n========================\n";
	cout << "| Daftar Antrian Apotek |\n";
	cout << "=========================\n";
	cetakqueue();
	cout << endl;
}

void antriansukses(){
	bottom = NULL;
	top = NULL;
	readstack();
	if(stackkosong()){
		cout << "\nTidak ada antrian!\n";
	} else{
		cout << "\n=====================================\n";
		cout << "| Daftar Antrian yang Telah Dilayani |\n";
		cout << "======================================\n";
		cetakstack();
	}
	cout << endl;
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
	if(qdepan==NULL){
		qdepan = NB;
	} else{
		qbelakang->next = NB;
	}
	qbelakang = NB;
	qbelakang->next = NULL;
}

void dequeue(){
	typeptr hapus;
	typeinfo stack;

	if(queuekosong()){
		cout << "\nTidak ada antrian!\n";
	} else{
		hapus = qdepan;
		stack = hapus->info;
		qdepan = hapus->next;
		push(stack);
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
			cout << "Nama\t: " << bantu->info.nama << endl;
			cout << "Umur\t: " << bantu->info.umur << endl;
			cout << "Obat\t: " << bantu->info.obat << endl;
			bantu = bantu->next;
		} while(bantu!=NULL);
	}
}

int cetakantrian(){ //untuk mencetak antrian terakhir
	typeptr bantu;
	int x=0;

	bantu = qdepan;
	do{
		++x;
		bantu = bantu->next;		
	} while(bantu!=NULL);
	return x;
}

int queuecek(typeinfo data){
	typeptr bantu;
	bantu = qdepan;

	while(bantu!=NULL){
		if(strcmp(bantu->info.nama, data.nama)==0){
			return true;
		}
		bantu = bantu->next;
	}
}

void buatstack(){
	typeptr NS;

	NS = (node *) malloc(sizeof(node));
	NS = NULL;
	bottom = NS;
	top = bottom;
}

int stackkosong(){
	if(bottom == NULL){
		return true;
	} else{
		return false;
	}
}

void push(typeinfo IB){
	typeptr NS;

	NS = (node *) malloc(sizeof(node));
	NS->info = IB;
	if(bottom == NULL){
		bottom = NS;
	} else{
		top->next = NS;
	}
	top = NS;
	top->next = NULL;
}

void pop() {
	typeptr bantu, hapus;

	if (stackkosong()){
		cout <<"\nTidak ada data!\n";
	} else{ 
		bantu = bottom;
		hapus = top;
		if(hapus==bottom){
			bottom = NULL;
		} else{ 
			while(bantu->next->next!=NULL){
				bantu = bantu->next;
			}
			top = bantu;
			top->next = NULL;
		}
		free(hapus);
	}
}

void cetakstack(){
	int urut=0;
	typeptr bantu, cetak;
	cetak = top;
	do{
		++urut;
		cout << "Data ke-" << urut << endl;
		if(cetak!=bottom){
			cout << "Nama\t: " << cetak->info.nama << endl;
			cout << "Umur\t: " << cetak->info.umur << endl;
			cout << "Obat\t: " << cetak->info.obat << endl;
			bantu = bottom;
			while(bantu->next!=cetak){
				bantu = bantu->next;
			}
			cetak = bantu;
		} else{
			cout << "Nama\t: " << cetak->info.nama << endl;
			cout << "Umur\t: " << cetak->info.umur << endl;
			cout << "Obat\t: " << cetak->info.obat << endl;
			break;
		}
		cout << endl;
	} while(cetak!= NULL);
}

int stackcek(typeinfo data){
	typeptr bantu;
	//cetak = top;
	bantu = bottom;
	while(bantu!=NULL){
		if(strcmp(bantu->info.nama, data.nama)==0){
			return true;
		}
		bantu = bantu->next;
	}
}

void masukfile(){
	ofstream myfile;
	typeinfo data;
	string ubah;
	typeptr bantu;
	
	myfile.open("antrianApotek.txt");
	bantu = qdepan;
	while(bantu!=NULL){
		data = bantu->info;
		myfile << strcpy(data.nama, stringreplace(data.nama).c_str()) << "\n" << data.umur << "\n" << data.obat << "\n";
		bantu = bantu->next;
	}
	myfile.close();
}

void keluarfile(){
	typeinfo data;
	ifstream myfile("antrianApotek.txt");
	
	if(myfile.is_open()){
		myfile >> strcpy(data.nama, stringreverse(data.nama).c_str()) >> data.umur >> data.obat;
		
		while(myfile.eof()==0){
			strcpy(data.nama,stringreverse(data.nama).c_str());
			enqueue(data);
			myfile >> strcpy(data.nama,stringreverse(data.nama).c_str()) >> data.umur >> data.obat;
		}
		myfile.close();
	}
}

void writestack(){
	ofstream myfile;
	typeinfo data;
	string ubah;
	typeptr bantu,cetak;

	myfile.open("antrianSukses.txt");
	cetak = top;
	do{
		data = cetak->info;
		if(cetak!=bottom){
			myfile << strcpy(data.nama, stringreplace(data.nama).c_str()) << "\n" << data.umur << "\n" << data.obat << "\n";
			bantu = bottom;
			while(bantu->next!=cetak){
				bantu=bantu->next;
			}
			cetak = bantu;
		} else{
			myfile << strcpy(data.nama, stringreplace(data.nama).c_str()) << "\n" << data.umur << "\n" << data.obat << "\n";
			break;
		}
	} while(cetak!= NULL);
	myfile.close();
}

void readstack(){
	typeinfo data;
	ifstream myfile("antrianSukses.txt");

	if(myfile.is_open()){
		myfile >> strcpy(data.nama, stringreverse(data.nama).c_str()) >> data.umur >> data.obat;
		
		while(myfile.eof()==0){
			strcpy(data.nama,stringreverse(data.nama).c_str());
			push(data);
			myfile >> strcpy(data.nama,stringreverse(data.nama).c_str()) >> data.umur >> data.obat;
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
