#ifndef LIB_DATABASE_LIBRARY_H
#define LIB_DATABASE_LIBRARY_H

#pragma once
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <time.h>


struct book_node{
    char* author;
    char* name_of_book;
    int all;
    int available;
} ;

struct node{
    int isbn;
    struct book_node* content;
    struct node* next;
};

typedef struct node bknode;

bknode* root = NULL;



// ------------------------------------------------ Library ------------------------------------------------
void clear_bknode_bk(bknode* node){
    free(node->content->author);
    free(node->content->name_of_book);
    free(node->content);
    free(node);
}

void add_lb(bknode* current,int isbn,struct book_node* content){
    if (current->next == NULL ){
        current->next = (bknode*)malloc(sizeof(bknode));
        current->next->isbn = isbn;
        current->next->next = NULL;
        current->next->content = content;
    } else if(isbn < current->next->isbn){
        bknode* temp = (bknode *)malloc(sizeof(bknode));
        temp->isbn=isbn;
        temp->content = content;
        temp->next = current->next;
        current->next = temp;
    } else {
        if (isbn != current->next->isbn){
            add_lb(current->next, isbn, content);
        } else {
            current->content = content;
        }
    }
}

void add_first_lb(bknode* current, int isbn, struct book_node* content){
    if (current == NULL){
        root = (bknode*)malloc(sizeof(bknode));
        root->isbn = isbn;
        root->next = NULL;
        root->content = content;
    } else if (isbn < current->isbn){
        bknode* nde = (bknode*)malloc(sizeof(bknode));
        nde->isbn = isbn;
        nde->next = root;
        nde->content = content;
        root = nde;
    } else if (isbn != current->isbn){
        add_lb(current, isbn, content);
    } else {
        current->content = content;
    }
}

void del_lb(bknode* current,int isbn){
    if (isbn != current->next->isbn){
        del_lb(current->next,isbn);
    }
    bknode* temp = current->next;
    current->next = current->next->next;
    free(temp);
}

void del_first_lb(bknode* current,int isbn){
    if(current->isbn != isbn){
        del_lb(current,isbn);
    } else {
        bknode* temp = current->next;
        free(current);
        root = temp;
    }
}

void delfull_lb(bknode* current){
    if (current == NULL){
        return;
    }
    bknode* next = current->next;
    clear_bknode_bk(current);
    delfull_lb(next);
}
void delfullfirst_lb(bknode* current){
    delfull_lb(current);
    root = NULL;
}

void base_out_lb(bknode* current,FILE* fth){
    fprintf(fth,"%d;",current->isbn);
    fprintf(fth,"%s;",current->content->author);
    fprintf(fth,"%s;",current->content->name_of_book);
    fprintf(fth,"%d;",current->content->all);
    fprintf(fth,"%d\n",current->content->available);
};

void list_lb(bknode* current,FILE* fth){
    if (current == NULL){
        return;
    }
    if (fth == NULL){
        return; //error
    }
    base_out_lb(root,stdout);
    list_lb(current->next, fth);
}


bknode* find_lb(bknode* current,int isbn){
if (current == NULL){
return NULL; //error
}
if (isbn == current->isbn){
base_out_lb(current,stdout);

}
return find_lb(current->next,isbn);
}

bknode* find_edit_lb(bknode* current,int isbn){
if (current == NULL){
return NULL; //error
}
if (isbn == current->isbn){
return current;
}
return find_edit_lb(current->next,isbn);
}

bknode* find_by_au(bknode* current,char* surname){
    if (current == NULL){
        return NULL; //error
    }
    if (!(strcmp(surname ,current->content->author))){
        base_out_lb(current,stdout);
    }
    return find_by_au(current->next, surname);
}

//--book
void give_book(bknode* current, int isbn){
    if (current == NULL){
        return; //error
    }
    current = find_lb(current,isbn);
    if (current -> content -> available != 0){
        --current -> content -> available;
    } else
        printf("Out of books");// error
}

//++book
void bring_book (bknode* current, int isbn){
    if (current == NULL){
        return; //error
    }
    current = find_lb(current,isbn);
    ++current -> content -> available;
}

void chg_count_by_isbn(bknode* current,int isbn){
    bknode* temp = find_lb(current,isbn);
    printf("\nAvailable quantity of book: %d\n",temp->content->available);
    printf("\nAll quantity of book: %d\n",temp->content->available);
    printf("Type value to change:");
    scanf("%d",&temp->content->all);
}

void edit_book(){
    printf("Welcome to Edit Menu\n");
    printf("write:\n");
    printf("isbn\n");
    printf("name of column\n");
    printf("value\n");
    int isbn = atoi(dynstring('\n'));
    char* cell = dynstring('\n');
    char* value = dynstring('\n');
    bknode* curr=find_edit_lb(root,isbn);
    if (!strcmp("author", cell)){
        free(curr->content->author);
        curr->content->author = value;
    } else if  (!strcmp("name of book", cell)) {
        free(curr->content->name_of_book);
        curr->content->name_of_book = value;
    } else if (!strcmp("all count", cell)) {
        curr->content->all = atoi(value);
    } else if (!strcmp("available", cell)) {
        curr->content->available = atoi(value);
    } else {
        //10/5 chertovikh errorov
    }

}


void backup_lb(){
    char* tmt = timeinf();
    char* book = "book_";
    char* flnm = "C:\\Users\\Timur\\Desktop\\Database\\Backups\\";
    char* filename = calloc(strlen(tmt) + strlen(book) + 1, 1);
    strcat(filename,flnm);
    strcat(filename,book);
    strcat(filename,tmt);
    strcat(filename,"csv");
    FILE* fth1 = fopen(filename,"w");
    list_lb(root,fth1);
    FILE* fth2 = fopen("C:\\Users\\Timur\\Desktop\\Database\\Backups\\BackupsLibrary.txt","a+");   //C:\Users\Timur\Desktop\Database\Backups
    fputs(filename,fth2);
    fputc('\n',fth2);
    fclose(fth1);
    fclose(fth2);
    printf("Backup saved\n");
}

void backup_out_lb(){
    delfullfirst_lb(root);
    printf("Choose file of backup\n");
    FILE* fth = fopen("C:\\Users\\Timur\\Desktop\\Database\\Backups\\BackupsLibrary.txt","r");
    if (fth == NULL){
        //error
    }
    char ch;
    while((ch = getc(fth)) != EOF){
        putchar(ch);
    }
    fclose(fth);
    char* string = dynstring('\n');
    char* way = "C:\\Users\\Timur\\Desktop\\Database\\Backups\\";
    char* str_bck = calloc(strlen(way) + strlen(string) + 1, 1);
    strcat(str_bck,way);
    strcat(str_bck,string);
    FILE *fth1, *fth2;
    // Open one file for reading
    fth1 = fopen(str_bck, "r");
    if (fth1 == NULL){
        printf("Cannot open file %s \n", str_bck);
        //error(0);
    }
    // Open another file for writing
    fth2 = fopen("C:\\Users\\Timur\\Desktop\\Database\\Databases\\Library.csv", "w");
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
}

void base_to_stack_lb(){
    FILE* fth1 = fopen("C:\\Users\\Timur\\Desktop\\Database\\Databases\\Library.csv","r");
    while(fgetc(fth1)!= EOF){
        fseek(fth1,-1,1);
        struct book_node* cont = (struct book_node*)malloc(sizeof(struct book_node));
        char* isbn = fdynstring(fth1,';');

        //char* isbn = fdynstring(fth1,';');
        cont->author = fdynstring(fth1,';');
        //printf("\n%s\n",cont->surname);
        cont->name_of_book = fdynstring(fth1,';');
        //printf("\n%s\n",cont->name);
        cont->all = atoi(fdynstring(fth1,';'));
        //printf("\n%s\n",cont->patronym);
        cont->available = atoi(fdynstring(fth1,';'));
        //printf("\n%s\n",cont->facility);
        add_first_lb(root,atoi(isbn),cont);
        fclose(fth1);
    }
}


void exit_lb(){
    list_lb(root,".\\library.csv")
    fclose();
    fclose();
    printf("Library database saved and closed");
}
//----------func for command getter----------
void add_book(){
    struct book_node* temp = (struct book_node*)malloc(sizeof(struct book_node));
    printf("Type isbn:");
    char* isbn = dynstring('\n');
    printf("Type author:");
    temp->author = dynstring('\n');
    printf("Type name of book:");
    temp->name_of_book = dynstring('\n');
    printf("Type count of books:");
    temp->all = atoi(dynstring('\n'));
    printf("Type available books:");
    temp->available = atoi(dynstring('\n'));
    add_first_lb(root,atoi(isbn),temp);
}


void del_book(){
    printf("Type isbn:");
    char* isbn = dynstring('\n');
    del_first_lb(root,atoi(isbn));
}


void find_book(){
    printf("Type isbn:");
    char* isbn = dynstring('\n');
    find_lb(root,atoi(isbn));
}


void find_by_author(){
    printf("Type author: ");
    char* surname = dynstring('\n');
    find_by_au(root,surname;)
}

void change_count_by_isbn(){
    printf("\nType isbn:");
    char* string = dynstring('n');
    chg_count_by_isbn(root,atoi(string));
}


//----------func for command getter----------

// ------------------------------------------------ Library ------------------------------------------------

#endif //LIB_DATABASE_LIBRARY_H
