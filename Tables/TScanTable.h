#pragma once
#include"TArrayTable.h"

class TScanTable :public TArrayTable
{
public:
	TScanTable(int _size = MAX_SIZE) : TArrayTable(_size) {};

	bool Find(TKey key)
	{
		for (int i = 0; i < DCount; i++)
		{
			Eff++;
			if (arr[i].key == key)
			{
				currentPos = i;
				return true;
			}
		}
		currentPos = DCount;
		return false;
	}
	bool Insert(TRecord _rec) {
		if (IsFull() || Find(_rec.key)) return false;
		this->arr[this->DCount] = _rec;
		Eff++;
		this->DCount++;
		return true;
	}

	bool Delete(TKey _key) {
		if (!Find(_key)) return false;
		arr[currentPos] = arr[DCount - 1];
		DCount--;
		Eff++;
		return true;
	};

	TScanTable operator=(const TScanTable& _tab)
	{
		this->DCount = _tab.DCount;
		this->Eff = _tab.Eff;
		delete[] this->arr;
		this->size = _tab.size;
		this->arr = new TRecord[this->size];
		for (int i = 0; i < this->size; i++)
		{
			this->arr[i] = _tab.arr[i];
		}
		this->currentPos = _tab.currentPos;
		return *this;
	}
};