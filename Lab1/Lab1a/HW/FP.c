#include <stdio.h>
#include <stdint.h>

int main(int argc, char* argv[]) {
//   int count = 0;
//   float cap = 16777218;

//   for (float i = 0; i < cap; i++) {
//     count++;
//   }

  //printf("This iterated %d times\n", count);

    unsigned x = 0x40700000;
     
    printf("%f\n", *(float*)&x);
  return 0;
}


