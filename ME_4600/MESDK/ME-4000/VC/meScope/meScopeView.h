// meScopeView.h : interface of the CMeScopeView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MESCOPEVIEW_H__BF0F90E6_7F9A_4A3D_AE53_F96A84B4BEF0__INCLUDED_)
#define AFX_MESCOPEVIEW_H__BF0F90E6_7F9A_4A3D_AE53_F96A84B4BEF0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

const COLORREF channel_colors[4] = { RGB(255, 0, 0), RGB(0, 255, 0), RGB(0, 0, 255), RGB(255, 255, 0) };

struct SChannel
{
	BOOL	m_bChannelActive;
	
	int		m_iChannelNumber;
	
	int		m_iRange;
	
	double	m_dMin;
	double	m_dMax;
};
	
struct SDisplayChannel
{
	int			m_iRange;
	
	double		m_dMin;
	double		m_dMax;

	COLORREF	m_crColor;

	double		m_dYFactor;

	double		m_dYConstant;

	// Internal variables for infinite acquisition
	
	int			m_iYLastPixel;
};
	
class CMeScopeView : public CView
{
protected: // create from serialization only
	CMeScopeView();
	DECLARE_DYNCREATE(CMeScopeView)

// Attributes
public:
	CMeScopeDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMeScopeView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMeScopeView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CMeScopeView)
	afx_msg void OnChannelSelection();
	afx_msg void OnStartAcquisition();
	afx_msg void OnUpdateStartAcquisition(CCmdUI* pCmdUI);
	afx_msg void OnStopAcquisition();
	afx_msg void OnUpdateStopAcquisition(CCmdUI* pCmdUI);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:

	// User settings
	
	BOOL			m_bMultiplexing;	
	
	SChannel		m_arrChannels[4];

	BOOL			m_bSampleAndHold ;
	unsigned int	m_uiCount;
	
	unsigned int	m_uiSampleRate;
	
	int				m_iAcqDuration;
	
	unsigned int	m_uiWindowWidthValues;
	
	double			m_dWindowWidthSecs;
	
	int				m_iAcqMode;

	int				m_iExtTriggerMode;
	
	int				m_iExtTriggerEdge;
	
	int				m_iSingleDiffMode;

	int				m_iBoardNumber;

	// Internal variables
	
	CRect			m_rectPlot;
	
	BOOL			m_bAcquisitionRunning;

	short*			m_psDataBuffer;

	unsigned int	m_uiMaxBufferSize;

	unsigned int	m_uiCurrentBufferSize;

	unsigned char	m_ucChanList[4];

	unsigned int	m_uiNoOfDisplayChannels;
	
	SDisplayChannel	m_arrDisplayChannels[4];

	double			m_dXIncrement;

	// Internal variables for infinite acquisition

	BOOL			m_bFirstDraw;
	
	double			m_dXLastPixel;
	
	int				m_iXLastPixel;

	static void _stdcall FiniteAcquisitionProc(short* psValues, 
												unsigned int uiNumberOfValues, 
														void* pCallbackContext,
																int iLastError);

	static void _stdcall InfiniteAcquisitionProc(short* psValues, 
													unsigned int uiNumberOfValues, 
															void* pCallbackContext,
																	int iLastError);

	void CalculateYFactorsAndConstants(void);
};

#ifndef _DEBUG  // debug version in meScopeView.cpp
inline CMeScopeDoc* CMeScopeView::GetDocument()
   { return (CMeScopeDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MESCOPEVIEW_H__BF0F90E6_7F9A_4A3D_AE53_F96A84B4BEF0__INCLUDED_)
