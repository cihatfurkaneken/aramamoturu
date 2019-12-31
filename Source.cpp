#include <iostream>
#include <string>
#include <fstream>
#include <locale.h>
#include <algorithm>
#include <time.h>
#include <stdlib.h>
#include <sstream>
#include <string.h>
#include <math.h>
#include <conio.h>
#include <windows.h>


using namespace std;
/*400.000 kelime okunur ve listelere harf sayılarına göre dizilir. Ararken arananın harf sayısına göre listelere bakar ve
eşleşen'i bulup sayisini ve hangi dosyada kaç tane olduğunu yazar. Tam eşleşme bulamazsa arananın harf sayısından
2 alt ve 2 üst listede levenshtein derecesi 2 ve altı olanları bulur ve yazar.

pdfdoc.exe: metin2.pdf ve metin4.docx'i txt formatına çevirip okur,okuduktan sonra txt,ler silinir. 
SharpZipLib.dll ve itextsharp.dll bu exenin dosyalarıdır. Classları içerir

distance.h : Levenshtein distance değerlerini bulur levenshtein algoritmasının kütüphanesidir.
*/


struct node{
	string data;
	node *next;
	int sayi = 1;
	int d1 = 0, d2 = 0, d3 = 0, d4 = 0;
};

size_t levin(const string &s1, const string &s2) //yakinsak arama icin algoritma.

{
	const size_t m(s1.size());
	const size_t n(s2.size());

	if (m == 0) return n;
	if (n == 0) return m;

	size_t *costs = new size_t[n + 1];

	for (size_t k = 0; k <= n; k++) costs[k] = k;

	size_t i = 0;
	for (string::const_iterator it1 = s1.begin(); it1 != s1.end(); ++it1, ++i)
	{
		costs[0] = i + 1;
		size_t corner = i;

		size_t j = 0;
		for (string::const_iterator it2 = s2.begin(); it2 != s2.end(); ++it2, ++j)
		{
			size_t upper = costs[j + 1];
			if (*it1 == *it2)
			{
				costs[j + 1] = corner;
			}
			else
			{
				size_t t(upper<corner ? upper : corner);
				costs[j + 1] = (costs[j]<t ? costs[j] : t) + 1;
			}

			corner = upper;
		}
	}
	size_t result = costs[n];
	delete[] costs;
	return result;
}
void yakin(node* dizi[],string aranan,int i)
{
	int q, count=0;

	if (aranan.length() <= 5)
		q = 2;
	else
		q = 3;

	int v = aranan.length();

	ofstream writer;
	writer.open("sonuc.txt",ios::app);
	ofstream depo;
	depo.open("depo.txt",ios::app);

	node* yrd3 = dizi[v + i];

	while (yrd3 != NULL)
	{
		if (levin(aranan, yrd3->data) < q)
		{
			writer << yrd3->data << " aramasi " << yrd3->sayi << " adet bulundu" << endl;
			writer << "TXT->:" << yrd3->d1 << endl;
			writer << "PDF->" << yrd3->d2 << endl;
			writer << "HTML->" << yrd3->d3 << endl;
			writer << "DOCX->" << yrd3->d4 << endl;
			writer << "------------------------------------------" << endl;

			depo << yrd3->data << " aramasi " << yrd3->sayi << " adet bulundu" << endl;
			depo << "TXT->:" << yrd3->d1 << endl;
			depo << "PDF->" << yrd3->d2 << endl;
			depo << "HTML->" << yrd3->d3 << endl;
			depo << "DOCX->" << yrd3->d4 << endl;
			depo << "------------------------------------------" << endl;

			count = 1;
		}
		yrd3 = yrd3->next;
	}

	if (count==1)
	{		
			writer << endl << " ^^^ Aradiginiz Burada  Olabilir ^^^ " << endl<<endl;			
	}


	writer.close();
	depo.close();
}

void arama(string aranan, node* dizi[])
{
	int v = aranan.length();
	ofstream  writer("sonuc.txt", ios::app);
	ofstream  depo("depo.txt", ios::app);
	int sayca = 0;
	
	node* yrd = dizi[v];
	while (yrd != NULL)
	{
		if (aranan[0]==yrd->data[0])
		{
			if (aranan == yrd->data)
			{
				writer << yrd->data << " Aramasi " << yrd->sayi << " Adet bulundu" << endl;
				writer << "TXT->:" << yrd->d1 << endl; writer << "PDF->" << yrd->d2 << endl;
				writer << "HTML->" << yrd->d3 << endl; writer << "DOCX->" << yrd->d4;

				depo << yrd->data << " Aramasi " << yrd->sayi << " Adet bulundu" << endl;
				depo << "TXT->:" << yrd->d1 << endl; depo << "PDF->" << yrd->d2 << endl;
				depo << "HTML->" << yrd->d3 << endl; depo << "DOCX->" << yrd->d4;

				sayca++;
				break;
			}
		}		
		yrd = yrd->next;
	}

	if (sayca == 0)
	{		
		writer << aranan << " aranirken ";
		writer << "Tam Eslesme Bulunamadi. >>" << endl;	
		depo << aranan << " aranirken ";
		depo << "Tam Eslesme Bulunamadi. >>" << endl;

		yakin(dizi, aranan, 0);
		yakin(dizi, aranan, 1);
		yakin(dizi, aranan, -1);

		if (aranan.length()>4)
		{
			yakin(dizi, aranan, 2);
			yakin(dizi, aranan, -2);
		}
		
	}
	writer.close();
	depo.close();
}

node *ekle(node *r, string x,int y) {

	if (r == NULL)
	{
		r = new node;
		r->data = x;
		r->next = NULL;
		if (y == 1)
			r->d1++;
		if (y == 2)
			r->d2++;
		if (y == 3)			//hangi dosyadaysan o düğümün 4 değerden birisini arttırıyor.
			r->d3++;
		if (y == 4)
			r->d4++;
		
	}
	else
	{
		int sayac = 0;
		node *yrd;
		yrd = r;
		while (yrd->next != NULL)
		{
			if (yrd->data == x)
			{
				yrd->sayi = yrd->sayi + 1;

				sayac++;
				if (y == 1)
					yrd->d1++;
				if (y == 2)
					yrd->d2++;
				if (y == 3)
					yrd->d3++;
				if (y == 4)
					yrd->d4++;

				break;
			}
			yrd = yrd->next;
		}
		
		if (yrd->data == x && sayac == 0) //yrd yukarda sonuncuya bakmıyor. Baksın diye koyuldu.
		{
			yrd->sayi = yrd->sayi + 1;
			sayac++;
			if (y == 1)
				yrd->d1++;
			if (y == 2)
				yrd->d2++;
			if (y == 3)
				yrd->d3++;
			if (y == 4)
				yrd->d4++;
		}

		if (sayac == 0)
		{			
			yrd->next = new node;
			yrd->next->data = x;
			yrd->next->next = NULL;
			if (y == 1)
				yrd->d1++;
			if (y == 2)
				yrd->d2++;
			if (y == 3)
				yrd->d3++;
			if (y == 4)
				yrd->d4++;
		}
		yrd = NULL;
		delete yrd;
	}
	return r;
}

void oku(string x, node *dizi[], int s)
{
	ifstream dosyaoku;
	dosyaoku.open(x, ios::in);
	string okunan;	
	while (dosyaoku >> okunan)
	{
		for_each(okunan.begin(), okunan.end(), [](char & c) {  //okuduğu kelimenin tüm harflerini küçültüyor.
			c = ::tolower(c);
		});

		string temp2;
		for (int i = 0; i < okunan.length(); i++)	//kelime okurken nokta,virgül vs. almaması için
		{
			if (okunan[i] >= 97 && okunan[i] <= 122)
			{
				temp2 += okunan[i];
			}
		}

		if (temp2.length() > 1)
		{
			dizi[temp2.length()] = ekle(dizi[temp2.length()], temp2, s);
		}

	}
	dosyaoku.close();

	if (x=="metin2.txt")
		remove("metin2.txt");

	 if (x == "metin4.txt")
		remove("metin4.txt");

	 cout << "#";
	
}

void htmloku(node *dizi[]){ //HTML dosyasındaki tagları kaldırıp sadece kelimeleri okuyor.
	ifstream dosyaoku3;
	dosyaoku3.open("metin3.html", ios::in);
	string okunan3;

	while (getline(dosyaoku3, okunan3))
	{
		for_each(okunan3.begin(), okunan3.end(), [](char & c) {	//okuduğu kelimenin tüm harflerini küçültüyor.
			c = ::tolower(c);
		});

		for (int i = 0; i < 10; i++)
		{
			string::size_type start = okunan3.find('<');

			if (start != okunan3.npos)
			{
				string::size_type end = okunan3.find('>', start + 1);
				if (end != okunan3.npos)
				{
					string::size_type count = end - start;
					okunan3.erase(start, count + 1);
				}
			}
		}

		string temp3;
		for (int i = 0; i <= okunan3.length(); i++)
		{
			if (okunan3[i] == ' ' || okunan3[i] == '\0')
			{

				if (temp3.length() > 1)
					dizi[temp3.length()] = ekle(dizi[temp3.length()], temp3, 3);								

				temp3 = "";

			}
			else
				if (okunan3[i] >= 97 && okunan3[i] <= 122)				
					temp3 += okunan3[i];
		}
	}

	dosyaoku3.close();
	cout << "#";
}

void gezin(node *r) {

	while (r != NULL)
	{
		cout <<"kelime: "<< r->data << " - sayi: " << r->sayi << endl;
		r = r->next;
	}
} 


void main(){

	setlocale(LC_ALL, "");
	system("color FA");

	node* dizi[35];
	for (int i = 0; i < 35; i++)
	{
		dizi[i] = NULL;
	}	
	
	system("pdfdoc.exe"); // pdf ve docx txt'ye dönüşüyor. c# ile yazıldı
	clock_t basla = clock(), bitis;

	oku("metin.txt", dizi, 1); oku("metin2.txt", dizi, 2); oku("metin4.txt", dizi, 4); htmloku(dizi);	

	bitis = clock();	
	
	cout << endl << "Dosyaların okunması " << (float)(bitis - basla) / CLOCKS_PER_SEC << " Saniyede tamamlandı." << endl;
	cout << endl;

	//gezin(dizi[6]);

	string aranan;
	clock_t basla2, bitis2;
	char selection;
	
	do
	{
		cout << "1-Arama" << endl<<endl;
		cout << "0-Çıkış" << endl;
		cout << "-> ";
		selection = _getch();

		ofstream  writer;
		ofstream depo;

		system("cls");

		cout << "~~~~~~~~~~~~~~~~BMT207 Veri Yapıları 2019-2020 Proje Ödevi~~~~~~~~~~~~~~~~"<< endl;

		cout << endl << endl;

		switch (selection)
		{
		case '1':
			cout << "Aranacak Kelimeyi Giriniz : ";
			cin >> aranan;
			cout << endl;

			basla2 = clock();

			arama(aranan, dizi);	
					
			bitis2 = clock();

			writer.open("sonuc.txt", ios::app);
			depo.open("depo.txt", ios::app);

			writer << endl << "Arama  " << (float)(bitis2 - basla2) / CLOCKS_PER_SEC << " Saniyede Tamamlandi." << endl;
			depo << endl << "Arama  " << (float)(bitis2 - basla2) / CLOCKS_PER_SEC << " Saniyede Tamamlandi." << endl;

			depo << "*********************************************************************************";

			writer << endl;
			depo << endl;

			depo.close();
			writer.close();

			system("sonuc.txt");

			remove("sonuc.txt");	

			break;
		case '0':
			cout << "Programdan Çıkılıyor..." << endl;
			system("depo.txt");
			break;
		default:			
			cout << "Yanlış Seçim Yaptınız..\nLütfen Sıfır(0) yada Bir(1) Değerlerinden Birini Giriniz." << endl;
			break;
		}
	} while (selection != '0');
		
}

