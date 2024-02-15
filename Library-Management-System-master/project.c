#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>  

#define MAX_BOOKS 100
#define MAX_USERS 100

typedef struct Book {
    char name[50];
    char author[50];
    int id;
    int rack;
    int copies;
} Book;

typedef struct User {
    char name[50];
    Book* book;
} User;

Book library[MAX_BOOKS];
User users[MAX_USERS];
int numBooks = 0;
int numUsers = 0;

int generateBookID(char* str);
int generateAlphabetID(char c);
void addBook(int shelve, char* book_name, char* author_name);
void displayLibrary();
void deleteBook(char* name, char* author_name);
void searchBook(char* name);
void issueBook(char* username, char* bookname, char* author_name);
void returnBook(char* username, char* bookname);
void displayIssuedBooks();

int main() {
    int choice;
    char username[50];
    char bookname[50];
    char authorname[50];

    printf("Developed By:\n");
    printf("Name: Hrithik.S\n");
    printf("Reg No:RA2211026020085\n");
    printf("Name:Vignesh.A\n");
    printf("Reg No:RA2211026020101\n");
    printf("Name:Kaushik.H\n");
    printf("Reg No:RA2211026020079\n");

    while (1) {
        printf("\n++++++++++     M E N U     ++++++++++\n");
        printf("0. Exit\n");
        printf("1. Display All Books\n");
        printf("2. Insert a Book\n");
        printf("3. Delete a Book\n");
        printf("4. Search Book By Name\n");
        printf("5. Issue Book\n");
        printf("6. Return Book\n");
        printf("7. Display Issued Books\n");
        printf("Select an option : ");
        scanf("%d", &choice);

        switch (choice) {
            case 0:
                exit(0);
            case 1:
                printf("\n++++++++++     D I S P L A Y     ++++++++++\n");
                displayLibrary();
                break;
            case 2:
                printf("\n++++++++++     I N S E R T     ++++++++++\n");
                printf("0. Back\n");
                printf("1. Novels\n");
                printf("2. Autobiography\n");
                printf("3. Fiction and Non-Fiction\n");
                printf("4. Reference Books\n");
                printf("5. Comics\n");
                printf("Select an option : ");
                scanf("%d", &choice);
                if (choice == 0) break;
                else {
                    printf("\nBook Name : ");
                    scanf(" %[^\n]s", bookname);
                    printf("Author Name : ");
                    scanf(" %[^\n]s", authorname);
                    addBook(choice - 1, bookname, authorname);
                }
                break;
            case 3:
                printf("\n++++++++++     D E L E T E     ++++++++++\n");
                printf("Enter Book Name : ");
                scanf(" %[^\n]s", bookname);
                printf("Enter Author Name : ");
                scanf(" %[^\n]s", authorname);
                deleteBook(bookname, authorname);
                break;
            case 4:
                printf("\n++++++++++     S E A R C H     ++++++++++\n");
                printf("Enter Book Name : ");
                scanf(" %[^\n]s", bookname);
                searchBook(bookname);
                break;
            case 5:
                printf("\n++++++++++     I S S U E     ++++++++++\n");
                printf("Enter User Name : ");
                scanf(" %[^\n]s", username);
                printf("Enter Book Name : ");
                scanf(" %[^\n]s", bookname);
                printf("Enter Author Name : ");
                scanf(" %[^\n]s", authorname);
                issueBook(username, bookname, authorname);
                break;
            case 6:
                printf("\n++++++++++     R E T U R N     ++++++++++\n");
                printf("Enter User Name : ");
                scanf(" %[^\n]s", username);
                printf("Enter Book Name : ");
                scanf(" %[^\n]s", bookname);
                returnBook(username, bookname);
                break;
            case 7:
                printf("\n++++++++++     I S S U E D   B O O K S     ++++++++++\n");
                displayIssuedBooks();
                break;
            default:
                printf("\nInvalid input!\n");
        }
    }

    return 0;
}

int generateBookID(char* str) {
    int value = 0;
    int len = strlen(str);
    for (int i = 0; i < len; i++) {
        if (str[i] == ' ') {
            value += generateAlphabetID(str[i - 1]);
        }
    }
    value += generateAlphabetID(str[len - 1]);
    return value;
}

int generateAlphabetID(char c) {
    char alphabets[] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's',
                        't', 'u', 'v', 'w', 'x', 'y', 'z'};
    c = tolower(c);
    for (int i = 0; i < 26; i++) {
        if (c == alphabets[i]) {
            return i + 1;
        }
    }
    return -1;
}

void addBook(int shelve, char* book_name, char* author_name) {
    int id = generateBookID(book_name);
    int rack = id % 10;
    int copies = 1;

    for (int i = 0; i < numBooks; i++) {
        if (library[i].id == id && strcmp(library[i].name, book_name) == 0 && strcmp(library[i].author, author_name) == 0) {
            library[i].copies++;
            return;
        }
    }

    Book new_book;
    strcpy(new_book.name, book_name);
    strcpy(new_book.author, author_name);
    new_book.id = id;
    new_book.rack = rack;
    new_book.copies = copies;

    library[numBooks] = new_book;
    numBooks++;
}

void displayLibrary() {
    for (int i = 0; i < numBooks; i++) {
        printf("Book ID = %-10d copies = %-10d Book Name = %-30s Author Name = %10s\n", library[i].id, library[i].copies, library[i].name, library[i].author);
    }
}

void deleteBook(char* name, char* author_name) {
    int id = generateBookID(name);
    for (int i = 0; i < numBooks; i++) {
        if (library[i].id == id && strcmp(library[i].name, name) == 0 && strcmp(library[i].author, author_name) == 0) {
            if (library[i].copies > 1) {
                library[i].copies--;
            } else {
                for (int j = i; j < numBooks - 1; j++) {
                    library[j] = library[j + 1];
                }
                numBooks--;
            }
            return;
        }
    }
    printf("Book not found\n");
}

void searchBook(char* name) {
    int id = generateBookID(name);
    for (int i = 0; i < numBooks; i++) {
        if (library[i].id == id && strcmp(library[i].name, name) == 0) {
            printf("Book ID = %-10d copies = %-10d Book Name = %-30s Author Name = %10s\n", library[i].id, library[i].copies, library[i].name, library[i].author);
            return;
        }
    }
    printf("Book not found\n");
}

void issueBook(char* username, char* bookname, char* author_name) {
    for (int i = 0; i < numUsers; i++) {
        if (strcmp(users[i].name, username) == 0) {
            printf("One User can Issue Only One Book\n");
            return;
        }
    }

    for (int i = 0; i < numBooks; i++) {
        if (strcmp(library[i].name, bookname) == 0 && strcmp(library[i].author, author_name) == 0) {
            if (library[i].copies > 0) {
                Book* new_book = (Book*)malloc(sizeof(Book));
                strcpy(new_book->name, library[i].name);
                strcpy(new_book->author, library[i].author);
                new_book->id = library[i].id;
                new_book->rack = library[i].rack;
                new_book->copies = 1;

                User new_user;
                strcpy(new_user.name, username);
                new_user.book = new_book;

                users[numUsers] = new_user;
                numUsers++;

                library[i].copies--;
                return;
            } else {
                printf("Book not available\n");
                return;
            }
        }
    }

    printf("Book not found\n");
}

void returnBook(char* username, char* bookname) {
    for (int i = 0; i < numUsers; i++) {
        if (strcmp(users[i].name, username) == 0) {
            if (strcmp(users[i].book->name, bookname) == 0) {
                for (int j = 0; j < numBooks; j++) {
                    if (strcmp(library[j].name, bookname) == 0 && strcmp(library[j].author, users[i].book->author) == 0) {
                        library[j].copies++;
                        free(users[i].book);
                        for (int k = i; k < numUsers - 1; k++) {
                            users[k] = users[k + 1];
                        }
                        numUsers--;
                        return;
                    }
                }
            } else {
                printf("Book not found\n");
                return;
            }
        }
    }

    printf("User not found\n");
}

void displayIssuedBooks() {
    for (int i = 0; i < numUsers; i++) {
        printf("Username : %-15sBook name : %-15s Author Name : %-15s\n", users[i].name, users[i].book->name, users[i].book->author);
    }
}