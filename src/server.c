#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORTA 12345
#define BUFFER_SIZE 1024

int main() {
    int servidor_fd, novo_socket;
    struct sockaddr_in endereco;
    socklen_t addrlen = sizeof(endereco);
    char buffer[BUFFER_SIZE] = {0};

    // Criar socket
    servidor_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (servidor_fd == -1) {
        perror("Erro ao criar socket");
        exit(EXIT_FAILURE);
    }

    endereco.sin_family = AF_INET;
    endereco.sin_addr.s_addr = INADDR_ANY;
    endereco.sin_port = htons(PORTA);

    // Associar o socket à porta
    bind(servidor_fd, (struct sockaddr*)&endereco, sizeof(endereco));

    // Esperar conexões
    listen(servidor_fd, 1);
    printf("Aguardando conexão...\n");

    novo_socket = accept(servidor_fd, (struct sockaddr*)&endereco, &addrlen);
    if (novo_socket < 0) {
        perror("Erro ao aceitar conexão");
        exit(EXIT_FAILURE);
    }

    // Ler dados do socket e imprimir
    int bytes_lidos;
    while ((bytes_lidos = read(novo_socket, buffer, BUFFER_SIZE)) > 0) {
        fwrite(buffer, sizeof(char), bytes_lidos, stdout);
    }

    printf("\nConexão encerrada.\n");

    close(novo_socket);
    close(servidor_fd);
    return 0;
}

