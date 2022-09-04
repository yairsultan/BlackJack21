#include "pch.h"
#include "Player.h"
#include "MFCApplication1Dlg.h"

Player::Player()
{
	mHitting = false;
}

void Player::updateTotalValue()
{
	CMFCApplication1Dlg dlg;
	CString temp;
	temp.Format(_T("%d"), getHand()->getTotal());
	dlg.playerTotalEditControl.SetWindowTextW(temp);
}

void Player::setHitting(bool iHitting) 
{
	mHitting = iHitting;
}

bool Player::isHitting() const
{
	return mHitting;
}

void Player::win() 
{
	CMFCApplication1Dlg dlg;
	CImage ViewImage;
	CBitmap ViewBitmap;
	ViewImage.Load(_T("objects\\win.jpg")); //welcome image background
	ViewBitmap.Attach(ViewImage.Detach());
	dlg.pResultControl->ShowWindow(SW_SHOW);
	dlg.pResultControl->SetBitmap((HBITMAP)ViewBitmap);
}

void Player::showCard()
{
	CMFCApplication1Dlg dlg;
	updateTotalValue();
	dlg.pPlayerCardControlArr.GetAt(mCardArray.GetSize() - 1)->ShowWindow(SW_SHOW);
	HBITMAP tempBITMAP = getCardArr().GetAt(mCardArray.GetSize() - 1)->getCardImage();
	dlg.pPlayerCardControlArr.GetAt(mCardArray.GetSize() - 1)->SetBitmap(tempBITMAP);
}
