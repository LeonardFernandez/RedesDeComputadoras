
#include "functions.h"
#include "structs.h"
#include <stdio.h>
#include <stdlib.h>
char *usuarios[] = {
    "nombre=pepito,apellido=asd", "nombre=paquito,apellido=asd"};
response getUsuario()
{
    char *strReturn = (char *)malloc((1024 + 1) * sizeof(char));
    int cantSize = sizeof(usuarios);
    for (size_t i = 0; i < usuarios; i++)
    {
        for (size_t j = 0; j < strlen(usuarios[i]); j++)
        {
            /* code */
        }
    }

    printf("ENTRO A METODO USUARIO");
}
response getUsuarioParams(int i)
{
    response respuesta;
    if (sizeof(usuarios) < i)
    {
        respuesta.response = 200;
    }
    else
    {
        respuesta = {1, ""};
    }

    printf("ENTRO A METODO USUARIO CON ID %i", i);
}