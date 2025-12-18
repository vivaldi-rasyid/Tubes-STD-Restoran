#ifndef RESTO_H_INCLUDED
#define RESTO_H_INCLUDED

#include <iostream>
#include <cstdlib> // Untuk system("cls")
using namespace std;

// --- STRUKTUR DATA ---

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
    string kategori;
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

// --- FUNGSI & PROSEDUR ---

// Basic
void createListResto(ListResto &L);
bool isEmptyResto(ListResto L);
bool isEmptyMenu(adrResto p);
adrResto createElementResto(string nama, string alamat, string jamOp);
adrMenu createElementMenu(string nama, int harga, string kategori);

// Add
void addResto(ListResto &L, adrResto p);
void addMenu(adrResto p, adrMenu pMenu);

// Search
adrResto searchResto(ListResto L, string nama);
adrMenu searchMenu(adrResto p, string namaMenu);
bool searchSemuaMenu(ListResto L, string namaMenu);

// Update
void updateResto(adrResto p, string namaBaru, string alamatBaru, string jamBaru);
void updateMenu(adrMenu p, string namaBaru, int hargaBaru, string kategoriBaru);

// Delete
void deleteResto(ListResto &L, string nama);
void deleteMenu(adrResto p, string namaMenu);

// Helper Hitungan
int countResto(ListResto L);
int countMenuByCategory(adrResto p, string kategori);
int countTotalMenu(adrResto p);
double calculateAvgPrice(adrResto p);

// Sorting
void selectionSortResto(adrResto* arrayResto, int n, int mode);

// Display
void displayTable(ListResto L, int mode);
void showRestoDetails(adrResto p);
void clearScreen();

#endif // RESTO_H_INCLUDED
