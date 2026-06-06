#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <random>
#include <ctime>

using namespace std;

mt19937 mesinAcak(time(0));

string acakNegara(const string& negara)
{
    string hasil = negara;
    int panjang = negara.length();

    vector<int> indeks;

    for (int i = 0; i < panjang; i++)
    {
        if (negara[i] != ' ')
        {
            indeks.push_back(i);
        }
    }

    shuffle(indeks.begin(), indeks.end(), mesinAcak);

    int jumlahDisembunyikan = indeks.size() / 2;

    for (int i = 0; i < jumlahDisembunyikan; i++)
    {
        hasil[indeks[i]] = '_';
    }

    return hasil;
}

int main()
{
    vector<string> negara = {
        "indonesia",
        "malaysia",
        "singapore",
        "thailand",
        "vietnam",
        "brunei",
        "norway",
        "germany",
        "canada",
        "japan",
        "china",
        "australia",
        "france",
        "italy",
        "spain"
    };

    int skor = 0;
    char lagi;

    do
    {
        
           
        

        uniform_int_distribution<int> acak(0, negara.size() - 1);
        int indeks = acak(mesinAcak);

        string jawabanBenar = negara[indeks];
        string soal = acakNegara(jawabanBenar);

        cout << "\n GAME TEBAK NEGARA \n";
        cout << "Tebak negara berikut : " << soal << endl;

        string jawaban;
        cout << "Jawaban : ";
        cin >> jawaban;

        if (jawaban == jawabanBenar)
        {
            skor++;
            cout << "Selamat! Anda benar." << endl;
        }
        else
        {
            cout << "Maaf, jawaban Anda salah." << endl;
            cout << "Jawaban yang benar adalah : " << jawabanBenar << endl;
        }

        cout << "Skor saat ini : " << skor << endl;

        

        cout << "\nIngin bermain lagi? (y/n) : ";
        cin >> lagi;

    } while (lagi == 'y' || lagi == 'Y');

    cout << "\n GAME SELESAI" << endl;
    cout << "Skor akhir Anda : " << skor << endl;
    cout << "Terima kasih telah bermain!" << endl;

    return 0;
}