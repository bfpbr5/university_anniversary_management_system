#ifndef MATERIAL_MANAGEMENT_H
#define MATERIAL_MANAGEMENT_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_MATERIALS 100

typedef struct {
    char name[100];
    char category[100];
    int quantity;
    char source[100];
    char purchaser[100];
    char purchase_date[20];
    char recipient[100];
    char recipient_department[100];
    char handler[100];
    char issue_date[20];
} Material;

extern Material materials[MAX_MATERIALS];
extern int material_count;

void add_material(char* name, char* category, int quantity, char* source, char* purchaser, char* purchase_date);
int issue_material(char* name, char* recipient, char* recipient_department, char* handler, char* issue_date);
void print_material(Material* material);
void find_materials_by_category(char* category);
void MaterialhandleError(char* errorMessage);
void MaterialUserInterface();

#endif /* MATERIAL_MANAGEMENT_H */
