/* ==========================================================================
	File :			ReportEntityEllipse.cpp
	
	Class :			CReportEntityEllipse

	Date :			07/14/04

	Purpose :		"CReportEntityEllipse" derives from "CDiagramEntity" and 
					is a class representing a simple ellipse.

	Description :	The class implements the necessary ovverides and adds 
					attributes to draw an ellipse.

	Usage :			Use as any "CDiagramEntity" object.

   ========================================================================*/

#include "stdafx.h"
#include "ReportEntityEllipse.h"
#include "DiagramEditor/Tokenizer.h"
#include "ReportEntitySettings.h"
#include "UnitConversion.h"

////////////////////////////////////////////////////////////////////
// Public functions
//
CReportEntityEllipse::CReportEntityEllipse()
/* ============================================================
	Function :		CReportEntityEllipse::CReportEntityEllipse
	Description :	Constructor.
	Access :		Public
					
	Return :		void
	Parameters :	none

	Usage :			

   ============================================================*/
{

	SetType( _T( "report_ellipse" ) );

	CReportEntitySettings::GetRESInstance()->GetBorderSettings( this );
	CReportEntitySettings::GetRESInstance()->GetFillSettings( this );
	SetPropertyDialog( &m_dlg, IDD_REPORT_DIALOG_ELLIPSE_PROPERTIES );

	SetMinimumSize( CSize( 0, 0 ) );

}

CReportEntityEllipse::~CReportEntityEllipse()
/* ============================================================
	Function :		CReportEntityEllipse::~CReportEntityEllipse
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

BOOL CReportEntityEllipse::GetBorder() const
/* ============================================================
	Function :		CReportEntityEllipse::GetBorder
	Description :	Accessor. Getter for "m_border".
	Access :		Public
					
	Return :		BOOL	-	"TRUE" if the object should 
								display a border.
	Parameters :	none

	Usage :			Call to get the value of "m_border".

   ============================================================*/
{

	return m_border;

}

void CReportEntityEllipse::SetBorder( BOOL value )
/* ============================================================
	Function :		CReportEntityEllipse::SetBorder
	Description :	Accessor. Setter for "m_border".
	Access :		Public
					
	Return :		void
	Parameters :	BOOL value	-	"TRUE" if the object should 
									display a border.

	Usage :			Call to set the value of "m_border".

   ============================================================*/
{

	m_border = value;

}

int CReportEntityEllipse::GetBorderThickness() const
/* ============================================================
	Function :		CReportEntityEllipse::GetBorderThickness
	Description :	Accessor. Getter for "m_borderThickness".
	Access :		Public
					
	Return :		int		-	Current thickness of the border.
	Parameters :	none

	Usage :			Call to get the value of "m_borderThickness".

   ============================================================*/
{

	return m_borderThickness;

}

void CReportEntityEllipse::SetBorderThickness( int value )
/* ============================================================
	Function :		CReportEntityEllipse::SetBorderThickness
	Description :	Accessor. Setter for "m_borderThickness".
	Access :		Public
					
	Return :		void
	Parameters :	int value	-	New thickness of the border.

	Usage :			Call to set the value of "m_borderThickness".

   ============================================================*/
{

	m_borderThickness = value;

}

int CReportEntityEllipse::GetBorderStyle() const
/* ============================================================
	Function :		CReportEntityEllipse::GetBorderStyle
	Description :	Accessor. Getter for "m_borderStyle".
	Access :		Public
					
	Return :		int		-	Current style of the border.
	Parameters :	none

	Usage :			Call to get the value of "m_borderStyle". 
					Can be one of the styles for "CreatePen".

   ============================================================*/
{

	return m_borderStyle;

}

void CReportEntityEllipse::SetBorderStyle( int value )
/* ============================================================
	Function :		CReportEntityEllipse::SetBorderStyle
	Description :	Accessor. Setter for "m_borderStyle".
	Access :		Public
					
	Return :		void
	Parameters :	int value	-	New style for the border.

	Usage :			Call to set the value of "m_borderStyle". 
					Can be one of the styles for "CreatePen".

   ============================================================*/
{

	m_borderStyle = value;

}

COLORREF CReportEntityEllipse::GetBorderColor() const
/* ============================================================
	Function :		CReportEntityEllipse::GetBorderColor
	Description :	Accessor. Getter for "m_borderColor".
	Access :		Public
					
	Return :		COLORREF	-	Current border color
	Parameters :	none

	Usage :			Call to get the value of "m_borderColor".

   ============================================================*/
{

	return m_borderColor;

}

void CReportEntityEllipse::SetBorderColor( COLORREF value )
/* ============================================================
	Function :		CReportEntityEllipse::SetBorderColor
	Description :	Accessor. Setter for "m_borderColor".
	Access :		Public
					
	Return :		void
	Parameters :	COLORREF value	-	New border color

	Usage :			Call to set the value of "m_borderColor".

   ============================================================*/
{

	m_borderColor = value;

}

BOOL CReportEntityEllipse::GetFill() const
/* ============================================================
	Function :		CReportEntityEllipse::GetFill
	Description :	Accessor. Getter for "m_fill".
	Access :		Public
					
	Return :		BOOL	-	"TRUE" if the object should be 
								filled.
	Parameters :	none

	Usage :			Call to get the value of "m_fill".

   ============================================================*/
{

	return m_fill;

}

void CReportEntityEllipse::SetFill( BOOL value )
/* ============================================================
	Function :		CReportEntityEllipse::SetFill
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

COLORREF CReportEntityEllipse::GetFillColor() const
/* ============================================================
	Function :		CReportEntityEllipse::GetFillColor
	Description :	Accessor. Getter for "m_fillColor".
	Access :		Public
					
	Return :		COLORREF	-	Current fill color
	Parameters :	none

	Usage :			Call to get the value of "m_fillColor".

   ============================================================*/
{

	return m_fillColor;

}

void CReportEntityEllipse::SetFillColor( COLORREF value )
/* ============================================================
	Function :		CReportEntityEllipse::SetFillColor
	Description :	Accessor. Setter for "m_fillColor".
	Access :		Public
					
	Return :		void
	Parameters :	COLORREF value	-	New fill color.

	Usage :			Call to set the value of "m_fillColor".

   ============================================================*/
{

	m_fillColor = value;

}

CDiagramEntity* CReportEntityEllipse::Clone()
/* ============================================================
	Function :		CReportEntityEllipse::Clone
	Description :	Clones this object to a new one.
	Access :		Public
					
	Return :		CDiagramEntity*	-	The cloned object.
	Parameters :	none

	Usage :			Call to clone the object.

   ============================================================*/
{

	CReportEntityEllipse* obj = new CReportEntityEllipse;
	obj->Copy( this );
	return obj;

}

void CReportEntityEllipse::Copy( CDiagramEntity * obj )
/* ============================================================
	Function :		CReportEntityEllipse::Copy
	Description :	Copies data from "obj" to this object.
	Access :		Public
					
	Return :		void
	Parameters :	CDiagramEntity * obj	-	The object to 
												copy from

	Usage :			Call to copy data from "obj".

   ============================================================*/
{

	CDiagramEntity::Copy( obj );

	CReportEntityEllipse* copy = static_cast< CReportEntityEllipse* >( obj );

	SetBorderThickness( copy->GetBorderThickness() );
	SetBorderStyle( copy->GetBorderStyle() );
	SetBorderColor( copy->GetBorderColor() );
	SetFill( copy->GetFill() );
	SetFillColor( copy->GetFillColor() );

}

BOOL CReportEntityEllipse::FromString( const CString& str )
/* ============================================================
	Function :		CReportEntityEllipse::FromString
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

CString CReportEntityEllipse::GetString() const
/* ============================================================
	Function :		CReportEntityEllipse::GetString
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

	CReportEntityEllipse* const local = const_cast< CReportEntityEllipse* const >( this );
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

CDiagramEntity* CReportEntityEllipse::CreateFromString( const CString & str )
/* ============================================================
	Function :		CReportEntityEllipse::CreateFromString
	Description :	Creates and returns an object of this 
					type from "str"
	Access :		Public

	Return :		CDiagramEntity*		-	Object created from "str"
	Parameters :	const CString & str	-	String to create object from
					
	Usage :			Call from a factory class to create 
					instances of this object.

   ============================================================*/
{

	CReportEntityEllipse* obj = new CReportEntityEllipse;
	if(!obj->FromString( str ) )
	{

		delete obj;
		obj = NULL;

	}

	return obj;

}

void CReportEntityEllipse::Draw( CDC* dc, CRect rect )
/* ============================================================
	Function :		CReportEntityEllipse::Draw
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

	dc->Ellipse( rect );

	dc->SelectStockObject( BLACK_PEN );
	dc->SelectStockObject( WHITE_BRUSH );

}
