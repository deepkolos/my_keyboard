
#ifndef SET_H
#define SET_H

#include "stdint.h"
#include "node.hpp"

class Set
{
public:
  Node *head;
  Set()
  {
    head = nullptr;
  }
  ~Set()
  {
    empty();
  }

  bool add(uint8_t data)
  {
    if (head == nullptr)
    {
      head = new Node(data);
    }
    else
    {
      Node *curr = head;
      while (curr->next != nullptr)
      {
        if (curr->data == data)
          return false;
        curr = curr->next;
      }
      curr->next = new Node(data);
    }

    return true;
  }

  bool remove(uint8_t data)
  {
    if (head == nullptr)
      return false;

    Node *curr = head;
    Node *before = head;

    while (curr->next != nullptr) {
      if (curr->data == data) {
        // 找到了
        // 删除该节点
        if (curr == head) {
          head = curr->next;
        } else {
          before->next = curr->next;
        }

        delete curr;
        return true;
      } else {
        // 找不到, 去找下一个节点
        before = curr;
        curr = curr->next;
      }
    }

    if (curr->data == data) {
      if (curr == head)
        head = curr->next;
      else 
        before->next = curr->next;
        
      delete curr;
      return true;
    }
    
    return false;
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

  void empty()
  {
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