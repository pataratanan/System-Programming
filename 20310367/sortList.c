/* Pataratanan Visitserngtrakul 20310367
 *
 * I hereby certify that no part of this assignment or product has been submitted by me in another (previous or current) assessment,
 * except where appropriately referenced, and with prior permission from the Lecturer/Tutor/Unit Coordinator for this unit.*/

//
// Created by Pataratanan Visitserngtrakul on 21/4/21.
//
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
typedef struct iorb {
    int base_pri;
    struct iorb *link; //a linked list node = variable name link
    char filler[100];
} IORB;
IORB *head = NULL; //Declaring and initializing head of the list as NULL
void bubbleSort(int arr[],int n);
int sortedInsert(IORB** head, IORB* node);



int priComp(int priority){
    return 119 - priority;
}
void sortList(IORB **head, int(*prio)(int)){
    //Initialize sorted linked list as NULL
    IORB *sorted = NULL;
    // Traverse the given linked list and insert every node to sorted
    IORB *curr = *head;

    while(curr != NULL){
        // Store next for next iteration
        IORB *next = curr->link; //-> use to access a member of a struct which is referenced by the pointer

        // insert current in sorted linked list
        sortedInsert(&sorted, curr);

        // Update current
        curr = next;
    }
    // Update head to point to sorted linked list
    *head = sorted;
}

void bubbleSort(int arr[],int n){
    int i = 0, j = 0, tmp;
    for (i = 0; i < n; i++) {   // loop n times - 1 per element
        for (j = 0; j < n - i - 1; j++) { // last i elements are sorted already
            if (arr[j] > arr[j + 1]) {  // swap if order is broken
                tmp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = tmp;
            }
        }
    }
}

int sortedInsert(IORB** head, IORB* node) //IORB **head means second pointer keep the address of the first pointer
                                          // and the first pointer keep the address of head and
                                          // the data type of head is the member in IORB
{
    IORB* curr;
    if (*head == NULL || priComp((*head)->base_pri) >= priComp(node->base_pri))
    {
        node->link = *head;
        *head = node;
        //if head is null or head > node. these two node interchange their position

        bubbleSort(*head,&node); //bubble here...
    }
    else
    {
        //Locate the node before the point of insertion
        curr = *head;
        //Traversing till priority of curr request less than the node request
        while (curr->link != NULL && priComp(curr->link->base_pri) < priComp(node->base_pri)) {
            curr = curr->link;
        }
        node->link = curr->link;
        curr->link = node;
    }
    return 0;
}

