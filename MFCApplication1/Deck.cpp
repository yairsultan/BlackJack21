#include "pch.h"
#include "Deck.h"
#include <random>
using namespace std;
Deck::Deck()
{
	populate();
}

Deck::~Deck()
{
	mCardArray.RemoveAll();
}

void Deck::populate()
{
	CString tempStr;
	CString pathStr;
	Card *tempCard;
	for (int i = 1; i <= 13; i++)
	{
		
		for (int j = 0; j < 4; j++)  // club = 0, diamon = 1, spade = 2, heart = 3
		{
			pathStr = CString(("objects\\"));
			switch (j)
			{
			case 0:
				pathStr.Append(_T("c"));

				break;
			case 1:
				pathStr.Append(_T("d"));
				break;
			case 2:
				pathStr.Append(_T("s"));
				break;
			case 3:
				pathStr.Append(_T("h"));
				break;
			}
			if (i > 9)
			{
				tempStr.Format(_T("%d"), i);
			}
			else {
				pathStr.Append(_T("0"));
				tempStr.Format(_T("%d"), i);
			}
			pathStr.Append(tempStr);
			pathStr.Append(_T(".bmp"));
			tempCard = new Card(i, pathStr,(i - 1) * 4 + j );
			mCardArray.Add(tempCard);
		}
	}
}

void Deck::deal(Hand & hand)
{
	CMFCApplication1Dlg dlg;
	thread_local static random_device rd;
	thread_local static mt19937 gen(rd());
	uniform_int_distribution<> dis(0, 7918);
	int temp = ( dis(gen) * (this->mCardArray.GetSize() + 83)) % 52;
	TRACE("%d \n", temp);
	hand.addCard(this->mCardArray.GetAt(temp));
	mCardArray.GetAt(temp)->setShowsLeft(-1);
}
