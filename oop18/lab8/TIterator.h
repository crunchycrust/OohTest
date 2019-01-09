#ifdef TQUEUE_H

template <typename T> template <typename N, typename M> 
TQueue<T>::TIterator<N, M>::TIterator(const N& node) {
	nodePtr = node;
}
    
template <class T> template <class N, class M> 
std::shared_ptr<M> TQueue<T>::TIterator<N, M>::operator* () {
	return nodePtr->GetItem();
}

template <class T> template <class N, class M> 
std::shared_ptr<M> TQueue<T>::TIterator<N, M>::operator-> () {
	return nodePtr->GetItem();
}
    
template <class T> template <class N, class M> 
void TQueue<T>::TIterator<N, M>::operator ++ () {
	nodePtr = nodePtr->GetNext();
}

template <class T> template <class N, class M> 
bool TQueue<T>::TIterator<N, M>::operator == (TIterator const& other) {
	return nodePtr == other.nodePtr;
}

template <class T> template <class N, class M> 
bool TQueue<T>::TIterator<N, M>::operator != (TIterator const& other) {
	return !(*this == other);
}

#endif
