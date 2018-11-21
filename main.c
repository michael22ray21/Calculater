#include <stdio.h>
#include "valinput.h"
#include "boolean.h"

int main()
{
    /* KAMUS */
    Tabel T;
    boolean IsSyntaxTrue;

    /* ALGORITMA */
    InputUser(&T,&IsSyntaxTrue);
    if (IsSyntaxTrue)
    {
        printf("Syntax Benar\n");
        printf("NEff(T) = %d\n",NEff(T));
        for (int i=1;i<=NEff(T);i++)
        {
            printf ("%f  | %d   | %c \n",Nilai(T,i),Prio(T,i),Oper(T,i));
        }
    }
    else
    {
        printf("Syntax salah\n");
    }
    return 0;
}
