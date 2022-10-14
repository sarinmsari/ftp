#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <unistd.h>
int main(){
    FILE *fp;
    int sd, newsd,ser,n,cli,pid,bd,port;
    char name[100],fileread[100],fname[100],ch,file[100],rcv[100];
    struct sockaddr_in server,client;
    printf("\nEnter the port address\n");
    scanf("%d",&port);
    sd=socket(AF_INET,SOCK_STREAM,0);
    if(sd<0){
        printf("Error in socket creation");
    }
    server.sin_family=AF_INET;
    server.sin_addr.s_addr=htonl(INADDR_ANY);
    server.sin_port=htons(port);
    bd=bind(sd,(struct sockaddr*)&server,sizeof(server));
    if(bd<0){
        printf("can't bind");
    }
    listen(bd,5);
    newsd=accept(sd,(struct sockaddr*)&client,sizeof(client));
    if(newsd<0){
        printf("can't accept");
    }
    n=recv(newsd,rcv,100,0);
    rcv[n]='\0';
    fp=fopen(rcv,"r");
    if(fp==NULL){
        send(newsd,"error",5,0);
        close(newsd);
    }else{
        while(fgets(fileread,sizeof(fileread),fp)){
            if(send(newsd,fileread,sizeof(fileread),0)<0){
                printf("can't send file contents\n");
            }
            sleep(1);
        }
        if(!fgets(fileread,sizeof(fileread),fp)){
            send(newsd,"completed",999999999,0);
        }
    }
}