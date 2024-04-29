#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define NUMESTADOS 15
#define NUMCOLS 13

const char *TOKEN_STRINGS[] = {
    "",
    "",
    "ID",
    "",
    "CONSTANTE",
    "SUMA",
    "RESTA",
    "PARENIZQUIERDO",
    "PARENDERECHO",
    "COMA",
    "PUNTOYCOMA",
    "",
    "ASIGNACION",
    "FDT",
    "ERRORLEXICO"
};

FILE* in;

typedef enum { 
 ID, CONSTANTE, SUMA, RESTA, PARENIZQUIERDO, PARENDERECHO, COMA, PUNTOYCOMA, ASIGNACION, FDT, ERRORLEXICO } TOKEN; 
TOKEN scanner (void); 


/**************************Scanner************************************/ 
TOKEN scanner(){
    char buffer[32];
 

                int tabla[NUMESTADOS][NUMCOLS] =  {
                   {  1,  3,  5,  6,  7,  8,  9, 10, 11, 14, 13,  0, 14 },
 				    {  1,  1,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2 },
 				    { 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14 },
				    {  4,  3,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4 },
				    { 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14 },
				    { 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14 },
				    { 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14 },
				    { 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14 },
				    { 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14 },
				    { 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14 },
				    { 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14 },
				    { 14, 14, 14, 14, 14, 14, 14, 14, 14, 12, 14, 14, 14 },
				    { 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14 },
				    { 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14 },
				    { 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14 } };
 int car, col, estado = 0, i = 0;
 do{
  car = fgetc(in);
  col = columna(car);
  estado = tabla[estado][col];
  if ( col != 11 ){
   buffer[i] = car;
   i++;
  } 
 }
 while ( !estadoFinal(estado) && !(estado == 14) );
 buffer[i] = '\0';
 if (estado != 2 && estado != 4)
 {
    printf("%s es %s \n", buffer, TOKEN_STRINGS[estado]);
 }
 switch ( estado ){
  case 2 : if ( col != 11 ){
	    ungetc(car, in);
	    buffer[i-1] = '\0';
        printf("%s es %s \n", buffer, TOKEN_STRINGS[estado]);
	   }
   	   return ID;
  case 4 : if ( col != 11 ){
	    ungetc(car, in);
	    buffer[i-1] = '\0';
        printf("%s es %s \n", buffer, TOKEN_STRINGS[estado]);
	   }
           return CONSTANTE;
  case 5 : return SUMA;
  case 6 : return RESTA;
  case 7 : return PARENIZQUIERDO;
  case 8 : return PARENDERECHO;
  case 9 : return COMA;
  case 10 : return PUNTOYCOMA;
  case 12 : return ASIGNACION;
  case 13 : return FDT;
  case 14 : return ERRORLEXICO;
 }
 return 0;
}


int estadoFinal(int e)
{
 if ( e == 0 || e == 1 || e == 3 || e == 11 || e == 14 ) return 0;
 return 1;
}

int columna(int c)
{
 if ( isalpha(c) ) return 0;
 if ( isdigit(c) ) return 1;
 if ( c == '+' ) return 2;
 if ( c == '-' ) return 3;
 if ( c == '(' ) return 4;
 if ( c == ')' ) return 5;
 if ( c == ',' ) return 6;
 if ( c == ';' ) return 7;
 if ( c == ':' ) return 8;
 if ( c == '=' ) return 9;
 if ( c == EOF ) return 10;
 if ( isspace(c) ) return 11;
 return 12;
}


/*************Fin Scanner**********************************************/

int main(int argc, char* argv[])
{
    /*
  char* nomArchi = "textoPrueba.txt";

 if ( argc == 1 )
 {
  printf("Debe ingresar el nombre del archivo fuente (en lenguaje Micro) en la linea de comandos\n");
  return -1;
 }
 if ( argc != 2 )
 {
  printf("Numero incorrecto de argumentos\n");
  return -1;
 }
 
 strcpy(nomArchi, argv[1]);
 int l = strlen(nomArchi);
 if ( l > TAMNOM )
 {
  printf("Nombre incorrecto del Archivo Fuente\n");
  return -1;
 }
 if ( nomArchi[l-1] != 'm' || nomArchi[l-2] != '.' )
 {
  printf("Nombre incorrecto del Archivo Fuente\n");
  return -1;
 }
 */

 if ( (in = fopen("texto.m", "r")) == NULL )
 {
  printf("No se pudo abrir archivo fuente\n");
  return -1;
 }

 while(!feof(in))
 {
    scanner();
 }
scanner();
 fclose(in);
 return 0;

}
