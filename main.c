#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef enum
{
    todoMake = 1,
    todoView = 2,
    todoDelete = 3,
    todoQuit = 4
} todoOptions;

typedef struct
{
    char todo[100];
    bool completed;

} todoStructer;

int main()
{
    int choice = 0;
    int isUser = 0;
    int todoNum = 0;
    int todoCount = 0;
    bool intro = true;
    char buffer[1024] = {0};
    char status = '\0';
    todoStructer *todos = NULL;
    FILE *pfile = NULL;
    FILE *pCounterFile = NULL;

    pCounterFile = fopen("todo_count.txt", "r");
    if (pCounterFile != NULL)
    {
        fscanf(pCounterFile, "%d", &todoCount);
        fclose(pCounterFile);
    }

    while (1)
    {
        system("cls");

        if (intro == true)
        {
            printf("***WELCOME TO YOUR TO-DO LIST***\n\n");
            intro = false;
        }

        printf("What do you want to do?\n\n");
        printf("1. Make To-Do's\n2. View To-Do's\n3. Delete To-Do's\n4. Quit To-Do's\n\n");
        printf("Enter your option: ");
        scanf(" %d", &choice);

        switch (choice)
        {
        case 1:
            isUser = todoMake;
            break;
        case 2:
            isUser = todoView;
            break;
        case 3:
            isUser = todoDelete;
            break;
        case 4:
            isUser = todoQuit;
            break;
        default:
            system("cls");
            printf("Error, Did not enter a vailid option!");
            return 1;
        }

        if (isUser == todoMake)
        {
            system("cls");
            printf("How many To-Do's do you want to make?: ");
            scanf(" %d", &todoNum);

            if (todoNum <= 0)
            {
                system("cls");
                printf("Error, Did not enter a vailid option!");
                return 1;
            }

            todos = malloc(todoNum * sizeof(todoStructer));

            if (todos == NULL)
            {
                printf("Error, Memory faild to be allocated!");
                return 1;
            }

            for (int i = 0; i < todoNum; i++)
            {
                printf("What is your #%d To-Do?: ", i + 1);
                scanf(" %[^\n]", todos[i].todo);
                printf("Is your #%d To-Do Completed? (Y/N): ", i + 1);
                scanf(" %c", &status);

                if (status == 'y' || status == 'Y')
                {
                    todos[i].completed = true;
                }
                else if (status == 'n' || status == 'N')
                {
                    todos[i].completed = false;
                }
                else
                {
                    system("cls");
                    printf("Error, Did not enter a vailid option!");
                    return 1;
                }
            }

            pfile = fopen("todo_list.txt", "r");
            if (pfile != NULL)
            {
                fclose(pfile);
                pfile = fopen("todo_list.txt", "a");
            }
            else
            {
                pfile = fopen("todo_list.txt", "w");
            }

            if (pfile == NULL)
            {
                printf("Error, Could not save To-Do's!");
                free(todos);
                return 1;
            }

            for (int i = 0; i < todoNum; i++)
            {
                todoCount++;
                fprintf(pfile, "#%d\nTo-Do: %s\nCompleted: %s\n\n", todoCount, todos[i].todo, todos[i].completed ? "Yes" : "No");
            }

            fclose(pfile);

            pCounterFile = fopen("todo_count.txt", "w");
            if (pCounterFile != NULL)
            {
                fprintf(pCounterFile, "%d", todoCount);
                fclose(pCounterFile);
            }

            free(todos);
        }
        else if (isUser == todoView)
        {
            system("cls");
            pfile = fopen("todo_list.txt", "r");
            if (pfile == NULL)
            {
                printf("Error, No To-Do's Found!\n");
            }
            else
            {
                while (fgets(buffer, sizeof(buffer), pfile) != NULL)
                {
                    printf("%s", buffer);
                }
                fclose(pfile);
            }
            system("pause");
        }
        else if (isUser == todoDelete)
        {
            system("cls");
            remove("todo_count.txt");
            remove("todo_list.txt");
            printf("Sucssesfuly deleted To-Do's\n");
            system("pause");
        }
        else if (isUser == todoQuit)
        {
            system("cls");
            printf("Thank you for useing the To-Do List!");
            return 0;
        }
    }

    if (todos != NULL)
    {
        free(todos);
    }

    todos = NULL;

    return 0;
}