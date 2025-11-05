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
		list.AddHead(item);
	}
    void pushBack(const T& item) override{
		list.AddTail(item);
	}

    // Core Removal Operations
    T popFront() override{
		if (list.getCount() != 0){
			T element = list.getHead()->getData();
			list.RemoveHead();
			return element;
		}
		else {
			throw std::runtime_error("Empty dequeue");
		}
		
	}
    T popBack() override{
		if (list.getCount() != 0){
			T element = list.getTail()->getData();
			list.RemoveTail();
			return element;
		}
		else {
			throw std::runtime_error("Empty dequeue");
		}
	}

    // Element Accessors
    const T& front() const override{
		if (list.getCount() == 0){
			throw std::runtime_error("Empty dequeue");
		}
		else{
			return list.getHead()->getData();
		}
		
	}
    const T& back() const override{
		if (list.getCount() == 0){
			throw std::runtime_error("Empty dequeue");
		}
		else{
			return list.getTail()->getData();
		}
	}

    // Getter
    std::size_t getSize() const noexcept override{
		return list.getCount();
	}
};






