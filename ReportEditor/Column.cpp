/* ==========================================================================
	File :			Column.cpp
	
	Class :			CColumn

	Date :			07/18/04

	Purpose :		"CColumn", derived from "CObject", represents a single 
					column in a grid.

	Description :	The class is a simple data class kept by a container 
					for the grid drawing object.

	Usage :			Create and add to a "CColumnContainer".

   ========================================================================*/

#include "stdafx.h"
#include "Column.h"
#include "ReportEntitySettings.h"
#include "DiagramEditor/Tokenizer.h"
#include "UnitConversion.h"

////////////////////////////////////////////////////////////////////
// Public functions
//

CColumn::CColumn()
/* ============================================================
	Function :		CColumn::CColumn
	Description :	Constructor.
	Access :		Public
					
	Return :		void
	Parameters :	none

	Usage :			

   ============================================================*/
{

	m_width = 0;
	m_charset = DEFAULT_CHARSET;
	CReportEntitySettings::GetRESInstance()->GetFontSettings( this );

}

CColumn::~CColumn()
/* ============================================================
	Function :		CColumn::~CColumn
	Description :	Destructor.
	Access :		Public
					
	Return :		void
	Parameters :	none

	Usage :			

   ============================================================*/
{
}

int CColumn::GetWidth() const
/* ============================================================
	Function :		CColumn::GetWidth
	Description :	Accessor. Getter for "m_width".
	Access :		Public
					
	Return :		int	-	Value of the attribute
	Parameters :	none

	Usage :			Call to get the value of "m_width".

   ============================================================*/
{

	return m_width;

}

void CColumn::SetWidth( int value )
/* ============================================================
	Function :		CColumn::SetWidth
	Description :	Accessor. Setter for "m_width".
	Access :		Public
					
	Return :		void
	Parameters :	int value	-	New value

	Usage :			Call to set the value of "m_width".

   ============================================================*/
{

	m_width = value;

}

CString CColumn::GetFontName() const
/* ============================================================
	Function :		CColumn::GetFontName
	Description :	Accessor. Getter for "m_fontName".
	Access :		Public
					
	Return :		CString	-	The value of the attribute.
	Parameters :	none

	Usage :			Call to get the value of "m_fontName".

   ============================================================*/
{

	return m_fontName;

}

void CColumn::SetFontName( CString value )
/* ============================================================
	Function :		CColumn::SetFontName
	Description :	Accessor. Setter for "m_fontName".
	Access :		Public
					
	Return :		void
	Parameters :	CString value	-	The value of the attribute.

	Usage :			Call to set the value of "m_fontName".

   ============================================================*/
{

	m_fontName = value;

}

CString CColumn::GetName() const
/* ============================================================
	Function :		CColumn::GetName
	Description :	Accessor. Getter for "m_name".
	Access :		Public
					
	Return :		CString	-	The value of the attribute.
	Parameters :	none

	Usage :			Call to get the value of "m_name".

   ============================================================*/
{

	return m_name;

}

void CColumn::SetName( CString value )
/* ============================================================
	Function :		CColumn::SetName
	Description :	Accessor. Setter for "m_name".
	Access :		Public
					
	Return :		void
	Parameters :	CString value	-	The value of the attribute.

	Usage :			Call to set the value of "m_name".

   ============================================================*/
{

	m_name = value;

}

int CColumn::GetFontSize() const
/* ============================================================
	Function :		CColumn::GetFontSize
	Description :	Accessor. Getter for "m_fontSize".
	Access :		Public
					
	Return :		int	-	The value of the attribute.
	Parameters :	none

	Usage :			Call to get the value of "m_fontSize".

   ============================================================*/
{

	return m_fontSize;

}

void CColumn::SetFontSize( int value )
/* ============================================================
	Function :		CColumn::SetFontSize
	Description :	Accessor. Setter for "m_fontSize".
	Access :		Public
					
	Return :		void
	Parameters :	int value	-	The value of the attribute.

	Usage :			Call to set the value of "m_fontSize".

   ============================================================*/
{

	m_fontSize = value;

}

BOOL CColumn::GetFontItalic() const
/* ============================================================
	Function :		CColumn::GetFontItalic
	Description :	Accessor. Getter for "m_fontItalic".
	Access :		Public
					
	Return :		BOOL	-	The value of the attribute.
	Parameters :	none

	Usage :			Call to get the value of "m_fontItalic".

   ============================================================*/
{

	return m_fontItalic;

}

void CColumn::SetFontItalic( BOOL value )
/* ============================================================
	Function :		CColumn::SetFontItalic
	Description :	Accessor. Setter for "m_fontItalic".
	Access :		Public
					
	Return :		void
	Parameters :	BOOL value	-	The value of the attribute.

	Usage :			Call to set the value of "m_fontItalic".

   ============================================================*/
{

	m_fontItalic = value;

}

BOOL CColumn::GetFontUnderline() const
/* ============================================================
	Function :		CColumn::GetFontUnderline
	Description :	Accessor. Getter for "m_fontUnderline".
	Access :		Public
					
	Return :		BOOL	-	The value of the attribute.
	Parameters :	none

	Usage :			Call to get the value of "m_fontUnderline".

   ============================================================*/
{

	return m_fontUnderline;

}

void CColumn::SetFontUnderline( BOOL value )
/* ============================================================
	Function :		CColumn::SetFontUnderline
	Description :	Accessor. Setter for "m_fontUnderline".
	Access :		Public
					
	Return :		void
	Parameters :	BOOL value	-	The value of the attribute.

	Usage :			Call to set the value of "m_fontUnderline".

   ============================================================*/
{

	m_fontUnderline = value;

}

BOOL CColumn::GetFontBold() const
/* ============================================================
	Function :		CColumn::GetFontBold
	Description :	Accessor. Getter for "m_fontBold".
	Access :		Public
					
	Return :		BOOL	-	The value of the attribute.
	Parameters :	none

	Usage :			Call to get the value of "m_fontBold".

   ============================================================*/
{

	return m_fontBold;

}

void CColumn::SetFontBold( BOOL value )
/* ============================================================
	Function :		CColumn::SetFontBold
	Description :	Accessor. Setter for "m_fontBold".
	Access :		Public
					
	Return :		void
	Parameters :	BOOL value	-	The value of the attribute.

	Usage :			Call to set the value of "m_fontBold".

   ============================================================*/
{

	m_fontBold = value;

}

BOOL CColumn::GetFontStrikeout() const
/* ============================================================
	Function :		CColumn::GetFontStrikeOut
	Description :	Accessor. Getter for "m_fontStrikeOut".
	Access :		Public
					
	Return :		BOOL	-	The value of the attribute.
	Parameters :	none

	Usage :			Call to get the value of "m_fontStrikeOut".

   ============================================================*/
{

	return m_fontStrikeOut;

}

void CColumn::SetFontStrikeout( BOOL value )
/* ============================================================
	Function :		CColumn::SetFontStrikeOut
	Description :	Accessor. Setter for "m_fontStrikeOut".
	Access :		Public
					
	Return :		void
	Parameters :	BOOL value	-	The value of the attribute.

	Usage :			Call to set the value of "m_fontStrikeOut".

   ============================================================*/
{

	m_fontStrikeOut = value;

}

COLORREF CColumn::GetFontColor() const
/* ============================================================
	Function :		CColumn::GetFontColor
	Description :	Accessor. Getter for "m_fontColor".
	Access :		Public
					
	Return :		COLORREF	-	The value of the attribute.
	Parameters :	none

	Usage :			Call to get the value of "m_fontColor".

   ============================================================*/
{

	return m_fontColor;

}

void CColumn::SetFontColor( COLORREF value )
/* ============================================================
	Function :		CColumn::SetFontColor
	Description :	Accessor. Setter for "m_fontColor".
	Access :		Public
					
	Return :		void
	Parameters :	COLORREF value	-	The value of the attribute.

	Usage :			Call to set the value of "m_fontColor".

   ============================================================*/
{

	m_fontColor = value;

}

int CColumn::GetJustification() const
/* ============================================================
	Function :		CColumn::GetJustification
	Description :	Accessor. Getter for "m_justification".
	Access :		Public
					
	Return :		int	-	The value of the attribute.
	Parameters :	none

	Usage :			Call to get the value of "m_justification".

   ============================================================*/
{

	return m_justification;

}

void CColumn::SetJustification( int value )
/* ============================================================
	Function :		CColumn::SetJustification
	Description :	Accessor. Setter for "m_justification".
	Access :		Public
					
	Return :		void
	Parameters :	int value	-	The value of the attribute.

	Usage :			Call to set the value of "m_justification".

   ============================================================*/
{

	m_justification = value;

}

CColumn* CColumn::Clone()
/* ============================================================
	Function :		CColumn::Clone
	Description :	Creates a new object of this type, copies 
					the data from this object, and returns the 
					new one.
	Access :		Public

	Return :		CColumn*	-	New object
	Parameters :	none

	Usage :			Call to clone this object

   ============================================================*/
{

	CColumn* obj = new CColumn;

	obj->SetWidth( GetWidth() );
	obj->SetFontName( GetFontName() );
	obj->SetFontSize( GetFontSize() );
	obj->SetFontItalic( GetFontItalic() );
	obj->SetFontUnderline( GetFontUnderline() );
	obj->SetFontBold( GetFontBold() );
	obj->SetFontStrikeout( GetFontStrikeout() );
	obj->SetFontColor( GetFontColor() );
	obj->SetJustification( GetJustification() );
	obj->SetName( GetName() );
	obj->SetFontCharset( GetFontCharset() );

	return obj;

}

void CColumn::FromString( const CString& str )
/* ============================================================
	Function :		CColumn::FromString
	Description :	Sets the object data from "str".
	Access :		Public

	Return :		void
	Parameters :	const CString& str	-	String to set data 
											from.
					
	Usage :			Call to create objects from a file.

   ============================================================*/
{

	CTokenizer tok( str, _T( "#" ) );

	double		width;
	CString		fontName;
	int			fontSize;
	BOOL		fontItalic;
	BOOL		fontUnderline;
	BOOL		fontBold;
	BOOL		fontStrikeout;
	COLORREF	fontColor;
	int			justification;
	CString		name;
	int			charset;

	int count = 0;

	tok.GetAt( count++, width );
	tok.GetAt( count++, fontName );
	tok.GetAt( count++, fontSize );
	tok.GetAt( count++, fontItalic );
	tok.GetAt( count++, fontUnderline );
	tok.GetAt( count++, fontBold );
	tok.GetAt( count++, fontStrikeout );
	tok.GetAt( count++, fontColor );
	tok.GetAt( count++, justification );
	tok.GetAt( count++, name );
	tok.GetAt( count++, charset );

	int pixelwidth = CUnitConversion::InchesToPixels( width );

	SetWidth( pixelwidth );
	SetFontName( fontName );
	SetFontSize( fontSize );
	SetFontItalic( fontItalic );
	SetFontUnderline( fontUnderline );
	SetFontBold( fontBold );
	SetFontStrikeout( fontStrikeout );
	SetFontColor( fontColor );
	SetJustification( justification );
	SetName( name );
	SetFontCharset( charset );

}

CString CColumn::GetString() const
/* ============================================================
	Function :		CColumn::GetString
	Description :	Creates a string representing this object.
	Access :		Public

	Return :		CString	-	Resulting string
	Parameters :	none

	Usage :			Call to save this object to file.

   ============================================================*/
{

	CString result;
	double width = CUnitConversion::PixelsToInches( GetWidth() );

	result.Format( _T( "%f#%s#%i#%i#%i#%i#%i#%i#%i#%s#%i" ), 
		width,
		GetFontName(),
		GetFontSize(),
		GetFontItalic(),
		GetFontUnderline(),
		GetFontBold(),
		GetFontStrikeout(),
		GetFontColor(),
		GetJustification(),
		GetName(),
		GetFontCharset()
	);

	return result;

}

int CColumn::GetFontCharset() const
/* ============================================================
	Function :		CColumn::GetFontCharset
	Description :	Accessor. Getter for "m_charset".
	Access :		Public
					
	Return :		void
	Parameters :	int value	-	The value of the attribute.

	Usage :			Call to get the value of "m_charset".

   ============================================================*/
{
	return m_charset;
}

void CColumn::SetFontCharset( int charset )
/* ============================================================
	Function :		CColumn::SetFontCharset
	Description :	Accessor. Setter for "m_charset".
	Access :		Public
					
	Return :		void
	Parameters :	int value	-	The value of the attribute.

	Usage :			Call to set the value of "m_charset".

   ============================================================*/
{
	m_charset = charset;
}
