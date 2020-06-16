#ifndef COM_DATABASE_LIBRARY_H
#define COM_DATABASE_LIBRARY_H 

#pragma once
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <time.h>
// ------------------------------------------------ Communication structs ------------------------------------------------
struct com_node{
	struct stnode* student;
    struct node* books;
    struct com_node* next;
    char* date;
};

typedef struct com_node comnode;

comnode* rootC = NULL;

// ------------------------------------------------ Communication structs ------------------------------------------------

// ------------------------------------------------ Communication ------------------------------------------------
void clear_comnode(comnode* node){
    free(node->date);
    free(node);
}

void add_com(comnode* current,int isbn, char* number ,char* date){
    if (current->next == NULL ){
        current->next = (comnode*)malloc(sizeof(comnode));
        current->next->books = find_edit_lb(root, isbn);
        current->next->next = NULL;
        current->next->student = find_edit_st(rootS, number);
        current->next->date = date;
    } else if(isbn == current->next->books->isbn && !strcmp(number, current->next->student->number)){
    	//error
    } else {
    	add_com(current->next,isbn,number,date);
    }
}

void add_first_com(comnode* current,int isbn, char* number ,char* date){
    if (current == NULL){
		rootC = (comnode*)malloc(sizeof(comnode));
		rootC->books = find_edit_lb(root, isbn);
		rootC->next = NULL;
		rootC->student = find_edit_st(rootS, number);
		rootC->date = date;
    } else if(isbn == current->books->isbn && !strcmp(number, current->student->number)){
    	//error
    } else {
    	add_com(current,isbn,number,date);
    }
}

void del_com(comnode* current,int isbn, char* number){
	if (current->next == NULL)
		//error
    if ((isbn != current->next->books->isbn) || (strcmp(current->next->student->number, number) != 0)){
        del_com(current->next,isbn,number);
    } else {
	    comnode* temp = current->next;
	    current->next = current->next->next;
	    clear_comnode(temp);
	}
}

void del_first_com(comnode* current,int isbn, char* number){
	if (current == NULL)
		//error
    if((current->books->isbn != isbn) || (strcmp(current->student->number, number) != 0)){
        del_com(current,isbn, number);
    } else {
        comnode* temp = current->next;
        clear_comnode(current);
        rootC = temp;
    }
}

void delfull_com(comnode* current){
    if (current == NULL){
        return;
    }
    comnode* next = current->next;
    clear_comnode(current);
    delfull_com(next);
}
void delfullfirst_com(comnode* current){
    delfull_com(current);
    rootC = NULL;
}

void base_out_com(comnode* current,FILE* fth){
    fprintf(fth,"%d;",current->books->isbn);
    fprintf(fth,"%s;",current->student->number);
    fprintf(fth,"%s\n",current->date);
}

void list_com(comnode* current,FILE* fth){
    if (current == NULL){
        return;
    }
    if (fth == NULL){
        return; //error
    }
    base_out_com(current,fth);
    list_com(current->next, fth);
}

comnode* find_by_isbn(comnode* current,int isbn){
	if (current == NULL){
		return NULL; //error
	}
	if (isbn == current->books->isbn){
		return current;
	}
	return find_by_isbn(current->next,isbn);
}

comnode* find_by_number(comnode* current,char* number){
    if (current == NULL){
        return NULL; //error
    }
    if (!(strcmp(number ,current->student->number))){
        return current;
    }
    return find_by_number(current->next, number);
}


/*
void backup_com(){
    char* tmt = timeinf();
    char* book = "communication_";
    char* flnm = "C:\\Users\\Timur\\Desktop\\Database\\Backups\\";
    char* filename = calloc(strlen(tmt) + strlen(book) + 1, 1);
    strcat(filename,flnm);
    strcat(filename,book);
    strcat(filename,tmt);
    strcat(filename,"csv");
    FILE* fth1 = fopen(filename,"w");
    list_lb(root,fth1);
    FILE* fth2 = fopen("C:\\Users\\Timur\\Desktop\\Database\\Backups\\BackupsLibraryStudent.txt","a+");   //C:\Users\Timur\Desktop\Database\Backups
    fputs(filename,fth2);
    fputc('\n',fth2);
    fclose(fth1);
    fclose(fth2);
    printf("Backup saved\n");
}

void backup_out_lb(){
    fth1 = fopen(" ", "r");
    if (fth1 == NULL){
        printf("Cannot open file %s \n", str_bck);
        //error(0);
    }
    // Open another file for writing
    fth2 = fopen("C:\\Users\\Timur\\Desktop\\Database\\Databases\\StudentLibrary.csv", "w");
    if (fth2 == NULL)
    {
        printf("Cannot open file %s \n", "Library.csv");
        //error();
    }
    // Read contents from file
    while ((ch = fgetc(fth1)) != EOF) {   //(ch = fgetc(fth1)) != EOF
        fputc(ch, fth2);
    }
    //fputc(EOF,fth2);
    //fseek(fth1,0,0);
    printf("\nBackup successful recover\n");
    fclose(fth1);
    fclose(fth2);
}*/

void base_to_stack_com(){
    FILE* fth1 = fopen("C:\\Users\\Timur\\Desktop\\Database\\Databases\\Library.csv","r");
    if (fth1 == NULL)
        return ;
    while(fgetc(fth1)!= EOF){
        fseek(fth1,-1,1);
        add_first_com(rootC,atoi(fdynstring(fth1,';')),fdynstring(fth1,';'),fdynstring(fth1,';'));
        fclose(fth1);
    }
}


void exit_com(){
    list_com(root,fth)
    fclose();
    fclose();
   //printf("StudentLibrary database saved and closed");
}

// ------------------------------------------------ Communication ------------------------------------------------


#endif //COM_DATABASE_LIBRARY_H