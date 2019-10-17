#include "LinkedList.h"



LinkedList::~LinkedList()
{
}
node* LinkedList::Read(int _cnt) {
	m_pCurrent = m_pHead;
	if (m_uCount < _cnt) {
		cout << "입력하신 번호가 없습니다.\n";
		return NULL;
	}
	for (int i = 1; i < _cnt; i++) {
		m_pCurrent = m_pCurrent->GetNext();
	}

	cout << m_pCurrent->GetiObject();

	return m_pCurrent;
}	// 임의 위치 값 읽기
void LinkedList::Display() {
	m_pCurrent = m_pHead;

	for (int i = 0; i < m_uCount; i++) {
		if (i == (m_uCount - 1))
			cout << m_pCurrent->GetiObject();
		else
			cout << m_pCurrent->GetiObject() << " -> ";
		m_pCurrent = m_pCurrent->GetNext();
	}
	cout << '\n';
}	//	화면 출력
node* LinkedList::AppendFromHead(int _iObject) {
	m_pCurrent = new node(_iObject);

	if (m_pHead) {
		m_pCurrent->SetNext(m_pHead);
		m_pHead->SetPrevious(m_pCurrent);
	}
	else
		m_pTail = m_pCurrent;
	m_pHead = m_pCurrent;
	(m_uCount)++;

	return m_pCurrent;
}	// 앞 노드 추가
node* LinkedList::AppendFromTail(int _iObject) {
	m_pCurrent = new node(_iObject);

	if (m_pHead) {
		m_pCurrent->SetPrevious(m_pTail);
		m_pTail->SetNext(m_pCurrent);
	}
	else
		m_pHead = m_pCurrent;
	m_pTail = m_pCurrent;
	(m_uCount)++;

	return m_pCurrent;
}	// 뒤 노드 추가
node* LinkedList::InsertBefore(int _cnt, int _iObject) {
	if (m_uCount < _cnt) {
		cout << "입력하신 번호에 노드가 존재하지 않습니다.\n번호와 데이터를 다시 입력해주세요.\n";
		return NULL;
	}
	m_pTemp = new node(_iObject);
	m_pCurrent = m_pHead;
	for (int i = 0; i < _cnt - 1; i++)
		m_pCurrent = m_pCurrent->GetNext();
	if (_cnt == 1) {
		m_pTemp->SetNext(m_pCurrent);
		m_pCurrent->SetPrevious(m_pTemp);
		m_pHead = m_pTemp;
	}
	else {
		m_pTemp->SetNext(m_pCurrent);
		m_pTemp->SetPrevious(m_pCurrent->GetPrevious());
		m_pCurrent->GetPrevious()->SetNext(m_pTemp);
		m_pCurrent->SetPrevious(m_pTemp);
	}
	m_uCount++;
}
node* LinkedList::InsertAfter(int _cnt, int _iObject) {
	if (m_uCount < _cnt) {
		cout << "입력하신 번호에 노드가 존재하지 않습니다.\n번호와 데이터를 다시 입력해주세요.\n";
		return NULL;
	}
	m_pTemp = new node(_iObject);
	m_pCurrent = m_pHead;
	for (int i = 1; i < _cnt; i++)
		m_pCurrent = m_pCurrent->GetNext();
	if (m_uCount == _cnt) {
		m_pTemp->SetPrevious(m_pTail);
		m_pTail->SetNext(m_pTemp);
		m_pTail = m_pTemp;
	}
	else {
		m_pTemp->SetNext(m_pCurrent->GetNext());
		m_pTemp->SetPrevious(m_pCurrent);
		m_pCurrent->GetNext()->SetPrevious(m_pTemp);
		m_pCurrent->SetNext(m_pTemp);
	}
	m_uCount++;
}
node* LinkedList::DeleteFromHead() {
	node *q;

	if (m_pHead) {
		if (m_uCount == 1) {
			m_uCount--;
			q = m_pHead;
			delete(m_pHead);
			m_pHead = NULL;
			return q;
		}
		else {
			m_pHead = m_pHead->GetNext();
			m_uCount--;
			q = m_pHead->GetPrevious();
			delete(m_pHead->GetPrevious());
			m_pHead->SetPrevious(m_pHead);
			return q;
		}
	}	
	cout << "데이터가 존재하지 않습니다.\n";
	return NULL;
}
node* LinkedList::DeleteFromTail() {
	node *q;

	if (m_pHead) {
		if (m_uCount == 1) {
			m_uCount--;
			q = m_pHead;
			delete(m_pHead);
			m_pHead = NULL;
			return q;
		}
		else {
			m_pTail = m_pTail->GetPrevious();
			m_uCount--;
			q = m_pTail->GetNext();
			delete(m_pTail->GetNext());
			m_pTail->SetNext(m_pTail);
			return q;
		}
	}
	cout << "데이터가 존재하지 않습니다.\n";
	return NULL;
}
node* LinkedList::Delete(int _cnt) {
	node *q;
	if (m_uCount < _cnt) {
		cout << "입력하신 번호에 노드가 존재하지 않습니다.\n번호와 데이터를 다시 입력해주세요.\n";
		return NULL;
	}
	m_pCurrent = m_pHead;
	if (m_pHead) {
		for (int i = 0; i < _cnt; i++)
			m_pCurrent = m_pCurrent->GetNext();
		if (m_uCount == 1) {
			q = m_pCurrent;
			delete(m_pCurrent);
			m_pHead = NULL;
			return q;
		}
		else if (m_uCount == _cnt) {
			m_pTail = m_pTail->GetPrevious();
			q = m_pTail->GetNext();
			delete(m_pTail->GetNext());
		}
		else if (_cnt == 1) {
			m_pHead = m_pHead->GetNext();
			q = m_pHead->GetPrevious();
			delete(m_pHead->GetPrevious());
		}
		else {
			m_pCurrent->GetNext()->SetPrevious(m_pCurrent->GetPrevious());
			m_pCurrent->GetPrevious()->SetNext(m_pCurrent->GetNext());
		}
		m_uCount--;
		return q;
	}
	cout << "데이터가 존재하지 않습니다.\n";
	return NULL;
}
void LinkedList::DeleteAll() {
	m_pCurrent = m_pHead;
	while (m_uCount != 0) {
		DeleteFromHead();
	}
}
node *LinkedList::Modify(int _cnt, int _iObject) {
	if (m_uCount < _cnt) {
		cout << "입력하신 번호에 노드가 존재하지 않습니다.\n번호와 데이터를 다시 입력하주세요.\n";
		return NULL;
	}
	m_pCurrent = m_pHead;
	for (int i = 1; i <= _cnt; i++)
		m_pCurrent = m_pCurrent->GetNext();
	m_pCurrent->SetiObject(_iObject);
}
void LinkedList::SortByBubble(int _option) {
	int temp;
	if (m_uCount == 0) {
		cout << "Sort할 노드가 없습니다.\n";
		return;
	}
	if (_option == 1) {
		for (int i = 0; i < m_uCount; i++) {
			m_pCurrent = m_pHead;
			for (int j = 0; j < m_uCount - i; j++) {
				m_pTemp = m_pCurrent->GetNext();
				if (m_pCurrent->GetiObject() > m_pTemp->GetiObject()) {
					if (m_pCurrent == m_pHead) {
						m_pHead = m_pTemp;
						m_pCurrent->SetNext(m_pTemp->GetNext());
						m_pTemp->SetNext(m_pCurrent);
						m_pCurrent->GetNext()->SetPrevious(m_pCurrent);
						m_pCurrent->SetPrevious(m_pTemp);
					}
					else if (m_pTemp == m_pTail) {
						m_pTail = m_pCurrent;
						m_pCurrent->GetPrevious()->SetNext(m_pTemp);
						m_pTemp->SetPrevious(m_pCurrent->GetPrevious());
						m_pTemp->SetNext(m_pCurrent);
						m_pCurrent->SetPrevious(m_pTemp);
					}
					else {
						m_pCurrent->GetPrevious()->SetNext(m_pTemp);
						m_pTemp->SetPrevious(m_pCurrent->GetPrevious());
						m_pCurrent->SetNext(m_pTemp->GetNext());
						m_pTemp->SetNext(m_pCurrent);
						m_pCurrent->GetNext()->SetPrevious(m_pCurrent);
						m_pCurrent->SetPrevious(m_pTemp);
					}
				}
				else {
					m_pCurrent = m_pCurrent->GetNext();
				}
			}
		}
	}
	else if (_option == 2) {
		for (int i = 0; i < m_uCount; i++) {
			m_pCurrent = m_pHead;
			for (int j = 0; j < m_uCount - i; j++) {
				m_pTemp = m_pCurrent->GetNext();
				if (m_pCurrent->GetiObject() < m_pTemp->GetiObject()) {
					if (m_pCurrent == m_pHead) {
						m_pHead = m_pTemp;
						m_pCurrent->SetNext(m_pTemp->GetNext());
						m_pTemp->SetNext(m_pCurrent);
						m_pCurrent->GetNext()->SetPrevious(m_pCurrent);
						m_pCurrent->SetPrevious(m_pTemp);
					}
					else if (m_pTemp == m_pTail) {
						m_pTail = m_pCurrent;
						m_pCurrent->GetPrevious()->SetNext(m_pTemp);
						m_pTemp->SetPrevious(m_pCurrent->GetPrevious());
						m_pTemp->SetNext(m_pCurrent);
						m_pCurrent->SetPrevious(m_pTemp);
					}
					else {
						m_pCurrent->GetPrevious()->SetNext(m_pTemp);
						m_pTemp->SetPrevious(m_pCurrent->GetPrevious());
						m_pCurrent->SetNext(m_pTemp->GetNext());
						m_pTemp->SetNext(m_pCurrent);
						m_pCurrent->GetNext()->SetPrevious(m_pCurrent);
						m_pCurrent->SetPrevious(m_pTemp);
					}
				}
				else {
					m_pCurrent = m_pCurrent->GetNext();
				}
			}
		}
	}
}
void LinkedList::SortByInsertion(int _option) {
	int temp;
	int cnt;

	node *q;
	if (m_uCount == 0) {
		cout << "Sort할 노드가 없습니다.\n";
		return;
	}
	m_pCurrent = m_pHead;
	if (_option == 1) {
		for (int i = 1; i < m_uCount; i++) {
			m_pCurrent = m_pCurrent->GetNext();
			m_pTemp = m_pCurrent;
			cnt = 1;
			for (int j = i - 1; j >= 0; j--) {
				q = m_pTemp->GetPrevious();
				if (q->GetiObject() > m_pTemp->GetiObject()) {
					if (q == m_pHead) {
						m_pHead = m_pTemp;
						q->SetNext(m_pTemp->GetNext());
						m_pTemp->SetNext(q);
						q->GetNext()->SetPrevious(q);
						q->SetPrevious(m_pTemp);
						if (cnt == 1) {
							cnt = 0;
							m_pCurrent = q;
						}
					}
					else if (m_pTemp == m_pTail) {
						m_pTail = q;
						q->GetPrevious()->SetNext(m_pTemp);
						m_pTemp->SetPrevious(q->GetPrevious());
						m_pTemp->SetNext(q);
						q->SetPrevious(m_pTemp);
					}
					else {
						if (cnt == 1) {
							cnt = 0;
							m_pCurrent = q;
						}
						q->GetPrevious()->SetNext(m_pTemp);
						m_pTemp->SetPrevious(q->GetPrevious());
						q->SetNext(m_pTemp->GetNext());
						m_pTemp->SetNext(q);
						q->GetNext()->SetPrevious(q);
						q->SetPrevious(m_pTemp);
					}
				}
			}
		}
	}
	if (_option == 2) {
		for (int i = 1; i < m_uCount; i++) {
			m_pCurrent = m_pCurrent->GetNext();
			m_pTemp = m_pCurrent;
			cnt = 1;
			for (int j = i - 1; j >= 0; j--) {
				q = m_pTemp->GetPrevious();
				if (q->GetiObject() < m_pTemp->GetiObject()) {
					if (q == m_pHead) {
						m_pHead = m_pTemp;
						q->SetNext(m_pTemp->GetNext());
						m_pTemp->SetNext(q);
						q->GetNext()->SetPrevious(q);
						q->SetPrevious(m_pTemp);
						if (cnt == 1) {
							cnt = 0;
							m_pCurrent = q;
						}
					}
					else if (m_pTemp == m_pTail) {
						m_pTail = q;
						q->GetPrevious()->SetNext(m_pTemp);
						m_pTemp->SetPrevious(q->GetPrevious());
						m_pTemp->SetNext(q);
						q->SetPrevious(m_pTemp);
					}
					else {
						if (cnt == 1) {
							cnt = 0;
							m_pCurrent = q;
						}
						q->GetPrevious()->SetNext(m_pTemp);
						m_pTemp->SetPrevious(q->GetPrevious());
						q->SetNext(m_pTemp->GetNext());
						m_pTemp->SetNext(q);
						q->GetNext()->SetPrevious(q);
						q->SetPrevious(m_pTemp);
					}
				}
			}
		}
	}/*
	m_pCurrent = m_pHead;
	if (_option == 1) {
		for (int i = 1; i < m_uCount; i++) {
			m_pCurrent = m_pCurrent->GetNext();
			m_pTemp = m_pCurrent->GetPrevious();
			for (int j = i - 1; j >= 0; j--) {
				if (m_pTemp->GetiObject() > m_pCurrent->GetiObject()) {
					temp = m_pTemp->GetiObject();
					m_pTemp->SetiObject(m_pCurrent->GetiObject());
					m_pCurrent->SetiObject(temp);
				}
			}
		}
	}
	else if (_option == 2) {
		for (int i = 1; i < m_uCount; i++) {
			m_pCurrent = m_pCurrent->GetNext();
			m_pTemp = m_pCurrent->GetPrevious();
			for (int j = i - 1; j >= 0; j--) {
				if (m_pTemp->GetiObject() < m_pCurrent->GetiObject()) {
					temp = m_pTemp->GetiObject();
					m_pTemp->SetiObject(m_pCurrent->GetiObject());
					m_pCurrent->SetiObject(temp);
				}
			}
		}
	}*/
}
void LinkedList::SortBySelection(int _option) {
	int temp, Min, Min_Address;

	m_pCurrent = m_pHead;
	if (m_uCount == 0) {
		cout << "Sort할 노드가 없습니다.\n";
		return;
	}
	if (_option == 1) {
		for (int i = 0; i < m_uCount - 1; i++) {
			m_pTemp = m_pCurrent;
			Min = m_pTemp->GetiObject();
			Min_Address = 0;
			for (int j = 0; j < m_uCount - i; j++) {
				if (m_pTemp->GetiObject() < Min) {
					Min = m_pTemp->GetiObject();
					Min_Address = j + i;
				}
				m_pTemp = m_pTemp->GetNext();
			}
			if (Min_Address != 0) {
				m_pTemp = m_pHead;
				for (int k = 0; k < Min_Address; k++)
					m_pTemp = m_pTemp->GetNext();
				temp = m_pCurrent->GetiObject();
				m_pCurrent->SetiObject(m_pTemp->GetiObject());
				m_pTemp->SetiObject(temp);
			}
			m_pCurrent = m_pCurrent->GetNext();
		}
	}
	else if (_option == 2) {
		for (int i = 0; i < m_uCount - 1; i++) {
			m_pTemp = m_pCurrent;
			Min = m_pTemp->GetiObject();
			Min_Address = 0;
			for (int j = 0; j < m_uCount - i; j++) {
				if (m_pTemp->GetiObject() > Min) {
					Min = m_pTemp->GetiObject();
					Min_Address = j + i;
				}
				m_pTemp = m_pTemp->GetNext();
			}
			if (Min_Address != 0) {
				m_pTemp = m_pHead;
				for (int k = 0; k < Min_Address; k++)
					m_pTemp = m_pTemp->GetNext();
				temp = m_pCurrent->GetiObject();
				m_pCurrent->SetiObject(m_pTemp->GetiObject());
				m_pTemp->SetiObject(temp);
			}
			m_pCurrent = m_pCurrent->GetNext();
		}
	}
}
node *LinkedList::LinearSearchByUnique(int SearchObject) {
	m_pCurrent = m_pHead;
	for (int i = 0; i < m_uCount; i++) {
		if (m_pCurrent->GetiObject() == SearchObject) {
			cout << "주소 : " << i+1 << "\n값 : " << m_pCurrent->GetiObject() << endl;
			return m_pCurrent;
		}
		m_pCurrent = m_pCurrent->GetNext();
	}
	cout << "입력하신 값이 없습니다.\n";
	return NULL;
}
void LinkedList::LinearSearchByDuplicate(LinkedList *_ptList_Temp, int SearchObject) {
	int *Index = (int *)malloc(sizeof(int)*m_uCount);
	int k = 0;
	m_pCurrent = m_pHead;
	for (int i = 0; i < m_uCount; i++) {
		if (m_pCurrent->GetiObject() == SearchObject) {
			_ptList_Temp->m_pCurrent = new node(SearchObject);
			if (_ptList_Temp->m_uCount == 0) {
				_ptList_Temp->m_pHead = _ptList_Temp->m_pCurrent;
				_ptList_Temp->m_pTail = _ptList_Temp->m_pCurrent;
				(_ptList_Temp->m_uCount)++;
			}
			else
				_ptList_Temp->AppendFromTail(SearchObject);
			Index[k] = i + 1;
			k++;
		}
		m_pCurrent = m_pCurrent->GetNext();
	}
	if (m_uCount == 0)
		cout << "입력하신 값이 없습니다.\n";
	else {
		_ptList_Temp->m_pCurrent = _ptList_Temp->m_pHead;
		for (int i = 0; i < k; i++) {
			cout << "주소 : " << Index[i] << "\n값 : " << _ptList_Temp->m_pCurrent->GetiObject() << endl;
			_ptList_Temp->m_pCurrent = _ptList_Temp->m_pCurrent->GetNext();
		}
	}
}
node *LinkedList::BinarySearchByUnique(int SearchObject) {
	int low, high, mid;

	SortBySelection(1);
	low = 1;
	high = m_uCount;
	mid = (low + high) / 2;

	while (low <= high) {
		m_pCurrent = m_pHead;
		for (int i = 1; i < mid; i++)
			m_pCurrent = m_pCurrent->GetNext();
		if (m_pCurrent->GetiObject() > SearchObject) {
			high = mid - 1;
			mid = (low + high) / 2;
		}
		else if (m_pCurrent->GetiObject() < SearchObject) {
			low = mid + 1;
			mid = (low + high) / 2;
		}
		else {
			cout << "주소 : " << mid << "\n값 : " << m_pCurrent->GetiObject() << endl;
			return m_pCurrent;
		}
	}
	cout << "입력하신 값이 없습니다.\n";
	return NULL;
}
void LinkedList::BinarySearchByDuplicate(LinkedList *_ptList_Temp, int SearchObject) {
	int low, high, mid, check = 0;
	int *Index = (int *)malloc(sizeof(int)*m_uCount);
	int k = 0;

	SortBySelection(1);
	low = 1;
	high = m_uCount;
	mid = (low + high) / 2;

	while (low <= high) {
		m_pCurrent = m_pHead;
		for (int i = 0; i < mid; i++)
			m_pCurrent = m_pCurrent->GetNext();
		if (m_pCurrent->GetiObject() > SearchObject) {
			high = mid - 1;
			mid = (low + high) / 2;
		}
		else if (m_pCurrent->GetiObject() < SearchObject) {
			low = mid + 1;
			mid = (low + high) / 2;
		}
		else {
			check = 1;
			int i = mid;
			while (m_pCurrent->GetPrevious()->GetiObject() == SearchObject) {
				m_pCurrent = m_pCurrent->GetPrevious();
				i--;
				if (m_pCurrent->GetPrevious() == m_pHead)
					break;
			}
			while (m_pCurrent->GetiObject() == SearchObject) {
				if (_ptList_Temp->m_uCount == 0) {
					_ptList_Temp->m_pCurrent = new node(SearchObject);
					_ptList_Temp->m_pHead = _ptList_Temp->m_pCurrent;
					_ptList_Temp->m_pTail = _ptList_Temp->m_pCurrent;
					(_ptList_Temp->m_uCount)++;
					m_pCurrent = m_pCurrent->GetNext();
				}
				else {
					_ptList_Temp->AppendFromTail(SearchObject);
					m_pCurrent = m_pCurrent->GetNext();
				}
				Index[k] = i + 1;
				i++;
				k++;
				if (i == m_uCount)
					break;
			}
			break;
		}
	}
	if (check == 0)
		cout << "입력하신 값이 없습니다.\n";
	else {
		_ptList_Temp->m_pCurrent = _ptList_Temp->m_pHead;
		for (int i = 0; i < k; i++) {
			cout << "주소 : " << Index[i] << "\n값 : " << _ptList_Temp->m_pCurrent->GetiObject() << endl;
			_ptList_Temp->m_pCurrent = _ptList_Temp->m_pCurrent->GetNext();
		}
	}

}