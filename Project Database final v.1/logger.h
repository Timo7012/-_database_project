#ifndef LOGGER_LIBRARY_H
#define LOGGER_LIBRARY_H

#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

void logger_book(int code, char* login){
    FILE* fth = fopen("C:\\Users\\Timur\\Desktop\\Database\\logger.log","a+");
    char* time = timeinf();
    fprintf(fth, "{\"time\" = %s\";\"login\" = \"%s\";\"operation\" = \"", time,login);
    switch (code) {
        case 0:  fputs("Entered in the system\"}",fth);  break; //Auth accepted
        case 1:  fputs("Add book to the library \"}",fth); break;
        case 2:  fputs("Delete's book from the library\"}",fth); break;
        case 3:  fputs("Edit's book in library\"}",fth); break;
        case 4:  fputs("Lists books\"}",fth); break;
        case 5:  fputs("Search books by author surname\"}",fth); break;
        case 6:  fputs("Change count of books by ISBN\"}",fth); break;
        case 7:  fputs("Backups the library\"}",fth); break;
        case 8:  fputs("Open library backup\"}",fth); break;
        case 9:  fputs("Exit from library\"}",fth); break;
        case 10: fputs("Get book from library\"}",fth); break;
        case 11: fputs("Bring book in library\"}",fth); break;
        case 12: fputs("User logged out\"}",fth); break;
        case 13: fputs("Change count of books\"}",fth); break;
        case 14: fputs("Search books by ISBN\"}",fth); break;
        case 15: fputs("Exit from the library\"}",fth);
        default:break;
    }
    fprintf(fth, "\n");
    free(time);
    fclose(fth);
}


void logger_student(int code, char* login){
    FILE* fth = fopen("C:\\Users\\Timur\\Desktop\\Database\\logger.log","a+");
    char* time = timeinf();
    fprintf(fth, "{\"time\" = %s\";\"login\" = \"%s\";\"operation\" = \"", time,login);
    switch (code) {
        case 1:  fputs("Add student in database \"}",fth); break;
        case 2:  fputs("Delete's student from database\"}",fth); break;
        case 3:  fputs("Edit's information about student in database\"}",fth); break;
        case 4:  fputs("Lists student by number of student book\"}",fth); break;
        case 5:  fputs("Search students by surname\"}",fth); break;
        case 6:  fputs("Backups the library\"}",fth); break;
        case 7:  fputs("Open library backup\"}",fth); break;
        case 8:  fputs("Exit from student database\"}",fth); break;
        case 9:  fputs("Search students by number\"}",fth); break;
        default:break;
    }
    fprintf(fth, "\n");
    free(time);
    fclose(fth);
}

#endif //LOGGER_LIBRARY_H
