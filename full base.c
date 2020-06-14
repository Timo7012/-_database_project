#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


// ---------------------------------------- Main Functions ----------------------------------------


void help() {
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
};

void error_code (int a){

    switch  (a) {
        case  1: printf("ERROR: File not be opened\n"); exit(0);
        case  2: printf("ERROR: File not indicated\n"); help(); exit(0);
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
        default: printf("ERROR: Fatal error\n"); exit(0);
    }
}

char* timeinf(){
    const time_t timer = time(NULL);
    char* tm =(char*)malloc(21*sizeof(char));
    struct tm* timeinf = localtime(&timer);
    strftime (tm,21,"%d_%m_%Y_%H.%M.%S.",timeinf);
    //printf("%s\n",buffer);
    return tm;
}


void clear_xnode_st(xnode* node);
void add_st(xnode* current,char* number,struct student_node* content);
void add_first_st(xnode* current,char* number, struct student_node* content);
void add_student();
void del_st();
void del_first_st(xnode* current,char* number);
void delfull_st(xnode* current);
void delfullfirst(xnode* current);
void base_out_st(xnode* current,FILE* fth);
void list_st(xnode* current,FILE* fth);
xnode* find_st(xnode* current,char* number);
xnode* find_by_surname(xnode* current,char* surname);
xnode* find_edit_st(xnode* current,char* number);
void edit_student_st();
void backup_st();
void backup_out_st();
void base_to_stack()




void command_getter_library(){
    printf("Please enter the command\n");
    char* string = dynsting('/n');
    if(!strcmp(string,"help")){help();command_getter_library();}
    else if (!strcmp(string,"add_book")){add_book();command_getter_library();}
    else if (!strcmp(string,"del_book")){del_book();command_getter_library();}
    else if (!strcmp(string,"get_book")){get_book();command_getter_library();}
    else if (!strcmp(string,"bring_book")){bring_book();command_getter_library();}
    else if (!strcmp(string,"list_books")){list_books();command_getter_library();}
    else if (!strcmp(string,"change_count_book_isbn")){change_count_book_isbn();command_getter_library();}
    else if (!strcmp(string,"backup_library")){backup_library();command_getter_library();}
    else if (!strcmp(string,"open_backup_library")){open_backup_library();command_getter_library();}
    else if (!strcmp(string,"exit_library_db")){exit_library_db();}
    else {error_code(20);}
}

void command_getter_student(){
    printf("\nPlease enter the command\n");
    char* string = dynsting('/n');
    if (!strcmp(string,"add_student")){add_student();command_getter_student();}
    else if (!strcmp(string,"del_student")){del_student();command_getter_student();}
    else if (!strcmp(string,"find_student")){find_student();command_getter_student();}
    else if (!strcmp(string,"find_students_by_surname")){find_students_by_surname();command_getter_student();}
    else if (!strcmp(string,"list_students")){list_students();command_getter_student();}
    else if (!strcmp(string,"change_count_book_isbn")){change_count_book_isbn();command_getter_student();}
    else if (!strcmp(string,"backup_student")){backup_student();command_getter_student();}
    else if (!strcmp(string,"open_backup_student")){open_backup_student();command_getter_student();}
    else if (!strcmp(string,"exit_student_db")){exit_student_db();}
    else {error_code(20);}
}

FILE* open_file(const char* argv[]){
    FILE* file_thread;
    if ((file_thread = (argv[0],"r");)==NULL) {
        error_code(1);
    }
}

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





int main() {


}
