#include "pch.h"
#include "GenericPlayer.h"

void GenericPlayer::push()
{
	CMFCApplication1Dlg dlg;
	CImage ViewImage;
	CBitmap ViewBitmap;
	ViewImage.Load(_T("objects\\push.jpg")); //welcome image background
	ViewBitmap.Attach(ViewImage.Detach());
	dlg.pResultControl->ShowWindow(SW_SHOW);
	dlg.pResultControl->SetBitmap((HBITMAP)ViewBitmap);
}

