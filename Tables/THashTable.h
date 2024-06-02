#pragma once
#include "TTable.h"
class THashTable : public TTable
{
protected:
	virtual int HashFunc(TKey _key)
	{
		int HashVal = _key;
		return HashVal;
	}
};