#pragma once
#include "MFCApplication1Dlg.h"

class Hand : public CObject
{
protected:
	CTypedPtrArray<CObArray, Card*> mCardArray;
	int mCardsCount;
	int mTotalValue;
	int mNonAceTotal;
	int mNumOfAces;

public:
	Hand();
	CTypedPtrArray<CObArray, Card*>& getCardArr();
	bool addCard(Card* iCard);
	void clear();
	int getTotal() const;
	void setTotal() ;
	Hand* getHand() ;
};

