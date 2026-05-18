#include <iostream>
#include <string>
#include <cstdlib>
using namespace std;

const int MAX_PARKIR = 3;
const int MAX_DATA = 100;

int jumlahParkir = 0;

struct Kendaraan {
    string nopol;
    string nama;
    string status;
    Kendaraan *kiri;
    Kendaraan *kanan;
};

struct Aksi {
    string jenis;
    string nopol;
    string antrianMasuk;
};

Kendaraan *root = NULL; // root untuk PTB

Aksi stackUndo[MAX_DATA]; // stack manual untuk riwayat aksi
int top = -1;

string queueAntrian[MAX_DATA]; // queue manual untuk antrian kendaraan
int depan = 0;
int belakang = -1;

void cls() {
    system("cls"); // biar tampilan bersih
}

void pause() {
    cout << "\nTekan Enter untuk kembali ke menu...";
    cin.get();
}

string kapital(string teks) {
    for (int i = 0; i < (int)teks.length(); i++) {
        if (teks[i] >= 'a' && teks[i] <= 'z') {
            teks[i] = teks[i] - 32;
        }
    }
    return teks;
}

Kendaraan* buatNode(string nopol, string nama) {
    Kendaraan *baru = new Kendaraan;
    baru->nopol = nopol;
    baru->nama = nama;
    baru->status = "Di Luar Parkiran";
    baru->kiri = NULL;
    baru->kanan = NULL;
    return baru;
}

Kendaraan* tambahPTB(Kendaraan *root, string nopol, string nama) {
    if (root == NULL) {
        cout << "Data kendaraan berhasil ditambahkan\n";
        return buatNode(nopol, nama);
    }

    if (nopol < root->nopol) {
        root->kiri = tambahPTB(root->kiri, nopol, nama);
    } else if (nopol > root->nopol) {
        root->kanan = tambahPTB(root->kanan, nopol, nama);
    } else {
        cout << "Nomor polisi sudah terdaftar!\n";
    }

    return root;
}

Kendaraan* cari(Kendaraan *root, string nopol) {
    if (root == NULL || root->nopol == nopol) {
        return root;
    }

    if (nopol < root->nopol) {
        return cari(root->kiri, nopol);
    } else {
        return cari(root->kanan, nopol);
    }
}

void tampil(Kendaraan *root) {
    if (root != NULL) {
        tampil(root->kiri);

        cout << "Nomor Polisi : " << root->nopol << endl;
        cout << "Nama Pemilik : " << root->nama << endl;
        cout << "Status       : " << root->status << endl;
        cout << "-----------------------------\n";

        tampil(root->kanan);
    }
}

void pushStack(string jenis, string nopol, string antrianMasuk) {
    if (top < MAX_DATA - 1) {
        top++;
        stackUndo[top].jenis = jenis;
        stackUndo[top].nopol = nopol;
        stackUndo[top].antrianMasuk = antrianMasuk;
    }
}

bool queueKosong() {
    return depan > belakang;
}

bool queuePenuh() {
    return belakang == MAX_DATA - 1;
}

void enqueue(string nopol) {
    if (!queuePenuh()) {
        belakang++;
        queueAntrian[belakang] = nopol;
    }
}

string dequeue() {
    string data = queueAntrian[depan];
    depan++;
    return data;
}

bool adaDiAntrian(string nopol) {
    for (int i = depan; i <= belakang; i++) {
        if (queueAntrian[i] == nopol) {
            return true;
        }
    }
    return false;
}

void hapusDariAntrian(string nopol) {
    for (int i = depan; i <= belakang; i++) {
        if (queueAntrian[i] == nopol) {
            for (int j = i; j < belakang; j++) {
                queueAntrian[j] = queueAntrian[j + 1];
            }
            belakang--;
            break;
        }
    }
}

void masukDepanAntrian(string nopol) {
    if (depan > 0) {
        depan--;
        queueAntrian[depan] = nopol;
    } else if (!queuePenuh()) {
        for (int i = belakang; i >= depan; i--) {
            queueAntrian[i + 1] = queueAntrian[i];
        }
        queueAntrian[depan] = nopol;
        belakang++;
    }
}

Kendaraan* cariTerkecil(Kendaraan *root) {
    while (root->kiri != NULL) {
        root = root->kiri;
    }
    return root;
}

Kendaraan* hapusPTB(Kendaraan *root, string nopol) {
    if (root == NULL) {
        return root;
    }

    if (nopol < root->nopol) {
        root->kiri = hapusPTB(root->kiri, nopol);
    } else if (nopol > root->nopol) {
        root->kanan = hapusPTB(root->kanan, nopol);
    } else {
        if (root->status == "Di Parkiran") {
            jumlahParkir--;
        }

        hapusDariAntrian(nopol);

        if (root->kiri == NULL) {
            Kendaraan *temp = root->kanan;
            delete root;
            return temp;
        } else if (root->kanan == NULL) {
            Kendaraan *temp = root->kiri;
            delete root;
            return temp;
        }

        Kendaraan *temp = cariTerkecil(root->kanan);
        root->nopol = temp->nopol;
        root->nama = temp->nama;
        root->status = temp->status;
        root->kanan = hapusPTB(root->kanan, temp->nopol);
    }

    return root;
}

void tambahKendaraan() {
    cls();

    string nopol, nama;

    cout << "===== TAMBAH DATA KENDARAAN =====\n";
    cout << "yuk masukkin nomor polisi: ";
    getline(cin, nopol);
    nopol = kapital(nopol);

    cout << "skrng masukkin nama pemilik: ";
    getline(cin, nama);

    root = tambahPTB(root, nopol, nama); // data masuk ke PTB

    pause();
}

void tampilKendaraan() {
    cls();

    cout << "===== DATA KENDARAAN =====\n";

    if (root == NULL) {
        cout << "data kendaraan masi kosong! isi dlu ya\n";
    } else {
        tampil(root);
    }

    pause();
}

void kendaraanMasuk() {
    cls();

    string nopol;

    cout << "===== KENDARAAN MASUK =====\n";
    cout << "yuk masukkin nomor polisi: ";
    getline(cin, nopol);
    nopol = kapital(nopol);

    Kendaraan *data = cari(root, nopol);

    if (data == NULL) {
        cout << "yahh kendaraan ga ketemuu!\n";
        pause();
        return;
    }

    if (data->status == "Di Parkiran") {
        cout << "kendaraanmu udah didalem parkiran!\n";
        pause();
        return;
    }

    if (jumlahParkir < MAX_PARKIR) {
        data->status = "Di Parkiran";
        jumlahParkir++;

        pushStack("MASUK", nopol, ""); // disimpan ke stack untuk undo

        cout << "Kendaraan berhasil masuk\n";
    } else {
        if (!adaDiAntrian(nopol)) {
            enqueue(nopol); // kalau penuh masuk queue
            cout << "yahh parkiran penuh, kendaraan masuk ke dalam antrian\n";
        } else {
            cout << "Kendaraan sudah ada di antrian!\n";
        }
    }

    pause();
}

void kendaraanKeluar() {
    cls();

    string nopol;

    cout << "===== KENDARAAN KELUAR =====\n";
    cout << "yukk masukkin nomor polisi: ";
    getline(cin, nopol);
    nopol = kapital(nopol);

    Kendaraan *data = cari(root, nopol);

    if (data == NULL) {
        cout << "yahh kendaraan tidak ditemukan!\n";
        pause();
        return;
    }

    if (data->status == "Di Luar Parkiran") {
        cout << "Kendaraan sedang tidak berada di parkiran!\n";
        pause();
        return;
    }

    data->status = "Di Luar Parkiran";
    jumlahParkir--;

    string antrianMasuk = "";

    cout << "yey kendaraan berhasil keluar\n";

    if (!queueKosong()) {
        string nopolAntrian = dequeue(); // ambil antrian pertama

        Kendaraan *dataAntrian = cari(root, nopolAntrian);

        if (dataAntrian != NULL) {
            dataAntrian->status = "Di Parkiran";
            jumlahParkir++;
            antrianMasuk = nopolAntrian;

            cout << "Kendaraan berikutnya langsung masuk ke area parkir dari antrian\n";
        }
    }

    pushStack("KELUAR", nopol, antrianMasuk); // aksi keluar disimpan

    pause();
}

void hapusKendaraan() {
    cls();

    string nopol;

    cout << "===== HAPUS DATA KENDARAAN =====\n";
    cout << "tadi nomor polisi yang ingin dihapus apa: ";
    getline(cin, nopol);
    nopol = kapital(nopol);

    Kendaraan *data = cari(root, nopol);

    if (data == NULL) {
        cout << "yahh kendaraan tidak ditemukan!\n";
    } else {
        root = hapusPTB(root, nopol);
        cout << "data kendaraan berhasil dihapus\n";
    }

    pause();
}

void undoAksi() {
    cls();

    cout << "===== UNDO AKSI TERAKHIR =====\n";

    if (top == -1) {
        cout << "Tidak ada aksi untuk di-undo\n";
        pause();
        return;
    }

    Aksi terakhir = stackUndo[top];
    top--;

    Kendaraan *data = cari(root, terakhir.nopol);

    if (data == NULL) {
        cout << "yahh data kendaraan tidak ditemukan, undo gagal!\n";
        pause();
        return;
    }

    if (terakhir.jenis == "MASUK") {
        data->status = "Di Luar Parkiran";
        jumlahParkir--;

        cout << "Undo: Kendaraan keluar dari parkiran\n";
    } else if (terakhir.jenis == "KELUAR") {
        data->status = "Di Parkiran";
        jumlahParkir++;

        if (terakhir.antrianMasuk != "") {
            Kendaraan *dataAntrian = cari(root, terakhir.antrianMasuk);

            if (dataAntrian != NULL) {
                dataAntrian->status = "Di Luar Parkiran";
                jumlahParkir--;
                masukDepanAntrian(terakhir.antrianMasuk);
            }
        }

        cout << "Undo: Kendaraan masuk kembali ke parkiran\n";
    }

    pause();
}

void tampilAntrian() {
    cls();

    cout << "===== ANTRIAN KENDARAAN =====\n";

    if (queueKosong()) {
        cout << "Antrian kosong\n";
        pause();
        return;
    }

    int nomor = 1;

    for (int i = depan; i <= belakang; i++) {
        cout << nomor << ". " << queueAntrian[i] << " menunggu antrian ke-" << nomor << endl;
        nomor++;
    }

    pause();
}

int main() {
    int pilih;

    do {
        cls();

        cout << "===== SISTEM PARKIR INAP BANDARA GSA =====\n";
        cout << "Kapasitas Parkir : " << MAX_PARKIR << endl;
        cout << "Terisi           : " << jumlahParkir << endl;
        cout << "Sisa Parkir      : " << MAX_PARKIR - jumlahParkir << endl;
        cout << "==========================================\n";
        cout << "1. Tambah Data Kendaraan\n";
        cout << "2. Tampil Kendaraan\n";
        cout << "3. Kendaraan Masuk\n";
        cout << "4. Kendaraan Keluar\n";
        cout << "5. Hapus Data Kendaraan\n";
        cout << "6. Undo Aksi Terakhir\n";
        cout << "7. Tampil Antrian Kendaraan\n";
        cout << "8. Keluar\n";
        cout << "==========================================\n";
        cout << "Pilih menu: ";
        cin >> pilih;
        cin.ignore();

        switch (pilih) {
            case 1:
                tambahKendaraan();
                break;

            case 2:
                tampilKendaraan();
                break;

            case 3:
                kendaraanMasuk();
                break;

            case 4:
                kendaraanKeluar();
                break;

            case 5:
                hapusKendaraan();
                break;

            case 6:
                undoAksi();
                break;

            case 7:
                tampilAntrian();
                break;

            case 8:
                cls();
                cout << "papaiiii programm selesaii! makasiii yaashhhh\n";
                break;

            default:
                cout << "\nyahh menu tidak tersedia!\n";
                pause();
        }

    } while (pilih != 8);

    return 0;
}
