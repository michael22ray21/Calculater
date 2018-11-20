#include <stdio.h>
#include "boolean.h"
#include "valinput.h"

/* fungsi2 */
void CreateEmptyTabel (Tabel *T) {
    NEff(*T) = 0;
}
/*membuat tabel kosong, Neff(T) = 0 */
void InputUser(Tabel *T,boolean *IsSyntaxTrue) {
  string S;

  scanf("%s",S);
  CreateEmptyTabel(T);
  *IsSyntaxTrue = SyntaxValidity(S,0,false,false);
  if (*IsSyntaxTrue) {
    InputToArray(S,T);
  }
}

void InputToArray(string S, Tabel *T) {
  char LastChar, CurrChar;
  int i, neff, prio, nfrac;
  infotype number, neg;
  boolean IsNeg, IsFrac;

  i = 0;
  prio = 0;
  neff = 0; neg = 1;
  number = 0;
  IsNeg = false;
  IsFrac = false;
  nfrac = 1;
  CurrChar = S[i];
  LastChar = OperUndef;

  while (S[i] != '\0') {
    CurrChar = S[i];
    if (IsOperator(CurrChar) && !(IsNeg && CurrChar == '-')) {
        neff++;
        Nilai(*T,neff) = NilaiUndef;
        Oper(*T,neff) = CurrChar;
        Prio(*T,neff) = prio + Priority(CurrChar);
        IsFrac = false;
        nfrac = 1;
    }

    else if (IsKurung(CurrChar)) {

      if (CurrChar == '(' && S[i+1] == '-') {
        if (!IsNeg) {
          IsNeg = true;
          neg *= -1;
        }
        else
          neg *= -1;
      }

      else {
        prio += Priority(CurrChar);
      }
    }

    else {
      if (CurrChar == '.') {

        IsFrac = true;
      }
      else {
        if (IsFrac) {

          number = number + charToInt(CurrChar)/(nfrac*10);
          nfrac*=10;
        }
        else {

          number = 10*number + charToInt(CurrChar);
        }
      }
      if (IsOperator(S[i+1]) || S[i+1]==')' || S[i+1] == '\0') {
        neff++;
        Nilai(*T,neff) = number;
        Oper(*T,neff) = OperUndef;
        Prio(*T,neff) = prio;

        if (IsNeg && S[i+1]==')') {
          Nilai(*T,neff) *= neg;
          i++;
        }
        number = 0;
        IsFrac = false;
        nfrac = 1;
        IsNeg = false;
        neg = 1;
      }
    }
    i++;
    LastChar = CurrChar;
    }
    NEff(*T) = neff;

}

boolean SyntaxValidity(string S, int i,boolean IsNeg, boolean IsFrac) {

  if (!IsBalancedKurung(S)) {
    return false;
  }
  else {
    if (IsBlank(S[i])) {
      return true;
    }
    else if (i==0) {
      if (IsBukaKurung(S[i])&&IsNegSign(S[i+1])) {
        return SyntaxValidity(S,i+2,true,IsFrac);
      }
      else if (IsBukaKurung(S[i])&&(IsDigit(S[i+1])||IsBukaKurung(S[i+1]))) {
        return SyntaxValidity(S,i+1,IsNeg,IsFrac);
      }
      else if (IsDigit(S[i])&&(IsDigit(S[i+1])||IsOperator(S[i+1])||IsBlank(S[i+1])||IsDot(S[i+1]))) {
        return SyntaxValidity(S,i+1,IsNeg,IsFrac);
      }
      else {
        return false;
      }
    }
    else if (IsBukaKurung(S[i])) {
      if (IsNegSign(S[i+1]))
        return SyntaxValidity(S,i+2,true,IsFrac);
      else if (IsDigit(S[i+1])||IsBukaKurung(S[i+1]))
        return SyntaxValidity(S,i+1,IsNeg,IsFrac);
      else
        return false;
    }
    else if (IstutupKurung(S[i])) {
      if (IsOperator(S[i+1])||IstutupKurung(S[i+1])||IsBlank(S[i+1]))
        return SyntaxValidity(S,i+1,false,false);
      else
        return false;
    }
    else if (IsOperator(S[i])) {
      if (IsDigit(S[i+1])||IsBukaKurung(S[i+1]))
        return SyntaxValidity(S,i+1,IsNeg,false);
      else
        return false;
    }
    else if (IsDot(S[i])) {
      if (!IsFrac)
        return SyntaxValidity(S,i+1,IsNeg,true);
      else
        return false;
    }
    else if (IsDigit(S[i])) {
      if (IsNeg) {
        if (!IsFrac) {
          if (IsDigit(S[i+1])||(IsDot(S[i+1])||IstutupKurung(S[i+1])))
            return SyntaxValidity(S,i+1,IsNeg,IsFrac);
          else
            return false;
        }
        else {
          if (IsDigit(S[i+1])||IstutupKurung(S[i+1]))
            return SyntaxValidity(S,i+1,IsNeg,IsFrac);
          else
            return false;
        }
      }
      else  { //!IsNeg
        if (!IsFrac) {
          if (IsDigit(S[i+1])||(IsDot(S[i+1])||IstutupKurung(S[i+1])||IsOperator(S[i+1])||IsBlank(S[i+1])))
            return SyntaxValidity(S,i+1,IsNeg,IsFrac);
          else
            return false;
        }
        else {
          if (IsDigit(S[i+1])||IstutupKurung(S[i+1])||IsBlank(S[i+1]))
            return SyntaxValidity(S,i+1,IsNeg,IsFrac);
          else if (IsOperator(S[i+1]))
            return SyntaxValidity(S,i+1,IsNeg,false);
          else
            return false;
        }
      }
    }

  }
  //return 0;
}

boolean IsBalancedKurung(string S) {
  int open, close, i;
  boolean IsBalance;

  i = 0;
  open = 0; close = 0;
  IsBalance = true;
  while (S[i]!= '\0' && IsBalance) {
    if (S[i]=='(') {
      open++;
    }
    else if (S[i]==')') {
      close++;
    }
    if (close > open) {
      IsBalance = false;
    }
    i++;
  }

  if (open != close) {
    IsBalance = false;
  }

  return IsBalance;
}
boolean IsBlank(char C) {
  return C =='\0';
}
boolean IsDigit(char C) {
  return (C=='1'||C=='2'||C=='3'||C=='4'||C=='5'||C=='6'||C=='7'||C=='8'||C=='9'||C=='0');
}
boolean IsDot(char C) {
  return C=='.';
}
boolean IsNegSign(char C) {
  return C=='-';
}
boolean IsBukaKurung(char C) {
  return C=='(';
}
boolean IstutupKurung(char C) {
  return C==')';
}
boolean IsOperator(char C) {
  return (C == '+' ||C == '-' || C == '*' || C == '/' || C == '^');
}
boolean IsKurung(char C) {
  return ( C == '(' || C == ')');
}
infotype charToInt(char C) {
  switch (C)
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
int Priority(char C) {
  switch (C)
  {
    case '(' : return 4; break;
    case ')' : return -4; break;
    case '+' :
    case '-' : return 1; break;
    case '*' :
    case '/' : return 2; break;
    case '^' : return 3; break;
    default : return 0;
  }
}
