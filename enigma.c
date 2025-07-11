#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define SIZE 96

void decode(void);
void encode(void);

char arr[] = {' ', '0', '1', '2', '3', '4', '5', '6',
              '7', '8', '9', '`', '~', '!', '@', '#', '$', '%', '^', '&',
              '*', '(', ')', '-', '_', '=', '+', '|', '\\', ',', '.', '<',
              '>', '?', '/', '\'', '"', ';', ':', '[', ']', '{', '}', '\n',
              'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L',
              'M', 'N', 'O', 'U', 'P', 'Q', 'R', 'S', 'T', 'V', 'W', 'X',
              'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j',
              'k', 'l', 'm', 'n', 'o', 'u', 'p', 'q', 'r', 's', 't', 'v',
              'w', 'x', 'y', 'z'};

int *get_digits(int kcode) {
    srand((unsigned) kcode);
    int *res = (int*)malloc(sizeof(int) * SIZE);
    for (int i = 0; i < SIZE; i++) {
        res[i] = rand();
    }
    return res;
}

char get_char(int *digits, int value) {
    char c = '\t';
    for (int i = 0 ; i < SIZE; i++) {
        if (value == digits[i]) {
            c = arr[i];
            break;
        }
    }
    return c;
}

int get_code(int *digits, char c) {
    int r = -1;
    for (int i = 0; i < SIZE; i++) {
        if (c == arr[i]) {
            r = digits[i];
            break;
        }
    }
    return r;
}

void decode(void) {
    while (true) {
        printf("Provide encoded file:\n");
        char filename[100];
        if (!fgets(filename, 100, stdin)) {
            perror("Shutting down");
            exit(2);
        }
        filename[strcspn(filename, "\n")] = '\0';
        FILE *f = fopen(filename, "r");
        if (!f) {
            perror("Can't open file");
            continue;
        }

        printf("Provide keycode for %s:\n", filename);
        char key[10];
        if (!fgets(key, 10, stdin)) {
            perror("Shutting down");
            exit(3);
        }
        int kcode = atoi(key);
        int *digits = get_digits(kcode);

        char *decoded = (char*) malloc(sizeof(char) * 1024);
        int dsize = 1024, dlen = 0;
        char line[100];

        while (fgets(line, 100, f)) {
            int value = atoi(line);
            char c = get_char(digits, value);
            if (c == '\t') {
                fprintf(stderr, "Invalid code %d in file — bad key?\n", value);
                exit(4);
            }
            decoded[dlen++] = c;
            if (dlen == dsize) {
                dsize *= 2;
                decoded = realloc(decoded, dsize);
                if (!decoded) {
                    perror("Memory allocation error");
                    exit(5);
                }
            }
        }

        decoded[dlen] = '\0';
        printf("Read %s\n", filename);
        printf("Decoded Content:\n%s\n", decoded);
        free(decoded);
        break;
    }
}

void fencode(int *digits) {
    while (true) {
        printf("Provide input filename:\n");
        char filename[100];
        if (!fgets(filename, 100, stdin)) {
            perror("Shutting down");
            exit(8);
        }
        filename[strcspn(filename, "\n")] = '\0';
        FILE *file = fopen(filename, "r");
        if (!file) {
            perror("Cannot open file");
            continue;
        }

        printf("Provide output filename:\n");
        char outfile[100];
        if (!fgets(outfile, 100, stdin)) {
            perror("Shutting down");
            exit(9);
        }
        outfile[strcspn(outfile, "\n")] = '\0';
        FILE *ofile = fopen(outfile, "w");
        if (!ofile) {
            perror("Cannot write output file");
            exit(13);
        }

        int next;
        while ((next = fgetc(file)) != EOF) {
            char c = (char)next;
            int code = get_code(digits, c);
            if (code == -1) {
                fprintf(stderr, "Unsupported character: %c\n", c);
                exit(10);
            }
            fprintf(ofile, "%d\n", code);
        }

        fclose(ofile);
        fclose(file);
        printf("Encoding complete\n");
        break;
    }
}

void sencode(int *digits) {
    printf("Enter message to encode:\n");
    char message[1024];
    if (!fgets(message, sizeof(message), stdin)) {
        perror("Error reading message");
        exit(11);
    }

    size_t len = strlen(message);
    if (message[len - 1] == '\n') message[len - 1] = '\0';

    printf("Encoded output:\n");
    for (size_t i = 0; i < strlen(message); i++) {
        int code = get_code(digits, message[i]);
        if (code == -1) {
            fprintf(stderr, "Character '%c' not supported\n", message[i]);
            exit(12);
        }
        printf("%d\n", code);
    }
}

void encode(void) {
    while (true) {
        printf("(1) Provide file to encode\n");
        printf("(2) Write a message to encode\n");

        char response[4];
        if (!fgets(response, 4, stdin)) {
            perror("Shutting down");
            exit(6);
        }
        response[strcspn(response, "\n")] = '\0';

        printf("Provide keycode digits:\n");
        char key[10];
        if (!fgets(key, 10, stdin)) {
            perror("Shutting down");
            exit(3);
        }
        int kcode = atoi(key);
        int *digits = get_digits(kcode);

        if (!strcmp(response, "1")) {
            fencode(digits);
        } else if (!strcmp(response, "2")) {
            sencode(digits);
        } else {
            fprintf(stderr, "Invalid option\n");
            continue;
        }
        break;
    }
}

int main(int argc, char **argv) {
    while (true) {
        printf("Please select mode:\n");
        printf("(D)ecode\n");
        printf("(E)ncode\n");
        printf("(Q)uit\n");
        char buf[4];
        if (!fgets(buf, sizeof(buf), stdin)) {
            perror("Shutting down");
            return 1;
        }
        if (buf[0] == 'D' || buf[0] == 'd') decode();
        else if (buf[0] == 'E' || buf[0] == 'e') encode();
        else if (buf[0] == 'Q' || buf[0] == 'q') break;
        else printf("Invalid selection\n");
    }
    return 0;
}
