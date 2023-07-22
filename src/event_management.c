#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <event_management.h>

// Event array to store all events
Event* events[100];
int eventCount = 0;

// Function to create a new event
Event* createEvent(char* organizer, char* content, char* time, char* resourceRequested) {
    Event* newEvent = (Event*)malloc(sizeof(Event));
    if (eventCount >= 100) {
        printf("Error: Maximum number of events reached.\n");
        return NULL;
    }
    strncpy(newEvent->organizer, organizer, sizeof(newEvent->organizer) - 1);
    strncpy(newEvent->content, content, sizeof(newEvent->content) - 1);
    strncpy(newEvent->time, time, sizeof(newEvent->time) - 1);
    strncpy(newEvent->resourceRequested, resourceRequested, sizeof(newEvent->resourceRequested) - 1);
    newEvent->approver[0] = '\0';
    newEvent->isApproved = 0;
    newEvent->resourceAllocator[0] = '\0';
    newEvent->isResourceAllocated = 0;
    // Add the new event to the array
    events[eventCount++] = newEvent;
    return newEvent;
}

// Function to approve an event
void approveEvent(char* organizer, char* approver) {
    printEventsByOrganizer(organizer);
    printf("Enter the event id to approve: ");
    int id;
    scanf("%d", &id);
    if (id < 0 || id >= eventCount) {
        printf("Invalid event id.\n");
        return;
    }
    Event* event = events[id];
    strncpy(event->approver, approver, sizeof(event->approver) - 1);
    event->isApproved = 1;
    printf("Event has been approved by %s.\n", event->approver);
}

// Function to allocate resources for an event
void allocateResources(char* organizer, char* allocator) {
    printEventsByOrganizer(organizer);
    printf("Enter the event id to allocate resources: ");
    int id;
    scanf("%d", &id);
    if (id < 0 || id >= eventCount) {
        printf("Invalid event id.\n");
        return;
    }
    Event* event = events[id];
    strncpy(event->resourceAllocator, allocator, sizeof(event->resourceAllocator) - 1);
    event->isResourceAllocated = 1;
    printf("Resources for the event have been allocated by %s.\n", event->resourceAllocator);
}

// Function to check an event's approval and resource allocation status
void checkStatus(char* organizer) {
    printEventsByOrganizer(organizer);
    printf("Enter the event id to check status: ");
    int id;
    scanf("%d", &id);
    if (id < 0 || id >= eventCount) {
        printf("Invalid event id.\n");
        return;
    }
    Event* event = events[id];
    if (event->isApproved) {
        printf("Event is approved by %s.\n", event->approver);
    } else {
        printf("Event is not approved.\n");
    }
    if (event->isResourceAllocated) {
        printf("Resources for the event are allocated by %s.\n", event->resourceAllocator);
    } else {
        printf("Resources for the event are not allocated.\n");
    }
}

// Function to print all events by an organizer
void printEventsByOrganizer(char* organizer) {
    int found = 0;
    for (int i = 0; i < eventCount; i++) {
        if (strcmp(events[i]->organizer, organizer) == 0) {
            printf("Event ID: %d\n", i);
            printf("Event Content: %s\n", events[i]->content);
            printf("Event Time: %s\n", events[i]->time);
            printf("Resources Requested: %s\n", events[i]->resourceRequested);
            // checkStatus(events[i]->organizer);
            found = 1;
        }
    }
    if (!found) {
        printf("No events found for the organizer: %s.\n", organizer);
    }
}

// Function to handle errors
void EventhandleError(char* errorMessage) {
    printf("Error: %s\n", errorMessage);
}

// Function for user interface
void EventUserInterface() {
    char organizer[50];
    char content[100];
    char time[50];
    char approver[50];
    char allocator[50];
    char resourceRequested[100];
    int option;
    Event* event = NULL;

    while (1) {
        printf("Welcome to event management system! Please select an option:\n");
        printf("1. Create Event\n");
        printf("2. Approve Event\n");
        printf("3. Allocate Resources\n");
        printf("4. Check Event Status by Organizer\n");
        printf("5. Exit\n");
        scanf("%d", &option);

        switch(option) {
            case 1:
                printf("Enter organizer name: ");
                scanf("%s", organizer);
                printf("Enter event content: ");
                scanf("%s", content);
                printf("Enter event time: ");
                scanf("%s", time);
                printf("Enter resources requested: ");
                scanf("%s", resourceRequested);
                event = createEvent(organizer, content, time, resourceRequested);
                if (event == NULL) {
                    EventhandleError("Unable to create event");
                    continue;
                }
                break;
            case 2:
                printf("Enter organizer name: ");
                scanf("%s", organizer);
                printf("Enter approver name: ");
                scanf("%s", approver);
                approveEvent(organizer, approver);
                break;
            case 3:
                printf("Enter organizer name: ");
                scanf("%s", organizer);
                printf("Enter allocator name: ");
                scanf("%s", allocator);
                allocateResources(organizer, allocator);
                break;
            case 4:
                printf("Enter organizer name: ");
                scanf("%s", organizer);
                checkStatus(organizer);
                break;
            case 5:
                if (event != NULL) {
                    free(event);
                }
                printf("Exiting...\n");
                return;
            default:
                printf("Invalid option.\n");
        }
    }
}