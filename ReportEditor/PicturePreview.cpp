/* ==========================================================================
	Class :			CPicturePreview

	Author :		Johan Rosengren, Abstrakt Mekanik AB

	Date :			2004-07-25

	Purpose :		"CPicturePreview", derived from "CStatic", is a simple 
					control to display BMP-files.

	Description :	The class overrides "OnPaint" and draws the bmp.

	Usage :			Call "SetFilename" to show a picture.

   ========================================================================*/
#include "stdafx.h"
#include "..\reportcreator.h"
#include "PicturePreview.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPicturePreview

CPicturePreview::CPicturePreview()
/* ============================================================
	Function :		CPicturePreview::CPicturePreview
	Description :	Constructor
	Access :		Public

	Return :		void
	Parameters :	none

	Usage :			

   ============================================================*/
{

	m_bitmap = NULL;

}

CPicturePreview::~CPicturePreview()
/* ============================================================
	Function :		CPicturePreview::~CPicturePreview
	Description :	Destructor
	Access :		Public

	Return :		void
	Parameters :	none

	Usage :			

   ============================================================*/
{

	if( m_bitmap )
		::DeleteObject( m_bitmap );

}

BEGIN_MESSAGE_MAP(CPicturePreview, CWnd)
	//{{AFX_MSG_MAP(CPicturePreview)
	ON_WM_PAINT()
	ON_WM_ERASEBKGND()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPicturePreview message handlers

void CPicturePreview::OnPaint() 
/* ============================================================
	Function :		CPicturePreview::OnPaint
	Description :	Handler for the "WM_PAINT" message.
	Access :		Protected

	Return :		void
	Parameters :	none

	Usage :			Called from MFC.

   ============================================================*/
{

	CPaintDC dc(this);
	CRect rect;
	GetClientRect( rect );
	CDC memDC;
	memDC.CreateCompatibleDC( &dc );
	if( m_bitmap )
	{

		CBitmap bitmap;
		bitmap.Attach( m_bitmap );
		CBitmap* oldbitmap = memDC.SelectObject( &bitmap );
		BITMAP bmp;
		bitmap.GetBitmap( &bmp );
		dc.StretchBlt( 0, 0, rect.Width(), rect.Height(), &memDC, 0, 0, bmp.bmWidth, bmp.bmHeight, SRCCOPY );
		memDC.SelectObject( oldbitmap );
		bitmap.Detach();

	}
	else
	{
		// Draw No-pic icon
		CBitmap bitmap;
		bitmap.CreateCompatibleBitmap( &dc, rect.Width(), rect.Height() );
		CBitmap* oldbitmap = memDC.SelectObject( &bitmap );

		CPen pen;
		pen.CreatePen( PS_SOLID, 0, RGB( 255, 0, 0 ) );
		memDC.SelectObject( &pen );
		memDC.SelectStockObject( WHITE_BRUSH );

		memDC.Rectangle( rect );
		memDC.MoveTo( rect.TopLeft() );
		memDC.LineTo( rect.BottomRight() );

		dc.BitBlt( 0, 0, rect.Width(), rect.Height(), &memDC, 0, 0, SRCCOPY );

		memDC.SelectStockObject( BLACK_PEN );
		memDC.SelectObject( oldbitmap );

	}

	dc.BitBlt( 0, 0, rect.Width(), rect.Height(), &memDC, 0, 0, SRCCOPY );

}

BOOL CPicturePreview::OnEraseBkgnd( CDC* /*pDC*/ ) 
/* ============================================================
	Function :		CPicturePreview::OnEraseBkgnd
	Description :	Handler for the "WM_ERASEBKGND" message.
	Access :		Protected

	Return :		BOOL		-	Always "TRUE"
	Parameters :	CDC* pDC	-	"CDC" to erase
					
	Usage :			Called from MFC.

   ============================================================*/
{

	return TRUE;

}

void CPicturePreview::SetFilename( const CString &filename )
/* ============================================================
	Function :		CPicturePreview::SetFilename
	Description :	Sets the bmp-file to display.
	Access :		Public

	Return :		void
	Parameters :	const CString &filename	-	File to display
					
	Usage :			Call to display a bmp-file in the control

   ============================================================*/
{
	if( m_bitmap )
		::DeleteObject( m_bitmap );

	m_filename = filename;

	if( m_filename.GetLength() )
	{
		m_bitmap = ( HBITMAP ) ::LoadImage( NULL, m_filename, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_DEFAULTCOLOR );
		if( !m_bitmap )
		{
			CString error;
			error.LoadString( IDS_REPORT_BAD_FILE );
			CString message;
			message.Format( error, m_filename );
			AfxMessageBox( message );
			m_filename = _T( "" );
		}
	}
	else
		m_bitmap = NULL;

}

CString CPicturePreview::GetFilename() const
/* ============================================================
	Function :		CPicturePreview::GetFilename
	Description :	Gets the name of the bmp-file currently 
					displayed in the control.
	Access :		Public

	Return :		CString	-	File displayed.
	Parameters :	none

	Usage :			Call to get the file displayed in the 
					control.

   ============================================================*/
{

	return m_filename;

}
