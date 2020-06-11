#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>

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

typedef struct node snode;

snode* root = NULL;

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
    string[l] = '\n';
    return string;
}

void clear_snode_st(snode* node){
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
    const time_t timer = time(NULL) + 3600*3;
    char* tm =(char*)malloc(20*sizeof(char));
    struct tm* timeinf = localtime(&timer);
    strftime (tm,20,"%d.%m.%Y %X.",timeinf);
    //printf("%s\n",buffer);
    return tm;
}


void add(snode* current,char* number,struct student_node* content){
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
        if (strcmp(number,current->number)){
            add(current->next, number, content);
        } else {
            current->content = content;
        }
    }
}

void add_first(snode* current,char* number, struct student_node* content){
    if (current == NULL){
        root = (snode*)malloc(sizeof(snode));
        root->number = number;
        root->next = NULL;
        root->content = content;
    } else if (strcmp(number,current->number) < 0){
        snode* nde = (snode*)malloc(sizeof(snode));
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

void del(snode* current,char* number){
    if (strcmp(number,current->next->number)){
        del(current->next,number);
    }
    snode* temp = current->next;
    current->next = current->next->next;
    free(temp);
}

void del_first(snode* current,char* number){
    if(strcmp(current->number,number)){
        del(current,number);
    } else {
        snode* temp = current->next;
        free(current);
        root = temp;
    }
}

void list(snode* current,FILE* fth){
    if (current == NULL){
        return;
    }
    if (fth == NULL){
        return; //error
    }
    fprintf(fth,"%s;",current->number);
    fprintf(fth,"%s;",current->content->name);
    fprintf(fth,"%s;",current->content->surname);
    fprintf(fth,"%s;",current->content->patronym);
    fprintf(fth,"%s;",current->content->facility);
    fprintf(fth,"%s\n",current->content->department);
    list(current->next, fth);
}

void base_out(snode* current){
    fprintf(stdout,"%s;",current->number);
    fprintf(stdout,"%s;",current->content->name);
    fprintf(stdout,"%s;",current->content->surname);
    fprintf(stdout,"%s;",current->content->patronym);
    fprintf(stdout,"%s;",current->content->facility);
    fprintf(stdout,"%s\n",current->content->department);
};

snode* find(snode* current,char* number){
    if (current == NULL){
        return NULL; //error
    }
    if (!strcmp(number,current->number)){
        base_out(current);
    }
    return find(current->next,number);
}

snode* find_by_surname(snode* current,char* surname){
    if (current == NULL){
        return NULL; //error
    }
    if (!(strcmp(surname ,current->content->surname))){
        base_out(current);
    }
    return find_by_surname(current->next, surname);
}



void edit_book(){
    printf("Welcome to Edit Menu\n");
    printf("write:\n");
    printf("number\n");
    printf("name of column\n");
    printf("value\n");
    char* number= dynstring('\n');
    char* cell = dynstring('\n');
    char* value = dynstring('\n');
    snode* curr=find(root,number);
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
    char* book = "book_";
    char* flnm = "C:\\Users\\Timur\\Desktop\\Database\\Backups\\";
    char* filename = calloc(strlen(tmt) + strlen(book) + 1, 1);
    strcat(filename,flnm);
    strcat(filename,book);
    strcat(filename,tmt);
    FILE* fth1 = fopen(filename,"w+");
    list(root,fth1);
    FILE* fth2 = fopen("C:\\Users\\Timur\\Desktop\\Database\\Backups\\Backups.txt","a+");
    fputs(filename,fth2);
    fputc('\n',fth2);
    fclose(fth1);
    fclose(fth2);
    printf("Backup saved");
}

void backup_out(){
    printf("Choose file of backup");
    FILE* fth = fopen("C:\\Users\\Timur\\Desktop\\Database\\Backups\\Backups.txt","r");
    if (fth == NULL){
        //error
    }
    char ch;
    while((ch = getc(fth)) == EOF){
        putchar(ch);
    }
    fclose(fth);
    char* string = dynstring('\n');
    char* way = "C:\\Users\\Timur\\Desktop\\Backups\\";
    char* str_bck = calloc(strlen(way) + strlen(string) + 1, 1);
    strcat(str_bck,way);
    strcat(str_bck,string);
    FILE *fth1, *fth2;
    // Open one file for reading
    fth1 = fopen(str_bck, "r");
    if (fth1 == NULL)
    {
        printf("Cannot open file %s \n", str_bck);
        //error(0);
    }

    // Open another file for writing
    fth2 = fopen("C:\\Users\\Timur\\Desktop\\Database\\Students.csv", "w");
    if (fth2 == NULL)
    {
        printf("Cannot open file %s \n", "Students.csv");
        //error();
    }
    // Read contents from file
    while ((ch = fgetc(fth1)) != EOF)
    {
        fputc(ch, fth2);
    }
    fputc(EOF,fth2);
    printf("\nBackup successful recover");
    fclose(fth1);
    fclose(fth2);
}





int main(){

    struct student_node* cont = (struct student_node*) malloc(sizeof(struct student_node));
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
    cont -> name= "ktimo" ;
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
    add_first(root,"19U255",cont);
    list(root,stdout);
    putchar('\n');
    del_first(root,"19U254");
    list(root,stdout);
    putchar('\n');
    find(root,"19U251");
    putchar('\n');
    find_by_surname(root,"mahmudov");
}

