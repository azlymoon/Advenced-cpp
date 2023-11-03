#include "point_list.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

void add_point(struct intrusive_list* list, int x, int y) {
    struct point* new_point = (struct point*)malloc(sizeof(struct point));
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
            if (list->head != NULL) {
                cur_node = list->head->next;
            }
        }
        else {
            cur_node = cur_node->next;
        }
    }
}

void write_all_points_txt_file(struct intrusive_list* list, char* path) {
    FILE* out = fopen(path, "w");
    int size_list = (int)get_length(list);
    if (size_list == 0)
        return;
    struct intrusive_node* cur_node = list->head->prev;
    struct point* cur_point;
    for (int i = 0; i < size_list; i++) {
        cur_point = container_of(cur_node, struct point, node);
        fprintf(out, "%d %d\n", cur_point->x, cur_point->y);
        cur_node = cur_node->prev;
    }
    fclose(out);
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

void read_txt_file(struct intrusive_list* list, char* path) {
    FILE* in = fopen(path, "r");
    int x, y;
    while (fscanf(in, "%d %d", &x, &y) != EOF) {
        add_point(list, x, y);
        if (ferror(in)) {
            printf("Error read file");
            exit(1);
        }
    }
    fclose(in);
}

void print(struct intrusive_node* cur_node, void* data) {
    char* format = (char*)data;
    struct point* cur_point = container_of(cur_node, struct point, node);
    printf(format, cur_point->x, cur_point->y);
}

void count(struct intrusive_node* cur_node, void* data) {
    int* size_list = (int*)data;
    if (cur_node != NULL) {
        *size_list += 1;
    }
}

int transform(unsigned char* bin) {
    int param = ((unsigned int)bin[0]) | (((unsigned int)bin[1]) << 8) | (((unsigned int)bin[2]) << 16);
    if (param & (1 << 23)) {
        param -= 1;
        param ^= 16777215;
        param *= -1;
    }
    return param;
}

void read_bin_file(struct intrusive_list* list, char* path) {
    FILE* in = fopen(path, "rb");
    int x, y;
    unsigned char* tmp_arr = malloc(sizeof(unsigned char) * 3);
    assert(tmp_arr);
    while (fread(tmp_arr, 3, 1, in)) {
        x = transform(tmp_arr);
        fread(tmp_arr, 3, 1, in);
        y = transform(tmp_arr);
        add_point(list, x, y);

        if (ferror(in)) {
            printf("Error read file");
            exit(1);
        }
    }
    free(tmp_arr);
    fclose(in);
}


void write_all_points_bin_file(struct intrusive_list* list, char* path) {
    FILE* out = fopen(path, "wb");
    int size_list = (int)get_length(list);
    if (size_list == 0)
        return;
    struct intrusive_node* cur_node = list->head->prev;
    struct point* cur_point;
    int* tmp_arr = malloc(sizeof(int));
    assert(tmp_arr);
    for (int i = 0; i < size_list; i++) {
        cur_point = container_of(cur_node, struct point, node);
        tmp_arr[0] = cur_point->x;
        fwrite(tmp_arr, 3, 1, out);
        tmp_arr[0] = cur_point->y;
        fwrite(tmp_arr, 3, 1, out);
        cur_node = cur_node->prev;
    }
    free(tmp_arr);
    fclose(out);
}

