#ifndef STACK_H
#define STACK_H

#include "stdint.h"
#include "node.hpp"

class Stack
{
  public:
  Node* head;
  Node* tail;

  Stack () {
    head = nullptr;
    tail = nullptr;  
  }

  ~Stack() {
    empty();
  }

  void push (uint8_t val) {
    if (head == nullptr) {
      head = new Node(val);
      tail = head;
    } else {
      tail->next = new Node(val);
      tail = tail->next;
    }
  }

  bool pop (uint8_t* val) {
    if (head == nullptr)
      return false;

    if (head == tail) {
      (*val) = tail->data;
      delete tail;
      head = tail = nullptr;
      return true;
    }

    Node* curr = head;

    while (curr->next != tail)
      curr = curr->next;
    
    (*val) = tail->data;
    delete tail;
    tail = curr;
    curr->next = nullptr;
    return true;
  }

  bool top (uint8_t * val) {
    if (head == nullptr)
      return false;

    Node* curr = head;

    while (curr->next != tail)
      curr = curr->next;
    
    (*val) = tail->data;
    tail = curr;
    return true;
  }

  void foreach (void (*callback)(uint8_t))
  {
    if (head == nullptr) return;
    
    Node *curr = head;
    while (curr->next != nullptr)
    {
      (*callback)(curr->data);
      curr = curr->next;
    }
    (*callback)(curr->data);
  }

  void empty () {
    if (head == nullptr)
      return;

    Node *curr = head;
    Node *before;
    while (curr->next != nullptr)
    {
      before = curr;
      curr = curr->next;
      delete before;
    }
    delete curr;
    head = nullptr;
  }

  bool item (uint8_t index, uint8_t* val) {
    Node* curr = head;

    if (index < 0) return false;

    while (index != 0) {
      index--;
      if (curr != nullptr)
        curr = curr->next;
      else
        return false;
    }

    if (curr != nullptr){
      (*val) = curr->data;
      return true;
    }
    return false;
  }
};

#endif