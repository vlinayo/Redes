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
bool err= 0;

/*Se hace la llamada respectiva al servidor cchat [-h <host>] [-p <puerto>] [-n <nombre>][-a <archivo>] */
/*opciones de puerto:
	p1: 20615 
	p2: 20414
	*/

	void error (err){

    printf ("%s\n\n","Verifique numero y orden de los argumentos.");
    printf ("%s\n\n","La sintaxis correcta es: cchat -h -p -n -a");
    printf("cchat , refiere al nombre del archivo ./cchat \n");
    printf("-h , se usara en minúscula, y se refiere al nombre o dirección IP del computador donde se ejecuta schat \n");
    printf("-p , se usara en minúscula, y se refiere al numero del puerto, el mismo puede ser 20615 o 20414 \n");
    printf("-n, se usara en minúscula, y se refiere al nombre del usuario \n");
	printf("-a, se usara en minúscula, y se refiere al nombre y direccion relativa o absoluta de un archivo en el que habrá un comando \n");
	err = 0;
    }

void entrada( char *a, char *b, char *c, char *d, char *e){

	if (a = "./cchat"){
		printf("schat en posicion\n");
		}
	else{
		err= 1;
		error(err);
		}
		
	if(strcmp(b, "159.90.10.9") == 0){   //supongo que es con la IP del LDC.. (PREGUNTAAAR!!)
		printf("nombre o dirección IP es: %s\n", b);
	}else{
		err=1;
		error(err);
		}

	if(strcmp(c, "20615") == 0){
		printf("el puerto de conexión es: %s\n", c);
	
	}else if (strcmp(c, "20414") == 0){
		printf("el puerto de conexión es: %s\n", c);
	
	}else{
		printf("ERROR! en el valor del puerto de conexión\n");
	    printf("-p , se usara en minúscula, y se refiere al numero del puerto, el mismo puede ser 20615 o 20414 \n");
		exit(0);
		}
	
	printf("el nombre del usuario es: %s\n" , d);
	printf("el nombre del archivo con los comando es: %s\n" , e);
}


int main ( int argc, char *argv[]) {

if (argc == 5) {
        entrada (argv[0], argv[1], argv[2], argv[3] , argv[4]);
	}else{
		/* arrojamos exception por sintaxis , error*/
		err = 1;
		error(err);
	
	}
}
