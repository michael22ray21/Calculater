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
        /* printf("Syntax Benar\n");
        printf("NEff(T) = %d\n",NEff(T));
        for (int i=1;i<=NEff(T);i++)
        {
            printf ("%.2f%c| %d%c| %c\n", Nilai(T,i), 9, Prio(T,i), 9, Oper(T,i));
        } */
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
