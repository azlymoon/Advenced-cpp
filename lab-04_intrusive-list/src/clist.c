#include "clist.h"
#include <assert.h>
#include <stdlib.h>

void init_list(struct intrusive_list* list) {
	list->head = NULL;
}

void add_node(struct intrusive_list* list, struct intrusive_node* node) {
	if (list->head == NULL) {
		list->head = node;
		node->prev = node;
		node->next = node;
	}
	else if (list->head->next == list->head) {
		list->head->next = node;
		list->head->prev = node;
		node->next = list->head;
		node->prev = list->head;
		list->head = node;
	}
	else {
		list->head->prev->next = node;
		node->prev = list->head->prev;
		list->head->prev = node;
		node->next = list->head;
		list->head = node;
	}
}

void remove_node(struct intrusive_list* list, struct intrusive_node* node) {
	size_t size_list = get_length(list);
	if (list->head == node) {
		list->head = node->next;
	}
	if (size_list == 1) {
		list->head = NULL;
	}
	else if (size_list == 2) {
		list->head->next = list->head;
		list->head->prev = list->head;
	}
	else {
		node->prev->next = node->next;
		node->next->prev = node->prev;
	}
}

int get_length(struct intrusive_list* list) {
	if (list->head == NULL) {
		return 0;
	}
	size_t size = 1;
	struct intrusive_node* cur_node = list->head;
	while (cur_node->next != list->head) {
		size++;
		cur_node = cur_node->next;
	}
	return size;
}