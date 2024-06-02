#pragma once
#include<string>
#include<iostream>

using namespace std;


typedef int TKey;
typedef string TVal;
constexpr auto MAX_SIZE = 999;

struct TRecord
{
	TKey key;     
	TVal val; 

	TRecord()
	{
		key = 0;
		val = "";
	}

	TRecord(TKey key, TVal _val)
	{
		this->key = key;
		this->val = _val;
	}

	TRecord& operator=(const TRecord& _rec)
	{
		key = _rec.key;
		val = _rec.val;
		return *this;
	}

	bool operator == (TRecord _rec)
	{
		if (this->val == _rec.val)
			return true;
		else
			return false;
	}

	void output() const
	{
		std::cout << "( " << key << "  " << val << " )" << std::endl;
	}

	bool operator != (const TRecord& _rec)
	{
		return !(*this == _rec);
	}

	void Print(ostream& os) const
	{ 
		os << key << " " << val; 
	}
};

class TTable
{
protected:
	int DCount;   
	int Eff;

public:
	TTable() { DCount = 0; Eff = 0; };
	virtual ~TTable() { };

	int GetDCount() const { return DCount; }
	int GetEff() const { return Eff; }
	void ClearEff() { Eff = 0; }

	bool IsEmpty() const { return DCount == 0; }
	virtual bool Find(TKey) = 0;
	virtual bool IsEnd() = 0;
	virtual bool Insert(TRecord record) = 0;
	virtual bool IsFull() const = 0;
	virtual void Reset() = 0;
	virtual bool Delete(TKey key) = 0; 
	virtual void GoNext() = 0;
	virtual TRecord GetCurrRecord() = 0;

	virtual void SetCurrRecord(TRecord record) = 0;   
	friend ostream& operator<<(ostream& os, TTable& _tab) {
		cout << "Table printing" << endl;
		for (_tab.Reset(); !_tab.IsEnd(); _tab.GoNext()) {
			os << " Key: " << _tab.GetCurrRecord().key << " Val: " << _tab.GetCurrRecord().val << endl;
			_tab.Eff++;
		}
		return os;
	}
};
