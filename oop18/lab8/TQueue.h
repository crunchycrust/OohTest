#ifndef TQUEUE_H
#define TQUEUE_H

#include <functional>
#include <iostream>
#include <memory>
#include <future>
#include <thread>

#include "TAllocationBlock.h"

template <class T> class TQueue {
 private:
  class TNode {
  public:
    TNode();
    TNode(const std::shared_ptr<T>&);
    auto GetNext() const;
    auto GetItem() const;
    std::shared_ptr<T> item;
    std::shared_ptr<TNode> next;

    void* operator new(size_t);
    void operator delete(void*);
    static TAllocationBlock nodeAllocator;
  };

  template <class N, class M>
    class TIterator {
  private:
    N nodePtr;
  public:
    TIterator(const N&);
    std::shared_ptr<M> operator* ();
    std::shared_ptr<M> operator-> ();
    void operator ++ ();
    bool operator == (const TIterator&);
    bool operator != (const TIterator&);
  };
 
  int length;
  
  std::shared_ptr<TNode> head;
  std::shared_ptr<TNode> tail;
  auto psort(std::shared_ptr<TNode>&);
  auto parts(std::shared_ptr<TNode>&);
  auto sort_parpar(std::shared_ptr<TNode>&);
  
 public:
  TQueue();
  bool Push(const std::shared_ptr<T>&);
  bool Pop(const int);
  bool IsEmpty() const;
  int GetLength() const;
  
  void sort();
  void sort_par();
    
  TIterator<std::shared_ptr<TNode>, T> begin() {return TIterator<std::shared_ptr<TNode>, T>(head->next);};
  TIterator<std::shared_ptr<TNode>, T> end() {return TIterator<std::shared_ptr<TNode>, T>(nullptr);};

};

#include "TQueue.hpp"
#include "TIterator.h"
#endif
