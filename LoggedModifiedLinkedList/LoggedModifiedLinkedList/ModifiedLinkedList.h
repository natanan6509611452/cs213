#ifndef MODIFIEDLINKEDLIST_H_
#define MODIFIEDLINKEDLIST_H_
#include <cstddef>

class ModifiedLinkedList {
	public:
		ModifiedLinkedList() {head = NULL; counter=0;}
			void add(double);
			void getData(double*&, int&);
			ModifiedLinkedList* clone();
			ModifiedLinkedList* mergeWith(ModifiedLinkedList*);
			int cut(int, ModifiedLinkedList* &, ModifiedLinkedList* &);
			void removeAllNodes();
			void print();
	protected:
		struct Node	{
			double data;
			Node *next;
			Node (double d) {data=d; next = NULL;}
		};
		int counter;
		Node* head;
		Node* mid;
};

#endif /* MODIFIEDLINKEDLIST_H_ */
