#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

/*enum é uma definição de dados que o usuário faz. Ele pode ser usado para para
transformar em tipo certos inteiros, strings e chars.
Por exemplo: tenho "abc", logo através do enum eu considero ele como tipo
"minhasLestras"*/
enum TokenType { 
  INVALIDO, 
  MAIS, 
  MENOS, 
  MULTIPLIC, 
  POTENCIA, 
  DIVISAO,
  TALVEZ_DOUBLE,
  DOUBLE,
  INTEIRO,
  PONTO
};

static const char *TokenTypeStrings[] = {
  "INVALIDO", 
  "MAIS", 
  "MENOS", 
  "MULTIPLIC", 
  "POTENCIA", 
  "DIVISAO",
  "TALVEZ_DOUBLE",
  "DOUBLE",
  "INTEIRO",
  "PONTO"
};


int main(int argc, char **argv) {
  enum TokenType type;

  // Read in the code from a file
  if (argc != 2) {
    fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
    return 1;
  }

  FILE *fp = fopen(argv[1], "rb");

  if (fp == NULL) {
    fprintf(stderr, "Unable to open file '%s'\n", argv[1]);
    return 1;
  }

  int text_length;

  fseek(fp, 0L, SEEK_END);
  text_length = ftell(fp);
  fseek(fp, 0L, SEEK_SET);

  char *text = (char *)calloc(text_length, sizeof(char));
  fread(text, sizeof(char), text_length, fp);
  fclose(fp);

  // mais espaço só por garantia
  char *token = (char *)malloc(text_length * sizeof(char));

  text[text_length] = '\0';
  token[text_length] = '\0';

  int cont = 0;
  bool suddenIter = false;
  // Interpret the code
  for (int i = 0; i < text_length; i++) {
    // printf("%c\n", text[i]);
    
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
        //Se no decorrer da função cair em um estado que talvez seja um double, ele confirmará ao rodá-la novamente
        if(type == TALVEZ_DOUBLE)
        {
          type = DOUBLE;
          token[cont] = text[i];
          //printf("double: %c\n", token[cont]);
        }
        else
        {
          type = INTEIRO;
          token[cont] = text[i];
          //printf("int: %c\n", token[cont]);
        }

        while(isdigit(text[i]) || text[i] == '.')
        {
          //No momento que o número tem um ponto, ele já pode ser considerado um double
          if (text[i] == '.')
          {
              if(type != DOUBLE)
              {
                  type = DOUBLE;
              }
          }

          token[cont] = text[i];
          //printf("while: %c\n", token[cont]);
          
          cont++;
          i++;
        }
    }
    else
    {
      //Se não foi confirmado um double acima, então é apenas um ponto
      if(type == TALVEZ_DOUBLE)
      {
        type = PONTO;
        token[cont] = text[i];
        //printf("talvez double else: %c\n", token[cont]);
      }
      else
      {
        switch (text[i]) {
          case '+':
            type = MAIS;
            token[cont] = text[i];
            //printf("Token: [\"%s\", Tipo: %s]\n", token, TokenTypeStrings[type]);
            break;
      
          case '-':
            type = MENOS;
            token[cont] = text[i];
            //printf("Token: [\"%s\", Tipo: %s]\n", token, TokenTypeStrings[type]);
            break;
      
          case '*':
            if (text[i + 1] != '\0' && text[i + 1] == '*')
            {
              type = POTENCIA;
              token[cont] = text[i];
              
              i++;
              cont++;
              
              token[cont] = text[i];
            } 
            else 
            {
              type = MULTIPLIC;
              token[cont] = text[i];
            }
      
            //printf("Token: [\"%s\", Tipo: %s]\n", token, TokenTypeStrings[type]);
            break;
      
          case '/':
            type = DIVISAO;
            token[cont] = text[i];
            //printf("Token: [\"%s\", Tipo: %s]\n", token, TokenTypeStrings[type]);
            break;


          case '.':
            type = TALVEZ_DOUBLE;
            token[cont] = text[i];
            //printf("Token: [\"%s\", Tipo: %s]\n", token, TokenTypeStrings[type]);
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
      
          default:
            type = INVALIDO;
            token[cont] = text[i];
            //printf("Token: [\"%s\", Tipo: %s]\n", token, TokenTypeStrings[type]);
            break;
        }
      }  
    }

    if(!suddenIter)
    {
      printf("Token: [\"%s\", Tipo: %s]\n", token, TokenTypeStrings[type]);
    }
  }

  free(text);
  free(token);

  //"make" para dar build no código -> e depois "./main lexer.txt" para rodar o
  //código

  return 0;
}