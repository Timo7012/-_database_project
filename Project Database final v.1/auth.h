#ifndef AUTH_LIBRARY_H
#define AUTH_LIBRARY_H

#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>



int auth(char ** log) {
    FILE *fth = fopen("C:\\Users\\Timur\\Desktop\\Database\\Databases\\Accounts.csv", "r");
    if (fth == NULL) {
        //error
        return 0;
    }
    char rights = 0;
    printf("-----------Authorizathion-----------\n");
    printf("Enter your login: ");
    char *login = dynstring('\n');
    printf("\nEnter your password: ");
    char *password = dynstring('\n');
    char temp = '0';
    while (temp != EOF) {
        int i = 0;
        for (; (temp = fgetc(fth)) != ';' && login[i] != '\0' && login[i] == temp; ++i);
        if (login[i] == '\0' && temp == ';') {
            i = 0;
            for (; (temp = fgetc(fth)) != ';' && password[i] != '\0' && password[i] == temp; ++i);
            if (password[i] == '\0' && temp == ';') {
                rights = (fgetc(fth) - '0') << 1;
                fgetc(fth);
                rights += fgetc(fth) - '0';
                //printf("\nrights: %d ", rights);
                break;
            } else {
                error_code(4);
            }
        } else {
            while ((temp = fgetc(fth)) != '\n' && temp != EOF);
        }
    }
    if (!rights) {
        error_code(23);
    } else {printf("\nGOD\n");}
    fclose(fth);
    free(password);
    *log = login;
    return rights;
}



#endif //AUTH_LIBRARY_H
