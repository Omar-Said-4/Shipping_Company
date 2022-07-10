#pragma once
template<typename t>
class Node
{
private:
	t data; //val to store
	Node<t>* next;//pointer to next node
public:
	Node() {};
	Node(const t& val) {
		data = val; next = nullptr;
	}
	Node(const t& val, Node<t>* nxt) { data = val; next = nxt; }
	Node(Node<t>* nxt) { next = nxt; }
	void setData(t val) { data = val; }
	t getData() { return data; }
	void setNext(Node<t>* nxt) { next = nxt; }
	Node<t>*getNext() { return next; }
};