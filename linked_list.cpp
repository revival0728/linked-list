// in linked_list.h
#ifndef LINKED_LIST_HPP
#define LINKED_LIST_HPP

#include <cstddef>

namespace myc
{
	template<class T> class linked_list {
		private:
			class list_node {
				public:
					list_node *next;
					T value;
					list_node();
					list_node(list_node*, T);
			} *front;
		public:
			linked_list();
			void insert(const std::size_t, T);
			void erase(const std::size_t);
			T& operator[](const std::size_t);
	};
}

#endif

// in linked_list.cpp
#include "linked_list.h"

using namespace myc;

// list_node member functions
template<class T> linked_list<T>::list_node::list_node() {}
template<class T> linked_list<T>::list_node(linked_list<T>::list_node *_next, T _val) {
	this->next = _next;
	this->val = _val;
}

// linked_list member functions
template<class T> linked_list<T>::linked_list() {
	this->front = new linked_list<T>::list_node(nullptr, T());
}
template<class T> void linked_list<T>::insert(const std::size_t index, T _val) {
	linked_list<T>::list_node *tmp = this->front;
	for(std::size_t i = 0; i < index; ++i) {
		tmp = tmp->next;
	}
	tmp->next = new linked_list<T>::list_node(nullptr, _val);
	tmp = nullptr;
}
template<class T> void linked_list<T>::erase(const std::size_t index) {
	linked_list<T>::list_node *tmp = this->front, *erased = this->front;
	for(std::size_t i = 0; i < index+1; ++i) {
		erased = erased->next;
	}
	tmp->next = erased->next;
	erased->next = nullptr;
	delete erased;
}
template<class T> T& linked_list<T>::operator[](const std::size_t index) {
	linked_list<T>::list_node *tmp = this->front;
	for(std::size_t i = 0; i < index; ++i) {
		tmp = tmp->next;
	}
	tmp = tmp->next;
	return &(tmp->value);
}

// in main.cpp
#include <iostream>
#include "linked_list.h"
using namespace std;
using namespace myc;

struct Student {
	unsigned int number, score;
	string name;
	Student() {}
	Student(unsigned int _number, string _name, unsigned int _score) {
		number = _number;
		name = _name;
		score = _score;
	}
};

int main() {
	linked_list<Student> lst;
	lst.insert(0, Student());
}
