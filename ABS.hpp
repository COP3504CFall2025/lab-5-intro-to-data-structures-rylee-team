#pragma once

#include <cstddef>
#include <stdexcept>
#include "Interfaces.hpp"

// Technically bad, but size_t isn't likely to conflict with any client code.
using std::size_t;

template<typename T>
class ABS : public StackInterface<T> {
public:
    // Big 5 + Parameterized Constructor
    ABS(){
		capacity = 1;
		size = 0;
		array = new T[1];
	}
    explicit ABS(const size_t c){
		capacity = c;
		size = 0;
		array = new T[c];
	}
    ABS(const ABS& other){
		capacity = other.capacity;
		size = other.size;
		array = new T[other.capacity];

		for (size_t i = 0; i < size; i++){
			array[i] = other.array[i];
		}
	}
    ABS& operator=(const ABS& rhs){
		if (this != &rhs){

			delete[] this->array;

			size = rhs.size;
			capacity = rhs.capacity;
			array = new T[capacity];

			for (size_t i = 0; i < size; i++){
				array[i] = rhs.array[i];
			}
		}
		return *this;
	}
    ABS(ABS&& other) noexcept{
		capacity = other.capacity;
		size = other.size;
		array = other.array;

		other.array = nullptr;
		other.capacity = 0;
		other.size = 0;
	}
    ABS& operator=(ABS&& rhs) noexcept{
		if (this != &rhs){
			delete[] array;
	
			capacity = rhs.capacity;
			size = rhs.size;

			array = rhs.array;
			rhs.array = nullptr;
			rhs.size = 0;
			rhs.capacity = 0;
		}
		return *this;
	}
    ~ABS() noexcept override{
		delete[] array;
	}

	void shrinkIfNeeded(){
		if (size > 0 && size <= capacity/4){
			capacity /= 2;

			T* temp = new T[capacity];
			for (size_t i = 0; i < size; i++){
				temp[i] = array[i];
			}
			delete[] array;
			array = temp;
			temp = nullptr;
		}
	}

    // Get the number of items in the ABS
    [[nodiscard]] size_t getSize() const noexcept override{
		return size;
	}

    // Get the max size of the ABS
    [[nodiscard]] size_t getMaxCapacity() const noexcept{
		return capacity;
	}

    // Return underlying data for the stack
    [[nodiscard]] T* getData() const noexcept{
		return array;
	}

    // Push item onto the stack
    void push(const T& data) override{
		if (size == capacity){
			capacity *= scale_factor;
			T* temp = new T[capacity];
			
			for (size_t i = 0; i < size; i++){
				temp[i] = array[i];
			}
			temp[size] = data;
			delete[] array;
			array = temp;
		}
		else {
			array[size] = data;
		}
		size++;
	}

    T peek() const override {
		if (size > 0){
			return array[size-1];
		}
		else {
			throw std::runtime_error("Empty stack");
		}
	}

    T pop() override{
		if (size > 0){
			size--;
			shrinkIfNeeded();
			return array[size];
		}
		else{
			throw std::runtime_error("Empty stack");
		}
	}

private:
    size_t capacity;
    size_t size;
    T* array;
    static constexpr size_t scale_factor = 2;
};
