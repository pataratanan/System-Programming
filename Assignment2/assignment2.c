/* waitdemo2.c - shows how parent gets child status
 */

//Pataratanan Visitserngtrakul 20310367

#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <time.h>
#include <sys/types.h>
#define DELAY

void child1(){
    int num[9];
    int i;
    float sum;
    float average,highest;
    
    printf("Child->%d here. will calculate average mark.\n",getpid());
    printf("Enter 8 marks: \n");
    
    sum = 0;
    highest = 0;
    
    //for loop to find the average of 8 elements and the highest numbers
    for(i=1; i<9; i++){
        printf("Enter #(%d):",i);
        scanf("%d", &num[i]);
        sum += num[i];
        if(num[i] > highest){
            highest = num[i];
        }
    }
    
    average = sum/8;
    
    //normal printf syntax
    printf("Average mark: %.2f, ", average);
    printf("The highest mark: %.2f\n", highest);
    
    _exit(0);
}
void child2(const char *file){
    //get the child2 id
    printf("\nChild->%d here. Will execute command wc.\n",getpid());
    //-w to count the word of "file" file is the name we provide when executed
    execlp("wc","wc","-w",file,NULL);
    _exit(0);
}
void child3(const char *file){
    printf("Child->%d here. Will update file.\n",getpid());
    printf("\nIt has been updated. Total words count\n");

    char c[256]; //giving 256 bytes of maximum file size

    
    snprintf(c,sizeof(c),
             //sed = stream editor
             "sed -i in-place \"s/execute/run/g\" %s;"// The g/ means global replace i.e. find all occurrences of foo and replace with bar using sed. If you removed the /g only first occurrence is changed:
           //-i is to use specific in my ubuntu because I'm using mac
    "sed -i in-place '1s/^/This is the updated version./' %s;",file,file);

    //bash calls the program bash as interpreter and the -c flag means execute the following command as interpreted by this program.
    execlp("bash", "bash", "-c", c, NULL);
    
    
    _exit(0);
}
/*
* parent waits for child then prints a message
*/
//parent code is for showing when any childs end
void parent_code(int childpid)
{
int wait_rv; /* return value from wait() */
int child_status;
int high_8, low_7, bit_7;
    
wait_rv = wait(&child_status);

printf("done waiting for child->%d.\n", wait_rv);
    
high_8 = child_status >> 8; /* 1111 1111 0000 0000 */
printf("status: exit=%d\n\n", high_8);
}

int main(int argc, char *argv[])
{
    int newpid;
    int pid1,pid2,pid3;

    
    if ((pid1 = fork()) == 0)
      child1();
        
    if ((pid2 = fork()) == 0)
      child2(argv[1]);
    
    if ((pid3 = fork()) == 0)
      child3(argv[2]);
    
    //I need to loop i < 3 because I have 3 childs to provide their exit status
    for(int i = 0; i < 3; i++){
      parent_code(getpid());
    }
    //wait the child to exit
    waitpid(pid1, NULL, 0);
    waitpid(pid2, NULL, 0);
    waitpid(pid3, NULL, 0);
    return 0;
}
