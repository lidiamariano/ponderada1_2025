#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORTA 12345
#define BUFFER_SIZE 1024

int main() {
    int socket_fd;
    struct sockaddr_in servidor;
    char buffer[BUFFER_SIZE];

    // Criar socket
    socket_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (socket_fd < 0) {
        perror("Erro ao criar socket");
        exit(EXIT_FAILURE);
    }

    servidor.sin_family = AF_INET;
    servidor.sin_port = htons(PORTA);
    servidor.sin_addr.s_addr = inet_addr("127.0.0.1"); // localhost

    // Conectar ao servidor
    if (connect(socket_fd, (struct sockaddr*)&servidor, sizeof(servidor)) < 0) {
        perror("Erro ao conectar");
        exit(EXIT_FAILURE);
    }

    // Abrir arquivo
    FILE *arquivo = fopen("mensagem.txt", "r");
    if (!arquivo) {
        perror("Erro ao abrir arquivo");
        exit(EXIT_FAILURE);
    }

    // Enviar conteúdo
    int bytes_lidos;
    while ((bytes_lidos = fread(buffer, sizeof(char), BUFFER_SIZE, arquivo)) > 0) {
        send(socket_fd, buffer, bytes_lidos, 0);
    }

    fclose(arquivo);
    close(socket_fd);

    printf("Arquivo enviado com sucesso.\n");
    return 0;
}
