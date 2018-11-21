#ifndef _VALINPUT_h
#define _VALINPUT_h

#include "boolean.h"

#define OperUndef '?'
#define NilaiUndef -999
#define MAXEL 100
typedef double infotype;
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

/* fungsi2 */
void CreateEmptyTabel (Tabel *T);
/*
membuat tabel kosong, Neff(T) = 0; */
void InputUser(Tabel *T,boolean *IsSyntaxTrue);

void InputToArray(string S, Tabel *T);

boolean SyntaxValidity(string S,int i,boolean IsNeg,boolean IsFrac);

boolean IsBalancedKurung(string S);

boolean IsBlank(char C);

boolean IsDigit(char C);

boolean IsDot(char C);

boolean IsNegSign(char C);

boolean IsBukaKurung(char C);

boolean IstutupKurung(char C);

boolean IsOperator(char C);

boolean IsKurung(char C);

infotype charToInt(char C);

int Priority(char C);



/*mengembalikan true jika karakter yg dibaca adalah buka atau tutup kurung*/

#endif
