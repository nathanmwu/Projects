/********************************************************************************* 
* Nathan Wu, nmwu 
* 2023 Winter CSE101 PA1 
* Lex.c 
* File line sorting program
*********************************************************************************/

#include "List.h"
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>

#define MAX_LEN 300

int main(int argc, char* argv[]){
    int line_count;
    FILE *in, *out;
    char line[MAX_LEN];

    // check command line for correct number of arguments
    if (argc != 3){
        fprintf(stderr, "Usage: %s <input file> <output file>\n", argv[0]);
        exit(1);
    }

    // open files for reading and writing 
    in = fopen(argv[1], "r");
        if( in==NULL ){
        fprintf(stderr, "Unable to open file %s for reading\n", argv[1]);
        exit(1);
    }
    out = fopen(argv[2], "w");
    if( out==NULL ){
        fprintf(stderr, "Unable to open file %s for writing\n", argv[2]);
        exit(1);
    }

    // count lines of input file
    line_count = 0;
    while( fgets(line, MAX_LEN, in) != NULL)  {
        line_count++;
    }

    // reset file position and allocate array
    rewind(in);
    char** array = calloc(line_count, sizeof(char *));

    // populate array with lines from file
    for(int i = 0; i < line_count; i++){
        fgets(line, MAX_LEN, in);       // read in line from file
        line[strcspn(line, "\n")] = 0;  // remove \n character from line
        array[i] = calloc(strlen(line)+1, sizeof(char));    // allocate memory for line
        strcpy(array[i], line); // copy line into array
    }

    // create List of indexes
    List L = newList();
    append(L, 0);   // add first element to empty list
    for(int i = 1; i < line_count; i++){    // outer loop inserts a line from array into List
        moveFront(L);
        while(index(L)>=0){     // while cursor is defined
            if(strcmp(array[i], array[get(L)])<0){
                insertBefore(L, i);
                break;  // array element has found its place in List
            } else {
                moveNext(L);    // check next element
            }
        }
        if (index(L)==-1){  // cursor moved all the way to end, therefore array[i] is last
            append(L, i);
        }
    }
    //printList(stdout, L);
    //printf("\n");

    // print sorted lines to outfile
    moveFront(L);
    while(index(L)>=0){
        if (index(L)!=0) {fprintf(out, "\n");}    // prints \n before line except before first line
        fprintf(out, "%s", array[get(L)]);  // write each line to outfile
        moveNext(L);
    }

    // close files 
    fclose(in);
    fclose(out);

    // free all allocated memory
    for(int i = 0; i < line_count; i++){
        free(array[i]);
    }
    free(array);
    freeList(&L);

    return(0);
}
