#pragma once

#include "Interfaces.hpp"
#include "LinkedList.hpp"
#include <stdlib.h>
#include <stdexcept>

template <typename T>
class LLS : public StackInterface<T> {
private:
    LinkedList<T> list;
public:
    // Constructor
    LLS(){}

    // Insertion
    void push(const T& item) override{
		list.AddHead(item);
	}

    // Deletion
    T pop() override{
		if (list.getCount() == 0){
			throw std::runtime_error("List is empty");
		}
		T element = list.getHead()->getData();
		list.RemoveHead();
		return element;
	}

    // Access
    T peek() const override{
		if (list.getCount() == 0){
			throw std::runtime_error("List is empty");
		}
		else{
			return list.getHead()->getData();
		}
	}

    //Getters
    std::size_t getSize() const noexcept override{
		return list.getCount();
	}

};