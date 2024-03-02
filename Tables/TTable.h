#pragma once
#include <iostream>
#include <string.h>
#include <string>


using namespace std;

typedef int TKey;
typedef string TVal;
struct TRecord {
	TKey key;
	TVal val;
};

class TTable
{
protected:
	int DataCount;
	int Eff;
public:
	virtual ~TTable() {};
	//GetCount();
	//GetEff();
	//ClearEff();
	//Empty();
	virtual bool Full() = 0;
	virtual bool Find(TKey key) = 0;		//find element
	virtual bool InsRecord(TRecord rec) = 0;
	virtual void DelRecord(TKey key);
	virtual void Reset() = 0;
	virtual void GoNext() = 0;
	virtual bool IsEnd() = 0;

	friend ostream& operator << (ostream& os, TTable& T) {
		for (T.Reset(); !T.IsEnd(); T.GoNext()) {
			os << T.GetKey() << T.GetValue() << end;
		}
		return os;
	}

};