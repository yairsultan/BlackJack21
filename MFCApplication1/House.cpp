#include "pch.h"
#include "House.h"

void House::updateTotalValue()
{
	CMFCApplication1Dlg dlg;
	CString temp;
	temp.Format(_T("%d"), getHand()->getTotal());
	dlg.houseTotalEditControl.SetWindowTextW(temp);
}

void House::showCard()
{
	CMFCApplication1Dlg dlg;
	bool isFirst = !(mCardArray.GetSize() == 1);
	HBITMAP tempBITMAP = getCardArr().GetAt(mCardArray.GetSize() - 1)->getCardImage(isFirst);
	dlg.pDealerCardControlArr.GetAt(mCardArray.GetSize() - 1)->ShowWindow(SW_SHOW);
	dlg.pDealerCardControlArr.GetAt(mCardArray.GetSize() - 1)->SetBitmap(tempBITMAP);
}

bool House::isHitting() const
{
	return (this->getTotal() < 17);
}

void House::win()
{
	CMFCApplication1Dlg dlg;
	CImage ViewImage;
	CBitmap ViewBitmap;
	ViewImage.Load(_T("objects\\lose.jpg")); //welcome image background
	ViewBitmap.Attach(ViewImage.Detach());
	dlg.pResultControl->ShowWindow(SW_SHOW);
	dlg.pResultControl->SetBitmap((HBITMAP)ViewBitmap);
	flipFirstCard();
}

void House::flipFirstCard()
{
	CMFCApplication1Dlg dlg;
	dlg.pDealerCardControlArr.GetAt(0)->SetBitmap(mCardArray.GetAt(0)->getCardImage());
	updateTotalValue();
}
