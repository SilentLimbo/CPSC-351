/**
 * A pthread program illustrating how to
 * create two threads, and what happens if you lock/don't lock them
 * and try to print to the (shared) stdout buffer
 * with/without locking the buffer with a pthread_mutex_t
 * 
 * clang print_threads.c -lpthread -g -o print_threads
 *
 */

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <pthread.h>

pthread_mutex_t lock;    // lock is shared between threads

char four_score[] = "Four score and seven years ago our fathers brought forth, upon this continent, a new nation, conceived in liberty, and dedicated to the proposition that all men are created equal.";
char o_temp[]     = "012345678901234567890123456789-012345789-0123456789-0123456789-0123456789-012345678-0123456789-0123456789-0123456789-0123456789-0123456789-0123456789-0123456789-0123456789-0123456";


void* runner0(void* param) {
	int i, id = (int)(long)param;
 int n = strnlen(four_score, BUFSIZ);

  printf("#%d entering\n", id);
  char *s = "one", *t = "two", *u = "three";
  usleep(1000);

  pthread_mutex_lock(&lock);
  for (int i = 0; i < n; ++i) { 
    printf("%c", o_temp[i]);    
  } 
  pthread_mutex_unlock(&lock);
  usleep(10);                   // sleeps for 10 us (microseconds)
  
	printf("\n#id: %d exiting\n", id);
	pthread_exit(0); 
}

void* runner1(void* param) { 
 	int i, id = (int)(long)param;
   int n = strnlen(four_score, BUFSIZ);

  printf("\n\t#%d entering\n", id);
  char *p = "usleep", *q = "in", *r = "Unix";

  // pthread_mutex_lock(&lock);
  for (int i = 0; i < n; ++i) { 
    printf("%c", four_score[i]);
    usleep(10); 
  }
  // pthread_mutex_unlock(&lock);

	printf("\n\t#id: %d exiting\n", id);
	pthread_exit(0); 
}
int get_cmd_arg(int argc, char* argv[]) { 
	if (argc != 2) {
		fprintf(stderr, "usage: a.out <integer value>\n");
		/*exit(1);*/
		return -1;
	}
	int arg = atoi(argv[1]);
	
	if (arg < 0) {
		fprintf(stderr,"Argument %d must be non-negative\n", atoi(argv[1]));
		/*exit(1);*/
		return -1;
	}
	return arg;
}

int main(int argc, char *argv[]) {
	pthread_t tid0, tid1; /* the thread identifier */
	pthread_attr_t attr; /* set of attributes for the thread */

	// int arg = get_cmd_arg(argc, argv);
	
  setbuf(stdout, NULL);
	pthread_attr_init(&attr);

	pthread_create(&tid0, &attr, runner0, (void*)0);
	pthread_create(&tid1, &attr, runner1, (void*)1);

	pthread_join(tid0, NULL);
	pthread_join(tid1, NULL); 
  printf("\n");
}

