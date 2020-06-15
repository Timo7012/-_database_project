#ifndef MAIN_FUNCTIONS_LIBRARY_H
#define MAIN_FUNCTIONS_LIBRARY_H

#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <time.h>


char* timeinf_file(){
    const time_t timer = time(NULL);
    char* tm =(char*)malloc(21*sizeof(char));
    struct tm* timeinf = localtime(&timer);
    strftime (tm,21,"%d_%m_%Y_%H.%M.%S.",timeinf);
    //printf("%s\n",buffer);
    return tm;
}

char* timeinf(){
    const time_t timer = time(NULL);
    char* tm =(char*)malloc(21*sizeof(char));
    struct tm* timeinf = localtime(&timer);
    strftime (tm,21,"%d_%m_%Y %X.",timeinf);
    //printf("%s\n",buffer);
    return tm;
}

/*
FILE* open_file(const char* argv[]){
    FILE* file_thread;
    if ((file_thread = (argv[0],"r");)==NULL) {
        error_code(1);
    }
}
*/

char* fdynstring(FILE* fp, char ch){
    int l = 0;
    char buf;
    for(;(buf = fgetc(fp)) != ch && buf != EOF; ++l);
    if (buf == EOF)
        fseek(fp, -1*(l), SEEK_CUR);
    else if (buf =='\n')
        fseek(fp, -1*(l+2), SEEK_CUR);
    else
        fseek(fp, -1*(l+1), SEEK_CUR);
    char* a = (char*)malloc((l + 1) * sizeof(char));
    for (int i = 0; i < l; ++i)
        a[i]=fgetc(fp);
    a[l] = '\0';
    if (buf != EOF)
        fgetc(fp);
    else
        fseek(fp, -1, 2);
    return a;
}

char* dynstring(char c) {
    int l = 0;
    int size = 1;
    char *string = (char*) malloc(size * sizeof(char));
    char ch = getchar();
    while (ch != c) {
        string[(l)++] = ch;
        if (l >= size) {
            size *= 2;
            string = (char*) realloc(string, size * sizeof(char));
        }
        ch = getchar();
    }
    string[l] = '\0';
    return string;
}

void error_code (int a){

    switch  (a) {
        case  1: printf("ERROR: File not be opened\n"); exit(0);
        case  2: printf("ERROR: File not indicated\n"); exit(0);
        case  3: printf("ERROR: Logger error\n"); exit(0);
        case  4: printf("ERROR: Wrong login or password\n"); exit(0);
        case  5: printf("ERROR: File not be opened\n"); exit(0);
        case  6: printf("ERROR: Can't add the book\n"); exit(0);
        case  7: printf("ERROR: Can't delete the book\n"); exit(0);
        case  8: printf("ERROR: Can't get the book\n"); exit(0);
        case  9: printf("ERROR: Can't bring the book\n"); exit(0);
        case 10: printf("ERROR: Can't change count of book \n"); exit(0);
        case 11: printf("ERROR: Can't create backup the library database \n"); exit(0);
        case 12: printf("ERROR: Can't open backup of library\n"); exit(0);
        case 13: printf("ERROR: Can't add the student\n"); exit(0);
        case 14: printf("ERROR: Can't delete the student\n"); exit(0);
        case 15: printf("ERROR: Can't find student by number\n"); exit(0);
        case 16: printf("ERROR: Can't find students by surname\n"); exit(0);
        case 17: printf("ERROR: Can't edit the student \n"); exit(0);
        case 18: printf("ERROR: Can't backup the students database \n"); exit(0);
        case 19: printf("ERROR: Can't open backup of students database \n"); exit(0);
        case 20: printf("ERROR: Enter wrong command\n"); exit(0);
        case 21: printf("ERROR: Number is already exists\n"); exit(0);
        case 22: printf("ERROR: ISBN is already exists\n"); exit(0);
        default: printf("ERROR: Fatal error\n"); exit(0);
    }
}

#endif //MAIN_FUNCTIONS_LIBRARY_H
