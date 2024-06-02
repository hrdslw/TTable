#pragma once
#include <fstream>
#include <iomanip>

#define _treetable_h
#include "TTable.h"
#include <stack>
#define  H_OK 0
#define  H_INC 1
#define  H_DEC -1
#define  BalRight 1
#define  BalOK 0
#define  BalLeft -1
using namespace std;



struct TTreeNode {
	TRecord rec;
	TTreeNode* pLeft, * pRight;
	int bal;
	TTreeNode(const TRecord& _rec)
	{
		rec = _rec;
		pLeft = nullptr;
		pRight = nullptr;
		bal = BalOK;
	}
};


class TTreeTable :public TTable
{
protected:

	TTreeNode* pRoot, * pCurr, * pPrev;
	std::stack<TTreeNode*> st;
	int countpos{}, lvl{};

public:


	TTreeTable()
	{
		pRoot = nullptr;
		pCurr = nullptr;
		pPrev = nullptr;
		//countpos = 0; lvl = 0;
	}
	~TTreeTable()
	{
		DeleteTreeTab(pRoot);
	}

	bool Find(TKey k) {
		pPrev = NULL;
		pCurr = pRoot;
		while (pCurr != NULL)
		{
			Eff++;
			if (pCurr->rec.key == k) break;
			else
			{
				pPrev = pCurr;
				if (pCurr->rec.key > k)
				{
					pCurr = pCurr->pLeft;
				}
				else pCurr = pCurr->pRight;

			}
		}
		if (pCurr != NULL) return true;
		else { pCurr = pPrev; return false; }
	}
	bool Insert(TRecord _rec)
	{

		if (Find(_rec.key))
		{
			return false;
		}
		else
		{
			TTreeNode* newNode = new TTreeNode(_rec);
			if (pRoot == nullptr)
			{
				pRoot = newNode;
			}
			else
			{
				if (pCurr->rec.key > _rec.key)
				{
					pCurr->pLeft = newNode;
				}
				else
				{
					pCurr->pRight = newNode;
				}
			}
			DCount++;
			return true;
		}
	}
	bool Delete(TKey key)
	{
		if (!Find(key)) return false;
		TTreeNode* pDel = pCurr;
		if (pCurr->pRight == nullptr)
		{
			if (pPrev == nullptr)  pRoot = pRoot->pLeft;
			else
			{
				if (pCurr->rec.key > pPrev->rec.key)
				{
					pPrev->pRight = pCurr->pLeft;
				}
				else
				{
					pPrev->pLeft = pCurr->pLeft;
				}
			}

		}
		else if (pCurr->pLeft == nullptr)
		{
			if (pPrev == nullptr)  pRoot = pRoot->pRight;
			else
			{
				if (pCurr->rec.key > pPrev->rec.key)
				{
					pPrev->pRight = pCurr->pRight;
				}
				else
				{
					pPrev->pLeft = pCurr->pRight;
				}
			}

		}
		else
		{
			TTreeNode* tmp = pCurr->pLeft;
			pPrev = pCurr;
			while (tmp->pRight != nullptr)
			{
				Eff++;
				pPrev = tmp;
				tmp = tmp->pRight;
			}
			pCurr->rec = tmp->rec;
			if (pPrev != pCurr)
			{
				pPrev->pRight = tmp->pLeft;
			}
			else
			{
				pPrev->pLeft = tmp->pLeft;
			}
			pDel = tmp;
		}
		Eff++;
		delete pDel;
		DCount--;
		return true;
	}
	void GoNext()
	{
		if (pCurr == nullptr || IsEnd())
		{
			throw std::exception();
		}
		if (!st.empty())
		{
			st.pop();
		}
		if (pCurr->pRight != nullptr)
		{
			pCurr = pCurr->pRight;
			while (pCurr != nullptr)
			{
				st.push(pCurr);
				pCurr = pCurr->pLeft;
			}
			pCurr = st.top();
		}
		else if (!st.empty())
		{
			pCurr = st.top();
		}
		countpos++;
	}

	void Reset()
	{
		TTreeNode* pNode = pCurr = pRoot;
		while (!st.empty()) st.pop();
		countpos = 0;
		while (pNode != NULL)
		{
			st.push(pNode);
			pCurr = pNode;
			pNode = pNode->pLeft;
		}
	}
	bool IsEnd()
	{
		return countpos == DCount;
	}

	void DeleteTreeTab(TTreeNode* pNode)
	{
		if (pNode != nullptr)
		{
			DeleteTreeTab(pNode->pLeft);
			DeleteTreeTab(pNode->pRight);
			delete pNode;
		}
	}
	void PrintTable(TTreeNode* pNode, ofstream& fout)
	{
		if (pNode != nullptr)
		{
			for (int i = 0; i < lvl; i++)
			{
				fout << " ";
			}
			fout << pNode->rec.key << std::endl;
			lvl++;
			PrintTable(pNode->pRight, fout);
			PrintTable(pNode->pLeft, fout);
			lvl--;
		}

	}
	void DrawConsole(void)
	{

		cout << "Table printing" << endl;
		PrintTableConsole(pRoot, cout);
	}
	void PrintTableConsole(TTreeNode* pNode, ostream& os)
	{
		if (pNode != nullptr)
		{
			for (int i = 0; i < lvl; i++)
			{
				os << " ";
			}
			os << pNode->rec.key << std::endl;
			lvl++;
			PrintTableConsole(pNode->pRight, os);
			PrintTableConsole(pNode->pLeft, os);
			lvl--;
		}

	}
	void Draw(void)
	{
		cout << "Table printing" << endl;
		ofstream fout("output.txt");
		PrintTable(pRoot, fout);

	}
	TTreeNode* GetpRoot()
	{
		return pRoot;
	}
	void SetCurrentRecord(TRecord record)
	{
		pCurr->rec.key = record.key;
		pCurr->rec.val = record.val;
	};
	bool IsFull() const { return false; };
	TRecord GetCurrentRecord() { return pCurr->rec; };
	TKey GetRightKey(TKey key)
	{
		Find(key);
		if (pCurr->pRight == nullptr)
		{
			return -1;
		}
		else
		{
			return pCurr->pRight->rec.key;
		}
	}
	TKey GetLeftKey(TKey key)
	{
		Find(key);
		if (pCurr->pLeft == nullptr)
		{
			return -1;
		}
		else
		{
			return pCurr->pLeft->rec.key;
		}
	}
	TKey GetRootKey()
	{
		return pRoot->rec.key;
	}
};

