#pragma once
#include "Hand.h"

class Deck :public Hand
{
public :
	Deck();
	~Deck();
	void populate();
	void deal(Hand& hand);
};

