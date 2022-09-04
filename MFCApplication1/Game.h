#pragma once
#include "Player.h"
#include "House.h"
#include "Deck.h"

class Game : public CObject
{
private:
	GenericPlayer *mPlayer;
	GenericPlayer *mHouse;
	Deck mDeck;
	int mBankTotalAmount;
	int mCurrentStage = 0;

public:
	Game();
	~Game();
	DECLARE_SERIAL(Game)
	void Serialize(CArchive& archive);
	void openFlop();
	void play();
	GenericPlayer* getPlayer();
	GenericPlayer* getHouse();
	Deck & getDeck();
	void updateBankTotalValue();
	void showAllCards();
	void newRound();
	void addBankTotalAmount(int iAmount);
	int getBankTotalAmount();
	void updateGame();
	void setCurrentStage(int iStage);
	int getCurrentStage();
	int playerHandArr[6];
	int houseHandArr[6];
};

