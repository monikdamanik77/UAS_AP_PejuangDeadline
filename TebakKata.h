#ifndef TEBAKKATA_H
#define TEBAKKATA_H

#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <cctype>

using namespace std;

struct KataGame {
    string kataAsli;          
    string statusTebakan;     
    int sisaNyawa;            
    char tebakanSalah[26];    
    int jumlahSalah;          
};

const string BANK_KATA[] = {
    "ALGORITMA", "STRUKTUR", "POINTER", "VARIABEL", "FUNGSI",
    "PROGRAMMING", "COMPILER", "INFORMATIKA", "LOOPING", "KONDISIONAL",
    "MAHASISWA", "TERMINAL", "DATABASE", "BOOLEAN", "HARDWARE",
    "SOFTWARE", "NETWORK", "ALPROG", "VECTOR", "LIBRARY",
    "DYNAMIC", "OBJECT", "MATRIX", "ELEMENT", "ROUTER"
};

int pilihKesulitan() {
    int pilihan;
    cout << "=================================\n";
    cout << "   PILIH TINGKAT KESULITAN       \n";
    cout << "=================================\n";
    cout << "1. Easy   (8 Nyawa)\n";
    cout << "2. Medium (6 Nyawa)\n";
    cout << "3. Hard   (4 Nyawa)\n";
    cout << "Pilihan Anda (1-3): ";
    cin >> pilihan;
    
    switch(pilihan) {
        case 1: return 8;
        case 2: return 6;
        case 3: return 4;
        default: 
            cout << "Pilihan tidak valid. Otomatis memilih Medium.\n";
            return 6;
    }
}

void inisialisasiGame(KataGame* game, int nyawa) {
    int indexAcak = rand() % 25;
    game->kataAsli = BANK_KATA[indexAcak];
    
    game->statusTebakan = string(game->kataAsli.length(), '_');
    
    game->sisaNyawa = nyawa;
    game->jumlahSalah = 0;

    for(int i = 0; i < 26; i++) {
        game->tebakanSalah[i] = ' ';
    }
}

void tampilkanStatus(const KataGame* game) {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif

    cout << "=========================================\n";
    cout << "           GAME TEBAK KATA CLI           \n";
    cout << "=========================================\n\n";
    
    cout << "Kata Rahasia : ";
    for (char c : game->statusTebakan) {
        cout << c << " ";
    }
    cout << "\n\n";

    cout << "Sisa Nyawa   : " << game->sisaNyawa << "\n";

    cout << "Huruf Salah  : ";
    for (int i = 0; i < game->jumlahSalah; i++) {
        cout << game->tebakanSalah[i] << " ";
    }
    cout << "\n-----------------------------------------\n";
}

void prosesTebakan(KataGame* game, char tebakan) {
    for (char c : game->statusTebakan) {
        if (c == tebakan) {
            cout << "\nPeringatan: Huruf '" << tebakan << "' sudah pernah ditebak dan BENAR!\n";
            cout << "Tekan Enter untuk lanjut...";
            cin.ignore(); cin.get();
            return;
        }
    }
    for (int i = 0; i < game->jumlahSalah; i++) {
        if (game->tebakanSalah[i] == tebakan) {
            cout << "\nPeringatan: Huruf '" << tebakan << "' sudah pernah ditebak dan SALAH!\n";
            cout << "Tekan Enter untuk lanjut...";
            cin.ignore(); cin.get();
            return;
        }
    }

    bool ditemukan = false;
    for (size_t i = 0; i < game->kataAsli.length(); i++) {
        if (game->kataAsli[i] == tebakan) {
            game->statusTebakan[i] = tebakan; 
            ditemukan = true;
        }
    }

    if (!ditemukan) {
        game->tebakanSalah[game->jumlahSalah] = tebakan;
        game->jumlahSalah++;
        game->sisaNyawa--;
        cout << "\nTebakan SALAH!\n";
        cout << "Tekan Enter untuk lanjut...";
        cin.ignore(); cin.get();
    } else {
        cout << "\nTebakan BENAR!\n";
        cout << "Tekan Enter untuk lanjut...";
        cin.ignore(); cin.get();
    }
}

#endif