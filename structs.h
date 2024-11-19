#ifndef STRUCTS_H
#define STRUCTS_H
typedef struct
{
    int statusCode;
    char response[1024]; // Lo uso en usuario si se cambia hay q modificarlo
} response;
#endif
