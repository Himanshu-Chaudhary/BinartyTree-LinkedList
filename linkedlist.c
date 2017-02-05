/**********************************************/
/*Himanshu Chaudhary                          */
/*April 13, 2016                              */
/*CS 241L    Section #003                     */
/**********************************************/

#include <stdlib.h>
#include <stdio.h>
#include "linkedlist.h"



/* @param data, type int
 *  is the data that needs to be assigned to a node
 * @returns ListNode*, type struct ListNode*
 *  the node that is created with the given data
 * This function Allocs a new node with given data. */

struct ListNode* createNode(int data)
{
  /* allocing space to a node*/
  struct ListNode* newNode = malloc(sizeof(struct ListNode));
  newNode->data = data;
  newNode->next = NULL;
  return newNode;
}



/* @param head, type struct ListNode*
 *  is the list where the data needs to be inserted
 * @param data, type int
 *  is the data that needs to inserted
 * @returns ListNode*, type struct ListNode*
 * This function Inserts data at appropriate place in a sorted list, 
 * and returns new list head */

struct ListNode* insertSorted(struct ListNode* head, int data)
{
  struct ListNode* new = createNode(data);
  struct ListNode* currentNode = head;
  /* finds the appropriate place to insert data by comaparing
   * node->data with data */
  if (currentNode == NULL || currentNode->data> data)
  {
    new->next = currentNode;
    return new;
  }
  else 
  {
   /* find the place where the data is smaller than next node-> data 
    * or the end of the list*/
    while (currentNode->next != NULL && currentNode->next->data< data)
    {
      currentNode= currentNode->next;
    }
    new->next=currentNode->next;
    currentNode->next = new;
    return head;
  }
}

/* @param headRef, type struct ListNode*
 *  is the list whose length needs to be found
 * @returns the length of the list 
 * This function returns the length of the list*/

int listLength(struct ListNode* head)
{
  struct ListNode* new = head;
  int count =0;
  /* the count is increased until end is reached*/
  while( new!= NULL)
  {
    count++;
    new = new->next;
  }
  return count;
}

/* @param headRef, type struct ListNode*
 *  is the list which needs to be printed
 * This function prints the data in the list*/

void printList ( struct ListNode * head )
{
  int i =0;
  int length = listLength(head);
  struct ListNode * temp = head ;
  /* the length is known of the list using listlength function
   * and the data is then printed in a loop*/
  for (i=0;i<length;i++)
  {
    printf ( "%d " , temp -> data );
    temp = temp -> next ;
  }
  printf ( "\n" );
}

void freeList ( struct ListNode * head )
{
  struct ListNode * temp = head ;
  if (temp!=NULL)
  {
    freeList(temp->next);
    free(temp);
  }

}

/* @param headRef, type struct ListNode*
 *  is the list which needs to be reversed
 * This function is used to reverse the data 
 * in the list list */

void reverseList(struct ListNode** headRef)
{
    /* previous points to the previous value pointed by
    * *headRef and next stores points to the next value*/
    struct ListNode* previous   = NULL;
    struct ListNode* current = *headRef;
    struct ListNode* next;
    /* previous points to the first data of current and it points to null
     * that data is then removed from current making the second data its first
     * each loops adds the first data current in the front of the previous*/ 
    while (current != NULL)
    {
        next  = current->next;  
        current->next = previous;   
        previous = current;
        current = next;
    }
    *headRef = previous;
}
 
    


/* @param headRef, type struct ListNode**
 *  is the list from where the data needs to be deleted
 * @param data, type int
 *  is the data that needs to be deleted
 * @returns either 0 or 1
 * This function Removes data from data from list 
 *  if the data is found */
int removeItem(struct ListNode** headRef, int data)
{
  /* loops until the data is found in the node or 
   * the end is reached*/
  while (*headRef && (*headRef)->data != data)
  {
    
    headRef= &(*headRef)->next;
  }
  /* if data is found the node is deleted the next node
   * is placed*/
  if (*headRef)
  {
    struct ListNode* newNode = *headRef;
    *headRef= (*headRef)->next;
    free(newNode);
    return 1;
  
}
 return 0;
}

/* @param headRef, type struct ListNode**
 *  is the list from where the data needs to be inserted
 * @param data, type int
 *  is the data that needs to be inserted
 * @returns the new list with the data at its head
 * This function inserts data at head of the list and 
 * returns the new list */
struct ListNode* push(struct ListNode* head, int data)
{
 /* creates a new list with the data and points it to the head*/
  struct ListNode* newNode = createNode(data);
  newNode->next = head;
  return newNode;
}


/* @param headRef, type struct ListNode*
 *  is the list whose data at head needs to be removed
 * @returns the data from head that is removed 
 * This function Removes and returns data from head of 
 * changing head and the memory is freed*/

int pop(struct ListNode** headRef)
{
  /* an int stores the data at head then the 
   * data at head is removed and the head of the 
   * list is pointed to the next data*/

  struct ListNode* newNode = *headRef;
  int value = newNode->data;
 (*headRef) = newNode->next;
  free(newNode);
  return value;
}


/* @param headRef, type struct ListNode*
 *  is the list which needs to be deleted
 * This function is used to free up the memory 
 * used by a list */



