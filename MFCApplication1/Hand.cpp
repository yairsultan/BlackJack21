#include "pch.h"
#include "Hand.h"


Hand::Hand()
{
	mCardsCount = 0;
	mTotalValue = 0;
	mNumOfAces = 0;
	mNonAceTotal = 0;
}

CTypedPtrArray<CObArray, Card*>& Hand::getCardArr()
{
	return mCardArray;
}

bool Hand::addCard(Card* iCard)
{
	mCardArray.Add(iCard);
	if (iCard->getValue() == 1)
	{
		mNumOfAces++;
	}
	setTotal();
	if (getTotal() < 21)
		return true;
	else
		return false;
}

void Hand::clear()
{
	mCardsCount = 0;
	mTotalValue = 0;
	mNumOfAces = 0;
	mNonAceTotal = 0;
	mCardArray.RemoveAll();
}

int Hand::getTotal() const
{
	return mTotalValue;
}

void Hand::setTotal()
{
	int aceValue;
	int addToValue = mCardArray[mCardArray.GetSize() - 1]->getValue();
	if (addToValue != 1)
	{
		mNonAceTotal += addToValue;
	}
	if (mNumOfAces)
	{
		if (mNonAceTotal + 11 + (mNumOfAces - 1) <= 21)
		{
			aceValue = 11 + (mNumOfAces - 1);
		}
		else
		{
			aceValue = mNumOfAces;
		}
	}
	else
	{
		aceValue = 0;
	}
	mTotalValue = mNonAceTotal + aceValue;
}

Hand* Hand::getHand() 
{
	return this;
}


