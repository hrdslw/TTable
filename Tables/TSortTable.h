#pragma once
#include "TScanTable.h"

enum SortType { Merge, Bubble, Quick };

class TSortTable :public TScanTable
{
private:
	void BubbleSort();
	void QuickSort(int first, int last);
	void MergeSort(int left, int right);
	void Merge(int left, int mid, int right);

public:
	TSortTable(int _size = MAX_SIZE) :TScanTable(_size) {};
	void ScanToSort(TScanTable& _tab, SortType _sortType);

	bool Find(TKey key);
	bool Insert(TRecord record);
	bool Delete(TKey key);

	TSortTable operator=(const TSortTable& _tab)
	{
		if (this->size != _tab.size)
		{
			delete[] this->arr;
			this->size = _tab.size;
			this->arr = new TRecord[this->size];
		}
		this->DCount = _tab.DCount;
		this->Eff = _tab.Eff;
		for (int i = 0; i < this->size; i++)
		{
			this->arr[i] = _tab.arr[i];
		}
		this->currentPos = _tab.currentPos;
		return *this;
	}
};
inline void TSortTable::QuickSort(int first, int last)
{
	if (this->IsEmpty()) return;

	int mid = (first + last) / 2;
	TKey key = this->arr[mid].key;
	int leftPos = first, rightPos = last;

	while (leftPos < rightPos)
	{
		while (this->arr[leftPos].key < key)
		{
			leftPos++;
			this->Eff++;
		}
		while (this->arr[rightPos].key > key)
		{
			rightPos--;
			this->Eff++;
		}
		if (leftPos <= rightPos)
		{
			std::swap(this->arr[leftPos], this->arr[rightPos]);
			leftPos++;
			rightPos--;
			this->Eff++;
		}
	}

	if (rightPos > first) QuickSort(first, rightPos);
	if (leftPos < last) QuickSort(leftPos, last);
}

inline void TSortTable::BubbleSort()
{
	if (this->IsEmpty()) return;

	for (int i = 0; i < this->DCount; i++)
	{
		for (int j = i + 1; j < this->DCount; j++)
		{
			if (this->arr[i].key > this->arr[j].key)
			{
				std::swap(this->arr[i], this->arr[j]);
			}
		}
	}
}

inline void TSortTable::MergeSort(int left, int right)
{
	if (left == right)
	{
		return;
	}
	else
	{
		int mid = (right + left) / 2;
		MergeSort(left, mid);
		MergeSort(mid + 1, right);
		Merge(left, mid, right);
	}
}

inline void TSortTable::Merge(int left, int mid, int right)
{
	TRecord* mas2;
	mas2 = new TRecord[this->DCount];

	int i = left, j = mid + 1, k = left;
	while (i <= mid && j <= right)
	{
		if (this->arr[i].key < this->arr[j].key)
		{
			mas2[k] = this->arr[i];
			k++; i++;
		}
		else
		{
			mas2[k] = this->arr[j];
			k++; j++;
		}
	}

	if (i > mid)
	{
		while (j <= right)
		{
			mas2[k] = this->arr[j];
			j++; k++;
		}
	}
	else
	{
		while (i <= mid)
		{
			mas2[k] = this->arr[i];
			i++; k++;
		}
	}

	for (i = left; i <= right; i++)
	{
		this->arr[i] = mas2[i];
	}
	delete[] mas2;
}

inline void TSortTable::ScanToSort(TScanTable& _tab, SortType _sortType)
{
	for (this->Reset(), _tab.Reset(); !_tab.IsEnd(); _tab.GoNext(), this->GoNext())
	{
		this->SetCurrRecord(_tab.GetCurrRecord());
		this->DCount++;
	}
	if (_sortType == SortType::Quick) this->QuickSort(0, this->DCount - 1);
	if (_sortType == SortType::Merge) this->MergeSort(0, this->DCount - 1);
	if (_sortType == SortType::Bubble) this->BubbleSort();
}

inline bool TSortTable::Find(TKey _key)
{
	int begin = 0, end = this->DCount - 1, middle;
	while (begin <= end)
	{
		Eff++;
		middle = (begin + end) / 2;
		if (this->arr[middle].key < _key)
		{
			begin = middle + 1;
		}
		else if (this->arr[middle].key > _key)
		{
			end = middle - 1;
		}
		else {
			this->currentPos = middle; return true;
		}
	}
	this->currentPos = begin;
	return false;
}

inline bool TSortTable::Insert(TRecord _rec)
{
	if (IsFull() || Find(_rec.key))
	{
		return false;
	}
	for (int i = this->DCount - 1; i >= this->currentPos; i--)
	{
		this->arr[i + 1] = this->arr[i];
		Eff++;
	}

	this->arr[currentPos] = _rec;
	Eff++;
	this->DCount++;
	return true;
}

inline bool TSortTable::Delete(TKey _key)
{
	if (!Find(_key))
	{
		return false;
	}
	for (int i = this->currentPos; i < this->DCount - 1; i++)
	{
		this->arr[i] = this->arr[i + 1];
		Eff++;
	}
	this->DCount--;
	return true;
}
