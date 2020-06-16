#ifndef UNTITLED_LIBRARY_H
#define UNTITLED_LIBRARY_H

#pragma once
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <time.h>

// ------------------------------------------------ Library Structs ------------------------------------------------
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
// ------------------------------------------------ Library Structs ------------------------------------------------

// ------------------------------------------ Students struct ------------------------------------------
struct student_node{
    char* surname;
    char* name;
    char* patronym;
    char* facility;
    char* department ;
} ;

struct stnode{
    char* number;
    struct student_node* content;
    struct stnode* next;
};

typedef struct stnode snode;

snode* rootS = NULL;

// ------------------------------------------ Students struct ------------------------------------------


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

// ------------------------------------------------ Library ------------------------------------------------
void clear_bknode_bk(bknode* node){
    free(node->content->author);
    free(node->content->name_of_book);
    free(node->content);
    free(node);
}

void add_lb(bknode* current,int isbn,struct book_node* content){
    if (current->next == NULL){
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
    if (current == NULL){
        return;
    }
    if (isbn != current->next->isbn){
        del_lb(current->next,isbn);
    }
    bknode* temp = current->next;
    current->next = current->next->next;
    free(temp);
}

comnode* find_by_isbn(comnode* ,int);

void del_first_lb(bknode* current,int isbn){
    if (find_by_isbn(rootC, isbn) != NULL)
        //error
    if (current == NULL){
        return;
    }
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
    base_out_lb(current,fth);
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

void add_first_com(comnode*,int, char*,char*);

//--book
void give_book(bknode* current, int isbn,char* number,char* date) {
    if (current == NULL) {
        return; //error
    }
    current = find_edit_lb(current, isbn);
    if (current->content->available != 0) {
        --current->content->available;
        add_first_com(rootC, isbn, number, date);

    } else {
        comnode *min = find_by_isbn(rootC, isbn);
        comnode* temp = min->next;
        while ((temp = find_by_isbn(temp,isbn))!= NULL){
            if (psdodate(min->date) > psdodate(temp->date))
                min = temp;
            temp=temp->next;
        }
        printf("Nearest return in %s\n",min->date);
    }
}


void del_first_com(comnode*,int, char*);
//++book
void bring_book (bknode* current, int isbn,char* number){
    if (current == NULL){
        return; //error
    }
    current = find_lb(current,isbn);
    ++current -> content -> available;
    del_first_com(rootC,isbn,number);
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
        cont->available = atoi(fdynstring(fth1,'\n'));
        //printf("\n%s\n",cont->facility);
        add_first_lb(root,atoi(isbn),cont);
        fclose(fth1);
    }
}


void exit_lb(){
    if (root == NULL){
        //error
    }
    FILE* fth1 = fopen("C:\\Users\\Timur\\Desktop\\Database\\Databases\\Library.csv","w");
    list_lb(root,fth1);
    fclose(fth1);
    printf("\nLibrary database saved and closed\n");
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
    find_by_au(root,surname);
}

void change_count_by_isbn(){
    printf("\nType isbn:");
    char* string = dynstring('n');
    chg_count_by_isbn(root,atoi(string));
}

void give_book_lb(){
    printf("\nType isbn:");
    char* isbn = dynstring('\n');
    printf("\nType number of student:");
    char* number = dynstring('\n');
    printf("\nType date:");
    char* date = dynstring('\n');
    give_book(root,atoi(isbn),number,date);
}


void bring_book_lb(){
    printf("\nType isbn:");
    char* isbn = dynstring('\n');
    printf("\nType number of student:");
    char* number = dynstring('\n');
    bring_book(root,atoi(isbn),number);
}


//----------func for command getter----------

// ------------------------------------------------ Library ------------------------------------------------




// ------------------------------------------ Student database ------------------------------------------
void clear_snode_st(snode* node) {
    free(node->content->surname);
    free(node->content->name);
    free(node->content->patronym);
    free(node->content->facility);
    free(node->content->department);
    free(node->number);
    free(node->content);
    free(node);
}


void add_st(snode* current,char* number,struct student_node* content){
    if (current->next == NULL ){
        current->next = (snode*)malloc(sizeof(snode));
        current->next->number = number;
        current->next->next = NULL;
        current->next->content = content;
    } else if(strcmp(number,current->next->number)<0){
        snode* temp = (snode *)malloc(sizeof(snode));
        temp->number=number;
        temp->content = content;
        temp->next = current->next;
        current->next = temp;
    } else {
        if (strcmp(number,current->next->number)){
            add_st(current->next, number, content);
        } else {
            current->content = content;
        }
    }
}

void add_first_st(snode* current,char* number, struct student_node* content){
    if (current == NULL){
        rootS = (snode*)malloc(sizeof(snode));
        rootS->number = number;
        rootS->next = NULL;
        rootS->content = content;
    } else if (strcmp(number,current->number) < 0){
        snode* nde = (snode*)malloc(sizeof(snode));
        nde->number = number;
        nde->next = rootS;
        nde->content = content;
        rootS = nde;
    } else if (strcmp(number,current->number)){
        add_st(current, number, content);
    } else {
        current->content = content;
    }
}
comnode* find_by_number(comnode*,char*);

void del_st(snode* current,char* number){
    if (strcmp(number,current->next->number)){
        del_st(current->next,number);
    }
    snode* temp = current->next;
    current->next = current->next->next;
    free(temp);
}

void del_first_st(snode* current,char* number){
    if (find_by_number(rootC, number) != NULL)
        //ERROR
    if(strcmp(current->number,number)){
        del_st(current,number);
    } else {
        snode* temp = current->next;
        free(current);
        rootS = temp;
    }
}


void delfull_st(snode* current){
    if (current == NULL){
        return;
    }
    snode* next = current->next;
    clear_snode_st(current);
    delfull_st(next);
}
void delfullfirst(snode* current){
    delfull_st(current);
    rootS = NULL;
}

void base_out_st(snode* current,FILE* fth){
    fprintf(fth,"%s;",current->number);
    fprintf(fth,"%s;",current->content->surname);
    fprintf(fth,"%s;",current->content->name);
    fprintf(fth,"%s;",current->content->patronym);
    fprintf(fth,"%s;",current->content->facility);
    fprintf(fth,"%s\n",current->content->department);
};

void list_st(snode* current,FILE* fth){
    if (current == NULL){
        return;
    }
    if (fth == NULL){
        return; //error
    }
    base_out_st(current,fth);
    list_st(current->next, fth);
}


snode* find_st(snode* current,char* number){
    if (current == NULL){
        return NULL; //error
    }
    if (!strcmp(number,current->number)){
        base_out_st(current,stdout);

    }
    return find_st(current->next,number);
}

snode* find_edit_st(snode* current,char* number){
    if (current == NULL){
        return NULL; //error
    }
    if (!strcmp(number,current->number)){
        return current;
    }
    return find_edit_st(current->next,number);
}

snode* find_by_surname(snode* current,char* surname){
    if (current == NULL){
        return NULL; //error
    }
    if (!(strcmp(surname ,current->content->surname))){
        base_out_st(current,stdout);
    }
    return find_by_surname(current->next, surname);
}



void edit_student(){
    printf("Welcome to Edit Menu\n");
    printf("write:\n");
    printf("number\n");
    char* number= dynstring('\n');
    printf("name of column\n");
    char* cell = dynstring('\n');
    printf("value\n");
    char* value = dynstring('\n');
    snode* curr = find_edit_st(rootS,number);
    if (!strcmp("name", cell)){
        free(curr->content->name);
        curr->content->name = value;
    } else if  (!strcmp("surname", cell)) {
        free(curr->content->surname);
        curr->content->surname = value;
    } else if  (!strcmp("patronym", cell)) {
        free(curr->content->patronym);
        curr->content->patronym = value;
    } else if  (!strcmp("facility", cell)) {
        free(curr->content->facility);
        curr->content->facility = value;
    } else if  (!strcmp("department", cell)) {
        free(curr->content->department);
        curr->content->department = value;
    } else {
        // 10/5 chertovikh errorov
    }

}



void backup_st(){
    char* tmt = timeinf();
    char* book = "students_";
    char* flnm = "C:\\Users\\Timur\\Desktop\\Database\\Backups\\";
    char* filename = calloc(strlen(tmt) + strlen(book) + 1, 1);
    strcat(filename,flnm);
    strcat(filename,book);
    strcat(filename,tmt);
    strcat(filename,"csv");
    FILE* fth1 = fopen(filename,"w");
    list_st(rootS,fth1);
    FILE* fth2 = fopen("C:\\Users\\Timur\\Desktop\\Database\\Backups\\BackupsStudents.txt","a+");   //C:\Users\Timur\Desktop\Database\Backups
    fputs(filename,fth2);
    fputc('\n',fth2);
    fclose(fth1);
    fclose(fth2);
    printf("Backup saved\n");
}

void backup_out_st(){
    delfullfirst(rootS);
    printf("Choose file of backup\n");
    FILE* fth = fopen("C:\\Users\\Timur\\Desktop\\Database\\Backups\\BackupsStudents.txt","r");
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
    fth2 = fopen("C:\\Users\\Timur\\Desktop\\Database\\Databases\\Students.csv", "w");
    if (fth2 == NULL)
    {
        printf("Cannot open file %s \n", "Students.csv");
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

void base_to_stack(){
    FILE* fth1 = fopen("C:\\Users\\Timur\\Desktop\\Database\\Databases\\Students.csv","r");
    while(fgetc(fth1)!= EOF){
        fseek(fth1,-1,1);
        struct student_node* cont = (struct student_node*)malloc(sizeof(struct student_node));
        char* number = fdynstring(fth1,';');
        cont->surname = fdynstring(fth1,';');
        //printf("\n%s\n",cont->surname);
        cont->name = fdynstring(fth1,';');
        //printf("\n%s\n",cont->name);
        cont->patronym = fdynstring(fth1,';');
        //printf("\n%s\n",cont->patronym);
        cont->facility = fdynstring(fth1,';');
        //printf("\n%s\n",cont->facility);
        cont->department = fdynstring(fth1, '\n');
        //printf("\n%s\n",cont->department);
        add_first_st(rootS,number,cont);
    }
}


void exit_st(){
    if (rootS == NULL){
        //error
    }
    FILE* fth2 = fopen("C:\\Users\\Timur\\Desktop\\Database\\Databases\\Students.csv", "w");
    list_st(rootS,fth2);
    fclose(fth2);
    printf("\nStudents database saved and closed\n");
}



//----------func for command getter----------
void add_student(){
    struct student_node* temp = (struct student_node*)malloc(sizeof(struct student_node));
    printf("Type number of student's book:");
    char* number = dynstring('\n');
    printf("Type surname:");
    temp->surname = dynstring('\n');
    printf("Type name:");
    temp->name = dynstring('\n');
    printf("Type patronym:");
    temp->patronym = dynstring('\n');
    printf("Type facility:");
    temp->facility = dynstring('\n');
    printf("Type name of department:");
    temp->department = dynstring('\n');
    putchar('\n');
    add_first_st(rootS,number,temp);
}

void del_student(){
    printf("Type number of student: ");
    char* string = dynstring('\n');
    del_first_st(rootS,string);
}


void find_student(){
    printf("Type number of student: ");
    char* string = dynstring('\n');
    find_st(rootS,string);
}

void find_students_by_surname(){
    printf("Type surname of students: ");
    char* string = dynstring('\n');
    find_by_surname(root,string);
}
//----------func for command getter----------

// ------------------------------------------ Student database ------------------------------------------



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

void print_books_by_number(comnode* current, char* number) {
    if (current == NULL)
        return;
    comnode *temp = find_by_number(current, number);
    if (temp == NULL)
        return;
    printf("\n%d;%s;%s;%s\n", current->books->isbn, current->books->content->author,
           current->books->content->name_of_book, current->date);
    print_books_by_number(current->next, number);
}

void print_students_by_isbn(comnode* current, int isbn){
    if (current == NULL)
        return;
    comnode* temp = find_by_isbn(current, isbn);
    if (temp == NULL)
        return;
    printf("\n%s;%s;%s;%s\n", current->student->number, current->student->content->surname, current->student->content->name,current->student->content->department,current->date);
    print_students_by_isbn(current->next, isbn);
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
    FILE* fth1 = fopen("C:\\Users\\Timur\\Desktop\\Database\\Databases\\Communication.csv","r");
    if (fth1 == NULL)
        return ;
    while(fgetc(fth1)!= EOF){
        fseek(fth1,-1,1);
        add_first_com(rootC,atoi(fdynstring(fth1,';')),fdynstring(fth1,';'),fdynstring(fth1,'\n'));
        fclose(fth1);
    }
}


void exit_com(){
    FILE* fth = fopen("C:\\Users\\Timur\\Desktop\\Database\\Databases\\Communications.csv","w+");
    list_com(rootC,fth);
    fclose(fth);
    //printf("StudentLibrary database saved and closed");
}

// ------------------------------------------------ Communication ------------------------------------------------


#endif //UNTITLED_LIBRARY_H
