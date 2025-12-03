#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <string>

using namespace std;

const int MAX_BARANG = 100;

struct Barang {
    int id;
    string nama;
    int stok;
    double harga;
};

Barang daftarBarang[MAX_BARANG];
int jumlahBarang = 0;

// ================== FUNGSI UTILITAS ==================
void muatDariFile(const string& namaFile) {
    ifstream file(namaFile);
    if (!file.is_open()) {
        // Jika file belum ada, anggap kosong
        cout << "File " << namaFile << " belum ada. Mulai dengan data kosong.\n";
        return;
    }

    jumlahBarang = 0;
    string line;
    while (getline(file, line) && jumlahBarang < MAX_BARANG) {
        if (line.empty()) continue;

        stringstream ss(line);
        string idStr, nama, stokStr, hargaStr;

        // Format: id|nama|stok|harga
        if (!getline(ss, idStr, '|')) continue;
        if (!getline(ss, nama, '|')) continue;
        if (!getline(ss, stokStr, '|')) continue;
        if (!getline(ss, hargaStr, '|')) continue;

        Barang b;
        b.id = stoi(idStr);
        b.nama = nama;
        b.stok = stoi(stokStr);
        b.harga = stod(hargaStr);

        daftarBarang[jumlahBarang++] = b;
    }

    file.close();
    cout << "Data berhasil dimuat dari " << namaFile << ". Jumlah barang: "
        << jumlahBarang << "\n";
}

void simpanKeFile(const string& namaFile) {
    ofstream file(namaFile);
    if (!file.is_open()) {
        cout << "Gagal membuka file " << namaFile << " untuk disimpan.\n";
        return;
    }

    for (int i = 0; i < jumlahBarang; ++i) {
        file << daftarBarang[i].id << "|"
            << daftarBarang[i].nama << "|"
            << daftarBarang[i].stok << "|"
            << daftarBarang[i].harga << "\n";
    }

    file.close();
    cout << "Data berhasil disimpan ke " << namaFile << "\n";
}

int cariIndexById(int id) {
    for (int i = 0; i < jumlahBarang; ++i) {
        if (daftarBarang[i].id == id) return i;
    }
    return -1;
}

// ================== CRUD ==================
void tampilkanBarang() {
    if (jumlahBarang == 0) {
        cout << "Belum ada data barang.\n";
        return;
    }

    cout << left << setw(5) << "ID"
        << left << setw(20) << "Nama"
        << left << setw(10) << "Stok"
        << left << setw(10) << "Harga" << "\n";
    cout << string(50, '-') << "\n";

    for (int i = 0; i < jumlahBarang; ++i) {
        cout << left << setw(5) << daftarBarang[i].id
            << left << setw(20) << daftarBarang[i].nama
            << left << setw(10) << daftarBarang[i].stok
            << left << setw(10) << daftarBarang[i].harga
            << "\n";
    }
}

void tambahBarang() {
    if (jumlahBarang >= MAX_BARANG) {
        cout << "Array penuh, tidak bisa menambah barang lagi.\n";
        return;
    }

    Barang b;
    cout << "Masukkan ID         : ";
    cin >> b.id;
    cin.ignore(); // bersihkan newline

    if (cariIndexById(b.id) != -1) {
        cout << "ID sudah digunakan, silakan pakai ID lain.\n";
        return;
    }

    cout << "Masukkan Nama Barang: ";
    getline(cin, b.nama);

    cout << "Masukkan Stok       : ";
    cin >> b.stok;

    cout << "Masukkan Harga      : ";
    cin >> b.harga;

    daftarBarang[jumlahBarang++] = b;
    cout << "Barang berhasil ditambahkan.\n";
}

void ubahBarang() {
    if (jumlahBarang == 0) {
        cout << "Belum ada data barang.\n";
        return;
    }

    int id;
    cout << "Masukkan ID barang yang akan diubah: ";
    cin >> id;
    cin.ignore();

    int index = cariIndexById(id);
    if (index == -1) {
        cout << "Barang dengan ID " << id << " tidak ditemukan.\n";
        return;
    }

    cout << "Data lama:\n";
    cout << "Nama  : " << daftarBarang[index].nama << "\n";
    cout << "Stok  : " << daftarBarang[index].stok << "\n";
    cout << "Harga : " << daftarBarang[index].harga << "\n\n";

    Barang& b = daftarBarang[index];
    string input;

    cout << "Nama baru (kosongkan jika tidak diubah): ";
    getline(cin, input);
    if (!input.empty()) b.nama = input;

    cout << "Stok baru (isi -1 jika tidak diubah)   : ";
    int stokBaru;
    cin >> stokBaru;
    if (stokBaru != -1) b.stok = stokBaru;

    cout << "Harga baru (isi -1 jika tidak diubah)  : ";
    double hargaBaru;
    cin >> hargaBaru;
    if (hargaBaru != -1) b.harga = hargaBaru;

    cout << "Data barang berhasil diubah.\n";
}

void hapusBarang() {
    if (jumlahBarang == 0) {
        cout << "Belum ada data barang.\n";
        return;
    }

    int id;
    cout << "Masukkan ID barang yang akan dihapus: ";
    cin >> id;

    int index = cariIndexById(id);
    if (index == -1) {
        cout << "Barang dengan ID " << id << " tidak ditemukan.\n";
        return;
    }

    // Geser elemen setelahnya ke depan
    for (int i = index; i < jumlahBarang - 1; ++i) {
        daftarBarang[i] = daftarBarang[i + 1];
    }
    jumlahBarang--;

    cout << "Barang berhasil dihapus.\n";
}

// ================== MENU ==================
void tampilkanMenu() {
    cout << "\n=== MENU CRUD BARANG ===\n";
    cout << "1. Tampilkan Semua Barang\n";
    cout << "2. Tambah Barang\n";
    cout << "3. Ubah Barang\n";
    cout << "4. Hapus Barang\n";
    cout << "5. Simpan ke File\n";
    cout << "0. Keluar\n";
    cout << "Pilihan: ";
}

int main() {
    string namaFile = "barang.txt";
    muatDariFile(namaFile);

    int pilihan;
    do {
        tampilkanMenu();
        cin >> pilihan;
        cin.ignore(); // bersihkan newline

        switch (pilihan) {
        case 1:
            tampilkanBarang();
            break;
        case 2:
            tambahBarang();
            break;
        case 3:
            ubahBarang();
            break;
        case 4:
            hapusBarang();
            break;
        case 5:
            simpanKeFile(namaFile);
            break;
        case 0:
            cout << "Keluar program...\n";
            break;
        default:
            cout << "Pilihan tidak valid.\n";
        }
    } while (pilihan != 0);

    // Otomatis simpan saat keluar (opsional)
    simpanKeFile(namaFile);

    return 0;
}