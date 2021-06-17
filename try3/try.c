#include<stdio.h>
#include <unistd.h>


void summer(void) {
  int x = 3;
  if (fork()) {
    if (fork()) {
      x += 7;
	fork(); }
	} else { x += 2;
  	}
  
printf("%d \n", x);
  if (fork()) {
	x -= 6; 
	} else {
	x -= 1; 
	printf("%d \n", x); 
	fork(); 
	printf("Bye \n");
	}
//exit(0); }
//printf("good\n");
}

int main(){

	summer();
	return 0;

}
