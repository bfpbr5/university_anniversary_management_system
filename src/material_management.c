#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <material_management.h>

#define MAX_MATERIALS 100

Material materials[MAX_MATERIALS];
int material_count = 0;

// Add a new material
void add_material(char* name, char* category, int quantity, char* source, char* purchaser, char* purchase_date) {
    if (material_count >= MAX_MATERIALS) {
        printf("Error: Cannot add more materials. The storage is full.\n");
        return;
    }
    Material material;
    strcpy(material.name, name);
    strcpy(material.category, category);
    material.quantity = quantity;
    strcpy(material.source, source);
    strcpy(material.purchaser, purchaser);
    strcpy(material.purchase_date, purchase_date);
    materials[material_count++] = material;
}

// Issue a material to a recipient
int issue_material(char* name, char* recipient, char* recipient_department, char* handler, char* issue_date) {
    for (int i = 0; i < material_count; i++) {
        if (strcmp(materials[i].name, name) == 0) {
            if (materials[i].quantity <= 0) {
                printf("Error: Material %s is out of stock.\n", name);
                return -1;
            }
            strcpy(materials[i].recipient, recipient);
            strcpy(materials[i].recipient_department, recipient_department);
            strcpy(materials[i].handler, handler);
            strcpy(materials[i].issue_date, issue_date);
            materials[i].quantity--;
            return 0;
        }
    }
    printf("Error: Material %s not found.\n", name);
    return -1;
}

// Print the details of a material
void print_material(Material* material) {
    printf("Name: %s\n", material->name);
    printf("Category: %s\n", material->category);
    printf("Quantity: %d\n", material->quantity);
    printf("Source: %s\n", material->source);
    printf("Purchaser: %s\n", material->purchaser);
    printf("Purchase Date: %s\n", material->purchase_date);
    if (material->quantity > 0) {
        printf("Recipient: %s\n", material->recipient);
        printf("Recipient Department: %s\n", material->recipient_department);
        printf("Handler: %s\n", material->handler);
        printf("Issue Date: %s\n", material->issue_date);
    }
}

// Find materials by category
void find_materials_by_category(char* category) {
    int found = 0;
    for (int i = 0; i < material_count; i++) {
        if (strcmp(materials[i].category, category) == 0) {
            print_material(&materials[i]);
            found = 1;
        }
    }
    if (!found) {
        printf("No materials found in category %s\n", category);
    }
}
// Function to handle errors
void MaterialhandleError(char* errorMessage) {
    printf("Error: %s\n", errorMessage);
}

// Function to clear the input buffer
void MaterialclearInputBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) { }
}

// User interface function
void MaterialUserInterface() {
    int option;
    char name[100], category[100], source[100], purchaser[100], purchase_date[20];
    char recipient[100], recipient_department[100], handler[100], issue_date[20];
    int quantity;

    while (1) {
        printf("Please select an option:\n");
        printf("1. Add a new material\n");
        printf("2. Issue a material\n");
        printf("3. Find materials by category\n");
        printf("4. Exit\n");

        if (scanf("%d", &option) != 1) {
            MaterialhandleError("Invalid input. Please enter a number.");
            MaterialclearInputBuffer();
            continue;
        }

        switch(option) {
            case 1:
                printf("Enter material name: ");
                scanf("%s", name);
                printf("Enter material category: ");
                scanf("%s", category);
                printf("Enter material quantity: ");
                scanf("%d", &quantity);
                printf("Enter source: ");
                scanf("%s", source);
                printf("Enter purchaser: ");
                scanf("%s", purchaser);
                printf("Enter purchase date (YYYY-MM-DD): ");
                scanf("%s", purchase_date);
                add_material(name, category, quantity, source, purchaser, purchase_date);
                break;
            case 2:
                printf("Enter material name: ");
                scanf("%s", name);
                printf("Enter recipient name: ");
                scanf("%s", recipient);
                printf("Enter recipient department: ");
                scanf("%s", recipient_department);
                printf("Enter handler name: ");
                scanf("%s", handler);
                printf("Enter issue date (YYYY-MM-DD): ");
                scanf("%s", issue_date);
                issue_material(name, recipient, recipient_department, handler, issue_date);
                break;
            case 3:
                printf("Enter material category: ");
                scanf("%s", category);
                find_materials_by_category(category);
                break;
            case 4:
                printf("Exiting...\n");
                return;
            default:
                MaterialhandleError("Invalid option.");
        }
    }
}
