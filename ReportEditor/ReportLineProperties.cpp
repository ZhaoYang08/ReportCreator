/* ==========================================================================
	Class :			CReportLineProperties

	Author :		Johan Rosengren, Abstrakt Mekanik AB

	Date :			2004-07-25

	Purpose :		"CReportBoxProperties" is a "CDiagramPropertyDlg"-derived 
					class for setting properties to a "CReportEntityLine" 
					object

	Description :	This is a Wizard-created dialogbox class.

	Usage :			See "CDiagramPropertyDlg".

   ========================================================================*/

#include "stdafx.h"
#include "ReportLineProperties.h"
#include "ReportEntityLine.h"
#include "ReportEntitySettings.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CReportLineProperties dialog


CReportLineProperties::CReportLineProperties(CWnd* pParent /*=NULL*/)
	: CDiagramPropertyDlg(CReportLineProperties::IDD, pParent)
/* ============================================================
	Function :		CReportLineProperties::CReportLineProperties
	Description :	Constructor
	Access :		Public

	Return :		void
	Parameters :	CWnd* pParent	-	Window parent
					
	Usage :			

   ============================================================*/
{
	//{{AFX_DATA_INIT(CReportLineProperties)
	m_thickness = 0;
	//}}AFX_DATA_INIT

	m_lineStyle = PS_SOLID;

}


void CReportLineProperties::DoDataExchange(CDataExchange* pDX)
/* ============================================================
	Function :		CReportLineProperties::DoDataExchange
	Description :	MFC data exchange handler.
	Access :		Protected

	Return :		void
	Parameters :	CDataExchange* pDX	-	Exchange object
					
	Usage :			Called from MFC.

   ============================================================*/
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CReportLineProperties)
	DDX_Control(pDX, IDC_STATIC_COLOR, m_ctrlColor);
	DDX_Control(pDX, IDC_COMBO_STYLE, m_ctrlStyle);
	DDX_Text(pDX, IDC_EDIT_THICKNESS, m_thickness);
	DDX_Text(pDX, IDC_EDIT_NAME, m_name);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CReportLineProperties, CDialog)
	//{{AFX_MSG_MAP(CReportLineProperties)
	ON_BN_CLICKED(IDC_BUTTON_COLOR, OnButtonColor)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CReportLineProperties message handlers

void CReportLineProperties::OnOK() 
/* ============================================================
	Function :		CReportLineProperties::OnOK
	Description :	Handler for the dialog OK-button.
	Access :		Protected

	Return :		void
	Parameters :	none

	Usage :			Called from MFC.

   ============================================================*/
{

	UpdateData();
	CReportEntityLine* obj = static_cast< CReportEntityLine* >( GetEntity() );
	
	obj->SetBorderColor( m_color );
	obj->SetBorderThickness( m_thickness );
	obj->SetName( m_name );

	CReportEntitySettings::GetRESInstance()->SetLineColor( m_color );
	CReportEntitySettings::GetRESInstance()->SetLineThickness( m_thickness );

	int index = m_ctrlStyle.GetCurSel();
	if( index != CB_ERR )
		obj->SetBorderStyle( m_ctrlStyle.GetItemData( index ) );

	ShowWindow( SW_HIDE );
	Redraw();

}

void CReportLineProperties::OnCancel() 
/* ============================================================
	Function :		CReportLineProperties::OnCancel
	Description :	Handler for the dialog Cancel-button.
	Access :		Protected

	Return :		void
	Parameters :	none

	Usage :			Called from MFC.

   ============================================================*/
{

	ShowWindow( SW_HIDE );

}

BOOL CReportLineProperties::OnInitDialog() 
/* ============================================================
	Function :		CReportLineProperties::OnInitDialog
	Description :	Handler for the "WM_INITDIALOG" messag
	Access :		Protected

	Return :		BOOL	-	Always "TRUE"
	Parameters :	none

	Usage :			Called from MFC

   ============================================================*/
{
	CDialog::OnInitDialog();
	
	m_ctrlColor.SetColor( m_color );
	
	if( m_ctrlStyle.GetCount() == 0 )
	{
		CString text;

		text.LoadString( IDS_REPORT_LINE_STYLE_1 );
		m_ctrlStyle.SetItemData( m_ctrlStyle.AddString( text ), PS_SOLID );

		text.LoadString( IDS_REPORT_LINE_STYLE_2 );
		m_ctrlStyle.SetItemData( m_ctrlStyle.AddString( text ), PS_DASH );

		text.LoadString( IDS_REPORT_LINE_STYLE_3 );
		m_ctrlStyle.SetItemData( m_ctrlStyle.AddString( text ), PS_DOT );

	}

	int max = m_ctrlStyle.GetCount();
	for( int t = 0 ; t < max ; t++ )
		if( m_ctrlStyle.GetItemData( t ) == static_cast< DWORD >( m_lineStyle ) )
			m_ctrlStyle.SetCurSel( t );

	return TRUE;

}

void CReportLineProperties::SetValues()
/* ============================================================
	Function :		CReportLineProperties::SetValues
	Description :	Sets the values of the property dialog
	Access :		Public

	Return :		void
	Parameters :	none

	Usage :			Call to set the property dialog values.

   ============================================================*/
{

	CReportEntityLine* obj = static_cast< CReportEntityLine* >( GetEntity() );
	m_color = obj->GetBorderColor();
	if( m_ctrlColor.m_hWnd )
		m_ctrlColor.SetColor( m_color );

	m_name = obj->GetName();
	m_thickness = obj->GetBorderThickness();
	m_lineStyle = obj->GetBorderStyle();

	if( m_ctrlStyle.m_hWnd )
	{
		int max = m_ctrlStyle.GetCount();
		for( int t = 0 ; t < max ; t++ )
			if( m_ctrlStyle.GetItemData( t ) == static_cast< DWORD >( m_lineStyle ) )
				m_ctrlStyle.SetCurSel( t );
	}

}

void CReportLineProperties::OnButtonColor() 
/* ============================================================
	Function :		CReportLineProperties::OnButtonColor
	Description :	Handler for the dialog button Color
	Access :		Protected

	Return :		void
	Parameters :	none

	Usage :			Called from MFC.

   ============================================================*/
{
	CColorDialog	dlg( m_color );
	if( dlg.DoModal() == IDOK )
	{
		m_color = dlg.GetColor();
		m_ctrlColor.SetColor( m_color );
	}

}
