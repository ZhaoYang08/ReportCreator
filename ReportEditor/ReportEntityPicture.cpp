/* ==========================================================================
	File :			ReportEntityPicture.cpp
	
	Class :			CReportEntityPicture

	Date :			07/14/04

	Purpose :		"CReportEntityPicture" derives from "CDiagramEntity" and 
					is a class representing a bmp picture.

	Description :	The class implements the necessary ovverides and adds 
					attributes to draw a picture.

	Usage :			Use as any "CDiagramEntity" object.
   ========================================================================
					23/9 2005	Added copying the border in Copy (Alex Evans)

   ========================================================================*/

#include "stdafx.h"
#include "ReportEntityPicture.h"
#include "DiagramEditor/Tokenizer.h"
#include "ReportEntitySettings.h"
#include "StringHelpers.h"
#include "UnitConversion.h"

////////////////////////////////////////////////////////////////////
// Public functions
//
CReportEntityPicture::CReportEntityPicture()
/* ============================================================
	Function :		CReportEntityPicture::CReportEntityPicture
	Description :	Constructor.
	Access :		Public
					
	Return :		void
	Parameters :	none

	Usage :			

   ============================================================*/
{

	SetType( _T( "report_picture" ) );

	CReportEntitySettings::GetRESInstance()->GetBorderSettings( this );

	SetPropertyDialog( &m_dlg, IDD_REPORT_DIALOG_PICTURE_PROPERTIES );

	m_bitmap = NULL;

	SetMinimumSize( CSize( 0, 0 ) );

}

CReportEntityPicture::~CReportEntityPicture()
/* ============================================================
	Function :		CReportEntityPicture::~CReportEntityPicture
	Description :	Destructor.
	Access :		Public
					
	Return :		void
	Parameters :	none

	Usage :			

   ============================================================*/
{

	if( m_dlg.m_hWnd )
		m_dlg.DestroyWindow();

	if( m_bitmap )
		::DeleteObject( m_bitmap );

}

BOOL CReportEntityPicture::GetBorder() const
/* ============================================================
	Function :		CReportEntityPicture::GetBorder
	Description :	Accessor. Getter for "m_border".
	Access :		Public
					
	Return :		BOOL	-	"TRUE" if the border should be 
								displayed.
	Parameters :	none

	Usage :			Call to get the value of "m_border".

   ============================================================*/
{

	return m_border;

}

void CReportEntityPicture::SetBorder( BOOL value )
/* ============================================================
	Function :		CReportEntityPicture::SetBorder
	Description :	Accessor. Setter for "m_border".
	Access :		Public
					
	Return :		void
	Parameters :	BOOL value	-	"TRUE" if borders should be 
									displayed.

	Usage :			Call to set the value of "m_border".

   ============================================================*/
{

	m_border = value;

}

int CReportEntityPicture::GetBorderThickness() const
/* ============================================================
	Function :		CReportEntityPicture::GetBorderThickness
	Description :	Accessor. Getter for "m_borderThickness".
	Access :		Public
					
	Return :		int		-	Current thickness
	Parameters :	none

	Usage :			Call to get the value of "m_borderThickness".

   ============================================================*/
{

	return m_borderThickness;

}

void CReportEntityPicture::SetBorderThickness( int value )
/* ============================================================
	Function :		CReportEntityPicture::SetBorderThickness
	Description :	Accessor. Setter for "m_borderThickness".
	Access :		Public
					
	Return :		void
	Parameters :	int value	-	New thickness

	Usage :			Call to set the value of "m_borderThickness".

   ============================================================*/
{

	m_borderThickness = value;

}

int CReportEntityPicture::GetBorderStyle() const
/* ============================================================
	Function :		CReportEntityPicture::GetBorderStyle
	Description :	Accessor. Getter for "m_borderStyle".
	Access :		Public
					
	Return :		int		-	Current style
	Parameters :	none

	Usage :			Call to get the value of "m_borderStyle".

   ============================================================*/
{

	return m_borderStyle;

}

void CReportEntityPicture::SetBorderStyle( int value )
/* ============================================================
	Function :		CReportEntityPicture::SetBorderStyle
	Description :	Accessor. Setter for "m_borderStyle".
	Access :		Public
					
	Return :		void
	Parameters :	int value	-	New style

	Usage :			Call to set the value of "m_borderStyle".

   ============================================================*/
{

	m_borderStyle = value;

}

COLORREF CReportEntityPicture::GetBorderColor() const
/* ============================================================
	Function :		CReportEntityPicture::GetBorderColor
	Description :	Accessor. Getter for "m_borderColor".
	Access :		Public
					
	Return :		COLORREF	-	Current color
	Parameters :	none

	Usage :			Call to get the value of "m_borderColor".

   ============================================================*/
{

	return m_borderColor;

}

void CReportEntityPicture::SetBorderColor( COLORREF value )
/* ============================================================
	Function :		CReportEntityPicture::SetBorderColor
	Description :	Accessor. Setter for "m_borderColor".
	Access :		Public
					
	Return :		void
	Parameters :	COLORREF value	-	New color

	Usage :			Call to set the value of "m_borderColor".

   ============================================================*/
{

	m_borderColor = value;

}

CDiagramEntity* CReportEntityPicture::Clone()
/* ============================================================
	Function :		CReportEntityPicture::Clone
	Description :	Clones the current object to a new one.
	Access :		Public
					
	Return :		CDiagramEntity*	-	New object.
	Parameters :	none

	Usage :			Call to clone this object to a new one

   ============================================================*/
{

	CReportEntityPicture* obj = new CReportEntityPicture;
	obj->Copy( this );
	return obj;

}

void CReportEntityPicture::Copy( CDiagramEntity * obj )
/* ============================================================
	Function :		CReportEntityPicture::Copy
	Description :	Copies data from "obj" to this object.
	Access :		Public
					
	Return :		void
	Parameters :	CDiagramEntity * obj	-	Object to copy from

	Usage :			Call to copy data from "obj" to this object.

   ============================================================*/
{

	CDiagramEntity::Copy( obj );

	CReportEntityPicture* copy = static_cast< CReportEntityPicture* >( obj );

	SetBorder( copy->GetBorder() );
	SetBorderThickness( copy->GetBorderThickness() );
	SetBorderStyle( copy->GetBorderStyle() );
	SetBorderColor( copy->GetBorderColor() );
	SetFilename( copy->GetFilename() );

}

BOOL CReportEntityPicture::FromString( const CString& str )
/* ============================================================
	Function :		CReportEntityPicture::FromString
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
		CString		filename;

		int	count = 0;
		tok.GetAt( count++, border );
		tok.GetAt( count++, borderthickness );
		tok.GetAt( count++, borderstyle );
		tok.GetAt( count++, bordercolor );
		tok.GetAt( count++, filename );

		int bt = CUnitConversion::InchesToPixels( borderthickness );
		SetBorder( border );
		SetBorderThickness( bt );
		SetBorderStyle( borderstyle );
		SetBorderColor( bordercolor );
		UnmakeSaveString( filename );

		SetFilename( filename );

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

CString CReportEntityPicture::GetString() const
/* ============================================================
	Function :		CReportEntityPicture::GetString
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

	CReportEntityPicture* const local = const_cast< CReportEntityPicture* const >( this );
	local->SetLeft( left );
	local->SetRight( right );
	local->SetTop( top );
	local->SetBottom( bottom );

	CString str;
	CString filename = GetFilename();
	MakeSaveString( filename );

	double thickness = CUnitConversion::PixelsToInches( GetBorderThickness() );

	str.Format( _T( ",%i,%f,%i,%i,%s;" ),
		GetBorder( ),
		thickness,
		GetBorderStyle( ),
		GetBorderColor( ),
		filename
		);

	str = GetDefaultGetString() + str;

	local->SetLeft( oldleft );
	local->SetRight( oldright );
	local->SetTop( oldtop );
	local->SetBottom( oldbottom );

	return str;

}

CDiagramEntity* CReportEntityPicture::CreateFromString( const CString & str )
/* ============================================================
	Function :		CReportEntityPicture::CreateFromString
	Description :	Creates and returns an object of this 
					type from "str"
	Access :		Public

	Return :		CDiagramEntity*		-	Object created from "str"
	Parameters :	const CString & str	-	String to create object from
					
	Usage :			Call from a factory class to create 
					instances of this object.

   ============================================================*/
{

	CReportEntityPicture* obj = new CReportEntityPicture;
	if(!obj->FromString( str ) )
	{

		delete obj;
		obj = NULL;

	}

	return obj;

}

void CReportEntityPicture::Draw( CDC* dc, CRect rect )
/* ============================================================
	Function :		CReportEntityPicture::Draw
	Description :	Draws the object.
	Access :		Public

	Return :		void
	Parameters :	CDC* dc		-	"CDC" to draw to
					CRect rect	-	True (zoomed) rectangle to 
									draw to.
					
	Usage :			Called from "CDiagramEditor::DrawObjects".

   ============================================================*/
{

	if( !m_bitmap )
		if( m_filename.GetLength() )
			m_bitmap = ( HBITMAP ) ::LoadImage( NULL, m_filename, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_DEFAULTCOLOR | LR_CREATEDIBSECTION );

	CPen pen;
	if( GetBorder() )
	{
		pen.CreatePen( GetBorderStyle(), round( static_cast< double > ( GetBorderThickness() ) * GetZoom() ), GetBorderColor() );
		dc->SelectObject( &pen );
	}
	else
		dc->SelectStockObject( NULL_PEN );

	dc->SelectStockObject( WHITE_BRUSH );

	dc->Rectangle( rect );

	if( m_bitmap )
	{
		rect.InflateRect( -1, -1 );

		CBitmap bitmap;
		bitmap.Attach( m_bitmap );
		CDC memDC;
		memDC.CreateCompatibleDC( dc );
		CBitmap* oldbitmap = memDC.SelectObject( &bitmap );
		BITMAP bmp;
		bitmap.GetBitmap( &bmp );
		dc->StretchBlt( rect.left, rect.top, rect.Width(), rect.Height(), &memDC, 0, 0, bmp.bmWidth, bmp.bmHeight, SRCCOPY );
		memDC.SelectObject( oldbitmap );
		bitmap.Detach();
	}

	dc->SelectStockObject( BLACK_PEN );
	dc->SelectStockObject( WHITE_BRUSH );

}

void CReportEntityPicture::SetFilename( const CString& filename )
/* ============================================================
	Function :		CReportEntityPicture::SetFilename
	Description :	Accessor. Setter for "m_filename".
	Access :		Public

	Return :		void
	Parameters :	const CString& filename	-	New filename
					
	Usage :			Call to set the value of "m_filename".

   ============================================================*/
{
	m_filename = filename;
	if( m_bitmap )
	{
		::DeleteObject( m_bitmap );
		m_bitmap = NULL;
	}
/*
	if( m_filename.GetLength() )
		m_bitmap = ( HBITMAP ) ::LoadImage( NULL, m_filename, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_DEFAULTCOLOR );
	else
		m_bitmap = NULL;
*/
	CString title( m_filename );
	int found = title.ReverseFind( _TCHAR( '\\' ) );
	if( found != -1 )
		title = title.Right( title.GetLength() - ( found + 1 ) );

	SetTitle( title );

}

CString CReportEntityPicture::GetFilename() const
/* ============================================================
	Function :		CReportEntityPicture::GetFilename
	Description :	Accessor. Getter for "m_filename".
	Access :		Public

	Return :		CString	-	Current filename
	Parameters :	none

	Usage :			Call to get the value of "m_filename".

   ============================================================*/
{

	return m_filename;

}

void CReportEntityPicture::AdjustSize()
/* ============================================================
	Function :		CReportEntityPicture::AdjustSize
	Description :	The function adjusts the object size to
					the size of the picture.
	Access :		Public

	Return :		void
	Parameters :	none

	Usage :			Call to make the object the size of the 
					picture. The size is scaled to the output 
					size of the current printer.

   ============================================================*/
{
	if( !m_bitmap )
		if( m_filename.GetLength() )
			m_bitmap = ( HBITMAP ) ::LoadImage( NULL, m_filename, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_DEFAULTCOLOR | LR_CREATEDIBSECTION );

	if( m_bitmap )
	{

		CClientDC dc( AfxGetMainWnd() );
		int screenResolutionX = dc.GetDeviceCaps( LOGPIXELSX );

		CPrintDialog	printer( TRUE, PD_RETURNDC );
		printer.GetDefaults();
		HDC	hdc = printer.GetPrinterDC();
		double diff = 1;
		if( hdc )
		{
			diff = static_cast< double >( GetDeviceCaps( hdc, LOGPIXELSX ) ) / static_cast< double >( screenResolutionX );
			::DeleteDC( hdc );
		}

		BITMAP bmp;
		CBitmap temp;
		temp.Attach( m_bitmap );
		temp.GetBitmap( &bmp );
		temp.Detach();

		::DeleteObject( m_bitmap );
		m_bitmap = NULL;

		CRect rect = GetRect();
		int width = round( static_cast< double >( bmp.bmWidth ) / diff );
		int height = round( static_cast< double >( bmp.bmHeight ) / diff );

		SetRect( rect.left, rect.top, rect.left + width, rect.top + height );

	}
}
