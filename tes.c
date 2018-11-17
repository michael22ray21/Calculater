#include <stdio.h>
#include "calculater.h"

int main() {
	
	string S;
	Tabel T;
	boolean IsSyntaxTrue;
	
	scanf("%s",S);
	ConvertInput(&T,S,&IsSyntaxTrue);
	
	if (IsSyntaxTrue) {
		printf("Syntax sudah benar\n");
	}
	else {
		printf("Syntax salah!!");
	}
	return 0;
}