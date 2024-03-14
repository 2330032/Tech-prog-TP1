#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Item {
	char name[256];
	int value;
}Item;

typedef struct Node Node;

struct Node {
	void* data;
	Node* prev;
	Node* next;
};

size_t getline(char** lineptr, size_t* n, FILE* stream);

int main(int argc, char** argv) {
	FILE* f = fopen("data.csv", "r");
	char* line = NULL;
	size_t len = 0;
	size_t read;

	getline(&line, &len, f);

	fclose(f);

	for (int i = 0; i < len; i++) {
		
	}
}

size_t getline(char** lineptr, size_t* n, FILE* stream) {
	char* bufptr = NULL;
	char* p = bufptr;
	size_t size;
	int c;

	if (lineptr == NULL) {
		return -1;
	}
	if (stream == NULL) {
		return -1;
	}
	if (n == NULL) {
		return -1;
	}
	bufptr = *lineptr;
	size = *n;

	c = fgetc(stream);
	if (c == EOF) {
		return -1;
	}
	if (bufptr == NULL) {
		bufptr = malloc(128);
		if (bufptr == NULL) {
			return -1;
		}
		size = 128;
	}
	p = bufptr;
	while (c != EOF) {
		if ((p - bufptr) > (size - 1)) {
			size = size + 128;
			bufptr = realloc(bufptr, size);
			if (bufptr == NULL) {
				return -1;
			}
		}
		*p++ = c;
		if (c == '\n') {
			break;
		}
		c = fgetc(stream);
	}

	*p++ = '\0';
	*lineptr = bufptr;
	*n = size;

	return p - bufptr - 1;
}
