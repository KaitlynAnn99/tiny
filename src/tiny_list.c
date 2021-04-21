/*!
 * @file
 * @brief
 */

#include <stddef.h>
#include "tiny_list.h"
#include "tiny_utils.h"

typedef struct {
  tiny_list_node_t* previous;
  tiny_list_node_t* current;
  uint16_t index;
} info_t;

static void find_node_info(tiny_list_t* self, tiny_list_node_t* target, info_t* info)
{
  info->current = &self->head;
  info->index = 0;

  tiny_list_for_each(self, tiny_list_node_t, node, {
    info->previous = info->current;
    info->current = node;

    if(node == target) {
      break;
    }

    info->index++;
  });
}

extern inline void tiny_list_init(tiny_list_t* self);

uint16_t tiny_list_count(tiny_list_t* self)
{
  tiny_list_node_t* current = self->head.next;
  uint16_t count = 0;

  while(current != &self->head) {
    count++;
    current = current->next;
  }

  return count;
}

extern inline void tiny_list_push_front(tiny_list_t* self, tiny_list_node_t* node);

void tiny_list_push_back(tiny_list_t* self, tiny_list_node_t* node)
{
  info_t info;
  find_node_info(self, &self->head, &info);
  info.current->next = node;
  node->next = &self->head;
}

extern inline tiny_list_node_t* tiny_list_pop_front(tiny_list_t* self);

tiny_list_node_t* tiny_list_pop_back(tiny_list_t* self)
{
  info_t info;
  find_node_info(self, &self->head, &info);
  info.previous->next = info.current->next;
  return info.current;
}

void tiny_list_remove(tiny_list_t* self, tiny_list_node_t* node)
{
  info_t info;
  find_node_info(self, node, &info);

  if(info.current == node) {
    info.previous->next = node->next;
  }
}

bool tiny_list_contains(tiny_list_t* self, tiny_list_node_t* node)
{
  info_t info;
  find_node_info(self, node, &info);
  return info.current == node;
}

uint16_t tiny_list_index_of(tiny_list_t* self, tiny_list_node_t* node)
{
  info_t info;
  find_node_info(self, node, &info);
  return info.index;
}

extern inline void tiny_list_iterator_init(tiny_list_iterator_t* self, tiny_list_t* list);

extern inline tiny_list_node_t* tiny_list_iterator_next(tiny_list_iterator_t* self, tiny_list_t* list);
