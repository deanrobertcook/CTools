#ifndef DLLIST_H
#define DLLIST_H

#include <stdlib.h>
#include "src/utils/utils.h"

typedef struct item_s {
  char* data; 
} item_t, *item_p_t;
 
typedef struct node_s {
  struct node_s* next;
  struct node_s* previous;
  item_p_t item;
} node_t, *node_p_t;

typedef node_t list_t, *list_p_t;

list_p_t DLLIST_create_list(void);

list_p_t DLLIST_append_item(list_p_t list, size_t index, item_p_t item);

item_p_t DLLIST_remove_item(list_p_t list, int index);

size_t DLLIST_length(list_p_t list);

item_p_t DLLIST_get_item(list_p_t list, int index);

list_p_t DLLIST_destroy_list(list_p_t list);

#endif
