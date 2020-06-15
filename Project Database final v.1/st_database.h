#ifndef ST_DATABASE_LIBRARY_H
#define ST_DATABASE_LIBRARY_H

#pragma once
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <time.h>


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



void del_st(snode* current,char* number){
    if (strcmp(number,current->next->number)){
        del_st(current->next,number);
    }
    snode* temp = current->next;
    current->next = current->next->next;
    free(temp);
}

void del_first_st(snode* current,char* number){
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
    list_st(rootS,".\\students.csv")
    fclose();
    fclose();
    printf("Students database saved and closed");
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


#endif //ST_DATABASE_LIBRARY_H
