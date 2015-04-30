// Parameters.cpp : implementation file
//

#include "stdafx.h"
#include "meScope.h"
#include "Parameters.h"

#include "meScopeDoc.h"

#include "meScopeView.h"

#include "resource.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CParameters dialog


CParameters::CParameters(CWnd* pParent /*=NULL*/)
	: CDialog(CParameters::IDD, pParent)
{
	//{{AFX_DATA_INIT(CParameters)
	m_iChanNumber1 = -1;
	m_iChanNumber2 = -1;
	m_iChanNumber3 = -1;
	m_iChanNumber4 = -1;
	m_bChan1 = FALSE;
	m_bChan2 = FALSE;
	m_bChan3 = FALSE;
	m_bChan4 = FALSE;
	m_bSampleAndHold = FALSE;
	m_uiCount = 0;
	m_uiSampleRate = 0;
	m_fMax1 = 0.0f;
	m_fMax2 = 0.0f;
	m_fMax3 = 0.0f;
	m_fMax4 = 0.0f;
	m_fMin1 = 0.0f;
	m_fMin2 = 0.0f;
	m_fMin3 = 0.0f;
	m_fMin4 = 0.0f;
	m_iAcqDuration = -1;
	m_iAcqMode = -1;
	m_iTriggerMode = -1;
	m_iTriggerEdge = -1;
	m_iSingleDiffMode = -1;
	m_iRange1 = -1;
	m_iRange2 = -1;
	m_iRange3 = -1;
	m_iRange4 = -1;
	m_fWindowWidthSecs = 0.0f;
	m_uiWindowWidthValues = 0;
	m_iNormalAnalog = -1;
	//}}AFX_DATA_INIT

	m_cbChannel1.m_crBackground = RGB(0, 0, 0);
	m_cbChannel1.m_crForeground = channel_colors[0];

	m_cbChannel2.m_crBackground = RGB(0, 0, 0);
	m_cbChannel2.m_crForeground = channel_colors[1];

	m_cbChannel3.m_crBackground = RGB(0, 0, 0);
	m_cbChannel3.m_crForeground = channel_colors[2];

	m_cbChannel4.m_crBackground = RGB(0, 0, 0);
	m_cbChannel4.m_crForeground = channel_colors[3];
}


void CParameters::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CParameters)
	DDX_Control(pDX, IDC_SPIN_WINDOW_WIDTH_VALUES, m_spinWindowWidthValues);
	DDX_Control(pDX, IDC_SPIN_SAMPLE_RATE, m_spinSampleRate);
	DDX_Control(pDX, IDC_SPIN_COUNT, m_spinCount);
	DDX_CBIndex(pDX, IDC_CHAN_NUMBER_1, m_iChanNumber1);
	DDX_CBIndex(pDX, IDC_CHAN_NUMBER_2, m_iChanNumber2);
	DDX_CBIndex(pDX, IDC_CHAN_NUMBER_3, m_iChanNumber3);
	DDX_CBIndex(pDX, IDC_CHAN_NUMBER_4, m_iChanNumber4);
	DDX_Check(pDX, IDC_CHECK_1, m_bChan1);
	DDX_Check(pDX, IDC_CHECK_2, m_bChan2);
	DDX_Check(pDX, IDC_CHECK_3, m_bChan3);
	DDX_Check(pDX, IDC_CHECK_4, m_bChan4);
	DDX_Check(pDX, IDC_CHECK_SAMPLE_AND_HOLD, m_bSampleAndHold);
	DDX_Text(pDX, IDC_EDIT_COUNT, m_uiCount);
	DDX_Text(pDX, IDC_EDIT_SAMPLE_RATE, m_uiSampleRate);
	DDX_Text(pDX, IDC_MAX_1, m_fMax1);
	DDX_Text(pDX, IDC_MAX_2, m_fMax2);
	DDX_Text(pDX, IDC_MAX_3, m_fMax3);
	DDX_Text(pDX, IDC_MAX_4, m_fMax4);
	DDX_Text(pDX, IDC_MIN_1, m_fMin1);
	DDX_Text(pDX, IDC_MIN_2, m_fMin2);
	DDX_Text(pDX, IDC_MIN_3, m_fMin3);
	DDX_Text(pDX, IDC_MIN_4, m_fMin4);
	DDX_Radio(pDX, IDC_RADIO_ACQ_INFINITE, m_iAcqDuration);
	DDX_Radio(pDX, IDC_RADIO_CONT_SW, m_iAcqMode);
	DDX_Radio(pDX, IDC_RADIO_DIGITAL, m_iTriggerMode);
	DDX_Radio(pDX, IDC_RADIO_HIGH_LOW, m_iTriggerEdge);
	DDX_Radio(pDX, IDC_RADIO_SINGLE_ENDED, m_iSingleDiffMode);
	DDX_CBIndex(pDX, IDC_RANGE_COMBO_1, m_iRange1);
	DDX_CBIndex(pDX, IDC_RANGE_COMBO_2, m_iRange2);
	DDX_CBIndex(pDX, IDC_RANGE_COMBO_3, m_iRange3);
	DDX_CBIndex(pDX, IDC_RANGE_COMBO_4, m_iRange4);
	DDX_Text(pDX, IDC_EDIT_WINDOW_WIDTH_SECS, m_fWindowWidthSecs);
	DDX_Text(pDX, IDC_EDIT_WINDOW_WIDTH_VALUES, m_uiWindowWidthValues);
	DDX_Radio(pDX, IDC_RADIO_NORMAL_ANALOG, m_iNormalAnalog);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CParameters, CDialog)
	//{{AFX_MSG_MAP(CParameters)
	ON_BN_CLICKED(IDC_CHECK_1, OnCheck1)
	ON_BN_CLICKED(IDC_CHECK_2, OnCheck2)
	ON_BN_CLICKED(IDC_CHECK_3, OnCheck3)
	ON_BN_CLICKED(IDC_CHECK_4, OnCheck4)
	ON_BN_CLICKED(IDC_RADIO_ACQ_FINITE, EnableChanListCount)
	ON_BN_CLICKED(IDC_RADIO_ACQ_INFINITE, DisableChanListCount)
	ON_BN_CLICKED(IDC_RADIO_CONT_SW, OnRadioContSw)
	ON_BN_CLICKED(IDC_RADIO_CONT_ET, OnRadioContEt)
	ON_BN_CLICKED(IDC_RADIO_CONT_ET_VALUE, OnRadioContEtValueOrChanList)
	ON_BN_CLICKED(IDC_RADIO_CONT_ET_CHANLIST, OnRadioContEtValueOrChanList)
	ON_BN_CLICKED(IDC_RADIO_NORMAL_ANALOG, OnRadioNormalAnalog)
	ON_BN_CLICKED(IDC_RADIO_ANALOG_MULTIPLEXING, OnRadioAnalogMultiplexing)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CParameters message handlers

BOOL CParameters::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here

	m_cbChannel1.SubclassDlgItem(IDC_COLOUR_1, this);
	
	m_cbChannel2.SubclassDlgItem(IDC_COLOUR_2, this);
	
	m_cbChannel3.SubclassDlgItem(IDC_COLOUR_3, this);
	
	m_cbChannel4.SubclassDlgItem(IDC_COLOUR_4, this);

	m_spinCount.SetRange32(4, 1000000);

	m_spinSampleRate.SetRange32(1, 500000);

	m_spinWindowWidthValues.SetRange32(4, 500000);

	OnCheck1();

	OnCheck2();

	OnCheck3();

	OnCheck4();

	if(m_iAcqMode == 0)
	{
		OnRadioContSw();
	}
	else if(m_iAcqMode == 1)
	{
		OnRadioContEt();
	}
	else
	{
		OnRadioContEtValueOrChanList();
	}

	if(m_iAcqDuration == 0)
	{
		DisableChanListCount();	
	}
	else
	{
		EnableChanListCount();	
	}
	
	if(m_iNormalAnalog == 0)
	{
		OnRadioNormalAnalog();	
	}
	else
	{
		OnRadioAnalogMultiplexing();	
	}
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CParameters::OnCheck1() 
{
	// TODO: Add your control notification handler code here
	
	BOOL b_enable = IsDlgButtonChecked(IDC_CHECK_1);

	GetDlgItem(IDC_CHAN_NUMBER_1)->EnableWindow(b_enable);

	GetDlgItem(IDC_RANGE_COMBO_1)->EnableWindow(b_enable);

	GetDlgItem(IDC_MIN_1)->EnableWindow(b_enable);

	GetDlgItem(IDC_MAX_1)->EnableWindow(b_enable);
}

void CParameters::OnCheck2() 
{
	// TODO: Add your control notification handler code here
	
	BOOL b_enable = IsDlgButtonChecked(IDC_CHECK_2);

	GetDlgItem(IDC_CHAN_NUMBER_2)->EnableWindow(b_enable);

	GetDlgItem(IDC_RANGE_COMBO_2)->EnableWindow(b_enable);

	GetDlgItem(IDC_MIN_2)->EnableWindow(b_enable);

	GetDlgItem(IDC_MAX_2)->EnableWindow(b_enable);
}

void CParameters::OnCheck3() 
{
	// TODO: Add your control notification handler code here
	
	BOOL b_enable = IsDlgButtonChecked(IDC_CHECK_3);

	GetDlgItem(IDC_CHAN_NUMBER_3)->EnableWindow(b_enable);

	GetDlgItem(IDC_RANGE_COMBO_3)->EnableWindow(b_enable);

	GetDlgItem(IDC_MIN_3)->EnableWindow(b_enable);

	GetDlgItem(IDC_MAX_3)->EnableWindow(b_enable);
}

void CParameters::OnCheck4() 
{
	// TODO: Add your control notification handler code here
	
	BOOL b_enable = IsDlgButtonChecked(IDC_CHECK_4);

	GetDlgItem(IDC_CHAN_NUMBER_4)->EnableWindow(b_enable);

	GetDlgItem(IDC_RANGE_COMBO_4)->EnableWindow(b_enable);

	GetDlgItem(IDC_MIN_4)->EnableWindow(b_enable);

	GetDlgItem(IDC_MAX_4)->EnableWindow(b_enable);
}

void CParameters::OnRadioContSw() 
{
	// TODO: Add your control notification handler code here
	
	GetDlgItem(IDC_RADIO_DIGITAL)->EnableWindow(FALSE);
	
	GetDlgItem(IDC_RADIO_ANALOG)->EnableWindow(FALSE);
	
	GetDlgItem(IDC_RADIO_HIGH_LOW)->EnableWindow(FALSE);
	
	GetDlgItem(IDC_RADIO_LOW_HIGH)->EnableWindow(FALSE);
	
	GetDlgItem(IDC_RADIO_BOTH)->EnableWindow(FALSE);
	
	GetDlgItem(IDC_EDIT_SAMPLE_RATE)->EnableWindow(TRUE);
	
	GetDlgItem(IDC_SPIN_SAMPLE_RATE)->EnableWindow(TRUE);

	if( IsDlgButtonChecked(IDC_RADIO_ACQ_INFINITE) )
	{
		GetDlgItem(IDC_EDIT_WINDOW_WIDTH_VALUES)->EnableWindow(FALSE);
	
		GetDlgItem(IDC_SPIN_WINDOW_WIDTH_VALUES)->EnableWindow(FALSE);
	
		GetDlgItem(IDC_EDIT_WINDOW_WIDTH_SECS)->EnableWindow(TRUE);
	}
}

void CParameters::OnRadioContEt() 
{
	// TODO: Add your control notification handler code here
	
	GetDlgItem(IDC_RADIO_DIGITAL)->EnableWindow(TRUE);
	
	GetDlgItem(IDC_RADIO_ANALOG)->EnableWindow(TRUE);
	
	GetDlgItem(IDC_RADIO_HIGH_LOW)->EnableWindow(TRUE);
	
	GetDlgItem(IDC_RADIO_LOW_HIGH)->EnableWindow(TRUE);
	
	GetDlgItem(IDC_RADIO_BOTH)->EnableWindow(TRUE);
	
	GetDlgItem(IDC_EDIT_SAMPLE_RATE)->EnableWindow(TRUE);
	
	GetDlgItem(IDC_SPIN_SAMPLE_RATE)->EnableWindow(TRUE);

	if( IsDlgButtonChecked(IDC_RADIO_ACQ_INFINITE) )
	{
		GetDlgItem(IDC_EDIT_WINDOW_WIDTH_VALUES)->EnableWindow(FALSE);
	
		GetDlgItem(IDC_SPIN_WINDOW_WIDTH_VALUES)->EnableWindow(FALSE);
	
		GetDlgItem(IDC_EDIT_WINDOW_WIDTH_SECS)->EnableWindow(TRUE);
	}
}

void CParameters::OnRadioContEtValueOrChanList() 
{
	// TODO: Add your control notification handler code here
	
	GetDlgItem(IDC_RADIO_DIGITAL)->EnableWindow(TRUE);
	
	GetDlgItem(IDC_RADIO_ANALOG)->EnableWindow(TRUE);
	
	GetDlgItem(IDC_RADIO_HIGH_LOW)->EnableWindow(TRUE);
	
	GetDlgItem(IDC_RADIO_LOW_HIGH)->EnableWindow(TRUE);
	
	GetDlgItem(IDC_RADIO_BOTH)->EnableWindow(TRUE);
	
	GetDlgItem(IDC_EDIT_SAMPLE_RATE)->EnableWindow(FALSE);
	
	GetDlgItem(IDC_SPIN_SAMPLE_RATE)->EnableWindow(FALSE);

	if( IsDlgButtonChecked(IDC_RADIO_ACQ_INFINITE) )
	{
		GetDlgItem(IDC_EDIT_WINDOW_WIDTH_VALUES)->EnableWindow(TRUE);
	
		GetDlgItem(IDC_SPIN_WINDOW_WIDTH_VALUES)->EnableWindow(TRUE);
	
		GetDlgItem(IDC_EDIT_WINDOW_WIDTH_SECS)->EnableWindow(FALSE);
	}
}

void CParameters::DisableChanListCount() 
{
	// TODO: Add your control notification handler code here
	
	GetDlgItem(IDC_EDIT_COUNT)->EnableWindow(FALSE);
	
	GetDlgItem(IDC_SPIN_COUNT)->EnableWindow(FALSE);
	
	if( IsDlgButtonChecked(IDC_RADIO_CONT_SW) )
	{
		GetDlgItem(IDC_EDIT_WINDOW_WIDTH_VALUES)->EnableWindow(FALSE);
	
		GetDlgItem(IDC_SPIN_WINDOW_WIDTH_VALUES)->EnableWindow(FALSE);
	
		GetDlgItem(IDC_EDIT_WINDOW_WIDTH_SECS)->EnableWindow(TRUE);
	}
	else // if( !IsDlgButtonChecked(IDC_RADIO_CONT_SW) )
	{
		GetDlgItem(IDC_EDIT_WINDOW_WIDTH_VALUES)->EnableWindow(TRUE);
	
		GetDlgItem(IDC_SPIN_WINDOW_WIDTH_VALUES)->EnableWindow(TRUE);
	
		GetDlgItem(IDC_EDIT_WINDOW_WIDTH_SECS)->EnableWindow(FALSE);
	}
}

void CParameters::EnableChanListCount() 
{
	// TODO: Add your control notification handler code here
	
	GetDlgItem(IDC_EDIT_COUNT)->EnableWindow(TRUE);
	
	GetDlgItem(IDC_SPIN_COUNT)->EnableWindow(TRUE);

	GetDlgItem(IDC_SPIN_WINDOW_WIDTH_VALUES)->EnableWindow(FALSE);

	GetDlgItem(IDC_EDIT_WINDOW_WIDTH_VALUES)->EnableWindow(FALSE);

	GetDlgItem(IDC_EDIT_WINDOW_WIDTH_SECS)->EnableWindow(FALSE);
}



void CParameters::OnRadioNormalAnalog() 
{
	// TODO: Add your control notification handler code here
	
	GetDlgItem(IDC_RANGE_COMBO_1)->EnableWindow(TRUE);
	
	GetDlgItem(IDC_RANGE_COMBO_2)->EnableWindow(TRUE);
	
	GetDlgItem(IDC_RANGE_COMBO_3)->EnableWindow(TRUE);
	
	GetDlgItem(IDC_RANGE_COMBO_4)->EnableWindow(TRUE);
	
	GetDlgItem(IDC_RADIO_SINGLE_ENDED)->EnableWindow(TRUE);
	
	GetDlgItem(IDC_RADIO_DIFFERENTIAL)->EnableWindow(TRUE);
	
	GetDlgItem(IDC_CHECK_SAMPLE_AND_HOLD)->EnableWindow(TRUE);
}

void CParameters::OnRadioAnalogMultiplexing() 
{
	// TODO: Add your control notification handler code here
	
	GetDlgItem(IDC_RANGE_COMBO_1)->EnableWindow(FALSE);
	
	GetDlgItem(IDC_RANGE_COMBO_2)->EnableWindow(FALSE);
	
	GetDlgItem(IDC_RANGE_COMBO_3)->EnableWindow(FALSE);
	
	GetDlgItem(IDC_RANGE_COMBO_4)->EnableWindow(FALSE);
	
	GetDlgItem(IDC_RADIO_SINGLE_ENDED)->EnableWindow(FALSE);
	
	GetDlgItem(IDC_RADIO_DIFFERENTIAL)->EnableWindow(FALSE);
	
	GetDlgItem(IDC_CHECK_SAMPLE_AND_HOLD)->EnableWindow(FALSE);
}
