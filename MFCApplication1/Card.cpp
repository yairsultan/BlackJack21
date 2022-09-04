#include "pch.h"
#include "Card.h"
#include <string.h>
#include <CString>
#include <atlimage.h>
#include "MFCApplication1Dlg.h"


Card::Card(int iNum, CString iStr, int iIndex)
{
	this->mValue = (iNum > 10 ? 10 : iNum);
	mShowsLeft = 7;
	setCardImage(iStr);
	mIndex = iIndex;
}

void Card::setCardImage(CString iStr)
{
	mCardImage = (HBITMAP)LoadImage(NULL, iStr, IMAGE_BITMAP, 71, 96, LR_LOADFROMFILE);
	iStr = CString(_T("objects\\back.bmp"));
	mFlipedImage = (HBITMAP)LoadImage(NULL, iStr, IMAGE_BITMAP, 71, 96, LR_LOADFROMFILE);
}

int Card::getValue() const
{
	return mValue;
}

HBITMAP Card::getCardImage(bool iFaceUp)
{
	if(iFaceUp)
		return mCardImage;
	else
		return mFlipedImage;
}

int Card::getShowsLeft() const
{
	return mShowsLeft;
}

int Card::getIndex() const
{
	return mIndex;
}

void Card::setShowsLeft(int iDecrease)
{
	mShowsLeft += iDecrease;
	if (mShowsLeft < 0)
		mShowsLeft = 0;
		
}
