#pragma once
#include <iostream>

template <typename T>
class LinkedList {
	struct Node {
		T data;
		Node* prev;
		Node* next;

		Node(){
			prev = nullptr;
			next = nullptr;
		}

		Node(T d, Node* previous, Node* n){
			data = d;
			prev = previous;
			next = n;
		}

		T& getData(){
			return data;
		}

		const T& getData() const{
			return data;
		}
	};

public:
	// Behaviors
	void printForward() const{
		Node* ptr = head;
		
		for (std::size_t i = 0; i < count; i++){
			std::cout << ptr->data << std::endl;
			ptr = ptr->next;
		}
	}

	void PrintReverse() const{
		Node* ptr = tail;
		for (std::size_t i = 0; i < count; i++){
			std::cout << ptr->data << std::endl;
			ptr = ptr->prev;
			
		}
	}

	// Accessors
	[[nodiscard]] unsigned int getCount() const{
		return count;
	}

	Node* getHead(){
		return head;
	}

	const Node* getHead() const{
		return head;
	}

	Node* getTail(){
		return tail;
	}

	const Node* getTail() const{
		return tail;
	}

	// Insertion
	void AddHead(const T& data){
		// create the new node
		Node* newNode = new Node(data, nullptr, head);

		// check if there are no elements
		if (count > 0){
			// set the first node's prev pointer to this node
			head->prev = newNode;
		}
		else {
			// if this node is only element, then head and tail both point to it
			tail = newNode;
		}

		// set head to the new node
		head = newNode;

		// update count
		count++;
	}

	void AddTail(const T& data){
				// create the new node
		Node* newNode = new Node(data, tail, nullptr);

		// check if there are no elements
		if (count > 0){
			// set the first node's prev pointer to this node
			tail->next = newNode;
		}
		else {
			// if this node is only element, then head and tail both point to it
			head = newNode;
		}

		// set tail to the new node
		tail = newNode;

		// update count
		count++;
	}

	// Removal
	bool RemoveHead(){
		if (count > 0){
			Node* temp = head;
			if (count == 1){
				count = 0;
				head = nullptr;
				tail = nullptr;
			}

			else {
				count--;
				head = temp->next;
				head->prev = nullptr;
			}

			delete temp;
			return true;
		}

		else {
			return false;
		}
	}

	bool RemoveTail(){
		if (count > 0){
			Node* temp = tail;
			if (count == 1){
				count = 0;
				head = nullptr;
				tail = nullptr;
			}

			else {
				count--;
				tail = temp->prev;
				tail->next = nullptr;
			}

			delete temp;
			return true;
		}

		else {
			return false;
		}		
	}

	void Clear(){
		while (count > 0){
			RemoveHead();
		}
	}

	// Constructor
	LinkedList(){
		count = 0;
		head = nullptr;
		tail = nullptr;
	}

	// copy constructor
	LinkedList(const LinkedList<T>& list){

		this->count = 0;
		this->head = nullptr;
		this->tail = nullptr;

		Node* ptr = list.head;
		for (std::size_t i = 0; i < list.count; i++){
			AddTail(ptr->data);
			ptr = ptr->next;
			}
		}

	// copy assignment
	LinkedList<T>& operator=(const LinkedList<T>& rhs){
		if (this != &rhs){
			Clear();

			if (rhs.count == 0){
				this->count = 0;
				this->head = nullptr;
				this->tail = nullptr;
			}

			else {
			Node* ptr = rhs.head;
			for (std::size_t i = 0; i < rhs.count; i++){
				AddTail(ptr->data);	
				ptr = ptr->next;
				}
			}

		}
		return *this;
	}

	// move constructor
	LinkedList(LinkedList<T>&& other) noexcept{
		this->count = other.count;
		this->head = other.head;
		this->tail = other.tail;
		
		other.count = 0;
		other.head = nullptr;
		other.tail = nullptr;

	}

	// move assignment
	LinkedList<T>& operator=(LinkedList<T>&& other) noexcept{
		if (this != &other){
			Clear();

			this->count = other.count;
			this->head = other.head;
			this->tail = other.tail;
			
			other.count = 0;
			other.head = nullptr;
			other.tail = nullptr;
			}
		
		return *this;
	}

	// destructor
	~LinkedList(){
		Clear();
	}

private:
	// Stores pointers to first and last nodes and count
	Node* head;
	Node* tail;
	unsigned int count;
};