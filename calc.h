#ifndef CALC_H
#define CALC_H

#include <math.h>
#include "boolean.h"

typedef struct
{
    char oper; /* Tempat menyimpan operator */
    double nilai; /* Tempat menyimpan nilai real operan */
    int prio; /* Prioritas operator */
} elmt; /* Type elemen tabel */
typedef struct
{
    elmt matArr[101]; /* Array */
    int Neff; /* Banyaknya elemen efektif array */
} Tabel; /* Type array */

#define ElmtUndef 'E'
#define OperUndef 'N'
#define NEff(T) (T).Neff
#define Oper(T, i) (T).matArr[i].oper
#define Prio(T, i) (T).matArr[i].prio
#define Nilai(T, i) (T).matArr[i].nilai

int Priority(char X);
/* Mengembalikan prioritas operator relatif terhadap jenisnya,
seperti '^' memiliki prioritas 3,'*' dan '/' memiliki prioritas 2,
dan '+' dan '-' prioritas 1 */
int charToInt(char X);
/* Mengubah karakter ke integer yang bersesuaian */
void Rapihin(Tabel *T);
/* Merapihkan array sehingga rapat kiri */
int IdxHighPrio(Tabel T);
/* Mengembalikan indeks tabel dengan operator prioritas tertinggi */
boolean IsOperator(char X);
/* Mengembalikan true bila karakter yang dibaca adalah operator */
void Hitung(Tabel *T, int i);
/* Menghitung hasi dari operator di indeks i dan menympannya kembali di tabel
lalu menghapus elemen-elemen tabel yang telah dihitung */
void MakeUndef(Tabel *T, int i);
/* Membuat elemen tabel ke i menjadi tak terdefinisi alias kosong */

#endif