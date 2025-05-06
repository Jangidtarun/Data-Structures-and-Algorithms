#ifndef _P3_STACK_ADT_H
#define _P3_STACK_ADT_H


struct STACK_NODE {
	void *dataptr;
	struct stack_node *link;
};


struct STACK {
	int count;
	struct stack_node *top;
};









































#endif
