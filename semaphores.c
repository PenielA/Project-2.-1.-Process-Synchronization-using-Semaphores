/*------------------------------------------------------*/
/* Skeleton for the synchronization Lab .   assignment 	*/
/*------------------------------------------------------*/
/* Note:						                        */
/* -----						                        */
/* 1. E = Elephant					                    */
/* 2. D = Dog						                    */
/* 3. C = Cat					                    	*/
/* 4. M = Mouse						                    */
/* 5. P = Parrot					                    */
/*------------------------------------------------------*/

#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

#define  CHILD		0       /* Return value of child proc from fork call */

int main()
{
    //sem_t * mutex;          /* my semaphores */
    
    int pid;		/* Process id after fork call */
    int i;		/* Loop index. */
    int N;		/* Number of requests to process */
    int status;  	/* Exit status of child process. */
    int type;           /* Type of animal */

   sem_t *EM_mutex;   
   sem_t *DC_mutex;   
   sem_t *CP_mutex;   
   sem_t *MP_mutex;   
  
    /*   Initialization of the semaphores   */
if ((EM_mutex = sem_open("semaphore 1", O_CREAT, 0644, 1)) == SEM_FAILED) {
    perror("semaphore initilization");
    exit(1);
  }     
if ((DC_mutex = sem_open("semaphore 2", O_CREAT, 0644, 1)) == SEM_FAILED) {
    perror("semaphore initilization");
    exit(1);
  }   
if ((CP_mutex = sem_open("semaphore 3", O_CREAT, 0644, 1)) == SEM_FAILED) {
    perror("semaphore initilization");
    exit(1);
  }   
if ((MP_mutex = sem_open("semaphore 4", O_CREAT, 0644, 1)) == SEM_FAILED) {
    perror("semaphore initilization");
    exit(1);
  }   
    printf("How many requests to be processed: \n");
    scanf("%d",&N);

    for (i=1; i<=N; i++) {
        printf("Who wants in (E=1)(D=2)(C=3)(M=4)(P=5): \n");
        fflush(stdout);
        scanf("%d",&type);
        if ((pid = fork()) == -1) {
   	        /* Fork failed! */
	        perror("fork");
	        exit(1);
        }
        
        
        if (pid == CHILD) {
	        pid = getpid();
            switch (type) {

		    case 1: /* Elephant code*/
                    printf("     Elephant process with pid %d wants in.\n",pid);
                    fflush(stdout);
                    sem_wait(EM_mutex);
                    printf("     Elephant process with pid %d is in.\n",pid);
                    fflush(stdout);
                    sleep(1);
                    printf("     Elephant process with pid %d is out.\n",pid);
                    fflush(stdout); 
                    sem_post(EM_mutex);
                    break;

		    case 2:  /*Dog code*/
                    printf("     Dog process with pid %d wants in.\n",pid);
                    fflush(stdout);
                    sem_wait(DC_mutex);
                    printf("     Dog process with pid %d is in.\n",pid);
                    fflush(stdout);
                    sleep(1);
                    printf("     Dog process with pid %d is out.\n",pid);
                    fflush(stdout);
                    sem_post(DC_mutex);
		            break;

		    case 3: /*Cat Code*/
                    printf("     Cat process with pid %d wants in.\n",pid);
                    fflush(stdout);
                    sem_wait(DC_mutex);
                    sem_wait(CP_mutex);
                    printf("     Cat process with pid %d is in.\n",pid);
                    fflush(stdout);
                    sleep(1);
                    printf("     Cat process with pid %d is out.\n",pid);
                    fflush(stdout);
                    sem_post(DC_mutex);
                    sem_post(CP_mutex);
		            break;

		    case 4: /*Mouse code*/
                    printf("     Mouse process with pid %d wants in.\n",pid);
                    fflush(stdout);
                    sem_wait(EM_mutex);
                    sem_wait(MP_mutex);
                    printf("     Mouse process with pid %d is in.\n",pid);
                    fflush(stdout);
                    sleep(1);
                    printf("     Mouse process with pid %d is out.\n",pid);
                    fflush(stdout); 
                    sem_post(EM_mutex);
                    sem_post(MP_mutex);
		            break;
		
		    case 5: /*Parrot  Code*/
                    printf("     Parrot process with pid %d wants in.\n",pid);
                    fflush(stdout);
                    sem_wait(CP_mutex);
                    sem_wait(MP_mutex);
                    printf("     Parrot process with pid %d is in.\n",pid);
                    fflush(stdout);
                    sleep(1);
                    printf("     Parrot process with pid %d is out.\n",pid);
                    fflush(stdout);
                    sem_post(CP_mutex);
                    sem_post(MP_mutex);
		            break;
            }
            exit(0);
        }
    }
    
    /* Now wait for the child processes to finish */
    for (i=1; i<=N; i++) {
        pid = wait(&status);
        printf("Child (pid = %d) exited with status %d.\n", pid, status);
        fflush(stdout);
    }
}


