# 🍽️ Restaurant Management System (C++)

Aplikasi manajemen data restoran berbasis _console_ (CLI) yang dibangun menggunakan bahasa C++. Proyek ini mengimplementasikan struktur data **Relational Doubly Linked List** (Parent-Child) untuk mengelola hubungan antara Restoran dan Menu.

**📋 Fitur Utama**

Aplikasi ini memiliki fitur **CRUD** (Create, Read, Update, Delete) lengkap beserta fitur pengurutan dan pencarian data:

**1\. Manajemen Restoran (Parent)**

- **Insert:** Menambahkan restoran baru (otomatis terurut secara alfabetis/sorted insert).
- **Update:** Mengubah nama, alamat, dan jam operasional restoran.
- **Delete:** Menghapus restoran (termasuk menghapus seluruh menu di dalamnya secara otomatis/cascade delete).
- **View:** Menampilkan daftar restoran dalam bentuk tabel yang rapi.

**2\. Manajemen Menu (Child)**

- **Insert:** Menambahkan menu ke restoran tertentu.
- **Update:** Mengubah nama, kategori, dan harga menu.
- **Delete:** Menghapus menu spesifik dari sebuah restoran.
- **Search:** Mencari menu di seluruh restoran yang ada.

**3\. Fitur Lanjutan (Sorting & Statistics)**

Aplikasi mendukung pengurutan tabel restoran berdasarkan berbagai kriteria menggunakan algoritma **Selection Sort**:

- 🔤 Nama Restoran (A-Z)
- 🔢 Jumlah Menu Terbanyak
- 🥗 Jumlah _Appetizer_ Terbanyak
- 🥩 Jumlah _Main Course_ Terbanyak
- 🍰 Jumlah _Dessert_ Terbanyak
- 🥤 Jumlah _Drinks_ Terbanyak
- 💲 Rata-rata Harga Termurah

**🛠️ Struktur Data**

Proyek ini menggunakan **Multi-Linked List** (List of Lists):

- **List Parent (Restoran):** Menggunakan _Doubly Linked List_. Setiap _node_ restoran memiliki pointer ke _node_ menu pertamanya (firstMenu).
- **List Child (Menu):** Menggunakan _Doubly Linked List_. Setiap _node_ menu terhubung satu sama lain dalam lingkup satu restoran.

**🚀 Cara Menjalankan**

**Opsi 1: Menggunakan Terminal (CLI)**

**Prasyarat:** Compiler C++ (GCC/G++ atau MinGW).

- Buka terminal/CMD di folder proyek.
- Kompilasi program:
- g++ main.cpp resto.cpp -o resto_app
- Jalankan program:
  - **Windows:** resto_app.exe
  - **Linux/Mac:** ./resto_app

**Opsi 2: Menggunakan Code::Blocks IDE (Rekomendasi)**

Jika Anda menggunakan IDE Code::Blocks, ikuti langkah berikut untuk menghindari error _undefined reference_:

- **Buat Project Baru:**
  - Buka Code::Blocks.
  - Klik File > New > Project...
  - Pilih Console application -> Go.
  - Pilih C++ -> Next.
  - Beri nama project (misal: RestoApp) dan tentukan folder penyimpanan -> Next -> Finish.
- **Masukkan File Codingan:**
  - Copy file main.cpp, resto.cpp, dan resto.h ke dalam folder project yang baru dibuat (folder tempat file .cbp berada).
  - Kembali ke Code::Blocks. Di panel kiri (Management), klik kanan nama project -> Add files...
  - Pilih ketiga file tersebut (main.cpp, resto.cpp, resto.h) -> Klik Open -> OK.
- **Build & Run:**
  - Pastikan tidak ada file main.cpp ganda (hapus main.cpp default bawaan Code::Blocks jika ada).
  - Tekan tombol **F9** (Build and Run).

**📚 Data Dummy (Copy & Paste)**

Berikut adalah [data](https://drive.google.com/file/d/1VLxjDS0PvMVaBzzoPmSfkWoIalnPgh97/view?usp=sharing) sampel yang dapat digunakan untuk menguji aplikasi.
