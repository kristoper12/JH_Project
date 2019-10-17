#pragma once
#ifndef _NODE_INT_H
#define _NODE_INT_H
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct _Node{
	struct _Node * m_pPrevious;
	struct _Node * m_pNext;
	int m_iObject;
}Node;

#endif