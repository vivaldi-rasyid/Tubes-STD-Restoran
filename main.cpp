#include <iostream>
#include "resto.h"
using namespace std;

int main() {
    ListResto L;
    createListResto(L);

    int pilihan;
    string nResto, aResto, jOp;
    string nMenu, kMenu, tResto;
    int hMenu;
    adrResto p;

    pilihan = -1;

    while (pilihan != 0) {
        cout << endl;
        cout << "========== APLIKASI RESTO MLL ==========" << endl;
        cout << "[1] Tambah Restoran" << endl;
        cout << "[2] Tambah Menu" << endl;
        cout << "[3] Hapus Restoran" << endl;
        cout << "[4] Hapus Menu" << endl;
        cout << "[5] Search Restoran" << endl;
        cout << "--- DISPLAY & SORTING ---" << endl;
        cout << "[6] Display (Urutan Saat Ini)" << endl;
        cout << "[7] Sort & Display (Alfabet Nama)" << endl;
        cout << "[8] Sort & Display (Jumlah Menu Terbanyak)" << endl;
        cout << "[9] Sort & Display (Appetizer Terbanyak)" << endl;
        cout << "[10] Sort & Display (Main Course Terbanyak)" << endl;
        cout << "[11] Sort & Display (Dessert Terbanyak)" << endl;
        cout << "[12] Sort & Display (Drinks Terbanyak)" << endl;
        cout << "[13] Sort & Display (Rata-rata Termurah)" << endl;
        cout << "[0] Keluar" << endl;
        cout << "Pilihan: ";
        cin >> pilihan;

        switch(pilihan) {
        case 1:
            cout << "Nama_Resto (Tanpa Spasi): "; cin >> nResto;
            cout << "Alamat (Tanpa Spasi): "; cin >> aResto;
            cout << "Jam_Ops (Tanpa Spasi): "; cin >> jOp;
            addResto(L, createElementResto(nResto, aResto, jOp));
            break;
        case 2:
            cout << "Resto_Tujuan: "; cin >> tResto;
            p = searchResto(L, tResto);
            if(p != NULL){
                cout << "Nama_Menu: "; cin >> nMenu;
                cout << "Kategori: "; cin >> kMenu;
                cout << "Harga: "; cin >> hMenu;
                addMenu(p, createElementMenu(nMenu, hMenu, kMenu));
            } else {
                cout << "Resto tidak ditemukan." << endl;
            }
            break;
        case 3:
            cout << "Hapus_Resto: "; cin >> tResto;
            deleteResto(L, tResto);
            break;
        case 4:
            cout << "Di_Resto_Mana: "; cin >> tResto;
            p = searchResto(L, tResto);
            if(p != NULL){
                cout << "Hapus_Menu: "; cin >> nMenu;
                deleteMenu(p, nMenu);
            } else {
                cout << "Resto tidak ditemukan." << endl;
            }
            break;
        case 5:
            cout << "Cari_Resto: "; cin >> tResto;
            p = searchResto(L, tResto);
            if(p != NULL) {
                cout << "Ditemukan: " << p->info.nama << " | " << p->info.alamat << endl;
            } else {
                cout << "Tidak ditemukan." << endl;
            }
            break;
        case 6:
            displayList(L);
            break;
        case 7:
            sortRestoByNama(L);
            displayList(L);
            break;
        case 8:
            sortRestoByTotalMenu(L);
            displayList(L);
            break;
        case 9:
            sortRestoByAppetizer(L);
            displayList(L);
            break;
        case 10:
            sortRestoByMainCourse(L);
            displayList(L);
            break;
        case 11:
            sortRestoByDessert(L);
            displayList(L);
            break;
        case 12:
            sortRestoByDrinks(L);
            displayList(L);
            break;
        case 13:
            sortRestoByAvgPrice(L);
            displayList(L);
            break;
        case 0:
            cout << "Terima kasih!" << endl;
            break;
        default:
            cout << "Pilihan salah." << endl;
            break;
        }
    }

    return 0;
}
