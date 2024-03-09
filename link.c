#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define the book structure
struct Book
{
    char title[100];
    char genre[50];
    char Enrol[16];
    int val;
    struct Book *next;
};

struct taker
{

    char Enrol[100];
    char book[100];
    int n;
    struct taker *next;
};

int counter(struct Book *library)
{
    int count = 0;
    struct Book *p = (struct Book *)malloc(sizeof(struct Book));
    p = library;
    while (p != NULL)
    {
        p = p->next;
        count++;
    }
    return count;
}

void addBook(struct Book **library, struct Book **pepe)
{
    struct Book *newBook = (struct Book *)malloc(sizeof(struct Book));
    if (newBook == NULL)
    {
        printf("Memory allocation failed\n");
        return;
    }
    newBook->val = 1;
    printf("Enter the title of the book: ");
    fgets(newBook->title, sizeof(newBook->title), stdin);
    newBook->title[strcspn(newBook->title, "\n")] = '\0'; // Remove newline character

    printf("Enter the genre of the book: ");
    fgets(newBook->genre, sizeof(newBook->genre), stdin);
    newBook->genre[strcspn(newBook->genre, "\n")] = '\0'; // Remove newline character

    printf("Enter the Quantity of the books: ");
    scanf("%d", &newBook->val);

    newBook->next = NULL;

    if (*library == NULL)
    {
        *library = newBook;
        *pepe = newBook;
    }
    else
    {
        (*pepe)->next = newBook;
        *pepe = newBook;
    }

    printf("Book added successfully!\n");
}

// Function to display all books in the library
void displayLibrary(struct Book *library)
{
    printf("\n\n**Library Contents**\n\n");
    int i = 0;
    printf("Title   :   Genre   :   Number of Items\n\n");

    while (library != NULL)
    {
        i++;

        printf("%d) %s  :  %s  :  %d \n", i, library->title, library->genre, library->val);
        library = library->next;
    }
}
void Rbook(struct Book *library, struct taker **take)
{
    int dum;
    int dum2;
    int count3 = 1;
    struct Book *ptr = library;
    struct Book *ptr1 = library;
    struct taker *pt = (struct taker *)malloc(sizeof(struct taker));
    pt = *take; 
    struct taker *tp = *take;
    int p;
    int i = 1;
    int count1 = counter(library);
    char enrol[25];
    if (*take == NULL)
    {
        printf("\n***NO ISSUES YET***\n");
        return;
    }
    displayLibrary(library);
    printf("\nWhich Book do you want to return?: ");
    scanf("%d", &p);
    while (count3 != p)
    {
        ptr1 = ptr1->next;
        count3++;
    }
    //printf("\n%s\n",pt->Enrol);

    if (p <= count1)
    {
        printf("Enter your Enrolment: ");
        scanf("%s", &enrol);

        while (pt != NULL && strcmp(pt->Enrol, enrol) != 0) 
        {

            pt = pt->next;
            if(pt == NULL)
            {
                printf("THIS ENROLMENT DID NOT ISSUE A BOOK");
                return;

            }
        }
        if(pt == *take && strcmp(pt->book,ptr1->title)==0)
        {
            (*take) = (*take)->next;
            pt =pt->next;
            tp = tp->next;

            ptr1->val++;
            printf("\n\n**Book Added In The Stack!**\n");
            printf("Number of %s books now are %d\n", ptr1->title, ptr1->val);

            return;
        }
        
        else if(strcmp(pt->book,ptr1->title)==0 )
        {
            while (tp->next != pt && tp != pt)
                    {
                        tp = tp->next;
                        printf("2\n");
                    }
                    tp->next = pt->next;

                    // 2printf("3\n");
                    while (i != p)
                    {
                        ptr = ptr->next;
                        i++;
                    }
                    ptr1->val++;
                    printf("\n\n**Book Added In The Stack!**\n");
                    printf("Number of %s books now are %d\n", ptr1->title, ptr1->val);
        }
        else
        {
            printf("This Enrolment Issued  Different book");
        }
        
        
    }
    else
    {
        printf("Index is Invalid\n");
    }
}

struct taker *t = NULL;

void takeabook(struct Book *library, struct taker **take)
{
    if (library == NULL)
    {
        printf("\nCannot take a book as there are no books in the library.\n");
        return;
    }

    displayLibrary(library);
    int count1 = counter(library);
    printf("\nEnter the index of the book you want to take: ");
    int index;
    scanf("%d", &index);

    if (index < 1 || index > count1)
    {
        printf("Invalid index.\n");
        return;
    }

    struct Book *selectedBook = library;
    for (int i = 1; i < index; i++)
    {
        selectedBook = selectedBook->next;
    }

    if (selectedBook->val == 0)
    {
        printf("This book is out of stock.\n");
        return;
    }

    char enrol[16];
    printf("Enter your Enrolment: ");
    scanf("%15s", enrol);

    struct taker *newTaker = (struct taker *)malloc(sizeof(struct taker));
    if (newTaker == NULL)
    {
        printf("Memory allocation failed.\n");
        return;
    }

    strcpy(newTaker->Enrol, enrol);
    strcpy(newTaker->book, selectedBook->title);
    newTaker->next = NULL;

    if (*take == NULL)
    {
        *take = newTaker;
    }
    else
    {
        struct taker *temp = *take;
        while (temp->next != NULL)
        {
            temp = temp->next;
        }
        temp->next = newTaker;
    }

    selectedBook->val--;
    printf("\nYou, %s, have taken %s!\n", newTaker->Enrol, newTaker->book);
    printf("Number of %s books remaining in the library: %d\n", selectedBook->title, selectedBook->val);
}

void takers(struct taker *take)
{
    struct taker *t = take;
    printf("\nThis is the list of students who issued a book from library: \n");
    printf("\nEnrolment  :  Book\n");
    while (t != NULL)
    {
        printf("%s  :  %s\n", t->Enrol, t->book);
        t = t->next;
    }
}

// Main function
int main()
{
    struct Book *library = NULL;
    struct Book *pepe = NULL; // Initialize library as empty
    struct taker *take = NULL;

    printf("\nHey welcome to this Library Management System! How may I help you today?");
    printf("\n***Add \"_\" (Underscore) between words***");
    int choice;
    do
    {
        printf("\n1. Add a book\n");
        printf("2. Display library\n");
        printf("3. Take a book\n");
        printf("4. Return a Book\n");
        printf("5. Display Takers\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");

        if (scanf("%d", &choice) != 1)
        {
            printf("Invalid input. Please enter a number.\n");
            // Clear the input buffer
            int c;
            while ((c = getchar()) != '\n' && c != EOF)
            {
            }
            continue;
        }

        // Clear input buffer
        int c;
        while ((c = getchar()) != '\n' && c != EOF)
        {
        }

        switch (choice)
        {
        case 1:
            addBook(&library, &pepe);
            break;
        case 2:
            displayLibrary(library);
            break;
        case 3:
            takeabook(library, &take);
            break;
        case 4:
            Rbook(library, &take);
            break;
        case 5:
            takers(take);
            break;
        case 6:
            printf("Exiting...\n");
            break;
        default:
            printf("Invalid choice. Please enter a number between 1 and 6.\n");
        }
    } while (choice != 6);

    // Free memory allocated for books
    struct Book *current = library;
    while (current != NULL)
    {
        struct Book *temp = current;
        current = current->next;
        free(temp);
    }

    return 0;
}
