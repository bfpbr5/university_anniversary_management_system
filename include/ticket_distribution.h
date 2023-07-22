#ifndef TICKET_DISTRIBUTION_H
#define TICKET_DISTRIBUTION_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define ALUMNI 0
#define STUDENT 1
#define TEACHER 2
#define ADMIN 3
#define STAFF 4
#define OTHER 5

#define TOTAL_TICKETS 1000
#define ALUMNI_RATIO 0.20
#define STUDENT_RATIO 0.20
#define TEACHER_RATIO 0.15
#define ADMIN_RATIO 0.15
#define STAFF_RATIO 0.15
#define OTHER_RATIO 0.15

typedef struct {
    int type;
    char holderName[50];
    int isDistributed;
} Ticket;

extern Ticket* tickets[TOTAL_TICKETS];
extern int ticketCount;
extern int ticketsPerType[6];

Ticket* createTicket(int type, char* holderName);
void distributeTicket(Ticket* ticket);
void checkTicketsAvailability();
void TickethandleError(char* errorMessage);
void distributeTickets(Ticket* tickets[]);
void TicketclearInputBuffer();
void TicketUserInterface();

#endif /* TICKET_DISTRIBUTION_H */
