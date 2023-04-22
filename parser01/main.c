#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

/*enum é uma definição de dados que o usuário faz. Ele pode ser usado para para
transformar em tipo certos inteiros, strings e chars.
Por exemplo: tenho "abc", logo através do enum eu considero ele como tipo
"minhasLestras"*/

typedef enum {
  INVALIDO, 
  MAIS, 
  MENOS, 
  MULTIPLIC, 
  POTENCIA, 
  DIVISAO,
  TALVEZ_DOUBLE,
  REAL,
  INTEIRO,
  PONTO,
  FIM
} TokenType;

static const char *TokenTypeStrings[] = {
  "INVALIDO", 
  "MAIS", 
  "MENOS", 
  "MULTIPLIC", 
  "POTENCIA", 
  "DIVISAO",
  "TALVEZ_DOUBLE",
  "REAL",
  "INTEIRO",
  "PONTO",
  "FIM"
};

//################################# Variaveis globais #########################################

char *token;
char *text;
int text_length;
TokenType type;

//contador global
int i = 0;

int inteiro = 0;
double real = 0.0;

//#############################################################################################


void nextToken()
{
  int cont = 0;
  bool suddenIter = false;

  // printf("%c\n", text[i]);
  //printf("i: %d\n", i);
   // para limpar os conteúdos da string
  memset(token,0,strlen(token));
  cont = 0;

  if(suddenIter)
  {
    suddenIter = false;
    i--;
  }

  //isdigit() é uma função que sempre reconhece um número inteiro
  if(isdigit(text[i]))
  { 
    bool containsDot = false;
    
    while(isdigit(text[i]) || text[i] == '.')
    {
      //printf("i no while: %d\n", i);
      //No momento que o número tem um ponto, ele já pode ser considerado um double
      if (text[i] == '.')
      {
        containsDot = true;
        if(type != REAL)
        {
          type = REAL;
        }
      }
      else if (type == REAL)
      {
        if(containsDot == false)
        {
          type = INTEIRO;
        }
      }
      
      token[cont] = text[i];
      //printf("while: %c\n", token[cont]);

      cont++;
      i++;      
    }
    //printf("Sai do while\n");
  //Não é necessario considerar o tipo como um inteiro antes deste loop. Se sair do loop e não for REAL e nem TALVEZ_DOUBLE, significa q é um inteiro
    if(type != REAL && type != TALVEZ_DOUBLE)
    {
      //printf("i int: %d\n", i);
      type = INTEIRO;
      inteiro = atoll(token);
      //printf("int: %c\n", token[cont]);
      //printf("%d", i);
    }

    if(type == REAL)
    {
      //printf("i r: %d\n", i);
      real = strtod(token,NULL);
    }

    if(i == text_length)
    {
      i--;
    }

  }
  else
  {
    //Se não foi confirmado um double acima, então é apenas um ponto
    if(type == TALVEZ_DOUBLE)
    {
      type = PONTO;
      token[cont] = text[i];
      //printf("%d", i);
      //printf("talvez double else: %c\n", token[cont]);
    }
    else
    {
      switch (text[i]) {
        case '+':
          type = MAIS;
          token[cont] = text[i];
          //printf("%d", i);
          i++;
          break;      
        
        case '.':
          type = TALVEZ_DOUBLE;
          token[cont] = text[i];
          i++;
          break;
    
        case ' ':
          i++;
          suddenIter = true;
          break;
    
        case '\n':
          i++;
          suddenIter = true;
          break;
    
        case '\t':
          i++;
          suddenIter = true;
          break;
        
        case '\0':
          type = FIM;
          //printf("fim: %d", i);
          break;
    
        default:
          type = INVALIDO;
          token[cont] = text[i];
          //printf("Token: [\"%s\", Tipo: %s]\n", token, TokenTypeStrings[type]);
          break;
      }
    }
  }

  if(!suddenIter && type != TALVEZ_DOUBLE)
  {
    printf("Token: [\"%s\", Tipo: %s]\n", token, TokenTypeStrings[type]); 
  }
   i++;
}



float Number() {
  //Rodar função do lexer
  nextToken();
  if (type == INTEIRO) 
  {
    printf("Número inteiro: %d\n", inteiro);
    return inteiro;  
  } 
    
  else if (type == REAL)
  {
    printf("Número real %f\n", real);
    return real;
  } 
  else 
  {
    printf("Não é um número\n");
    exit(1);
  }
}



float Term() {
  float left = Number();

  //rodar função do lexer
  nextToken();

  if (type == MAIS) 
  {
    printf("tipo mais\n");
    float right = Number();
    printf("%f + %f = %f\n", left, right, left + right);
    
    return left + right;
  } 
  else if (type == FIM) 
  {
    return left;
  } 
  else {
    printf("Token: inválido\n");
    exit(1);
  }
}




int main(int argc, char **argv) {
  // Read in the code from a file
  if (argc != 2) {
    fprintf(stderr, "Uso: %s <filename>\n", argv[0]);
    return 1;
  }

  FILE *fp = fopen(argv[1], "rb");

  if (fp == NULL) {
    fprintf(stderr, "Incapaz de abrir arquivo '%s'\n", argv[1]);
    return 1;
  }

  fseek(fp, 0L, SEEK_END);
  text_length = ftell(fp);
  fseek(fp, 0L, SEEK_SET);

  text = (char *)calloc(text_length, sizeof(char));
  fread(text, sizeof(char), text_length, fp);
  fclose(fp);

  // mais espaço só por garantia
  token = (char *)malloc(text_length * sizeof(char));

  text[text_length] = '\0';
  token[text_length] = '\0';


  while(i <= text_length)
  {
    printf("%f\n", Term());
  }

  free(text);
  free(token);

  //"make" para dar build no código -> e depois "./main parser.txt" para rodar o
  //código
  
  return 0;
}
