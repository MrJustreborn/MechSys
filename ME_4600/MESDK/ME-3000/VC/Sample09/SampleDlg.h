// sampleDlg.h : header file
//

#if !defined(AFX_TESTAICONTINUOUSDLG_H__062171B2_1F41_4C5D_8926_7975FA2943B1__INCLUDED_)
#define AFX_TESTAICONTINUOUSDLG_H__062171B2_1F41_4C5D_8926_7975FA2943B1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CTestAIContinuousDlg dialog

class CTestAIContinuousDlg : public CDialog
{
// Construction
public:
	CTestAIContinuousDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CTestAIContinuousDlg)
	enum { IDD = IDD_TESTAICONTINUOUS_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTestAIContinuousDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CTestAIContinuousDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnStart();
	afx_msg void OnStop();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:

	int m_iNumberOfChannels;
	
	double m_dSampleRate; // Hz SINGLE channel sampling rate
	
	double m_dWindowWidth;	// Seconds
	
	double m_dCurrentXPix;

	double m_dXPixIncrement;
	
	double m_dYPixelFactor;
	
	int m_iLastXPixel;

	int m_iLastYPixel[32];
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TESTAICONTINUOUSDLG_H__062171B2_1F41_4C5D_8926_7975FA2943B1__INCLUDED_)
