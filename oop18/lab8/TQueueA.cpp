#include "TQueueA.h"

template <class T> 
TQueueA<T>::TQueueA() {
	first = nullptr;
	last = nullptr;
	size = 0;
}

template <class T> 
bool TQueueA<T>::IsEmpty() const {
    return size == 0;
}

template <class T>
uint32_t TQueueA<T>::GetSize() const
{
    return size;
}

template <class T> 
void TQueueA<T>::Push(const T &item) {
	TQueueItemA<T> *tmp = new TQueueItemA<T>(item, first);
    first = tmp;
    size++;
}

template <class T> 
void TQueueA<T>::Pop() {
    if(first != nullptr) {
        TQueueItemA<T>  *oldFirst = &first->GetNext();
        oldFirst->SetNext(nullptr);
        size--;
        if(size == 0) {
            last = nullptr;
        }
    }
}

template <class T> TQueueA<T>::~TQueueA() {
	while (!IsEmpty()) {
        TQueueItemA<T> *temp = &first->GetNext();
        delete temp;
    }
    first = nullptr;
    last = nullptr;
}

typedef unsigned char Byte;

template class
TQueueA<void *>;
