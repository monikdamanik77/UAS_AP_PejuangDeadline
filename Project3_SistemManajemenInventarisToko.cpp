#include <iostream> 
#include <vector>
#include <cstdlib>
using namespace std;

struct Barang {
    string kodeBarang;
    string namaBarang;
    double harga;
    int stok;
};

vector <Barang> daftarBarang;


void tambah_barang() {
    Barang barang;

    cout << "Masukkan kode barang: ";
    cin >> barang.kodeBarang;

    cout << "Masukkan nama barang: ";
    cin >> barang.namaBarang;

    do {
    cout << "Masukkan harga barang: ";
    cin >> barang.harga;
    if (barang.harga < 0) {
        cout << "--- Error !!! (harga barang ga boleh negatif) ---";
    } } while (barang.harga < 0);

    do {
    cout << "Masukkan stok barang: ";
    cin >> barang.stok;
    if (barang.stok < 0) {
        cout << "--- Error !!! (stok barang ga boleh negatif) ---";
    } 
        } while (barang.stok < 0);

    daftarBarang.push_back(barang);
    cout << endl << "Barang berhasil ditambahkan" << endl;
}


void tampilkan_semua_barang() {
    if (daftarBarang.size() == 0) {
        cout << endl << "Belum ada data barang" << endl;
    }

    for (int i = 0; i < daftarBarang.size(); i++) {
        cout << endl << "Barang ke-" << i + 1 << endl;
        cout << "Kode  : " << daftarBarang[i].kodeBarang << endl;
        cout << "Nama  : " << daftarBarang[i].namaBarang << endl;
        cout << "Harga : " << daftarBarang[i].harga << endl;
        cout << "Stok  : " << daftarBarang[i].stok << endl;
    }
}


void cari_barang_termahal() {
     if (daftarBarang.size() == 0) {
        cout << endl << "Belum ada data barang" << endl;
    }

    int termahal = 0;
    for (int i = 1; i < daftarBarang.size(); i++) {
        if (daftarBarang[i].harga > daftarBarang[termahal].harga) {
            termahal = i;
        }
    }
        cout << endl << "Barang Termahal" << endl;
        cout << "Kode  : " << daftarBarang[termahal].kodeBarang << endl;
        cout << "Nama  : " << daftarBarang[termahal].namaBarang << endl;
        cout << "Harga : " << daftarBarang[termahal].harga << endl;
        cout << "Stok  : " << daftarBarang[termahal].stok << endl;
}


void hitung_total_nilai_inventaris() {
    double total = 0;
    
    for (int i = 0; i < daftarBarang.size(); i++) {
        total += daftarBarang[i].harga * daftarBarang[i].stok;
    }
        cout << endl << "Total nilai inventaris = " << total << endl;
}


void cek_restock() {
    cout << endl << "Barang yg perlu direstock: " << endl;
     for (int i = 0; i < daftarBarang.size(); i++) {
        if (daftarBarang[i].stok < 5) {
            cout << daftarBarang[i].kodeBarang << " - " << daftarBarang[i].namaBarang << " (stok: " << daftarBarang[i].stok << ")" << endl;
        }
    }
}


void update_stock() {
    string kode;

    cout << "Masukkan kode barang: ";
    cin >> kode;

    for (int i = 0; i < daftarBarang.size(); i++)
    {
        if (daftarBarang[i].kodeBarang == kode)
        {
            int *ptr = &daftarBarang[i].stok;
            cout << "Stok saat ini: " << *ptr << endl;
            cout << "Masukkan stok baru: ";
            cin >> *ptr;
            cout << "Stok berhasil diubah" << endl;
            return;
        }
    }
        cout << "Barang tidak ditemukan" << endl;
}

int main () {
    system ("cls");
    int pilihan;

    do{
        cout << endl << "Sistem Manajemen Inventaris Toko" << endl;
        cout << "Daftar menu: " << endl;
        cout << "1. Tambah barang" << endl;
        cout << "2. Tampilkan semua barang" << endl;
        cout << "3. Barang termahal" << endl;
        cout << "4. Total nilai inventaris (total harga seluruh aset)" << endl;
        cout << "5. Cek Restock " << endl;
        cout << "6. Update Stok " << endl;
        cout << "7. Keluar " << endl;
        cout << "Pilih daftar menunya (cukup angka aja): ";
        cin >> pilihan;

        switch (pilihan) {
            case 1:
                tambah_barang();
                break;
            case 2:
                tampilkan_semua_barang();
                break;
            case 3:
                cari_barang_termahal();
                break;
            case 4:
                hitung_total_nilai_inventaris();
                break;
            case 5:
                cek_restock();
                break;
            case 6:
                update_stock();
                break;
            case 7:
                cout << "Selesai";
                break;
            default:
                cout << "Menu yg kamu pilih salah" << endl;
        } 
    } while (pilihan != 7);
}
