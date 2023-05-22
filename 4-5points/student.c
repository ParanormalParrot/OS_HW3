#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#define ARRAY_SIZE 1000
int student_number;
int client_socket;

void exit_program() {
    printf("\nClose socket and exit program\n");
    close(client_socket);
    exit(0);
}

int main(int argc, char *argv[]) {
    if (argc != 4) {
        printf("Запускайте так: %s <Server IP Address> <Server Port><student_number>\n", argv[0]);
        exit_program();
    }
    struct sockaddr_in server_addr;
    if ((client_socket = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("Ошибка при создании сокета");
        exit(1);
    }
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(atoi(argv[2]));
    inet_pton(AF_INET, argv[1], &server_addr.sin_addr);
    student_number = atoi(argv[3]);
    if (connect(client_socket, (struct sockaddr *) &server_addr, sizeof(server_addr)) < 0) {
        perror("Ошибка соединения");
        exit_program();
    }
    sleep(1);
    while (1) {
        int n, k, row_index;
        if (recv(client_socket, &n, sizeof(n), 0) < 0) {
            perror("Recv failed");
            exit(1);
        }
        if (n == -1) {
            break;
        }
        if (recv(client_socket, &k, sizeof(k), 0) < 0) {
            perror("Recv failed");
            exit(1);
        }
        if (recv(client_socket, &row_index, sizeof(k), 0) < 0) {
            perror("Recv failed");
            exit(1);
        }

        int row[n * k];
        if (recv(client_socket, row, n * k * sizeof(int), 0) < 0) {
            perror("Recv failed");
            exit(1);
        }

        // Сортировка выбором
        for (int j = 0; j < n * k - 1; ++j) {
            int min = j;
            for (int l = j + 1; l < n * k; ++l) {
                if (row[l] < row[min]) {
                    min = l;
                }
            }
            int tmp = row[j];
            row[j] = row[min];
            row[min] = tmp;
            printf("Student %d have inserted book %d at the position %d of the bookshelf %d in a row %d. \n",
                   student_number,
                   row[j],
                   (j % k + 1), (j / n + 1), row_index + 1);
            usleep(rand() % 10);
        }
        if (send(client_socket, row, n * k * sizeof(int), 0) < 0) {
            perror("Send failed");
            exit(1);
        }
        printf("Student %d have finished sorting subcatalogue for row %d and passed it to the librarian.\n",
               student_number, row_index + 1);
    }

    close(client_socket);
    return 0;
}
