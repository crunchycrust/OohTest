#ifdef TQUEUE_H

#include <unistd.h>
#include <future>
#include <thread>
#include <functional>

template <class T> 
TAllocationBlock TQueue<T>::TNode::nodeAllocator(sizeof(TQueue<T>::TNode), 100);

template <class T> 
void* TQueue<T>::TNode::operator new(size_t size) {
	return nodeAllocator.Allocate();
}

template <class T> 
void TQueue<T>::TNode::operator delete(void* ptr) {
	nodeAllocator.Deallocate(ptr);
}
//TNode private class for Queue usage
template <class T> TQueue<T>::TNode::TNode() {
  item = std::shared_ptr<T>();
  next = nullptr;
}

template <class T> TQueue<T>::TNode::TNode(const std::shared_ptr<T>& obj) {
	item = obj;
	next = nullptr;
}

template <class T> auto TQueue<T>::TNode::GetNext() const {
  return this->next;
}

template <class T> auto TQueue<T>::TNode::GetItem() const {
  return this->item;
}
//public for TNTree as well
template <class T> TQueue<T>::TQueue() {
	head = std::make_shared<TNode>();
	tail = std::make_shared<TNode>();
	length = 0;
}

template <class T> bool TQueue<T>::IsEmpty() const {
	return this->length == 0;
}

template <class T> int TQueue<T>::GetLength() const {
  return this->length;
}

template <class T> bool TQueue<T>::Push(const std::shared_ptr<T>& obj) {  
  auto Nitem = std::make_shared<TNode>(obj);
  std::swap(Nitem->next, head->next);
  std::swap(head->next, Nitem);
  length++;
  
  return true;
}

template <class T> 
bool TQueue<T>::Pop(int pos) {
	if (pos < 1 || pos > length || IsEmpty())
		return false;
	if (pos == 1) {
		if (IsEmpty())
			return false;
		else
		head->next = std::move(head->next->next);
		length--;
  
		return true;
	}
	auto iter = head->next;
	int i = 0;

	while (i < pos - 2) {
		iter = iter->next;
		i++;
	}
  
	iter->next = std::move(iter->next->next);
	length--;

	return true;
}
//sorting
template <class T> void TQueue<T>::sort() {
	head->next = psort(head->next);
}

template <class T> auto TQueue<T>::psort(std::shared_ptr<TNode>& head) {
	if (head == nullptr || head->next == nullptr) {
		return head;
	}
	
	auto p1 = parts(head);
	auto leftPart = p1->next;
	auto rightPart = head;

	p1->next = nullptr;

	if (leftPart == nullptr) {
		leftPart = head;
		rightPart = head->next;
		head->next = nullptr;
	}

	rightPart = psort(rightPart);
	leftPart = psort(leftPart);
	auto iter = leftPart;
	while (iter->next != nullptr) {
		iter = iter->next;
	}

	iter->next = rightPart;

	return leftPart;
}

template <class T> 
auto TQueue<T>::parts(std::shared_ptr<TNode>& head) {
	if (head->next->next == nullptr) {
		if (head->next->GetItem()->Square() > head->GetItem()->Square()) {
		return head->next;
		} 
		else {
		return head;
		}
	} 
	else {
		auto i = head->next;
		auto check = head;
		auto lastchange = (check->next->GetItem()->Square() >= check->GetItem()->Square()) ? check->next : check;

		while ((i != nullptr) && (i->next != nullptr)) {
			if (i->next->GetItem()->Square() >= check->GetItem()->Square()) {
				if (i->next == lastchange->next) {
					lastchange = lastchange->next;
				} 
			}
			i = i->next;
		}
		return lastchange;
	}
  
}

template <class T> 
void TQueue<T>::sort_par() {
	head->next = sort_parpar(head->next);
}


template <class T> auto TQueue<T>::sort_parpar(std::shared_ptr<TNode>& head) {
	if (head == nullptr || head->next == nullptr) {
		return head;
	}

	auto p1 = parts(head);
	auto leftPart = p1->next;
	auto rightPart = head;

	p1->next = nullptr;

	if (leftPart == nullptr) {
		leftPart = head;
		rightPart = head->next;
		head->next = nullptr;
	}

	std::packaged_task<std::shared_ptr<TNode>(std::shared_ptr<TNode>&)>
		task1(std::bind(&TQueue<T>::sort_parpar, this, std::placeholders::_1));
	std::packaged_task<std::shared_ptr<TNode>(std::shared_ptr<TNode>&)>
		task2(std::bind(&TQueue<T>::sort_parpar, this, std::placeholders::_1));
	auto rightPartHandle = task1.get_future();
	auto leftPartHandle = task2.get_future();
	
	std::thread(std::move(task1), std::ref(rightPart)).join();
	rightPart = rightPartHandle.get();
	std::thread(std::move(task2), std::ref(leftPart)).join();
	leftPart = leftPartHandle.get();
	
	auto iter = leftPart;
	while (iter->next != nullptr) {
		iter = iter->next;
	}

	iter->next = rightPart;

	return leftPart;
}



#endif
