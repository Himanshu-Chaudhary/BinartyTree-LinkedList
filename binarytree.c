/**********************************************/
/*Himanshu Chaudhary                          */
/*April 13, 2016                              */
/*CS 241L    Section #003                     */
/**********************************************/

#include<stdio.h>
#include<stdlib.h>
#include "binarytree.h"



/* @param data, type int
 *  is the data that needs to be assigned to a node
 * @returns TreeNode*, type struct TreeNode*
 *  the node that is created with the given data
 * This function Allocs a new node with given data. */
struct TreeNode* createNode(int data)
{
  /* allocing space to a node*/
  struct TreeNode* newNode= malloc(sizeof(struct TreeNode));
  newNode->data=data;
  newNode->right=NULL;
  newNode->left=NULL;
  return newNode;
}


/* @param root, type struct TreeNode*
 *  is the Tree where the data needs to be inserted
 * @param data, type int
 *  is the data that needs to inserted
 * @returns TreeNode*, type struct TreeNode*
 * This function Inserts data at appropriate place in BST, 
 * and returns new tree root */
struct TreeNode * insertBST ( struct TreeNode * root , int data )
{
  if( root == NULL ) root = createNode ( data );
  /* uses recursion to find the place for data by comparing 
   * data with the node-> data values*/
  else if( data < root-> data ) root-> left = insertBST ( root-> left , data );
  else root-> right = insertBST ( root-> right , data );
  return root;
}



/* @param root, type struct TreeNode*
 *  is the Tree from where the minimun values needs 
 *  to be returned
 * @returns the minimun value from the binary tree
 * This function Returns the minimum value from the
 *  binary search tree*/
int minValueBST(struct TreeNode* root)
{
  struct TreeNode* current = root;
 
  /* loops toward the leftmost leaf and returns the\
   * value from the leftmost leaf */
  while (current->left != NULL) {
    current = current->left;
  }
  return(current->data);
  
}


/* @param root, type struct TreeNode*
 *  is the Tree whose depth needs to be found
 * @returns the depth of the tree
 * This function Returns the maximum depth of the tree*/
int maxDepth(struct TreeNode* root)
{
  /* finds the leftDepth and the rightDepth and returns the 
   * highest among them*/
  int leftDepth , rightDepth ;
  if( root == NULL ) return 0;
  
  else
  {
    leftDepth = maxDepth ( root-> left );
    rightDepth = maxDepth ( root-> right );
    if (leftDepth> rightDepth) return (leftDepth+1);
    return rightDepth+1;
  }
}











/* @param root, type struct TreeNode*
 *  is the Tree from where the data needs to be printed
 * @param mode, type int
 *  1 is used for printLeaves function and
 *  0 is used for printTree function
 * This function prints data for inorder tree traversal or
 *  data for leaves depending upon its mode*/
 void printHelper ( struct TreeNode * root, int mode)
 {
 if (root == NULL) return;
 printHelper ( root-> left,mode);
 if (mode==0) printf ("%d ", root-> data );
 else if (mode==1 
          && root-> left == NULL && root-> right == NULL)
 {
   printf ("%d ", root-> data );
 }
 printHelper ( root-> right,mode);
 }

/* Print data for inorder tree traversal on single line,
 *  using the printHelper function*/
 void printTree ( struct TreeNode * root )
 {
 printHelper (root,0);
 printf("\n");
}



/* Print data for leaves on single line,
 *  using the printHelper function*/

void printLeaves ( struct TreeNode * root )
{
  printHelper (root,1);
  printf ("\n");
}

/* @param root, type struct TreeNode*
 *  is the Tree which needs to be checked
 * @returns either 0 or 1
 * This function checks if a tree is a binary tree or not*/
int isBSTHelper ( struct TreeNode * root , int min , int max )
 {
 if( root == NULL ) return 1;\
 /* uses recursion to check if the data in each node is a 
  * valid member of binary tree or not*/
 if( root-> data >  min 
     && root->data < max
     && isBSTHelper(root->left, min, root->data)
     && isBSTHelper(root->right, root->data, max))
   return 1;
 else return 0;
 }



/* uses isBSTHelper function to check if a tree is a
 * binary tree or not and return either 0 or 1*/
 int isBST ( struct TreeNode * root )
 {
 return isBSTHelper ( root , -32768 , +32767 );
 }


/* @param root, type struct TreeNode*
 *  is the Tree which needs to be checked
 * @returns either 0 or 1
 * This function checks if a tree is balanced or not*/
int isBalanced(struct TreeNode* root)
{ 
  /* finds the leftDepth and rightDepth and checks the
   * difference between them and again uses recursion to
   * check the same for subtrees*/
  int difference = 0;
  int leftDepth , rightDepth ;
  if( root == NULL ) return 1;
  leftDepth = maxDepth ( root-> left );
  rightDepth = maxDepth ( root-> right );
  difference = leftDepth - rightDepth;
  /* checks if the difference is in the range 1 or not and
   * then proceeds towards subtrees*/
  if ( -1 <= difference && difference <= 1
         && isBalanced ( root-> left )
         && isBalanced ( root-> right ))
      {
        return 1;
      }
      else return 0;
 
}



/* @param rootRef, type struct TreeNode**
 *  is the Tree from where the data needs to be deleted
 * @param data, type int
 *  is the data that needs to be deleted
 * @returns either 0 or 1
 * This function Removes data from BST pointed to by rootRef */
int removeBST ( struct TreeNode ** rootRef , int data )
{
  struct TreeNode * temp ;
  /* using recursion to find the location of data in TreeNode
   * and then delets the data*/
  if( data < (* rootRef )-> data )
  {
    if ((*rootRef)->left!=NULL) 
      return removeBST (&((* rootRef )-> left ) , data );
    else return 0;
  }
  else if ( data > (* rootRef )-> data )
  {
    if ((*rootRef)->right!=NULL) 
      return removeBST (&((* rootRef )-> right ) , data );
    else return 0;
  }
   else
   /* if data is found its deleted and the location replaced with 
      appropriate node*/
  { 
    if ((*rootRef)-> left!=NULL  && (*rootRef)-> right!=NULL)
    {
      (* rootRef )-> data = minValueBST ((* rootRef )-> right );
      return removeBST (&((* rootRef )-> right ) , (* rootRef )-> data );
    }
    if ((* rootRef )-> left == NULL )
    {
      temp = * rootRef ;
      * rootRef = (* rootRef )-> right ;
      free ( temp );
    }
    else if ((* rootRef )-> right == NULL )
    {
      temp = * rootRef ;
      * rootRef = (* rootRef )-> left ;
      free ( temp );
    }
    return 1;
  
 }
      
}

/* @param root, type struct TreeNode*
 *  is the Tree which needs to be deleted
 * This function frees up the memory used by a Tree*/
void freeTree(struct TreeNode* root)
{
 if(root == NULL) return;
 freeTree ( root-> left );
 freeTree ( root-> right );
 free ( root );
 }


