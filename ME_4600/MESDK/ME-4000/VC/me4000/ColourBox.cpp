// ColourBox.cpp : implementation file
//

#include "stdafx.h"
#include "meScope.h"
#include "ColourBox.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CColourBox

CColourBox::CColourBox()
{
}

CColourBox::~CColourBox()
{
}


BEGIN_MESSAGE_MAP(CColourBox, CStatic)
	//{{AFX_MSG_MAP(CColourBox)
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CColourBox message handlers

void CColourBox::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	// TODO: Add your message handler code here

	CRect rect_win;

	GetClientRect(&rect_win);
	
	dc.FillSolidRect(&rect_win, m_crBackground);

	CPen colour_pen(PS_SOLID, 1, m_crForeground);
	
	CPen* p_old_pen = (CPen*)dc.SelectObject(&colour_pen);

	dc.MoveTo(rect_win.left, (rect_win.top + rect_win.bottom) / 2);
	
	dc.LineTo(rect_win.right, (rect_win.top + rect_win.bottom) / 2);
	
	dc.SelectObject(p_old_pen);


	
	// Do not call CStatic::OnPaint() for painting messages
}
