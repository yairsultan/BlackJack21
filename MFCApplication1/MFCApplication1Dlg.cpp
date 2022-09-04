
// MFCApplication1Dlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "MFCApplication1.h"
#include "MFCApplication1Dlg.h"
#include "afxdialogex.h"
#include "Deck.h"
#include "Game.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CTypedPtrArray<CObArray, CStatic *> CMFCApplication1Dlg::pPlayerCardControlArr;
CTypedPtrArray<CObArray, CStatic *> CMFCApplication1Dlg::pDealerCardControlArr;
CStatic * CMFCApplication1Dlg::pWelcomeLogoControl;
CStatic * CMFCApplication1Dlg::pStartControl;
CStatic * CMFCApplication1Dlg::pResultControl;
CButton CMFCApplication1Dlg::hitMeVariable;
CButton CMFCApplication1Dlg::standVariable;
CButton CMFCApplication1Dlg::dealVariable;
CEdit CMFCApplication1Dlg::playerTotalEditControl;
CEdit CMFCApplication1Dlg::houseTotalEditControl;
CEdit CMFCApplication1Dlg::bankEditVariable;
int CMFCApplication1Dlg::isWelcomePage = 0;
int CMFCApplication1Dlg::playerCardsAmount = 0;
int CMFCApplication1Dlg::dealerCardsAmount = 0;
static Game myGame;
BOOL DoEvents();

// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

	// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


CMFCApplication1Dlg::CMFCApplication1Dlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCAPPLICATION1_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCApplication1Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_PLAYER_TOTAL_VALUE, playerTotalEditControl);
	DDX_Control(pDX, IDC_HOUSE_TOTAL_VALUE, houseTotalEditControl);
	DDX_Control(pDX, IDC_START_GAME, startGame);
	DDX_Control(pDX, IDC_HIT_ME_BTN, hitMeVariable);
	DDX_Control(pDX, IDC_STAND_BTN, standVariable);
	DDX_Control(pDX, IDC_DEAL, dealVariable);
	DDX_Control(pDX, IDC_RESULT, resultFieldVariable);
	DDX_Control(pDX, IDC_BANK_TOTAL_AMOUNT, bankTotalAmountVariable);
	DDX_Control(pDX, IDC_BANK_EDIT_CONTROL, bankEditVariable);
	DDX_Control(pDX, IDC_SAVE_BTN, saveVariable);
	DDX_Control(pDX, IDC_UPLOAD_BTN, uploadGameVariable);
}

BEGIN_MESSAGE_MAP(CMFCApplication1Dlg, CDialogEx)
	ON_WM_CTLCOLOR()
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_STAND_BTN, &CMFCApplication1Dlg::OnBnClickedStandBtn)
	ON_BN_CLICKED(IDC_HIT_ME_BTN, &CMFCApplication1Dlg::OnBnClickedHitMeBtn)
	ON_BN_CLICKED(IDC_START_GAME, &CMFCApplication1Dlg::OnBnClickedStartGame)
	ON_BN_CLICKED(IDC_DEAL, &CMFCApplication1Dlg::OnBnClickedDeal)
	ON_BN_CLICKED(IDC_UPLOAD_BTN, &CMFCApplication1Dlg::OnBnClickedUploadBtn)
	ON_BN_CLICKED(IDC_SAVE_BTN, &CMFCApplication1Dlg::OnBnClickedSaveBtn)
END_MESSAGE_MAP()


// CMFCApplication1Dlg message handlers

BOOL CMFCApplication1Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	pPlayerCardControlArr.Add((CStatic *)GetDlgItem(IDC_PICTURE_P1));
	pPlayerCardControlArr.Add((CStatic *)GetDlgItem(IDC_PICTURE_P2));
	pPlayerCardControlArr.Add((CStatic *)GetDlgItem(IDC_PICTURE_P3));
	pPlayerCardControlArr.Add((CStatic *)GetDlgItem(IDC_PICTURE_P4));
	pPlayerCardControlArr.Add((CStatic *)GetDlgItem(IDC_PICTURE_P5));
	pPlayerCardControlArr.Add((CStatic *)GetDlgItem(IDC_PICTURE_P6));
	pDealerCardControlArr.Add((CStatic *)GetDlgItem(IDC_PICTURE_D1));
	pDealerCardControlArr.Add((CStatic *)GetDlgItem(IDC_PICTURE_D2));
	pDealerCardControlArr.Add((CStatic *)GetDlgItem(IDC_PICTURE_D3));
	pDealerCardControlArr.Add((CStatic *)GetDlgItem(IDC_PICTURE_D4));
	pDealerCardControlArr.Add((CStatic *)GetDlgItem(IDC_PICTURE_D5));
	pDealerCardControlArr.Add((CStatic *)GetDlgItem(IDC_PICTURE_D6));
	pWelcomeLogoControl = (CStatic *)GetDlgItem(IDC_WELCOME_LOGO);
	pResultControl = (CStatic *)GetDlgItem(IDC_RESULT);
	pStartControl = (CStatic *)GetDlgItem(IDC_START_GAME);

	m_BackGroudbrush.CreateSolidBrush(RGB(42, 124, 53));

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CMFCApplication1Dlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CMFCApplication1Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		if (isWelcomePage == 0)
		{
			CImage ViewImage;
			CBitmap ViewBitmap;
			ViewImage.Load(_T("objects\\welcome11.jpg")); //welcome image background
			ViewBitmap.Attach(ViewImage.Detach());
			pWelcomeLogoControl->ShowWindow(SW_SHOW);
			uploadGameVariable.ShowWindow(SW_SHOW);
			pWelcomeLogoControl->SetBitmap((HBITMAP)ViewBitmap);
			//pStartControl->SetBitmap((HBITMAP)ViewBitmap);
		}
		else if (isWelcomePage == 1)
		{
			pWelcomeLogoControl->ShowWindow(SW_HIDE);
			uploadGameVariable.ShowWindow(SW_HIDE);
			CPaintDC dc(this);
			COLORREF green = RGB(15, 92, 43); //dialog background color
			CPen pen(PS_DASH, 5, green);
			CPen* old = dc.SelectObject(&pen);
			CBrush brush(green);
			CBrush* oldb = dc.SelectObject(&brush);
			dc.Rectangle(0, 0, 1500, 1500);
			dc.SelectObject(old);
			dc.SelectObject(brush);
		}
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CMFCApplication1Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


HBITMAP CMFCApplication1Dlg::ScaleBitmapInt(HBITMAP hBitmap, WORD wNewWidth, WORD wNewHeight)
{
	// Create a memory DC compatible with the display
	CDC sourceDC, destDC;
	sourceDC.CreateCompatibleDC(NULL);
	destDC.CreateCompatibleDC(NULL);

	// Get logical coordinates
	BITMAP bm;
	::GetObject(hBitmap, sizeof(bm), &bm);

	// Create a bitmap to hold the result
	HBITMAP hbmResult = ::CreateCompatibleBitmap(CClientDC(NULL),
		wNewWidth, wNewHeight);

	// Select bitmaps into the DCs
	HBITMAP hbmOldSource = (HBITMAP)::SelectObject(sourceDC.m_hDC, hBitmap);
	HBITMAP hbmOldDest = (HBITMAP)::SelectObject(destDC.m_hDC, hbmResult);



	destDC.StretchBlt(0, 0, wNewWidth, wNewHeight, &sourceDC,
		0, 0, bm.bmWidth, bm.bmHeight, SRCCOPY);

	// Reselect the old bitmaps
	::SelectObject(sourceDC.m_hDC, hbmOldSource);
	::SelectObject(destDC.m_hDC, hbmOldDest);

	return hbmResult;
}

void CMFCApplication1Dlg::OnBnClickedStandBtn()
{
	myGame.getPlayer()->setHitting(false);
	myGame.getHouse()->updateTotalValue();
	myGame.getHouse()->flipFirstCard();
	DoEvents();
	Sleep(1500);
	while (myGame.getHouse()->getTotal() < 17)
	{
		myGame.getDeck().deal(*(myGame.getHouse()->getHand()));
		myGame.getHouse()->showCard();
		myGame.getHouse()->updateTotalValue();
		DoEvents();
		Sleep(1500);
	}
	if (myGame.getPlayer()->getTotal() == myGame.getHouse()->getTotal())
	{
		myGame.getPlayer()->push();
		myGame.setCurrentStage(3);
		myGame.addBankTotalAmount(100);
		myGame.updateBankTotalValue();
	}
	else if (myGame.getHouse()->getTotal() > 21)
	{
		myGame.getPlayer()->win();
		myGame.setCurrentStage(1);
		myGame.addBankTotalAmount(200);
		myGame.updateBankTotalValue();
	}
	else if (myGame.getHouse()->getTotal() < myGame.getPlayer()->getTotal())
	{
		myGame.getPlayer()->win();
		myGame.setCurrentStage(1);
		myGame.addBankTotalAmount(200);
		myGame.updateBankTotalValue();
	}
	else
	{
		myGame.getHouse()->win();
		myGame.setCurrentStage(2);
	}
	dealVariable.ShowWindow(SW_SHOW);
	hitMeVariable.ShowWindow(SW_HIDE);
	standVariable.ShowWindow(SW_HIDE);
	pResultControl->SetFocus();

}



void CMFCApplication1Dlg::OnBnClickedHitMeBtn()
{
	if (myGame.getPlayer()->getTotal() < 21) 
	{
		myGame.getDeck().deal(*(myGame.getPlayer()->getHand()));
		myGame.getPlayer()->showCard();
		Sleep(400);
	}
	if (myGame.getPlayer()->getTotal() == 21)
	{
		dealVariable.ShowWindow(SW_SHOW);
		hitMeVariable.ShowWindow(SW_HIDE);
		standVariable.ShowWindow(SW_HIDE);
		myGame.getPlayer()->win();
		myGame.setCurrentStage(1);
		myGame.addBankTotalAmount(200);
		myGame.updateBankTotalValue();
	}
	else if (myGame.getPlayer()->getTotal() > 21)
	{
		dealVariable.ShowWindow(SW_SHOW);
		hitMeVariable.ShowWindow(SW_HIDE);
		standVariable.ShowWindow(SW_HIDE);
		myGame.getHouse()->win();
		myGame.setCurrentStage(2);
	}
	pResultControl->SetFocus();

}

void CMFCApplication1Dlg::OnBnClickedStartGame()
{
	isWelcomePage = 1;
	startGame.ShowWindow(SW_HIDE);
	dealVariable.ShowWindow(SW_SHOW);
	myGame.updateBankTotalValue();
	bankEditVariable.ShowWindow(SW_SHOW);
	bankTotalAmountVariable.ShowWindow(SW_SHOW);
	saveVariable.ShowWindow(SW_SHOW);
}

void CMFCApplication1Dlg::OnBnClickedDeal()
{
	playerTotalEditControl.SetWindowTextW(_T(""));
	houseTotalEditControl.SetWindowTextW(_T(""));
	myGame.addBankTotalAmount(-100);
	myGame.updateBankTotalValue();
	pResultControl->SetFocus();
	myGame.newRound();
	DoEvents();
	myGame.play();
	if (myGame.getPlayer()->getTotal() == 21)
	{
		myGame.getPlayer()->win();
		myGame.setCurrentStage(1);
		myGame.addBankTotalAmount(250);
		myGame.getHouse()->flipFirstCard();
	}
	else
	{
		dealVariable.ShowWindow(SW_HIDE);
		hitMeVariable.ShowWindow(SW_SHOW);
		standVariable.ShowWindow(SW_SHOW);
	}
	houseTotalEditControl.ShowWindow(SW_SHOW);
	playerTotalEditControl.ShowWindow(SW_SHOW);
}

BOOL DoEvents()
{
	MSG msg;
	while (::PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
	{
		if (msg.message == WM_QUIT)
		{
			return FALSE;
		}
		if (!AfxGetApp()->PreTranslateMessage(&msg))
		{
			::TranslateMessage(&msg);
			::DispatchMessage(&msg);
		}
	}
	return TRUE;
}


void CMFCApplication1Dlg::OnBnClickedUploadBtn()
{
	CFile myFile;
	myFile.Open(_T("CArchive_game1.ser"), CFile::modeRead);
	CArchive archive(&myFile, CArchive::load);
	myGame.Serialize(archive);
	OnBnClickedStartGame();
	OnPaint();
	myGame.updateGame();
}


void CMFCApplication1Dlg::OnBnClickedSaveBtn()
{
	int temp, size = myGame.getPlayer()->getCardArr().GetSize();
	for (int i = 0; i < 6; i++)
	{
		if (i < size)
		{
			temp = myGame.getPlayer()->getCardArr().GetAt(i)->getIndex();
			myGame.playerHandArr[i] = (temp);
		}
		else
		{
			myGame.playerHandArr[i] = -1;
		}
	}
	size = myGame.getHouse()->getCardArr().GetSize();
	for (int i = 0; i < 6; i++)
	{
		if (i < size)
		{
			temp = myGame.getHouse()->getCardArr().GetAt(i)->getIndex();
			myGame.houseHandArr[i] = (temp);
		}
		else
		{
			myGame.houseHandArr[i] = -1;
		}
	}
	CFile myFile;
	myFile.Open(_T("CArchive_game1.ser"), CFile::modeCreate | CFile::modeWrite);
	CArchive archive(&myFile, CArchive::store);
	myGame.Serialize(archive);
	CDialogEx::OnCancel();
}
