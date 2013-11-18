/*Universidad Simón Bolivar
Proyecto 1.
Redes I
Grupo: Verónica Irene Liñayo Vega 08-10615
        Karina Valera 06-40414 
*/


#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>

#define true 1;
#define false 0;
typedef int bool;


/*variales globales de prueba*/
int a = 2;
int b= 3;
int result;
bool err= 0;

/*Se hace la llamada respectiva al servidor schat [-p <puerto>] [-s <sala>] */
/*opciones de puerto:
	p1: 20615 
	p2: 20414
	*/

	void error (err){

    printf ("%s\n\n","Verifique Número y Orden de los argumentos.");
    printf ("%s\n\n","La sintaxis correcta es: schat -p -s");
    printf("schat , refiere al nombre del archivo ./schat \n");
    printf("-p , se usara en minúscula, y se refiere al numero del puerto, el mismo puede ser 20615 o 20414 \n");
    printf("-s , se usara en minúscula, y se refiere al nombre de la sala, si desea que se use el valor por defecto (actual) , escribir -s \n");
	err = 0;
    }

void entrada( char *a, char *b, char *c){

	if (a = "./schat"){
		printf("schat en posicion\n");
		}
	else{
		err= 1;
		error(err);
		}

	if(strcmp(b, "20615") == 0){
		printf("el puerto de conexión es: %s\n", b);
	
	}else if (strcmp(b, "20414") == 0){
		printf("el puerto de conexión es: %s\n", b);
	
	}else{
		printf("ERROR! en el valor del puerto de conexión\n");
	    printf("-p , se usara en minúscula, y se refiere al numero del puerto, el mismo puede ser 20615 o 20414 \n");
		exit(0);
		}
	
	if(strcmp(c, "-s") == 0){
		printf("se llama a la sala por defecto: actual \n");
	
	}else{
		printf("se llama a la sala solicitada: %s\n" , c);
		}
}




int main ( int argc, char *argv[]) {

if (argc == 3) {
        entrada (argv[0], argv[1], argv[2]);
	}else{
		/* arrojamos exception por sintaxis , error*/
		err = 1;
		error(err);
	
	}
}
