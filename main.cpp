#include <iostream>
#include "resto.h"

using namespace std;

int main() {
    ListResto L;
    createListResto(L);

    string pilihanMenu;
    string namaResto, alamatResto, jamResto;
    string namaMenu, kategoriMenu, targetResto;
    int hargaMenu;
    int modeUrutan = 1;
    adrResto p;

    bool berjalan = true;

    while (berjalan == true) {
        clearScreen();

        displayTable(L, modeUrutan);

        cout << "\nMENU UTAMA:" << endl;
        cout << "[1] Tambah Restoran" << endl;
        cout << "[2] Tambah Menu" << endl;
        cout << "[3] Lihat Detail Restoran & Menu" << endl;
        cout << "[4] Update Data Restoran" << endl;
        cout << "[5] Update Data Menu" << endl;
        cout << "[6] Hapus Restoran" << endl;
        cout << "[7] Hapus Menu" << endl;
        cout << "[8] Ubah Urutan Tabel" << endl;
        cout << "[9] Cari Menu (Global)" << endl;
        cout << "[0] Keluar" << endl;
        cout << "Pilihan: ";
        cin >> pilihanMenu;

        if (pilihanMenu == "1") {
            cout << "\n--- TAMBAH RESTORAN ---" << endl;
            cout << "Ketik 'x' untuk batal." << endl;

            // VALIDASI
            bool valid = false;
            do {
                cout << "Nama Resto: "; cin >> namaResto;
                if (namaResto == "x") {
                    valid = true; // Batal
                } else {
                    if (searchResto(L, namaResto) != NULL) {
                        cout << "[!] Error: Nama sudah dipakai! Silakan input nama lain." << endl;
                    } else {
                        valid = true;
                        cout << "Alamat: "; cin >> alamatResto;
                        cout << "Jam Operasional (xx:xx-xx:xx): "; cin >> jamResto;
                        addResto(L, createElementResto(namaResto, alamatResto, jamResto));
                    }
                }
            } while (valid == false);

        } else if (pilihanMenu == "2") {
            cout << "\n--- TAMBAH MENU ---" << endl;
            cout << "Ketik 'x' untuk batal." << endl;

            bool valid = false;
            do {
                cout << "Nama Restoran Tujuan: "; cin >> targetResto;
                if (targetResto == "x") {
                    valid = true;
                } else {
                    p = searchResto(L, targetResto);
                    if (p == NULL) {
                        cout << "[!] Error: Restoran tidak ditemukan! Input ulang." << endl;
                    } else {
                        valid = true;
                        cout << "Nama Menu: "; cin >> namaMenu;
                        cout << "Kategori (Appetizer/Main_Course/Dessert/Drinks): "; cin >> kategoriMenu;
                        cout << "Harga: "; cin >> hargaMenu;
                        addMenu(p, createElementMenu(namaMenu, hargaMenu, kategoriMenu));
                    }
                }
            } while (valid == false);

        } else if (pilihanMenu == "3") {
            cout << "\n--- LIHAT DETAIL RESTORAN ---" << endl;
            cout << "Ketik 'x' untuk batal." << endl;

            bool valid = false;
            do {
                cout << "Nama Restoran: "; cin >> targetResto;
                if (targetResto == "x") {
                    valid = true;
                } else {
                    p = searchResto(L, targetResto);
                    if (p == NULL) {
                        cout << "[!] Error: Restoran tidak ditemukan! Input ulang." << endl;
                    } else {
                        valid = true;
                        showRestoDetails(p);
                        cout << "(Ketik x lalu enter untuk kembali) ";
                        string dummy; cin >> dummy;
                    }
                }
            } while (valid == false);

        } else if (pilihanMenu == "4") {
            cout << "\n--- UPDATE RESTORAN ---" << endl;
            cout << "Ketik 'x' untuk batal." << endl;

            bool valid = false;
            do {
                cout << "Nama Restoran Lama: "; cin >> targetResto;
                if (targetResto == "x") {
                    valid = true;
                } else {
                    p = searchResto(L, targetResto);
                    if (p == NULL) {
                        cout << "[!] Error: Restoran tidak ditemukan! Input ulang." << endl;
                    } else {
                        valid = true;
                        string nBaru, aBaru, jBaru;
                        cout << "Nama Baru: "; cin >> nBaru;
                        cout << "Alamat Baru: "; cin >> aBaru;
                        cout << "Jam Operasional Baru (xx:xx-xx:xx): "; cin >> jBaru;
                        if (nBaru != targetResto && searchResto(L, nBaru) != NULL) {
                             cout << "[!] Gagal: Nama baru sudah dipakai resto lain." << endl;
                        } else {
                             updateResto(p, nBaru, aBaru, jBaru);
                        }
                    }
                }
            } while (valid == false);

        } else if (pilihanMenu == "5") {
            cout << "\n--- UPDATE MENU ---" << endl;
            cout << "Ketik 'x' untuk batal." << endl;

            bool valid = false;
            do {
                cout << "Nama Restoran: "; cin >> targetResto;
                if (targetResto == "x") {
                    valid = true;
                } else {
                    p = searchResto(L, targetResto);
                    if (p == NULL) {
                        cout << "[!] Error: Restoran tidak ditemukan! Input ulang." << endl;
                    } else {
                        valid = true;
                        string nmLama;
                        cout << "Nama Menu Lama: "; cin >> nmLama;

                        // Cari pointer menu
                        adrMenu q = p->firstMenu;
                        adrMenu foundMenu = NULL;
                        while(q != NULL) {
                            if(q->info.namaMenu == nmLama) foundMenu = q;
                            q = q->next;
                        }

                        if (foundMenu != NULL) {
                            string nmBaru, kBaru;
                            int hBaru;
                            cout << "Nama Menu Baru: "; cin >> nmBaru;
                            cout << "Kategori Baru (Appetizer/Main_Course/Dessert/Drinks): "; cin >> kBaru;
                            cout << "Harga Baru: "; cin >> hBaru;
                            updateMenu(foundMenu, nmBaru, hBaru, kBaru);
                        } else {
                            cout << "[!] Menu tidak ditemukan." << endl;
                        }
                    }
                }
            } while (valid == false);

        } else if (pilihanMenu == "6") {
            cout << "\n--- HAPUS RESTORAN ---" << endl;
            cout << "Ketik 'x' untuk batal." << endl;
            bool valid = false;
            do {
                cout << "Nama Restoran: "; cin >> targetResto;
                if (targetResto == "x") {
                    valid = true;
                } else {
                    if (searchResto(L, targetResto) == NULL) {
                        cout << "[!] Error: Restoran tidak ditemukan! Input ulang." << endl;
                    } else {
                        deleteResto(L, targetResto);
                        valid = true;
                    }
                }
            } while (valid == false);

        } else if (pilihanMenu == "7") {
            cout << "\n--- HAPUS MENU ---" << endl;
            cout << "Ketik 'x' untuk batal." << endl;
            bool valid = false;
            do {
                cout << "Nama Restoran: "; cin >> targetResto;
                if (targetResto == "x") {
                    valid = true;
                } else {
                    p = searchResto(L, targetResto);
                    if (p == NULL) {
                         cout << "[!] Error: Restoran tidak ditemukan! Input ulang." << endl;
                    } else {
                        valid = true;
                        cout << "Nama Menu dihapus: "; cin >> namaMenu;
                        deleteMenu(p, namaMenu);
                    }
                }
            } while (valid == false);

        } else if (pilihanMenu == "8") {
            cout << "\n--- PILIH URUTAN TABEL ---" << endl;
            cout << "1. Alfabet" << endl;
            cout << "2. Menu Terbanyak" << endl;
            cout << "3. Appetizer Terbanyak" << endl;
            cout << "4. Main_Course Terbanyak" << endl;
            cout << "5. Dessert Terbanyak" << endl;
            cout << "6. Drinks Terbanyak" << endl;
            cout << "7. Harga Termurah" << endl;
            cout << "Pilih: ";
            int tempMode;
            cin >> tempMode;
            if (tempMode >= 1 && tempMode <= 7) {
                modeUrutan = tempMode;
            }

        }else if (pilihanMenu == "9") {
            cout << "\n--- CARI MENU ---" << endl;
            cout << "Masukkan nama menu yang dicari: ";
            string cariMenu;
            cin >> cariMenu;

            searchSemuaMenu(L, cariMenu);

            cout << "(Tekan enter untuk kembali)";
            string dummy; cin.ignore(); getline(cin, dummy);

        } else if (pilihanMenu == "0") {
            berjalan = false;
        }
    }

    return 0;
}
