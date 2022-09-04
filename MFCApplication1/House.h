#pragma once
#include "GenericPlayer.h"
class House :
	public GenericPlayer
{
private:
	CTypedPtrArray<CObArray, CStatic *> pDealerCardControlArr;
	
public:
	House() {};
	void updateTotalValue();
	void showCard();
	virtual bool isHitting() const;
	void win();
	void flipFirstCard();
};

