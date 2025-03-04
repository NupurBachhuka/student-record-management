#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct student
 {
    int roll_no;
    char name[100];
    float marks;
    struct student *next;
} node;

node *create_list();
void display(node *);
void count(node *);
void search(node *, int);
node *addatbeg(node *);
node *addatend(node *);
node *addafter(node *, int);
node *addbefore(node *, int);
node *addatpos(node *, int);
node *del(node *, int);
node *reverse(node *);
node *getnode();

int main() 
{
    int choice, data, item, pos;
    node *start;
    start = NULL;

    do {
        printf("ENTER YOUR CHOICE\n");
        printf("1. Create List\n");
        printf("2. Display\n");
        printf("3. Count\n");
        printf("4. Search\n");
        printf("5. Add to empty list / Add at beginning\n");
        printf("6. Add at end\n");
        printf("7. Add after node\n");
        printf("8. Add before node\n");
        printf("9. Add at position\n");
        printf("10. Delete\n");
        printf("11. Reverse\n");
        printf("12. Quit\n\n");

        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                start = create_list();
                break;
            case 2:
                display(start);
                break;
            case 3:
                count(start);
                break;
            case 4:
                printf("Enter the roll number to be searched: ");
                scanf("%d", &data);
                search(start, data);
                break;
            case 5:
                start = addatbeg(start);
                break;
            case 6:
                start = addatend(start);
                break;
            case 7:
                printf("Enter the roll number after which to insert: ");
                scanf("%d", &item);
                start = addafter(start, item);
                break;
            case 8:
                printf("Enter the roll number before which to insert: ");
                scanf("%d", &item);
                start = addbefore(start, item);
                break;
            case 9:
                printf("Enter the position at which to insert: ");
                scanf("%d", &pos);
                start = addatpos(start, pos);
                break;
            case 10:
                printf("Enter the roll number to be deleted: ");
                scanf("%d", &data);
                start = del(start, data);
                break;
            case 11:
                start = reverse(start);
                break;
            case 12:
                exit(0);
            default:
                printf("Wrong choice\n");
        }
    } while (choice != 12);
}

node *create_list() 
{
    int roll;
    float marks;
    char Name[100];
    char ans = 'y';
    node *temp, *new, *start;
    start = NULL;

    do {
        printf("Enter the roll number: ");
        scanf("%d", &roll);

        printf("Enter name of student: ");
        scanf("%s", Name);  // Directly read a single word name (no spaces allowed).

        printf("Enter the marks: ");
        scanf("%f", &marks);

        new = getnode();
        if (new == NULL)
        {
            printf("\nMemory not allocated.\n");
            return start;
        }

        new->roll_no = roll;
        strcpy(new->name, Name);  
        new->marks = marks;

        if (start == NULL)
        {
            start = new;
            temp = start;
        }   
        else  
        {
            temp->next = new;
            temp = new;
        }

        printf("\nDo you want to enter more elements (y/n): ");
        scanf(" %c", &ans);  


    } 
    while (ans == 'y' || ans == 'Y');
    printf("\nThe single linked list is created\n");
    return start;
}

node *getnode() 
{
    node *temp;
    temp = (node *)malloc(sizeof(node));
    temp->next = NULL;
    return temp;
}

void display(node *start) {
    node *p = start;
    if (p == NULL) {
        printf("List is empty\n");
        return;
    }
    printf("List is:\n");
    while (p != NULL) {
        printf("%d | %s | %.2f\n", p->roll_no, p->name, p->marks);
        p = p->next;
    }
    printf("\n");
}

void count(node *start) {
    node *p = start;
    int cnt = 0;
    while (p != NULL) {
        cnt++;
        p = p->next;
    }
    printf("Number of elements are %d\n", cnt);
}
// search using roll number only
void search(node *start, int roll_no) 
{
    node *p = start;
    int pos = 1;

    while (p != NULL) {
        if (p->roll_no == roll_no) {
            // Display the data of the node
           // printf("Item %d found at position %d\n", roll_no, pos);
            printf("Details of the student:\n");
            printf("Roll Number: %d\n", p->roll_no);
            printf("Name: %s\n", p->name);
            printf("Marks: %.2f\n", p->marks);
            return;
        }
        p = p->next;
        pos++;
    }

    // If roll number not found
    printf("Item %d not found in the list.\n", roll_no);
}


node *addatbeg(node *start) {
    node *new = getnode();
    printf("Enter the roll number: ");
    scanf("%d", &new->roll_no);
    printf("Enter the name: ");
    scanf(" %99[^\n]", new->name); 
    printf("Enter the marks: ");
    scanf("%f", &new->marks);

    new->next = start;
    start = new;
    return start;
}

node *addatend(node *start) {
    node *new = getnode(), *p;
    printf("Enter the roll number: ");
    scanf("%d", &new->roll_no);
    printf("Enter the name: ");
    scanf(" %99[^\n]", new->name); 
    printf("Enter the marks: ");
    scanf("%f", &new->marks);

    if (start == NULL) {
        start = new;
    } else {
        p = start;
        while (p->next != NULL)
            p = p->next;
        p->next = new;
    }
    return start;
}

node *addafter(node *start, int item) {
    node *new, *p = start;
    while (p != NULL) {
        if (p->roll_no == item) {
            new = getnode();
            printf("Enter the roll number: ");
            scanf("%d", &new->roll_no);
            printf("Enter the name: ");
            scanf(" %99[^\n]", new->name); 
            printf("Enter the marks: ");
            scanf("%f", &new->marks);

            new->next = p->next;
            p->next = new;
            return start;
        }
        p = p->next;
    }
    printf("%d not present in the list\n", item);
    return start;
}

node *addbefore(node *start, int item) {
    node *new, *p = start, *prev = NULL;
    if (start == NULL) {
        printf("List is empty\n");
        return start;
    }

    if (start->roll_no == item) {
        new = getnode();
        printf("Enter the roll number: ");
        scanf("%d", &new->roll_no);
        printf("Enter the name: ");
        scanf(" %99[^\n]", new->name); 
        printf("Enter the marks: ");
        scanf("%f", &new->marks);

        new->next = start;
        start = new;
        return start;
    }

    while (p != NULL && p->roll_no != item) {
        prev = p;
        p = p->next;
    }

    if (p != NULL) {
        new = getnode();
        printf("Enter the roll number: ");
        scanf("%d", &new->roll_no);
        printf("Enter the name: ");
        scanf(" %99[^\n]", new->name); 
        printf("Enter the marks: ");
        scanf("%f", &new->marks);

        new->next = p;
        prev->next = new;
    } else {
        printf("%d not present in the list\n", item);
    }
    return start;
}

node *addatpos(node *start, int pos) {
    node *new, *p = start;
    int i;

    if (pos == 1) {
        new = getnode();
        printf("Enter the roll number: ");
        scanf("%d", &new->roll_no);
        printf("Enter the name: ");
        scanf(" %99[^\n]", new->name); 
        printf("Enter the marks: ");
        scanf("%f", &new->marks);

        new->next = start;
        start = new;
        return start;
    }

    for (i = 1; i < pos - 1 && p != NULL; i++) {
        p = p->next;
    }

    if (p == NULL) {
        printf("There are less than %d elements\n", pos);
    } else {
        new = getnode();
        printf("Enter the roll number: ");
        scanf("%d", &new->roll_no);
        printf("Enter the name: ");
        scanf(" %99[^\n]", new->name); 
        printf("Enter the marks: ");
        scanf("%f", &new->marks);

        new->next = p->next;
        p->next = new;
    }
    return start;
}

node *del(node *start, int data) {
    node *temp, *p = start;

    if (start == NULL) {
        printf("List is empty\n");
        return start;
    }

    if (start->roll_no == data) {
        temp = start;
        start = start->next;
        free(temp);
        return start;
    }

    while (p->next != NULL) {
        if (p->next->roll_no == data) {
            temp = p->next;
            p->next = temp->next;
            free(temp);
            return start;
        }
        p = p->next;
    }

    printf("Element %d not found\n", data);
    return start;
}

node *reverse(node *start) 
{
    node *prev = NULL, *next = NULL, *p = start;

    while (p != NULL) {
        next = p->next;
        p->next = prev;
        prev = p;
        p = next;
    }
    start = prev;
    return start;
}
