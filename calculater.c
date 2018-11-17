#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "calculater.h"

/* KAMUS GLOBAL */
void CreateEmptyTabel (Tabel *T){
	NEff(*T) = 0;
}
////////////////////
void ConvertInput(Tabel *T, string S, boolean *IsSyntaxTrue) {
	char LastChar, CurrChar;
	int i, prio, nkoma, op, close;
	infotype number;
	boolean IsKoma;
	
	CreateEmptyTabel(T);
	i = 0;
	MakeUndef(T,NEff(*T)+1);
	
	CurrChar = S[i];
	if (IsOperator(CurrChar)) {
		*IsSyntaxTrue = false;
	}
	else {
		*IsSyntaxTrue = true;
		IsKoma = false;
		nkoma = 0;
		NEff(*T) = 1; prio = 0;
		number = charToInt(CurrChar);
		LastChar = CurrChar;
		i++;
		op = 0; close = 0;
		MakeUndef(T,NEff(*T)+1);
		
		while (S[i] != '\0' && IsSyntaxTrue) { /// sampe sini
			
			CurrChar = S[i];
			if (IsOperator(LastChar)&&IsOperator(CurrChar) && CurrChar != '-'){ 
				//ada dua operator sebelahan
	
				*IsSyntaxTrue = false;
			}
			else if ( LastChar == '('&&IsOperator(CurrChar)&&(CurrChar != '.')) { 
				//setelah kurung buka ada operator
				
				*IsSyntaxTrue = false;
			}
			else if ((!IsOperator(LastChar) && !IsKurung(LastChar)) && (CurrChar = '(')) {
				//sebelum kurung buka bilangan
				
				*IsSyntaxTrue = false;
			}
			
			else if ((!IsOperator(CurrChar) && !IsKurung(CurrChar)) && (LastChar = ')')) {
				//setelah kurung tutup bilangan
				
				*IsSyntaxTrue = false;
			}
			else if (close > op) {
				//jika ada tutup kurung yang muncul terlebih dulu ") ... ("
				
				*IsSyntaxTrue = false;			
			}
			
			else if (!IsOperator(CurrChar)&&!IsKurung(CurrChar)) {
				if (IsKoma) {
					//jika bilangan sudah masuk pecahan
					
					number = number + charToInt(CurrChar)/(nkoma*10);
					nkoma++;
				}
				else {
					//jika bilangan masih bilangan bulat
					number = 10*number + charToInt(CurrChar);
				}
			}
			else  {
				if (CurrChar == '(') { //tambah piorotas dan op
					prio += 4;
					op++;
				}
				else if (CurrChar = ')') { //kurang prioritas dan tambah close
					prio -= 4;
					close++;
				}
				else if (CurrChar = '.') {
					if (IsKoma) {
						//Jika dalam satu operan ada 2 titik
						*IsSyntaxTrue = false;
					}
					else {
						//dari integer masuk ke float
						IsKoma = true;
						nkoma = 1;
					}
				}
				else {
					//nambah ke array setelah lewatin semua case diatas
					NEff(*T)++;
					Nilai(*T, NEff(*T)) = number;
					Oper(*T,NEff(*T)) = CurrChar;
					Prio(*T,NEff(*T)) = prio + Priority(CurrChar);
					
					IsKoma = false; nkoma = 0;
					MakeUndef(T,NEff(*T)+1);
					number = 0;
				}					
			}
			
			LastChar = CurrChar;
			i++;
			
		}
		
		//case setelah pembacaan selesai
		if (op != close) {		//jumlah kurung tutup kurang
			*IsSyntaxTrue = false;
		}
		if (IsOperator(CurrChar)) {  //karakter terakhir operator
			*IsSyntaxTrue = false;
		}
		
		if (*IsSyntaxTrue) {
			NEff(*T)++;
			Nilai(*T, NEff(*T)) = number;
			Oper(*T,NEff(*T)) = '=';
			Prio(*T,NEff(*T)) = prio;
			MakeUndef(T,NEff(*T)+1);
		}
		else {
			CreateEmptyTabel(T);
		}
	}
	
}
////////////////////////////
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

infotype charToInt(char X)
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
    return (X == '+' || X == '-' || X == '*' || X == '.' || X == '/' || X == '^');
}

boolean IsKurung(char X) {
	return ( X == '(' || X == ')');
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
                //else MathErr = true;
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
                    //else MathErr = true;
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