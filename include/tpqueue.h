// Copyright 2022 NNTU-CS
#ifndef INCLUDE_TPQUEUE_H_
#define INCLUDE_TPQUEUE_H_

#include <stdexcept>

template<typename T>
class TPQueue {
 private:
  struct Node {
    T dt;
    Node* next;

    explicit Node(const T& data, Node* n = nullptr)
        : dt(data), next(n) {}
  };

  Node* hd;

 public:
  TPQueue() : hd(nullptr) {}

  ~TPQueue() {
    while (hd != nullptr) {
      Node* temp = hd;
      hd = hd->next;
      delete temp;
    }
  }

  TPQueue(const TPQueue&) = delete;
  TPQueue& operator=(const TPQueue&) = delete;

  void push(const T& it) {
    Node* new_n = new Node(it);

    if (hd == nullptr || it.prior > hd->dt.prior) {
      new_n->next = hd;
      hd = new_n;
    } else {
      Node* cur = hd;
      while (cur->next != nullptr &&
             it.prior <= cur->next->dt.prior) {
        cur = cur->next;
      }
      new_n->next = cur->next;
      cur->next = new;
    }
  }

  T pop() {
    if (empty()) {
      throw std::runtime_error("Pop from empty queue");
    }
    Node* temp = hd;
    T it_dt = temp->dt;
    hd = hd->next;
    delete temp;
    return it_dt;
  }

  bool empty() const {
    return hd == nullptr;
  }
};

struct SYM {
  char ch;
  int prior;
};


#endif  // INCLUDE_TPQUEUE_H_
