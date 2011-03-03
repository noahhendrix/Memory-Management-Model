#ifndef CIRCULARLIST_H
#define CIRCULARLIST_H

#include "./List.h"

template <class dataType>
class CircularList: public List<dataType> {
 public:
  void push(dataType item)
  {
    ListNode<dataType> *newNode = new ListNode<dataType>;
    newNode->item = item;
    
    if(this->isEmpty()) //insert first node
      this->frontPtr = newNode;
    else
      this->backPtr->next = newNode;
    
    newNode->next = this->frontPtr;
    this->backPtr = newNode;
  }
  
  dataType pop()
  {
    if(this->isEmpty())
      return NULL;
    
    ListNode<dataType> *topNode = this->frontPtr; //remember orig frontPtr for returning
    this->frontPtr = topNode->next; //move frontPtr to next in the list
    this->backPtr->next = this->frontPtr;
    return topNode->item;
  }

  void remove(dataType item)
  {
    ListNode<dataType> *curNode = this->frontPtr;
    ListNode<dataType> *prevNode = NULL;
    
    do {
      if(curNode->item == item) {//true - found the node
        if(prevNode == NULL){ //we're at the first node
          this->frontPtr = curNode->next;
          this->backPtr->next = curNode->next;
        } else {
          prevNode->next = curNode->next;
        }
        return;
      }
      prevNode = curNode;
      curNode = curNode->next;
    } while(curNode != this->frontPtr);
  }

  void remove_all()
  {
    this->frontPtr = NULL;
    this->backPtr = NULL;
  }
  
  dataType detect(bool (*test_function)(dataType, int&), int& extra_parameter) {
    ListNode<dataType> *curNode = this->frontPtr;
    
    do {
      if(test_function(curNode->item, extra_parameter))
        return curNode->item;
      curNode = curNode->next;
    } while(curNode != this->frontPtr);
    return NULL;
  }

  void each(void (*function)(dataType))
  {
    ListNode<dataType> *curNode = this->frontPtr;
    
    do {
      function(curNode->item);
      curNode = curNode->next;
    } while(curNode != this->frontPtr);
  }

  void each_with_parameter(void (*function)(dataType, int&), int& extra_parameter)
  {
    ListNode<dataType> *curNode = this->frontPtr;
    
    do {
      function(curNode->item, extra_parameter);
      curNode = curNode->next;
    } while(curNode != this->frontPtr);
  }

  int count_if(bool (*test_function)(dataType))
  {
    int count = 0;
    ListNode<dataType> *curNode = this->frontPtr;
    
    do {
      if(test_function(curNode->item))
        count++;
      curNode = curNode->next;
    } while(curNode != this->frontPtr);
    
    return count;
  }
  
};

#endif //CIRCULARLIST_H
