#pragma once
class Card : public CObject
{
private:
	int mValue;
	HBITMAP mCardImage;
	HBITMAP mFlipedImage;
	int mType; // club = 0, diamon = 1, spade = 2, heart = 3
	int mShowsLeft;
	int mIndex;

public:
	Card() {};
	Card(int iNum ,CString iStr, int mIndex);
	void setCardImage(CString iStr);
	int getValue() const ;
	HBITMAP getCardImage(bool iFaceUp = true);
	int getShowsLeft() const;
	int getIndex() const;
	void setShowsLeft(int iDecrease);
};

