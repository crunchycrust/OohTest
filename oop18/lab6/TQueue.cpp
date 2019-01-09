#include "TQueue.h"

template <class T> 
TQueue<T>::TQueue() {
	first = nullptr;
	last = nullptr;
	size = 0;
}

template <class T> 
bool TQueue<T>::IsEmpty() const {
    return size == 0;
}

template <class T>
uint32_t TQueue<T>::GetSize() const
{
    return size;
}

template <class T> 
void TQueue<T>::Push(const T &item) {
	TQueueItem<T> *tmp = new TQueueItem<T>(item, first);
    first = tmp;
    size++;
}

template <class T> 
void TQueue<T>::Pop() {
    if(first != nullptr) {
        TQueueItem<T>  *oldFirst = &first->GetNext();
        oldFirst->SetNext(nullptr);
        size--;
        if(size == 0) {
            last = nullptr;
        }
    }
}

template <class T> TQueue<T>::~TQueue() {
	while (!IsEmpty()) {
        TQueueItem<T> *temp = &first->GetNext();
        delete temp;
    }
    first = nullptr;
    last = nullptr;
}

typedef unsigned char Byte;

template class
TQueue<void *>;
