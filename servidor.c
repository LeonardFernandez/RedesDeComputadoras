#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>


// Structs que definen el formato/protocolo de comunicación
typedef struct {
    char method[10];
    char url[100];
} HttpRequest;

typedef struct {
    int status_code;
    char body[4096];
} HttpResponse;

int main(int argc, char *argv[]) {
    int sockfd, connectionfd; // File descriptors para socket local y socket de conexión con el cliente
    struct sockaddr_in infoSocketServ, infoSocketClient; // Estructura que define puerto e IPv4
    int puerto, tamanio, longitud; // Variables auxiliares
    HttpRequest req; // Estructura para la solicitud HTTP
    puerto = 8080;

    // Crear el socket
    sockfd = socket(AF_INET, SOCK_STREAM, 0); // SOCK_STREAM --> TCP
    if (sockfd == -1) {
        printf("Error al crear el socket\n");
    } else {
        printf("Socket creado\n");
    }

    // Limpiamos la estructura del socket
    memset(&infoSocketServ, 0, sizeof(infoSocketServ));

    // Rellenamos la estructura del socket
    infoSocketServ.sin_family = AF_INET; // Asigna familia de direcciones
    infoSocketServ.sin_addr.s_addr = INADDR_ANY; // INADDR_ANY para asignar la IP local automáticamente
    infoSocketServ.sin_port = htons(puerto); // Asigna puerto, `htons` da el formato necesario

    // Bind: Asigna dirección IP y puerto al socket
    if (bind(sockfd, (struct sockaddr *)&infoSocketServ, sizeof(infoSocketServ)) < 0) {
        perror("Error en bind");
        return 1;
    }

    printf("Servidor escuchando en el puerto: %d\n", ntohs(infoSocketServ.sin_port));
    // Servidor comienza a escuchar, permitiendo conexiones
    listen(sockfd, 1);

    tamanio = sizeof(infoSocketClient);
    while (1) {
        connectionfd = accept(sockfd, (struct sockaddr *)&infoSocketClient, &tamanio);
        if (connectionfd < 0) {
            perror("Error de conexión");
        } else {
            do {
                // Recibimos la solicitud del cliente
                longitud = read(connectionfd, (struct HttpRequest *)&req, sizeof(HttpRequest));
                // Aquí debería interpretarse la petición y devolver lo que solicita el cliente
                 if (longitud < 0) {
                    perror("Mensaje no leído\n");
                } else {
                    //iria lo que el joaco hizo (ver si es GET y responderle)

                    //test (comentar luego)
                    printf("Solicitud recibida:\nMethod: %s\nURL: %s\n", req.method, req.url);
                    write(connectionfd, "Recibi tu mensaje", 17); // Respondemos al cliente
                }
            } while (longitud > 0);

            close(connectionfd);
        }
    }

    close(sockfd);
    return 0;
}

