#define _GNU_SOURCE  // usleep
#include <string.h>
#include <stdbool.h>
#include <time.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <arpa/inet.h> // inet_addr

#define SERVER_HOST "127.0.0.1"
#define SERVER_PORT 8080
#define CLIENT_PORT 8081

int main(void)
{
    int sock_fd;

    struct sockaddr_in client, server;

    sock_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (sock_fd < 0)
    {
        perror("ERROR opening socket");
        exit(EXIT_FAILURE);
    }

    memset((char*)&client, '\0', sizeof(client));
    memset((char*)&server, '\0', sizeof(server));

    client.sin_family = AF_INET;
    client.sin_addr.s_addr = htonl(INADDR_ANY);
    client.sin_port = htons(CLIENT_PORT);

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = inet_addr(SERVER_HOST);
    server.sin_port = htons(SERVER_PORT);

    bind(sock_fd, (struct sockaddr *) &client, sizeof(client));
    int con = connect(sock_fd, (struct sockaddr *) &server, sizeof(server));
    if(con < 0)
    {
        perror("connect failed");
        exit(EXIT_FAILURE);
    }

    srand(time(NULL));
    int min = 500000, max = 999999;
    int n = 0;
    char type_of_client[2] = "w\n";  // отправляем тип клиента писатель
    while(true)
    {
        int time_i = min + rand() % (max - min + 1); // interval
        n = send(sock_fd, &type_of_client, sizeof(type_of_client), 0); // или MSG_NOSIGNAL
        printf("Запрос на запись буквы отправлен\n");
        fflush(stdout);
        if(n < 0) break;
        usleep(time_i); // udelay() #include <linux/delay.h>
    }
    if(n < 0)
    {
        perror("send failed");
        // exit(EXIT_FAILURE);
    }

    close(sock_fd);

    return 0;
}