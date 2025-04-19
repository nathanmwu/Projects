/********************************************************************************* 
* Nathan Wu, nmwu 
* 2023 Winter CSE101 PA1 
*  ListTest.c
*  Test client for List ADT
*********************************************************************************/
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include"List.h"

int main(int argc, char* argv[]){
   List A = newList();  // List with > 1 elements
   List B = newList();  // List with 1 element
   List C = newList();  // empty List
   List D = NULL;       // NULL List
   int i;

   for(i=1; i<=10; i++){
      append(A,i);
   }
   prepend(B, 5);

   printList(stdout,A); printf("\n");
   printList(stdout,B); printf("\n");
   printList(stdout,C); printf("\n"); 
   //printList(stdout,D); printf("\n");   // correctly prints error

   moveFront(A);
   moveFront(B);
   moveFront(C);
   //moveFront(D);   // correctly prints error

   printf("len: %i index: %i\n", length(A), index(A));
   printf("len: %i index: %i\n", length(B), index(B));
   printf("len: %i index: %i\n", length(C), index(C));
   //printf("len: %i index: %i\n", length(D), index(D));    // correctly prints error


   printf("%i\n", front(A));
   printf("%i\n", front(B));
   //printf("%i\n", front(C));  // correctly prints error
   //printf("%i\n", front(D));  // correctly prints error

   printf("%i\n", back(A));
   printf("%i\n", back(B));
   //printf("%i\n", back(C));  // correctly prints error
   //printf("%i\n", back(D));  // correctly prints error

   for(moveFront(A); index(A)>=0; moveNext(A)){
      printf("%d ", get(A));
   }
   printf("\n");
   for(moveBack(B); index(B)>=0; movePrev(B)){
      printf("%d ", get(B));
   }
   printf("\n");

   D = copyList(A);
   printf("%s\n", equals(A,D)?"true":"false");
   printf("%s\n", equals(D,B)?"true":"false");

   moveFront(A);
   insertBefore(A, 0);
   delete(A);
   //insertAfter(A, 0);   // reports correct error message
   moveBack(D);
   deleteFront(D);
   moveNext(D);
   deleteBack(D);
   movePrev(D);
   //delete(D); // reports correct error message
   moveFront(D);
   set(D, 0);
   clear(B);

   printList(stdout,A); printf("\n");
   printList(stdout,B); printf("\n");
   printList(stdout,C); printf("\n"); 
   printList(stdout,D); printf("\n"); 

   freeList(&A);
   freeList(&B);
   freeList(&C);
   freeList(&D);

   return(0);
}