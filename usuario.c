
#include "functions.h"
#include "structs.h"
#include <stdio.h>
#include <stdlib.h>
char *usuarios[] = {
    "nombre=pepito,apellido=asd", "nombre=paquito,apellido=asdasd"};
response getUsuario()
{
    int cantSize = sizeof(usuarios) / sizeof(usuarios[0]);
    int inxStr = 0;
    response respuesta;
    for (int i = 0; i < cantSize; i++)
    {
        char *str = usuarios[i];
        int j = 0;
        while (str[j])
        {
            respuesta.response[inxStr] = str[j];
            inxStr++;
            j++;
        }
    }
    if (cantSize != 0)
    {
        if(respuesta.response[inxStr]!='\0'){
            respuesta.response[inxStr+1]='\0';
        }
        respuesta.statusCode=200;
    }

    return respuesta;
}
response getUsuarioParams(int i)
{

    response respuesta;
    if (sizeof(usuarios) / sizeof(usuarios[0]) > i)
    {
        respuesta.statusCode=200;
        char *str = usuarios[i];
        int j = 0;
        while (str[j])
        {
            respuesta.response[j] = str[j];
            j++;
        }
        
    }
    else
    {
        respuesta = (response){-1, ""};
    }
    return respuesta;
}