/* ==========================================================================
	Class :			CColumnDialog

	Author :		Johan Rosengren, Abstrakt Mekanik AB

	Date :			2004-07-25

	Purpose :		"CColumnDialog" derives from "CDialog" and is a class for 
					creating/editing individual columns.

	Description :	A standard ClassWizard created dialog.

	Usage :			Call from the grid property dialog.

   ========================================================================*/
#include "stdafx.h"
#include "..\reportcreator.h"
#include "ColumnDialog.h"
#include "UnitConversion.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CColumnDialog dialog


CColumnDialog::CColumnDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CColumnDialog::IDD, pParent)
/* ============================================================
	Function :		CColumnDialog::CColumnDialog
	Description :	Constructor
	Access :		Public

	Return :		void
	Parameters :	CWnd* pParent	-	Parent window
					
	Usage :			

   ============================================================*/
{
	//{{AFX_DATA_INIT(CColumnDialog)
	m_width = _T("");
	m_justification = 0;
	m_name = _T("");
	//}}AFX_DATA_INIT

	m_column = NULL;
	m_color = RGB( 0, 0, 0 );
	ZeroMemory( &m_lf, sizeof( m_lf ) );

	m_measurement = 0;

}

void CColumnDialog::DoDataExchange(CDataExchange* pDX)
/* ============================================================
	Function :		CColumnDialog::DoDataExchange
	Description :	MFC data exchange handler.
	Access :		Protected

	Return :		void
	Parameters :	CDataExchange* pDX	-	Exchange object
					
	Usage :			Called from MFC.

   ============================================================*/
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CColumnDialog)
	DDX_Text(pDX, IDC_EDIT_WIDTH, m_width);
	DDX_Radio(pDX, IDC_RADIO_LEFT, m_justification);
	DDX_Text(pDX, IDC_EDIT_NAME, m_name);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CColumnDialog, CDialog)
	//{{AFX_MSG_MAP(CColumnDialog)
	ON_BN_CLICKED(IDC_BUTTON_FONT, OnButtonFont)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CColumnDialog message handlers

void CColumnDialog::OnButtonFont() 
/* ============================================================
	Function :		CColumnDialog::OnButtonFont
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

	CFontDialog dlg( &m_lf );
	dlg.m_cf.rgbColors = m_color;
	dlg.m_cf.Flags |= CF_EFFECTS;

	if( dlg.DoModal() == IDOK )
	{
		dlg.GetCurrentFont( &m_lf );

		m_lf.lfHeight = dlg.GetSize();
		m_color = dlg.GetColor();
	}
	
}

void CColumnDialog::OnOK() 
/* ============================================================
	Function :		CColumnDialog::OnOK
	Description :	Handler for the dialog OK-button.
	Access :		Protected

	Return :		void
	Parameters :	none

	Usage :			Called from MFC.

   ============================================================*/
{

	UpdateData();

	if( !m_column )
		m_column = new CColumn;
	int width = 0;
	char   *stop;
	double val = _tcstod( m_width, &stop );
	switch( m_measurement )
	{
		case 0:
			width = static_cast< int >( val );
		break;

		case 1:
			width = CUnitConversion::InchesToPixels( val );
		break;
		case 2:
			width = CUnitConversion::CentimeterToPixels( val );
		break;
	}

	m_column->SetName( m_name );
	m_column->SetWidth( width );
	m_column->SetFontName( m_lf.lfFaceName );
	m_column->SetFontSize( m_lf.lfHeight );
	m_column->SetFontBold( ( m_lf.lfWeight != FW_NORMAL ) );
	m_column->SetFontItalic( m_lf.lfItalic );
	m_column->SetFontStrikeout( m_lf.lfStrikeOut );
	m_column->SetFontUnderline( m_lf.lfUnderline );

	m_column->SetFontColor( m_color );
	m_column->SetJustification( m_justification );
	m_column->SetFontCharset( m_lf.lfCharSet );

	CDialog::OnOK();

}

BOOL CColumnDialog::OnInitDialog() 
/* ============================================================
	Function :		CColumnDialog::OnInitDialog
	Description :	Handler for the "WM_INITDIALOG" messag
	Access :		Protected

	Return :		BOOL	-	Always "TRUE"
	Parameters :	none

	Usage :			Called from MFC

   ============================================================*/
{
	CDialog::OnInitDialog();
	
	if( m_column )
	{
		switch( m_measurement )
		{

			case 0:
				m_width.Format( _T( "%i" ), m_column->GetWidth() );
			break;

			case 1:
				m_width.Format( _T( "%.02f" ), CUnitConversion::PixelsToInches( m_column->GetWidth() ) );
			break;

			case 2:
				m_width.Format( _T( "%.02f" ), CUnitConversion::PixelsToCentimeters( m_column->GetWidth() ) );
			break;

		}

		lstrcpy( m_lf.lfFaceName, m_column->GetFontName() );
		m_lf.lfHeight  = m_column->GetFontSize( );
		m_lf.lfWeight = FW_NORMAL;
		if( m_column->GetFontBold())
			m_lf.lfWeight = FW_BOLD;

		m_lf.lfItalic = ( BYTE ) m_column->GetFontItalic();
		m_lf.lfStrikeOut = ( BYTE ) m_column->GetFontStrikeout();
		m_lf.lfUnderline = ( BYTE ) m_column->GetFontUnderline();
		m_lf.lfCharSet = ( BYTE ) m_column->GetFontCharset();

		m_color = m_column->GetFontColor();
		m_justification = m_column->GetJustification();
		m_name = m_column->GetName();

		UpdateData( FALSE );

	}
	
	return TRUE;

}
