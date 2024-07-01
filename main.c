#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_BOOKS 100
#define MAX_TITLE_LEN 100
#define MAX_AUTHOR_LEN 100

typedef struct {
    int id;
    char title[MAX_TITLE_LEN];
    char author[MAX_AUTHOR_LEN];
    int is_checked_out;
} Book;

typedef struct {
    int id;
    char name[MAX_TITLE_LEN];
    int borrowed_book_id;
} Patron;

Book library[MAX_BOOKS];
Patron patrons[MAX_BOOKS];
int book_count = 0;
int patron_count = 0;

void addBook() {
    if (book_count >= MAX_BOOKS) {
        printf("Library is full!\n");
        return;
    }
    Book new_book;
    new_book.id = book_count + 1;
    printf("Enter book title: ");
    getchar(); // clear the newline left in the buffer
    fgets(new_book.title, MAX_TITLE_LEN, stdin);
    strtok(new_book.title, "\n"); // remove newline character
    printf("Enter book author: ");
    fgets(new_book.author, MAX_AUTHOR_LEN, stdin);
    strtok(new_book.author, "\n"); // remove newline character
    new_book.is_checked_out = 0;
    library[book_count++] = new_book;
    printf("Book added successfully!\n");
}

void deleteBook() {
    int id;
    printf("Enter book ID to delete: ");
    scanf("%d", &id);
    for (int i = 0; i < book_count; i++) {
        if (library[i].id == id) {
            for (int j = i; j < book_count - 1; j++) {
                library[j] = library[j + 1];
            }
            book_count--;
            printf("Book deleted successfully!\n");
            return;
        }
    }
    printf("Book not found!\n");
}

void searchBook() {
    char keyword[MAX_TITLE_LEN];
    printf("Enter book title or author to search: ");
    getchar(); // clear the newline left in the buffer
    fgets(keyword, MAX_TITLE_LEN, stdin);
    strtok(keyword, "\n"); // remove newline character
    for (int i = 0; i < book_count; i++) {
        if (strstr(library[i].title, keyword) != NULL || strstr(library[i].author, keyword) != NULL) {
            printf("Book ID: %d\nTitle: %s\nAuthor: %s\nChecked Out: %s\n", library[i].id, library[i].title, library[i].author, library[i].is_checked_out ? "Yes" : "No");
        }
    }
}

void checkOutBook() {
    int id;
    printf("Enter book ID to check out: ");
    scanf("%d", &id);
    for (int i = 0; i < book_count; i++) {
        if (library[i].id == id) {
            if (library[i].is_checked_out) {
                printf("Book is already checked out!\n");
                return;
            }
            library[i].is_checked_out = 1;
            printf("Book checked out successfully!\n");
            return;
        }
    }
    printf("Book not found!\n");
}

void checkInBook() {
    int id;
    printf("Enter book ID to check in: ");
    scanf("%d", &id);
    for (int i = 0; i < book_count; i++) {
        if (library[i].id == id) {
            if (!library[i].is_checked_out) {
                printf("Book is already checked in!\n");
                return;
            }
            library[i].is_checked_out = 0;
            printf("Book checked in successfully!\n");
            return;
        }
    }
    printf("Book not found!\n");
}

void menu() {
    int choice;
    while (1) {
        printf("\nLibrary Management System\n");
        printf("1. Add Book\n");
        printf("2. Delete Book\n");
        printf("3. Search Book\n");
        printf("4. Check Out Book\n");
        printf("5. Check In Book\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                addBook();
                break;
            case 2:
                deleteBook();
                break;
            case 3:
                searchBook();
                break;
            case 4:
                checkOutBook();
                break;
            case 5:
                checkInBook();
                break;
            case 6:
                exit(0);
                break;
            default:
                printf("Invalid choice! Please try again.\n");
        }
    }
}

int main() {
    menu();
    return 0;
}
