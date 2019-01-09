#ifndef TITERATOR_H
#define TITERATOR_H

#include <iostream>
#include <memory>

template <class N, class T>
class TIterator {
public:
	TIterator(std::shared_ptr<N> n) { //it is a pointer to
		iter = n; //an item officially now 
	}

	std::shared_ptr<T> operator*() { //oooh what's over here?
		return iter->GetFigure();
	}

	std::shared_ptr<T> operator->() {
		return iter->GetFigure();	
	} // same... ..

	void operator++() {
		iter = iter->Next();
	}

	TIterator operator++(int) {
		TIterator iter(*this);
		++(*this);
		return iter;
	}

	bool operator==(const TIterator &i) {// 2 iterators are equal
		return (iter == i.iter);
	}

	bool operator!=(const TIterator &i) {// 2 iterators are NOT equal
		return (iter != i.iter);
	}

private:
	std::shared_ptr<N> iter;// here is our beauty iter-pointer
};

#endif

