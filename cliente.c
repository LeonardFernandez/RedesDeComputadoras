#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include "structs.h"

typedef struct {
    char method[10];
    char url[100];
} HttpRequest;

int main(int argc, char *argv[]) {
    response respuesta;
    int sockfd, portno, n;
    char url[100];
    struct sockaddr_in serv_addr;
    struct hostent *server;
    char buffer[4096]; // Para recibir la respuesta

    if (argc < 3) {
        printf("Para %s ingrese nombre del servidor y el numero de puerto\n", argv[0]);
       exit(1);
    }
    portno = atoi(argv[2]); // Captura el número de puerto de salida

    // Crear el socket
    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    server = gethostbyname(argv[1]); // Recuperar la información del servidor
    if (server == NULL) {
        fprintf(stderr,"ERROR, %s no conoce ese servidor\n", argv[1]);
        exit(2);
    }

    // Rellenar la estructura del socket del cliente
    bzero((char *)&serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy((char *)server->h_addr, (char *)&serv_addr.sin_addr.s_addr, server->h_length);
    serv_addr.sin_port = htons(portno);

    // Conectar con el servidor
    if (connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        error("Error al conectar con el servidor");
    }

    // Construir una solicitud HTTP básica
    printf("Ingrese la URL: ");
    bzero(url, sizeof(url));
    fgets(url, sizeof(url), stdin);
    strtok(url, "\n"); // Remover el salto de línea

   // strcpy(req.method, "GET"); // Usamos el método GET
    printf("Enviando solicitud: URL: %s\n", url);

    n = write(sockfd, url, sizeof(url));
    if (n < 0) {
        error("Conexion no aceptada\n");
    }

    // Leer la respuesta del servidor
    n = read(sockfd, (response *)&respuesta, sizeof(response));
    if (n < 0) {
        error("ERROR de lectura del socket\n");
    }

    // Mostrar la respuesta del servidor
    printf("[CLIENTE]Respuesta del server:\nRespuesta:%s\n, StatusCode: %i\n", respuesta.response, respuesta.statusCode);

    close(sockfd);
    return 0;
}
