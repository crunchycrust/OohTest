#ifndef TQUEUEITEMA_H
#define TQUEUEITEMA_H

#include <iostream>
#include <memory>

template <class T> 
class TQueueItemA {
public:
    TQueueItemA(const T &val, TQueueItemA<T> *item);
    virtual ~TQueueItemA();
    
    void SetNext(TQueueItemA<T> *item);
    TQueueItemA<T> &GetNext() const;
    
private:
    T *value;
    TQueueItemA<T> *next;  
};

#endif //TQUEUEITEMA_H
