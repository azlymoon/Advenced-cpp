#include "clist.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


struct point {
    int x, y;
    struct intrusive_node node;
};

void add_point(struct intrusive_list *list, int x, int y) {
    struct point *new_point = (struct point*)malloc(sizeof(struct point));
    assert(new_point);
    new_point->x = x;
    new_point->y = y;
    add_node(list, &new_point->node);
}

void remove_point(struct intrusive_list* list, int x, int y) {
    struct intrusive_node* cur_node = list->head;
    struct point* cur_point;
    size_t size_list = get_length(list);
    for (size_t i = 0; i < size_list; i++) {
        cur_point = container_of(cur_node, struct point, node);
        if (cur_point->x == x && cur_point->y == y) {
            remove_node(list, cur_node);
            free(cur_point);
            cur_node = list->head->next;
        }
        else {
            cur_node = cur_node->next;
        }
    }
}

void show_all_points(struct intrusive_list* list) {
    struct intrusive_node* cur_node = list->head;
    struct point* cur_point;
    size_t size_list = get_length(list);
    for (size_t i = 0; i < size_list - 1; i++) {
        cur_point = container_of(cur_node, struct point, node);
        printf("(%d %d) ", cur_point->x, cur_point->y);
        cur_node = cur_node->next;
    }
    cur_point = container_of(cur_node, struct point, node);
    printf("(%d %d)", cur_point->x, cur_point->y);
    cur_node = cur_node->next;
    printf("\n");
}

void remove_all_points(struct intrusive_list* list) {
    struct intrusive_node* cur_node;
    struct point* cur_point;
    size_t size_list = get_length(list);
    for (size_t i = 0; i < size_list; i++) {
        cur_node = list->head;
        cur_point = container_of(cur_node, struct point, node);
        remove_node(list, cur_node);
        free(cur_point);
    }
}

int main() {
    struct intrusive_list l;
    init_list(&l);
    char command[10];
    while (1) {
        scanf("%10s", command);
        if (strcmp(command, "add") == 0) {
            int x, y;
            scanf("%d %d", &x, &y);
            add_point(&l, x, y);
        }
        else if (strcmp(command, "rm") == 0) {
            int x, y;
            scanf("%d %d", &x, &y);
            remove_point(&l, x, y);
        }
        else if (strcmp(command, "print") == 0) {
            show_all_points(&l);
        }
        else if (strcmp(command, "rma") == 0) {
            remove_all_points(&l);
        }
        else if (strcmp(command, "len") == 0) {
            printf("%d\n", get_length(&l));
        }
        else if (strcmp(command, "exit") == 0) {
            exit(0);
        }
        else {
            printf("Unknown command\n");
        }
    }
    return 0;
}
