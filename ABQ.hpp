#pragma once

#include <cstddef>
#include <stdexcept>
#include "Interfaces.hpp"

// Technically bad, but size_t isn't likely to conflict with any client code.
using std::size_t;

template<typename T>
class ABQ : public QueueInterface<T>{

    size_t capacity;
    size_t size;
    T* array;
    static constexpr size_t scale_factor_ = 2;

public:
    // Constructors + Big 5
    ABQ(){
		capacity = 1;
		size = 0;
		array = new T[1];
	}
    explicit ABQ(const size_t c){
		capacity = c;
		size = 0;
		array = new T[c];
	}
    ABQ(const ABQ& other){
		capacity = other.capacity;
		size = other.size;
		
		array = new T[other.capacity];

		for (size_t i = 0; i < size; i++){
			array[i] = other.array[i];
		}
	}
    ABQ& operator=(const ABQ& rhs){
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
    ABQ(ABQ&& other) noexcept{
		capacity = other.capacity;
		size = other.size;
		array = other.array;

		other.array = nullptr;
		other.capacity = 0;
		other.size = 0;
	}
    ABQ& operator=(ABQ&& rhs) noexcept{
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
    ~ABQ() noexcept override{
		delete[] array;
	}

    // Getters
    [[nodiscard]] size_t getSize() const noexcept override{
		return size;
	}
    [[nodiscard]] size_t getMaxCapacity() const noexcept{
		return capacity;
	}
    [[nodiscard]] T* getData() const noexcept{
		return array;
	}

    // Insertion
    void enqueue(const T& data) override{
		if (size == capacity){
			capacity *= scale_factor_;
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

    // Access
    T peek() const override{
		if (size == 0) {
			throw std::runtime_error("Dequeue is empty");
		}
		else{
			return array[0];
		}
	}

    // Deletion
    T dequeue() override{
		if (size > 0) {
		T elem = array[0];
		
		T* temp = new T[capacity];
		for (size_t i = 0; i < size-1; i++) {
			temp[i] = array[i+1];
		}

		delete[] array;

		array = temp;
		temp = nullptr;
		size--;

		return elem;
		}
		else {
			throw std::out_of_range("Empty queue");
		}
	}
};
