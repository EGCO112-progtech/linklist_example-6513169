// Fig. 12.3: fig12_03.c
// Inserting and deleting nodes in a list
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// self-referential structure
struct Node {
  int id; // each listNode contains a character
  char name[30];
  struct Node *nextPtr; // pointer to next node
  struct Node *pPtr;    // pointer to next node
};                      // end structure listNode

typedef struct Node LLnode; // synonym for struct listNode
typedef LLnode *LLPtr;      // synonym for ListNode*

// prototypes

void insert(LLPtr *sPtr, int number, char yourname[]);
int deletes(LLPtr *sPtr, int number);

int isEmpty(LLPtr sPtr);
void printList(LLPtr currentPtr);
void reverseList(LLPtr currentPtr);
void instructions(void);
void Freeall(LLPtr head);

int main(void) {
  LLPtr startPtr = NULL; // initially there are no nodes
  unsigned int choice;   // user's choice
  int yourid;            // char entered by user
  char yourname[30];

  instructions(); // display the menu
  printf("%s", "? ");
  scanf("%u", &choice);

  // loop while user does not choose 3
  while (choice != 3) {

    switch (choice) {
    case 1:
      printf("%s", "Enter an id: ");
      scanf("%d", &yourid);
      printf("%s", "Enter a name: ");
      scanf("%s", yourname);
      insert(&startPtr, yourid, yourname); // insert item in list
      printList(startPtr);
      reverseList(startPtr);
      break;
    case 2: // delete an element
      // if list is not empty
      if (!isEmpty(startPtr)) {
        printf("Enter id to be deleted: ");
        scanf("%d", &yourid);

        // if character is found, remove it
        if (deletes(&startPtr, yourid)) { // remove item
          printf("%d is deleted.\n", yourid);
          printList(startPtr);
          reverseList(startPtr);
        } // end if
        else {
          printf("%d not found.\n\n", yourid);
        } // end else
      }   // end if
      else {
        puts("List is empty.\n");
      } // end else

      break;
    default:
      puts("Invalid choice.\n");
      instructions();

      break;
    } // end switch

    printf("?");
    scanf("%u", &choice);
  } // end while
  /* Clear all nodes at the end of nodes*/
  Freeall(startPtr);
   puts("List is empty.\n");

  return 0;
  puts("End of run.");
} // end main

// display program instructions to user
void instructions(void) {
  puts("Enter your choice:\n"
       "   1 to insert an element into the list.\n"
       "   2 to delete an element from the list.\n"
       "   3 to end.");
} // end function instructions

// insert a new value into the list in sorted order
void insert(LLPtr *sPtr, int number, char yourname[]) {
  LLPtr newPtr;      // pointer to new node
  LLPtr previousPtr; // pointer to previous node in list
  LLPtr currentPtr;  // pointer to current node in list

  newPtr = (LLPtr)malloc(sizeof(LLnode)); // create node

  if (newPtr != NULL) {  // is space available
    newPtr->id = number; // place value in node
    strcpy(newPtr->name, yourname);
    newPtr->nextPtr = NULL; // node does not link to another node

    newPtr->pPtr = NULL;

    previousPtr = NULL;
    currentPtr = *sPtr;

    // loop to find the correct location in the list
    while (currentPtr != NULL && number > currentPtr->id) {
      previousPtr = currentPtr;         // walk to ...
      currentPtr = currentPtr->nextPtr; // ... next node
    }                                   // end while

    // insert new node at beginning of list
    if (previousPtr == NULL) {
      newPtr->nextPtr = *sPtr;
      if (currentPtr)
        currentPtr->pPtr = newPtr;

      *sPtr = newPtr;

    }      // end if
    else { // insert new node between previousPtr and currentPtr
      previousPtr->nextPtr = newPtr;
      newPtr->pPtr = previousPtr;

      newPtr->nextPtr = currentPtr;
      if (currentPtr)
        currentPtr->pPtr = newPtr;

    } // end else
  }   // end if
  else {
    printf("%d not inserted. No memory available.\n", number);
  } // end else
} // end function insert

// delete a list element
int deletes(LLPtr *sPtr, int number) {
  LLPtr previousPtr; // pointer to previous node in list
  LLPtr currentPtr;  // pointer to current node in list
  LLPtr tempPtr;     // temporary node pointer

  // delete first node
  if (number == (*sPtr)->id) {
    tempPtr = *sPtr;          // hold onto node being removed
    *sPtr = (*sPtr)->nextPtr; // de-thread the node
    if (*sPtr)
      (*sPtr)->pPtr = NULL;
    free(tempPtr); // free the de-threaded node
    return number;
  } // end if
  else {
    previousPtr = *sPtr;
    currentPtr = (*sPtr)->nextPtr;

    // loop to find the correct location in the list
    while (currentPtr != NULL && currentPtr->id != number) {
      previousPtr = currentPtr;         // walk to ...
      currentPtr = currentPtr->nextPtr; // ... next node
    }                                   // end while

    // delete node at currentPtr
    if (currentPtr != NULL) {
      tempPtr = currentPtr;

      previousPtr->nextPtr = currentPtr->nextPtr;
      if (currentPtr->nextPtr)
        currentPtr->nextPtr->pPtr = previousPtr;

      free(tempPtr);

      return number;
    } // end if
  }   // end else

  return '\0';
} // end function delete

// return 1 if the list is empty, 0 otherwise
int isEmpty(LLPtr sPtr) { return sPtr == NULL; } // end function isEmpty

// print the list
void printList(LLPtr currentPtr) {
  // if list is empty
  if (isEmpty(currentPtr)) {
    puts("List is empty.\n");
  } // end if
  else {
    puts("The list is:");

    // while not the end of the list
    while (currentPtr->nextPtr != NULL) {
      printf("%d %s--> ", currentPtr->id, currentPtr->name);
      currentPtr = currentPtr->nextPtr;
    } // end while

    printf("%d %s--> NULL\n", currentPtr->id, currentPtr->name);

  } // end else
} // end function printList
void reverseList(LLPtr currentPtr) {
  // if list is empty
  if (isEmpty(currentPtr)) {
    puts("List is empty.\n");
  } // end if
  else {
    puts("The list is:");
    while (currentPtr->nextPtr != NULL) {
      currentPtr = currentPtr->nextPtr;
    } // end while

    // while not the end of the list

    while (currentPtr->pPtr != NULL) {
      printf("%d %s --> ", currentPtr->id, currentPtr->name);
      currentPtr = currentPtr->pPtr;
    } // end while

    printf("%d %s --> NULL\n", currentPtr->id, currentPtr->name);

  } // end else
} // end function printList

void Freeall(LLPtr head) {
  LLPtr tmp;
  tmp = head;
  while (tmp != NULL) {
    printf("deleting id %d\n", tmp->id);
    printf("%d is deleted.\n", tmp->id);
    head = head->nextPtr;
    free(tmp);
    tmp = head;
  }
}
