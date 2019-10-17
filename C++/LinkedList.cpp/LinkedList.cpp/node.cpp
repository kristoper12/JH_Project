#include "node.h"



node::node(int _iObject) {
	m_pNext = this;
	m_pPrevious = this;
	m_iObject = _iObject;
}

node::~node()
{
}

node* node::GetNode(int _iObject) {
	return this;
}	// 노드 생성