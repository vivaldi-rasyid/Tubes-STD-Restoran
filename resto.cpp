#include <iostream>
#include "resto.h"
using namespace std;

void createList(List &L){
    L.first = nullptr;
}
adrResto createResto(int id, string name, string alamat, string kategoriResto){
    adrResto p = new Resto;
    p->idResto = id;
    p->namaResto = nama;
    p->alamat = alamat;
    p->kategoriResto = kategoriResto;
    p->nextParent = nullptr;
    p->firstChild = nullptr;
    return p;
}
adrMenu createMenu(string nama, int harga, string kategoriMenu){
    adrMenu p = new Menu;
    p->namaMenu = nama;
    p->harga = harga;
    p->kategoriMenu = kategoriMenu;
    p->nextChild = nullptr;
    return p;
}
void insertResto(List &L, adrResto p){
    adrResto q;
    if (L.first == nullptr){
        L.first = p;
    }else{
        q = L.first;
        while (q->nextParent != nullptr){
            q = q->nextParent
        }
        q->nextParent = p;
    }
}
void deleteResto(List &L, int id){
    adrResto p = L.first;
    adrResto prev = nullptr;
    if (L.first == null){
        cout << "Menu kosong" << endl;
    }

    while (p != nullptr && p->idResto != id){
        prev = p;
        p = p->nextParent;
    }

    if (p == nullptr){
        cout << "Restoran dengan ID " << id << " tidak ditemukan" << endl;
    }

    // di buatin biar dia ngehapus childnya dulu dong disini, soalnya kalo langsung hapus parent pasti error //

    if (p == L.first){
        L.first = p->nextParent;
    }else{
        prev->nextParent = p->nextParent;
    }
    delete p;
    cout << "Restoran dengan ID " << id << " berhasil dihapus" << endl;
}
adrResto searchResto(List L, int id){
    adrResto p = L.first;
    while (p != nullptr){
        if (p->idResto){
            return p;
        }
        p = p->nextParent;
    }
    return nullptr;
}
