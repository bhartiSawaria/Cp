#include <stdio.h>
#include <stdlib.h>

typedef struct node {
	int data;
	struct node *ptr;
}node;

node *createLinkedList(int n) {
	node *start;
	start = (node *)malloc(sizeof(node));
	scanf("%d", &(start->data));
	node *curr;
	curr = start;
	int i;
	for (i=0; i<n-1; i++) {
		curr->ptr = (node *)malloc(sizeof(node));
		curr = curr->ptr; 
		scanf("%d", &(curr->data));
	}
	curr->ptr = NULL;
	return start;
}

displayLinkedList(node *start) {
	node *temp;
	temp = start;
	while (temp != NULL) {
		printf("%d ", (temp->data));
		temp = temp->ptr;
	}
	printf("\n");
}

void insertAfterInLinkedList(node *start, int val, int newval) {
	node *temp, *newnode;
	temp = start;
	while (temp != NULL && temp->data != val) {
		temp = temp->ptr;
	}	
	if (temp == NULL)  {
		printf("Value not found in Linked List\n");
	} else {
		newnode = (node *)malloc(sizeof(node));
		newnode->data = newval;
		newnode->ptr = temp->ptr;
		temp->ptr = newnode; 	
	}
}

node *insertBeforeInLinkedList(node *start, int val, int newval) {
	node *temp, *prev, *newnode;
	temp = start;
	prev = NULL;
	while (temp!=NULL && temp->data != val) {
		prev = temp;
		temp = temp->ptr;
	}
	if (temp == NULL) {
		printf("Value not found in Linked List\n");
	} else if (prev != NULL){
		newnode = (node *)malloc(sizeof(node));
		newnode->data = newval;
		newnode->ptr = prev->ptr;
		prev->ptr = newnode; 
	} else {
		newnode = (node *)malloc(sizeof(node));
		newnode->data = newval;
		newnode->ptr = start;
		start = newnode;
	}
	return start;
}

insertOnPosition(node *start, int pos, int newval) {
}

int main() {
	printf("Enter the length of the array: ");
	int length;
	scanf("%d", &length);
	node *head;
	head = createLinkedList(length);
	displayLinkedList(head);
	head = insertBeforeInLinkedList(head, 6, 102);


	displayLinkedList(head);
	return 0;
}
