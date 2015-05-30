#include "dllist.h"

list_p_t DLLIST_create_list(void)
{
  list_p_t list = UTILS_NEW(list_t);
  list->next = list;
  list->previous = list;
  list->item = NULL;
  return list;
}

node_p_t traverse_forward(node_p_t currentNode, size_t distance) {
  for (size_t i = 0; i < distance; i++) {
    currentNode = currentNode->next;
  }
  return currentNode;
}

list_p_t DLLIST_append_item(list_p_t list, size_t index, item_p_t item)
{
  size_t listLength = DLLIST_length(list);
  if(index >= listLength) {
    index = listLength;
  }
  
  node_p_t nodeAtIndex = traverse_forward(list, index);
  node_p_t nodeBeforeIndex = nodeAtIndex->previous;
  
  node_p_t newNode = UTILS_NEW(node_t);
  newNode->next = nodeAtIndex;
  newNode->previous = nodeBeforeIndex;
  newNode->item = item;

  nodeAtIndex->previous = newNode;
  nodeBeforeIndex->next = newNode;
  
  return list;  
}

item_p_t DLLIST_remove_item(list_p_t list, int index)
{
  if(index > DLLIST_length(list) - 1) {
    printf("The specified index lies outside of the list\n");
  } else {
    node_p_t nodeAtIndex = traverse_forward(list, index);
    node_p_t nodeBeforeIndex = nodeAtIndex->previous;
    node_p_t nodeAfterIndex = nodeAtIndex->next;

    nodeBeforeIndex->next = nodeAfterIndex;
    nodeAfterIndex->previous = nodeBeforeIndex;

    nodeAtIndex = DLLIST_destroy_list(nodeAtIndex);
  }
  return list;  

}

size_t DLLIST_length(list_p_t list)
{
  size_t size = 0;
  node_p_t currentNode = list;
  while (currentNode->next != list) {
    size++;
    currentNode = currentNode->next;
  }
  return size;
}

item_p_t DLLIST_get_item(list_p_t list, int index)
{
  if(index > DLLIST_length(list) - 1) {
    printf("The specified index lies outside of the list\n");
    return NULL;
  } else {
    node_p_t nodeAtIndex = traverse_forward(list, index);
    return nodeAtIndex->item;
  }
}

list_p_t DLLIST_destroy_list(list_p_t list)
{
  list = UTILS_free(list);
  list = NULL;
  return list;
}
