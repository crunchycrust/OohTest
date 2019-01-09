#ifndef TQUEUE_H
#define TQUEUE_H

#include <iostream>
#include <memory>
#include "TQueueItem.h"

template <class T> 
class TQueue {
public:
    TQueue();
    virtual ~TQueue();

	void Push(const T &item);
    void Pop();
    T &Front();
    bool IsEmpty() const;
    uint32_t GetSize() const;
	
private:
	TQueueItem<T> *first;
	TQueueItem<T> *last;
    uint32_t size;
};

#endif //TQUEUE_H
