#include <iostream>
#include <ctime>
#include <cstdlib>
using namespace std;

const int MAX_MOBIL = 20;
const int TARIF_PER_JAM = 5000;

struct Petugas {
    string nama;
    string id;
};

struct Mobil {
    string plat;
    string merk;
    string warna;
    time_t waktuMasuk;
    bool terparkir;
};

class SistemParkir {
private:
    Mobil daftarMobil[MAX_MOBIL];
    int jumlahMobil;

public:
    SistemParkir() {
        jumlahMobil = 0;

        for (int i = 0; i < MAX_MOBIL; i++) {
            daftarMobil[i].terparkir = false;
        }
    }

    void tambahKendaraan() {
        int jumlahInput;

        if (jumlahMobil >= MAX_MOBIL) {
            cout << "\nMaaf, parkiran penuh! Maksimal "
                 << MAX_MOBIL << " mobil.\n";
            return;
        }

        cout << "\nMasukkan jumlah mobil yang akan diparkir : ";
        cin >> jumlahInput;

        if (jumlahMobil + jumlahInput > MAX_MOBIL) {
            cout << "\nMaaf, parkiran hanya dapat memuat "
                 << MAX_MOBIL << " mobil.\n";

            jumlahInput = MAX_MOBIL - jumlahMobil;

            cout << "Hanya "
                 << jumlahInput
                 << " mobil yang dapat ditambahkan.\n";
        }

        cin.ignore(1000, '\n');

        Mobil* ptrMobil = daftarMobil;

        for (int i = 0; i < jumlahInput; i++) {
            cout << "\nMobil ke-" << jumlahMobil + 1 << endl;

            cout << "Masukkan plat mobil : ";
            getline(cin, (ptrMobil + jumlahMobil)->plat);

            cout << "Masukkan merk mobil : ";
            getline(cin, (ptrMobil + jumlahMobil)->merk);

            cout << "Masukkan warna mobil : ";
            getline(cin, (ptrMobil + jumlahMobil)->warna);

            (ptrMobil + jumlahMobil)->waktuMasuk = time(0);
            (ptrMobil + jumlahMobil)->terparkir = true;

            jumlahMobil++;
        }

        cout << "\nData kendaraan berhasil ditambahkan!\n";
    }

    void tampilkanKendaraan() {
        if (jumlahMobil == 0) {
            cout << "\nBelum ada kendaraan di parkiran.\n";
            return;
        }

        cout << "\n=====================================\n";
        cout << "DAFTAR MOBIL YANG SEDANG TERPARKIR\n";
        cout << "=====================================\n";

        for (int i = 0; i < jumlahMobil; i++) {
            time_t sekarang = time(0);

            int durasi =
                difftime(sekarang,
                         daftarMobil[i].waktuMasuk);

            int jam = durasi / 3600;
            int menit = (durasi % 3600) / 60;
            int detik = durasi % 60;

            cout << "\nMobil ke-" << i + 1 << endl;
            cout << "Plat Mobil  : "
                 << daftarMobil[i].plat << endl;

            cout << "Merk Mobil  : "
                 << daftarMobil[i].merk << endl;

            cout << "Warna Mobil : "
                 << daftarMobil[i].warna << endl;

            cout << "Durasi Parkir : "
                 << jam << " jam "
                 << menit << " menit "
                 << detik << " detik\n";
        }
    }

    void pembayaran() {
        if (jumlahMobil == 0) {
            cout << "\nTidak ada kendaraan di parkiran.\n";
            return;
        }

        string cariPlat;
        bool ditemukan = false;

        cin.ignore(1000, '\n');

        cout << "\nMasukkan plat mobil yang ingin dibayar : ";
        getline(cin, cariPlat);

        for (int i = 0; i < jumlahMobil; i++) {
            if (daftarMobil[i].plat == cariPlat &&
                daftarMobil[i].terparkir) {

                ditemukan = true;

                time_t sekarang = time(0);

                double durasiJam =
                    difftime(sekarang,
                             daftarMobil[i].waktuMasuk) / 3600.0;

                int biaya;

                if (durasiJam < 1) {
                    biaya = TARIF_PER_JAM;
                } else {
                    biaya =
                        (int)(durasiJam + 1)
                        * TARIF_PER_JAM;
                }

                cout << "\n=====================================\n";
                cout << "BIAYA PARKIR : Rp"
                     << biaya << endl;
                cout << "=====================================\n";

                cout << "Mobil dengan plat "
                     << daftarMobil[i].plat
                     << " telah keluar.\n";

                daftarMobil[i].terparkir = false;

                for (int j = i; j < jumlahMobil - 1; j++) {
                    daftarMobil[j] = daftarMobil[j + 1];
                }

                jumlahMobil--;
                break;
            }
        }

        if (!ditemukan) {
            cout << "\nPLAT TIDAK DITEMUKAN!\n";
        }
    }
};

void tampilMenu() {
    cout << "\n=====================================\n";
    cout << "        SISTEM PARKIR MALL\n";
    cout << "           MALL PRIENAL\n";
    cout << "=====================================\n";
    cout << "1. Tambahkan Daftar Kendaraan\n";
    cout << "2. Tampilkan Daftar Kendaraan\n";
    cout << "3. Pembayaran\n";
    cout << "4. Keluar Program\n";
    cout << "Masukkan opsi : ";
}

int main() {
    system("cls");

    Petugas petugas;

    cout << "=====================================\n";
    cout << "   SELAMAT DATANG DI PARKIR MALL\n";
    cout << "           MALL PRIENAL\n";
    cout << "=====================================\n";

    cout << "Masukkan nama petugas : ";
    getline(cin, petugas.nama);

    cout << "Masukkan ID petugas : ";
    getline(cin, petugas.id);

    SistemParkir parkir;

    int pilihan;

    do {
        cout << "\nNama Petugas : "
             << petugas.nama << endl;

        cout << "ID Petugas   : "
             << petugas.id << endl;

        tampilMenu();

        cin >> pilihan;

        switch (pilihan) {
        case 1:
            parkir.tambahKendaraan();
            break;

        case 2:
            parkir.tampilkanKendaraan();
            break;

        case 3:
            parkir.pembayaran();
            break;

        case 4:
            cout << "\nTerima kasih telah menggunakan program.\n";
            break;

        default:
            cout << "\nPilihan tidak valid!\n";
        }

    } while (pilihan != 4);

    return 0;
}
