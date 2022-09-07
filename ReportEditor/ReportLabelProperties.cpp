/* ==========================================================================
	Class :			CReportLabelProperties

	Author :		Johan Rosengren, Abstrakt Mekanik AB

	Date :			2004-07-25

	Purpose :		"CReportBoxProperties" is a "CDiagramPropertyDlg"-derived 
					class for setting properties to a "CReportEntityLabel" 
					object

	Description :	This is a Wizard-created dialogbox class.

	Usage :			See "CDiagramPropertyDlg".

   ========================================================================*/

#include "stdafx.h"
#include "ReportLabelProperties.h"
#include "ReportEntityLabel.h"
#include "ReportEntitySettings.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CReportLabelProperties dialog


CReportLabelProperties::CReportLabelProperties(CWnd* pParent /*=NULL*/)
	: CDiagramPropertyDlg(CReportLabelProperties::IDD, pParent)
/* ============================================================
	Function :		CReportLabelProperties::CReportLabelProperties
	Description :	Constructor
	Access :		Public

	Return :		void
	Parameters :	CWnd* pParent	-	Window parent
					
	Usage :			

   ============================================================*/
{
	//{{AFX_DATA_INIT(CReportLabelProperties)
	m_contents = _T("");
	m_justification = 0;
	//}}AFX_DATA_INIT
}


void CReportLabelProperties::DoDataExchange(CDataExchange* pDX)
/* ============================================================
	Function :		CReportLabelProperties::DoDataExchange
	Description :	MFC data exchange handler.
	Access :		Protected

	Return :		void
	Parameters :	CDataExchange* pDX	-	Exchange object
					
	Usage :			Called from MFC.

   ============================================================*/
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CReportLabelProperties)
	DDX_Text(pDX, IDC_EDIT_CONTENTS, m_contents);
	DDX_Text(pDX, IDC_EDIT_NAME, m_name);
	DDX_Radio(pDX, IDC_RADIO_LEFT, m_justification);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CReportLabelProperties, CDialog)
	//{{AFX_MSG_MAP(CReportLabelProperties)
	ON_BN_CLICKED(IDC_BUTTON_FONT, OnButtonFont)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CReportLabelProperties message handlers

void CReportLabelProperties::OnOK() 
/* ============================================================
	Function :		CReportLabelProperties::OnOK
	Description :	Handler for the dialog OK-button.
	Access :		Protected

	Return :		void
	Parameters :	none

	Usage :			Called from MFC.

   ============================================================*/
{
	UpdateData();

	CReportEntityLabel* label = static_cast< CReportEntityLabel* >( GetEntity() );

	label->SetFontName( m_lf.lfFaceName );
	label->SetFontSize( m_lf.lfHeight );
	label->SetFontColor( m_color );
	label->SetFontBold( ( m_lf.lfWeight == FW_BOLD ) );
	label->SetFontItalic( m_lf.lfItalic );
	label->SetFontUnderline( m_lf.lfUnderline );
	label->SetFontStrikeout( m_lf.lfStrikeOut );
	label->SetFontCharset( m_lf.lfCharSet );

	label->SetTitle( m_contents );
	label->SetName( m_name );

	if( m_justification == 0 )
		label->SetJustification( DT_LEFT );
	if( m_justification == 1 )
		label->SetJustification( DT_CENTER );
	if( m_justification == 2 )
		label->SetJustification( DT_RIGHT );

	CReportEntitySettings::GetRESInstance()->SetLogFont( m_lf );
	CReportEntitySettings::GetRESInstance()->SetColor( m_color );
	CReportEntitySettings::GetRESInstance()->SetJustification( label->GetJustification() );

	ShowWindow( SW_HIDE );
	Redraw();

}

void CReportLabelProperties::OnCancel() 
/* ============================================================
	Function :		CReportLabelProperties::OnCancel
	Description :	Handler for the dialog Cancel-button.
	Access :		Protected

	Return :		void
	Parameters :	none

	Usage :			Called from MFC.

   ============================================================*/
{

	ShowWindow( SW_HIDE );

}

void CReportLabelProperties::OnButtonFont() 
/* ============================================================
	Function :		CReportLabelProperties::OnButtonFont
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

void CReportLabelProperties::SetValues() 
/* ============================================================
	Function :		CReportLabelProperties::SetValues
	Description :	Sets the values of the property dialog
	Access :		Public

	Return :		void
	Parameters :	none

	Usage :			Call to set the property dialog values.

   ============================================================*/
{

	CReportEntityLabel* label = static_cast< CReportEntityLabel* >( GetEntity() );

	m_contents = label->GetTitle();
	m_name = label->GetName();

	ZeroMemory( &m_lf, sizeof( m_lf ) );

	m_lf.lfHeight = label->GetFontSize();
	lstrcpy( m_lf.lfFaceName, label->GetFontName() );

	if( label->GetFontBold() )
		m_lf.lfWeight = FW_BOLD;
	else
		m_lf.lfWeight = FW_NORMAL;

	if( label->GetFontUnderline() )
		m_lf.lfUnderline = TRUE;

	if( label->GetFontItalic() )
		m_lf.lfItalic = TRUE;

	if( label->GetFontStrikeout() )
		m_lf.lfStrikeOut = TRUE;

	m_lf.lfCharSet = ( unsigned char ) label->GetFontCharset();

	m_color = label->GetFontColor();

	if( label->GetJustification() == DT_LEFT )
		m_justification = 0;

	if( label->GetJustification() == DT_CENTER )
		m_justification = 1;

	if( label->GetJustification() == DT_RIGHT )
		m_justification = 2;

}

