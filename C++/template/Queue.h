//tempalte queue
#include<iostream>

// queueItem

template<class Type> 
class QueueItem
{
	QueueItem(const Type &t):item(t),next(0){}
	Type item;
	QueueItem *next;
};

template<class Type>
class Queue
{
public:
	Queue():head(0),tail(0){}
	
	Queue(const Queue& q):head(0),tail(0){ copy_element(q);}
		
	Queue& operator=(const Queue&);
	~Queue(){destroy();}
	
	Type& front() {return head->item;}
	const Type& front() const { return head->item;}
	void push(const Type&);
	void pop();
	bool empty() { return head == 0; }
private:
	
QueueItem<Type> *head;
QueueItem<Type> *tail;

void destroy();
void copy_elements(const Queue&);
};
 
 
 
 template<class Type> 
 void Queue<Type>::pop()
 {
	 QueueItem<Type>* p = head;
	 head = head->next;
	 delete p;
 }
 template<class Type>
 void Queue<Type>::push(const Type& val)
 {
	 QueueItem<Type> *pt = new QueueItem<Type>(val);
	 if(empty())
	 {
		 head = tail = pt;
	 }
	 else
	 {
		 tail->next = pt;
		 tail = pt;
	 }
	 
 }
 
 
 template<class Type>
 void Queue<Type>::copy_elements(const Queue&orig)
 {
	 
	 for(Queue<Type> *pt = orig.head; pt; pt = pt->next)
	 {
		 push(pt->item);
	 }
 }
 