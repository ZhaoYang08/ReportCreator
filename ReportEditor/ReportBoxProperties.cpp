/* ==========================================================================
	Class :			CReportBoxProperties

	Author :		Johan Rosengren, Abstrakt Mekanik AB

	Date :			2004-07-25


	Purpose :		"CReportBoxProperties" is a "CDiagramPropertyDlg"-derived 
					class for setting properties to a "CReportEntityBox" 
					object

	Description :	This is a Wizard-created dialogbox class.

	Usage :			See "CDiagramPropertyDlg".

   ========================================================================*/

#include "stdafx.h"
#include "ReportBoxProperties.h"
#include "ReportEntityBox.h"
#include "ReportEntitySettings.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CReportBoxProperties dialog

CReportBoxProperties::CReportBoxProperties(CWnd* pParent /*=NULL*/)
	: CDiagramPropertyDlg(CReportBoxProperties::IDD, pParent)
/* ============================================================
	Function :		CReportBoxProperties::CReportBoxProperties
	Description :	Constructor
	Access :		Public

	Return :		void
	Parameters :	CWnd* pParent	-	Parent window
					
	Usage :			

   ============================================================*/
{
	//{{AFX_DATA_INIT(CReportBoxProperties)
	m_borderThickness = 0;
	m_fill = FALSE;
	m_border = FALSE;
	//}}AFX_DATA_INIT

	m_borderStyle = PS_SOLID;

}

void CReportBoxProperties::DoDataExchange(CDataExchange* pDX)
/* ============================================================
	Function :		CReportBoxProperties::DoDataExchange
	Description :	MFC data exchange handler.
	Access :		Protected

	Return :		void
	Parameters :	CDataExchange* pDX	-	Exchange object
					
	Usage :			Called from MFC.

   ============================================================*/
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CReportBoxProperties)
	DDX_Control(pDX, IDC_COMBO_BORDER_STYLE, m_ctrlBorderStyle);
	DDX_Control(pDX, IDC_STATIC_FILL_COLOR, m_ctrlFillColor);
	DDX_Control(pDX, IDC_STATIC_BORDER_COLOR, m_ctrlBorderColor);
	DDX_Text(pDX, IDC_EDIT_BORDER_THICKNESS, m_borderThickness);
	DDX_Text(pDX, IDC_EDIT_NAME, m_name);
	DDX_Check(pDX, IDC_CHECK_FILL, m_fill);
	DDX_Check(pDX, IDC_CHECK_BORDER, m_border);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CReportBoxProperties, CDialog)
	//{{AFX_MSG_MAP(CReportBoxProperties)
	ON_BN_CLICKED(IDC_BUTTON_FILL_COLOR, OnButtonFillColor)
	ON_BN_CLICKED(IDC_BUTTON_BORDER_COLOR, OnButtonBorderColor)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CReportBoxProperties message handlers

void CReportBoxProperties::OnOK() 
/* ============================================================
	Function :		CReportBoxProperties::OnOK
	Description :	Handler for the dialog OK-button.
	Access :		Protected

	Return :		void
	Parameters :	none

	Usage :			Called from MFC.

   ============================================================*/
{
	UpdateData();

	CReportEntityBox* obj = static_cast< CReportEntityBox* >( GetEntity() );

	obj->SetBorder( m_border );
	obj->SetBorderColor( m_borderColor );
	obj->SetBorderThickness( m_borderThickness );

	obj->SetFill( m_fill );
	obj->SetFillColor( m_fillColor );

	int index = m_ctrlBorderStyle.GetCurSel();
	if( index != CB_ERR )
		obj->SetBorderStyle( m_ctrlBorderStyle.GetItemData( index ) );

	obj->SetName( m_name );

	CReportEntitySettings::GetRESInstance()->SetFill( m_fill );
	CReportEntitySettings::GetRESInstance()->SetFillColor( m_fillColor );
	CReportEntitySettings::GetRESInstance()->SetBorder( m_border );
	CReportEntitySettings::GetRESInstance()->SetBorderColor( m_borderColor );
	CReportEntitySettings::GetRESInstance()->SetBorderThickness( m_borderThickness );
	CReportEntitySettings::GetRESInstance()->SetBorderStyle( m_borderStyle );

	ShowWindow( SW_HIDE );
	Redraw();

}

void CReportBoxProperties::OnCancel() 
/* ============================================================
	Function :		CReportBoxProperties::OnCancel
	Description :	Handler for the dialog Cancel-button.
	Access :		Protected

	Return :		void
	Parameters :	none

	Usage :			Called from MFC.

   ============================================================*/
{

	ShowWindow( SW_HIDE );

}

BOOL CReportBoxProperties::OnInitDialog() 
/* ============================================================
	Function :		CReportBoxProperties::OnInitDialog
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

void CReportBoxProperties::SetValues()
/* ============================================================
	Function :		CReportBoxProperties::SetValues
	Description :	Sets the data in the box from the attached 
					object.
	Access :		Public

	Return :		void
	Parameters :	none

	Usage :			Called from the object

   ============================================================*/
{

	CReportEntityBox* obj = static_cast< CReportEntityBox* >( GetEntity() );

	m_borderColor = obj->GetBorderColor();
	m_fillColor = obj->GetFillColor();
	if( m_ctrlFillColor.m_hWnd )
		m_ctrlFillColor.SetColor( m_fillColor );

	if( m_ctrlBorderColor.m_hWnd )
		m_ctrlBorderColor.SetColor( m_borderColor );

	m_name = obj->GetName();

	m_border = obj->GetBorder();
	m_fill = obj->GetFill();

	m_borderStyle = obj->GetBorderStyle();

	if( m_ctrlBorderStyle.m_hWnd )
	{
		int max = m_ctrlBorderStyle.GetCount();
		for( int t = 0 ; t < max ; t++ )
			if( m_ctrlBorderStyle.GetItemData( t ) == static_cast< DWORD >( m_borderStyle ) )
				m_ctrlBorderStyle.SetCurSel( t );
	}

}

void CReportBoxProperties::OnButtonFillColor() 
/* ============================================================
	Function :		CReportBoxProperties::OnButtonFillColor
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
		UpdateData( FALSE );
	}
	
}

void CReportBoxProperties::OnButtonBorderColor() 
/* ============================================================
	Function :		CReportBoxProperties::OnButtonBorderColor
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
		UpdateData( FALSE );
	}
	
}
