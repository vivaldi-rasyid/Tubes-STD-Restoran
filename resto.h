#ifndef RESTO_H_INCLUDED
#define RESTO_H_INCLUDED
#include <iostream>
using namespace std;

// Struktur Data
typedef struct elemenResto *adrResto;
typedef struct elemenMenu *adrMenu;

struct Restoran {
    string nama;
    string alamat;
    string jamOperasional;
};

struct Menu {
    string namaMenu;
    int harga;
    string kategori; // Appetizer, Main Course, Dessert, Drinks
};

struct elemenResto {
    Restoran info;
    adrResto next;
    adrResto prev;
    adrMenu firstMenu;
};

struct elemenMenu {
    Menu info;
    adrMenu next;
    adrMenu prev;
};

struct ListResto {
    adrResto first;
    adrResto last;
};

// CreateList & isEmpty
void createListResto(ListResto &L);
bool isEmptyResto(ListResto L);
bool isEmptyMenu(adrResto p);

// Create & Add
adrResto createElementResto(string nama, string alamat, string jamOp);
adrMenu createElementMenu(string nama, int harga, string kategori);
void addResto(ListResto &L, adrResto p);
void addMenu(adrResto p, adrMenu q);

// Search & Display
adrResto searchResto(ListResto L, string nama);
void displayList(ListResto L);

// Delete
void deleteResto(ListResto &L, string nama);
void deleteMenu(adrResto p, string namaMenu);

// Sorting
void sortRestoByNama(ListResto &L);          // Alfabet A-Z
void sortRestoByTotalMenu(ListResto &L);     // Menu Terbanyak
void sortRestoByAppetizer(ListResto &L);     // Appetizer Terbanyak
void sortRestoByMainCourse(ListResto &L);    // Main Course Terbanyak
void sortRestoByDessert(ListResto &L);       // Dessert Terbanyak
void sortRestoByDrinks(ListResto &L);        // Drinks Terbanyak
void sortRestoByAvgPrice(ListResto &L);      // Harga Termurah

// Fungsi Lainnya
int countMenuByCategory(adrResto p, string kategori);
int countTotalMenu(adrResto p);
double calculateAvgPrice(adrResto p);

#endif // RESTO_H_INCLUDED
