#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <time.h>

struct student_node{
    char* surname;
    char* name;
    char* patronym;
    char* facility;
    char* department ;
} ;

struct node{
    char* number;
    struct student_node* content;
    struct node* next;
};

typedef struct node xnode;

xnode* root = NULL;

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

void clear_xnode_st(xnode* node){
    free(node->content->surname);
    free(node->content->name);
    free(node->content->patronym);
    free(node->content->facility);
    free(node->content->department);
    free(node->number);
    free(node->content);
    free(node);
}



char* timeinf(){
    const time_t timer = time(NULL);
    char* tm =(char*)malloc(21*sizeof(char));
    struct tm* timeinf = localtime(&timer);
    strftime (tm,21,"%d_%m_%Y_%H.%M.%S.",timeinf);
    //printf("%s\n",buffer);
    return tm;
}


void add(xnode* current,char* number,struct student_node* content){
    if (current->next == NULL ){
        current->next = (xnode*)malloc(sizeof(xnode));
        current->next->number = number;
        current->next->next = NULL;
        current->next->content = content;
    } else if(strcmp(number,current->next->number)<0){
        xnode* temp = (xnode *)malloc(sizeof(xnode));
        temp->number=number;
        temp->content = content;
        temp->next = current->next;
        current->next = temp;
    } else {
        if (strcmp(number,current->next->number)){
            add(current->next, number, content);
        } else {
            current->content = content;
        }
    }
}

void add_first(xnode* current,char* number, struct student_node* content){
    if (current == NULL){
        root = (xnode*)malloc(sizeof(xnode));
        root->number = number;
        root->next = NULL;
        root->content = content;
    } else if (strcmp(number,current->number) < 0){
        xnode* nde = (xnode*)malloc(sizeof(xnode));
        nde->number = number;
        nde->next = root;
        nde->content = content;
        root = nde;
    } else if (strcmp(number,current->number)){
        add(current, number, content);
    } else {
        current->content = content;
    }
}

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
    add_first(root,number,temp);
}

void del(xnode* current,char* number){
    if (strcmp(number,current->next->number)){
        del(current->next,number);
    }
    xnode* temp = current->next;
    current->next = current->next->next;
    free(temp);
}

void del_first(xnode* current,char* number){
    if(strcmp(current->number,number)){
        del(current,number);
    } else {
        xnode* temp = current->next;
        free(current);
        root = temp;
    }
}


void delfull(xnode* current){
    if (current == NULL){
        return;
    }
    xnode* next = current->next;
    clear_xnode_st(current);
    delfull(next);
}
void delfullfirst(xnode* current){
    delfull(current);
    root = NULL;
}

void base_out(xnode* current,FILE* fth){
    fprintf(fth,"%s;",current->number);
    fprintf(fth,"%s;",current->content->surname);
    fprintf(fth,"%s;",current->content->name);
    fprintf(fth,"%s;",current->content->patronym);
    fprintf(fth,"%s;",current->content->facility);
    fprintf(fth,"%s\n",current->content->department);
};

void list(xnode* current,FILE* fth){
    if (current == NULL){
        return;
    }
    if (fth == NULL){
        return; //error
    }
    //base_out(current,fth);
    fprintf(fth,"%s;",current->number);
    fprintf(fth,"%s;",current->content->surname);
    fprintf(fth,"%s;",current->content->name);
    fprintf(fth,"%s;",current->content->patronym);
    fprintf(fth,"%s;",current->content->facility);
    fprintf(fth,"%s\n",current->content->department);
    list(current->next, fth);
}


xnode* find(xnode* current,char* number){
    if (current == NULL){
        return NULL; //error
    }
    if (!strcmp(number,current->number)){
        base_out(current,stdout);

    }
    return find(current->next,number);
}

xnode* find_edit(xnode* current,char* number){
    if (current == NULL){
        return NULL; //error
    }
    if (!strcmp(number,current->number)){
        return current;
    }
    return find_edit(current->next,number);
}

xnode* find_by_surname(xnode* current,char* surname){
    if (current == NULL){
        return NULL; //error
    }
    if (!(strcmp(surname ,current->content->surname))){
        base_out(current,stdout);
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
    xnode* curr = find_edit(root,number);
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



void backup(){
    char* tmt = timeinf();
    char* book = "students_";
    char* flnm = "C:\\Users\\Timur\\Desktop\\Database\\Backups\\";
    char* filename = calloc(strlen(tmt) + strlen(book) + 1, 1);
    strcat(filename,flnm);
    strcat(filename,book);
    strcat(filename,tmt);
    strcat(filename,"csv");
    FILE* fth1 = fopen(filename,"w");
    list(root,fth1);
    FILE* fth2 = fopen("C:\\Users\\Timur\\Desktop\\Database\\Backups\\BackupsStudents.txt","a+");   //C:\Users\Timur\Desktop\Database\Backups
    fputs(filename,fth2);
    fputc('\n',fth2);
    fclose(fth1);
    fclose(fth2);
    printf("Backup saved\n");
}

void backup_out(){
    delfullfirst(root);
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
        add_first(root,number,cont);
    }
}




int main(){
    // backup_out();



    /*struct student_node* cont = (struct student_node*) malloc(sizeof(struct student_node));
    cont -> name= "timo" ;
    cont -> surname="mahmudov";
    cont -> patronym = "naz";
    cont -> department="IU";
    cont -> facility="IU4";
    add_first(root,"19U254",cont);
    cont = (struct student_node*) malloc(sizeof(struct student_node));
    cont -> name= "ktimo" ;
    cont -> surname="mahmudov";
    cont -> patronym = "naz";
    cont -> department="IU";
    cont -> facility="IU4";
    cont = (struct student_node*) malloc(sizeof(struct student_node));
    add_first(root,"19U251",cont);
    cont -> name = "ktimo" ;
    cont -> surname="mahmudov";
    cont -> patronym = "naz";
    cont -> department="IU";
    cont -> facility="IU4";
    add_first(root,"19U256",cont);
    cont = (struct student_node*) malloc(sizeof(struct student_node));
    cont -> name= "ktimo" ;
    cont -> surname="mahmudov";
    cont -> patronym = "naz";
    cont -> department="IU";
    cont -> facility="IU4";
    add_first(root,"19U255",cont);*/
      //add_student();
      //backup();
      //list(root,stdout);
      //backup_out();
      //list(root,stdout);
      //edit_student();
      //list(root,stdout);
    //list(root,stdout);
    //delfullfirst(root);
    //del_first(root,"19U251");
    //list(root,stdout);
    //backup();
    //putchar('\n');
    //find(root,"19U256");
    //putchar('\n');
    //find_by_surname(root,"mahmudov");
    //backup();
}
