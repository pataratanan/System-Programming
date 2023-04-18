/* Pataratanan Visitserngtrakul 20310367
 *
 * I hereby certify that no part of this assignment or product has been submitted by me in another (previous or current) assessment,
 * except where appropriately referenced, and with prior permission from the Lecturer/Tutor/Unit Coordinator for this unit.*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "sortList.c"

void buildList(int n) {
    IORB *prev;

    // generating loop of list length n
    for (int i = 0; i < n; i++) {
        IORB *tmp = malloc(sizeof(IORB)); //Define *tmp to dynamic memory allocation
        //malloc can returns null

        // assigning priority using random number generator
        tmp->base_pri = rand()%100;
        // Storing the request number in filler
        tmp->filler[0] = i;
        // assigning head if generated request is first request
        if (i == 0) {
            head = tmp;
            prev = head;    //after this, head = tmp and prev = head
        }
        else  {
            prev->link = tmp;
            prev = tmp;
        }
    }

    prev->link = NULL;
}
void displayList() {
    IORB *curr = head;
    // Display till end of List
    while(curr != NULL) {
        printf("Description: this is i/o request %d, Base Priority: %d Priority: %d\n",
               curr->filler[0],curr->base_pri,priComp(curr->base_pri));

        curr = curr->link;
    }
    // priComp(curr->base_pri) based on the integer(based priority) passed to it.
    // the formula is 119-priority. (based priority) generate by rand()%100;
}
int main() {
    srand(time(0)); //Initializing seed for rand using current time
    while(1) { //while 1 is infinite loop, the condition is always true
        int option;
        printf("0) Exit\n1) Build List\n2) Sort List (ascending)\n3) Display List\n");
        printf("Please choose your choice..\n");
        scanf("%d",&option);
        if (option == 0) {
            //Exit
            printf("Terminating...\n");
            break;
        }
        if (option == 1) {
            //to build the list

            //printf("Please input your length..\n");
            //int n;
            //scanf("%d",&n);
            buildList(10); //provide the argument (n) length of buildList
        }
        if (option == 2) {
            //sorted the list
            sortList(&head,priComp);
        }
        if(option == 3){
            //to display the list
            displayList();
        }
//        char *abc[100];
//        scanf("%d",&abc);
//        if(abc > 1 ){
//            break;
//        }

    }
    return 0;
}
