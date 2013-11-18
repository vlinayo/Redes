/*Universidad SimÃ³n Bolivar
Proyecto 2.
Sistemas de OperaciÃ³n I
Grupo 07
*/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include "queue.h"
#include "queue.c"
#include <sys/types.h>


int main ( int argc, char *argv[]) {
  if (argc > 4 || argc < 3) {
    printf ("%s\n","NÃºmero de argumentos invÃ¡lido.");
    printf ("%s\n","La sintaxis correcta es: arbol [-x] -f <nombre de archivo de salida>");
  
    }else if (argc == 3) {
        if (strcmp(argv[1] , "-f") == 0){

// Se prepara la creacion del archivo.
    
        FILE *archivo;
        char caracter;
        int len= 1000;
        char buffer[len];
        int i=0;
        int cont=0;
         
        archivo = fopen(argv[2],"w");
        queue *cola;
        cola = newQueue();
        node *primero;
        int a = 1;
        int b= 2;
        int c;


    //se procede a la escritura para una entrada de 3 argumentos.
          
        c = b + b;
        fprintf(archivo,"%d",c); /* Escribe los datos */
        fprintf(archivo,"%s","\n"); /* Escribe los datos */
        fclose(archivo);  /* Cierra los archivos */
        return 0;
         
        }else{
        printf ("%s\n","error de sintaxis");
        printf ("%s\n","La sintaxis correcta es: arbol [-x] -f <nombre de archivo de salida>");

        }// fin del else.
     }//fin del else if

else{

   // Se prepara la creacion del archivo.
    
        FILE *archivo;
        char caracter;
        int len= 1000;
        char buffer[len];
        int i=0;
        int cont=0;
         
        archivo = fopen(argv[3],"w");
        queue *cola;
        cola = newQueue();
        node *primero;
        int a = 1;
        int b= 2;
        int c;


    //se procede a la escritura para una entrada de 4 argumentos.
          
        c = a + b;
        fprintf(archivo,"%d",c); /* Escribe los datos */
        fprintf(archivo,"%s","\n"); /* Escribe los datos */
        fclose(archivo);  /* Cierra los archivos */
        return 0;   
        }//fin del else.


}