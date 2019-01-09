#ifndef TQUEUEA_H
#define TQUEUEA_H

#include <iostream>
#include <memory>
#include "TQueueItemA.h"

template <class T> 
class TQueueA {
public:
    TQueueA();
    virtual ~TQueueA();

	void Push(const T &item);
    void Pop();
    T &Front();
    bool IsEmpty() const;
    uint32_t GetSize() const;
	
private:
	TQueueItemA<T> *first;
	TQueueItemA<T> *last;
    uint32_t size;
};

#endif //TQUEUEA_H
