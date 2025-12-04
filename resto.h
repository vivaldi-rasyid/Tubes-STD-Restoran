#ifndef RESTO_H_INCLUDED
#define RESTO_H_INCLUDED
#include <iostream>
using namespace std;

typedef struct Menu* adrMenu;
typedef struct Resto* adrResto;

struct Menu{
    string namaMenu;
    int harga;
    string kategoriMenu;
    adrMenu nextChild;
};

struct Resto{
    int idResto;
    string namaResto;
    string alamat;
    string kategoriResto;
    adrMenu firstChild;
    adrResto nextParent;
};

struct List{
    adrResto first;
};

void createList(List &L);
adrResto createResto(int id, string name, string alamat, string kategoriResto);
adrMenu createMenu(string nama, int harga, string kategoriMenu);
void insertResto(List &L, adrResto p);
void deleteResto(List &L, int id);
adrResto searchResto(List L, int id);



#endif // RESTO_H_INCLUDED
