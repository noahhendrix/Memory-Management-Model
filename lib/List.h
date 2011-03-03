#ifndef LIST_H
#define LIST_H

#include "../models/ListNode.h"
#include <iostream>

template <class dataType>
class List {
 protected:
  ListNode<dataType> *frontPtr;
  ListNode<dataType> *backPtr;
  
 public:
 List() : frontPtr(NULL), backPtr(NULL) {} //end default constructor
  
  int size()
  {
    int size = 0;
    ListNode<dataType> *curNode = frontPtr;
    
    while(curNode != NULL) {
      size++;
      curNode = curNode->next;
    }

    return size;
  }

  void push(dataType item)
  {
    ListNode<dataType> *newNode = new ListNode<dataType>;
    newNode->item = item;
    newNode->next = NULL;
    
    if(isEmpty()) //insert first node
      frontPtr = newNode;
    else
      backPtr->next = newNode;

    backPtr = newNode;
  }

  //returns first node
  ListNode<dataType>* peekNode() {
    return frontPtr;
  }

  dataType pop()
  {
    if(isEmpty())
      return NULL;
    
    ListNode<dataType> *topNode = frontPtr; //remember orig frontPtr for returning
    frontPtr = topNode->next; //move frontPtr to next in the list
    return topNode->item;
  }

  void remove(dataType item)
  {
    ListNode<dataType> *curNode = frontPtr;
    ListNode<dataType> *prevNode = NULL;
    
    while(curNode != NULL) {
      if(curNode->item == item) {//true - found the node
        if(prevNode == NULL) //we're at the first node
          frontPtr = curNode->next;
        else
          prevNode->next = curNode->next;
        
        if(backPtr == curNode) //we're at the end
          backPtr = prevNode;;
        return;
      }
      prevNode = curNode;
      curNode = curNode->next;
    }
  }

  //returns the first node's item where test_function returns true
  //returns NULL if no node matches
  dataType detect(bool (*test_function)(dataType, int&), int& extra_parameter) {
    ListNode<dataType> *curNode = frontPtr;
    
    while(curNode != NULL) {  
      if(test_function(curNode->item, extra_parameter))
        return curNode->item;
      curNode = curNode->next;
    }
    return NULL;
  }

  void remove_if(bool (*test_function)(dataType)) {
    ListNode<dataType> *curNode = frontPtr;
    
    while(curNode != NULL) {
      if(test_function(curNode->item))
        remove(curNode->item);
      curNode = curNode->next;
    }
  }

  void each(void (*function)(dataType))
  {
    ListNode<dataType> *curNode = frontPtr;
    
    while(curNode != NULL) {
      function(curNode->item);
      curNode = curNode->next;
    }
  }

  void each_with_parameter(void (*function)(dataType, int&), int& extra_parameter)
  {
    ListNode<dataType> *curNode = frontPtr;
    
    while(curNode != NULL) {
      function(curNode->item, extra_parameter);
      curNode = curNode->next;
    }
  }
  
  
  dataType peek()
  {
    if(isEmpty())
      return NULL;
    
    return frontPtr->item;
  }

  dataType peek_back()
  {
    if(isEmpty())
      return NULL;
    
    return backPtr->item;
  }
  
  /* UTILITIES */
  bool isEmpty()
  {
    return frontPtr == NULL;
  }
};

#endif //LIST_H
