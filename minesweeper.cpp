#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

const int MAKS = 10;

class Minesweeper {
private:
    int n, totalBom, flagTersisa;
    bool bom[MAKS][MAKS];
    bool buka[MAKS][MAKS];
    bool flag[MAKS][MAKS];
    int angka[MAKS][MAKS];
    bool kalah, menang;
    time_t waktuMulai;

    void tanamBom() {
        int ditanam = 0;
        while (ditanam < totalBom) {
            int r = rand() % n;
            int c = rand() % n;
            if (!bom[r][c]) {
                bom[r][c] = true;
                ditanam++;
            }
        }
    }

    void hitungAngka() {
        int dr[] = {-1,-1,-1, 0, 0, 1, 1, 1};
        int dc[] = {-1, 0, 1,-1, 1,-1, 0, 1};
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (bom[i][j]) { angka[i][j] = -1; continue; }
                int total = 0;
                for (int d = 0; d < 8; d++) {
                    int ni = i + dr[d], nj = j + dc[d];
                    if (ni >= 0 && ni < n && nj >= 0 && nj < n && bom[ni][nj])
                        total++;
                }
                angka[i][j] = total;
            }
        }
    }

    void bukaOtomatis(int r, int c) {
        if (r < 0 || r >= n || c < 0 || c >= n) return;
        if (buka[r][c] || bom[r][c] || flag[r][c]) return;
        buka[r][c] = true;
        if (angka[r][c] == 0) {
            int dr[] = {-1,-1,-1, 0, 0, 1, 1, 1};
            int dc[] = {-1, 0, 1,-1, 1,-1, 0, 1};
            for (int d = 0; d < 8; d++)
                bukaOtomatis(r + dr[d], c + dc[d]);
        }
    }

    void cekMenang() {
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++) {
                if (bom[i][j] && !flag[i][j]) return;
                if (!bom[i][j] && flag[i][j]) return;
            }
        menang = true;
    }

    void tampilkan(bool gameOver = false) {
        int detik = (int)difftime(time(NULL), waktuMulai);
        cout << "Waktu: " << detik << " detik | Flag tersisa: " << flagTersisa << endl;
        cout << endl;

        cout << "   ";
        for (int j = 0; j < n; j++) cout << " " << j+1;
        cout << endl;

        cout << "   ";
        for (int j = 0; j < n; j++) cout << "--";
        cout << endl;

        for (int i = 0; i < n; i++) {
            cout << " " << i+1 << "|";
            for (int j = 0; j < n; j++) {
                if (gameOver && bom[i][j]) cout << " *";
                else if (flag[i][j]) cout << " F";
                else if (!buka[i][j]) cout << " .";
                else if (angka[i][j] == 0) cout << "  ";
                else cout << " " << angka[i][j];
            }
            cout << endl;
        }
        cout << endl;
        cout << "[ . ] belum dibuka  [ F ] flag  [   ] kosong  [1-8] angka" << endl;
    }

public:
    Minesweeper() {
        n = 5; totalBom = 5; flagTersisa = 5;
        kalah = false; menang = false;
    }

    void reset() {
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                bom[i][j] = buka[i][j] = flag[i][j] = false, angka[i][j] = 0;
        kalah = menang = false;
        flagTersisa = totalBom;
    }

    void mulaiMain() {
        cout << "Ukuran papan (4-10): ";
        cin >> n;
        while (n < 4 || n > 10) {
            cout << "Harus antara 4-10: ";
            cin >> n;
        }

        cout << "Jumlah bom (1-" << n*n-1 << "): ";
        cin >> totalBom;
        while (totalBom < 1 || totalBom >= n*n) {
            cout << "Harus antara 1-" << n*n-1 << ": ";
            cin >> totalBom;
        }

        reset();
        srand(time(NULL));
        tanamBom();
        hitungAngka();
        waktuMulai = time(NULL);

        cout << "Aksi : 1 = Buka kotak, 2 = Pasang/cabut flag" << endl;

        while (!kalah && !menang) {
            tampilkan();

            int aksi, r, c;
            cout << "Aksi (1/2) : "; cin >> aksi;
            cout << "Baris : "; cin >> r;
            cout << "Kolom : "; cin >> c;

            if (aksi < 1 || aksi > 2 || r < 1 || r > n || c < 1 || c > n) {
                cout << "Input tidak valid" << endl;
                continue;
            }

            r--; c--;

            if (aksi == 1) {
                if (buka[r][c]) { cout << "Sudah terbuka" << endl; continue; }
                if (flag[r][c]) { cout << "Cabut flag dulu" << endl; continue; }
                if (bom[r][c]) {
                    buka[r][c] = true;
                    kalah = true;
                } else {
                    bukaOtomatis(r, c);
                    cekMenang();
                }
            } else {
                if (buka[r][c]) { cout << "Tidak bisa flag kotak terbuka" << endl; continue; }
                if (!flag[r][c] && flagTersisa == 0) { cout << "Flag habis" << endl; continue; }
                flag[r][c] = !flag[r][c];
                flagTersisa += flag[r][c] ? -1 : 1;
                cout << (flag[r][c] ? "Flag dipasang" : "Flag dicabut") << endl;
                cekMenang();
            }
        }

        int waktu = (int)difftime(time(NULL), waktuMulai);
        if (kalah) {
        tampilkan(true);
        cout << "Game over! kena bom :(" << endl;
        } else {
        tampilkan();
        cout << "Selamat! kamu menang :p" << endl;
        }
        cout << "Waktu : " << waktu << " detik" << endl;
    }
};

int main() {
    Minesweeper game;
    int pilih;
    do {
        cout << "=== Minesweeper Game ===" << endl;
        cout << "1. Mulai Permainan" << endl;
        cout << "2. Keluar" << endl;
        cout << "Pilih : "; cin >> pilih;
        if (pilih == 1) game.mulaiMain();
    } while (pilih != 2);

    cout << "Game selesai, sampai jumpa ><" << endl;
    return 0;
}