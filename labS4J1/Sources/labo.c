#include <stdint.h>
#include <assert.h>
#include "labo.h"



Stack* new_stack(size_t max_size)
{
	Stack* newStack = allocate(sizeof(Stack));
	newStack->max_size = max_size;
	newStack->top = -1;
	newStack->data = (void**)allocate(sizeof(void*) * max_size);
	return newStack;
}

void push(Stack* s, void* newData)
{
	if (s->top + 1 < s->max_size ) {
		s->top += 1;
		s->data[s->top] = newData;
	}
	else {
		printf("Stack overflows\n");
	}
}

void* pop(Stack* s)
{
	if (s->top == -1) {
		return NULL;
	}
	else {
		return s->data[(s->top)--];
	}
}

void* peek(Stack* s)
{
	if (s->top == -1) {
		return NULL;
	}
	else {
		return s->data[s->top];
	}
}

void reverseStack(Stack* s){
	if (s->top == -1) {
		return;
	}
	else {
		int start = 0;
		int end = s->top;
		while (start < end) {
		Person* temp = s->data[start];
		s->data[start] = s->data[end];
		s->data[end] = temp;
		start++;
		end--;
		}
	}
}

void sortStack(Stack* s)
{
	Stack* tempStack = new_stack(s->max_size);
	Person* personne1 = NULL;
	Person* personne2 = NULL;
	if (s->top != -1) {
		while (s->top > 0) {
			personne1 = (Person*)pop(s);
			personne2 = (Person*)pop(s);
			if (personne1->age < personne2->age) {
				push(tempStack, personne1);
				push(s, personne2);
			}
			else {
				push(tempStack, personne2);
				push(s, personne1);
			}
		}
		while (tempStack->top != -1) {
			if (tempStack->top == 0) {
				push(s, pop(tempStack));
				return;
			}
			personne1 = pop(tempStack);
			personne2 = pop(tempStack);
			if (personne1->age > personne2->age) {
				push(s, personne1);
				push(tempStack, personne2);
			}
			else {
				push(s, personne2);
				push(tempStack, personne1);
			}
		}
	}
}
