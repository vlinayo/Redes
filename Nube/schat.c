/*Universidad Simón Bolivar
Proyecto 1.
Redes I
Grupo: Verónica Irene Liñayo Vega 08-10615
        Karina Valera 06-40414 


schat: Programa que simula la conexión de un servidor a una sala que pertenece a una Red, se le ingresa el nombre del puerto a usar para el servidor, el nombre de la sala a la que se desea conectar y esto pone en funcionamiento al servidor, dejandolo en espera de que distintos clientes le realicen solicitudes variadas.
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

#define QUEUELENGTH 5

/*Función que permite la lectura y escritura del servidor*/
void echo(int sockfd) {
  char c;
  int status;

  while (read(sockfd, &c, 1) == 1)
    /* Echo the character. */
    if (write(sockfd, &c, 1) != 1)
      printf("can't write to socket");
}
    

/*variales para lectura de la entrada*/
char *puerto = NULL;
char *sala = NULL;
int opt;


/*Se hace la llamada respectiva al servidor schat [-p <puerto>] [-s <sala>] */
/*Puertos de prueba a usar:
	p1: 20615 
	p2: 20414
	*/


void error_entrada(char *name, int exitcode) {
        if (exitcode != EX_OK) fprintf(stderr, "\n");
        fprintf((exitcode == EX_OK) ? stdout : stderr,
                        "Sintaxis correcta: %s ./schat -s <puerto> -s <sala> \n"
                        "\n"
                        "Detalles de las opciones:\n"
// -------------------------------------------- OPCIONES ------------------------------------------------------------------------------------//
                        "  -p <puerto>      : Numero del puerto al que se desea conectar.\n"
                        "  -s <sala>   : Nombre de la sala a conectar.\n", name);

// --------------------------------------FIN DE OPCIONES-------------------------------------------------------------------------------------//
        exit(exitcode);
}



int main ( int argc, char *argv[]) {

while(( opt = getopt(argc, argv, "p:s")) != -1) switch (opt) {
      
	case 'p':
		if(puerto != NULL) free(puerto);
		if(asprintf(&puerto, "%s", optarg) == -1) {
			fprintf(stderr, "%s:Error en la lectura del puerto.\n", argv[0]);
		exit(EX_OSERR);
		}
		break;

	case 's':
		if (sala != NULL) free(sala);
		if(asprintf(&sala, "%s", optarg) == -1) {
			fprintf(stderr, "%s:Error en la lectura del la sala.\n", argv[0]);
		exit(EX_OSERR);
		}
		break;


	default:
	    error_entrada(argv[0],EX_USAGE);

	}

// -------------------------------- CONDICIONES DE ENTRADA ---------------------------------------------------------------------------------//


	if (puerto == NULL) {
                fprintf(stderr, "%s: Es obligatorio especificar un puerto.\n", argv[0]);
                error_entrada(argv[0], EX_USAGE);
        }
        if (sala == NULL) {
                fprintf(stderr, "%s: Es obligatorio especificar una sala.\n", argv[0]);
                error_entrada(argv[0], EX_USAGE);
        }

// ---------------------------------------- FIN CONDICIONES ---------------------------------------------------------------------------------//

// ------------------------------------- MANEJADOR CONEXIÓN SOCKETS--------------------------------------------------------------------------//


/*Inicializamos variables y estructuras necesarias para configurar al servidor*/

  int sockfd, newsockfd, child;
  struct sockaddr_in clientaddr, serveraddr;
  int clientaddrlength;
  int pid;

  /* Abrimos el Socket TCP. */
  sockfd = socket(AF_INET, SOCK_STREAM, 0);
  if (sockfd < 0)
    printf("can't open socket");

  /* Hacemos el Bind de la dirección con el Socket. */
  bzero(&serveraddr, sizeof(serveraddr));
  serveraddr.sin_family = AF_INET;
  serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);
  serveraddr.sin_port = htons(atoi(puerto));
  if (bind(sockfd, (struct sockaddr *) &serveraddr,
           sizeof(serveraddr)) != 0)
    printf("can't bind to socket");
  if (listen(sockfd, QUEUELENGTH) < 0)
    printf("can't listen");

  while (1) {
    /* Esperamos por alguna conexión. */
    clientaddrlength = sizeof(clientaddr);
    newsockfd = accept(sockfd, 
                       (struct sockaddr *) &clientaddr,
                       &clientaddrlength);
    if (newsockfd < 0)
      printf("accept failure");

    /* Realizamos Fork para manejar la conexión. */
    pid = fork();
    if (pid < 0)
      printf("fork error");
    else if (pid == 0) {
      /* EL hijo, se crea para hacerse cargo de los requerimientos que van llegando. */
      echo(newsockfd);
      printf("El hijo se muere cuando el cliente se muere\n");
      exit(EXIT_SUCCESS);
    }
    else
      {
	/* EL padre se mantiene vivo esperando nuevos requerimientos. */
	printf("El papa muere. Queda mi hijo haciendo el echo. Chao...\n");
	close(newsockfd);
      }
  }
	exit(EXIT_SUCCESS);

}//fin del main.
