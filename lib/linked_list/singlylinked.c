#include <stdio.h>
#include <stdlib.h>
#define MAX_SIZE 100

struct LNode {
  int val;
  struct LNode* next;
};

struct LNode* lnode_new(int val, struct LNode* next) {
  struct LNode* nnode = (struct LNode*) malloc(sizeof(struct LNode));
  nnode->val = val;
  nnode->next = next | NULL;
  return nnode;
}

void lnode_insert(struct LNode* head, struct LNode* nnode) {
  nnode->next = head->next;
  head->next = nnode;
}

void lnode_delete(struct LNode* head, struct LNode* nnode) {
  for (struct LNode* i = head; i != NULL; i=i->next) {
    if (i->next == nnode) {
      i->next = nnode->next;
      break;
    }
  }
  free(nnode);
}

struct LNode* lnode_search(struct LNode* head, int key) {
  for (struct LNode* i = head; i != NULL; i=i->next) {
    if (i->val == key) {
      return i;
    }
  }
  return NULL;
}
