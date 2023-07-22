#ifndef CAMPUS_CELEBRATION_H
#define CAMPUS_CELEBRATION_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <donation_management.h>
#include <event_management.h>
#include <material_management.h>
#include <ticket_distribution.h>

#define ALUMNI 0
#define STUDENT 1
#define TEACHER 2
#define ADMIN 3
#define STAFF 4
#define OTHER 5

#define TICKET_MODULE 1
#define DONATION_MODULE 2
#define EVENT_MODULE 3
#define MATERIAL_MODULE 4

#define MAX_USERS 1000

typedef struct {
    int type;
    char name[50];
    char password[50];
    int isLoggedIn;
} User;

extern User* users[MAX_USERS];
extern int userCount;

User* createUser(int type, char* name);
void registerUser(int type, char* name, char* password);
void loginUser(char* name, char* password);
void checkPermissions(User* user);
int canAccessTicketModule(User* user);
int canAccessDonationModule(User* user);
int canAccessEventModule(User* user);
int canAccessMaterialModule(User* user);
void UserhandleError(char* errorMessage);
void showSystemModules(User* user);
void handleSelectedModule(int module, User* user);
void UserclearInputBuffer();
void userInterface();

#endif /* CAMPUS_CELEBRATION_H */
