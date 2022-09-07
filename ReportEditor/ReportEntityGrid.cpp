/* ==========================================================================
	File :			ReportEntityGrid.cpp
	
	Class :			CReportEntityGrid

	Date :			07/14/04

	Purpose :		"CReportEntityGrid" derives from "CDiagramEntity" and 
					is a class representing a field grid.

	Description :	The class implements the necessary ovverides and adds 
					attributes to draw a grid.

	Usage :			Use as any "CDiagramEntity" object.

   ========================================================================*/

#include "stdafx.h"
#include "ReportEntityGrid.h"
#include "DiagramEditor/Tokenizer.h"
#include "ReportEntitySettings.h"
#include "../resource.h"
#include "UnitConversion.h"

////////////////////////////////////////////////////////////////////
// Public functions
//
CReportEntityGrid::CReportEntityGrid()
/* ============================================================
	Function :		CReportEntityGrid::CReportEntityGrid
	Description :	Constructor.
	Access :		Public
					
	Return :		void
	Parameters :	none

	Usage :			

   ============================================================*/
{

	SetType( _T( "report_grid" ) );
	SetName( _T( "Grid" ) );
	SetLPI( 6 );

	CReportEntitySettings::GetRESInstance()->GetBorderSettings( this );
	CReportEntitySettings::GetRESInstance()->GetColumnLineSettings( this );
	CReportEntitySettings::GetRESInstance()->GetRowLineSettings( this );

	SetPropertyDialog( &m_dlg, IDD_REPORT_DIALOG_GRID_PROPERTIES );

	SetMinimumSize( CSize( 0, 0 ) );

}

CReportEntityGrid::~CReportEntityGrid()
/* ============================================================
	Function :		CReportEntityGrid::~CReportEntityGrid
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

BOOL CReportEntityGrid::GetBorder() const
/* ============================================================
	Function :		CReportEntityGrid::GetBorder
	Description :	Accessor. Getter for "m_border".
	Access :		Public
					
	Return :		BOOL	-	"TRUE" if object displays a border.
	Parameters :	none

	Usage :			Call to get the value of "m_border".

   ============================================================*/
{

	return m_border;

}

void CReportEntityGrid::SetBorder( BOOL value )
/* ============================================================
	Function :		CReportEntityGrid::SetBorder
	Description :	Accessor. Setter for "m_border".
	Access :		Public
					
	Return :		void
	Parameters :	BOOL value	-	"TRUE" for object to display 
									a border.

	Usage :			Call to set the value of "m_border".

   ============================================================*/
{

	m_border = value;

}

int CReportEntityGrid::GetBorderThickness() const
/* ============================================================
	Function :		CReportEntityGrid::GetBorderThickness
	Description :	Accessor. Getter for "m_borderThickness".
	Access :		Public
					
	Return :		int		-	Current border thickness
	Parameters :	none

	Usage :			Call to get the value of "m_borderThickness".

   ============================================================*/
{

	return m_borderThickness;

}

void CReportEntityGrid::SetBorderThickness( int value )
/* ============================================================
	Function :		CReportEntityGrid::SetBorderThickness
	Description :	Accessor. Setter for "m_borderThickness".
	Access :		Public
					
	Return :		void
	Parameters :	int value	-	New border thickness

	Usage :			Call to set the value of "m_borderThickness".

   ============================================================*/
{

	m_borderThickness = value;

}

int CReportEntityGrid::GetBorderStyle() const
/* ============================================================
	Function :		CReportEntityGrid::GetBorderStyle
	Description :	Accessor. Getter for "m_borderStyle".
	Access :		Public
					
	Return :		int		-	Current border style
	Parameters :	none

	Usage :			Call to get the value of "m_borderStyle".

   ============================================================*/
{

	return m_borderStyle;

}

void CReportEntityGrid::SetBorderStyle( int value )
/* ============================================================
	Function :		CReportEntityGrid::SetBorderStyle
	Description :	Accessor. Setter for "m_borderStyle".
	Access :		Public
					
	Return :		void
	Parameters :	int value	-	New border style

	Usage :			Call to set the value of "m_borderStyle".

   ============================================================*/
{

	m_borderStyle = value;

}

COLORREF CReportEntityGrid::GetBorderColor() const
/* ============================================================
	Function :		CReportEntityGrid::GetBorderColor
	Description :	Accessor. Getter for "m_borderColor".
	Access :		Public
					
	Return :		COLORREF	-	Current border color
	Parameters :	none

	Usage :			Call to get the value of "m_borderColor".

   ============================================================*/
{

	return m_borderColor;

}

void CReportEntityGrid::SetBorderColor( COLORREF value )
/* ============================================================
	Function :		CReportEntityGrid::SetBorderColor
	Description :	Accessor. Setter for "m_borderColor".
	Access :		Public
					
	Return :		void
	Parameters :	COLORREF value	-	New border color

	Usage :			Call to set the value of "m_borderColor".

   ============================================================*/
{

	m_borderColor = value;

}

CDiagramEntity* CReportEntityGrid::Clone()
/* ============================================================
	Function :		CReportEntityGrid::Clone
	Description :	Clones this object to a new one.
	Access :		Public
					
	Return :		CDiagramEntity*	-	The new object
	Parameters :	none

	Usage :			Call to clone this object.

   ============================================================*/
{

	CReportEntityGrid* obj = new CReportEntityGrid;
	obj->Copy( this );
	return obj;

}

void CReportEntityGrid::Copy( CDiagramEntity * obj )
/* ============================================================
	Function :		CReportEntityGrid::Copy
	Description :	Copies data from "obj" to this object.
	Access :		Public
					
	Return :		void
	Parameters :	CDiagramEntity * obj	-	Object to copy from

	Usage :			Call to copy data from "obj".

   ============================================================*/
{

	CDiagramEntity::Copy( obj );

	CReportEntityGrid* copy = static_cast< CReportEntityGrid* >( obj );

	SetBorderThickness( copy->GetBorderThickness() );
	SetBorderStyle( copy->GetBorderStyle() );
	SetBorderColor( copy->GetBorderColor() );

	SetColumnLines( copy->GetColumnLines() );
	SetColumnLineThickness( copy->GetColumnLineThickness() );
	SetColumnLineStyle( copy->GetColumnLineStyle() );
	SetColumnLineColor( copy->GetColumnLineColor() );

	SetRowLines( copy->GetRowLines() );
	SetRowLineThickness( copy->GetRowLineThickness() );
	SetRowLineStyle( copy->GetRowLineStyle() );
	SetRowLineColor( copy->GetRowLineColor() );
	SetLPI( copy->GetLPI() );

	m_columns = copy->m_columns;

}

BOOL CReportEntityGrid::FromString( const CString& str )
/* ============================================================
	Function :		CReportEntityGrid::FromString
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

		BOOL		columnlines;
		double		columnlinethickness;
		int			columnlinestyle;
		COLORREF	columnlinecolor;

		BOOL		rowlines;
		double		rowlinethickness;
		int			rowlinestyle;
		COLORREF	rowlinecolor;

		int			lpi;

		CString		columns;

		int	count = 0;
		tok.GetAt( count++, border );
		tok.GetAt( count++, borderthickness );
		tok.GetAt( count++, borderstyle );
		tok.GetAt( count++, bordercolor );

		tok.GetAt( count++, columnlines );
		tok.GetAt( count++, columnlinethickness );
		tok.GetAt( count++, columnlinestyle );
		tok.GetAt( count++, columnlinecolor );

		tok.GetAt( count++, rowlines );
		tok.GetAt( count++, rowlinethickness );
		tok.GetAt( count++, rowlinestyle );
		tok.GetAt( count++, rowlinecolor );
		tok.GetAt( count++, lpi );

		tok.GetAt( count++, columns );

		int bt = CUnitConversion::InchesToPixels( borderthickness );
		int ct = CUnitConversion::InchesToPixels( columnlinethickness );
		int rt = CUnitConversion::InchesToPixels( rowlinethickness );

		SetBorder( border );
		SetBorderThickness( bt );
		SetBorderStyle( borderstyle );
		SetBorderColor( bordercolor );

		SetColumnLines( columnlines );
		SetColumnLineThickness( ct );
		SetColumnLineStyle( columnlinestyle );
		SetColumnLineColor( columnlinecolor );

		SetRowLines( rowlines );
		SetRowLineThickness( rt );
		SetRowLineStyle( rowlinestyle );
		SetRowLineColor( rowlinecolor );

		SetLPI( lpi );

		int left = CUnitConversion::InchesToPixels( GetLeft() );
		int right = CUnitConversion::InchesToPixels( GetRight() );
		int top = CUnitConversion::InchesToPixels( GetTop() );
		int bottom = CUnitConversion::InchesToPixels( GetBottom() );

		CRect rect( left, top, right, bottom );
		SetRect( rect );

		m_columns.FromString( columns );

		result = TRUE;

	}

	return result;

}

CString CReportEntityGrid::GetString() const
/* ============================================================
	Function :		CReportEntityGrid::GetString
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

	CReportEntityGrid* const local = const_cast< CReportEntityGrid* const >( this );
	local->SetLeft( left );
	local->SetRight( right );
	local->SetTop( top );
	local->SetBottom( bottom );

	CString str;

	double bthickness = CUnitConversion::PixelsToInches( GetBorderThickness() );
	double cthickness = CUnitConversion::PixelsToInches( GetColumnLineThickness() );
	double rthickness = CUnitConversion::PixelsToInches( GetRowLineThickness() );

	str.Format( _T( ",%i,%f,%i,%i,%i,%f,%i,%i,%i,%f,%i,%i,%i," ),
		GetBorder(),
		bthickness,
		GetBorderStyle(),
		GetBorderColor(),
		GetColumnLines(),
		cthickness,
		GetColumnLineStyle(),
		GetColumnLineColor(),
		GetRowLines(),
		rthickness,
		GetRowLineStyle(),
		GetRowLineColor(),
		GetLPI()
		);

	str += m_columns.GetString();
	str += _T( ";" );
	str = GetDefaultGetString() + str;

	local->SetLeft( oldleft );
	local->SetRight( oldright );
	local->SetTop( oldtop );
	local->SetBottom( oldbottom );

	return str;

}

CDiagramEntity* CReportEntityGrid::CreateFromString( const CString & str )
/* ============================================================
	Function :		CReportEntityGrid::CreateFromString
	Description :	Creates and returns an object of this 
					type from "str"
	Access :		Public

	Return :		CDiagramEntity*		-	Object created from "str"
	Parameters :	const CString & str	-	String to create object from
					
	Usage :			Call from a factory class to create 
					instances of this object.

   ============================================================*/
{

	CReportEntityGrid* obj = new CReportEntityGrid;
	if(!obj->FromString( str ) )
	{

		delete obj;
		obj = NULL;

	}

	return obj;

}

void CReportEntityGrid::Draw( CDC* dc, CRect rect )
/* ============================================================
	Function :		CReportEntityGrid::Draw
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
	dc->SelectStockObject( WHITE_BRUSH );
	dc->SelectStockObject( WHITE_PEN );

	dc->Rectangle( rect );

	CColumn* restobj = NULL;
	int totalwidth = 0;
	int max = m_columns.GetSize();
	if( max )
	{
		for( int t = 0 ; t < max ; t++ )
		{
			CColumn* obj = m_columns.GetAt( t );
			int column = round( static_cast< double >( obj->GetWidth() ) * GetZoom() );
			totalwidth += column;
			if( obj->GetWidth() == 0 )
				restobj = obj;
		}
	}

	if( restobj && totalwidth < rect.Width() )
	{
		int colwidth = round( static_cast< double >( rect.Width() - totalwidth ) / GetZoom() );
		restobj->SetWidth( colwidth );
	}

	if( GetRowLines() )
	{
		CPen pen;
		pen.CreatePen( m_rowStyle, round( static_cast< double > ( m_rowThickness ) * GetZoom() ), m_rowColor );
		dc->SelectObject( &pen );

		int lineheight = round( dc->GetDeviceCaps( LOGPIXELSY ) / GetLPI() );
		for( int t = rect.top ; t < rect.bottom ; t += lineheight )
		{
			dc->MoveTo( rect.left, t );
			dc->LineTo( rect.right, t );
		}

		dc->SelectStockObject( BLACK_PEN );
	}

	if( GetColumnLines() )
	{
		CPen pen;
		pen.CreatePen( m_columnStyle, round( static_cast< double > ( m_columnThickness ) * GetZoom() ), m_columnColor );
		dc->SelectObject( &pen );
		int max = m_columns.GetSize();
		int width = 0;
		for( int t = 0 ; t < max ; t++ )
		{
			CColumn* obj = m_columns.GetAt( t );
			int column = round( static_cast< double >( obj->GetWidth() ) * GetZoom() );
			CRect rc( rect.left + width, rect.top, width + column, rect.bottom );
			width += column;
			if( width < rect.Width() )
			{
				dc->MoveTo( rect.left + width, rect.top );
				dc->LineTo( rect.left + width, rect.bottom );

			}
		}

		dc->SelectStockObject( BLACK_PEN );

	}

	max = m_columns.GetSize();
	int width = 0;
	for( int t = 0 ; t < max ; t++ )
	{
		CColumn* obj = m_columns.GetAt( t );
		int column = round( static_cast< double >( obj->GetWidth() ) * GetZoom() );
		CRect rc( rect.left + width, rect.top, rect.left + width + column, rect.bottom );
		width += column;
		if( rc.right > rect.right )
			rc.right = rect.right;

		if( rc.right > rc.left )
		{
			rc.InflateRect( -2, 0 );
			CFont* font = GetColumnFont( obj );
			dc->SelectObject( font );
			int color = dc->SetTextColor( obj->GetFontColor() );
			int mode = dc->SetBkMode( TRANSPARENT );
			int justification = obj->GetJustification();
			CString title( obj->GetName() );

			dc->DrawText( title, rc, DT_NOPREFIX | justification );

			dc->SetBkMode( mode );
			dc->SetTextColor( color );
			dc->SelectStockObject( ANSI_VAR_FONT );

			delete font;

		}
	}

	if( GetBorder() )
	{
		pen.CreatePen( GetBorderStyle(), round( static_cast< double > ( GetBorderThickness() ) * GetZoom() ), GetBorderColor() );
		dc->SelectObject( &pen );
	}
	else
		dc->SelectStockObject( NULL_PEN );

	dc->SelectStockObject( NULL_BRUSH );
	dc->Rectangle( rect );

	dc->SelectStockObject( BLACK_PEN );
	dc->SelectStockObject( WHITE_BRUSH );

	if( restobj )
		restobj->SetWidth( 0 );

}

BOOL CReportEntityGrid::GetColumnLines() const
/* ============================================================
	Function :		CReportEntityGrid::GetColumnLines
	Description :	Getter from the column lines flag.
	Access :		Public

	Return :		BOOL	-	"TRUE" if column lines should 
								be displayed.
	Parameters :	none

	Usage :			Call to get the column line flag.

   ============================================================*/
{

	return m_columnLines;

}

void CReportEntityGrid::SetColumnLines( BOOL value )
/* ============================================================
	Function :		CReportEntityGrid::SetColumnLines
	Description :	Setter for the column line flag
	Access :		Public

	Return :		void
	Parameters :	BOOL value	-	"TRUE" if column lines 
									should be displayed.
					
	Usage :			Call to set the column line flag.

   ============================================================*/
{

	m_columnLines = value;

}

int CReportEntityGrid::GetColumnLineThickness() const
/* ============================================================
	Function :		CReportEntityGrid::GetColumnLineThickness
	Description :	Getter for the column line thickness.
	Access :		Public

	Return :		int	-	New column line thickness. 0 means 
							1 pixel
	Parameters :	none

	Usage :			Call to get the column line thickness.

   ============================================================*/
{

	return m_columnThickness;

}

void CReportEntityGrid::SetColumnLineThickness( int value )
/* ============================================================
	Function :		CReportEntityGrid::SetColumnLineThickness
	Description :	Setter for the column line thickness.
	Access :		Public

	Return :		void
	Parameters :	int value	-	New column line thickness. 
									0 means 1 pixel.
					
	Usage :			Call to set the column line thickness.

   ============================================================*/
{

	m_columnThickness = value;

}

int CReportEntityGrid::GetColumnLineStyle() const
/* ============================================================
	Function :		CReportEntityGrid::GetColumnLineStyle
	Description :	Getter column line style.
	Access :		Public

	Return :		int	-	New column line style. Valid values 
							are the constants from "CreatePen"
	Parameters :	none

	Usage :			Call to get the column line style.

   ============================================================*/
{

	return m_columnStyle;

}

void CReportEntityGrid::SetColumnLineStyle( int value )
/* ============================================================
	Function :		CReportEntityGrid::SetColumnLineStyle
	Description :	Setter for the column line style.
	Access :		Public

	Return :		void
	Parameters :	int value	-	New column line style. Valid 
									values are the constants 
									from "CreatePen"
					
	Usage :			Call to set the style for the column lines

   ============================================================*/
{

	m_columnStyle = value;

}

COLORREF CReportEntityGrid::GetColumnLineColor() const
/* ============================================================
	Function :		CReportEntityGrid::GetColumnLineColor
	Description :	Getter for the column line color
	Access :		Public

	Return :		COLORREF	-	Color of the column lines
	Parameters :	none

	Usage :			Call to get the color of the column lines

   ============================================================*/
{

	return m_columnColor;

}

void CReportEntityGrid::SetColumnLineColor( COLORREF value )
/* ============================================================
	Function :		CReportEntityGrid::SetColumnLineColor
	Description :	Setter for the column line color
	Access :		Public

	Return :		void
	Parameters :	COLORREF value	-	New color for the 
										column lines.
					
	Usage :			Call to set the column line colors.

   ============================================================*/
{

	m_columnColor = value;

}

BOOL CReportEntityGrid::GetRowLines() const
/* ============================================================
	Function :		CReportEntityGrid::GetRowLines
	Description :	Getter for the row line flag.
	Access :		Public

	Return :		BOOL	-	"TRUE" if row lines should be 
								displayed.
	Parameters :	none

	Usage :			Call to get the row line flag.

   ============================================================*/
{

	return m_rowLines;

}

void CReportEntityGrid::SetRowLines( BOOL value )
/* ============================================================
	Function :		CReportEntityGrid::SetRowLines
	Description :	Setter for the row line flag.
	Access :		Public

	Return :		void
	Parameters :	BOOL value	-	"TRUE" if row lines should 
									be displayed.
					
	Usage :			Call to set the row line flag.

   ============================================================*/
{

	m_rowLines = value;

}

int CReportEntityGrid::GetRowLineThickness() const
/* ============================================================
	Function :		CReportEntityGrid::GetRowLineThickness
	Description :	Getter for the row line thickness.
	Access :		Public

	Return :		int	-	Row line thickness. 0 means 1 pixels.
	Parameters :	none

	Usage :			Call to get the row line thickness.

   ============================================================*/
{

	return m_rowThickness;

}

void CReportEntityGrid::SetRowLineThickness( int value )
/* ============================================================
	Function :		CReportEntityGrid::SetRowLineThickness
	Description :	Setter for the row line thickness.
	Access :		Public

	Return :		void
	Parameters :	int value	-	Row line thickness. 0 means 
									1 pixels.
					
	Usage :			Call to set the row line thickness.

   ============================================================*/
{

	m_rowThickness = value;

}

int CReportEntityGrid::GetRowLineStyle() const
/* ============================================================
	Function :		CReportEntityGrid::GetRowLineStyle
	Description :	Getter for the row line style.
	Access :		Public

	Return :		int	-	Style. Can be any of the "CreatePen" 
							constants.
	Parameters :	none

	Usage :			Call to get the row line style.

   ============================================================*/
{

	return m_rowStyle;

}

void CReportEntityGrid::SetRowLineStyle( int value )
/* ============================================================
	Function :		CReportEntityGrid::SetRowLineStyle
	Description :	Setter for the row line style.
	Access :		Public

	Return :		void
	Parameters :	int value	-	Style. Can be any of the 
									"CreatePen" constants.
					
	Usage :			Call to set the row line style.

   ============================================================*/
{

	m_rowStyle = value;

}

COLORREF CReportEntityGrid::GetRowLineColor() const
/* ============================================================
	Function :		CReportEntityGrid::GetRowLineColor
	Description :	Getter for the row line color
	Access :		Public

	Return :		COLORREF	-	Row line color
	Parameters :	none

	Usage :			Call to get the row line color

   ============================================================*/
{

	return m_rowColor;

}

void CReportEntityGrid::SetRowLineColor( COLORREF value )
/* ============================================================
	Function :		CReportEntityGrid::SetRowLineColor
	Description :	Setter for the row line color
	Access :		Public

	Return :		void
	Parameters :	COLORREF value	-	New color
					
	Usage :			Call to set the row line color

   ============================================================*/
{

	m_rowColor = value;

}

int CReportEntityGrid::GetLPI() const
/* ============================================================
	Function :		CReportEntityGrid::GetLPI
	Description :	Getter for the lines-per-inch setting of 
					the grid.
	Access :		Public

	Return :		int	-	Lines-per-inch
	Parameters :	none

	Usage :			Call to get the lines per inch to show.

   ============================================================*/
{

	return m_lpi;

}

void CReportEntityGrid::SetLPI( int value )
/* ============================================================
	Function :		CReportEntityGrid::SetLPI
	Description :	Setter for the lines-per-inch setting of 
					the grid.
	Access :		Public

	Return :		void
	Parameters :	int value	-	Lines-per-inch
					
	Usage :			Call to set the lines per inch to show.

   ============================================================*/
{

	m_lpi = value;

}

CFont* CReportEntityGrid::GetColumnFont( CColumn* obj )
/* ============================================================
	Function :		CReportEntityGrid::GetColumnFont
	Description :	Gets the font for "obj".
	Access :		Private

	Return :		CFont*			-	Resulting font
	Parameters :	CColumn* obj	-	Column to get font for
					
	Usage :			Call to get the physical font for the column 
					"obj". The font will be scaled to the 
					current zoom.

   ============================================================*/
{

	int fontheight = CUnitConversion::PointsToPixels( obj->GetFontSize() );

	LOGFONT	lf;
	ZeroMemory( &lf, sizeof( lf ) );

	lstrcpy( lf.lfFaceName, obj->GetFontName() );
	lf.lfHeight = round( static_cast< double>( fontheight ) * GetZoom() );
	lf.lfItalic = ( BYTE ) obj->GetFontItalic();
	lf.lfUnderline = ( BYTE ) obj->GetFontUnderline();
	lf.lfStrikeOut = ( BYTE ) obj->GetFontStrikeout();
	lf.lfCharSet = ( BYTE ) obj->GetFontCharset();
	if( obj->GetFontBold() )
		lf.lfWeight = FW_BOLD;
	else
		lf.lfWeight = FW_NORMAL;

	CFont	*font;
	font = new CFont;
	font->CreateFontIndirect( &lf );

	return font;

}
