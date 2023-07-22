#ifndef DONATION_H
#define DONATION_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Donation {
    char donorName[50];
    char donorIdentity[50];
    char donationContent[100];
    char expectedUse[100];
    int donationAmount;
    struct Donation* next;
} Donation;

typedef struct {
    Donation* head;
} DonationList;

Donation* createDonation(char* donorName, char* donorIdentity, char* donationContent, char* expectedUse, int donationAmount);
void addDonation(DonationList* list, char* donorName, char* donorIdentity, char* donationContent, char* expectedUse, int donationAmount);
void printDonation(Donation* donation);
void printDonationsByDonor(DonationList* list, char* donorIdentity);
DonationList* createDonationList();
void DonationclearInputBuffer();
void DonationUserInterface();

#endif //DONATION_H
