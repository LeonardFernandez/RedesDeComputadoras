#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include "functions.h"
#include "structs.h"

#define maxSizeMethod 8
#define maxSizeParam 16
#define maxSizePath 16
#define maxSizeQuery 256
// agrego un comentario "vacio" donde deberia limpiar memoria
int pointer = 0;
char *GetSubstringUntil(char *str, char *charToFind, int maxSizeStr, int voidChar)
{
    // GET/usuario
    int size = strlen(str);
    int j = 0;
    int bool = 0;
    char *strReturn = (char *)malloc((maxSizeStr + 1) * sizeof(char));
    while (bool == 0)
    {
        if (j >= maxSizeStr - 1 || j > size)
        {
            bool = 2;
        }
        else
        {
            pointer++;
            int charToFindSize = strlen(charToFind);
            if (voidChar)
            {
                charToFindSize = charToFindSize + 1;
            }
            int charFinded = 0;
            int i = 0;
            while (charFinded == 0 && i < charToFindSize)
            {
                charFinded = str[j] == charToFind[i];
                i++;
            }

            if (charFinded)
            {
                if (str[j] == '\0' && voidChar)
                {
                    pointer = pointer - 1; // Si encontramos x ejemplo GET/CLIENTE
                    // le restamos 1 al pointer porque encontramos el vacio y no queremos irnos de la cadena
                }
                bool = 1;
            }
            else
            {
                strReturn[j] = str[j];
            }
        }

        j++;
    }
    if (bool == 2)
    {
        strReturn[0] = '\0'; //"Vacio" la cadena a retornar
                             // No se encontro el caracter recorriendo hasta el tamaño maximo
    }
    else
    {
        strReturn[j] = '\0';
    }
    return strReturn;
}

char *extractMethod(char *str)
{
    // Este parametro necesita recibir -> METHOD/ <-
    char *method = "";
    if (strlen(str) != 0)
    {
        method = GetSubstringUntil(str, "/", maxSizeMethod, 0);
    }
    return method;
}

char *extractQuery(char *str)
{
    char *param = "";
    if (strlen(str) != 0)
    {
        param = GetSubstringUntil(str, "", maxSizeQuery, 1);
    }
    return param;
}
char *extractParam(char *str)
{
    // Este parametro necesita recibir -> /PARAM <-
    char *param = "";
    if (strlen(str) != 0)
    {
        if (str[-1] == '/')
        {
            param = GetSubstringUntil(str, "?", maxSizeParam, 1);
        }
    }
    return param;
}
char *extractPath(char *str)
{
    // Este metodo necesita recibir -> PATH/ O PATH O PATH? <-
    char *path = "";
    if (strlen(str) != 0)
    {
        path = GetSubstringUntil(str, "?/", maxSizePath, 1);
    }
    return path;
}
response mapeoPath(char *path, char *query, char *method, char *param)
{
    response respuesta = {0, ""};

    if (!strcmp(path, "usuario"))
    {

        if (!strcmp(method, "GET"))
        {

            if (query[0] == '\0' && param[0] == '\0')
            {
                // No tiene parametro ni query
                respuesta = getUsuario();
            }
            if (query[0] == '\0' && param[0] != '\0')
            {
                // tiene query y no tiene parametro
            }
            if (query[0] == '\0' && param[0] != '\0')
            {

                char *endptr;
                int num = strtol(param, &endptr, 10);
                if (endptr[0] == '\0')
                {
                    // No hay error
                    respuesta = getUsuarioParams(num);
                }
                else
                {
                    // error al convertir el parametro a numero
                    // seter response con el statuscode de error x parametro
                }
                // tiene parametro y no tiene query
            }
            if (query[0] != '\0' && param[0] != '\0')
            {
                // tiene parametro y tiene query
            }
        }
    }
    return respuesta;
}
response requestIn(char *url)
{
    response respuesta;
    char *method = extractMethod(url);
    if (method[0] != '\0')
    {
        url = &url[pointer];
        pointer = 0;
    }
    //printf("Metodo :%s \n", method);
    // printf("URL :%s \n",url);

    char *path = extractPath(url);
    //printf("Path :%s \n", path);
    // SOLO HACER CAMBIOS EN URL SI TENGO PATH
    if (path[0] != '\0')
    {
        url = &url[pointer];
        pointer = 0;
    }

    // printf("URL :%s \n",url);

    char *param = extractParam(url);
    //printf("param :%s \n", param);
    if (param[0] != '\0')
    {
        url = &url[pointer];
        pointer = 0;
    }
    // printf("URL :%s \n",url);

    char *query = extractQuery(url);
    //printf("query :%s \n", query);
    // printf("URL :%s \n",url);
    respuesta = mapeoPath(path, query, method, param);
    return respuesta;
}

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
    char url[100];
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
                longitud = read(connectionfd, url, sizeof(url));
                // Aquí debería interpretarse la petición y devolver lo que solicita el cliente
                 if (longitud < 0) {
                    perror("Mensaje no leído\n");
                } else {
                    //iria lo que el joaco hizo (ver si es GET y responderle)
                    response respuesta;
                    //test (comentar luego)
                    printf("Solicitud recibida:URL: %s\n", url);
                    respuesta=requestIn(url);
                    printf("[SERVER]Respuesta del server:\nRespuesta:%s\n, StatusCode: %i\n", respuesta.response, respuesta.statusCode);
                    write(connectionfd, (response *)&respuesta, sizeof(response)); // Respondemos al cliente
                }
            } while (longitud > 0);

            close(connectionfd);
        }
    }

    close(sockfd);
    return 0;
}

