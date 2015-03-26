// ME9000DDlg.h : header file
//

#if !defined(AFX_ME9000DDLG_H__4DDEE63E_5FC1_4F86_8509_F56742FA595F__INCLUDED_)
#define AFX_ME9000DDLG_H__4DDEE63E_5FC1_4F86_8509_F56742FA595F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CME9000DDlg dialog

class CME9000DDlg : public CDialog
{
// Construction
public:
	CME9000DDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CME9000DDlg)
	enum { IDD = IDD_ME9000D_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CME9000DDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CME9000DDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnButtonDioOpen();
	afx_msg void OnButtonDioReset();
	afx_msg void OnButtonDioConfig();
	afx_msg void OnButtonDioGetBit();
	afx_msg void OnButtonDioSetBit();
	afx_msg void OnButtonDioGetByte();
	afx_msg void OnButtonDioSetByte();
	afx_msg void OnButtonDioOutput();
	afx_msg void OnButtonDioSetCallback();
	afx_msg void OnButtonDioGetIrqCount();
	afx_msg void OnButtonDioClose();
	afx_msg void OnButtonCntOpen();
	afx_msg void OnButtonCntReset();
	afx_msg void OnButtonCntConfig();
	afx_msg void OnButtonCntWrite();
	afx_msg void OnButtonCntStart();
	afx_msg void OnButtonCntRead();
	afx_msg void OnButtonCntStop();
	afx_msg void OnButtonCntGetIrqCount();
	afx_msg void OnButtonCntClose();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnSelchangeComboDioConfigDirection();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:

	unsigned long m_ulNumberOfDIOInterrupts;

	unsigned long m_ulNumberOfCntInterrupts;

	static void _stdcall CallbackDIOBeep(void* pDIOIrqContext);

	static void _stdcall CallbackDIODisplayIrqCount(void* pDIOIrqContext);

	static void _stdcall CallbackCntBeep(void* pDIOIrqContext);

	static void _stdcall CallbackCntDisplayIrqCount(void* pDIOIrqContext);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ME9000DDLG_H__4DDEE63E_5FC1_4F86_8509_F56742FA595F__INCLUDED_)
