#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
-------------------------------------------------
Project Title : BookNest – Smart Library Manager
Developed By  : Shraddha Dusane
Course        : B.Tech Computer Engineering
Subject       : Data Structures
-------------------------------------------------
*/

/* ================== BOOK LINKED LIST ================== */
struct Book {
    int id;
    char name[50];
    char author[50];
    int issued;              // 0 = Available, 1 = Issued
    struct Book *next;
};

struct Book *head = NULL;

/* ================== STACK FOR ISSUE HISTORY ================== */
struct Stack {
    int bookId;
    char studentName[50];
    int rollNo;
    char issueDate[15];
    struct Stack *next;
};

struct Stack *top = NULL;

/* ================== STACK OPERATIONS ================== */

// Push issue details
void push(int id, char sname[], int roll, char date[]) {
    struct Stack *temp = (struct Stack *)malloc(sizeof(struct Stack));
    temp->bookId = id;
    strcpy(temp->studentName, sname);
    temp->rollNo = roll;
    strcpy(temp->issueDate, date);
    temp->next = top;
    top = temp;
}

// Pop issue record
struct Stack* pop() {
    if (top == NULL)
        return NULL;

    struct Stack *temp = top;
    top = top->next;
    return temp;
}

/* ================== BOOK OPERATIONS ================== */

// Add book
void addBook() {
    struct Book *temp = (struct Book *)malloc(sizeof(struct Book));

    printf("Enter Book ID: ");
    scanf("%d", &temp->id);

    printf("Enter Book Name: ");
    scanf(" %[^\n]", temp->name);

    printf("Enter Author Name: ");
    scanf(" %[^\n]", temp->author);

    temp->issued = 0;
    temp->next = head;
    head = temp;

    printf("? Book added successfully!\n");
}

// Search book
struct Book* searchBook(int id) {
    struct Book *curr = head;
    while (curr != NULL) {
        if (curr->id == id)
            return curr;
        curr = curr->next;
    }
    return NULL;
}

// Issue book with student details
void issueBook() {
    int id, roll;
    char sname[50], date[15];

    printf("Enter Book ID to Issue: ");
    scanf("%d", &id);

    struct Book *book = searchBook(id);

    if (book == NULL) {
        printf("? Book not found!\n");
        return;
    }
    if (book->issued) {
        printf("?? Book already issued!\n");
        return;
    }

    printf("Enter Student Name: ");
    scanf(" %[^\n]", sname);

    printf("Enter Roll Number: ");
    scanf("%d", &roll);

    printf("Enter Issue Date (DD-MM-YYYY): ");
    scanf("%s", date);

    book->issued = 1;
    push(id, sname, roll, date);

    printf("? Book issued successfully to %s\n", sname);
}

// Return book + fine calculation
void returnBook() {
    struct Stack *record = pop();
    int daysLate, fine;

    if (record == NULL) {
        printf("?? No issued book to return!\n");
        return;
    }

    struct Book *book = searchBook(record->bookId);
    if (book != NULL)
        book->issued = 0;

    printf("\nReturned By : %s (Roll %d)\n", record->studentName);
    printf("Issue Date : %s\n", record->issueDate);

    printf("Enter number of late days: ");
    scanf("%d", &daysLate);

    fine = daysLate * 2;
    printf("Fine Amount: ?%d\n", fine);

    free(record);
    printf("? Book returned successfully!\n");
}

// Delete book
void deleteBook() {
    int id;
    printf("Enter Book ID to delete: ");
    scanf("%d", &id);

    struct Book *curr = head, *prev = NULL;

    while (curr != NULL && curr->id != id) {
        prev = curr;
        curr = curr->next;
    }

    if (curr == NULL) {
        printf("? Book not found!\n");
        return;
    }

    if (prev == NULL)
        head = curr->next;
    else
        prev->next = curr->next;

    free(curr);
    printf("? Book deleted successfully!\n");
}

// Count books
void countBooks() {
    int count = 0;
    struct Book *curr = head;
    while (curr != NULL) {
        count++;
        curr = curr->next;
    }
    printf("?? Total books: %d\n", count);
}

// Show all books
void displayBooks() {
    struct Book *curr = head;

    if (curr == NULL) {
        printf("?? No books available!\n");
        return;
    }

    printf("\nID\tBook Name\tAuthor\t\tStatus\n");
    while (curr != NULL) {
        printf("%d\t%s\t\t%s\t%s\n",
               curr->id,
               curr->name,
               curr->author,
               curr->issued ? "Issued" : "Available");
        curr = curr->next;
    }
}

// Show issued books only
void showIssuedBooks() {
    struct Book *curr = head;
    printf("\n?? Issued Books:\n");
    while (curr != NULL) {
        if (curr->issued)
            printf("ID: %d | %s | %s\n",
                   curr->id, curr->name, curr->author);
        curr = curr->next;
    }
}

/* ================== MAIN FUNCTION ================== */
int main() {
    int choice;

    do {
        printf("\n?? BookNest – Smart Library Manager ??\n");
        printf("1. Add Book\n");
        printf("2. Issue Book\n");
        printf("3. Return Book\n");
        printf("4. Search Book\n");
        printf("5. Display All Books\n");
        printf("6. Delete Book\n");
        printf("7. Count Books\n");
        printf("8. View Issued Books\n");
        printf("0. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
        case 1: addBook(); break;
        case 2: issueBook(); break;
        case 3: returnBook(); break;
        case 4: {
            int id;
            printf("Enter Book ID: ");
            scanf("%d", &id);
            struct Book *book = searchBook(id);
            if (book)
                printf("? Found: %s by %s (%s)\n",
                       book->name, book->author,
                       book->issued ? "Issued" : "Available");
            else
                printf("? Book not found!\n");
            break;
        }
        case 5: displayBooks(); break;
        case 6: deleteBook(); break;
        case 7: countBooks(); break;
        case 8: showIssuedBooks(); break;
        case 0: printf("?? Thank you for using BookNest!\n"); break;
        default: printf("? Invalid choice!\n");
        }
    } while (choice != 0);

    return 0;
}

