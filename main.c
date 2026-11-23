#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

char** whitespaceDelimiter(char *string);

int main() {

	char **vector;
	char buffer[1001];
	int counter = 0;

	do {
		counter = 0;
		printf("> ");
		fgets(buffer, 1000, stdin);
		vector = whitespaceDelimiter(buffer);
		while (vector[counter] != NULL) {
			printf("%s\n", vector[counter]);
			counter++;
		}
		if (vector[0] != NULL && strcmp(vector[0], "clear") == 0) {
			printf("\033[2J\033[H");
		}
	} while (vector[0] == NULL || strcmp(vector[0], "exit") != 0);
	printf("Program exited, have a nice day\n");

	return 0;
}

char** whitespaceDelimiter(char *string) {

	if (strlen(string) == 0) {
		char ** returner = malloc(sizeof(char *));
		*returner = NULL;
		return returner;
	}
	//care about 2D array dynamic sizing later
	//returning vector
	char **returner;
	size_t capacity = 10;
	returner = malloc(sizeof(char *) * capacity);
	int argc = 0;

	//valid string tracking
	int substrStartMarker = 0;
	int substrlen = 1;

	//FSM states init
	int state = 0;

	#define START 0
	#define BLANK_STATE 1
	#define NON_BLANK_STATE 2
	#define END 3

	//iterative counter tracker
	int i = 0;
	int exitLoop = 0;

	while (1) {
		switch (state) {
			case START: 
				if (string[i] == '\0') {
					state = END;
				} else if (isspace(string[i])) {
					state = BLANK_STATE;
				} else {
					state = NON_BLANK_STATE;
					i++;
				}
			break;
			case BLANK_STATE:
				if (string[i] == '\0') {
					state = END;
				} else if (!isspace(string[i])) {
					state = NON_BLANK_STATE;
					substrStartMarker = i;
					substrlen = 1;
				}
				i++;

			break;
			case NON_BLANK_STATE:
				if (string[i] == '\0') {
					//realloc + 1 if needed here
					state = END;
					*(returner + argc) = strndup(string + substrStartMarker, substrlen);
					argc++;
				} else if (isspace(string[i])) {
					state = BLANK_STATE;
					//realloc here
					*(returner + argc) = strndup(string + substrStartMarker, substrlen);
					argc++;
				} else {
					substrlen++;
				}
				i++;
			break;
			case END:
				//realloc + 1 if needed here
				returner[argc] = NULL;
				exitLoop = 1;
			break;
		}
		if (exitLoop == 1) {
			break;
		}
	}
	return returner;
}
