/* ==========================================================================
	Class :			CReportEntityLabel

	Author :		Johan Rosengren, Abstrakt Mekanik AB

	Date :			2004-07-25

	Purpose :		"CReportEntityLabel" derives from "CDiagramEntity" and 
					is a class representing a label.

	Description :	The class implements the necessary ovverides and adds 
					attributes to draw a label.

	Usage :			Use as any "CDiagramEntity" object.

   ========================================================================*/
#include "stdafx.h"
#include "ReportEntityLabel.h"
#include "DiagramEditor/Tokenizer.h"
#include "ReportEntitySettings.h"
#include "UnitConversion.h"

CReportEntityLabel::CReportEntityLabel()
/* ============================================================
	Function :		CReportEntityLabel::CReportEntityLabel
	Description :	Constructor
	Access :		Public

	Return :		void
	Parameters :	none

	Usage :			

   ============================================================*/
{

	SetType( _T( "report_label" ) );
	SetTitle( _T( "Label" ) );
	SetFontCharset( DEFAULT_CHARSET );

	CReportEntitySettings::GetRESInstance()->GetFontSettings( this );
	SetPropertyDialog( &m_dlg, IDD_REPORT_DIALOG_LABEL_PROPERTIES );

	SetMinimumSize( CSize( 0, 0 ) );

}

CReportEntityLabel::~CReportEntityLabel()
/* ============================================================
	Function :		CReportEntityLabel::~CReportEntityLabel
	Description :	Destructor
	Access :		Public

	Return :		void
	Parameters :	none

	Usage :			

   ============================================================*/
{

	if( m_dlg.m_hWnd )
		m_dlg.DestroyWindow();

}

CDiagramEntity* CReportEntityLabel::Clone()
/* ============================================================
	Function :		CReportEntityLabel::Clone
	Description :	Creates a new object of this type, copies the data from this object, and returns the new one.
	Access :		Public

	Return :		CDiagramEntity*	-	A clone of this object
	Parameters :	none

	Usage :			Call to clone this object

   ============================================================*/
{

	CReportEntityLabel* obj = new CReportEntityLabel;
	obj->Copy( this );
	return obj;

}

void CReportEntityLabel::Copy( CDiagramEntity* obj )
/* ============================================================
	Function :		CReportEntityLabel::Copy
	Description :	Copies data from "obj" to this object.
	Access :		Public

	Return :		void
	Parameters :	CDiagramEntity* obj	-	Object to copy from
					
	Usage :			Call to copy data from "obj" to this object.

   ============================================================*/
{

	CDiagramEntity::Copy( obj );

	CReportEntityLabel* copy = static_cast< CReportEntityLabel* >( obj );

	SetFontName( copy->GetFontName() );
	SetFontSize( copy->GetFontSize() );
	SetFontBold( copy->GetFontBold() );
	SetFontItalic( copy->GetFontItalic() );
	SetFontUnderline( copy->GetFontUnderline() );
	SetFontStrikeout( copy->GetFontStrikeout() );
	SetFontColor( copy->GetFontColor() );
	SetJustification( copy->GetJustification() );
	SetFontCharset( copy->GetFontCharset() );

}

BOOL CReportEntityLabel::FromString( const CString& str )
/* ============================================================
	Function :		CReportEntityLabel::FromString
	Description :	Sets the data of the object from "str".
	Access :		Public

	Return :		BOOL				-	"TRUE" if the string
											represents an object 
											of this type.
	Parameters :	const CString& str	-	String to parse
					
	Usage :			Call to load objects from a file.

   ============================================================*/
{

	BOOL result = FALSE;
	CString data( str );
	if( LoadFromString( data ) )
	{

		CTokenizer	tok( data );

		CString		fontname;
		int			fontsize;
		BOOL		fontbold;
		BOOL		fontitalic;
		BOOL		fontunderline;
		BOOL		fontstrikeout;
		COLORREF	fontcolor;
		int			justification;
		int			charset;

		int count = 0;

		tok.GetAt( count++, fontname );
		tok.GetAt( count++, fontsize );
		tok.GetAt( count++, fontbold );
		tok.GetAt( count++, fontitalic );
		tok.GetAt( count++, fontunderline );
		tok.GetAt( count++, fontstrikeout );
		tok.GetAt( count++, fontcolor );
		tok.GetAt( count++, justification );
		tok.GetAt( count++, charset );

		SetFontName( fontname );
		SetFontSize( fontsize );
		SetFontBold( fontbold );
		SetFontItalic( fontitalic );
		SetFontUnderline( fontunderline );
		SetFontStrikeout( fontstrikeout );
		SetFontColor( fontcolor );
		SetJustification( justification );
		SetFontCharset( charset );

		int left = CUnitConversion::InchesToPixels( GetLeft() );
		int right = CUnitConversion::InchesToPixels( GetRight() );
		int top = CUnitConversion::InchesToPixels( GetTop() );
		int bottom = CUnitConversion::InchesToPixels( GetBottom() );

		CRect rect( left, top, right, bottom );
		SetRect( rect );

		result = TRUE;

	}

	return result;

}

CString CReportEntityLabel::GetString() const
/* ============================================================
	Function :		CReportEntityLabel::GetString
	Description :	Creates a string representing this object.
	Access :		Public

	Return :		CString	-	Resulting string
	Parameters :	none

	Usage :			Call to save this object to file.

   ============================================================*/
{


	CRect rect = GetRect();

	double oldleft = GetLeft();
	double oldright = GetRight();
	double oldtop = GetTop();
	double oldbottom = GetBottom();

	double left = CUnitConversion::PixelsToInches( rect.left );
	double right = CUnitConversion::PixelsToInches( rect.right );
	double top = CUnitConversion::PixelsToInches( rect.top );
	double bottom = CUnitConversion::PixelsToInches( rect.bottom );

	CReportEntityLabel* const local = const_cast< CReportEntityLabel* const >( this );
	local->SetLeft( left );
	local->SetRight( right );
	local->SetTop( top );
	local->SetBottom( bottom );

	CString str;

	str.Format( _T( ",%s,%i,%i,%i,%i,%i,%i,%i,%i;" ),
		GetFontName( ),
		GetFontSize( ),
		GetFontBold( ),
		GetFontItalic( ),
		GetFontUnderline( ),
		GetFontStrikeout( ),
		GetFontColor( ),
		GetJustification( ),
		GetFontCharset( ) );

	str = GetDefaultGetString() + str;

	local->SetLeft( oldleft );
	local->SetRight( oldright );
	local->SetTop( oldtop );
	local->SetBottom( oldbottom );

	return str;

}

CDiagramEntity* CReportEntityLabel::CreateFromString( const CString & str )
/* ============================================================
	Function :		CReportEntityLabel::CreateFromString
	Description :	Creates and returns an object of this 
					type from "str"
	Access :		Public

	Return :		CDiagramEntity*		-	Object created from "str"
	Parameters :	const CString & str	-	String to create object from
					
	Usage :			Call from a factory class to create 
					instances of this object.

   ============================================================*/
{

	CReportEntityLabel* obj = new CReportEntityLabel;
	if(!obj->FromString( str ) )
	{

		delete obj;
		obj = NULL;

	}

	return obj;

}

CString CReportEntityLabel::GetFontName() const
/* ============================================================
	Function :		CReportEntityLabel::GetFontName
	Description :	Accessor. Getter for "m_fontName".
	Access :		Public
					
	Return :		CString	-	Current font
	Parameters :	none

	Usage :			Call to get the value of "m_fontName".

   ============================================================*/
{

	return m_fontName;

}

void CReportEntityLabel::SetFontName( CString value )
/* ============================================================
	Function :		CReportEntityLabel::SetFontName
	Description :	Accessor. Setter for "m_fontName".
	Access :		Public
					
	Return :		void
	Parameters :	CString value	-	New font
	Usage :			Call to set the value of "m_fontName".

   ============================================================*/
{

	m_fontName = value;

}

int CReportEntityLabel::GetFontSize() const
/* ============================================================
	Function :		CReportEntityLabel::GetFontSize
	Description :	Accessor. Getter for "m_fontSize".
	Access :		Public
					
	Return :		int	- Current size
	Parameters :	none

	Usage :			Call to get the value of "m_fontSize".

   ============================================================*/
{

	return m_fontSize;

}

void CReportEntityLabel::SetFontSize( int value )
/* ============================================================
	Function :		CReportEntityLabel::SetFontSize
	Description :	Accessor. Setter for "m_fontSize".
	Access :		Public
					
	Return :		void
	Parameters :	int value	-	New size
	Usage :			Call to set the value of "m_fontSize".

   ============================================================*/
{

	m_fontSize = value;

}

BOOL CReportEntityLabel::GetFontBold() const
/* ============================================================
	Function :		CReportEntityLabel::GetFontBold
	Description :	Accessor. Getter for "m_fontBold".
	Access :		Public
					
	Return :		BOOL	-	"TRUE" for a bold font
	Parameters :	none

	Usage :			Call to get the value of "m_fontBold".

   ============================================================*/
{

	return m_fontBold;

}

void CReportEntityLabel::SetFontBold( BOOL value )
/* ============================================================
	Function :		CReportEntityLabel::SetFontBold
	Description :	Accessor. Setter for "m_fontBold".
	Access :		Public
					
	Return :		void
	Parameters :	BOOL value	-	"TRUE" for a bold font.
	Usage :			Call to set the value of "m_fontBold".

   ============================================================*/
{

	m_fontBold = value;

}

BOOL CReportEntityLabel::GetFontItalic() const
/* ============================================================
	Function :		CReportEntityLabel::GetFontItalic
	Description :	Accessor. Getter for "m_fontItalic".
	Access :		Public
					
	Return :		BOOL	-	"TRUE" for an italic font
	Parameters :	none

	Usage :			Call to get the value of "m_fontItalic".

   ============================================================*/
{

	return m_fontItalic;

}

void CReportEntityLabel::SetFontItalic( BOOL value )
/* ============================================================
	Function :		CReportEntityLabel::SetFontItalic
	Description :	Accessor. Setter for "m_fontItalic".
	Access :		Public
					
	Return :		void
	Parameters :	BOOL value	-	"TRUE" for an italic font
	Usage :			Call to set the value of "m_fontItalic".

   ============================================================*/
{

	m_fontItalic = value;

}

BOOL CReportEntityLabel::GetFontUnderline() const
/* ============================================================
	Function :		CReportEntityLabel::GetFontUnderline
	Description :	Accessor. Getter for "m_fontUnderline".
	Access :		Public
					
	Return :		BOOL	-	"TRUE" for an underlined font
	Parameters :	none

	Usage :			Call to get the value of "m_fontUnderline".

   ============================================================*/
{

	return m_fontUnderline;

}

void CReportEntityLabel::SetFontUnderline( BOOL value )
/* ============================================================
	Function :		CReportEntityLabel::SetFontUnderline
	Description :	Accessor. Setter for "m_fontUnderline".
	Access :		Public
					
	Return :		void
	Parameters :	BOOL value	-	"TRUE" for an underlined font
	Usage :			Call to set the value of "m_fontUnderline".

   ============================================================*/
{

	m_fontUnderline = value;

}

BOOL CReportEntityLabel::GetFontStrikeout() const
/* ============================================================
	Function :		CReportEntityLabel::GetFontStrikeout
	Description :	Accessor. Getter for "m_fontStrikeout".
	Access :		Public
					
	Return :		BOOL	-	"TRUE" for a strikeout font
	Parameters :	none

	Usage :			Call to get the value of "m_fontStrikeout".

   ============================================================*/
{

	return m_fontStrikeout;

}

void CReportEntityLabel::SetFontStrikeout( BOOL value )
/* ============================================================
	Function :		CReportEntityLabel::SetFontStrikeout
	Description :	Accessor. Setter for "m_fontStrikeout".
	Access :		Public
					
	Return :		void
	Parameters :	BOOL value	-	"TRUE" for a strikeout font
	Usage :			Call to set the value of "m_fontStrikeout".

   ============================================================*/
{

	m_fontStrikeout = value;

}

COLORREF CReportEntityLabel::GetFontColor() const
/* ============================================================
	Function :		CReportEntityLabel::GetFontColor
	Description :	Accessor. Getter for "m_fontColor".
	Access :		Public
					
	Return :		COLORREF	-	Font color
	Parameters :	none

	Usage :			Call to get the value of "m_fontColor".

   ============================================================*/
{

	return m_fontColor;

}

void CReportEntityLabel::SetFontColor( COLORREF value )
/* ============================================================
	Function :		CReportEntityLabel::SetFontColor
	Description :	Accessor. Setter for "m_fontColor".
	Access :		Public
					
	Return :		void
	Parameters :	COLORREF value	-	Font color
	Usage :			Call to set the value of "m_fontColor".

   ============================================================*/
{

	m_fontColor = value;

}

void CReportEntityLabel::Draw( CDC* dc, CRect rect )
/* ============================================================
	Function :		CReportEntityLabel::Draw
	Description :	Draws the object.
	Access :		Public

	Return :		void
	Parameters :	CDC* dc		-	"CDC" to draw to
					CRect rect	-	True (zoomed) rectangle to 
									draw to.
					
	Usage :			Called from "CDiagramEditor::DrawObjects".

   ============================================================*/
{

	int fontheight = CUnitConversion::PointsToPixels( GetFontSize() );

	LOGFONT	lf;
	ZeroMemory( &lf, sizeof( lf ) );

	lstrcpy( lf.lfFaceName, GetFontName() );
	lf.lfHeight = round( static_cast< double >( fontheight ) * GetZoom() );
	lf.lfItalic = ( BYTE ) GetFontItalic();
	lf.lfUnderline = ( BYTE ) GetFontUnderline();
	lf.lfStrikeOut = ( BYTE ) GetFontStrikeout();
	lf.lfCharSet = ( BYTE ) GetFontCharset();
	if( GetFontBold() )
		lf.lfWeight = FW_BOLD;
	else
		lf.lfWeight = FW_NORMAL;

	CFont	font;
	font.CreateFontIndirect( &lf );

	dc->SelectObject( &font );
	int color = dc->SetTextColor( GetFontColor() );
	int mode = dc->SetBkMode( TRANSPARENT );
	int justification = GetJustification();

	CString title = GetTitle();

	dc->DrawText( title, rect, DT_NOPREFIX | DT_WORDBREAK | justification );

	dc->SetBkMode( mode );
	dc->SetTextColor( color );
	dc->SelectStockObject( ANSI_VAR_FONT );

}

void CReportEntityLabel::SetJustification( int justification )
/* ============================================================
	Function :		CReportEntityLabel::SetJustification
	Description :	Setter for the justification attribute.
	Access :		Public

	Return :		void
	Parameters :	int justification	-	New justification
					
	Usage :			Call to set the justification for the flag. 
					Values are the valid flags for "DrawText"

   ============================================================*/
{

	m_justification = justification;

}

int CReportEntityLabel::GetJustification() const
/* ============================================================
	Function :		CReportEntityLabel::GetJustification
	Description :	Getter for the justification attribute
	Access :		Public

	Return :		int	-	Current justification
	Parameters :	none

	Usage :			Call to get the justification for the flag. 
					Values are the valid flags for "DrawText"

   ============================================================*/
{

	return m_justification;

}

void CReportEntityLabel::SetFontCharset( int charset )
/* ============================================================
	Function :		CReportEntityLabel::SetFontCharset
	Description :	Setter for the charset attribute.
	Access :		Public

	Return :		void
	Parameters :	int charset	-	New charset
					
	Usage :			Call to set the charset for the attribute. 

   ============================================================*/
{
	m_charset = charset;
}

int CReportEntityLabel::GetFontCharset() const
/* ============================================================
	Function :		CReportEntityLabel::GetFontCharset
	Description :	Getter for the charset attribute.
	Access :		Public

	Return :		int		-	The current charset
	Parameters :	nothing
					
	Usage :			Call to get the charset attribute. 

   ============================================================*/
{
	return m_charset;
}