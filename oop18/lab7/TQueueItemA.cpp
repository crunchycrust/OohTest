#include "TQueueItemA.h"


template <class T> 
TQueueItemA<T>::TQueueItemA(const T &val, TQueueItemA<T> *item) {
    value = new T(val);
    next = item;
}

template <class T>
void TQueueItemA<T>::SetNext(TQueueItemA<T> *item)
{
    next = item;
}

template <class T>
TQueueItemA<T> &TQueueItemA<T>::GetNext() const
{
    return *next;
}

template <class T> TQueueItemA<T>::~TQueueItemA() {
    delete value;
}

typedef unsigned char Byte;

template class
TQueueItemA<void *>;
