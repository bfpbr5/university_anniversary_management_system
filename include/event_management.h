#ifndef EVENT_MANAGEMENT_H
#define EVENT_MANAGEMENT_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char organizer[50];
    char content[100];
    char time[50];
    char approver[50];
    int isApproved;
    char resourceRequested[100];
    char resourceAllocator[50];
    int isResourceAllocated;
} Event;

extern Event* events[100];
extern int eventCount;

Event* createEvent(char* organizer, char* content, char* time, char* resourceRequested);
void approveEvent(char* organizer, char* approver);
void allocateResources(char* organizer, char* allocator);
void checkStatus(char* organizer);
void printEventsByOrganizer(char* organizer);
void EventhandleError(char* errorMessage);
void EventUserInterface();

#endif /* EVENT_MANAGEMENT_H */
