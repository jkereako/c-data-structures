#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef struct item {
  int value;
  struct item *next_item;
} Item;

Item * init_list(Item *);
Item * append_item(Item *, Item *);
Item * prepend_item(Item *, Item *);
Item * allocate_item(void);
Item * insert_item(Item *, Item *, int);
Item * find_item(Item *, int);

Item * init_list(Item *list) {
  assert(list != NULL);

  list->next_item = NULL;

  return list;
}


Item * allocate_item(void) {
  Item *item = (Item *)malloc(sizeof(Item));

  return item;
}

Item * prepend_item(Item *list, Item *item) {
  assert(list != NULL);
  assert(item != NULL);

  list->next_item = item;

  return list;
}

Item * append_item(Item *list, Item *item) {
  assert(list != NULL);
  assert(item != NULL);
  
  list->next_item = item;
  item->next_item = NULL;

  return list;
}

Item * insert_item(Item *list, Item *item, int position) {
  assert(list != NULL);
  assert(item != NULL);
  assert(position >= 0);
  
  if (position == 0) {
   return prepend_item(list, item);
  }
  
  Item *current_item = list;
  // In order to insert a new item, we must find the item 1 position before the
  // desired insert position.
  int i = position -  1;

  while(--i && current_item != NULL) {
    current_item = current_item->next_item;
  }
 
  if (current_item == NULL) {
    return append_item(list, item);
  }

  // Insert the new item
  Item *temp = current_item->next_item;
  current_item->next_item = item;
  item->next_item = temp;

  return list;
}

// Returns an item for a given position
Item* find_item(Item* list, int position){ 
  // Assert that the position is greater than or equal to zero.
  // Normally, you want a program to continue executing if an error is
  // encountered. However, passing an invalid position is a programming error
  // and as such, the program ought to halt execution so the bug may be fixed.
  assert(position >= 0);

  int i = position; 
  Item *current_item = list;

  while (--i && current_item != NULL) {
    current_item = current_item->next_item;
  }

  return current_item;
}

int main(int argc, char **argv) {
  unsigned int i;
  unsigned int limit = 10;
  // Think of `list` as an array variable. In C, an array variable is
  // actually a pointer to the first element of the array.
  Item *list, *current_item;
  
  // Initialize the list
  current_item = list = allocate_item();
   
  //printf("\n  Got here. \n");
  init_list(list);

  // Create list items
  for(i = 0; i < limit; i ++) {
    // When creating a new item, set the new item's address to the struct
    // memeber `next_item` and then set `next_item` to `current_item` to advance
    // the list.
    Item *item = allocate_item();
    append_item(current_item, item);
    current_item->value = i;
    current_item = current_item->next_item;
  }
  
  // Reset the current item pointer to the start of the list so we can print the
  // list to stdout
  current_item = list;

  while(current_item != NULL) {
    printf("  %d\n", current_item->value);
    current_item = current_item->next_item;
  }

  current_item = find_item(list, 4);

  printf("  Searched item: %d", current_item->value);
  // Leak memory.
}
