#pragma once
#include<iostream>
#include"Node.h"
using namespace std;

template<class t>
class LinkedList
{
private:
	Node<t>* head;
public:
	LinkedList(const LinkedList& l)
	{
		if (l.head == NULL)
			head = NULL;
		else
		{
			head = new Node<t>(l.head->getData());
			Node<t>*pn1 = l.head;
			Node<t>*pn2 = head;
			pn1 = pn1->getNext();
			while (pn1 != NULL)
			{
				pn2 ->setNext(new Node<t>(pn1->getData()));
				pn2 = pn2->getNext();
				pn1 = pn1->getNext();

			}
		}
	}
	LinkedList& operator=(const LinkedList& l)
	{
		clear();
		if (l.head == NULL)
			head = NULL;
		else
		{
			head = new Node<t>(l.head->getData());
			Node<t>* pn1 = l.head;
			Node<t>* pn2 = head;
			pn1 = pn1->getNext();
			while (pn1 != NULL)
			{
				pn2->setNext(new Node<t>(pn1->getData()));
				pn2 = pn2->getNext();
				pn1 = pn1->getNext();

			}
		}
		return*this;
	}
	LinkedList()
	{
		head = NULL;
	}
	bool isEmpty()
	{
		return head == NULL;
	}
	void insertFirst(t val)
	{
		Node<t>* newNode = new Node<t>;
		newNode->setData(val);
		//if there are no nodes yet
		if (isEmpty()) {
			head = newNode;
			newNode->setNext(NULL);
		}
		else
		{
			newNode->setNext(head);
			head = newNode;
		}
	}
	void insertFirstNode(Node<t>*val)
	{//if there are no nodes yet
		if (isEmpty()) {
			head = val;
			val->setNext(NULL);
		}
		else
		{
			val->setNext(head);
			head = val;
		}
	}	void insertLast(t val)
	{
		Node<t>* newNode = new Node<t>;
		newNode->setData(val);
		newNode->setNext(NULL);
		//if there are no nodes yet
		if (isEmpty())
		{
			head = newNode;
		}
		else
		{
			Node<t>* tmp;
			for (tmp = head; tmp->getNext() != NULL; tmp = tmp->getNext());
			tmp->setNext(newNode);
		}
	}
	void removeFirst()
	{
		if (head)
			head = head->getNext();
	}
	bool insertBefore(t bef, t val)
	{
		//no value to insert before
		if (!exists(bef))
			return false;
		else if (head->getData() == bef)
		{
			// value is in head
			insertFirst(val);
			return true;
		}
		else
		{
			Node<t>* newNode = new Node<t>;
			newNode->setData(val);
			Node<t>* tmp;
			// loop until next is the Node required
			for (tmp = head; tmp->getNext()->getData() != bef; tmp = tmp->getNext());
			newNode->setNext(tmp->getNext());
			tmp->setNext(newNode);
			return true;
		}
	}
	bool insertAfter(t aft, t val)
	{
		if (!exists(aft))
			return false;
		else if (head->getData() == aft)
		{
			insertBefore(head->getNext()->getData(), val);
			return true;
		}
		else
		{
			Node<t>* newNode = new Node<t>;
			newNode->setData(val);
			Node<t>* tmp;
			for (tmp = head; tmp->getNext()->getData() != aft; tmp = tmp->getNext());
			tmp = tmp->getNext();
			newNode->setNext(tmp->getNext());
			tmp->setNext(newNode);
			return true;
		}
	}
	void display()
	{
		if (!isEmpty())
		{
			for (Node<t>* tmp = head; tmp != NULL; tmp = tmp->getNext()) {
				cout << tmp->getData();
				if (tmp->getNext() != NULL)
					cout << "-->";
			}
			cout << endl;
		}
	}
	
	void Recursivedisplay(Node<t>*hd)
	{
			if (hd == NULL)
			{
				cout <<endl;
				return;
	     	}
			cout << hd->getData();
			if (hd->getNext() != NULL)
			cout<< "-->";
			Recursivedisplay(hd->getNext());
			return;
	}
	void BackwardDisplay(Node<t>*hd)
	{
		if (hd->getNext() != NULL)
		{
			BackwardDisplay(hd->getNext());
		}
		cout << hd->getData();
		if (hd != head)
			cout << "-->";
	}
	int count()const
	{
		int n = 0;
		for (Node<t>* tmp = head; tmp != NULL; tmp = tmp->getNext()) 
			n++;
		return n;
	}
	bool exists(t val)
	{
		if (isEmpty())
			return false;
		for (Node<t>* tmp = head; tmp != NULL; tmp = tmp->getNext())
		{
			if (tmp-> getData() == val)
				return true;
		}
		return false;
	}
	bool del(t val)
	{
		if (!exists(val))
			return false;
		else
		{
			Node<t>* tmp;
			if (head->getData() == val)
			{
				tmp = head;
				head = head->getNext();
				delete tmp;
				return true;
			}
			else
			{
				for (tmp = head; tmp->getNext()->getData() != val; tmp = tmp->getNext());
					Node<t>* ptr = tmp->getNext();
					tmp->setNext(tmp->getNext()->getNext());
					delete ptr;
			}
		}
	}
	bool deleteFirst()
	{
		if (head)
		{
			Node<t>* tmp = head;
			head = head->getNext();
			delete tmp;
			return true;
		}
		return false;
	}
	bool Replace(t val1,t val2)
	{
		if (!exists(val1))
			return false;
		Node<t>* tmp;
		for (tmp = head; tmp->getData() != val1; tmp = tmp->getNext());
		tmp->setData(val2);
		return true;
	}
	bool checkSorted(Node<t>* hd)
	{
		if (!hd || !hd->getNext())
			return true;
		if (hd->getData() > hd->getNext()->getData())
			return false;
		return checkSorted(hd->getNext());
	}
	Node<t>* Reverse(Node<t>*hd)
	{
		if (!hd||!hd->getNext())
			return hd;
		else
		{
			Node<t>*reset = Reverse(hd->getNext());
			hd->getNext()->setNext(hd);
			hd->setNext(NULL);
			return reset;
		}
	}
	void setHead(Node<t>*hd)
	{
		head = hd;
	}
	void clear()
	{
		if (!isEmpty()) {
			Node<t>* tmp;
			while (head != NULL)
			{
				tmp = head;
				head = head->getNext();
				delete tmp;
			}
		}
	}
	t getFirst()
	{
		if (head == NULL)
		{
			return NULL;
		}
		else
		{
			return head->getData();
		}
	}
	~LinkedList()
	{ 
		clear();
	}
};

