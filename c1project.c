#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct book {
    char title[50];
    char author[50];
    char description[200];
};

struct donor_receiver {
    char name[50];
    char address[100];
    char contact_no[15];
    struct book book_details;
};

void add_record() {
    FILE *fp;
    struct donor_receiver dr;
    fp = fopen("book_donation_system.txt", "a+");
    if (fp == NULL) {
        printf("Error opening file\n");
        return;
    }
    printf("\nEnter the name of the donor/receiver: ");
    fgets(dr.name, 50, stdin);
    printf("\nEnter the address: ");
    fgets(dr.address, 100, stdin);
    printf("\nEnter the contact number: ");
    fgets(dr.contact_no, 15, stdin);
    printf("\nEnter the book title: ");
    fgets(dr.book_details.title, 50, stdin);
    printf("\nEnter the book author: ");
    fgets(dr.book_details.author, 50, stdin);
    printf("\nEnter the book description: ");
    fgets(dr.book_details.description, 200, stdin);
    fwrite(&dr, sizeof(struct donor_receiver), 1, fp);
    fclose(fp);
    printf("\nRecord added successfully.\n");
}

void delete_record() {
    FILE *fp, *temp_fp;
    struct donor_receiver dr;
    char name[50];
    int found = 0;
    printf("\nEnter the name of the donor/receiver to delete: ");
    fgets(name, 50, stdin);
    fp = fopen("book_donation_system.txt", "    r");
    if (fp == NULL) {
        printf("Error opening file\n");
        return;
    }
    temp_fp = fopen("temp.txt", "w");
    if (temp_fp == NULL) {
        printf("Error opening file\n");
        fclose(fp);
        return;
    }
    while (fread(&dr, sizeof(struct donor_receiver), 1, fp)) {
        if (strcmp(dr.name, name) == 0) {
            found = 1;
        } else {
            fwrite(&dr, sizeof(struct donor_receiver), 1, temp_fp);
        }
    }
    fclose(fp);
    fclose(temp_fp);
    remove("book_donation_system.txt");
    rename("temp.txt", "book_donation_system.txt");
    if (found) {
        printf("\nRecord deleted successfully.\n");
    } else {
        printf("\nRecord not found.\n");
    }
}

void update_record() {
    FILE *fp, *temp_fp;
    struct donor_receiver dr;
    char name[50];
    int found = 0;
    printf("\nEnter the name of the donor/receiver to update: ");
    fgets(name, 50, stdin);
    fp = fopen("book_donation_system.txt", "r");
    if (fp == NULL) {
        printf("Error opening file\n");
        return;
    }
    temp_fp = fopen("temp.txt", "w");
    if (temp_fp == NULL) {
        printf("Error opening file\n");
        fclose(fp);
        return;
    }
    while (fread(&dr, sizeof(struct donor_receiver), 1, fp)) {
        if (strcmp(dr.name, name) == 0) {
            found = 1;
            printf("\nEnter the new name: ");
            fgets(dr.name, 50, stdin);
            printf("\nEnter the new address: ");
            fgets(dr.address, 100, stdin);
            printf("\nEnter the new contact number: ");
            fgets(dr.contact_no, 15, stdin);
            printf("\nEnter the new book title: ");
            fgets(dr.book_details.title, 50, stdin);
            printf("\nEnter the new book author: ");
            fgets(dr.book_details.author,50, stdin);
printf("\nEnter the new book description: ");
fgets(dr.book_details.description, 200, stdin);
fwrite(&dr, sizeof(struct donor_receiver), 1, temp_fp);
} else {
fwrite(&dr, sizeof(struct donor_receiver), 1, temp_fp);
}
}
fclose(fp);
fclose(temp_fp);
remove("book_donation_system.txt");
rename("temp.txt", "book_donation_system.txt");
if (found) {
printf("\nRecord updated successfully.\n");
} else {
printf("\nRecord not found.\n");
}
}

void search_record() {
    FILE *fp;
    struct donor_receiver dr;
    char search_key[50];
    int found = 0;
    printf("\nEnter the search key (either author name or book title): ");
    fgets(search_key, 50, stdin);
    fp = fopen("book_donation_system.txt", "r");
    if (fp == NULL) {
        printf("Error opening file\n");
        return;
    }
    while (fread(&dr, sizeof(struct donor_receiver), 1, fp)) {
        if (strstr(dr.book_details.title, search_key) != NULL || strstr(dr.book_details.author, search_key) != NULL) {
            found = 1;
            printf("\nRecord found:\n");
            printf("Name: %s", dr.name);
            printf("Address: %s", dr.address);
            printf("Contact No: %s", dr.contact_no);
            printf("Book Title: %s", dr.book_details.title);
            printf("Book Author: %s", dr.book_details.author);
            printf("Book Description: %s", dr.book_details.description);
            break;
        }
    }
    fclose(fp);
    if (!found) {
        printf("\nRecord not found.\n");
    }
}

void display_records() {
    FILE *fp;
    struct donor_receiver dr;
    int serial_no = 1;
    fp = fopen("book_donation_system.txt", "r");
    if (fp == NULL) {
        printf("Error opening file\n");
        return;
    }
    printf("\nBook Donation System Records:\n");
    while (fread(&dr, sizeof(struct donor_receiver), 1, fp)) {
        printf("\n%d. Donor/Receiver: %s\n",serial_no++, dr.name);
        printf("Address: %s", dr.address);
        printf("Contact No: %s", dr.contact_no);
        printf("Book Title: %s", dr.book_details.title);
        printf("Author: %s", dr.book_details.author);
        printf("Description: %s", dr.book_details.description);
        printf("\n");
    }
    fclose(fp);
}

int main() {
int choice;
while(1){
printf("\nWelcome to Book Donation System\n");
printf("1. Add record\n");
printf("2. Delete record\n");
printf("3. Update record\n");
printf("4. Search a Particular Book(Using Author Name/Book Title)\n");
printf("5. Display records\n");
printf("6. Exit\n");
printf("Enter your choice: ");
scanf("%d", &choice);
getchar(); // Consume newline character
switch (choice) {
case 1:
add_record();
break;
case 2:
delete_record();
break;
case 3:
update_record();
break;
case 4:
search_record();
break;
case 5:
display_records();
break;
case 6:
printf("\nGoodbye! Thanks for Donating\n");
exit(0);
break;
default:
printf("\nInvalid choice. Please try again.\n");
break;
}
}
return 0;
}
