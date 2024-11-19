//Structs que definen el formato/protocolo de comunicacion
typedef struct{
  char method[10];
  char url[100];
}HttpRequest

typedef struct{
  int status_code;
  char body[4096];
}HttpResponse

int main(int argc, char *argv[]){
  int sockfd, connectionfd;//file descriptors para socket local y socket de conexion con el cliente
  struct sockaddr_in infoSocketServ, infoSocketClient;//Esta estructura  define puerto,ipv4
  //struct o buffer emision recepcion
  //Se crea el socket
  sockfd=socket(AF_INET,SOCK_STREAM,0); //sock_stream --> TCP
  if(sockfd ==-1){
    printf("Error al crear el socket\n");
  }else{
    printf("Socket creado\n");
  }
  //Limpiamos estructura del socket
  
  //Rellenamos la estructura del socket
  infoSocketServ.sin_family=AF_INET;//Asigna familia de direcciones
  infoSocketServ.sin_addr.s_addr=INADDR_ANY;// INADDR para que el sistema operativo asigne al servidor la ip local
  infoSocketServ.sin_port=htons(puerto);//Asigna puerto, htons le da el formato necesario
  
  //Bind asigna direccion ip y puerto al socket
  if(bind(sockfd, (struct sockaddr *) &infoSocketServ, sizeof(infoSocketServ) ) < 0)
    error("Error bind");
  
  //Servidor comienza a escuchar, permite conexiones
  listen(sockfd,1);
  tamanio=sizeof(infoSocketClient);
  while(1){
    connectionfd=accept(sockfd, (struct sockaddr *) &infoSocketClient, &tamanio);
    if(connectionfd<0){
      perror("Error de conexion");
    }else{
      do{
        //Recibimos la solicitud del cliente
        longitud=read(connectionfd,(struct HttpRequest *) &req, sizeof(HttpRequest));
        //Aca deberia interpretar la peticion y devolver lo que solicita el cliente
      }while()
    }
  }
}
