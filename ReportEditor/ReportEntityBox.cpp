/* ==========================================================================
	File :			ReportEntityBox.cpp
	
	Class :			CReportEntityBox

	Date :			07/14/04

	Purpose :		"CReportEntityBox" derives from "CDiagramEntity" and 
					is a class representing a simple box.

	Description :	The class implements the necessary ovverides and adds 
					attributes to draw a box.

	Usage :			Use as any "CDiagramEntity" object.

   ========================================================================*/

#include "stdafx.h"
#include "ReportEntityBox.h"
#include "DiagramEditor/Tokenizer.h"
#include "ReportEntitySettings.h"
#include "UnitConversion.h"

////////////////////////////////////////////////////////////////////
// Public functions
//
CReportEntityBox::CReportEntityBox()
/* ============================================================
	Function :		CReportEntityBox::CReportEntityBox
	Description :	Constructor.
	Access :		Public
					
	Return :		void
	Parameters :	none

	Usage :			

   ============================================================*/
{

	SetType( _T( "report_box" ) );

	CReportEntitySettings::GetRESInstance()->GetBorderSettings( this );
	CReportEntitySettings::GetRESInstance()->GetFillSettings( this );

	SetPropertyDialog( &m_dlg, IDD_REPORT_DIALOG_BOX_PROPERTIES );

	SetMinimumSize( CSize( 0, 0 ) );

}

CReportEntityBox::~CReportEntityBox()
/* ============================================================
	Function :		CReportEntityBox::~CReportEntityBox
	Description :	Destructor.
	Access :		Public
					
	Return :		void
	Parameters :	none

	Usage :			

   ============================================================*/
{

	if( m_dlg.m_hWnd )
		m_dlg.DestroyWindow();

}

BOOL CReportEntityBox::GetBorder() const
/* ============================================================
	Function :		CReportEntityBox::GetBorder
	Description :	Accessor. Getter for "m_border".
	Access :		Public
					
	Return :		BOOL	-	Resulting value
	Parameters :	none

	Usage :			Call to get the value of "m_border".

   ============================================================*/
{

	return m_border;

}

void CReportEntityBox::SetBorder( BOOL value )
/* ============================================================
	Function :		CReportEntityBox::SetBorder
	Description :	Accessor. Setter for "m_border".
	Access :		Public
					
	Return :		void
	Parameters :	BOOL value	-	New value

	Usage :			Call to set the value of "m_border".

   ============================================================*/
{

	m_border = value;

}

int CReportEntityBox::GetBorderThickness() const
/* ============================================================
	Function :		CReportEntityBox::GetBorderThickness
	Description :	Accessor. Getter for "m_borderThickness".
	Access :		Public
					
	Return :		int		-	Current thickness
	Parameters :	none

	Usage :			Call to get the value of "m_borderThickness".

   ============================================================*/
{

	return m_borderThickness;

}

void CReportEntityBox::SetBorderThickness( int value )
/* ============================================================
	Function :		CReportEntityBox::SetBorderThickness
	Description :	Accessor. Setter for "m_borderThickness".
	Access :		Public
					
	Return :		void
	Parameters :	int value	-	New thickness

	Usage :			Call to set the value of "m_borderThickness".

   ============================================================*/
{

	m_borderThickness = value;

}

int CReportEntityBox::GetBorderStyle() const
/* ============================================================
	Function :		CReportEntityBox::GetBorderStyle
	Description :	Accessor. Getter for "m_borderStyle".
	Access :		Public
					
	Return :		int		-	Current style
	Parameters :	none

	Usage :			Call to get the value of "m_borderStyle". 
					Can be one of the styles for "CreatePen"

   ============================================================*/
{

	return m_borderStyle;

}

void CReportEntityBox::SetBorderStyle( int value )
/* ============================================================
	Function :		CReportEntityBox::SetBorderStyle
	Description :	Accessor. Setter for "m_borderStyle".
	Access :		Public
					
	Return :		void
	Parameters :	int value	-	New style

	Usage :			Call to set the value of "m_borderStyle". 
					Can be one of the styles from "CreatePen".

   ============================================================*/
{

	m_borderStyle = value;

}

COLORREF CReportEntityBox::GetBorderColor() const
/* ============================================================
	Function :		CReportEntityBox::GetBorderColor
	Description :	Accessor. Getter for "m_borderColor".
	Access :		Public
					
	Return :		COLORREF	-	Current border color
	Parameters :	none

	Usage :			Call to get the value of "m_borderColor".

   ============================================================*/
{

	return m_borderColor;

}

void CReportEntityBox::SetBorderColor( COLORREF value )
/* ============================================================
	Function :		CReportEntityBox::SetBorderColor
	Description :	Accessor. Setter for "m_borderColor".
	Access :		Public
					
	Return :		void
	Parameters :	COLORREF value	-	New border color

	Usage :			Call to set the value of "m_borderColor".

   ============================================================*/
{

	m_borderColor = value;

}

BOOL CReportEntityBox::GetFill() const
/* ============================================================
	Function :		CReportEntityBox::GetFill
	Description :	Accessor. Getter for "m_fill".
	Access :		Public
					
	Return :		BOOL	-	"TRUE" if the object should 
								be filled.
	Parameters :	none

	Usage :			Call to get the value of "m_fill".

   ============================================================*/
{

	return m_fill;

}

void CReportEntityBox::SetFill( BOOL value )
/* ============================================================
	Function :		CReportEntityBox::SetFill
	Description :	Accessor. Setter for "m_fill".
	Access :		Public
					
	Return :		void
	Parameters :	BOOL value	-	"TRUE" if the object should 
									be filled.

	Usage :			Call to set the value of "m_fill".

   ============================================================*/
{

	m_fill = value;

}

COLORREF CReportEntityBox::GetFillColor() const
/* ============================================================
	Function :		CReportEntityBox::GetFillColor
	Description :	Accessor. Getter for "m_fillColor".
	Access :		Public
					
	Return :		COLORREF	-	Current fill color.
	Parameters :	none

	Usage :			Call to get the value of "m_fillColor".

   ============================================================*/
{

	return m_fillColor;

}

void CReportEntityBox::SetFillColor( COLORREF value )
/* ============================================================
	Function :		CReportEntityBox::SetFillColor
	Description :	Accessor. Setter for "m_fillColor".
	Access :		Public
					
	Return :		void
	Parameters :	COLORREF value	-	New fill color.

	Usage :			Call to set the value of "m_fillColor".

   ============================================================*/
{

	m_fillColor = value;

}

CDiagramEntity* CReportEntityBox::Clone()
/* ============================================================
	Function :		CReportEntityBox::Clone
	Description :	Clones the current object to a new one.
	Access :		Public
					
	Return :		CDiagramEntity*	-	A clone of this object
	Parameters :	none

	Usage :			Call to clone the current object.

   ============================================================*/
{

	CReportEntityBox* obj = new CReportEntityBox;
	obj->Copy( this );
	return obj;

}

void CReportEntityBox::Copy( CDiagramEntity * obj )
/* ============================================================
	Function :		CReportEntityBox::Copy
	Description :	Copies the data from "obj" to this object.
	Access :		Public
					
	Return :		void
	Parameters :	CDiagramEntity * obj	-	Object to copy from

	Usage :			Call to copy data from "obj"

   ============================================================*/
{

	CDiagramEntity::Copy( obj );

	CReportEntityBox* copy = static_cast< CReportEntityBox* >( obj );

	SetBorderThickness( copy->GetBorderThickness() );
	SetBorderStyle( copy->GetBorderStyle() );
	SetBorderColor( copy->GetBorderColor() );
	SetFill( copy->GetFill() );
	SetFillColor( copy->GetFillColor() );

}

BOOL CReportEntityBox::FromString( const CString& str )
/* ============================================================
	Function :		CReportEntityBox::FromString
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

		CTokenizer tok( data );

		BOOL		border;
		double		borderthickness;
		int			borderstyle;
		COLORREF	bordercolor;
		BOOL		fill;
		COLORREF	fillcolor;

		int	count = 0;
		tok.GetAt( count++, border );
		tok.GetAt( count++, borderthickness );
		tok.GetAt( count++, borderstyle );
		tok.GetAt( count++, bordercolor );
		tok.GetAt( count++, fill );
		tok.GetAt( count++, fillcolor );

		int bt = CUnitConversion::InchesToPixels( borderthickness );
		SetBorder( border );
		SetBorderThickness( bt );
		SetBorderStyle( borderstyle );
		SetBorderColor( bordercolor );
		SetFill( fill );
		SetFillColor( fillcolor );

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

CString CReportEntityBox::GetString() const
/* ============================================================
	Function :		CReportEntityBox::GetString
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

	CReportEntityBox* const local = const_cast< CReportEntityBox* const >( this );
	local->SetLeft( left );
	local->SetRight( right );
	local->SetTop( top );
	local->SetBottom( bottom );

	CString str;
	double thickness = CUnitConversion::PixelsToInches( GetBorderThickness() );
	str.Format( _T( ",%i,%f,%i,%i,%i,%i;" ),
		GetBorder( ),
		thickness,
		GetBorderStyle( ),
		GetBorderColor( ),
		GetFill( ),
		GetFillColor( ) );

	str = GetDefaultGetString() + str;

	local->SetLeft( oldleft );
	local->SetRight( oldright );
	local->SetTop( oldtop );
	local->SetBottom( oldbottom );

	return str;

}

CDiagramEntity* CReportEntityBox::CreateFromString( const CString & str )
/* ============================================================
	Function :		CReportEntityBox::CreateFromString
	Description :	Creates and returns an object of this 
					type from "str"
	Access :		Public

	Return :		CDiagramEntity*		-	Object created from "str"
	Parameters :	const CString & str	-	String to create object from
					
	Usage :			Call from a factory class to create 
					instances of this object.

   ============================================================*/
{

	CReportEntityBox* obj = new CReportEntityBox;
	if(!obj->FromString( str ) )
	{

		delete obj;
		obj = NULL;

	}

	return obj;

}

void CReportEntityBox::Draw( CDC* dc, CRect rect )
/* ============================================================
	Function :		CReportEntityBox::Draw
	Description :	Draws the object.
	Access :		Public

	Return :		void
	Parameters :	CDC* dc		-	"CDC" to draw to
					CRect rect	-	True (zoomed) rectangle to 
									draw to.
					
	Usage :			Called from "CDiagramEditor::DrawObjects".

   ============================================================*/
{

	CPen pen;
	if( GetBorder() )
	{
		pen.CreatePen( GetBorderStyle(), round( static_cast< double > ( GetBorderThickness() ) * GetZoom() ), GetBorderColor() );
		dc->SelectObject( &pen );
	}
	else
		dc->SelectStockObject( NULL_PEN );

	CBrush brush;
	if( GetFill() )
	{
		brush.CreateSolidBrush( GetFillColor() );
		dc->SelectObject( &brush );
	}
	else
		dc->SelectStockObject( NULL_BRUSH );

	dc->Rectangle( rect );

	dc->SelectStockObject( BLACK_PEN );
	dc->SelectStockObject( WHITE_BRUSH );

}