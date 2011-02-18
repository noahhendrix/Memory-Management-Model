#ifndef LIST_H
#define LIST_H

#include <iostream>

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
    
    ListNode *topNode = frontPtr; //remember orig frontPtr for returning
    frontPtr = topNode->next; //move frontPtr to next in the list
    return topNode->item;
  }
  
  dataType peek()
  {
    return frontPtr->item;
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
      std::cout << curNode->item << std::endl;
      curNode = curNode->next;
    }
  }
};

#endif //LIST_H
