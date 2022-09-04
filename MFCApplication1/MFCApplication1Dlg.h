
// MFCApplication1Dlg.h : header file
//

#pragma once
#include "Card.h"
#include "Hand.h"
#include <atlimage.h>

class CMFCApplication1Dlg : public CDialogEx
{
// Construction
public:
	CMFCApplication1Dlg(CWnd* pParent = nullptr);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCAPPLICATION1_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;
	CBrush m_BackGroudbrush;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()



public:
	static CTypedPtrArray<CObArray, CStatic *> pPlayerCardControlArr;
	static CTypedPtrArray<CObArray, CStatic *> pDealerCardControlArr;
	static CStatic * pWelcomeLogoControl;
	static CStatic * pStartControl;
	static CStatic * pResultControl;
	static CButton hitMeVariable;
	static CButton standVariable;
	static CButton dealVariable;
	static CEdit playerTotalEditControl;
	static CEdit houseTotalEditControl;
	static CEdit bankEditVariable;
	static int isWelcomePage;
	static int playerCardsAmount;
	static int dealerCardsAmount;
	HBITMAP ScaleBitmapInt(HBITMAP hBitmap, WORD wNewWidth, WORD wNewHeight);

	afx_msg void OnBnClickedStandBtn();
	afx_msg void OnBnClickedHitMeBtn();
	CButton startGame;
	afx_msg void OnBnClickedStartGame();
	afx_msg void OnBnClickedDeal();
	CStatic resultFieldVariable;
	CStatic bankTotalAmountVariable;
	CButton saveVariable;
	CButton uploadGameVariable;
	afx_msg void OnBnClickedUploadBtn();
	afx_msg void OnBnClickedSaveBtn();
};
