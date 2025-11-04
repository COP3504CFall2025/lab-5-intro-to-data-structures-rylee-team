#pragma once

#include <cstddef>
#include <stdexcept>
#include "Interfaces.hpp"
#include <utility>

template <typename T>
class ABDQ : public DequeInterface<T> {
private:
    T* array;                 // underlying dynamic array
    std::size_t capacity;    // total allocated capacity
    std::size_t size;        // number of stored elements
    std::size_t front_;       // index of front element
    std::size_t back;        // index after the last element (circular)

    static constexpr std::size_t SCALE_FACTOR = 2;

public:
    // Big 5
    ABDQ(){
		capacity = 4;
		size = 0;
		array = new T[4];
		front_ = 0;
		back = 0;
	}
    explicit ABDQ(std::size_t c){
		capacity = c;
		size = 0;
		array = new T[c];
		front_ = 0;
		back = 0;
	}
    ABDQ(const ABDQ& other){
		capacity = other.capacity;
		size = other.size;
		front_ = other.front_;
		back = other.back;

		array = new T[other.capacity];

		std::size_t index;
		for (size_t i = 0; i < size; i++){
			index = (other.front + i) % other.capacity;
			array[i] = other.array[index];
		}
	}
    ABDQ(ABDQ&& other) noexcept{
		capacity = other.capacity;
		size = other.size;
		front_ = other.front_;
		back = other.back;
		array = other.array;

		other.array = nullptr;
		other.capacity = 0;
		other.size = 0;
		other.front_ = 0;
		other.back = 0;
	}
    ABDQ& operator=(const ABDQ& other){
		if (this != &other){

			delete[] this->array;

			size = other.size;
			front_ = other.front_;
			back = other.back;
			capacity = other.capacity;
			array = new T[capacity];
			
			std::size_t index;
			for (size_t i = 0; i < size; i++){
				index = (other.front + i) % other.capacity;
				array[i] = other.array[index];
			}
		}
		return *this;
	}
    ABDQ& operator=(ABDQ&& other) noexcept{
		if (this != &other){

			delete[] array;
	
			capacity = other.capacity;
			size = other.size;
			front_ = other.front_;
			back = other.back;
			array = other.array;

			other.array = nullptr;
			other.size = 0;
			other.capacity = 0;
			other.front_ = 0;
			other.back = 0;
		}
		return *this;
	}
    ~ABDQ() override{
		delete[] array;
	}

    // Insertion
    void pushFront(const T& item) override{
		if (size == capacity){
			std::size_t old_capacity = capacity;
			capacity *= SCALE_FACTOR;
			T* temp = new T[capacity];
			std::size_t index;

			for (std::size_t i = 0; i < size; i++){
				index = (front_ + i) % (old_capacity);
				temp[i] = array[index];
			}

			delete[] array;

			array = temp;
			temp = nullptr;
			front_ = 0;
			back = size;
		}
		
		front_ = (front_ - 1 + capacity) % capacity;
		array[front_] = item;
		size++;
	}
    void pushBack(const T& item) override{
		if (size == capacity){
			std::size_t old_capacity = capacity;
			capacity *= SCALE_FACTOR;
			T* temp = new T[capacity];
			std::size_t index;

			for (std::size_t i = 0; i < size; i++){
				index = (front_ + i) % (old_capacity);
				temp[i] = array[index];
			}

			delete[] array;

			array = temp;
			temp = nullptr;
			front_ = 0;
			back = size;
		}
		
		array[back] = item;
		back = (back + 1) % capacity;
		size++;
		
	}

    // Deletion
    T popFront() override{
		if (size == 0){
			throw std::out_of_range("Empty dequeue");
		}
		else {
			std::size_t index = front_;
			front_ = (front_ + 1) % capacity;
			size--;
			return array[index];
		}
	}

    T popBack() override{
		if (size == 0){
			throw std::out_of_range("Empty dequeue");
		}
		else{
			back = (capacity + back - 1) % capacity;
			size--;
			return array[back];
		}
	}

    // Access
    const T& front() const override{
		return array[front_];
	}
    const T& back() const override{
		std::size_t index = (capacity + back - 1) % capacity;
		return array[index];
	}

    // Getters
    std::size_t getSize() const noexcept override{
		return size;
	}

};
