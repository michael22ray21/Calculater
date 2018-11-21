#include <stdio.h>
#include <math.h>
#include "calc.h"
#include "boolean.h"


/* KAMUS GLOBAL */
boolean MathErr = false;
/* Untuk stop codition saat menghitung bertemu dengan math error */

boolean IsOneElmt(Tabel T)
/* Mengembalikan true jika tabel hanya berisi 1 elemen */
{
    /* KAMUS LOKAL */
    /* ALGORITMA */
    return (NEff(T) == 1);
}

int IdxHighPrio(Tabel T)
/* Mengembalikan indeks tabel dengan operator prioritas tertinggi */
{
    /* KAMUS LOKAL */
    int i;
    int Maxtemp = Prio(T,IdxMin);
    int Idxtemp;

    /* ALGORITMA */
    for (i = IdxMin; i <= NEff(T); i++)
    {
        if (Prio(T, i) > Maxtemp)
        {
            Maxtemp = Prio(T, i);
            Idxtemp = i;
        }
    }
    return Idxtemp;
}

void MakeUndef(Tabel *T, int i)
/* Membuat elemen tabel ke i menjadi tak terdefinisi alias kosong */
{
    /* KAMUS LOKAL */
    /* ALGORITMA */
    Oper(*T, i) = ElmtUndef;
}

void Rapihin(Tabel *T)
/* Merapihkan array sehingga rapat kiri */
{
    /* KAMUS LOKAL */
    int IdxKos = IdxMin, i, j;

    /* ALGORITMA */
    /* Mencari tempat pertama terjadinya kekosongan pada array */
    while ((Oper(*T,IdxKos) != ElmtUndef) && (IdxKos <= NEff(*T))) IdxKos++;
    if (IdxKos == NEff(*T))
    {
        if (Oper(*T,IdxKos) == ElmtUndef)
        {
            NEff(*T)--;
        }
    }
    else
    {
        /* Mencari elemen yang tidak rapat kiri */
        i = IdxKos;
        while ((Oper(*T,i) == ElmtUndef) && i <= NEff(*T)) i++;
        /* Melakukan pemindahan */
        for (j = i; j <= NEff(*T); j++)
        {
            Prio(*T, IdxKos) = Prio(*T, i);
            Oper(*T, IdxKos) = Oper(*T, i);
            Nilai(*T, IdxKos) = Nilai(*T, i);
            MakeUndef(T, i);
            IdxKos++; i++;
        }
        /* Dikarenakan adanya kekosongan, maka isi elemen tabel akan berkurang */
        j = i - IdxKos;
        NEff(*T) -= j;
    }
}

void Hitung(Tabel *T, int i)
/* Menghitung hasi dari operator di indeks i dan menympannya kembali di tabel
lalu menghapus elemen-elemen tabel yang telah dihitung */
{
    /* KAMUS LOKAL */
    int temp;
    double op1, op2, hasil = 0;

    /* ALGORITMA */
    /* Jika elemen yang berprioritas tinggi adalah operan,
    kurangi prioritasnya menjadi selevel dengan elemen diluarnya */
    if (Oper(*T,i) == OperUndef)
    {
        Prio(*T, i) -= 4;
    }
    else
    {
        op1 = Nilai(*T, i - 1);
        op2 = Nilai(*T, i + 1);
         /* Menghitung hasil operasi yang sesuai dengan operatornya */
        switch (Oper(*T, i))
        {
            case '*':
                hasil = op1 * op2;
                break;
            case '/':
                if (op2 != 0) hasil = op1 / op2;
                else MathErr = true;
                break;
            case '+':
                hasil = op1 + op2;
                break;
            case '-':
                hasil = op1 - op2;
                break;
            case '^':
                if (op1 >= 0) hasil = pow(op1, op2);
                else
                {
                    temp = 1.0/op2;
                    if (temp % 2 == 1 && 0 <= op2 && op2 < 1)
                    {
                        hasil = pow(op1, op2);
                    }
                    else MathErr = true;
                }
        }
        /* Memasukkan hasil agar tetap rapat, merapikan tabel,
        membuat elemen yang telah dipakai menjadi Undefined */
        // printf("%.2f %c %.2f = %.2f\n", op1, Oper(*T, i), op2, hasil);
        Nilai(*T, i - 1) = hasil;
        MakeUndef(T, i);
        MakeUndef(T, i + 1);
        Rapihin(T);
    }
}