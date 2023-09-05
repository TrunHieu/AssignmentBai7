#include <stdio.h>
#include <string.h>

struct Contact {
    char name[50];
    char phone[15];
    char address[100];
};

void addContact(FILE *file) {
    struct Contact contact;
    printf("Enter name: "); scanf(" %[^\n]", contact.name);
    printf("Enter phone number: "); scanf("%s", contact.phone);
    printf("Enter address: "); scanf(" %[^\n]", contact.address);

    fprintf(file, "%s|%s|%s\n", contact.name, contact.phone, contact.address);
    printf("\nContact added successfully!\n");
}

void displayContacts(FILE *file) {
    printf("Contact List:\n");
    struct Contact contact;
    int contactNumber = 1;

    rewind(file);
    while (fscanf(file, "%[^|]|%[^|]|%[^\n]\n", contact.name, contact.phone, contact.address) != EOF) {
        printf("%d. Name: %s\n   Phone: %s\n   Address: %s\n\n", contactNumber, contact.name, contact.phone, contact.address);
        contactNumber++;
    }
}

void searchContact(FILE *file) {
    char searchName[50];
    printf("Enter name to search for: "); scanf(" %[^\n]", searchName);

    struct Contact contact;
    int found = 0;

    rewind(file);
    while (fscanf(file, "%[^|]|%[^|]|%[^\n]\n", contact.name, contact.phone, contact.address) != EOF) {
        if (strcmp(contact.name, searchName) == 0) {
            printf("\nContact found:\n");
            printf("Name: %s\nPhone: %s\nAddress: %s\n\n", contact.name, contact.phone, contact.address);
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("\nContact not found.\n\n");
    }
}

int main() {
    FILE *file = fopen("contacts.txt", "a+");

    if (file == NULL) {
        printf("Could not open or create the contact file.\n");
        return 1;
    }

    printf("Welcome to the Contact Manager!\n");

    while (1) {
        printf("1. Add a new contact\n2. Display all contacts\n3. Search for a contact\n4. Exit\n\nEnter your choice: ");
        int choice;
        scanf("%d", &choice);

        switch (choice) {
            case 1: addContact(file); break;
            case 2: displayContacts(file); break;
            case 3: searchContact(file); break;
            case 4: fclose(file); printf("Goodbye!\n"); return 0;
            default: printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}
