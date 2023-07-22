#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <donation_management.h>
#include <event_management.h>
#include <material_management.h>
#include <ticket_distribution.h>
#include <user_management.h>

// Array to store all users
User* users[MAX_USERS];
int userCount = 0;

// Function to create a new user
User* createUser(int type, char* name) {
    User* newUser = (User*)malloc(sizeof(User));
    if (newUser == NULL) {
        printf("Error: Unable to allocate memory for new user.\n");
        return NULL;
    }
    newUser->type = type-1;
    strncpy(newUser->name, name, sizeof(newUser->name) - 1);
    return newUser;
}

// Function to register a new user
void registerUser(int type, char* name, char* password) {
    if (type < ALUMNI || type > OTHER) {
        UserhandleError("Invalid user type. Please choose a number from 1 to 6.");
        return;
    }
    if (userCount >= MAX_USERS) {
        UserhandleError("User limit reached.");
        return;
    }
    User* newUser = createUser(type, name);
    strncpy(newUser->password, password, sizeof(newUser->password) - 1);
    users[userCount++] = newUser;
}

// Function to log in a user
void loginUser(char* name, char* password) {
    for (int i = 0; i < userCount; i++) {
        if (strcmp(users[i]->name, name) == 0 && strcmp(users[i]->password, password) == 0) {
            users[i]->isLoggedIn = 1;
            printf("User %s logged in.\n", name);
            return;
        }
    }
    UserhandleError("Invalid username or password.");
}

// Function to check a user's permissions
void checkPermissions(User* user) {
    if (user == NULL) {
        printf("Error: User does not exist.\n");
        return;
    }
    switch (user->type) {
        case ALUMNI:
            printf("User %s (Alumni) can visit campus, participate in activities, and receive souvenirs.\n", user->name);
            break;
        case STUDENT:
            printf("User %s (Student) can propose anniversary-themed activities.\n", user->name);
            break;
        case TEACHER:
            printf("User %s (Teacher) can participate in activities.\n", user->name);
            break;
        case ADMIN:
            printf("User %s (Admin) can approve applications and manage resources.\n", user->name);
            break;
        case STAFF:
            printf("User %s (Staff) can participate in activities.\n", user->name);
            break;
        case OTHER:
            printf("User %s (Other) has limited permissions.\n", user->name);
            break;
        default:
            printf("Error: Unknown user type.\n");
            break;
    }
}

// Check permission for each module
int canAccessTicketModule(User* user) {
    // All user types can access the ticket module
    return 1;
}

int canAccessDonationModule(User* user) {
    // Alumni, Admin, and Staff can access the donation module
    return user->type == ALUMNI || user->type == ADMIN || user->type == STAFF;
}

int canAccessEventModule(User* user) {
    // All user types except Alumni and Other can access the event module
    return user->type != ALUMNI && user->type != OTHER;
}

int canAccessMaterialModule(User* user) {
    // Only Admin and Staff can access the material module
    return user->type == ADMIN || user->type == STAFF;
}

// Function to handle errors
void UserhandleError(char* errorMessage) {
    printf("Error: %s\n", errorMessage);
}

// Function to show system modules to the logged-in user based on their permissions
void showSystemModules(User* user) {
    if (user == NULL || !user->isLoggedIn) {
        printf("Error: User is not logged in.\n");
        return;
    }

    printf("Welcome, %s. You can access the following modules:\n", user->name);

    if (canAccessTicketModule(user)) {
        printf("%d. Ticket Distribution\n", TICKET_MODULE);
    }

    if (canAccessDonationModule(user)) {
        printf("%d. Donation Management\n", DONATION_MODULE);
    }

    if (canAccessEventModule(user)) {
        printf("%d. Event Management\n", EVENT_MODULE);
    }

    if (canAccessMaterialModule(user)) {
        printf("%d. Material Management\n", MATERIAL_MODULE);
    }
}

// Function to handle selected module
void handleSelectedModule(int module, User* user) {
    switch (module) {
        case TICKET_MODULE:
            if (canAccessTicketModule(user)) {
                TicketUserInterface();
            } else {
                UserhandleError("Invalid module selection.");
            }
            break;
        case DONATION_MODULE:
            if (canAccessDonationModule(user)) {
                DonationUserInterface();
            } else {
                UserhandleError("Invalid module selection.");
            }
            break;
        case EVENT_MODULE:
            if (canAccessEventModule(user)) {
                EventUserInterface();
            } else {
                UserhandleError("Invalid module selection.");
            }
            break;
        case MATERIAL_MODULE:
            if (canAccessMaterialModule(user)) {
                MaterialUserInterface();
            } else {
                UserhandleError("Invalid module selection.");
            }
            break;
        default:
            UserhandleError("Invalid module selection.");
            break;
    }
}

// Function to clear the input buffer
void UserclearInputBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) { }
}

void userInterface() {
    int option, type, module;
    char name[50], password[50];
    User* currentUser = NULL;

    while (1) {
        printf("Welcome to Tsinghua University Campus Celebration Information Portal! Please select an option:\n");
        printf("1. Register\n");
        printf("2. Login\n");
        printf("3. Check Permissions\n");
        printf("4. Access System Modules\n");
        printf("5. Exit\n");

        if (scanf("%d", &option) != 1) {
            printf("Invalid input. Please enter a number.\n");
            UserclearInputBuffer();
            continue;
        }

        switch(option) {
            case 1:
                printf("Enter user type (1: Alumni, 2: Student, 3: Teacher, 4: Admin, 5: Staff, 6: Other): ");
                if (scanf("%d", &type) != 1) {
                    printf("Invalid input. Please enter a number.\n");
                    UserclearInputBuffer();
                    continue;
                }
                printf("Enter user name: ");
                scanf("%s", name);
                printf("Enter password: ");
                scanf("%s", password);
                registerUser(type, name, password);
                break;
            case 2:
                printf("Enter user name: ");
                scanf("%s", name);
                printf("Enter password: ");
                scanf("%s", password);
                loginUser(name, password);
                for (int i = 0; i < userCount; i++) {
                    if (users[i]->isLoggedIn && strcmp(users[i]->name, name) == 0) {
                        currentUser = users[i];
                    }
                }
                break;
            case 3:
                if (currentUser != NULL) {
                    checkPermissions(currentUser);
                } else {
                    printf("No user is currently logged in.\n");
                }
                break;
            case 4:
                if (currentUser != NULL) {
                    showSystemModules(currentUser);
                    printf("Select a module: ");
                    if (scanf("%d", &module) != 1) {
                        printf("Invalid input. Please enter a number.\n");
                        UserclearInputBuffer();
                        continue;
                    }
                    handleSelectedModule(module, currentUser);
                } else {
                    printf("No user is currently logged in.\n");
                }
                break;
            case 5:
                printf("Exiting...\n");
                return;
            default:
                UserhandleError("Invalid option.");
        }
    }
}

int main() {
    userInterface();
    return 0;
}
