#ifndef OPERATORS_H_
#define OPERATORS_H_
#include <string>

class Operators {
public:
	void cutList(int);
	void undo();
	void cloneList();
	void printCurrentList();
	void printHistory();
	void makeList(double[], int);
	void undoAll();
	void reset();
	Operators(int sSize=20) {
		ops = new Op*[sSize]();
		lists = new ModifiedLinkedList*[sSize]();
		topOp = -1;
		topList = -1;
		maxTopLists = sSize;
		maxTopOps = sSize;
	}

protected :
	struct Op{
		std::string op;
		int pos;
		Op(int position) {
			if (position == -1) {
				op = "CLONE";
				pos = -1;
			}
			else {
				op = "CUT";
				pos = position;
			}
		}
	};
	ModifiedLinkedList** lists;
	Op** ops;
	int topOp;
	int topList;
	int maxTopOps;
	int maxTopLists;
};



#endif /* OPERATORS_H_ */
