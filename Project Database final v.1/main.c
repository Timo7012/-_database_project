#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "C:\Users\Timur\Desktop\ICT\Project Database final v.1\main_functions\main_functions.h"
#include "C:\Users\Timur\Desktop\ICT\Project Database final v.1\lib_database\library.h"
#include "C:\Users\Timur\Desktop\ICT\Project Database final v.1\st_database\st_database.h"
#include "C:\Users\Timur\Desktop\ICT\Project Database final v.1\auth\auth.h"
#include "C:\Users\Timur\Desktop\ICT\Project Database final v.1\logger\logger.h"

void help(int rights) {
    if(rights & 2) {
        printf("*Commands for library database*\n");
        printf("_________________________________________________________________\n");
        printf("add_book                                   Add book to library\n");
        printf("del_book                                   Delete book from library\n");
        printf("get_book                                   Get book from library and adds book to student\n");
        printf("bring_book                                 Adds count of book to library and delete book from student\n");
        printf("list_books                                 Shows all books in library\n"); // sorted ny ISBN
        printf("change_count_book_isbn                     Change count of book to library by ISBN \n");
        printf("backup_library                             Save the data of library in backup file\n");
        printf("open_backup_library                        Open backup version of library\n");
        printf("exit_library_db                            Save and close file of library\n\n");
        printf("_________________________________________________________________\n\n");
    }
    if(rights & 1) {
        printf("*Commands for student database*\n");
        printf("_________________________________________________________________\n");
        printf("add_student                                Add student to database\n");
        printf("del_student                                Delete student from database\n");
        printf("find_student                               Get student from database by number\n");
        printf("find_students_by_surname                   Get student from database by surname\n");
        printf("list_students                              Shows all students in database\n"); // sorted ny number
        printf("edit_student                               Change count of book to library by ISBN \n");
        printf("backup_student                             Save the data of students database in backup file\n");
        printf("open_backup_student                        Open backup version of students database\n");
        printf("exit_student_db                            Save and close file of student database\n\n");
        printf("_________________________________________________________________\n");
    }
};

int command_getter(int rights) {
    printf("Please enter the command\n");
    char *string = dynstring('\n');
    if(rights & 2){
        if (!strcmp(string, "add_book")) {
            add_book();
            return 1;
        } else if (!strcmp(string, "del_book")) {
            del_book();
            return 1;
        } else if (!strcmp(string, "get_book")) {
            get_book();
            return 1;
        } else if (!strcmp(string, "bring_book")) {
            bring_book();
            return 1;
        } else if (!strcmp(string, "list_books")) {
            list_lb();
            return 1;
        } else if (!strcmp(string, "change_count_book_isbn")) {
            change_count_by_isbn();
            return 1;
        } else if (!strcmp(string, "backup_library")) {
            backup_lb();
            return 1;
        } else if (!strcmp(string, "open_backup_library")) {
            backup_out_lb();
            return 1;
        } else if (!strcmp(string, "find_book")) {
            find_lb();
            return 1;
        } else if (!strcmp(string, "find_by_author")) {
            find_by_author();
            return 1;
        } else if (!strcmp(string, "exit_library_db")) {
            exit_lb();
            return 1;
        }
    }
    if(rights & 1) {
        if (!strcmp(string, "add_student")) {
            add_student();
            return 1;
        } else if (!strcmp(string, "del_student")) {
            del_student();
            return 1;
        } else if (!strcmp(string, "find_student")) {
            find_student();
            return 1;
        } else if (!strcmp(string, "find_students_by_surname")) {
            find_students_by_surname();
            return 1;
        } else if (!strcmp(string, "list_students")) {
            list_st();
            return 1;
        } else if (!strcmp(string, "edit information about student")) {
            edit_student();
            return 1;
        } else if (!strcmp(string, "backup_student")) {
            backup_st();
            return 1;
        } else if (!strcmp(string, "open_backup_student")) {
            backup_out_st();
            return 1;
        } else if (!strcmp(string, "exit_student_db")) {
            exit_lb();
            return 1;
        }
    }
    error_code(20);
}
int main() {



    while (command_getter());


    return 0;
}
