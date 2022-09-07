/* ==========================================================================
	Class :			CReportEllipseProperties

	Author :		Johan Rosengren, Abstrakt Mekanik AB

	Date :			2004-07-25

	Purpose :		"CReportBoxProperties" is a "CDiagramPropertyDlg"-derived 
					class for setting properties to a "CReportEntityEllipse" 
					object

	Description :	This is a Wizard-created dialogbox class.

	Usage :			See "CDiagramPropertyDlg".


   ========================================================================*/
#include "stdafx.h"
#include "ReportEllipseProperties.h"
#include "ReportEntityEllipse.h"
#include "ReportEntitySettings.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CReportEllipseProperties dialog

CReportEllipseProperties::CReportEllipseProperties(CWnd* pParent /*=NULL*/)
	: CDiagramPropertyDlg(CReportEllipseProperties::IDD, pParent)
/* ============================================================
	Function :		CReportEllipseProperties::CReportEllipseProperties
	Description :	Constructor
	Access :		Public

	Return :		void
	Parameters :	CWnd* pParent	-	Parent window
					
	Usage :			

   ============================================================*/
{
	//{{AFX_DATA_INIT(CReportEllipseProperties)
	m_border = FALSE;
	m_fill = FALSE;
	m_borderThickness = 0;
	//}}AFX_DATA_INIT

	m_borderStyle = PS_SOLID;

}

void CReportEllipseProperties::DoDataExchange(CDataExchange* pDX)
/* ============================================================
	Function :		CReportEllipseProperties::DoDataExchange
	Description :	MFC data exchange handler.
	Access :		Protected

	Return :		void
	Parameters :	CDataExchange* pDX	-	Exchange object
					
	Usage :			Called from MFC.

   ============================================================*/
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CReportEllipseProperties)
	DDX_Control(pDX, IDC_STATIC_FILL_COLOR, m_ctrlFillColor);
	DDX_Control(pDX, IDC_STATIC_BORDER_COLOR, m_ctrlBorderColor);
	DDX_Check(pDX, IDC_CHECK_BORDER, m_border);
	DDX_Check(pDX, IDC_CHECK_FILL, m_fill);
	DDX_Control(pDX, IDC_COMBO_BORDER_STYLE, m_ctrlBorderStyle);
	DDX_Text(pDX, IDC_EDIT_BORDER_THICKNESS, m_borderThickness);
	DDX_Text(pDX, IDC_EDIT_NAME, m_name);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CReportEllipseProperties, CDialog)
	//{{AFX_MSG_MAP(CReportEllipseProperties)
	ON_BN_CLICKED(IDC_BUTTON_BORDER_COLOR, OnButtonBorderColor)
	ON_BN_CLICKED(IDC_BUTTON_FILL_COLOR, OnButtonFillColor)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CReportEllipseProperties message handlers

void CReportEllipseProperties::OnOK() 
/* ============================================================
	Function :		CReportEllipseProperties::OnOK
	Description :	Handler for the dialog OK-button.
	Access :		Protected

	Return :		void
	Parameters :	none

	Usage :			Called from MFC.

   ============================================================*/
{

	UpdateData();

	CReportEntityEllipse* obj = static_cast< CReportEntityEllipse* >( GetEntity() );

	obj->SetName( m_name );
	obj->SetBorder( m_border );
	obj->SetBorderColor( m_borderColor );
	obj->SetBorderThickness( m_borderThickness );

	obj->SetFill( m_fill );
	obj->SetFillColor( m_fillColor );

	int index = m_ctrlBorderStyle.GetCurSel();
	if( index != CB_ERR )
		obj->SetBorderStyle( m_ctrlBorderStyle.GetItemData( index ) );

	CReportEntitySettings::GetRESInstance()->SetFill( m_fill );
	CReportEntitySettings::GetRESInstance()->SetFillColor( m_fillColor );
	CReportEntitySettings::GetRESInstance()->SetBorder( m_border );
	CReportEntitySettings::GetRESInstance()->SetBorderColor( m_borderColor );
	CReportEntitySettings::GetRESInstance()->SetBorderThickness( m_borderThickness );
	CReportEntitySettings::GetRESInstance()->SetBorderStyle( m_borderStyle );

	ShowWindow( SW_HIDE );
	Redraw();

}

void CReportEllipseProperties::OnCancel() 
/* ============================================================
	Function :		CReportEllipseProperties::OnCancel
	Description :	Handler for the dialog Cancel-button.
	Access :		Protected

	Return :		void
	Parameters :	none

	Usage :			Called from MFC.

   ============================================================*/
{

	ShowWindow( SW_HIDE );

}

BOOL CReportEllipseProperties::OnInitDialog() 
/* ============================================================
	Function :		CReportEllipseProperties::OnInitDialog
	Description :	Handler for the "WM_INITDIALOG" messag
	Access :		Protected

	Return :		BOOL	-	Always "TRUE"
	Parameters :	none

	Usage :			Called from MFC

   ============================================================*/
{
	CDialog::OnInitDialog();
	
	m_ctrlFillColor.SetColor( m_fillColor );
	m_ctrlBorderColor.SetColor( m_borderColor );

	if( m_ctrlBorderStyle.GetCount() == 0 )
	{
		CString text;

		text.LoadString( IDS_REPORT_LINE_STYLE_1 );
		m_ctrlBorderStyle.SetItemData( m_ctrlBorderStyle.AddString( text ), PS_SOLID );

		text.LoadString( IDS_REPORT_LINE_STYLE_2 );
		m_ctrlBorderStyle.SetItemData( m_ctrlBorderStyle.AddString( text ), PS_DASH );

		text.LoadString( IDS_REPORT_LINE_STYLE_3 );
		m_ctrlBorderStyle.SetItemData( m_ctrlBorderStyle.AddString( text ), PS_DOT );

	}

	int max = m_ctrlBorderStyle.GetCount();
	for( int t = 0 ; t < max ; t++ )
		if( m_ctrlBorderStyle.GetItemData( t ) == static_cast< DWORD >( m_borderStyle ) )
			m_ctrlBorderStyle.SetCurSel( t );

	return TRUE;

}

void CReportEllipseProperties::SetValues()
/* ============================================================
	Function :		CReportEllipseProperties::SetValues
	Description :	Sets the data in the box from the attached 
					object.
	Access :		Public

	Return :		void
	Parameters :	none

	Usage :			Called from the object

   ============================================================*/
{

	CReportEntityEllipse* obj = static_cast< CReportEntityEllipse* >( GetEntity() );

	m_borderColor = obj->GetBorderColor();
	m_fillColor = obj->GetFillColor();
	if( m_ctrlFillColor.m_hWnd )
		m_ctrlFillColor.SetColor( m_fillColor );

	if( m_ctrlBorderColor.m_hWnd )
		m_ctrlBorderColor.SetColor( m_borderColor );

	m_border = obj->GetBorder();
	m_fill = obj->GetFill();
	m_name = obj->GetName();
	m_borderStyle = obj->GetBorderStyle();

	if( m_ctrlBorderStyle.m_hWnd )
	{
		int max = m_ctrlBorderStyle.GetCount();
		for( int t = 0 ; t < max ; t++ )
			if( m_ctrlBorderStyle.GetItemData( t ) == static_cast< DWORD >( m_borderStyle ) )
				m_ctrlBorderStyle.SetCurSel( t );
	}

}

void CReportEllipseProperties::OnButtonBorderColor() 
/* ============================================================
	Function :		CReportEllipseProperties::OnButtonBorderColor
	Description :	Handler for the dialog button BorderColor
	Access :		Protected

	Return :		void
	Parameters :	none

	Usage :			Called from MFC.

   ============================================================*/
{

	CColorDialog	dlg( m_borderColor );
	if( dlg.DoModal() == IDOK )
	{

		m_border = TRUE;
		m_borderColor = dlg.GetColor();
		m_ctrlBorderColor.SetColor( m_borderColor );
		UpdateData( TRUE );

	}
	
	
}

void CReportEllipseProperties::OnButtonFillColor() 
/* ============================================================
	Function :		CReportEllipseProperties::OnButtonFillColor
	Description :	Handler for the dialog button FillColor
	Access :		Protected

	Return :		void
	Parameters :	none

	Usage :			Called from MFC.

   ============================================================*/
{

	CColorDialog	dlg( m_fillColor );
	if( dlg.DoModal() == IDOK )
	{
		m_fill = TRUE;
		m_fillColor = dlg.GetColor();
		m_ctrlFillColor.SetColor( m_fillColor );
		UpdateData( TRUE );
	}
	
	
}
