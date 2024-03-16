#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Item {
	char name[256];
	int value;
}Item;

typedef struct Node Node;

struct Node {
	Item data;
	Node* prev;
	Node* next;
};

Node* CreateNewNode(Item item) {
	Node* node = (Node*)malloc(sizeof(Node));

	if (node == NULL) {
		printf("Error creating node\n");
	}
	node->data = item;
	node->prev = NULL;
	node->next = NULL;
	return node;
}

void Push(Node** head, Item item) {
	Node* newNode = CreateNewNode(item);

	if (*head == NULL) {
		*head = newNode;
	}
	else {
		newNode->prev = *head;
		(*head)->prev = newNode;
		*head = newNode;
	}
}

Item Pop(Node** head) {
	Node* temp = *head;
	Item item = temp->data;
	*head = (*head)->next;

	if (*head != NULL) {
		(*head)->prev = NULL;
	}
	return item;
}

void AlphabeticalSort(Node** head) {
	Node* current;
	Node* i;
	Item temp;

	if (*head = NULL || (*head)->next == NULL) {
		return;
	}

	for (current = *head; current->next != NULL; current = current->next) {
		for (i = current->next; i != NULL; i = i->next) {
			if (strcmp(current->data.name, i->data.name) > 0) {
				temp = current->data;
				current->data = i->data;
				i->data = temp;
			}
		}
	}
}


size_t getline(char** lineptr, size_t* n, FILE* stream);

int main(int argc, char** argv) {
	FILE* f = fopen("data.csv", "r");

	if (f == NULL) {
		printf("Error opening file\n");
		return;
	}

	char* line = NULL;
	size_t len = 0;
	size_t read;

	while ((read = getline(&line, &len, f)) != -1) {
		char* context = NULL;
		char* token = strtok_s(line, ",", &context);
		int count = 0;

		Item Item;
		while (token != NULL) {
			if (count == 1) {
				strcpy_s(Item.name, sizeof(Item.name), token);
			}
			else if (count == 3) {
				Item.value = atoi(token);
				printf("Item name: %s \nPrice: %d\n", Item.name, Item.value);
			}
			token = strtok_s(NULL, ",", &context);
			count++;
		}

	}

	fclose(f);
	return 0;
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
