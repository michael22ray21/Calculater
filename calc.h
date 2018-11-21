#ifndef CALC_H
#define CALC_H

#include <math.h>
#include "boolean.h"
#include "valinput.h"

#define ElmtUndef 'E'
#define IdxMin 1

extern boolean MathErr;
/* Untuk stop codition saat menghitung bertemu dengan math error */

void Rapihin(Tabel *T);
/* Merapihkan array sehingga rapat kiri */
int IdxHighPrio(Tabel T);
/* Mengembalikan indeks tabel dengan operator prioritas tertinggi */
boolean IsOneElmt(Tabel T);
/* Mengembalikan true jika tabel hanya berisi 1 elemen */
void Hitung(Tabel *T, int i);
/* Menghitung hasi dari operator di indeks i dan menympannya kembali di tabel
lalu menghapus elemen-elemen tabel yang telah dihitung */
void MakeUndef(Tabel *T, int i);
/* Membuat elemen tabel ke i menjadi tak terdefinisi alias kosong */

#endif