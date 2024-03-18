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
}

Item Pop(Node** head) {
	Node* temp = *head;
	Item item = temp->data;
	*head = (*head)->next;

	if (*head != NULL) {
		(*head)->prev = NULL;
	}
	printf("Item deleted from inventory.");
	return item;
}

void SortByName(Node** head) {
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

void SortByValue(Node** head)
{
	Node* current;
	Node* i;
	Item temp;

	if (*head == NULL || (*head)->next == NULL)
	{
		return;
	}
	for (current = *head; current->next != NULL; current = current->next)
	{
		for (i = current->next; i != NULL; i = i->next)
		{
			if (current->data.value > i->data.value)
			{
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

void DeleteItemByName(Node** head, const char* name)
{
	if (name == NULL)
	{
		printf("Item not found. Make sure item name is valid.\n");
		return;
	}
	Node* current = *head;

	while (current != NULL)
	{
		if (strcmp(current->data.name, name) == 0)
		{
			Pop(head);
			printf("Item named %s  was deleted from inventory.", name);
			return;
		}
		current = current->next;
	}
	printf("No item by the name %s was found in inventory.", name);
	return;
}

void DeleteItemByPosition(Node** head, int position)
{
	if (position == NULL)
	{
		printf("Item not found. Make sure position is valid.");
		return;
	}

	Node* foundItem = FindItemByPosition(*head, position);
	if (foundItem != NULL)
	{
		Pop(head);
		printf("Item at position %d was successfully deleted from inventory.", position);
	}
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
			}
			token = strtok_s(NULL, ",", &context);
			i++;
		}
		printf("\n\nAdded random item to inventory\nItem name: %s \nItem price: %d\n", Item.name, Item.value);
		Push(head, Item);
	}
	fclose(f);
}

void PrintInventory(Node* head)
{
	Node* current = head;

	printf("\n\nHere is your current inventory: \n\n");

	while (current != NULL)
	{
		printf("Item name: %s\nItem value: %d\n\n", current->data.name, current->data.value);
		current = current->next;
	}
}


int main(int argc, char** argv) {
	Node* head = NULL;

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
		Push(&head, Item);
	}
	fclose(f);


	int choice = NULL;
	printf("Welcome!");

	while (choice != 8) {

		printf("\n\nWhat would you like to do ? \n\nChoose from the following options : \n\n");
		printf("[1] - See inventory\n[2] - Add to inventory\n[3] - Delete item from inventory\n[4] - Sort inventory\n[5] - Find item by position\n[6] - Find item by name\n[7] - See total number of items in inventory\n[8] - Exit");
		printf("\n\nChoice: ");
		scanf("%d", &choice);


		if (choice == 1) {

			PrintInventory(head);
		}
		else if (choice == 2) {
			int subChoice;

			printf("\n\nWould you like to add [1] a specific item or [2] a random item?\n");
			printf("\n\nChoice: ");
			scanf("%d", &subChoice);

			if (subChoice == 1)
			{
				Item item;
				printf("\n\nEnter item name: ");
				scanf("%s", &item.name);
				printf("\nEnter item value: ");
				scanf("%d", &item.value);
				Push(&head, item);
			}
			else if (subChoice == 2)
			{
				AddRandomItem(&head, "data.csv");
			}
		}
		else if (choice == 3) {
			int subChoice;

			printf("\n\nWould you like to delete item [1] by name or [2] by position?\n\n ");
			printf("\n\nChoice: ");
			scanf("%d", &subChoice);

			if (subChoice == 1)
			{
				char name[256];
				printf("\nEnter item name to delete: ");
				scanf("%s", name);
				DeleteItemByName(&head, name);
			}
			if (subChoice == 2)
			{
				int position;
				printf("\nEnter position of item to delete: ");
				scanf("%d", &position);
				DeleteItemByPosition(&head, position);
			}
		}
		else if (choice == 4) {
			int subChoice;
			printf("\n\nWould you like to sort items [1] by name or [2] by value?\n\n ");
			printf("\n\nChoice: ");
			scanf("%d", &subChoice);

			if (subChoice == 1) {
				SortByName(&head);
			}
			else if (subChoice == 2) {
				SortByValue(&head);
			}
		}
		else if (choice == 5) {
			int position;
			printf("\n\nEnter desired item position: ");
			scanf("%d", &position);
			Item* foundItem = FindItemByPosition(head, position);
			if (foundItem != NULL) {
				printf("\nItem found at position %d:\nItem name: %s\nItem value: %d", position, foundItem->name, foundItem->value);
			}
			else {
				printf("\nNo item was found at position %d\n", position);
			}
		}
		else if (choice == 6) {
			char itemName[256];
			printf("\n\nEnter desired item name: ");
			scanf("%s", itemName);
			Item* foundItem = FindItemByName(head, itemName);
			if (foundItem != NULL) {
				printf("\nItem found:\nItem name: %s\nItem value: %d", foundItem->name, foundItem->value);
			}
			else {
				printf("\nNo item was found with name: %s\n", itemName);
			}

		}
		else if (choice == 7) {
			printf("\n\nThe total number of items currently in inventory is: %d\n", ItemQuantity(head));
		}
		else {
			printf("\n\nPlease choose a valid option from the list\n");
		}
	}
	printf("\n\nGoodbye!");
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
