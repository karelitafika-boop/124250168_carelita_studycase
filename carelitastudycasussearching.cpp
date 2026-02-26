#include <iostream>
using namespace std;

struct Buku {
    string nama;
    int harga;
};

int main() {

    Buku data[6] = {
        {"Kisah klasik", 50000},
        {"Mewarnai", 60000},
        {"Resep memasak", 70000},
        {"Matematika", 80000},
        {"Pemrograman", 90000}
    };

    int n = 5;
    int pilihan, pilihansekuen;
    string cari;

    cout << "===== DAFTAR BUKU =====" << endl;
    for(int i = 0; i < n; i++) {
        cout << i+1 << ". " << data[i].nama << endl;
    }
    cout << "========================" << endl;


    cout << "\n=== MENU PENCARIAN ===" << endl;
    cout << "1. Pencarian Biner" << endl;
    cout << "2. Pencarian Sekuensial" << endl;
    cout << "yuk pilih (1/2): ";
    cin >> pilihan;


    if (pilihan == 2) {
        cout << "\nMetode Sekuensial:" << endl;
        cout << "1. Tanpa Sentinel" << endl;
        cout << "2. Dengan Sentinel" << endl;
        cout << "yukk dipilih lagiii! (1/2): ";
        cin >> pilihansekuen;
    }
    cin.ignore();

    cout << "\nKamu mau buku judul apa? : ";
    getline(cin, cari);


    if (pilihan == 1) {

        int awal = 0, akhir = n-1, tengah;
        bool ketemu = false;

        while (awal <= akhir && !ketemu) {
            tengah = (awal + akhir) / 2;

            if (cari == data[tengah].nama)
                ketemu = true;
            else if (cari < data[tengah].nama)
                akhir = tengah - 1;
            else
                awal = tengah + 1;
        }

        if (ketemu)
            cout << "yeyy buku yang kamu mau ditemukan! Harga: Rp "
                 << data[tengah].harga << endl;
        else
            cout << "yahhh, maaf buku yang kamu mau tidak ada ditoko ini. \ncoba masukkan ulang judul dengan penulisan yang sesuai daftar buku" << endl;
    }

    else if (pilihan == 2 && pilihansekuen == 1) {

        int i = 0;
        bool ketemu = false;

        while (i < n && !ketemu) {
            if (data[i].nama == cari)
                ketemu = true;
            else
                i++;
        }

        if (ketemu)
            cout << "yeyy buku yang kamu mau ditemukan! Harga: Rp "
                 << data[i].harga << endl;
        else
            cout << "yahhh, maaf buku yang kamu mau tidak ada ditoko ini. \ncoba masukkan ulang judul dengan penulisan yang sesuai daftar buku" << endl;
    }

    else if (pilihan == 2 && pilihansekuen == 2) {

        data[n].nama = cari; 
        int i = 0;

        while (data[i].nama != cari) {
            i++;
        }

        if (i < n)
            cout << "yeyy buku yang kamu mau ditemukan! Harga: Rp "
                 << data[i].harga << endl;
        else
            cout << "yahhh, maaf buku yang kamu mau tidak ada ditoko ini. \ncoba masukkan ulang judul dengan penulisan yang sesuai daftar buku" << endl;
    }

    else {
        cout << "maaf pilihan tidak tersedia." << endl;
    }

    return 0;
}
