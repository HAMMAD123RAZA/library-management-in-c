#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <stdlib.h>

void addRecord();
void editRecord();
void deleteRecord();
void showRecord();
void serchBook();
struct book
{
    char name[100];
    char autherName[100];
    int pages;
};
struct book std;
int main()
{

    system("cls");
    printf("1 - add book\n");
    printf("2 - edit book\n");
    printf("3 - delete book\n");
    printf("4 - show books\n");
    printf("5 - search book\n");
    printf("6 - exit\n");
    int choice;
    
    printf("enter choice\n");
    scanf("%d", &choice);
    
    switch (choice)
    {
    case 1:
        addRecord();
        break;
    case 2:
        editRecord();
        break;
    case 3:
        deleteRecord();
        break;
    case 4:
        showRecord();
        break;
    case 5:
        serchBook();
        break;
    case 6:
        return 0;
        break;

    default:
        printf("enter correct number\n");
        main();
        break;
    }
}

void addRecord()
{
    system("cls");
    FILE *ptr;
    ptr = fopen("a.txt", "ab");
    printf("enter Book name:");
    scanf("%s", &std.name);
    printf("enter auther name:");
    scanf("%s", &std.autherName);
    printf("enter book pages:");
    scanf("%d", &std.pages);
    fwrite(&std, sizeof(std), 1, ptr);
    fclose(ptr);
    printf("enter any key\n");
    getch();
    main();
}


void showRecord()
{
    system("cls");
    printf("book name\tauther\tno of pages\n");
    FILE *ptr;
    ptr = fopen("a.txt", "rb");
    while (fread(&std, sizeof(std), 1, ptr))
    {
        printf("%s\t\t%s\t\t%d\n", std.name, std.autherName, std.pages);
    }
    fclose(ptr);
    printf("enter any keys\n");
    getch();
    main();
}

void deleteRecord()
{
    system("cls");
    FILE *ptr, *ptr2;
    ptr = fopen("a.txt", "rb");
    ptr2 = fopen("temp.txt", "ab");

    char name[100];
    printf("enter book name\n");
    scanf("%s", name);

    int found = 0;
    while (fread(&std, sizeof(std), 1, ptr) == 1)
    {
        if (strcmp(name, std.name) != 0)
        {
            fwrite(&std, sizeof(std), 1, ptr2);
        }
        else
        {
            found = 1;
        }
    }
    
    fclose(ptr);
    fclose(ptr2);
    remove("a.txt");
    rename("temp.txt", "a.txt");

    if (found)
    {
        printf("Book deleted successfully!\n");
    }
    else
    {
        printf("Book not found!\n");
    }

    printf("Enter any key to return to the main menu:");
    getch();
    main();
}

void editRecord()
{
    system("cls");
    FILE *ptr;
    ptr = fopen("a.txt", "rb+");

    char name[100];
    printf("enter book name\n");
    scanf("%s", name);

    int found = 0;
    while (fread(&std, sizeof(std), 1, ptr) == 1)
    {
        if (strcmp(name, std.name) == 0)
        {
            found = 1;
            printf("enter updated Book name");
            scanf("%s", std.name);
            printf("enter updated auther name");
            scanf("%s", std.autherName);
            printf("enter updated book pages");
            scanf("%d", &std.pages);

            fseek(ptr, -sizeof(std), SEEK_CUR);
            fwrite(&std, sizeof(std), 1, ptr);
            break;
        }
    }

    fclose(ptr);

    if (found)
    {
        printf("Book updated successfully!\n");
    }
    else
    {
        printf("Book not found!\n");
    }

    printf("Enter any key to return to the main menu:");
    getch();
    main();
}

void serchBook()
{
    system("cls");
    char name[100];
    FILE *ptr;
    ptr = fopen("a.txt", "rb");
    printf("enter book name\n");
    scanf("%s", name);

    int found = 0;
    while (fread(&std, sizeof(std), 1, ptr))
    {
        if (strcmp(name, std.name) == 0)
        {
            found = 1;
            printf("book name is %s\n", std.name);
            printf("book auther is %s\n", std.autherName);
            printf("book pages is %d\n", std.pages);
        }
    }
    fclose(ptr);

    if (!found)
    {
        printf("Book not found!\n");
    }

    printf("Enter any key to return to the main menu:");
    getch();
    main();
}
