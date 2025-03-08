#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILE_NAME "phonebook.txt"

void addContact();
void searchContact();
void displayContacts();

int main() {
    int choice;

    while (1) {
        printf("\nPhone Book Management\n");
        printf("1. Add Contact\n");
        printf("2. Search Contact\n");
        printf("3. Display All Contacts\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar(); // Clear newline from buffer

        switch (choice) {
            case 1:
                addContact();
                break;
            case 2:
                searchContact();
                break;
            case 3:
                displayContacts();
                break;
            case 4:
                exit(0);
            default:
                printf("Invalid choice! Try again.\n");
        }
    }

    return 0;
}

void addContact() {
    FILE *file = fopen(FILE_NAME, "a");
    if (!file) {
        printf("Error opening file!\n");
        return;
    }

    char name[50], phone[15];
    printf("Enter name: ");
    fgets(name, sizeof(name), stdin);
    name[strcspn(name, "\n")] = 0; // Remove newline

    printf("Enter phone number: ");
    fgets(phone, sizeof(phone), stdin);
    phone[strcspn(phone, "\n")] = 0; // Remove newline

    fprintf(file, "%s,%s\n", name, phone);
    fclose(file);
    printf("Contact added successfully!\n");
}

void searchContact() {
    FILE *file = fopen(FILE_NAME, "r");
    if (!file) {
        printf("Error opening file!\n");
        return;
    }

    char name[50], line[100];
    printf("Enter name to search: ");
    fgets(name, sizeof(name), stdin);
    name[strcspn(name, "\n")] = 0; // Remove newline

    int found = 0;
    while (fgets(line, sizeof(line), file)) {
        char *token = strtok(line, ",");
        if (strcmp(token, name) == 0) {
            printf("Contact found: %s - %s", token, strtok(NULL, ","));
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("Contact not found!\n");
    }

    fclose(file);
}

void displayContacts() {
    FILE *file = fopen(FILE_NAME, "r");
    if (!file) {
        printf("Error opening file!\n");
        return;
    }

    char line[100];
    printf("\nContacts List:\n");
    while (fgets(line, sizeof(line), file)) {
        printf("%s", line);
    }

    fclose(file);
}
