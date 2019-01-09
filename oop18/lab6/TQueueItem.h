#ifndef TQUEUEITEM_H
#define TQUEUEITEM_H

#include <iostream>
#include <memory>

template <class T> 
class TQueueItem {
public:
    TQueueItem(const T &val, TQueueItem<T> *item);
    virtual ~TQueueItem();
    
    void SetNext(TQueueItem<T> *item);
    TQueueItem<T> &GetNext() const;
    
private:
    T *value;
    TQueueItem<T> *next;  
};

#endif //TQUEUEITEM_H
