#ifndef CIRCULARCircularDoublyLinkedList_HPP
#define CIRCULARCircularDoublyLinkedList_HPP
#include <Iterator.hpp>

using namespace std;

template <typename Object>
class CircularDoublyLinkedList {
private:
	Node<Object>* head;
	int size;
	Iterator<Object> IterateFromPrevIndex(int index) const {
		if (!(index < 0 || index > Count())) {
			int i = 0;
			Iterator<Object> itr(head);
			while (!itr.IsEndNode() && index != i++)
				itr.StepNext();
			return itr;
		}
		return NULL;
	}
	Iterator<Object> IterateFromFirstNode() const {
		if (!IsEmpty())
			return Iterator<Object>(head->next);
		return NULL;
	}
public:
	CircularDoublyLinkedList() {
		head = new Node<Object>();
		size = 0;
	}
	bool IsEmpty() const {
		return head->next == NULL;
	}
	int Count() const {
		return size;
	}
	const Object& First() const {
		if (!IsEmpty())
			return head->next->data;
		return NULL;
	}
	const Object& Last() const {
		if (!IsEmpty())
			return head->next->prev->data;//yeni
		return NULL;
	}
	void Add(const Object& obj) {
		Insert(Count(), obj);
	}
	void Insert(int index, const Object& obj) {
		Iterator<Object> itr;
		itr = IterateFromPrevIndex(index);
		Node<Object>* newNext = itr.current->next;
		itr.current->next = new Node<Object>(obj, newNext, itr.current);
		if (newNext != NULL) {
			newNext->prev = itr.current->next;
			if (index == 0) {
				Node<Object>* last = newNext->prev;
				head->next->prev = last;
				last->next = head->next;
			}
		}
		if (size == 0) {
			head->next->next = head->next;
			head->next->prev = head->next;
		}
		size++;
	}
	void Remove(const Object& obj) {
		int index = IndexOf(obj);
		RemoveAt(index);
	}
	void RemoveAt(int index) {
		Iterator<Object> itr;
		itr = IterateFromPrevIndex(index);
		if (itr.current->next != NULL) {
			Node<Object>* oldNode = itr.current->next;
			itr.current->next = itr.current->next->next;
			oldNode->next->prev = oldNode->prev;
			delete oldNode;
			if (index == 0)
				head->next->prev->next = head->next;
			size--;
			if (size == 0)
				itr.current->next = NULL;
		}
	}
	int IndexOf(const Object& obj) const {
		int index = 0;
		for (Iterator<Object> itr(head->next); index < size; itr.StepNext()) {
			if (itr.GetCurrentData() == obj)
				return index;
			index++;
		}
		return -1;
	}
	bool Find(const Object& obj) const {
		int index = 0;
		for (Iterator<Object> itr(head->next); index < size; itr.StepNext()) {
			if (itr.GetCurrentData() == obj)
				return true;
		}
		return false;
	}
	friend ostream& operator<<(ostream& screen, CircularDoublyLinkedList& list) {
		if (list.IsEmpty())
			screen << "Liste bos";
		else {
			int index = 0;
			for (Iterator<Object> itr = list.IterateFromFirstNode(); index < list.size; itr.StepNext(), index++)
				screen << itr.GetCurrentData() << endl;
		}
		return screen;
	}
	void PrintAllFromIndexReversed(int index) {
		int i = 0;
		for (Iterator<Object> itr = IterateFromPrevIndex(index + 1); i < size; itr.StepBack(), i++)
			cout << itr.GetCurrentData() << endl;
	}
	void PrintAllReversed() {
		PrintAllFromIndexReversed(size - 1);
	}
	void Clear() {
		while (!IsEmpty()) {
			RemoveAt(0);
		}
	}
	~CircularDoublyLinkedList() {
		Clear();
		delete head;
	}
};
#endif