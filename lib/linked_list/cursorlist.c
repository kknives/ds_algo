#include <stdio.h>
#include <stdlib.h>
#define MAX_SIZE 100
typedef int element_t;
typedef size_t offset_t;

const offset_t NULL_OFFSET = 0;
const element_t LIST_HEADER = 0xfeed;
struct CursorNode
{
  element_t val;
  offset_t next;
};

struct CursorNode cursor_space[MAX_SIZE];

offset_t
cursor_alloc(void)
{
  offset_t p = cursor_space[0].next;
  cursor_space[0].next = cursor_space[p].next;
  return p;
}

void
cursor_free(offset_t p)
{
  cursor_space[p].next = cursor_space[0].next;
  cursor_space[0].next = p;
}

void
cursorspace_init()
{
  cursor_space[0].next = 1;
  cursor_space[0].val = MAX_SIZE - 1;
  for (offset_t i = 1; i < MAX_SIZE - 1; i++) {
    cursor_space[i] = (struct CursorNode){ -1, i + 1 };
  }
  cursor_space[MAX_SIZE - 1].next = NULL_OFFSET;
}

static inline int
cursor_is_last(offset_t p)
{
  return cursor_space[p].next == NULL_OFFSET;
}

// Practice exercises
void
practice_q()
{
  cursorspace_init();
  const int members[] = { 21, 24, 12, 5, 15, 7 };
  offset_t head = cursor_alloc(), prev = head;
  cursor_space[head].val = members[0];
  for (int i = 1; i < 6; i++) {
    offset_t p = cursor_alloc();
    cursor_space[prev].next = p;
    cursor_space[p].val = members[i];
    prev = p;
  }
  cursor_space[prev].next = NULL_OFFSET;

  // Question1:
  /* Find the 3rd node from the end of a linked list */
  /* given in the following cursor representation. */
  printf("Question#1: Find the 3rd node from the end of a linked list.\n");
  int len = 0;
  for (offset_t p = head; !cursor_is_last(p); p = cursor_space[p].next) {
    len++;
  }
  int idx = 0;
  for (offset_t p = head; idx < len - 2; p = cursor_space[p].next) {
    if (idx == (len - 3))
      printf("3rd last node has value: %d\n\n", cursor_space[p].val);
    idx++;
  }

  // Question2:
  // Sort the elements of the linked list .
  printf("Question#2: Sort the elements of the linked list\n");
  printf("Before sorting, the order of the elements is as follows:\n");
  for (offset_t p = head; !cursor_is_last(p); p = cursor_space[p].next) {
    printf("%d ", cursor_space[p].val);
  }
  printf("\n");
  int i = 0;
  for (offset_t p = head; i < len - 1; p = cursor_space[p].next) {
    int j = 0;
    for (offset_t q = head; j < len - i - 1; q = cursor_space[q].next) {
      if (cursor_space[q].val > cursor_space[cursor_space[q].next].val) {
        int tmp = cursor_space[q].val;
        cursor_space[q].val = cursor_space[cursor_space[q].next].val;
        cursor_space[cursor_space[q].next].val = tmp;
      }
      j++;
    }
    i++;
  }

  printf("After sorting, the order of the elements is as follows:\n");
  for (offset_t p = head; !cursor_is_last(p); p = cursor_space[p].next) {
    printf("%d ", cursor_space[p].val);
  }
  printf("\n\n");

  // Question 3: Find the 1st largest element in the linked list.
  printf("Question#3: Find the largest element in the linked list\n");
  int hval = 0;
  for (offset_t p = head; !cursor_is_last(p); p = cursor_space[p].next) {
    hval = cursor_space[p].val;
  }
  printf("The largest element is: %d\n\n", hval);

  // Question 4:
  /*   Find the first 3 smallest element from the */
  /* linked list. */
  printf(
    "Question#4: Find the first 3 smallest elements from the linked list\n");
  printf("The smallest 3 elements are: ");
  i = 0;
  for (offset_t p = head; i < 3; p = cursor_space[p].next) {
    printf("%d ", cursor_space[p].val);
    i++;
  }
  printf("\n\n");

  // Question 5: Remove duplicates from the given linked list
  printf("Question#5: Remove duplicates from the given linked list\n");
  printf(
    "Before removing duplicates, the order of the elements is as follows:\n");
  for (offset_t p = head; !cursor_is_last(p); p = cursor_space[p].next) {
    printf("%d ", cursor_space[p].val);
  }
  printf("\n");

  offset_t last_c = NULL_OFFSET;
  for (offset_t p = head; !cursor_is_last(p); p = cursor_space[p].next) {
    if (last_c != NULL_OFFSET) {
      if (cursor_space[last_c].val == cursor_space[p].val) {
        cursor_space[last_c].next = cursor_space[p].next;
        cursor_free(p);
        p = cursor_space[last_c].next;
      }
    }
  }

  printf(
    "After removing duplicates, the order of the elements is as follows:\n");
  for (offset_t p = head; !cursor_is_last(p); p = cursor_space[p].next) {
    printf("%d ", cursor_space[p].val);
  }
  printf("\n\n");
}

int
main(void)
{
  practice_q();
}
