#if !defined(AFX_PARAMETERS_H__3D6D144C_8F8E_401F_91EC_241546E1B57C__INCLUDED_)
#define AFX_PARAMETERS_H__3D6D144C_8F8E_401F_91EC_241546E1B57C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Parameters.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CParameters dialog

#include "ColourBox.h"

class CParameters : public CDialog
{
// Construction
public:
	CParameters(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CParameters)
	enum { IDD = IDD_DIALOG_PARAMETERS };
	CSpinButtonCtrl	m_spinWindowWidthValues;
	CSpinButtonCtrl	m_spinSampleRate;
	CSpinButtonCtrl	m_spinCount;
	int		m_iChanNumber1;
	int		m_iChanNumber2;
	int		m_iChanNumber3;
	int		m_iChanNumber4;
	BOOL	m_bChan1;
	BOOL	m_bChan2;
	BOOL	m_bChan3;
	BOOL	m_bChan4;
	BOOL	m_bSampleAndHold;
	UINT	m_uiCount;
	UINT	m_uiSampleRate;
	float	m_fMax1;
	float	m_fMax2;
	float	m_fMax3;
	float	m_fMax4;
	float	m_fMin1;
	float	m_fMin2;
	float	m_fMin3;
	float	m_fMin4;
	int		m_iAcqDuration;
	int		m_iAcqMode;
	int		m_iTriggerMode;
	int		m_iTriggerEdge;
	int		m_iSingleDiffMode;
	int		m_iRange1;
	int		m_iRange2;
	int		m_iRange3;
	int		m_iRange4;
	float	m_fWindowWidthSecs;
	UINT	m_uiWindowWidthValues;
	int		m_iNormalAnalog;
	//}}AFX_DATA

	CColourBox m_cbChannel1;

	CColourBox m_cbChannel2;

	CColourBox m_cbChannel3;

	CColourBox m_cbChannel4;


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CParameters)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CParameters)
	virtual BOOL OnInitDialog();
	afx_msg void OnCheck1();
	afx_msg void OnCheck2();
	afx_msg void OnCheck3();
	afx_msg void OnCheck4();
	afx_msg void EnableChanListCount();
	afx_msg void DisableChanListCount();
	afx_msg void OnRadioContSw();
	afx_msg void OnRadioContEt();
	afx_msg void OnRadioContEtValueOrChanList();
	afx_msg void OnRadioNormalAnalog();
	afx_msg void OnRadioAnalogMultiplexing();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PARAMETERS_H__3D6D144C_8F8E_401F_91EC_241546E1B57C__INCLUDED_)
