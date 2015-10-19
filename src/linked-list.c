#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef struct item {
  int value;
  struct item *next_item;
} Item;

Item * init_list(Item *);
Item * find_item(Item *, int);


Item * init_list(Item *list) {
  //assert(list);
  list->value = 0;
  list->next_item = NULL;

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
  list = current_item = (Item *)malloc(sizeof(Item));

  init_list(list);

  current_item->next_item = NULL;
  
  // Create list items
  for(i = 1; i < limit; i ++) {
    // When creating a new item, set the new item's address to the struct
    // memeber `next_item` and then set `next_item` to `current_item` to advance
    // the list.
    current_item->next_item = (Item *)malloc(sizeof(Item));
    current_item = current_item->next_item;
    current_item->value = i;
  }
  
  // Set the last item to NULL to indicate that there are no more items.
  current_item->next_item = NULL;
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
