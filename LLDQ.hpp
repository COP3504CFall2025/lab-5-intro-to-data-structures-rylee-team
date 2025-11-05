#pragma once

#include <cstddef>
#include <stdexcept>
#include "Interfaces.hpp"
#include "LinkedList.hpp"
#include <utility>



template <typename T>
class LLDQ : public DequeInterface<T> {
private:
    LinkedList<T> list;

public:
    // Constructor
    LLDQ(){}

    // Core Insertion Operations
    void pushFront(const T& item) override{
		list.addHead(item);
	}
    void pushBack(const T& item) override{
		list.addTail(item);
	}

    // Core Removal Operations
    T popFront() override{
		T element = list.getHead()->getData();
		list.removeHead();
		return element;
	}
    T popBack() override{
		T element = list.getTail()->getData();
		list.removeTail();
		return element;
	}

    // Element Accessors
    const T& front() const override{
		return list.getHead()->getData();
	}
    const T& back() const override{
		return list.getTail()->getData();
	}

    // Getter
    std::size_t getSize() const noexcept override{
		return list.getCount();
	}
};






