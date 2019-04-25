// k-lib.c, 159

#include "k-include.h"
#include "k-type.h"
#include "k-data.h"

// clear DRAM data block, zero-fill it
void Bzero(char *p, int bytes) {
	while (bytes--)
		*p++ = '\0';
}

int QisEmpty(q_t *p) { // return 1 if empty, else 0
	return (p->tail == 0);
}

int QisFull(q_t *p) { // return 1 if full, else 0
	return (p->tail == Q_SIZE);
}

// dequeue, 1st # in queue; if queue empty, return -1
// move rest to front by a notch, set empty spaces -1
int DeQ(q_t *p) { // return -1 if q[] is empty
   int i, ret;

   if(QisEmpty(p)) {
      cons_printf("Panic: queue is empty, cannot DeQ!\n");
      return NONE;
   }
   
   
   ret = p->q[0];	//set return value to from front of queue
   p->tail--;		//move tail back
   

   //shift everything to the front by 1
   for(i = 0; i < p->tail; i++)	
	   p->q[i] = p->q[i + 1];
   
   //clear out 'old' entries
   for(i = p->tail; i < Q_SIZE; i++)
	   p->q[i] = NONE;
   return ret;
}

// if not full, enqueue # to tail slot in queue
void EnQ(int to_add, q_t *p) {
   if(QisFull(p)) {
	   cons_printf("Panic: queue is full, cannot EnQ!\n");
	   breakpoint();
      return;	
   }
   
   p->q[p->tail] = to_add;	//add item to current end
   p->tail++;	//increment tail position
}

void MemCpy(char *dst, char *src, int size){
  while(size--){
    *dst = *src;
    dst++;
    src++;
  }
}

int StrCmp(char *str1, char *str2){
  int compare = 1;
  while(1)
  {
    if(*str1 != *str2){
      compare = 0;
      break;
    }
    if(*str1 == '\0'){
      break;
    }
    str1++;
    str2++;
  }

  return compare;
}

void reverse(char *str, int upper) {
	
    char hold;
    int lower = 0;
    while (lower < upper){
      hold = str[lower];
      str[lower] = str[upper];
      str[upper] = hold;
      lower++;
      upper--;
    }
}

void Itoa(char *str, int x){
  int size = 0;
  while (x > 0){
    *str = 48 + x % 10;
    str++;
    x = x / 10;
    size++;
  }
  str -= size;
  reverse(str, size - 1);
}  
