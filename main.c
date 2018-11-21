#include <stdio.h>
#include "valinput.h"
#include "boolean.h"
#include "calc.h"

int main()
{
    /* KAMUS */
    Tabel T;
    boolean IsSyntaxTrue;

    /* ALGORITMA */
    InputUser(&T,&IsSyntaxTrue);
    if (IsSyntaxTrue)
    {
        while (!IsOneElmt(T) && !MathErr)
        {
            Hitung(&T, IdxHighPrio(T));
        }
        if (MathErr) printf("MATH ERROR!\n");
        else printf("Hasil perhitungan : %.2f\n", Nilai(T, IdxMin));
    }
    else
    {
        printf("SYNTAX ERROR!\n");
    }
    return 0;
}