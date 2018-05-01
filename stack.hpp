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

    Node* curr = head;

    while (curr->next != tail)
      curr = curr->next;
    
    (*val) = tail->data;
    delete tail;
    tail = curr;
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
};

#endif