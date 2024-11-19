#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#define maxSizeMethod 8
#define maxSizeParam 16
#define maxSizePath 16
// agrego un comentario "vacio" donde deberia limpiar memoria
int pointer = 0;
char *GetSubstringUntil(char *str, char *charToFind, int maxSizeStr,int voidChar)
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
            int charToFindSize = strlen(charToFind);
            if(voidChar){charToFindSize = charToFindSize + 1;}
            int charFinded = 0;
            int i = 0;
            while (charFinded == 0 && i < charToFindSize)
            {
                charFinded = str[j] == charToFind[i];
                i++;
            }
            if (charFinded)
            {
                bool = 1;
            }
            else
            {
                strReturn[j] = str[j];
            }
        }
        pointer++;
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
    //Este parametro necesita recibir -> METHOD/ <-
    char * method = GetSubstringUntil(str, "/", maxSizeMethod,0);
    if(method[0] == '\0'){
        printf("MetodoVacio\n");
    }
    return method;
}

char*extractQuery(char *str){

}
char*extractParam(char *str){
    //Este parametro necesita recibir -> /PARAM <-
    char* param = "";
    
    if (str[0] == '/')
    {
        str = &str[1];
        param = GetSubstringUntil(str,"",maxSizeParam,1);
    }
    if(param[0] == '\0'){
        printf("ParametroVacio\n");
    }
    return param;
}
char* extractPath (char* str){
    //Este metodo necesita recibir -> PATH/ O PATH O PATH? <- 
    char* path = GetSubstringUntil(str,"/?",maxSizePath,1);
    if(path[0] == '\0'){
        printf("PathVacio\n");
    }
    return path;
}
int llegoMetodo(char *url){
    char *method = extractMethod(url);
    url = &url[pointer];
    pointer = 0;
    printf("Metodo :%s \n",method);

    char *path = extractPath(url);
    printf("Path :%s \n",path);
    url = &url[pointer-1];
    pointer = 0;

    char *param = extractParam(url);
    printf("param :%s \n",param);
    url = &url[pointer];
    return 0;
}
int main(int argc, char const *argv[])
{
    char *url = "GET/USUARIO/123";
    //char *url = "GET/USUARIO?nombre=juan";
    printf("%s\n",url);
    llegoMetodo(url);
    return 0;
}