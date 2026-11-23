#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char** delimiter(char *string, char DELIM);

int main() {

        char **vector;
        char buffer[1001];
        int counter = 0;

        do {
                counter = 0;
                printf(">");
                fgets(buffer, 1000, stdin);
                vector = delimiter(buffer, ' ');
                while (vector[counter] != NULL) {
                        printf("%s\n", vector[counter]);
                        counter++;
                }
        } while (strcmp(vector[0], "exit") != 0);
        printf("Program exited, have a nice day\n");

        return 0;
}

char** delimiter(char *string, char DELIM) {

        if (strlen(string) == 0) {
                return NULL;
        }
        //care about 2D array dynamic sizing later
        char **returner;
        returner = malloc(sizeof(char *) * 10);
        int argc = 0;
        int substrStartMarker = 0;
        int substrlen = 1;
        for (int i = 0; i < strlen(string); i++) {
                if (string[i] == DELIM) {
                        *(returner + argc) = strndup(string + substrStartMarker, substrlen - 1);
                        substrStartMarker = i + 1;
                        substrlen = 1;
                        argc++;
                } else {
                        substrlen++;
                }
        }
        *(returner + argc) = strndup(string + substrStartMarker, substrlen - 2);
        returner[argc + 1] = NULL;
        return returner;
}
