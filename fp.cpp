#include <iostream>
#include <malloc.h>
#include <conio.h>
#include <string.h>
#include <fstream>
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

int antrian = 0;
int riwayat = 0;

void tambahantrian();
void lihatantrian();
void layaniantrian();
void lihatriwayat();

void buatqueue();
int queuekosong();
void enqueue(typeinfo IB);
void dequeue();
void cetakqueue();

void buat_stack();
int stack_kosong();
void push(typeinfo IB);
void pop();
void cetak_stack();

void masukfile();
void keluarfile();
void writestack();
void readstack();
string stringreplace(string x);
string stringreverse(string x);

int main()
{
	 int pilih, angka;

	Mulai:
	cout << "==============================\n";
	cout << "|       Antrian Apotek       |\n";
	cout << "==============================\n";
	cout << "1. Tambah Antrian" << endl;
	cout << "2. Lihat Antrian" << endl;
	cout << "3. Layani Antrian" << endl;
	cout << "4. Lihat Riwayat Antrian" << endl;
	cout << "0. Exit" << endl;
	cout << "Pilih: "; cin >> pilih;
	cout << endl;

	 switch(pilih)
	 {
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
	 		cout << "Salah input." << endl;
	 	break;
	}
	cout << endl;
	system("pause");
	system("cls");
	goto Mulai;
}

void tambahantrian()
{
	typeinfo antre;
	int banyakantre;

	keluarfile();
	cout << "==============================\n";
	cout << "| Tambah Data Antrian Apotek |\n";
	cout << "==============================\n";

	cout << "\nBanyak antrian yang ingin diinput: "; cin >> banyakantre;
	for (int i=0; i<banyakantre; i++)
	{
		antrian++;
		cout << "\nAntrian ke-" << antrian << endl;
		cout << "\tNama\t: "; cin.getline(antre.nama, 30); cin.getline(antre.nama, 30); fflush(stdin);
		cout << "\tUmur\t: "; cin >> antre.umur; fflush(stdin);
		cout << "\tObat\t: "; cin.getline(antre.obat, 100); fflush(stdin);

		enqueue(antre);
	}
	masukfile();
}

void lihatantrian()
{
	keluarfile();
	cout << "==============================\n";
	cout << "|       Daftar Antrian       |\n";
	cout << "==============================\n";
	cetakqueue();
}

void layaniantrian()
{
	char layani;

	keluarfile();
	readstack();
	cout << "==============================\n";
	cout << "|       Layani Antrian       |\n";
	cout << "==============================\n";

	if (queuekosong())
	{
		cout << "\nBelum ada antrian." << endl;
	}
	else
	{
		cout << "\nNama : " << qdepan->info.nama << endl;
		cout << "Umur : " << qdepan->info.umur << endl;
		cout << "Obat : " << qdepan->info.obat << endl;

		cout << "\nLayani antrian? (y/n): "; cin >> layani;
		if (layani == 'y')
		{
			dequeue();
			cout << "\nAntrian dihapus." << endl;
		}
		else
		{
			cout << "\nAntrian belum dilayani." << endl;
		}
	}
	masukfile();
	readstack();
}

void lihatriwayat()
{
	writestack();
	cout << "==============================\n";
	cout << "|       Riwayat Antrian      |\n";
	cout << "==============================\n";
	cetak_stack();
}

void buatqueue()
{
	qdepan=(node *) malloc(sizeof(node));
 	qdepan=NULL;
 	qbelakang=qdepan;
}

int queuekosong()
{
 	if(qdepan==NULL)
		return(True);
 	else
		return(False);
}

void enqueue(typeinfo IB)
{
	typeptr NB;
 	NB=(node *) malloc(sizeof(node));
 	NB->info=IB;

 	if (qdepan==NULL)
 		qdepan=NB;
 	else
 		qbelakang->next=NB;

 	qbelakang=NB;
 	qbelakang->next=NULL;
}

void dequeue()
{
 	typeptr hapus;

 	if (queuekosong())
 	{
 		cout << "\nTidak ada antrian." << endl;
 	}
 	else
 	{
 		hapus=qdepan;
		qdepan=hapus->next;
		push(hapus->info);
		free(hapus);
		antrian--;
		riwayat++;
	}
}

void cetakqueue()
{
 	typeptr bantu;

	if(queuekosong())
	{
		cout << "\nTidak ada antrian." << endl;
	}
	else
	{
		bantu = qdepan;

		for (int i=0; i<antrian; i++)
		{
			cout << "\nAntrian ke-" << i+1 << endl;
			cout << "\tNama : " << bantu->info.nama << endl;
			cout << "\tUmur : " << bantu->info.umur << endl;
			cout << "\tObat : " << bantu->info.obat << endl;
			bantu = bantu->next;
		}
	}
}

void buat_stack()
{
	typeptr NS;
 	NS=NULL;
 	awalstack=NS;
 	akhirstack=awalstack;
 }

int stack_kosong()
{
 	if(awalstack==NULL)
		return(True);
 	else
		return(False);
}

void push(typeinfo IB)
{
	typeptr NS;
 	NS=(node *) malloc(sizeof(node));
 	NS->info=IB;

 	if (awalstack==NULL)
 		awalstack=NS;
 	else
 		akhirstack->next=NS;

 	akhirstack=NS;
 	akhirstack->next=NULL;
 	riwayat++;
 }

void pop()
{
	typeptr hapus, bantu;

 	if (stack_kosong())
 	{
 		cout << "\nTidak ada riwayat antrian." << endl;
	}
	else
 	{
 		bantu=awalstack;
		hapus=akhirstack;

		if (hapus==awalstack)
			awalstack=NULL;
		else
		{
			while(bantu->next->next!=NULL)
 				bantu=bantu->next;

			akhirstack=bantu;
			akhirstack->next=NULL;
		}
		free(hapus);
		riwayat--;
	}
}

void cetak_stack()
{
	typeptr depan,bantu;
	char hapus;

 	if (stack_kosong())
 	{
 		cout << "\nTidak ada riwayat antrian." << endl;
 	}
 	else
 	{
 		depan = akhirstack;
		do
		{
			if(depan!=awalstack)
			{

				cout << "Nama : " << depan->info.nama << endl;
				cout << "NIK  : " << depan->info.umur << endl;
				cout << "Umur : " << depan->info.obat << endl;
				bantu = awalstack;
				while(bantu->next!=depan){
					bantu=bantu->next;
				}
				depan = bantu;
			}
			else
			{

				cout << "Nama : " << depan->info.nama << endl;
				cout << "NIK  : " << depan->info.umur << endl;
				cout << "Umur : " << depan->info.obat << endl;
				break;
			}
			cout << endl;
		}while(depan!= NULL);

		cout << "\nHapus riwayat antrian? (y/n): "; cin >> hapus;

		if (hapus == 'y')
		{
			for (int i=0; i<riwayat; i++)
			{
				pop(); //MENGHAPUS SEBANYAK JUMLAH RIWAYAT YANG ADA
			}
			cout << riwayat << " riwayat antrian berhasil dihapus." << endl;
		}
		else
		{
			cout << "Kembali ke menu." << endl;
		}
 	}
}

void masukfile()
{
	ofstream myfile;
	typeinfo antre;
	string ubah;
	typeptr bantu;

	myfile.open("1_DaftarAntrian.txt");
	bantu = qdepan;
	while(bantu!=NULL){
		antre = bantu->info;
		myfile << strcpy(antre.nama, stringreplace(antre.nama).c_str()) << "\n" << antre.umur << "\n" << antre.obat << "\n";
		bantu = bantu->next;
	}
	myfile.close();
}

void keluarfile()
{
	typeinfo antre;
	ifstream myfile("1_DaftarAntrian.txt");

	if(myfile.is_open()){
		myfile >> strcpy(antre.nama, stringreverse(antre.nama).c_str()) >> antre.umur >> antre.obat;

		while(myfile.eof()==0){
			strcpy(antre.nama,stringreverse(antre.nama).c_str());
			enqueue(antre);
			myfile >> strcpy(antre.nama,stringreverse(antre.nama).c_str()) >> antre.umur >> antre.obat;
		}
		myfile.close();
	}
}

void writestack()
{
	ofstream myfile;
	typeinfo antre;
	string ubah;
	typeptr bantu,cetak;

	myfile.open("2_RiwayatAntrian.txt");
	cetak = akhirstack;
	do{
		antre = cetak->info;
		if(cetak!=awalstack){
			myfile << strcpy(antre.nama, stringreplace(antre.nama).c_str()) << "\n" << antre.umur << "\n" << antre.obat << "\n";
			bantu = awalstack;
			while(bantu->next!=cetak){
				bantu=bantu->next;
			}
			cetak = bantu;
		} else{
			myfile << strcpy(antre.nama, stringreplace(antre.nama).c_str()) << "\n" << antre.umur << "\n" << antre.obat << "\n";
			break;
		}
	} while(cetak!= NULL);
	myfile.close();
}

void readstack()
{
	typeinfo antre;
	ifstream myfile("2_RiwayatAntrian.txt");

	if(myfile.is_open()){
		myfile >> strcpy(antre.nama, stringreverse(antre.nama).c_str()) >> antre.umur >> antre.obat;

		while(myfile.eof()==0){
			strcpy(antre.nama,stringreverse(antre.nama).c_str());
			push(antre);
			myfile >> strcpy(antre.nama,stringreverse(antre.nama).c_str()) >> antre.umur >> antre.obat;
		}
		myfile.close();
	}
}

string stringreplace(string x)
{
	for (int i = 0; x[i]; i++){
		if(x[i]==' '){
			x.replace(i,1,1,'_');
		}
	}
	return x;
}

string stringreverse(string x)
{
	for (int i = 0; x[i]; i++){
		if(x[i]=='_'){
			x.replace(i,1,1,' ');
		}
	}
	return x;
}

/*void cetak_stack()
{
	typeptr depan,bantu;
	char hapus;

 	if (stack_kosong())
 	{
 		cout << "\nTidak ada riwayat antrian." << endl;
 	}
 	else
 	{
 		depan=awalstack;
 		awalstack=akhirstack;
 		do
	 	{
	 		bantu=depan;
			while (bantu->next!=akhirstack)
	 			bantu=bantu->next;
			akhirstack->next=bantu;
			akhirstack=bantu;
		}
		while (akhirstack!=depan);

	 	akhirstack->next=NULL;
	 	bantu=awalstack;
	 	while(bantu!=NULL)
	 	{
			cout << "\nNama : " << bantu->info.nama << endl;
			cout << "\nUmur : " << bantu->info.umur << endl;
			cout << "\nObat : " << bantu->info.obat << endl;
			bantu=bantu->next;
		}

		cout << "Hapus riwayat antrian? (y/n): "; cin >> hapus;

		if (hapus == 'y')
		{
			for (int i=0; i<riwayat; i++)
			{
				pop(); //MENGHAPUS SEBANYAK JUMLAH RIWAYAT YANG ADA
			}
			cout << riwayat << " riwayat antrian berhasil dihapus." << endl;
		}
		else
		{
			cout << "Kembali ke menu." << endl;
		}
 	}
}*/
