#pragma once
#include "THashTable.h"
#include <list>
class TListHash :public THashTable
{
protected:
	list<TRecord>* pList;
	int size, CurrList;
	list<TRecord>::iterator pCurr;
public:

	TListHash(int _size = MAX_SIZE)
	{
		if (_size > MAX_SIZE)
		{
			throw exception();
		}
		size = _size;
		pList = new list<TRecord>[size];
	}
	~TListHash()
	{
		delete[] pList;
	}

	bool Find(TKey _key)
	{
		CurrList = HashFunc(_key) % size;
		for (pCurr = pList[CurrList].begin(); pCurr != pList[CurrList].end(); pCurr++)
		{
			Eff++;
			if (pCurr->key == _key)
			{
				return true;
			}
		}
		return false;
	}
	bool Insert(TRecord record)
	{
		bool isfind = Find(record.key);
		if (isfind) { return false; }
		else
		{
			pList[CurrList].push_front(record);
			DCount++;
		}
		return true;
	}
	bool Delete(TKey _key)
	{
		if (this->IsEmpty())
		{
			throw exception();
		}

		bool isfind = Find(_key);
		if (!isfind) { return false; }
		else
		{
			pList[CurrList].erase(pCurr);
			DCount--;
		}
		return true;
	}

	void Reset()
	{
		CurrList = 0;
		pCurr = pList[CurrList].begin();
		while (pCurr == pList[CurrList].end())
		{
			CurrList++;
			if (CurrList < size)
			{
				pCurr = pList[CurrList].begin();
			}
			else
			{
				break;
			}
		}
	}
	void GoNext()
	{
		pCurr++;
		while (pCurr == pList[CurrList].end())
		{
			CurrList++;
			if (CurrList < size)
			{
				pCurr = pList[CurrList].begin();
			}
			else
			{
				break;
			}
		}
	}
	bool IsEnd()
	{
		return CurrList == size - 1;
	}

	int GetSize() { return size; }
	bool IsFull() const
	{
		if (DCount == size)
			return true;
		else
		{
			return false;
		}
	};
	virtual int GetCurrentPos() { return CurrList; }
	virtual void SetCurrentPos(int _curPos)
	{
		if (_curPos < size)
		{
			CurrList = _curPos;
		}
		else {
			throw exception();
		}
	}
	TRecord GetCurrentRecord()
	{
		return *pCurr;
	}
	void SetCurrentRecord(TRecord record)
	{
		if (CurrList<0 && CurrList>size)
		{
			throw exception();
		}
		pList[CurrList].push_front(record);

	}
};

