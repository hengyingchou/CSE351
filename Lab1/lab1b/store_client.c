// Written by Porter Jones (pbjones@cs.washington.edu)
//
// This is a file for managing a store of various aisles,
// represented by an array of 64-bit integers

#include <stddef.h>  // To be able to use NULL
#include "aisle_manager.h"
#include "store_client.h"
#include "store_util.h"
#include <stdio.h>

// Number of aisles in the store
#define NUM_AISLES 10

// Number of sections per aisle
#define SECTIONS_PER_AISLE 4

// Number of items in the stockroom (2^6 different id combinations)
#define NUM_ITEMS 64

// Global array of aisles in this store. Each unsigned long in the array
// represents one aisle.
unsigned long aisles[NUM_AISLES];

// Array used to stock items that can be used for later. The index of the array
// corresponds to the item id and the value at an index indicates how many of
// that particular item are in the stockroom.
int stockroom[NUM_ITEMS];


/* Starting from the first aisle, refill as many sections as possible using
 * items from the stockroom. A section can only be filled with items that match
 * the section's item id. Priotizes and fills sections with lower addresses
 * first. Sections with lower addresses should be fully filled (if possible)
 * before moving onto the next section.
 */
void refill_from_stockroom() {
  // TODO: implement this function

  int i = 0;
  unsigned short ID = 0;
  int num;
  for(i = 0 ; i < NUM_AISLES  ; i++){
    for(int j = 0; j < SECTIONS_PER_AISLE ;j++){
        ID = get_id(&aisles[i],j );
        num = num_items(&aisles[i],j );
        num = 10-num;
        add_items(&aisles[i],j,stockroom[ID]);
        stockroom[ID] -= num;
        if(stockroom[ID] < 0) stockroom[ID] = 0;
        
    }
  }
}

/* Remove at most num items from sections with the given item id, starting with
 * sections with lower addresses, and return the total number of items removed.
 * Multiple sections can store items of the same item id. If there are not
 * enough items with the given item id in the aisles, first remove all the
 * items from the aisles possible and then use items in the stockroom of the
 * given item id to finish fulfilling an order. If the stockroom runs out of
 * items, you should remove as many items as possible.
 */
int fulfill_order(unsigned short id, int num) {
  // TODO: implement this function

  int i = 0;
  int max = num;
  unsigned short ID = 0;
  int count = 0;
  int num2;

  for(i = 0 ; i < NUM_AISLES  ; i++){
    for(int j = 0; j < SECTIONS_PER_AISLE ;j++){

      ID = get_id(&aisles[i],j);
      if(ID == id){
      num2 = num_items(&aisles[i],j);
      remove_items(&aisles[i],j,num);
      //printf("num2 = %d, num = %d\n",num2,num);
      num -= num2;
      count += num2;
      //printf("I am here\n");
      if(num < 0) return max;  
    }
  }
  }
  if(num > 0 && stockroom[id] >= num){
        count += num;
        stockroom[id] -= num;

        
        
  }else if(num > 0 && stockroom[id] < num){
        count+= stockroom[id];
        num -= stockroom[id];
        stockroom[id] = 0;
        
  }
    return count;

}


/* Return a pointer to the first section in the aisles with the given item id
 * that has no items in it or NULL if no such section exists. Only consider
 * items stored in sections in the aisles (i.e., ignore anything in the
 * stockroom). Break ties by returning the section with the lowest address.
 */
unsigned short* empty_section_with_id(unsigned short id) {
  // TODO: implement this function

  int i;
  int j;
  int number;
  int ID;
  //unsigned long temp = 0x1;
  unsigned long temp2;
  for(i = 0; i < NUM_AISLES ; i++){
    for(j = 0 ; j < SECTIONS_PER_AISLE ; j++){

      number = num_items(&aisles[i], j);
      ID = get_id(&aisles[i], j);

      //printf("number = %d\n",number);
      // printf("id = %d\n",id);
      // printf("ID = %d\n",ID);
  
      if(number == 0 && ID == id){
        // printf("i = %d\n",i);
        // printf("j = %d\n",j);
        // printf("id = %d\n",id);
        // printf("ID = %d\n",ID);
        // printf("I am goint to return\n");
        //temp2 = (unsigned long) &aisles[i];
        if(j == 0) temp2 = (unsigned long) &aisles[i];
        if(j == 1) temp2 = (unsigned long) &aisles[i] + (unsigned long) 0x2;
        if(j == 2) temp2 = (unsigned long) &aisles[i] + (unsigned long) 0x4;
        if(j == 3) temp2 = (unsigned long) &aisles[i] + (unsigned long) 0x6;
        
        return (unsigned short*) temp2;
    }
    }
  }
  
  return NULL;
}

/* Return a pointer to the section with the most items in the store. Only
 * consider items stored in sections in the aisles (i.e., ignore anything in
 * the stockroom). Break ties by returning the section with the lowest address.
 */
unsigned short* section_with_most_items() {
  // TODO: implement this function
  int i;
  int j;
  int number;
  int max_number = 0;
  int max_i = 0;
  int max_j = 0;
  
  unsigned long temp2;
  for(i = 0; i < NUM_AISLES ; i++){
    for(j = 0 ; j < SECTIONS_PER_AISLE ; j++){

      number = num_items(&aisles[i], j);
      if(number > max_number){
        max_number = number;
        max_i = i;
        max_j = j;

      }     
    }
  }
  
 

        // printf("i = %d\n",i);
        // printf("j = %d\n",j);
        // printf("id = %d\n",id);
        // printf("ID = %d\n",ID);
        // printf("I am goint to return\n");
        //temp2 = (unsigned long) &aisles[i];
  if(max_j == 0) temp2 = (unsigned long) &aisles[max_i];
  if(max_j == 1) temp2 = (unsigned long) &aisles[max_i] + (unsigned long) 0x2;
  if(max_j == 2) temp2 = (unsigned long) &aisles[max_i] + (unsigned long) 0x4;
  if(max_j == 3) temp2 = (unsigned long) &aisles[max_i] + (unsigned long) 0x6;
        
  return (unsigned short*) temp2;




  
}

