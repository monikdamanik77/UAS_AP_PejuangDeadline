#include "TebakKata.h"

int main() {
    srand(static_cast<unsigned int>(time(0)));
    
    char mainLagi;
    
    do {
        #ifdef _WIN32
            system("cls");
        #else
            system("clear");
        #endif
        
        cout << "=================================\n";
        cout << "  SELAMAT DATANG DI TEBAK KATA   \n";
        cout << "=================================\n\n";
        
        int nyawaAwal = pilihKesulitan();
        
        KataGame game;
        inisialisasiGame(&game, nyawaAwal);
     
        while (game.sisaNyawa > 0 && game.statusTebakan != game.kataAsli) {
            tampilkanStatus(&game);
            
            char inputUser;
            cout << "Masukkan tebakan huruf Anda: ";
            cin >> inputUser;

            inputUser = toupper(inputUser);

            prosesTebakan(&game, inputUser);
        }

        tampilkanStatus(&game);

        if (game.statusTebakan == game.kataAsli) {
            int poinPerNyawa = 10; 

            if (nyawaAwal == 6) {     
                poinPerNyawa = 20;
            } else if (nyawaAwal == 4) { 
                poinPerNyawa = 30;
            }

            int skorAkhir = game.sisaNyawa * poinPerNyawa;
            
            cout << "\n=========================================\n";
            cout << " CONGRATULATIONS! Anda Berhasil Menang! \n";
            cout << " Kata rahasia adalah: " << game.kataAsli << "\n";
            cout << " Sisa Nyawa         : " << game.sisaNyawa << "\n";
            cout << " Total Skor Anda    : " << skorAkhir << " Poin\n"; 
            cout << "=========================================\n";
        } else {
            cout << "\n=========================================\n";
            cout << " GAME OVER! Anda Kehabisan Nyawa.       \n";
            cout << " Kata yang benar adalah: " << game.kataAsli << "\n";
            cout << "=========================================\n";
        }

        cout << "\nApakah Anda ingin bermain lagi? (Y/N): ";
        cin >> mainLagi;
        mainLagi = toupper(mainLagi);
        
    } while (mainLagi == 'Y');
    
    cout << "\nTerima kasih telah bermain game buatan Nisa! Sampai jumpa!\n";
    return 0;
}
