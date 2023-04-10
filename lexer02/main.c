#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
  DIVISAO 
};

static const char *TokenTypeStrings[] = {
  "INVALIDO", 
  "MAIS", 
  "MENOS", 
  "MULTIPLIC", 
  "POTENCIA", 
  "DIVISAO"
};

int main(int argc, char **argv) {
  // mais espaço só por garantia
  char *token = (char *)malloc(3 * sizeof(char));

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

  text[text_length] = '\0';

  int cont = 0;
  // Interpret the code
  for (int i = 0; i < text_length; i++) {
    // printf("%c\n", text[i]);
    switch (text[i]) {
    case '+':
      type = MAIS;
      token[0] = text[i];
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

    /*case ' ':
      i++;
      break;

    case '\n':
      i++;
      break;

    case '\t':
      i++;
      break;*/

    default:
      type = INVALIDO;
      token[cont] = text[i];
      //printf("Token: [\"%s\", Tipo: %s]\n", token, TokenTypeStrings[type]);
      break;
    }
    printf("Token: [\"%s\", Tipo: %s]\n", token, TokenTypeStrings[type]);
    // para limpar os conteúdos da string
    memset(token,0,strlen(token));
    cont = 0;
  }

  free(text);
  free(token);

  //"make" para dar build no código -> e depois "./main lexer.txt" para rodar o
  //código

  return 0;
}