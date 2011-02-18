#ifndef LIST_H
#define LIST_H

#include <iostream>

using namespace std;

template <class dataType>
class List {
  struct ListNode {
    dataType item;
    ListNode *next;
  };
  
  ListNode *frontPtr;
  ListNode *backPtr;
  
 public:
 List() : frontPtr(NULL), backPtr(NULL) {} //end default constructor
  
  void push(dataType item)
  {
    ListNode *newNode = new ListNode;
    newNode->item = item;
    newNode->next = NULL;
    
    if(isEmpty()) //insert first node
      frontPtr = newNode;
    else
      backPtr->next = newNode;
    
    backPtr = newNode;
  }
  
  dataType pop()
  {
    if(isEmpty())
      return NULL;
    
    ListNode *topNode = peek(); //remember orig frontPtr for returning
    frontPtr = topNode->next; //move frontPtr to next in the list
    return topNode;
  }
  
  dataType peek()
  {
    return frontPtr;
  }
  
  /* UTILITIES */
  bool isEmpty()
  {
    return frontPtr == NULL;
  }

  void print()
  {
    ListNode *curNode = frontPtr;
    
    while(curNode != NULL) {
      cout << curNode->item << endl;
      curNode = curNode->next;
    }
  }
};

#endif //LIST_H
