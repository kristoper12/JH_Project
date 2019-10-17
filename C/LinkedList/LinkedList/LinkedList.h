#pragma once
#ifndef _LINKEDLIST_INT_H
#define _LINKEDLIST_INT_H
#include "Node.h"

typedef struct{
	Node * m_pHead;
	Node * m_pTail;
	Node * m_pCurrent;
	Node * m_pTemp;
	unsigned int m_uCount;
}LinkedList;
#endif


