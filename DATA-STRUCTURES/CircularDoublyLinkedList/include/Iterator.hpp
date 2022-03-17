#ifndef ITERATOR_HPP
#define ITERATOR_HPP
#include <Node.hpp>

template <typename Object>
class Iterator {
public:
	Node<Object>* current;
	
	Iterator() {
		current = NULL;
	}
	Iterator(Node<Object>* node) {
		current = node;
	}
	bool IsEndNode() {
		return current == NULL;
	}
	void StepNext() {
		if (!IsEndNode())
			current = current->next;
	}
	void StepBack() {
		if (!IsEndNode())
			current = current->prev;
	}
	const Object& GetCurrentData()const {
		return current->data;
	}
};
#endif