#include <stdio.h>
#include <math.h>
#include "boolean.h"

typedef struct
{
    char oper;
    double nilai;
    int prio;
} elmt;
typedef struct 
{
    elmt matArr[101];
    int Neff;
} Tabel;

#define OperUndef '?'
#define NilaiUndef -999
#define NEff(T) (T).Neff
#define Oper(T, i) (T).matArr[i].oper
#define Prio(T, i) (T).matArr[i].prio
#define Nilai(T, i) (T).matArr[i].nilai

int Priority(char X);
/* Mengembalikan prioritas operator relatif terhadap jenisnya,
seperti '()' memiliki prioritas 4, '^' memiliki prioritas 3,
 '*' dan '/' memiliki prioritas 2, dan '+' dan '-' prioritas 1 */
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
boolean ElmtUndef(Tabel T, int i);
/* Mengembalikan true bila elemen-elemen di indeks ke i adalah elemen Undef semua */

/* KAMUS GLOBAL */
boolean MathErr = false;

int main()
{
    /* KAMUS */
    int i = 0, j, k, baseprio;
    double temp;
    char C;
    char ekspresi[101];
    Tabel T;

    /* ALGORITMA */
    scanf("%s", &ekspresi[0]);
    i = 0; j = 0; baseprio = 0;
    while (ekspresi[i] != '\0')
    {
        if (!IsOperator(ekspresi[i]))
        {
            temp = 0;
            while (!IsOperator(ekspresi[i]) && ekspresi[i] != '\0')
            {
                C = ekspresi[i];
                temp = temp*10 + (double) charToInt(C);
                i++;
            }
            if (ekspresi[i] == '.')
            {
                i++; k = 1;
                while (!IsOperator(ekspresi[i]) && ekspresi[i] != '\0')
                {
                    C = ekspresi[i];
                    temp += ((double) charToInt(C))/(pow(10, k));
                    i++; k++;
                }
            }
            Nilai(T, j) = temp;
            Oper(T, j) = OperUndef;
            Prio(T, j) = Priority('0') + baseprio;
        }
        else
        {
            if (ekspresi[i] != '(' && ekspresi[i] != ')')
            {
                Oper(T, j) = ekspresi[i];
                Nilai(T, j) = NilaiUndef;
                Prio(T, j) = Priority(ekspresi[i]) + baseprio;
            }
            else
            {
                if (ekspresi[i] == '(') baseprio += 4;
                else baseprio -= 4;
                j--;
            }
            i++;
        }
        j++;
    }
    NEff(T) = j;/* 
    for (k = 0; k < j; k++)
    {
        printf("%d\nOperan = %c\nNilai = %.2f\nPriority = %d\n\n", k, Oper(T, k), Nilai(T, k), Prio(T, k));
    } */
    while (NEff(T) != 1 && !MathErr)
    {
        i = IdxHighPrio(T);
        /* printf("Indeks = %d\n", i); */
        Hitung(&T, i);
    }
    if (MathErr) printf("MATH ERROR\n");
    else printf("Hasil operasi = %.2f\n", Nilai(T, 0));
}

int Priority(char X)
{
    /* KAMUS LOKAL */
    /* ALGORITMA */
    switch (X)
    {
        case '+' :
        case '-' : return 1; break;
        case '*' :
        case '/' : return 2; break;
        case '^' : return 3; break;
        default : return 0;
    }
}

int charToInt(char X)
{
    /* KAMUS LOKAL */
    /* ALGORITMA */
    switch (X)
    {
        case '1' : return 1; break;
        case '2' : return 2; break;
        case '3' : return 3; break;
        case '4' : return 4; break;
        case '5' : return 5; break;
        case '6' : return 6; break;
        case '7' : return 7; break;
        case '8' : return 8; break;
        case '9' : return 9; break;
        default : return 0;
    }
}

int IdxHighPrio(Tabel T)
{
    /* KAMUS LOKAL */
    int i;
    int Maxtemp, Idxtemp;

    /* ALGORITMA */
    for (i = 0; i < NEff(T); i++)
    {
        if (Prio(T, i) > Maxtemp)
        {
            Maxtemp = Prio(T, i);
            Idxtemp = i;
        }
    }
    return Idxtemp;
}

boolean IsOperator(char X)
{
    /* KAMUS LOKAL */
    /* ALGORITMA */
    return (X == '+' || X == '-' || X == '*' || X == '.' || X == '/' || X == '(' || X == ')' || X == '^');
}

void MakeUndef(Tabel *T, int i)
{
    /* KAMUS LOKAL */
    /* ALGORITMA */
    Nilai(*T, i) = NilaiUndef;
    Oper(*T, i) = OperUndef;
    Prio(*T, i) = 0;
}

boolean ElmtUndef(Tabel T, int i)
{
    /* KAMUS LOKAL */
    /* ALGORITMA */
    return (Oper(T, i) == OperUndef && Nilai(T, i) == NilaiUndef);
}

void Rapihin(Tabel *T)
{
    /* KAMUS LOKAL */
    int IdxKos = 0, i, j;

    /* ALGORITMA */
    while (!ElmtUndef(*T, IdxKos) && IdxKos < NEff(*T)) IdxKos++;
    i = IdxKos;
    while (ElmtUndef(*T, i) && i < NEff(*T)) i++;
    for (j = i; j < NEff(*T); j++)
    {
        Prio(*T, IdxKos) = Prio(*T, i);
        Oper(*T, IdxKos) = Oper(*T, i);
        Nilai(*T, IdxKos) = Nilai(*T, i);
        MakeUndef(T, i);
        IdxKos++; i++;
    }
    j = i - IdxKos;
    NEff(*T) -= j;
}

void Hitung(Tabel *T, int i)
{
    /* KAMUS LOKAL */
    int temp;
    double op1, op2, hasil = 0;

    /* ALGORITMA */
    if (Nilai(*T, i) != NilaiUndef)
    {
        Prio(*T, i) -= 4;
    }
    else
    {
        op1 = Nilai(*T, i - 1);
        op2 = Nilai(*T, i + 1);
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
        /* printf("%.2f %c %.2f = %.2f\n", op1, Oper(*T, i), op2, hasil); */
        Nilai(*T, i - 1) = hasil;
        Oper(*T, i - 1) = OperUndef;
        Prio(*T, i - 1) = Prio(*T, i) - Priority(Oper(*T, i));
        MakeUndef(T, i);
        MakeUndef(T, i + 1);
        Rapihin(T);
    }
}