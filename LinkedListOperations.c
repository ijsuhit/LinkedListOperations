#include<stdio.h>
#include<stdlib.h>

#define HEAD_NULL_ERROR_MSG "\n\nError : 'Head' is invalid! Contains NULL!"
#define INVALID_INPUT_ERROR_MSG "\nError : Invalid input... Could not contine the operation!"
#define MEMORY_ERROR_MSG "Error : Memory Error Occurred!"
#define SUCCESS 1
#define FAILED 0

/* Structure of NODE */
struct node {
    int data;
    struct node *next;
};

void linkedListOperations();
int insertNode(struct node **head, int nodesCount);
int deleteNode(struct node **head, int nodesCount);
void displayList(struct node *current);
void reverseLinkedList(struct node **head);
int deleteLinkedList(struct node **head);
void printLinkedListMenu();

int main() {
    linkedListOperations();
    return 0;
}

/*
    All Linked List Operations are carried from here
    No list is present prior to this function
*/
void linkedListOperations() {
    int choice;
    int nodesCount = 0;
    int success;
    struct node *head = NULL;

    printf("**************** Start Linked List Operations *****************");
    do {
        printLinkedListMenu();
        printf("\nEnter your choice : ");
        scanf("%d", &choice);

        switch(choice) {
            case 1:
                printf("\n\n************   Insert Node   *********************");
                success = insertNode(&head, nodesCount);
                if(success) {
                    nodesCount++;
                    printf("\nNew node inserted successfully into the Linked List! The list is : ");
                    displayList(head);
                } else {
                    printf("\n\nInsertion of new node failed!");
                }
                printf("\n\n************   End Insert Node   *********************");
                break;
            case 2:
                printf("\n\n************   Delete Node   *********************");
                if(head) {
                    success = deleteNode(&head, nodesCount);
                    if(success) {
                        nodesCount--;
                        printf("\n\nDeletion of node successful! The list is : ");
                        displayList(head);
                    } else {
                        printf("\n\nDeletion of node failed!");
                    }
                } else {
                    printf("\n\nList is empty. Deletion cannot be done!");
                }

                printf("\n\n************   End Delete Node   *********************");
                break;
            case 3:
                printf("\n\n************   Display Linked List   *********************");
                displayList(head);
                printf("\n\n************   End Display Linked List   *********************");
                break;
            case 4:
                printf("\n\n************   Get Nodes Count   *********************");
                printf("\n\nNo. of nodes in the Linked List = %d", nodesCount);
                printf("\n\n************   End Get Nodes Count   *****************");
                break;
            case 5:
                printf("\n\n************   Reverse Linked List   *********************");
                if(head == NULL) {
                    printf("\n\nLinked List does not exist to reverse!");
                } else {
                    reverseLinkedList(&head);
                    printf("\n\nLinked List is reversed successfully!");
                    displayList(head);
                }
                printf("\n\n************   End Reverse Linked List   *********************");
                break;
            case 6:
                printf("\n\n************   Delete Linked List   *********************");
                if(head == NULL) {
                    printf("\n\nLinked List does not exist to delete!");
                } else {
                    success = deleteLinkedList(&head);
                    if(success) {
                        printf("\n\nLinked List is deleted successfully");
                        nodesCount = 0;
                    }
                }
                printf("\n\n************   End Delete Linked List   *********************");
                break;
            case 7:
                system("cls");
                break;
            case 8:
                break;
            default:
                printf(INVALID_INPUT_ERROR_MSG);
        }
        if(choice != 7 && choice != 8) {
            printf("\n\n\tPress Enter to Continue...\t");
            fflush(stdin);
            getchar();
            fflush(stdin);
        }
    } while(choice != 8);

    deleteLinkedList(&head);
}

// Function to insert a node into the Linked List at any given position
// Head of the linked list is passed as argument
// Pre-condition : The argument 'head' must be valid
// Returns 1 on successful insertion, else returns 0

int insertNode(struct node **head, int nodesCount) {
    struct node *newNode = (struct node *) malloc(sizeof(struct node));
    struct node *temp = *head;
    int position;

    if(newNode == NULL) {
        printf(MEMORY_ERROR_MSG);
        return FAILED;
    }

    printf("\nEnter a position to insert new node... (You can enter -1 if you want to insert at the end) : ");
    scanf("%d", &position);

    if((position != -1 && position < 1) || position > nodesCount + 1) {
        printf(INVALID_INPUT_ERROR_MSG);
        return FAILED;
    }
    printf("\nEnter an integer into the node : ");
    scanf("%d", &(newNode -> data));

    /*
    * The fact that control reached this point means the scenario is valid. If *head == NULL we have to insert at the beginning
    * If *head == NULL we will reach here only if position == 1 or position == -1. So we can directly check and add node to *head
    * Also, we are handling position == 1 case here itself. Insertion at position 1 is a special case compared to others
    * And it fits in here so well. So we are making that here itself instead of making many checks later in the code
    */

    if(*head == NULL || position == 1) {
        *head = newNode;
        newNode -> next = temp;
        return SUCCESS;
    }

    if(position == -1) {
        position = nodesCount + 1;
    }

    /*
    * Here we are not doing the conventional while(temp -> next != NULL)
    * The reason is we need a code which would insert at any given position
    * temp -> next != NULL would be a useless check as we already heave total number of nodes
    * So going with the following approach
    */
    position -= 2;                  // To insert at nth position traverse n - 1 nodes. So n - 2 jumps are needed
    while(position > 0) {
        temp = temp -> next;
        position--;
    }
    newNode -> next = temp -> next;
    temp -> next = newNode;
    return SUCCESS;
}

// Function to delete a node from the Linked List from any given position
// Head of the linked list is passed as argument
// Pre-condition : The linked list must contain at least one element
// Returns 1 on successful deletion, else returns 0
// If head is null it returns 0
int deleteNode(struct node **head, int nodesCount) {
    int position;
    struct node *current;
    struct node *prev;

    if(*head == NULL) {
        printf(HEAD_NULL_ERROR_MSG);
        return FAILED;
    }

    printf("\nEnter the position of the node to be deleted... (You can enter -1 if you want to delete the last node) : ");
    scanf("%d", &position);

    if((position != -1 && position < 1) || position > nodesCount) {
        printf(INVALID_INPUT_ERROR_MSG);
        return FAILED;
    }
    if(position == -1) {
        position = nodesCount;
    }

    current = *head;
    if(position == 1) {
        *head = current -> next;
    } else {
        while(--position > 0) {
            prev = current;
            current = current -> next;
        }
        prev -> next = current -> next;
    }
    free(current);
    return SUCCESS;
}

// Function to display the contents of the linked list
// Pre-condition : 'head' must be valid
void displayList(struct node *current) {

    printf("\n\n");
    while(current != NULL) {
        printf("%d -> ", current -> data);
        current = current -> next;
    }
    printf("NULL");
}

// Reverses the linked list
// Pre-condition : 'head' must be valid
void reverseLinkedList(struct node **head) {
    struct node *prev;
    struct node *current;
    struct node *next;

    if(*head == NULL || (*head) -> next == NULL) {
        return;
    }

    prev = NULL;
    current = *head;
    next = current -> next;
    while(next) {
        current -> next = prev;
        prev = current;
        current = next;
        next = current -> next;
    }
    current -> next = prev;
    *head = current;
}

// Function to delete the Linked List
// Head of the linked list is passed as argument
// Pre-condition : The argument 'head' must be valid
// Returns 1 on successful deletion, else returns 0
// If head is null, then nop is performed and 1 is returned
int deleteLinkedList(struct node **head) {
    struct node *current = *head;
    struct node *next = *head;

    *head = NULL;
    while(next) {
        next = next -> next;
        free(current);
    }
    return SUCCESS;
}

// Function to print the menu for Linked List Operations
void printLinkedListMenu() {
    printf("\n\n****************************************");
    printf("\n*\t   Linked List Operations      *\n");
    printf("****************************************\n");

    printf("\n1. Insert Node");
    printf("\n2. Delete Node");
    printf("\n3. Display Linked List");
    printf("\n4. Get Count of Nodes");
    printf("\n5. Reverse Linked List");
    printf("\n6. Delete Linked List");
    printf("\n7. Clear Screen");
    printf("\n8. Exit");
}
