#pragma once
#include "clist.h"

struct point {
    int x, y;
    struct intrusive_node node;
};

void add_point(struct intrusive_list* list, int x, int y);
void remove_point(struct intrusive_list* list, int x, int y);
void write_all_points_txt_file(struct intrusive_list* list, char* path);
void write_all_points_bin_file(struct intrusive_list* list, char* path);
void remove_all_points(struct intrusive_list* list);
void read_txt_file(struct intrusive_list* list, char* path);
void read_bin_file(struct intrusive_list* list, char* path);
void print(struct intrusive_node* node, void* data);
void count(struct intrusive_node* cur_node, void* data);