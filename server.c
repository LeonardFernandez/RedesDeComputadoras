#include <string.h>
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
int requestIn(char *url)
{
    char *method = extractMethod(url);
    if (method[0] != '\0')
    {
        url = &url[pointer];
        pointer = 0;
    }
    printf("Metodo :%s \n", method);
    // printf("URL :%s \n",url);

    char *path = extractPath(url);
    printf("Path :%s \n", path);
    // SOLO HACER CAMBIOS EN URL SI TENGO PATH
    if (path[0] != '\0')
    {
        url = &url[pointer];
        pointer = 0;
    }

    // printf("URL :%s \n",url);

    char *param = extractParam(url);
    printf("param :%s \n", param);
    if (param[0] != '\0')
    {
        url = &url[pointer];
        pointer = 0;
    }
    // printf("URL :%s \n",url);

    char *query = extractQuery(url);
    printf("query :%s \n", query);
    // printf("URL :%s \n",url);

    mapeoPath(path, query, method, param);
    return 0;
}
int mapeoPath(char *path, char *query, char *method, char *param)
{
    if (!strcmp(path, "usuario"))
    {

        if (!strcmp(method, "GET"))
        {

            if (query[0] == '\0' && param[0] == '\0')
            {
                // No tiene parametro ni query
                getUsuario();
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
                    getUsuarioParams(num);
                }
                else
                {
                    // error al convertir el parametro a numero
                }
                // tiene parametro y no tiene query
            }
            if (query[0] != '\0' && param[0] != '\0')
            {
                // tiene parametro y tiene query
            }
        }
    }
    return 0;
}
int main(int argc, char const *argv[])
{
    char *url = "GET/usuario/123";
    //  char *url = "GET/usuario?nombre=juan";
    //  char *url = "GET/usuario/123?nombre=juan";
    // char *url = "GET/usuario";
    printf("%s\n", url);
    requestIn(url);
    return 0;
}