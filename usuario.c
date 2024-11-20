
#include "functions.h"
#include "structs.h"
#include <stdio.h>
#include <stdlib.h>
char *usuarios[] = {
    "nombre=pepito,apellido=asd", "nombre=paquito,apellido=asdasd"};
response getUsuario()
{
    char *strReturn = (char *)malloc((1024 + 1) * sizeof(char));
    int cantSize = sizeof(usuarios) / sizeof(usuarios[0]);
    int inxStr = 0;
    response respuesta = {-1, ""};
    for (int i = 0; i < cantSize; i++)
    {
        char *str = usuarios[i];
        int j = 0;
        while (str[j])
        {
            strReturn[inxStr] = str[j];
            inxStr++;
            j++;
        }
    }
    if (cantSize != 0)
    {
        respuesta = (response){200, strReturn};
    }
    return respuesta;
}
response getUsuarioParams(int i)
{

    response respuesta;
    if (sizeof(usuarios) / sizeof(usuarios[0]) > i)
    {
        respuesta = (response){200, usuarios[i]};
    }
    else
    {
        respuesta = (response){-1, ""};
    }
    return respuesta;
}