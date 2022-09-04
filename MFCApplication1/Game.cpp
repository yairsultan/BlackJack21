#include "pch.h"
#include "Game.h"
#include <windows.h> 

IMPLEMENT_SERIAL(Game, CObject, 1)

void Game::Serialize(CArchive & archive)
{
	CObject::Serialize(archive);
	if (archive.IsStoring())
		archive << mCurrentStage << mBankTotalAmount << playerHandArr[0] << playerHandArr[1] << playerHandArr[2] <<
		playerHandArr[3] << playerHandArr[4] << playerHandArr[5] << houseHandArr[0] << houseHandArr[1]
		<< houseHandArr[2] << houseHandArr[3] << houseHandArr[4] << houseHandArr[5];
	else
		archive >> mCurrentStage >> mBankTotalAmount >> playerHandArr[0] >> playerHandArr[1] >> playerHandArr[2] >>
		playerHandArr[3] >> playerHandArr[4] >> playerHandArr[5] >> houseHandArr[0] >> houseHandArr[1]
		>> houseHandArr[2] >> houseHandArr[3] >> houseHandArr[4] >> houseHandArr[5];
}

Game::Game()
{
	mPlayer = new Player();
	mHouse = new House();
	mBankTotalAmount = 850;
	mCurrentStage = 0;
}

Game::~Game()
{
	delete mPlayer;
	delete mHouse;
}

void Game::openFlop()
{
	static CMFCApplication1Dlg dlg;
	for (int i = 0; i < 2; i++)
	{
		mDeck.deal(*(mPlayer->getHand()));
		mPlayer->showCard();
		Sleep(400);

		mDeck.deal(*(mHouse->getHand()));
		mHouse->showCard();
		Sleep(400);
	}
	mPlayer->updateTotalValue();
}

void Game::play()
{
	openFlop(); //Open 2 cards for each player and dealer
	mCurrentStage = 0;
}

GenericPlayer * Game::getPlayer()
{
	return mPlayer;
}

GenericPlayer * Game::getHouse()
{
	return mHouse;
}

Deck & Game::getDeck()
{
	return mDeck;
}

void Game::updateBankTotalValue()
{
	CMFCApplication1Dlg dlg;
	CString temp;
	temp.Format(_T("%d"), mBankTotalAmount);
	dlg.bankEditVariable.SetWindowTextW(temp);
}

void Game::showAllCards()
{
	CMFCApplication1Dlg dlg;
	Hand *playerHand = getPlayer()->getHand();
	Hand *houseHand = getHouse()->getHand();
	for (int i = 0; i < (*playerHand).getCardArr().GetSize(); i++)
	{
		dlg.pPlayerCardControlArr.GetAt(i)->ShowWindow(SW_SHOW);
		HBITMAP tempBITMAP = (*playerHand).getCardArr().GetAt(i)->getCardImage();
		dlg.pPlayerCardControlArr.GetAt(i)->SetBitmap(tempBITMAP);
	}
	for (int i = 0; i < (*houseHand).getCardArr().GetSize(); i++)
	{
		HBITMAP tempBITMAP = (*houseHand).getCardArr().GetAt(i)->getCardImage(i > 0);
		dlg.pDealerCardControlArr.GetAt(i)->ShowWindow(SW_SHOW);
		dlg.pDealerCardControlArr.GetAt(i)->SetBitmap(tempBITMAP);
	}
}

void Game::newRound()
{
	CMFCApplication1Dlg dlg;
	dlg.pResultControl->ShowWindow(SW_HIDE);
	mPlayer->getHand()->clear();
	mHouse->getHand()->clear(); 
	for (int i = 0; i < dlg.pDealerCardControlArr.GetSize(); i++)
	{
		dlg.pDealerCardControlArr.GetAt(i)->ShowWindow(SW_HIDE);
		dlg.pPlayerCardControlArr.GetAt(i)->ShowWindow(SW_HIDE);
	}
	dlg.pResultControl->ShowWindow(SW_HIDE);
}

void Game::addBankTotalAmount(int iAmount)
{
	mBankTotalAmount += iAmount;
}

int Game::getBankTotalAmount()
{
	return mBankTotalAmount;
}

void Game::updateGame()
{
	CMFCApplication1Dlg dlg;
	if (playerHandArr[0] != -1)
	{
		for (int i = 0; i < 6; i++)
		{
			if (playerHandArr[i] > -1)
			{
				mPlayer->getHand()->addCard(mDeck.getCardArr().GetAt(playerHandArr[i]));
				mPlayer->showCard();
			}
			else
				break;
		}
		for (int i = 0; i < 6; i++)
		{
			if (houseHandArr[i] > -1)
			{
				mHouse->getHand()->addCard(mDeck.getCardArr().GetAt(houseHandArr[i]));
				mHouse->showCard();
			}
			else
				break;
		}
		if (mCurrentStage > 0)
		{

			dlg.dealVariable.ShowWindow(SW_SHOW);
			dlg.hitMeVariable.ShowWindow(SW_HIDE);
			dlg.standVariable.ShowWindow(SW_HIDE);
			mHouse->flipFirstCard();
			if (mCurrentStage == 1)
				mPlayer->win();
			else if (mCurrentStage == 2)
				mHouse->win();
			else
				mPlayer->push();
		}
		else
		{
			dlg.dealVariable.ShowWindow(SW_HIDE);
			dlg.hitMeVariable.ShowWindow(SW_SHOW);
			dlg.standVariable.ShowWindow(SW_SHOW);
		}
		dlg.houseTotalEditControl.ShowWindow(SW_SHOW);
		dlg.playerTotalEditControl.ShowWindow(SW_SHOW);
	}
}

void Game::setCurrentStage(int iStage)
{
	mCurrentStage = iStage;
}

int Game::getCurrentStage()
{
	return mCurrentStage;
}
