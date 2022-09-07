/* ==========================================================================
	Class :			CReportEntityField

	Author :		Johan Rosengren, Abstrakt Mekanik AB

	Date :			2004-07-25

	Purpose :		"CReportEntityField" derives from "CDiagramEntity" and 
					is a class representing a dynamic field.

	Description :	The class implements the necessary ovverides and adds 
					attributes to draw a field.

	Usage :			Use as any "CDiagramEntity" object.


   ========================================================================*/
#include "stdafx.h"
#include "ReportEntityField.h"
#include "DiagramEditor/Tokenizer.h"
#include "ReportEntitySettings.h"
#include "UnitConversion.h"

CReportEntityField::CReportEntityField()
/* ============================================================
	Function :		CReportEntityField::CReportEntityField
	Description :	Constructor
	Access :		Public

	Return :		void
	Parameters :	none

	Usage :			

   ============================================================*/
{

	SetType( _T( "report_field" ) );
	SetName( _T( "Fieldname" ) );
	SetFontCharset( DEFAULT_CHARSET );

	CReportEntitySettings::GetRESInstance()->GetFontSettings( this );
	SetPropertyDialog( &m_dlg, IDD_REPORT_DIALOG_FIELD_PROPERTIES );

	SetMinimumSize( CSize( 0, 0 ) );

}

CReportEntityField::~CReportEntityField()
/* ============================================================
	Function :		CReportEntityField::~CReportEntityField
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

CDiagramEntity* CReportEntityField::Clone()
/* ============================================================
	Function :		CReportEntityField::Clone
	Description :	Creates a new object of this type, copies the data from this object, and returns the new one.
	Access :		Public

	Return :		CDiagramEntity*	-	
	Parameters :	none

	Usage :			Call to clone this object

   ============================================================*/
{

	CReportEntityField* obj = new CReportEntityField;
	obj->Copy( this );
	return obj;

}

void CReportEntityField::Copy( CDiagramEntity* obj )
/* ============================================================
	Function :		CReportEntityField::Copy
	Description :	Copies the data from "obj" to this object.
	Access :		Public

	Return :		void
	Parameters :	CDiagramEntity* obj	-	Object to copy from
					
	Usage :			Call to copy data from "obj" to this object.

   ============================================================*/
{

	CDiagramEntity::Copy( obj );

	CReportEntityField* copy = static_cast< CReportEntityField* >( obj );

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

BOOL CReportEntityField::FromString( const CString& str )
/* ============================================================
	Function :		CReportEntityField::FromString
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

CString CReportEntityField::GetString() const
/* ============================================================
	Function :		CReportEntityField::GetString
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

	CReportEntityField* const local = const_cast< CReportEntityField* const >( this );
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

CDiagramEntity* CReportEntityField::CreateFromString( const CString & str )
/* ============================================================
	Function :		CReportEntityField::CreateFromString
	Description :	Creates and returns an object of this 
					type from "str"
	Access :		Public

	Return :		CDiagramEntity*		-	Object created from "str"
	Parameters :	const CString & str	-	String to create object from
					
	Usage :			Call from a factory class to create 
					instances of this object.

   ============================================================*/
{

	CReportEntityField* obj = new CReportEntityField;
	if(!obj->FromString( str ) )
	{

		delete obj;
		obj = NULL;

	}

	return obj;

}

CString CReportEntityField::GetFontName() const
/* ============================================================
	Function :		CReportEntityField::GetFontName
	Description :	Accessor. Getter for "m_fontName".
	Access :		Public
					
	Return :		CString	-	Current font name
	Parameters :	none

	Usage :			Call to get the value of "m_fontName".

   ============================================================*/
{

	return m_fontName;

}

void CReportEntityField::SetFontName( CString value )
/* ============================================================
	Function :		CReportEntityField::SetFontName
	Description :	Accessor. Setter for "m_fontName".
	Access :		Public
					
	Return :		void
	Parameters :	CString value	-	New font name

	Usage :			Call to set the value of "m_fontName".

   ============================================================*/
{

	m_fontName = value;

}

int CReportEntityField::GetFontSize() const
/* ============================================================
	Function :		CReportEntityField::GetFontSize
	Description :	Accessor. Getter for "m_fontSize".
	Access :		Public
					
	Return :		int		-	Current font size
	Parameters :	none

	Usage :			Call to get the value of "m_fontSize".

   ============================================================*/
{

	return m_fontSize;

}

void CReportEntityField::SetFontSize( int value )
/* ============================================================
	Function :		CReportEntityField::SetFontSize
	Description :	Accessor. Setter for "m_fontSize".
	Access :		Public
					
	Return :		void
	Parameters :	int value	-	New font size

	Usage :			Call to set the value of "m_fontSize".

   ============================================================*/
{

	m_fontSize = value;

}

BOOL CReportEntityField::GetFontBold() const
/* ============================================================
	Function :		CReportEntityField::GetFontBold
	Description :	Accessor. Getter for "m_fontBold".
	Access :		Public
					
	Return :		BOOL	-	"TRUE" if font is bold
	Parameters :	none

	Usage :			Call to get the value of "m_fontBold".

   ============================================================*/
{

	return m_fontBold;

}

void CReportEntityField::SetFontBold( BOOL value )
/* ============================================================
	Function :		CReportEntityField::SetFontBold
	Description :	Accessor. Setter for "m_fontBold".
	Access :		Public
					
	Return :		void
	Parameters :	BOOL value	-	"TRUE" if font is bold

	Usage :			Call to set the value of "m_fontBold".

   ============================================================*/
{

	m_fontBold = value;

}

BOOL CReportEntityField::GetFontItalic() const
/* ============================================================
	Function :		CReportEntityField::GetFontItalic
	Description :	Accessor. Getter for "m_fontItalic".
	Access :		Public
					
	Return :		BOOL	-	"TRUE" if font is italic
	Parameters :	none

	Usage :			Call to get the value of "m_fontItalic".

   ============================================================*/
{

	return m_fontItalic;

}

void CReportEntityField::SetFontItalic( BOOL value )
/* ============================================================
	Function :		CReportEntityField::SetFontItalic
	Description :	Accessor. Setter for "m_fontItalic".
	Access :		Public
					
	Return :		void
	Parameters :	BOOL value	-	"TRUE" if font is italic.

	Usage :			Call to set the value of "m_fontItalic".

   ============================================================*/
{

	m_fontItalic = value;

}

BOOL CReportEntityField::GetFontUnderline() const
/* ============================================================
	Function :		CReportEntityField::GetFontUnderline
	Description :	Accessor. Getter for "m_fontUnderline".
	Access :		Public
					
	Return :		BOOL	-	"TRUE" if font is underlined.
	Parameters :	none

	Usage :			Call to get the value of "m_fontUnderline".

   ============================================================*/
{

	return m_fontUnderline;

}

void CReportEntityField::SetFontUnderline( BOOL value )
/* ============================================================
	Function :		CReportEntityField::SetFontUnderline
	Description :	Accessor. Setter for "m_fontUnderline".
	Access :		Public
					
	Return :		void
	Parameters :	BOOL value	-	"TRUE" if font is underlined.

	Usage :			Call to set the value of "m_fontUnderline".

   ============================================================*/
{

	m_fontUnderline = value;

}

BOOL CReportEntityField::GetFontStrikeout() const
/* ============================================================
	Function :		CReportEntityField::GetFontStrikeout
	Description :	Accessor. Getter for "m_fontStrikeout".
	Access :		Public
					
	Return :		BOOL	-	"TRUE" for a strikeout font
	Parameters :	none

	Usage :			Call to get the value of "m_fontStrikeout".

   ============================================================*/
{

	return m_fontStrikeout;

}

void CReportEntityField::SetFontStrikeout( BOOL value )
/* ============================================================
	Function :		CReportEntityField::SetFontStrikeout
	Description :	Accessor. Setter for "m_fontStrikeout".
	Access :		Public
					
	Return :		void
	Parameters :	BOOL value	-	"TRUE" for a strikeout font

	Usage :			Call to set the value of "m_fontStrikeout".

   ============================================================*/
{

	m_fontStrikeout = value;

}

COLORREF CReportEntityField::GetFontColor() const
/* ============================================================
	Function :		CReportEntityField::GetFontColor
	Description :	Accessor. Getter for "m_fontColor".
	Access :		Public
					
	Return :		COLORREF	-	Current font color
	Parameters :	none

	Usage :			Call to get the value of "m_fontColor".

   ============================================================*/
{

	return m_fontColor;

}

void CReportEntityField::SetFontColor( COLORREF value )
/* ============================================================
	Function :		CReportEntityField::SetFontColor
	Description :	Accessor. Setter for "m_fontColor".
	Access :		Public
					
	Return :		void
	Parameters :	COLORREF value	-	New font color

	Usage :			Call to set the value of "m_fontColor".

   ============================================================*/
{

	m_fontColor = value;

}

void CReportEntityField::Draw( CDC* dc, CRect rect )
/* ============================================================
	Function :		CReportEntityField::Draw
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
	lf.lfHeight = round( static_cast< double>( fontheight ) * GetZoom() );
	lf.lfItalic = static_cast< BYTE >( GetFontItalic() );
	lf.lfUnderline = ( BYTE ) GetFontUnderline();
	lf.lfStrikeOut = ( BYTE ) GetFontStrikeout();
	lf.lfCharSet = ( unsigned char ) GetFontCharset();
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

	dc->DrawText( GetName(), rect, DT_NOPREFIX | DT_WORDBREAK | justification );

	dc->SetBkMode( mode );
	dc->SetTextColor( color );
	dc->SelectStockObject( ANSI_VAR_FONT );

}

void CReportEntityField::SetJustification( int justification )
/* ============================================================
	Function :		CReportEntityField::SetJustification
	Description :	Setter for the justification attribute.
	Access :		Public

	Return :		void
	Parameters :	int justification	-	New justification.
					
	Usage :			Call to set the justification for the flag. 
					Values are the valid flags for "DrawText"

   ============================================================*/
{

	m_justification = justification;

}

int CReportEntityField::GetJustification() const
/* ============================================================
	Function :		CReportEntityField::GetJustification
	Description :	Getter for the justification attribute.
	Access :		Public

	Return :		int		-	Current justification.
	Parameters :	none

	Usage :			Call to get the justification for the flag. 
					Values are the valid flags for "DrawText"

   ============================================================*/
{

	return m_justification;

}

void CReportEntityField::SetFontCharset( int value )
/* ============================================================
	Function :		CReportEntityField::SetFontCharset
	Description :	Setter for the charset attribute.
	Access :		Public

	Return :		void
	Parameters :	int charset	-	New charset
					
	Usage :			Call to set the charset for the attribute. 

   ============================================================*/
{
	m_charset = value;
}

int CReportEntityField::GetFontCharset() const
/* ============================================================
	Function :		CReportEntityField::GetFontCharset
	Description :	Getter for the charset attribute.
	Access :		Public

	Return :		int		-	The current charset
	Parameters :	nothing
					
	Usage :			Call to get the charset attribute. 

   ============================================================*/
{
	return m_charset;
}
