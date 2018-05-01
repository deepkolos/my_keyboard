#ifndef NODE_HPP
#define NODE_HPP

#include "stdint.h"

class Node
{
public:
  Node *next;
  uint8_t data;

  Node(uint8_t _data)
  {
    data = _data;
    next = nullptr;
  }
};

#endif