#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*enum é uma definição de dados que o usuário faz. Ele pode ser usado para para
transformar em tipo certos inteiros, strings e chars.
Por exemplo: tenho "abc", logo através do enum eu considero ele como tipo "minhasLestras"*/
enum TokenType {
    IDENTIFICADOR,
    MAIS,
    MENOS,
    MULTIPLIC,
    POTENCIA,
    DIVISAO   
};

static const char *TokenTypeStrings[] = {
    "IDENTIFICADOR",
    "MAIS",
    "MENOS",
    "MULTIPLIC",
    "POTENCIA",
    "DIVISAO"   
};


int main(int argc, char *argv[]) {
    char *text;
    int text_length;
    
    //mais espaço só por garantia 
    char *token = malloc(3*sizeof(char));

    enum TokenType type;

    // Read in the code from a file
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    FILE *fp = fopen(argv[1], "r");
    if (fp == NULL) {
        fprintf(stderr, "Unable to open file '%s'\n", argv[1]);
        return 1;
    }

    fseek(fp, 0, SEEK_END);
    text_length = ftell(fp);
    fseek(fp, 0, SEEK_SET);

    text = malloc(text_length + 1);
    fread(text, 1, text_length, fp);
    fclose(fp);

    text[text_length] = '\0';

    

    // Interpret the code
    for (int i = 0; i < text_length; i++) 
    {
        switch (text[i]) {
            case '+':
                type = MAIS;
                token = text[i];
                printf("Token: [\"%s\", Tipo: %s]\n", token, TokenTypeStrings[type]);
                break;

            case '-':
                type = MENOS;
                token = text[i];
                printf("Token: [\"%s\", Tipo: %s]\n", token, TokenTypeStrings[type]);
                break;

            case '*':
                /*if(text[i+1] != '\0' && text[i+1] == '*')
                {
                    type = POTENCIA;
                    token = text[i];
                    token += text[i+1];
                }
                else
                {
                    type = MULTIPLIC;
                    token = text[i];
                } */
                type = MULTIPLIC;
                token = text[i];
                printf("Token: [\"%s\", Tipo: %s]\n", token, TokenTypeStrings[type]);              
                break;

            case '/':
                type = DIVISAO;
                token = text[i];
                printf("Token: [\"%s\", Tipo: %s]\n", token, TokenTypeStrings[type]);
                break;

            default:
                type = IDENTIFICADOR;
                token = text[i];
                printf("Token: [\"%s\", Tipo: %s]\n", token, TokenTypeStrings[type]);
                break;           
        }

        //para limpar os conteúdos da string
        memset(token,0,strlen(token));
    }

    free(text);
    free(token);

    return 0;
}