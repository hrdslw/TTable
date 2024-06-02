#pragma once
#include<exception>
#include"TTable.h"



class TArrayTable :public TTable
{
protected:
	TRecord* arr;
	int size, currentPos;

public:
	TArrayTable(int _size = MAX_SIZE)
	{
		if (_size > MAX_SIZE)
		{
			throw  exception();
		}
		this->size = _size;
		arr = new TRecord[size];
		currentPos = 0;
	};
	TArrayTable(const TArrayTable& _tab)
	{
		DCount = _tab.DCount;
		Eff = _tab.Eff;
		size = _tab.size;
		arr = new TRecord[size];
		for (int i = 0; i < size; i++)
		{
			arr[i] = _tab.arr[i];
		}
		currentPos = _tab.currentPos;
	}
	~TArrayTable() { delete[] arr; }

	bool IsFull() const override { return DCount == size; }

	void GoNext() override { currentPos++; }
	void Reset() override { currentPos = 0; }
	bool IsEnd() override { return currentPos == DCount; }

	TRecord GetCurrRecord() override {
		return arr[currentPos];
	}
	void SetCurrRecord(TRecord _rec) override { arr[currentPos] = _rec; }
	virtual int GetSize() { return size; }
	virtual int GetCurrPos() { return currentPos; }
	virtual void SetCurrPos(int _curPos)
	{
		if (_curPos < size)
		{
			currentPos = _curPos;
		}
		else {
			throw exception();
		}
	}


	friend  ostream& operator<<( ostream& os, TArrayTable& _tab)
	{
		os << "Output:" <<  endl;
		 cout << "Key" << " " << "Value" <<  endl;
		for (_tab.Reset(); !_tab.IsEnd(); _tab.GoNext())
		{
			if (_tab.GetCurrRecord().key <= 9)
			{
				 cout << _tab.GetCurrRecord().key << "   " <<  left << _tab.GetCurrRecord().val <<  endl;
			}
			else if (_tab.GetCurrRecord().key >= 10 && _tab.GetCurrRecord().key <= 99)
			{
				 cout << _tab.GetCurrRecord().key << "  " <<  left << _tab.GetCurrRecord().key <<  endl;
			}
			else
			{
				 cout << _tab.GetCurrRecord().key << " " <<  left << _tab.GetCurrRecord().key <<  endl;
			}
		}
		return os;
	}
};


