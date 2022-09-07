/* ==========================================================================
	Class :			CReportFieldProperties

	Author :		Johan Rosengren, Abstrakt Mekanik AB

	Date :			2004-07-25

	Purpose :		"CReportBoxProperties" is a "CDiagramPropertyDlg"-derived 
					class for setting properties to a "CReportEntityField" 
					object

	Description :	This is a Wizard-created dialogbox class.

	Usage :			See "CDiagramPropertyDlg".

   ========================================================================*/

#include "stdafx.h"
#include "ReportFieldProperties.h"
#include "ReportEntityField.h"
#include "ReportEntitySettings.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CReportFieldProperties dialog


CReportFieldProperties::CReportFieldProperties(CWnd* pParent /*=NULL*/)
	: CDiagramPropertyDlg(CReportFieldProperties::IDD, pParent)
/* ============================================================
	Function :		CReportFieldProperties::CReportFieldProperties
	Description :	Constructor
	Access :		Public

	Return :		void
	Parameters :	CWnd* pParent	-	Parent window
					
	Usage :			

   ============================================================*/
{
	//{{AFX_DATA_INIT(CReportFieldProperties)
	m_contents = _T("");
	m_justification = 0;
	//}}AFX_DATA_INIT
}


void CReportFieldProperties::DoDataExchange(CDataExchange* pDX)
/* ============================================================
	Function :		CReportFieldProperties::DoDataExchange
	Description :	MFC data exchange handler.
	Access :		Protected

	Return :		void
	Parameters :	CDataExchange* pDX	-	Exchange object
					
	Usage :			Called from MFC.

   ============================================================*/
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CReportFieldProperties)
	DDX_Text(pDX, IDC_EDIT_CONTENTS, m_contents);
	DDX_Radio(pDX, IDC_RADIO_LEFT, m_justification);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CReportFieldProperties, CDialog)
	//{{AFX_MSG_MAP(CReportFieldProperties)
	ON_BN_CLICKED(IDC_BUTTON_FONT, OnButtonFont)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CReportFieldProperties message handlers

void CReportFieldProperties::OnOK() 
/* ============================================================
	Function :		CReportFieldProperties::OnOK
	Description :	Handler for the dialog OK-button.
	Access :		Protected

	Return :		void
	Parameters :	none

	Usage :			Called from MFC.

   ============================================================*/
{
	UpdateData();

	CReportEntityField* field = static_cast< CReportEntityField* >( GetEntity() );

	field->SetFontName( m_lf.lfFaceName );
	field->SetFontSize( m_lf.lfHeight );
	field->SetFontColor( m_color );
	field->SetFontBold( ( m_lf.lfWeight == FW_BOLD ) );
	field->SetFontItalic( m_lf.lfItalic );
	field->SetFontUnderline( m_lf.lfUnderline );
	field->SetFontStrikeout( m_lf.lfStrikeOut );
	field->SetFontCharset( m_lf.lfCharSet );

	field->SetName( m_contents );

	if( m_justification == 0 )
		field->SetJustification( DT_LEFT );
	if( m_justification == 1 )
		field->SetJustification( DT_CENTER );
	if( m_justification == 2 )
		field->SetJustification( DT_RIGHT );

	CReportEntitySettings::GetRESInstance()->SetLogFont( m_lf );
	CReportEntitySettings::GetRESInstance()->SetColor( m_color );
	CReportEntitySettings::GetRESInstance()->SetJustification( field->GetJustification() );

	ShowWindow( SW_HIDE );
	Redraw();

}

void CReportFieldProperties::OnCancel() 
/* ============================================================
	Function :		CReportFieldProperties::OnCancel
	Description :	Handler for the dialog Cancel-button.
	Access :		Protected

	Return :		void
	Parameters :	none

	Usage :			Called from MFC.

   ============================================================*/
{

	ShowWindow( SW_HIDE );

}

void CReportFieldProperties::OnButtonFont() 
/* ============================================================
	Function :		CReportFieldProperties::OnButtonFont
	Description :	Handler for the dialog button Font
	Access :		Protected

	Return :		void
	Parameters :	none

	Usage :			Called from MFC.

   ============================================================*/
{

	CClientDC	dc( this );
	int inch = dc.GetDeviceCaps( LOGPIXELSX );
	double pt = static_cast< double >( inch ) / 72;
	int height = m_lf.lfHeight / 10;
	height = round( static_cast< double >( height ) * pt );
	m_lf.lfHeight = -( height );

	CFontDialog	dlg( &m_lf );
	dlg.m_cf.rgbColors = m_color;
	dlg.m_cf.Flags |= CF_EFFECTS;
	if( dlg.DoModal() == IDOK )
	{

		dlg.GetCurrentFont( &m_lf );
		m_lf.lfHeight = dlg.GetSize();

		m_color = dlg.GetColor();

	}

}

void CReportFieldProperties::SetValues() 
/* ============================================================
	Function :		CReportFieldProperties::SetValues
	Description :	Sets the values in the property dialog
	Access :		Public

	Return :		void
	Parameters :	none

	Usage :			Call to set the fields in the property 
					dialog.

   ============================================================*/
{

	CReportEntityField* field = static_cast< CReportEntityField* >( GetEntity() );

	m_contents = field->GetName();

	ZeroMemory( &m_lf, sizeof( m_lf ) );

	m_lf.lfHeight = field->GetFontSize();
	lstrcpy( m_lf.lfFaceName, field->GetFontName() );

	if( field->GetFontBold() )
		m_lf.lfWeight = FW_BOLD;
	else
		m_lf.lfWeight = FW_NORMAL;

	if( field->GetFontUnderline() )
		m_lf.lfUnderline = TRUE;

	if( field->GetFontItalic() )
		m_lf.lfItalic = TRUE;

	if( field->GetFontStrikeout() )
		m_lf.lfStrikeOut = TRUE;

	m_lf.lfCharSet = ( BYTE ) field->GetFontCharset();

	m_color = field->GetFontColor();
	
	if( field->GetJustification() == DT_LEFT )
		m_justification = 0;

	if( field->GetJustification() == DT_CENTER )
		m_justification = 1;

	if( field->GetJustification() == DT_RIGHT )
		m_justification = 2;

}

