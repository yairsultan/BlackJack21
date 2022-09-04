#pragma once
#include "Hand.h"
class GenericPlayer :
	public Hand
{
public:
	GenericPlayer() {};
	virtual void flipFirstCard() {};
	virtual void updateTotalValue() = 0;
	virtual void setHitting(bool) {};
	virtual bool isHitting() const = 0;
	virtual void showCard() = 0;
	virtual void win() = 0;
	void push();
};

