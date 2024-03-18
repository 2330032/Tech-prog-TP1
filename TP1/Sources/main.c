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

size_t getline(char** lineptr, size_t* n, FILE* stream);

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
		newNode->next = *head;
		(*head)->prev = newNode;
		*head = newNode;
	}
	printf("Item added to inventory.");
}

Item Pop(Node** head) {
	Node* temp = *head;
	Item item = temp->data;
	*head = (*head)->next;

	if (*head != NULL) {
		(*head)->prev = NULL;
	}
	printf("Item deleted to inventory.");
	return item;
}

void AlphabeticalSort(Node** head) {
	Node* current;
	Node* i;
	Item temp;

	if (*head == NULL || (*head)->next == NULL) {
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

Item* FindItemByPosition(Node* head, int position)
{
	Node* current = head;
	int i = 0;

	while (current != NULL && i < position)
	{
		current = current->next;
		i++;
	}
	if (i == position && current != NULL)
	{
		return &(current->data);
	}
	else
	{
		return NULL;
	}
}

Item* FindItemByName(Node* head, const char* name)
{
	Node* current = head;

	while (current != NULL)
	{
		if (strcmp(current->data.name, name) == 0)
		{
			return &(current->data);
		}
		current = current->next;
	}
	return NULL;
}

int ItemQuantity(Node* head)
{
	int i = 0;
	Node* current = head;

	while (current != NULL)
	{
		i++;
		current = current->next;
	}
	return i;
}

void AddRandomItem(Node** head, const char* file)
{
	FILE* f = fopen(file, "r");

	if (f == NULL) {
		printf("Error opening file\n");
		return;
	}

	int line_count = 0;
	char* line = NULL;
	size_t len = 0;
	size_t read;

	while ((read = getline(&line, &len, f)) != -1) {
		line_count++;
	}
	rewind(f);

	srand(time(NULL));
	int random_line = rand() % line_count;

	for (int i = 0; i < random_line; i++) {
		getline(&line, &len, f);
	}
	while ((read = getline(&line, &len, f)) != -1) {
		char* context = NULL;
		char* token = strtok_s(line, ",", &context);
		int i = 0;

		Item Item;
		while (token != NULL) {
			if (i == 1) {
				strcpy_s(Item.name, sizeof(Item.name), token);
			}
			else if (i == 3) {
				Item.value = atoi(token);
				printf("*Added random item*\nItem name: %s \nItem price: %d\n", Item.name, Item.value);
			}
			token = strtok_s(NULL, ",", &context);
			i++;
		}
	}
	fclose(f);
}

void PrintInventory(Node* head)
{
	Node* current = head;

	printf("Here is your current inventory: \n\n");

	while (current != NULL)
	{
		printf("Item name: %s\nItem value: %d\n\n", current->data.name, current->data.value);
		current = current->next;
	}
}


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
		int i = 0;

		Item Item;
		while (token != NULL) {
			if (i == 1) {
				strcpy_s(Item.name, sizeof(Item.name), token);
			}
			else if (i == 3) {
				Item.value = atoi(token);
			}
			token = strtok_s(NULL, ",", &context);
			i++;
		}

	}
	fclose(f);

	int choice;

	printf("Welcome! \n\nWhat would you like to do?\n\nChoose from the following options:\n\n");
	printf("[1] - See inventory\n[2] - Add to inventory\n[3] - Delete item from inventory\n[4] - Sort inventory\n[5] - Find item by position\n[6] - Find item by name\n[7] - See total number of items in inventory\n[8] - Exit");
	printf("\nChoice:");
	scanf("%d", &choice);


	while (choice != 8) {

		if (choice == 1) {

			PrintInventory();
		}
		else if (choice == 2) {
			Push();
		}
		else if (choice == 3) {
			Pop();
		}
		else if (choice == 4) {
			printf("Would you like to sort items [1] by name or [2] by value?\n\n ");
			scanf("%d", &choice);

			if (choice == 1) {
				AlphabeticalSort();
			}
			else if (choice == 2) {

			}
		}
		else if (choice == 5) {
			FindItemByPosition();
		}
		else if (choice == 6) {
			FindItemByName();
		}
		else if (choice == 7) {
			ItemQuantity();
		}
	}
	printf("Goodbye!");
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
