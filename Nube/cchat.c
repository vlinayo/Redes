/*Universidad Simón Bolivar
Proyecto 1.
Redes I
Grupo: Verónica Irene Liñayo Vega 08-10615
            Karina Valera 06-40414

cchat: programa que hace la vez de cliente para el servidor schat, y permite realizar la conexión por medio del uso de sockets, y el cual permite que los usuarios generados a través de este programa interactúen con el servidor mediante el uso de los comandos establecidos en el proyecto.

*/


/*opciones de puerto:
	p1: 20615 
	p2: 20414
	*/


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <netdb.h>
#include <netinet/in.h>
#include <pthread.h>
#include <unistd.h>
#include <getopt.h>
#include <sysexits.h>
#include <errno.h>

#define true 1;
#define false 0;
typedef int bool;

/*variales globales para la lectura de la entrada*/
char *server=NULL;
char *puerto=NULL;
char *nombre=NULL;
char *archivo=NULL;
int opt;

void copy(int sockfd) {
  int c;
  char outbuffer;
  char inbuffer;

  while ((c = getchar()) != EOF) {
    /* Write a character to the socket. */
    outbuffer = c;
    if (write(sockfd, &outbuffer, 1) != 1)
      printf("can't write to socket");
    /* Read the response and print it. */
    if (read(sockfd, &inbuffer, 1) != 1)
      printf("can't read from socket");
    putchar(inbuffer);
  }
}


/*Función utilizada para los errores de sintaxis de entrada*/
void error_entrada(char *name, int exitcode) {
        if (exitcode != EX_OK) fprintf(stderr, "\n");
        fprintf((exitcode == EX_OK) ? stdout : stderr,
                        "Sintaxis correcta: %s ./cchat -h <host> -p <puerto> -n <nombre> -a <archivo> \n"
                        "\n"
                        "Detalles de las opciones:\n"
// -------------------------------------------- OPCIONES ------------------------------------------------------------------------------------//
			"  -h <host>      : Nombre o dirección IP donde está corriendo schat.\n"                        
			"  -p <puerto>    : Numero del puerto que schat usará para recibir las conexiones.\n"
                        "  -n <nombre>    : Nombre del usuario que se conecta como cliente.\n"
			"  -a <archivo>   : Archivo de texto que posee los comandos a ejecutar.\n", name);
// --------------------------------------FIN DE OPCIONES-------------------------------------------------------------------------------------//
        exit(exitcode);
}

int main ( int argc, char *argv[]) {

/*Función getop, permite que manejemos la entrada de forma aleatoria, y usamos case para señalar los posibles casos de la entrada */
while((opt = getopt(argc, argv, "h:p:n:a"))!=-1) switch (opt) {
	case 'h':
		if(server!=NULL) free(server);
		if(asprintf(&server, "%s", optarg) == -1){
			fprintf(stderr, "%s: Error en la lectura del host.\n", argv[0]);
		exit(EX_OSERR);
		}
		break;

	case 'p':
		if(puerto!=NULL) free(puerto);
		if(asprintf(&puerto, "%s", optarg) == -1){
			fprintf(stderr, "%s: Error en la lectura del puerto.\n", argv[0]);
		exit(EX_OSERR);
		}
		break;
	case 'n':
		if(nombre!=NULL) free(nombre);
		if(asprintf(&nombre, "%s", optarg) == -1){
			fprintf(stderr, "%s: Error en la lectura del nombre.\n", argv[0]);
		exit(EX_OSERR);
		}
		break;
	case 'a':
		if(archivo!=NULL) free(archivo);
		if(asprintf(&archivo, "%s", optarg) == -1){
			fprintf(stderr, "%s: Error en la lectura del archivo.\n", argv[0]);
		exit(EX_OSERR);
		}
		break;

	default:
		error_entrada(argv[0], EX_USAGE);
	}

// -------------------------------- CONDICIONES DE ENTRADA ---------------------------------------------------------------------------------//

if(server==NULL){
	fprintf(stderr, "%s: Es obligatorio especificar un host.\n", argv[0]);
                error_entrada(argv[0], EX_USAGE);
	}

if(puerto==NULL){
	fprintf(stderr, "%s: Es obligatorio especificar un puerto.\n", argv[0]);
                error_entrada(argv[0], EX_USAGE);
	}

if(nombre==NULL){
	fprintf(stderr, "%s: Es obligatorio especificar un nombre.\n", argv[0]);
                error_entrada(argv[0], EX_USAGE);
	}

if(archivo==NULL){
	fprintf(stderr, "%s: Es obligatorio especificar un archivo.\n", argv[0]);
                error_entrada(argv[0], EX_USAGE);
	}


// ---------------------------------------- FIN CONDICIONES ---------------------------------------------------------------------------------//

// ------------------------------------- MANEJADOR CONEXIÓN SOCKETS--------------------------------------------------------------------------//
 

  /* Variables y estructuras necesarias para la configuración del cliente */
    int sockfd;
    struct sockaddr_in serveraddr;


  /* Obtenemos la dirección del servidor. */
  bzero(&serveraddr, sizeof(serveraddr));
  serveraddr.sin_family = AF_INET;
  serveraddr.sin_addr.s_addr = inet_addr(server);
  serveraddr.sin_port = htons(atoi(puerto));

  /* Abrimos el servidor. */
  sockfd = socket(AF_INET, SOCK_STREAM, 0);
  if (sockfd < 0)
    printf("can't open socket");

  /* Nos conectamos al servidor. */
  if (connect(sockfd, (struct sockaddr *) &serveraddr,
              sizeof(serveraddr)) < 0)
    printf("can't connect to server");

  /* Copiamos los valores ingresador por consola al servidor. */
  copy(sockfd);
  close(sockfd);

  exit(EXIT_SUCCESS);
}

// -------------------------------------- FIN MANEJADOR DE CONEXIÓN--------------------------------------------------------------------------//

