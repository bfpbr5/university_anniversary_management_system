#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <donation_management.h>

// Function to create a new donation
Donation* createDonation(char* donorName, char* donorIdentity, char* donationContent, char* expectedUse, int donationAmount) {
    Donation* newDonation = (Donation*)malloc(sizeof(Donation));
    if (newDonation == NULL) {
        printf("Error: Unable to allocate memory for new donation.\n");
        return NULL;
    }
    strncpy(newDonation->donorName, donorName, sizeof(newDonation->donorName) - 1);
    strncpy(newDonation->donorIdentity, donorIdentity, sizeof(newDonation->donorIdentity) - 1);
    strncpy(newDonation->donationContent, donationContent, sizeof(newDonation->donationContent) - 1);
    strncpy(newDonation->expectedUse, expectedUse, sizeof(newDonation->expectedUse) - 1);
    newDonation->donationAmount = donationAmount;
    newDonation->next = NULL;
    return newDonation;
}

// Function to add a donation to a linked list of donations
void addDonation(DonationList* list, char* donorName, char* donorIdentity, char* donationContent, char* expectedUse, int donationAmount) {
    Donation* newDonation = createDonation(donorName, donorIdentity, donationContent, expectedUse, donationAmount);
    if (newDonation == NULL) {
        return;
    }
    newDonation->next = list->head;
    list->head = newDonation;
}

// Function to print a donation's details
void printDonation(Donation* donation) {
    if (donation == NULL) {
        printf("Error: Donation does not exist.\n");
        return;
    }
    printf("Donor Name: %s\n", donation->donorName);
    printf("Donor Identity: %s\n", donation->donorIdentity);
    printf("Donation Content: %s\n", donation->donationContent);
    printf("Expected Use: %s\n", donation->expectedUse);
    printf("Donation Amount: %d\n\n", donation->donationAmount);
}

// Function to print all donations from a specific donor
void printDonationsByDonor(DonationList* list, char* donorIdentity) {
    Donation* current = list->head;
    int found = 0;
    while (current != NULL) {
        if (strcmp(current->donorIdentity, donorIdentity) == 0) {
            printDonation(current);
            found = 1;
        }
        current = current->next;
    }
    if (!found) {
        printf("No donations found for the specified donor identity.\n");
    }
}

// Function to create a new donation list
DonationList* createDonationList() {
    DonationList* newList = (DonationList*)malloc(sizeof(DonationList));
    if (newList == NULL) {
        printf("Error: Unable to allocate memory for new donation list.\n");
        return NULL;
    }
    newList->head = NULL;
    return newList;
}

// Function to clear the input buffer
void DonationclearInputBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) { }
}

// Function for user interface
void DonationUserInterface() {
    char donorName[50];
    char donorIdentity[50];
    char donationContent[100];
    char expectedUse[100];
    int donationAmount;
    int option;

    DonationList* list = createDonationList();

    while (1) {
        printf("Welcome to donation management system! Please select an option:\n");
        printf("1. Add Donation\n");
        printf("2. Print Donations by Donor\n");
        printf("3. Exit\n");

        if (scanf("%d", &option) != 1) {
            printf("Invalid input. Please enter a number.\n");
            DonationclearInputBuffer();
            continue;
        }
        
        switch(option) {
            case 1:
                printf("Enter donor name: ");
                scanf("%s", donorName);
                printf("Enter donor identity: ");
                scanf("%s", donorIdentity);
                printf("Enter donation content: ");
                scanf("%s", donationContent);
                printf("Enter expected use: ");
                scanf("%s", expectedUse);
                printf("Enter donation amount: ");
                if (scanf("%d", &donationAmount) != 1) {
                    printf("Invalid input. Please enter a number.\n");
                    DonationclearInputBuffer();
                    continue;
                }
                addDonation(list, donorName, donorIdentity, donationContent, expectedUse, donationAmount);
                break;
            case 2:
                printf("Enter donor identity: ");
                scanf("%s", donorIdentity);
                printDonationsByDonor(list, donorIdentity);
                break;
            case 3:
                printf("Exiting...\n");
                return;
            default:
                printf("Invalid option.\n");
        }
    }
}

