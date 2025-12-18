#include "resto.h"
#include <string>

void clearScreen() {
    system("cls"); // Gunakan "clear" di Linux/Mac
}

// --- BASIC OPERATIONS ---

void createListResto(ListResto &L) {
    L.first = NULL;
    L.last = NULL;
}

bool isEmptyResto(ListResto L) {
    return (L.first == NULL);
}

bool isEmptyMenu(adrResto p) {
    return (p->firstMenu == NULL);
}

adrResto createElementResto(string nama, string alamat, string jamOp) {
    adrResto p = new elemenResto;
    p->info.nama = nama;
    p->info.alamat = alamat;
    p->info.jamOperasional = jamOp;
    p->next = NULL;
    p->prev = NULL;
    p->firstMenu = NULL;
    return p;
}

adrMenu createElementMenu(string nama, int harga, string kategori) {
    adrMenu p = new elemenMenu;
    p->info.namaMenu = nama;
    p->info.harga = harga;
    p->info.kategori = kategori;
    p->next = NULL;
    p->prev = NULL;
    return p;
}

// --- ADD ---

void addResto(ListResto &L, adrResto p) {
    if (searchResto(L, p->info.nama) == NULL) {
        if (isEmptyResto(L)) {
            L.first = p;
            L.last = p;
        } else {
            // Insert Sorted (A-Z)
            if (p->info.nama < L.first->info.nama) {
                p->next = L.first;
                L.first->prev = p;
                L.first = p;
            } else if (p->info.nama > L.last->info.nama) {
                p->prev = L.last;
                L.last->next = p;
                L.last = p;
            } else {
                adrResto q = L.first;
                bool inserted = false;
                while (q != NULL && inserted == false) {
                    if (p->info.nama < q->info.nama) {
                        p->next = q;
                        p->prev = q->prev;
                        q->prev->next = p;
                        q->prev = p;
                        inserted = true;
                    }
                    q = q->next;
                }
            }
        }
    }
}

void addMenu(adrResto p, adrMenu pMenu) {
    if (p->firstMenu == NULL) {
        p->firstMenu = pMenu;
    } else {
        adrMenu q = p->firstMenu;
        while (q->next != NULL) {
            q = q->next;
        }
        q->next = pMenu;
        pMenu->prev = q;
    }
}

// --- SEARCH ---

adrResto searchResto(ListResto L, string nama) {
    adrResto p = L.first;
    while (p != NULL) {
        if (p->info.nama == nama) {
            return p;
        }
        p = p->next;
    }
    return NULL;
}

adrMenu searchMenu(adrResto p, string namaMenu) {
    if (p == NULL) return NULL;

    adrMenu q = p->firstMenu;
    while (q != NULL) {
        if (q->info.namaMenu == namaMenu) {
            return q;
        }
        q = q->next;
    }
    return NULL;
}

void searchSemuaMenu(ListResto L, string namaMenu) {
    adrResto p = L.first;
    bool found = false;

    cout << "\n--- HASIL PENCARIAN GLOBAL: '" << namaMenu << "' ---" << endl;
    while (p != NULL) {
        adrMenu q = searchMenu(p, namaMenu);
        if (q != NULL) {
            cout << "Ditemukan di Restoran: " << p->info.nama
                 << " | Kategori: " << q->info.kategori
                 << " | Harga: Rp " << q->info.harga << endl;
            found = true;
        }
        p = p->next;
    }

    if (!found) {
        cout << "[!] Menu '" << namaMenu << "' tidak ditemukan di restoran manapun." << endl;
    }
    cout << "---------------------------------------------" << endl;
}
// --- UPDATE ---

void updateResto(adrResto p, string namaBaru, string alamatBaru, string jamBaru) {
    if (p != NULL) {
        p->info.nama = namaBaru;
        p->info.alamat = alamatBaru;
        p->info.jamOperasional = jamBaru;
    }
}

void updateMenu(adrMenu p, string namaBaru, int hargaBaru, string kategoriBaru) {
    if (p != NULL) {
        p->info.namaMenu = namaBaru;
        p->info.harga = hargaBaru;
        p->info.kategori = kategoriBaru;
    }
}

// --- DELETE ---

void deleteResto(ListResto &L, string nama) {
    adrResto p = searchResto(L, nama);
    if (p != NULL) {
        p->firstMenu = NULL; // Putus ke anak

        if (p == L.first && p == L.last) {
            L.first = NULL;
            L.last = NULL;
        } else if (p == L.first) {
            L.first = p->next;
            L.first->prev = NULL;
        } else if (p == L.last) {
            L.last = p->prev;
            L.last->next = NULL;
        } else {
            p->prev->next = p->next;
            p->next->prev = p->prev;
        }
    }
}

void deleteMenu(adrResto p, string namaMenu) {
    if (p != NULL && !isEmptyMenu(p)) {
        adrMenu q = p->firstMenu;
        bool found = false;

        while (q != NULL && found == false) {
            if (q->info.namaMenu == namaMenu) {
                found = true;
            } else {
                q = q->next;
            }
        }

        if (found == true) {
            if (q == p->firstMenu) {
                p->firstMenu = q->next;
                if (p->firstMenu != NULL) p->firstMenu->prev = NULL;
            } else {
                q->prev->next = q->next;
                if (q->next != NULL) q->next->prev = q->prev;
            }
        }
    }
}

// --- HELPER & HITUNGAN ---

int countResto(ListResto L) {
    int hasil = 0;
    adrResto q = L.first;
    while(q != NULL) { hasil = hasil + 1; q = q->next; }
    return hasil;
}

int countMenuByCategory(adrResto p, string kategori) {
    int hasil = 0;
    adrMenu q = p->firstMenu;
    while(q != NULL) {
        if(q->info.kategori == kategori) hasil = hasil + 1;
        q = q->next;
    }
    return hasil;
}

int countTotalMenu(adrResto p) {
    int hasil = 0;
    adrMenu q = p->firstMenu;
    while(q != NULL) { hasil = hasil + 1; q = q->next; }
    return hasil;
}

double calculateAvgPrice(adrResto p) {
    double total = 0;
    int count = 0;
    adrMenu q = p->firstMenu;
    while(q != NULL) {
        total = total + q->info.harga;
        count = count + 1;
        q = q->next;
    }
    if (count == 0) return 0;
    return total / count;
}

// --- SORTING ---

void selectionSortResto(adrResto* arrayResto, int n, int mode) {
    int i = 0;
    while (i < n - 1) {
        int indexTerpilih = i;
        int j = i + 1;

        while (j < n) {
            bool harusTukar = false;
            adrResto restoA = arrayResto[j];
            adrResto restoB = arrayResto[indexTerpilih];

            if (mode == 1) {
                if (restoA->info.nama < restoB->info.nama) harusTukar = true;
            } else if (mode == 2) {
                if (countTotalMenu(restoA) > countTotalMenu(restoB)) harusTukar = true;
            } else if (mode == 3) {
                if (countMenuByCategory(restoA, "Appetizer") > countMenuByCategory(restoB, "Appetizer")) harusTukar = true;
            } else if (mode == 4) {
                if (countMenuByCategory(restoA, "Main_Course") > countMenuByCategory(restoB, "Main_Course")) harusTukar = true;
            } else if (mode == 5) {
                if (countMenuByCategory(restoA, "Dessert") > countMenuByCategory(restoB, "Dessert")) harusTukar = true;
            } else if (mode == 6) {
                if (countMenuByCategory(restoA, "Drinks") > countMenuByCategory(restoB, "Drinks")) harusTukar = true;
            } else if (mode == 7) {
                double hargaA = calculateAvgPrice(restoA);
                double hargaB = calculateAvgPrice(restoB);
                if (hargaA == 0) hargaA = 99999999;
                if (hargaB == 0) hargaB = 99999999;
                if (hargaA < hargaB) harusTukar = true;
            }

            if (harusTukar == true) {
                indexTerpilih = j;
            }
            j = j + 1;
        }

        adrResto temp = arrayResto[i];
        arrayResto[i] = arrayResto[indexTerpilih];
        arrayResto[indexTerpilih] = temp;

        i = i + 1;
    }
}

// --- DISPLAY ---

void displayTable(ListResto L, int mode) {
    if (isEmptyResto(L)) {
        cout << "\nDAFTAR RESTORAN (KOSONG)" << endl;
        cout << "================================================================================================" << endl;
        cout << "| NAMA RESTORAN       | ALAMAT          | JAM OPERASIONAL | JUMLAH MENU | RATA-RATA HARGA    |" << endl;
        cout << "================================================================================================" << endl;
        cout << "| -                   | -               | -               | -           | -                  |" << endl;
        cout << "================================================================================================" << endl;
    } else {
        int n = countResto(L);
        adrResto *arrayResto = new adrResto[n];
        adrResto q = L.first;
        int idx = 0;
        while(q != NULL) {
            arrayResto[idx] = q;
            q = q->next;
            idx = idx + 1;
        }

        selectionSortResto(arrayResto, n, mode);

        cout << "\nDAFTAR RESTORAN (Mode: " << mode << ")" << endl;
        cout << "================================================================================================" << endl;
        cout << "| NAMA RESTORAN       | ALAMAT          | JAM OPERASIONAL | JUMLAH MENU | RATA-RATA HARGA    |" << endl;
        cout << "================================================================================================" << endl;

        int k = 0;
        while (k < n) {
            adrResto currentResto = arrayResto[k];

            cout << "| " << currentResto->info.nama;
            int paddingSpace = 0;
            while(paddingSpace < 20 - currentResto->info.nama.length()) { cout << " "; paddingSpace++; }

            cout << "| " << currentResto->info.alamat;
            paddingSpace = 0;
            while(paddingSpace < 16 - currentResto->info.alamat.length()) { cout << " "; paddingSpace++; }

            cout << "| " << currentResto->info.jamOperasional;
            paddingSpace = 0;
            while(paddingSpace < 16 - currentResto->info.jamOperasional.length()) { cout << " "; paddingSpace++; }

            cout << "| " << countTotalMenu(currentResto);
            if(countTotalMenu(currentResto) < 10) cout << "           "; else cout << "          ";

            double averagePrice = calculateAvgPrice(currentResto);
            cout << "| Rp " << (int)averagePrice;
            string stringAveragePrice = to_string((int)averagePrice);
            paddingSpace = 0;
            while(paddingSpace < 16 - stringAveragePrice.length()) { cout << " "; paddingSpace++; }

            cout << "|" << endl;
            k = k + 1;
        }
        cout << "================================================================================================" << endl;
    }
}

void showRestoDetails(adrResto p) {
    if (p != NULL) {
        cout << "\n========================================" << endl;
        cout << " DETAIL RESTORAN" << endl;
        cout << "========================================" << endl;
        cout << "Nama    : " << p->info.nama << endl;
        cout << "Alamat  : " << p->info.alamat << endl;
        cout << "Jam Ops : " << p->info.jamOperasional << endl;
        cout << "----------------------------------------" << endl;
        cout << "DAFTAR MENU:" << endl;

        adrMenu q = p->firstMenu;
        if (q == NULL) {
            cout << "(Tidak ada menu)" << endl;
        }
        while (q != NULL) {
            cout << "- " << q->info.namaMenu
                 << " [" << q->info.kategori << "] : Rp " << q->info.harga << endl;
            q = q->next;
        }
        cout << "========================================" << endl;
    }
}
