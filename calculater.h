#ifndef calculater_H
#define calculater_H

#include "boolean.h"

#define OperUndef '?'
#define NilaiUndef -999
#define MAXEL 100
typedef float infotype;
typedef struct
{
    char oper; /* Tempat menyimpan operator */
    infotype nilai; /* Tempat menyimpan nilai real operan */
    int prio; /* Prioritas operator */
} elmt; /* Type elemen tabel */
typedef struct
{
    elmt matArr[MAXEL+1]; /* Array */
    int Neff; /* Banyaknya elemen efektif array */
} Tabel; /* Type array */

typedef char string[MAXEL+1];

#define NEff(T) (T).Neff
#define Oper(T, i) (T).matArr[i].oper
#define Prio(T, i) (T).matArr[i].prio
#define Nilai(T, i) (T).matArr[i].nilai

/*
Menset Neff(T) + 1 dengan nilai Undef
siapa tau dibutuhin buat perhitungan
*/
void CreateEmptyTabel (Tabel *T);
/*
membuat tabel kosong, Neff(T) = 0;
*/
void ConvertInput (Tabel *T, string S, boolean *IsSyntaxTrue);
/*
Menginput string ke dalam array dengan mengecek syntaxnya
*/
int Priority(char X);
/* Mengembalikan prioritas operator relatif terhadap jenisnya,
seperti '()' memiliki prioritas 4, '^' memiliki prioritas 3,
'*' dan '/' memiliki prioritas 2, dan '+' dan '-' prioritas 1 */
infotype charToInt(char X);
/* Mengubah karakter ke integer yang bersesuaian */
void Rapihin(Tabel *T);
/* Merapihkan array sehingga rapat kiri */
int IdxHighPrio(Tabel T);
/* Mengembalikan indeks tabel dengan operator prioritas tertinggi */
boolean IsOperator(char X);
/* Mengembalikan true bila karakter yang dibaca adalah operator */
boolean IsKurung(char X);
/*mengembalikan true jika karakter yg dibaca adalah buka atau tutup kurung*/
void Hitung(Tabel *T, int i);
/* Menghitung hasi dari operator di indeks i dan menympannya kembali di tabel
lalu menghapus elemen-elemen tabel yang telah dihitung */
void MakeUndef(Tabel *T, int i);
/* Membuat elemen tabel ke i menjadi tak terdefinisi alias kosong */
boolean ElmtUndef(Tabel T, int i);
/* Mengembalikan true bila elemen-elemen di indeks ke i adalah elemen Undef semua */

#endif