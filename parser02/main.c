#include <stdio.h>
#include <stdlib.h>
#include "tinyexpr.h"

int main() {
  char input[100];
  float result;

  printf("Enter an arithmetic expression:\n");
  fgets(input, 100, stdin);

  // Parse the expression and compute the result
  int err;
  te_expr* expr = te_compile(input, NULL, 0, &err);
  
  if (expr) 
  {
    printf("Compilação feita com sucesso!\n");
    result = (float)te_eval(expr);

    // Print the result
    printf("Result: %f\n", result);
  } 
  else 
  {
    printf("Compilação falhou");
  }

   te_free(expr);
  
  return 0;
}