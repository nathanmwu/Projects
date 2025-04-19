/********************************************************************************* 
* Nathan Wu, nmwu 
* 2023 Winter CSE101 PA4 
* ListTest.c
* Test client for List ADT
*********************************************************************************/
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include"List.h"

int main(int argc, char* argv[]){
   
   List A = newList();
   List B = newList();
   List C = newList();
   int X[] = {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'};
   int i;
   char u='A', v='B', w='C'; 
   bool equal = false;

   // initialize Lists A and B
   for(i=0; i<=25; i++){
      append(A, &X[i]);
      prepend(B, &X[i]);
   }
   // print alphabet in reverse and forward
   for(moveBack(A); index(A)>=0; movePrev(A)){
      printf("%c ", *(char*)get(A));
   }
   printf("\n");
   for(moveBack(B); index(B)>=0; movePrev(B)){
      printf("%c ", *(char*)get(B));
   }
   printf("\n");
   // print alphabet forwards and in reverse
   for(moveFront(A); index(A)>=0; moveNext(A)){
      printf("%c ", *(char*)get(A));
   }
   printf("\n");
   for(moveFront(B); index(B)>=0; moveNext(B)){
      printf("%c ", *(char*)get(B));
   }
   printf("\n");
   // make a copy of A
   moveFront(A);
   while( index(A)>=0 ){
      append(C, get(A));
      moveNext(A);
   }
   // print copy
   for(moveFront(C); index(C)>=0; moveNext(C)){
      printf("%c ", *(char*)get(C));
   }
   printf("\n");
   // check equality of A and C
   equal = (length(A)==length(C));
   moveFront(A);
   moveFront(C);
   while( index(A)>=0 && equal){
      equal = ( get(A)==get(C) );
      moveNext(A);
      moveNext(C);
   }
   printf("A equals C is %s\n", (equal?"true":"false") );

   moveFront(A);
   for(i=0; i<5; i++) moveNext(A);     // at index 5
   printf("index(A)=%d\n", index(A));
   insertBefore(A, &u);                // now at index 6
   printf("index(A)=%d\n", index(A));
   for(i=0; i<9; i++) moveNext(A);     // at index 15
   printf("index(A)=%d\n", index(A));
   insertAfter(A, &v);                 // doesn't change index
   printf("index(A)=%d\n", index(A));
   for(i=0; i<5; i++) movePrev(A);     // at index 10
   printf("index(A)=%d\n", index(A));
   delete(A);                          // index is now undefined
   printf("index(A)=%d\n", index(A));
   moveBack(A);                        // now at index 26
   printf("index(A)=%d\n", index(A));
   for(i=0; i<10; i++) movePrev(A);    // at index 16
   printf("index(A)=%d\n", index(A));
   set(A, &w);
   // print A in forward and backward direction
   for(moveFront(A); index(A)>=0; moveNext(A)){
      printf("%c ", *(char*)get(A));
   }
   printf("\n");
   for(moveBack(A); index(A)>=0; movePrev(A)){
      printf("%c ", *(char*)get(A));
   }
   printf("\n");
   // check length of A
   printf("%d\n", length(A));
   clear(A);
   printf("%d\n", length(A));

   freeList(&A);
   freeList(&B);
   freeList(&C);

   return(0);
}

/*
Output of this program:
a b c d e f g h i j k l m n o p q r s t u v w x y z 
z y x w v u t s r q p o n m l k j i h g f e d c b a 
z y x w v u t s r q p o n m l k j i h g f e d c b a 
a b c d e f g h i j k l m n o p q r s t u v w x y z 
a b c d e f g h i j k l m n o p q r s t u v w x y z 
A equals C is true
index(A)=5
index(A)=6
index(A)=15
index(A)=15
index(A)=10
index(A)=-1
index(A)=26
index(A)=16
a b c d e A f g h i k l m n o B C q r s t u v w x y z 
z y x w v u t s r q C B o n m l k i h g f A e d c b a 
27
0
*/