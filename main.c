#include "calc.h"
#include <stdio.h>
#include <math.h>


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
                Prio(T, j) = Priority(ekspresi[i]) + baseprio;
            }
            else
            {
                /* Karena kurung hanya meningkatkan prioritas suatu operasi,
                kurung tidak dimasukkan ke array tetapi hanya menambah base priority */
                if (ekspresi[i] == '(') {
                    baseprio += 4;
                }
                /* Jika kurung tutup sudah ditemukan, turunkan kembali base priority */
                else{
                    baseprio -= 4;
                }
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