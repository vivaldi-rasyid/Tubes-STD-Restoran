#include <iostream>
#include "resto.h"
using namespace std;

void createListResto(ListResto &L) {
    L.first = NULL;
    L.last = NULL;
}

bool isEmptyResto(ListResto L) {
    return (L.first == NULL && L.last == NULL);
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
    adrMenu q = new elemenMenu;
    q->info.namaMenu = nama;
    q->info.harga = harga;
    q->info.kategori = kategori;
    q->next = NULL;
    q->prev = NULL;
    return q;
}

void addResto(ListResto &L, adrResto p) {
    if (isEmptyResto(L)) {
        L.first = p;
        L.last = p;
    } else {
        p->prev = L.last;
        L.last->next = p;
        L.last = p;
    }
}

void addMenu(adrResto p, adrMenu q) {
    if (p->firstMenu == NULL) {
        p->firstMenu = q;
    } else {
        adrMenu temp = p->firstMenu;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = q;
        q->prev = temp;
    }
}

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

void deleteResto(ListResto &L, string nama) {
    adrResto p = searchResto(L, nama);

    if (p != NULL) {
        // 1. Hapus Anak
        adrMenu q = p->firstMenu;
        while (q != NULL) {
            adrMenu temp = q;
            q = q->next;
            delete temp;
        }
        p->firstMenu = NULL;

        // 2. Hapus Parent
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
        delete p;
        cout << "[V] Restoran berhasil dihapus." << endl;
    } else {
        cout << "[X] Restoran tidak ditemukan." << endl;
    }
}

void deleteMenu(adrResto p, string namaMenu) {
    if (p != NULL && !isEmptyMenu(p)) {
        adrMenu q = p->firstMenu;
        bool found = false;

        while (q != NULL && !found) {
            if (q->info.namaMenu == namaMenu) {
                found = true;
            } else {
                q = q->next;
            }
        }

        if (found) {
            if (q == p->firstMenu) {
                p->firstMenu = q->next;
                if (p->firstMenu != NULL) {
                    p->firstMenu->prev = NULL;
                }
            } else {
                q->prev->next = q->next;
                if (q->next != NULL) {
                    q->next->prev = q->prev;
                }
            }
            delete q;
            cout << "[V] Menu berhasil dihapus." << endl;
        } else {
            cout << "[X] Menu tidak ditemukan." << endl;
        }
    } else {
        cout << "[!] Data kosong." << endl;
    }
}

void displayList(ListResto L) {
    if (isEmptyResto(L)) {
        cout << "--- Data Kosong ---" << endl;
    } else {
        adrResto p = L.first;
        while (p != NULL) {
            cout << "RESTO: " << p->info.nama
                 << " | Avg Price: " << calculateAvgPrice(p)
                 << " | Total Menu: " << countTotalMenu(p) << endl;

            adrMenu q = p->firstMenu;
            if (q == NULL) {
                cout << "   (Menu Kosong)" << endl;
            } else {
                while (q != NULL) {
                    cout << "   - " << q->info.namaMenu
                         << " [" << q->info.kategori << "] Rp" << q->info.harga << endl;
                    q = q->next;
                }
            }
            cout << "-----------------------------------" << endl;
            p = p->next;
        }
    }
}

int countMenuByCategory(adrResto p, string kategori) {
    int count = 0;
    adrMenu q = p->firstMenu;
    while (q != NULL) {
        if (q->info.kategori == kategori) count++;
        q = q->next;
    }
    return count;
}

int countTotalMenu(adrResto p) {
    int count = 0;
    adrMenu q = p->firstMenu;
    while (q != NULL) {
        count++;
        q = q->next;
    }
    return count;
}

double calculateAvgPrice(adrResto p) {
    double total = 0;
    int count = 0;
    adrMenu q = p->firstMenu;
    while (q != NULL) {
        total += q->info.harga;
        count++;
        q = q->next;
    }
    if (count == 0) return 99999999;
    return total / count;
}

void sortRestoByNama(ListResto &L) {
    if (!isEmptyResto(L) && L.first->next != NULL) {
        bool swapped = true;
        adrResto ptr1;
        adrResto lptr = NULL;

        while (swapped) {
            swapped = false;
            ptr1 = L.first;
            while (ptr1->next != lptr) {
                if (ptr1->info.nama > ptr1->next->info.nama) {
                    // Swap Info
                    Restoran tempInfo = ptr1->info;
                    ptr1->info = ptr1->next->info;
                    ptr1->next->info = tempInfo;
                    // Swap Child
                    adrMenu tempMenu = ptr1->firstMenu;
                    ptr1->firstMenu = ptr1->next->firstMenu;
                    ptr1->next->firstMenu = tempMenu;

                    swapped = true;
                }
                ptr1 = ptr1->next;
            }
            lptr = ptr1;
        }
    }
}

void sortRestoByTotalMenu(ListResto &L) {
    if (!isEmptyResto(L) && L.first->next != NULL) {
        bool swapped = true;
        adrResto ptr1;
        adrResto lptr = NULL;

        while (swapped) {
            swapped = false;
            ptr1 = L.first;
            while (ptr1->next != lptr) {
                if (countTotalMenu(ptr1) < countTotalMenu(ptr1->next)) {
                    Restoran tempInfo = ptr1->info;
                    ptr1->info = ptr1->next->info;
                    ptr1->next->info = tempInfo;
                    adrMenu tempMenu = ptr1->firstMenu;
                    ptr1->firstMenu = ptr1->next->firstMenu;
                    ptr1->next->firstMenu = tempMenu;
                    swapped = true;
                }
                ptr1 = ptr1->next;
            }
            lptr = ptr1;
        }
    }
}

void sortRestoByAppetizer(ListResto &L) {
    if (!isEmptyResto(L) && L.first->next != NULL) {
        bool swapped = true;
        adrResto ptr1;
        adrResto lptr = NULL;
        while (swapped) {
            swapped = false;
            ptr1 = L.first;
            while (ptr1->next != lptr) {
                if (countMenuByCategory(ptr1, "Appetizer") < countMenuByCategory(ptr1->next, "Appetizer")) {
                    Restoran tempInfo = ptr1->info;
                    ptr1->info = ptr1->next->info;
                    ptr1->next->info = tempInfo;
                    adrMenu tempMenu = ptr1->firstMenu;
                    ptr1->firstMenu = ptr1->next->firstMenu;
                    ptr1->next->firstMenu = tempMenu;
                    swapped = true;
                }
                ptr1 = ptr1->next;
            }
            lptr = ptr1;
        }
    }
}

void sortRestoByMainCourse(ListResto &L) {
    if (!isEmptyResto(L) && L.first->next != NULL) {
        bool swapped = true;
        adrResto ptr1;
        adrResto lptr = NULL;
        while (swapped) {
            swapped = false;
            ptr1 = L.first;
            while (ptr1->next != lptr) {
                if (countMenuByCategory(ptr1, "Main Course") < countMenuByCategory(ptr1->next, "Main Course")) {
                    Restoran tempInfo = ptr1->info;
                    ptr1->info = ptr1->next->info;
                    ptr1->next->info = tempInfo;
                    adrMenu tempMenu = ptr1->firstMenu;
                    ptr1->firstMenu = ptr1->next->firstMenu;
                    ptr1->next->firstMenu = tempMenu;
                    swapped = true;
                }
                ptr1 = ptr1->next;
            }
            lptr = ptr1;
        }
    }
}

void sortRestoByDessert(ListResto &L) {
    if (!isEmptyResto(L) && L.first->next != NULL) {
        bool swapped = true;
        adrResto ptr1;
        adrResto lptr = NULL;
        while (swapped) {
            swapped = false;
            ptr1 = L.first;
            while (ptr1->next != lptr) {
                if (countMenuByCategory(ptr1, "Dessert") < countMenuByCategory(ptr1->next, "Dessert")) {
                    Restoran tempInfo = ptr1->info;
                    ptr1->info = ptr1->next->info;
                    ptr1->next->info = tempInfo;
                    adrMenu tempMenu = ptr1->firstMenu;
                    ptr1->firstMenu = ptr1->next->firstMenu;
                    ptr1->next->firstMenu = tempMenu;
                    swapped = true;
                }
                ptr1 = ptr1->next;
            }
            lptr = ptr1;
        }
    }
}

void sortRestoByDrinks(ListResto &L) {
    if (!isEmptyResto(L) && L.first->next != NULL) {
        bool swapped = true;
        adrResto ptr1;
        adrResto lptr = NULL;
        while (swapped) {
            swapped = false;
            ptr1 = L.first;
            while (ptr1->next != lptr) {
                if (countMenuByCategory(ptr1, "Drinks") < countMenuByCategory(ptr1->next, "Drinks")) {
                    Restoran tempInfo = ptr1->info;
                    ptr1->info = ptr1->next->info;
                    ptr1->next->info = tempInfo;
                    adrMenu tempMenu = ptr1->firstMenu;
                    ptr1->firstMenu = ptr1->next->firstMenu;
                    ptr1->next->firstMenu = tempMenu;
                    swapped = true;
                }
                ptr1 = ptr1->next;
            }
            lptr = ptr1;
        }
    }
}

void sortRestoByAvgPrice(ListResto &L) {
    if (!isEmptyResto(L) && L.first->next != NULL) {
        bool swapped = true;
        adrResto ptr1;
        adrResto lptr = NULL;
        while (swapped) {
            swapped = false;
            ptr1 = L.first;
            while (ptr1->next != lptr) {
                if (calculateAvgPrice(ptr1) > calculateAvgPrice(ptr1->next)) {
                    Restoran tempInfo = ptr1->info;
                    ptr1->info = ptr1->next->info;
                    ptr1->next->info = tempInfo;
                    adrMenu tempMenu = ptr1->firstMenu;
                    ptr1->firstMenu = ptr1->next->firstMenu;
                    ptr1->next->firstMenu = tempMenu;
                    swapped = true;
                }
                ptr1 = ptr1->next;
            }
            lptr = ptr1;
        }
    }
}
