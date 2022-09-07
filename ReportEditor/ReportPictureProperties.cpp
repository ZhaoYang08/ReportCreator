/* ==========================================================================
	Class :			CReportPictureProperties

	Author :		Johan Rosengren, Abstrakt Mekanik AB

	Date :			2004-07-23

	Purpose :		"CReportBoxProperties" is a "CDiagramPropertyDlg"-derived 
					class for setting properties to a "CReportEntityPicture" 
					object

	Description :	This is a Wizard-created dialogbox class.

	Usage :			See "CDiagramPropertyDlg".
   ========================================================================
					19/9 2005	Moved AdjustSize to the end of OnOK to 
								avoid resetting of the other values (Alex Evans)

   ========================================================================*/

#include "stdafx.h"
#include "ReportPictureProperties.h"
#include "ReportEntityPicture.h"
#include "ReportEntitySettings.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CReportPictureProperties dialog

CReportPictureProperties::CReportPictureProperties(CWnd* pParent /*=NULL*/)
	: CDiagramPropertyDlg(CReportPictureProperties::IDD, pParent)
/* ============================================================
	Function :		CReportPictureProperties::CReportPictureProperties
	Description :	Constructor
	Access :		Public

	Return :		void
	Parameters :	CWnd* pParent	-	Parent window
					
	Usage :			

   ============================================================*/
{
	//{{AFX_DATA_INIT(CReportPictureProperties)
	m_filename = _T("");
	m_borderThickness = 0;
	m_border = FALSE;
	//}}AFX_DATA_INIT

	m_borderStyle = PS_SOLID;

}

void CReportPictureProperties::DoDataExchange(CDataExchange* pDX)
/* ============================================================
	Function :		CReportPictureProperties::DoDataExchange
	Description :	MFC data exchange handler.
	Access :		Protected

	Return :		void
	Parameters :	CDataExchange* pDX	-	Exchange object
					
	Usage :			Called from MFC.

   ============================================================*/
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CReportPictureProperties)
	DDX_Control(pDX, IDC_STATIC_PREVIEW, m_preview);
	DDX_Text(pDX, IDC_EDIT_FILENAME, m_filename);
	DDX_Control(pDX, IDC_COMBO_BORDER_STYLE, m_ctrlBorderStyle);
	DDX_Control(pDX, IDC_STATIC_BORDER_COLOR, m_ctrlBorderColor);
	DDX_Text(pDX, IDC_EDIT_BORDER_THICKNESS, m_borderThickness);
	DDX_Check(pDX, IDC_CHECK_BORDER, m_border);
	DDX_Text(pDX, IDC_EDIT_NAME, m_name);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CReportPictureProperties, CDialog)
	//{{AFX_MSG_MAP(CReportPictureProperties)
	ON_BN_CLICKED(IDC_BUTTON_BROWSE, OnButtonBrowse)
	ON_BN_CLICKED(IDC_BUTTON_BORDER_COLOR, OnButtonBorderColor)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CReportPictureProperties message handlers

void CReportPictureProperties::OnOK() 
/* ============================================================
	Function :		CReportPictureProperties::OnOK
	Description :	Handler for the dialog OK-button.
	Access :		Protected

	Return :		void
	Parameters :	none

	Usage :			Called from MFC.

   ============================================================*/
{
	UpdateData();

	CReportEntityPicture* pic = static_cast< CReportEntityPicture* >( GetEntity() );
	
	pic->SetFilename( m_filename );

	pic->SetBorder( m_border );
	pic->SetBorderColor( m_borderColor );
	pic->SetBorderThickness( m_borderThickness );

	pic->SetName( m_name );

	int index = m_ctrlBorderStyle.GetCurSel();
	if( index != CB_ERR )
		pic->SetBorderStyle( m_ctrlBorderStyle.GetItemData( index ) );

	CReportEntitySettings::GetRESInstance()->SetBorder( m_border );
	CReportEntitySettings::GetRESInstance()->SetBorderColor( m_borderColor );
	CReportEntitySettings::GetRESInstance()->SetBorderThickness( m_borderThickness );
	CReportEntitySettings::GetRESInstance()->SetBorderStyle( m_borderStyle );

	pic->AdjustSize();

	ShowWindow( SW_HIDE );
	Redraw();

}

void CReportPictureProperties::OnCancel() 
/* ============================================================
	Function :		CReportPictureProperties::OnCancel
	Description :	Handler for the dialog Cancel-button.
	Access :		Protected

	Return :		void
	Parameters :	none

	Usage :			Called from MFC.

   ============================================================*/
{

	ShowWindow( SW_HIDE );

}

void CReportPictureProperties::OnButtonBrowse() 
/* ============================================================
	Function :		CReportPictureProperties::OnButtonBrowse
	Description :	Handler for the dialog button Browse
	Access :		Protected

	Return :		void
	Parameters :	none

	Usage :			Called from MFC.

   ============================================================*/
{
	CFileDialog	dlg( TRUE, _T( "bmp" ) , _T( "*.bmp" ) );
	if( dlg.DoModal() == IDOK )
	{

		m_filename = dlg.GetPathName();
		m_preview.SetFilename( m_filename );

		m_filename = m_preview.GetFilename(); // If any error
		UpdateData( FALSE );

	}
	
}

void CReportPictureProperties::SetValues()
/* ============================================================
	Function :		CReportPictureProperties::SetValues
	Description :	Sets the values of the property dialog
	Access :		Public

	Return :		void
	Parameters :	none

	Usage :			Call to set the property dialog values.

   ============================================================*/
{

	CReportEntityPicture* pic = static_cast< CReportEntityPicture* >( GetEntity() );
	m_filename = pic->GetFilename();
	if( m_preview.m_hWnd )
		m_preview.SetFilename( m_filename );

	m_borderColor = pic->GetBorderColor();

	if( m_ctrlBorderColor.m_hWnd )
		m_ctrlBorderColor.SetColor( m_borderColor );

	m_name = pic->GetName();
	m_border = pic->GetBorder();
	m_borderStyle = pic->GetBorderStyle();

	if( m_ctrlBorderStyle.m_hWnd )
	{
		int max = m_ctrlBorderStyle.GetCount();
		for( int t = 0 ; t < max ; t++ )
			if( m_ctrlBorderStyle.GetItemData( t ) == static_cast< DWORD >( m_borderStyle ) )
				m_ctrlBorderStyle.SetCurSel( t );
	}

}

BOOL CReportPictureProperties::OnInitDialog() 
/* ============================================================
	Function :		CReportPictureProperties::OnInitDialog
	Description :	Handler for the "WM_INITDIALOG" messag
	Access :		Protected

	Return :		BOOL	-	Always "TRUE"
	Parameters :	none

	Usage :			Called from MFC

   ============================================================*/
{
	CDialog::OnInitDialog();

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

void CReportPictureProperties::OnButtonBorderColor() 
/* ============================================================
	Function :		CReportPictureProperties::OnButtonBorderColor
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
