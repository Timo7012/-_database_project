#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "C:\Users\Timur\Desktop\ICT\Project Database final v.1\main_functions\main_functions.h"
#include "C:\Users\Timur\Desktop\ICT\Project Database final v.1\logger\logger.h"
#include "C:\Users\Timur\Desktop\ICT\Project Database final v.1\auth\auth.h"
#include "C:\Users\Timur\Desktop\ICT\Project Database final v.1\untitled\lib_stu_com.h"

void help(int rights) {
    if(rights & 1) {
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
        printf("exit_library_db                            Save and close file of library\n");
        printf("_________________________________________________________________\n\n");
    }
    if(rights & 2) {
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
        printf("exit_student_db                            Save and close file of student database\n");
        printf("_________________________________________________________________\n");
    }
};

void command_get_by_rights(int rights){
    if (rights == 1){
        printf("\n Enter_lib                Enter the library database\nExit                     Exit from programme\n");
    }
    else if (rights == 2){
        printf("\n Enter_stu                Enter the student database\nExit                     Exit from programme\n");
    }
    else if(rights == 3){
        printf("\nEnter_lib                Enter the library database\nEnter_stu               Enter the student database\nExit                     Exit from programme\n");
    }
    else{
        error_code(23);
    }
}

int com_get(int rights){
    char *string = dynstring('\n');
    if (!strcmp(string, "Enter_lib") && (rights & 1)){
        help(rights & 1);
        return 1;
    }
    else if (!strcmp(string, "Enter_stu") && (rights & 2)){
        help(rights & 2);
        return 1;
    }
    else if (!strcmp(string, "Exit") && rights){
        return 0;
    }

}



int command_getter(int rights,char* log) {
    printf("Please enter the command\n");
    char *string = dynstring('\n');
    if(rights & 2){
        if (!strcmp(string, "add_book")) {
            add_book();
            logger_book(1,log);
            return 1;
        } else if (!strcmp(string, "del_book")) {
            del_book();
            logger_book(2,log);
            return 1;
        } else if (!strcmp(string, "get_book")) {
            give_book_lb();
            return 1;
        } else if (!strcmp(string, "bring_book")) {
            bring_book_lb();
            return 1;
        } else if (!strcmp(string, "list_books")) {
            list_lb(root,stdout);
            logger_book(4,log);
            return 1;
        } else if (!strcmp(string, "change_count_book_isbn")) {
            change_count_by_isbn();
            logger_book(13,log);
            return 1;
        } else if (!strcmp(string, "backup_library")) {
            backup_lb();
            logger_book(7,log);
            return 1;
        } else if (!strcmp(string, "open_backup_library")) {
            backup_out_lb();
            logger_book(8,log);
            return 1;
        } else if (!strcmp(string, "find_book")) {
            find_book();
            logger_book(14,log);
            return 1;
        } else if (!strcmp(string, "find_by_author")) {
            find_by_author();
            logger_book(5,log);
            return 1;
        } else if (!strcmp(string, "exit_library_db")) {
            exit_lb();
            logger_book(15,log);
            return 0;
        }
    }
    if(rights & 1) {
        if (!strcmp(string, "add_student")) {
            add_student();
            logger_student(1,log);
            return 1;
        } else if (!strcmp(string, "del_student")) {
            del_student();
            logger_student(2,log);
            return 1;
        } else if (!strcmp(string, "find_student")) {
            find_student();
            logger_student(9,log);
            return 1;
        } else if (!strcmp(string, "find_students_by_surname")) {
            find_students_by_surname();
            logger_student(5,log);
            return 1;
        } else if (!strcmp(string, "list_students")) {
            list_st(rootS,stdout);
            logger_student(4,log);
            return 1;
        } else if (!strcmp(string, "edit information about student")) {
            edit_student();
            logger_student(3,log);
            return 1;
        } else if (!strcmp(string, "backup_student")) {
            backup_st();
            logger_student(6,log);
            return 1;
        } else if (!strcmp(string, "open_backup_student")) {
            backup_out_st();
            logger_student(7,log);
            return 1;
        } else if (!strcmp(string, "exit_student_db")) {
            exit_st();
            logger_student(8,log);
            return 0;
        }
    }
    error_code(20);
}
int main() {
    char ** log = (char**)malloc(sizeof(char*));
    int rights = auth(log);
    logger_book(0,*log);
    base_to_stack();
    base_to_stack_com();
    base_to_stack_lb();
    command_get_by_rights(rights);
    while(com_get(rights)) {
        while (command_getter(rights,*log)){}
        command_get_by_rights(rights);
    }
    logger_book(12,*log);
    exit_com();
    return 0;
}
