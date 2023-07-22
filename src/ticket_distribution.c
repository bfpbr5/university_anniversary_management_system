#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ticket_distribution.h>

// Array to store all tickets
Ticket* tickets[TOTAL_TICKETS];
int ticketCount = 0;

// Array to store the count of tickets per type
int ticketsPerType[6] = {
    TOTAL_TICKETS * ALUMNI_RATIO,
    TOTAL_TICKETS * STUDENT_RATIO,
    TOTAL_TICKETS * TEACHER_RATIO,
    TOTAL_TICKETS * ADMIN_RATIO,
    TOTAL_TICKETS * STAFF_RATIO,
    TOTAL_TICKETS * OTHER_RATIO
};


// Function to create a new ticket
Ticket* createTicket(int type, char* holderName) {
    Ticket* newTicket = (Ticket*)malloc(sizeof(Ticket));
    if (newTicket == NULL) {
        printf("Error: Unable to allocate memory for new ticket.\n");
        return NULL;
    }
    newTicket->type = type-1;
    strncpy(newTicket->holderName, holderName, sizeof(newTicket->holderName) - 1);
    newTicket->isDistributed = 0;
    return newTicket;
}

// Function to distribute a ticket
void distributeTicket(Ticket* ticket) {
    if (ticket == NULL) {
        printf("Error: Ticket does not exist.\n");
        return;
    }
    ticket->isDistributed = 1;
    printf("Ticket has been distributed to %s.\n", ticket->holderName);
}

// Function to check the number of tickets available per type
void checkTicketsAvailability() {
    printf("Tickets available:\n");
    printf("Alumni: %d\n", ticketsPerType[ALUMNI]);
    printf("Student: %d\n", ticketsPerType[STUDENT]);
    printf("Teacher: %d\n", ticketsPerType[TEACHER]);
    printf("Admin: %d\n", ticketsPerType[ADMIN]);
    printf("Staff: %d\n", ticketsPerType[STAFF]);
    printf("Other: %d\n", ticketsPerType[OTHER]);
}

// Function to handle errors
void TickethandleError(char* errorMessage) {
    printf("Error: %s\n", errorMessage);
}

// Function to distribute tickets according to the distribution ratio
void distributeTickets(Ticket* tickets[]) {
    srand(time(NULL));
    int alumniTickets = TOTAL_TICKETS * ALUMNI_RATIO;
    int studentTickets = TOTAL_TICKETS * STUDENT_RATIO;
    int teacherTickets = TOTAL_TICKETS * TEACHER_RATIO;
    int adminTickets = TOTAL_TICKETS * ADMIN_RATIO;
    int staffTickets = TOTAL_TICKETS * STAFF_RATIO;
    int otherTickets = TOTAL_TICKETS * OTHER_RATIO;
    
    for (int i = 0; i < TOTAL_TICKETS; i++) {
        if (tickets[i]->type == ALUMNI && alumniTickets > 0) {
            distributeTicket(tickets[i]);
            alumniTickets--;
        } else if (tickets[i]->type == STUDENT && studentTickets > 0) {
            distributeTicket(tickets[i]);
            studentTickets--;
        } else if (tickets[i]->type == TEACHER && teacherTickets > 0) {
            distributeTicket(tickets[i]);
            teacherTickets--;
        } else if (tickets[i]->type == ADMIN && adminTickets > 0) {
            distributeTicket(tickets[i]);
            adminTickets--;
        } else if (tickets[i]->type == STAFF && staffTickets > 0) {
            distributeTicket(tickets[i]);
            staffTickets--;
        } else if (tickets[i]->type == OTHER && otherTickets > 0) {
            distributeTicket(tickets[i]);
            otherTickets--;
        } else if (rand() % 2 == 0) {  // 50% chance to distribute the remaining tickets
            distributeTicket(tickets[i]);
        }
    }
}

// Function to clear the input buffer
void TicketclearInputBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) { }
}

// Function for user interface
void TicketUserInterface() {
    char holderName[50];
    int type;
    int option;

    while (1) {
        printf("Welcome to the ticket distribution system! Please select an option:\n");
        printf("1. Create Ticket\n");
        printf("2. Distribute Tickets\n");
        printf("3. Check Tickets Availability\n");
        printf("4. Exit\n");

        if (scanf("%d", &option) != 1) {
            printf("Invalid input. Please enter a number.\n");
            TicketclearInputBuffer();
            continue;
        }

        switch(option) {
            case 1:
                printf("Enter holder name: ");
                scanf("%s", holderName);
                printf("Enter ticket type: ");
                scanf("%d", &type);
                if (type < 0 || type > 4) {
                    TickethandleError("Invalid ticket type.");
                } else if (ticketsPerType[type] > 0) {
                    tickets[ticketCount] = createTicket(type, holderName);
                    ticketCount++;
                    ticketsPerType[type]--;
                } else {
                    printf("No more tickets available for this type.\n");
                }
                break;
            case 2:
                for (int i = 0; i < ticketCount; i++) {
                    if (!tickets[i]->isDistributed) {
                        distributeTicket(tickets[i]);
                    }
                }
                break;
            case 3:
                checkTicketsAvailability();
                break;
            case 4:
                printf("Exiting...\n");
                return;
            default:
                TickethandleError("Invalid option.");
        }
    }
}