#include <stdio.h>
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
boolean MathErr = false; /* Untuk stop codition saat menghitung bertemu dengan math error */

int main()
{
    /* KAMUS */
    int i = 0, j, k, baseprio;
    double temp;
    char C;
    char ekspresi[101];
    Tabel T;

    /* ALGORITMA */
    /* Membaca string */
    scanf("%s", &ekspresi[0]);
    /* Memasukkan string ke array */
    i = 0; j = 0; baseprio = 0;
    while (ekspresi[i] != '\0')
    {
        if (!IsOperator(ekspresi[i]))
        {
            /* Untuk menghitung nilai real dari masing-masing operan */
            temp = 0;
            while (!IsOperator(ekspresi[i]) && ekspresi[i] != '\0')
            {
                C = ekspresi[i];
                temp = temp*10 + (double) charToInt(C);
                i++;
            }
            /* Untuk menghitung nilai dibelakang koma */
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
        else /* Jika karakter di string sekarang adalah operator */
        {
            if (ekspresi[i] != '(' && ekspresi[i] != ')')
            {
                Oper(T, j) = ekspresi[i];
                Nilai(T, j) = NilaiUndef;
                Prio(T, j) = Priority(ekspresi[i]) + baseprio;
            }
            else
            {
                /* Karena kurung hanya meningkatkan prioritas suatu operasi,
                kurung tidak dimasukkan ke array tetapi hanya menambah base priority */
                if (ekspresi[i] == '(') baseprio += 4;
                /* Jika kurung tutup sudah ditemukan, turunkan kembali base priority */
                else baseprio -= 4;
                /* Karena kurung tidak masuk array maka iterator j harus tidak berubah */
                j--;
            }
            i++;
        }
        j++;
    }
    NEff(T) = j;
    while (NEff(T) != 1 && !MathErr)
    {
        /* Mencari indeks tempat operator yang memiliki prioritas paling tinggi */
        i = IdxHighPrio(T);
        /* Menghitung hasil operasi */
        Hitung(&T, i);
    }
    /* Jika MATH ERROR terjadi maka tampilkan pesan */
    if (MathErr) printf("MATH ERROR\n");
    /* Jika tidak tampilkan hasi perhitungan */
    else printf("Hasil operasi = %.2f\n", Nilai(T, 0));
}


int Priority(char X)
/* Mengembalikan prioritas operator relatif terhadap jenisnya,
seperti '()' memiliki prioritas 4, '^' memiliki prioritas 3,
'*' dan '/' memiliki prioritas 2, dan '+' dan '-' prioritas 1 */
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
/* Mengubah karakter ke integer yang bersesuaian */
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
/* Mengembalikan indeks tabel dengan operator prioritas tertinggi */
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
/* Mengembalikan true bila karakter yang dibaca adalah operator */
{
    /* KAMUS LOKAL */
    /* ALGORITMA */
    return (X == '+' || X == '-' || X == '*' || X == '.' || X == '/' || X == '(' || X == ')' || X == '^');
}

void MakeUndef(Tabel *T, int i)
/* Membuat elemen tabel ke i menjadi tak terdefinisi alias kosong */
{
    /* KAMUS LOKAL */
    /* ALGORITMA */
    Nilai(*T, i) = NilaiUndef;
    Oper(*T, i) = OperUndef;
    Prio(*T, i) = 0;
}

boolean ElmtUndef(Tabel T, int i)
/* Mengembalikan true bila elemen-elemen di indeks ke i adalah elemen Undef semua */
{
    /* KAMUS LOKAL */
    /* ALGORITMA */
    return (Oper(T, i) == OperUndef && Nilai(T, i) == NilaiUndef);
}

void Rapihin(Tabel *T)
/* Merapihkan array sehingga rapat kiri */
{
    /* KAMUS LOKAL */
    int IdxKos = 0, i, j;

    /* ALGORITMA */
    /* Mencari tempat pertama terjadinya kekosongan pada array */
    while (!ElmtUndef(*T, IdxKos) && IdxKos < NEff(*T)) IdxKos++;
    /* Mencari elemen yang tidak rapat kiri */
    i = IdxKos;
    while (ElmtUndef(*T, i) && i < NEff(*T)) i++;
    /* Melakukan pemindahan */
    for (j = i; j < NEff(*T); j++)
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
    if (Nilai(*T, i) != NilaiUndef)
    {
        Prio(*T, i) -= 4;
    }
    else
    {
        op1 = Nilai(*T, i - 1);
        op2 = Nilai(*T, i + 1);
         /* Menghitung hasi operasi yang sesuai dengan operatornya */
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
        Nilai(*T, i - 1) = hasil;
        Oper(*T, i - 1) = OperUndef;
        Prio(*T, i - 1) = Prio(*T, i) - Priority(Oper(*T, i));
        MakeUndef(T, i);
        MakeUndef(T, i + 1);
        Rapihin(T);
    }
}