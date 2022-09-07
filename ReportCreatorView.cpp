/* ==========================================================================
	Class :			CReportCreatorView

	Author :		Johan Rosengren, Abstrakt Mekanik AB

	Date :			2004-07-25

	Purpose :		"CReportCreatorView" derives from "CView" and is the main 
					view class of the application.

	Description :	The member "m_editor" is the actual editor, and covers 
					all of the client area together with the rulers.

	Usage :			Created by MFC

   ========================================================================*/

#include "stdafx.h"
#include "ReportCreator.h"

#include "ReportCreatorDoc.h"
#include "ReportCreatorView.h"
#include "EditorSettingsDialog.h"

#include "ReportEditor/ReportEntityBox.h"
#include "ReportEditor/ReportEntityEllipse.h"
#include "ReportEditor/ReportEntityLine.h"
#include "ReportEditor/ReportEntityLabel.h"
#include "ReportEditor/ReportEntityPicture.h"

#include "ReportEditor/ReportEntityField.h"
#include "ReportEditor/ReportEntityGrid.h"

#include "ReportEditor/ReportEntitySettings.h"
#include "ReportEditor/UnitConversion.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define RULER_SIZE	24

/////////////////////////////////////////////////////////////////////////////
// CReportCreatorView

IMPLEMENT_DYNCREATE(CReportCreatorView, CView)

BEGIN_MESSAGE_MAP(CReportCreatorView, CView)
	//{{AFX_MSG_MAP(CReportCreatorView)
	ON_WM_ERASEBKGND()
	ON_WM_SIZE()
	ON_COMMAND(ID_BUTTON_SETTINGS, OnButtonSettings)
	ON_COMMAND(ID_BUTTON_GRID, OnButtonGrid)
	ON_UPDATE_COMMAND_UI(ID_BUTTON_GRID, OnUpdateButtonGrid)
	ON_COMMAND(ID_BUTTON_MARGIN, OnButtonMargin)
	ON_UPDATE_COMMAND_UI(ID_BUTTON_MARGIN, OnUpdateButtonMargin)
	ON_COMMAND(ID_BUTTON_SNAP, OnButtonSnap)
	ON_UPDATE_COMMAND_UI(ID_BUTTON_SNAP, OnUpdateButtonSnap)
	ON_COMMAND(ID_BUTTON_ADD_BOX, OnButtonAddBox)
	ON_COMMAND(ID_BUTTON_ADD_ELLIPSE, OnButtonAddEllipse)
	ON_COMMAND(ID_BUTTON_ADD_FIELD, OnButtonAddField)
	ON_COMMAND(ID_BUTTON_ADD_LABEL, OnButtonAddLabel)
	ON_COMMAND(ID_BUTTON_ADD_LINE, OnButtonAddLine)
	ON_COMMAND(ID_EDIT_COPY, OnEditCopy)
	ON_UPDATE_COMMAND_UI(ID_EDIT_COPY, OnUpdateEditCopy)
	ON_COMMAND(ID_EDIT_CUT, OnEditCut)
	ON_UPDATE_COMMAND_UI(ID_EDIT_CUT, OnUpdateEditCut)
	ON_COMMAND(ID_EDIT_PASTE, OnEditPaste)
	ON_UPDATE_COMMAND_UI(ID_EDIT_PASTE, OnUpdateEditPaste)
	ON_COMMAND(ID_EDIT_UNDO, OnEditUndo)
	ON_UPDATE_COMMAND_UI(ID_EDIT_UNDO, OnUpdateEditUndo)
	ON_COMMAND(ID_ZOOM_IN, OnZoomIn)
	ON_COMMAND(ID_ZOOM_OUT, OnZoomOut)
	ON_COMMAND(ID_BUTTON_ALIGN_BOTTOM, OnButtonAlignBottom)
	ON_UPDATE_COMMAND_UI(ID_BUTTON_ALIGN_BOTTOM, OnUpdateButtonAlignBottom)
	ON_COMMAND(ID_BUTTON_ALIGN_LEFT, OnButtonAlignLeft)
	ON_UPDATE_COMMAND_UI(ID_BUTTON_ALIGN_LEFT, OnUpdateButtonAlignLeft)
	ON_COMMAND(ID_BUTTON_ALIGN_RIGHT, OnButtonAlignRight)
	ON_UPDATE_COMMAND_UI(ID_BUTTON_ALIGN_RIGHT, OnUpdateButtonAlignRight)
	ON_COMMAND(ID_BUTTON_ALIGN_TOP, OnButtonAlignTop)
	ON_UPDATE_COMMAND_UI(ID_BUTTON_ALIGN_TOP, OnUpdateButtonAlignTop)
	ON_COMMAND(ID_BUTTON_SAME_SIZE, OnButtonSameSize)
	ON_UPDATE_COMMAND_UI(ID_BUTTON_SAME_SIZE, OnUpdateButtonSameSize)
	ON_COMMAND(ID_BUTTON_ZOOM_TO_FIT, OnButtonZoomToFit)
	ON_COMMAND(ID_BUTTON_PROPERTIES, OnButtonProperties)
	ON_COMMAND(ID_BUTTON_ADD_GRID, OnButtonAddGrid)
	ON_COMMAND(ID_BUTTON_ADD_PICTURE, OnButtonAddPicture)
	ON_WM_DESTROY()
	ON_COMMAND(ID_DELETE, OnDelete)
	ON_COMMAND(ID_INSERT, OnInsert)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)

	ON_REGISTERED_MESSAGE(UWM_HSCROLL, OnEditorHScroll)
	ON_REGISTERED_MESSAGE(UWM_VSCROLL, OnEditorVScroll)
	ON_REGISTERED_MESSAGE(UWM_ZOOM, OnEditorZoom)
	ON_REGISTERED_MESSAGE(UWM_MOUSE, OnEditorMouse)
	ON_REGISTERED_MESSAGE(UWM_MEASUREMENTS, OnRulerMeasurements)

END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CReportCreatorView construction/destruction

CReportCreatorView::CReportCreatorView()
/* ============================================================
	Function :		CReportCreatorView::CReportCreatorView
	Description :	Constructor
	Access :		Public

	Return :		void
	Parameters :	none

	Usage :			

   ============================================================*/
{

	m_screenResolutionX = 0;

}

CReportCreatorView::~CReportCreatorView()
/* ============================================================
	Function :		CReportCreatorView::~CReportCreatorView
	Description :	Destructor
	Access :		Public

	Return :		void
	Parameters :	none

	Usage :			

   ============================================================*/
{
}

BOOL CReportCreatorView::PreCreateWindow(CREATESTRUCT& cs)
/* ============================================================
	Function :		CReportCreatorView::PreCreateWindow
	Description :	Called befor the window is created
	Access :		Public

	Return :		BOOL				-	Not interested
	Parameters :	CREATESTRUCT& cs	-	Not interested
					
	Usage :			Called from MFC

   ============================================================*/
{
	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CReportCreatorView drawing

void CReportCreatorView::OnDraw(CDC* pDC)
/* ============================================================
	Function :		CReportCreatorView::OnDraw
	Description :	Draws the view
	Access :		Public

	Return :		void
	Parameters :	CDC* pDC	-	"CDC" to draw to
					
	Usage :			Called from MFC

   ============================================================*/
{
	CReportCreatorDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	if( pDC->IsPrinting() )
	{

		COLORREF col = m_editor.GetBackgroundColor();

		// Print zoom is the difference between screen- 
		// and printer resolution.
		double zoom = pDC->GetDeviceCaps( LOGPIXELSX ) / m_screenResolutionX;

		CRect rect( 0,0, 
			round( static_cast< double >( m_editor.GetVirtualSize().cx ) * zoom ), 
			round( static_cast< double >( m_editor.GetVirtualSize().cy ) * zoom ) );

		m_editor.SetRedraw( FALSE );
		m_editor.SetBackgroundColor( RGB( 255, 255, 255 ) );
		m_editor.Print( pDC, rect, zoom );
		m_editor.SetBackgroundColor( col );
		m_editor.SetRedraw( TRUE );

	}

}

/////////////////////////////////////////////////////////////////////////////
// CReportCreatorView printing

BOOL CReportCreatorView::OnPreparePrinting(CPrintInfo* pInfo)
/* ============================================================
	Function :		CReportCreatorView::OnPreparePrinting
	Description :	Called before a printout
	Access :		Public

	Return :		BOOL				-	Not interested
	Parameters :	CPrintInfo* pInfo	-	Not interested	
					
	Usage :			Called from MFC

   ============================================================*/
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CReportCreatorView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
/* ============================================================
	Function :		CReportCreatorView::OnBeginPrinting
	Description :	Called before a printout
	Access :		Public

	Return :		void
	Parameters :	CDC*		-	Not interested
					CPrintInfo*	-	Not interested
					
	Usage :			Called from MFC

   ============================================================*/
{
}

void CReportCreatorView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
/* ============================================================
	Function :		CReportCreatorView::OnEndPrinting
	Description :	Called after a printout
	Access :		Public

	Return :		void
	Parameters :	CDC*		-	Not interested
					CPrintInfo*	-	Not interested
					
	Usage :			Called from MFC

   ============================================================*/
{
}

/////////////////////////////////////////////////////////////////////////////
// CReportCreatorView diagnostics

#ifdef _DEBUG
void CReportCreatorView::AssertValid() const
/* ============================================================
	Function :		CReportCreatorView::AssertValid
	Description :	Checks object validity
	Access :		Public

	Return :		void
	Parameters :	none

	Usage :			Debug function

   ============================================================*/
{
	CView::AssertValid();
}

void CReportCreatorView::Dump(CDumpContext& dc) const
/* ============================================================
	Function :		CReportCreatorView::Dump
	Description :	Dumps object data
	Access :		Public

	Return :		void
	Parameters :	CDumpContext& dc	-	Dump context
					
	Usage :			Debug function

   ============================================================*/
{
	CView::Dump(dc);
}

CReportCreatorDoc* CReportCreatorView::GetDocument()
/* ============================================================
	Function :		CReportCreatorView::GetDocument
	Description :	Returns a pointer to the current document
	Access :		Public

	Return :		CReportCreatorDoc*	-	Current document
	Parameters :	none

	Usage :			Call to get a pointer to the view document.

   ============================================================*/
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CReportCreatorDoc)));
	return (CReportCreatorDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CReportCreatorView message handlers

void CReportCreatorView::OnInitialUpdate() 
/* ============================================================
	Function :		CReportCreatorView::OnInitialUpdate
	Description :	Called before the view is displayed
	Access :		Public

	Return :		void
	Parameters :	none

	Usage :			Called from MFC. We create the editor.

   ============================================================*/
{
	CView::OnInitialUpdate();
	
	if( !m_editor.m_hWnd )
	{
		CSize sz = GetDocument()->GetData()->GetVirtualSize();

		int restraintMode = theApp.GetProfileInt( _T( "Application" ), _T( "Restraint" ), 0 );
		int left = theApp.GetProfileInt( _T( "Application" ), _T( "Left" ), 0 );
		int right = theApp.GetProfileInt( _T( "Application" ), _T( "Right" ), 0 );
		int top = theApp.GetProfileInt( _T( "Application" ), _T( "Top" ), 0 );
		int bottom = theApp.GetProfileInt( _T( "Application" ), _T( "Bottom" ), 0 );

		int width = theApp.GetProfileInt( _T( "Application" ), _T( "Width" ), -1 );
		int height = theApp.GetProfileInt( _T( "Application" ), _T( "Height" ), -1 );

		COLORREF colorBg = ( COLORREF ) theApp.GetProfileInt( _T( "Application" ), _T( "ColorBg" ), RGB( 255, 255, 255 ) );
		COLORREF colorGrid = ( COLORREF ) theApp.GetProfileInt( _T( "Application" ), _T( "ColorGrid" ), RGB( 222, 222, 222 ) );
		COLORREF colorMargin = ( COLORREF ) theApp.GetProfileInt( _T( "Application" ), _T( "ColorMargin" ), RGB( 0, 0, 255 ) );

		BOOL margin = ( BOOL ) theApp.GetProfileInt( _T( "Application" ), _T( "Margin" ), FALSE );
		BOOL grid = ( BOOL ) theApp.GetProfileInt( _T( "Application" ), _T( "Grid" ), FALSE );
		BOOL snap = ( BOOL ) theApp.GetProfileInt( _T( "Application" ), _T( "Snap" ), FALSE );
		int measurements = theApp.GetProfileInt( _T( "Application" ), _T( "Units" ), 0 );

		CReportEntitySettings::GetRESInstance()->SetMeasurementUnits( measurements );

		double zoom = static_cast< double >( theApp.GetProfileInt( _T( "Application" ), _T( "ZoomLevel" ), 100 ) ) / 100;
		double zoomfactor = static_cast< double >( theApp.GetProfileInt( _T( "Application" ), _T( "ZoomFactor" ), 1 ) ) / 100;

		CRect	rect;
		GetClientRect( rect );
		rect.left = RULER_SIZE;
		rect.top = RULER_SIZE;
		m_editor.Create( WS_CHILD | WS_VISIBLE, rect, this, GetDocument()->GetData() );

		rect.top = 0;
		rect.bottom = RULER_SIZE;
		m_horzRuler.Create( NULL, NULL, WS_CHILD | WS_VISIBLE, rect, this, 100 );

		GetClientRect( rect );
		rect.right = RULER_SIZE;
		rect.top = RULER_SIZE;
		m_vertRuler.Create( NULL, NULL, WS_CHILD | WS_VISIBLE, rect, this, 101 );

		rect.left = 0;
		rect.top = 0;
		rect.right = RULER_SIZE;
		rect.bottom = RULER_SIZE;
		m_cornerBox.Create( NULL, NULL, WS_CHILD | WS_VISIBLE, rect, this, 102 );

		m_horzRuler.SetMeasurements( measurements );
		m_vertRuler.SetMeasurements( measurements );
		m_cornerBox.SetMeasurements( measurements );

		CClientDC dc( this );
		m_screenResolutionX = dc.GetDeviceCaps( LOGPIXELSX );
		CUnitConversion::Init( m_screenResolutionX );

		int step = m_screenResolutionX / 6;
		int gridSize = theApp.GetProfileInt( _T( "Application" ), _T( "GridSize" ), step );

		if( width == -1 )
		{
			CPrintDialog	printer( TRUE, PD_RETURNDC );
			printer.GetDefaults();
			HDC	hdc = printer.GetPrinterDC();
			if( hdc )
			{

				double diff = static_cast< double > ( GetDeviceCaps( hdc, LOGPIXELSX ) ) / static_cast< double > ( m_screenResolutionX );
				int horzSize = ::GetDeviceCaps( hdc, PHYSICALWIDTH );
				int vertSize = ::GetDeviceCaps( hdc, PHYSICALHEIGHT );

				int leftMarg = ::GetDeviceCaps( hdc, PHYSICALOFFSETX );
				int topMarg = ::GetDeviceCaps( hdc, PHYSICALOFFSETY );

				int horzPrintable = ::GetDeviceCaps( hdc, HORZRES );
				int vertPrintable = ::GetDeviceCaps( hdc, VERTRES );

				int rightMarg = horzSize - ( horzPrintable + leftMarg );
				int bottomMarg = vertSize - ( vertPrintable + topMarg );

				left = static_cast< int > ( static_cast< double > ( leftMarg ) / diff );
				top = static_cast< int > ( static_cast< double > ( topMarg ) / diff );
				right = static_cast< int > ( static_cast< double > ( rightMarg ) / diff );
				bottom = static_cast< int > ( static_cast< double > ( bottomMarg ) / diff );
				width = static_cast< int > ( static_cast< double > ( horzSize ) / diff );
				height = static_cast< int > ( static_cast< double > ( vertSize ) / diff );
	
				::DeleteDC( hdc );

			}
			else
			{
				// No default printer installed
				width = 8 * m_screenResolutionX;
				height = 11 * m_screenResolutionX;

				left = 0;
				top = 0;
				right = 0;
				bottom = 0;
			}
		}

		m_editor.SetZoom( zoom );

		m_editor.SetZoomFactor( zoomfactor );
		m_editor.SetVirtualSize( CSize( width, height ) );
		m_editor.SetMargins( left, top, right, bottom );
		m_editor.SetSnapToGrid( snap );
		m_editor.ShowGrid( grid );
		m_editor.ShowMargin( margin );
		m_editor.SetRestraints( restraintMode );
		m_editor.SetBackgroundColor( colorBg );
		m_editor.SetGridColor( colorGrid );
		m_editor.SetMarginColor( colorMargin );

		m_editor.SetScrollWheelMode( WHEEL_ZOOM );

		m_editor.SetGridSize( CSize( gridSize, gridSize ) );

		m_editor.SetZoomMin( .05 );
		m_editor.SetZoomMax( 4 );

		if( sz.cx != 0 && sz.cy != 0 )
			m_editor.SetVirtualSize( sz );

		m_editor.SetModified( FALSE );
	}
	else
		m_editor.Clear();
	
}

BOOL CReportCreatorView::OnEraseBkgnd( CDC* /*pDC*/ ) 
/* ============================================================
	Function :		CReportCreatorView::OnEraseBkgnd
	Description :	Handler for the "WM_ERASEBKND"-message.
	Access :		Protected

	Return :		BOOL		-	Always "TRUE"
	Parameters :	CDC* pDC	-	"CDC" to erase
					
	Usage :			Called from MFC.

   ============================================================*/
{

	return TRUE;

}

void CReportCreatorView::OnSize(UINT nType, int cx, int cy) 
/* ============================================================
	Function :		CReportCreatorView::OnSize
	Description :	Handler for the "WM_SIZE" message.
	Access :		Protected

	Return :		void
	Parameters :	UINT nType	-	Not interested
					int cx		-	New x-size
					int cy		-	New y-size
					
	Usage :			Called from MFC.

   ============================================================*/
{

	CView::OnSize(nType, cx, cy);

	if( m_editor.m_hWnd )
	{
		m_editor.MoveWindow( RULER_SIZE, RULER_SIZE, cx - RULER_SIZE, cy - RULER_SIZE );
		m_horzRuler.MoveWindow( RULER_SIZE, 0, cx, RULER_SIZE );
		m_vertRuler.MoveWindow( 0, RULER_SIZE, RULER_SIZE, cy );
	}

}

void CReportCreatorView::OnButtonSettings() 
/* ============================================================
	Function :		CReportCreatorView::OnButtonSettings
	Description :	Handler for the toolbar button Settings
	Access :		Protected

	Return :		void
	Parameters :	none

	Usage :			Called from MFC.

   ============================================================*/
{

	CEditorSettingsDialog	dlg;

	dlg.m_colorBg = m_editor.GetBackgroundColor();
	dlg.m_colorGrid = m_editor.GetGridColor();
	dlg.m_colorMargin = m_editor.GetMarginColor();

	dlg.m_width = m_editor.GetVirtualSize().cx;
	dlg.m_height = m_editor.GetVirtualSize().cy;

	dlg.m_margins = m_editor.IsMarginVisible();
	dlg.m_snap = m_editor.GetSnapToGrid();
	dlg.m_grid = m_editor.IsGridVisible();

	m_editor.GetMargins( dlg.m_left, dlg.m_top, dlg.m_right, dlg.m_bottom );
	int restraintMode = m_editor.GetRestraints();
	if( restraintMode == RESTRAINT_NONE )
		dlg.m_restraint = 2;
	if( restraintMode == RESTRAINT_VIRTUAL )
		dlg.m_restraint = 1;
	if( restraintMode == RESTRAINT_MARGIN )
		dlg.m_restraint = 0;

	dlg.m_zoom = round( m_editor.GetZoomFactor() * 100 );
	dlg.m_zoomlevel = round( m_editor.GetZoom() * 100 );
	dlg.m_gridsize = m_editor.GetGridSize().cx;

	dlg.m_measurements = CReportEntitySettings::GetRESInstance()->GetMeasurementUnits();

	if( dlg.DoModal() )
	{

		m_editor.SetVirtualSize( CSize( dlg.m_width, dlg.m_height ) );
		m_editor.SetBackgroundColor( dlg.m_colorBg );
		m_editor.SetGridColor( dlg.m_colorGrid );
		m_editor.SetMarginColor( dlg.m_colorMargin );
		m_editor.ShowMargin( dlg.m_margins );
		m_editor.SetSnapToGrid( dlg.m_snap );
		m_editor.ShowGrid( dlg.m_grid );
		m_editor.SetGridSize( CSize( dlg.m_gridsize, dlg.m_gridsize ) );
		m_editor.SetMargins( dlg.m_left, dlg.m_top, dlg.m_right, dlg.m_bottom );

		if( dlg.m_restraint == 2 )
			restraintMode = RESTRAINT_NONE;
		if( dlg.m_restraint == 1 )
			restraintMode = RESTRAINT_VIRTUAL;
		if( dlg.m_restraint == 0 )
			restraintMode = RESTRAINT_MARGIN;

		m_editor.SetRestraints( restraintMode );
		m_editor.SetZoomFactor( static_cast< double >( dlg.m_zoom ) / 100 );

		m_editor.SetZoom( static_cast< double >( dlg.m_zoomlevel ) / 100 );

		CReportEntitySettings::GetRESInstance()->SetMeasurementUnits( dlg.m_measurements );
		
		m_horzRuler.SetMeasurements( dlg.m_measurements );
		m_vertRuler.SetMeasurements( dlg.m_measurements );
		m_cornerBox.SetMeasurements( dlg.m_measurements );

		SaveSettings();

		m_editor.RedrawWindow();

	}

}

void CReportCreatorView::SaveSettings()
/* ============================================================
	Function :		CReportCreatorView::SaveSettings
	Description :	Saves the editor settings to the registry.
	Access :		Private

	Return :		void
	Parameters :	none

	Usage :			Call to save the editor settings to the 
					registry.

   ============================================================*/
{

	int left;
	int right;
	int top;
	int bottom;
	int measurements;

	m_editor.GetMargins( left, top, right, bottom );
	measurements = CReportEntitySettings::GetRESInstance()->GetMeasurementUnits();

	theApp.WriteProfileInt( _T( "Application" ), _T( "Restraint" ), m_editor.GetRestraints() );
	theApp.WriteProfileInt( _T( "Application" ), _T( "Left" ), left );
	theApp.WriteProfileInt( _T( "Application" ), _T( "Right" ), right );
	theApp.WriteProfileInt( _T( "Application" ), _T( "Top" ), top );
	theApp.WriteProfileInt( _T( "Application" ), _T( "Bottom" ), bottom );

	theApp.WriteProfileInt( _T( "Application" ), _T( "Width" ), m_editor.GetVirtualSize().cx );
	theApp.WriteProfileInt( _T( "Application" ), _T( "Height" ), m_editor.GetVirtualSize().cy );
	theApp.WriteProfileInt( _T( "Application" ), _T( "ColorBg" ), m_editor.GetBackgroundColor() );
	theApp.WriteProfileInt( _T( "Application" ), _T( "ColorGrid" ), m_editor.GetGridColor() );
	theApp.WriteProfileInt( _T( "Application" ), _T( "ColorMargin" ), m_editor.GetMarginColor() );
	theApp.WriteProfileInt( _T( "Application" ), _T( "Margin" ), m_editor.IsMarginVisible() );
	theApp.WriteProfileInt( _T( "Application" ), _T( "Grid" ), m_editor.IsGridVisible() );
	theApp.WriteProfileInt( _T( "Application" ), _T( "Snap" ), m_editor.GetSnapToGrid() );
	theApp.WriteProfileInt( _T( "Application" ), _T( "ZoomFactor" ), static_cast< int >( m_editor.GetZoomFactor() * 100.0 ));
	theApp.WriteProfileInt( _T( "Application" ), _T( "ZoomLevel" ), static_cast< int >( m_editor.GetZoom() * 100.0 ) );
	theApp.WriteProfileInt( _T( "Application" ), _T( "Units" ), measurements );

}

void CReportCreatorView::OnButtonGrid() 
/* ============================================================
	Function :		CReportCreatorView::OnButtonGrid
	Description :	Handler for the toolbar button Grid
	Access :		Protected

	Return :		void
	Parameters :	none

	Usage :			Called from MFC.

   ============================================================*/
{

	m_editor.ShowGrid( !m_editor.IsGridVisible() );

}

void CReportCreatorView::OnUpdateButtonGrid(CCmdUI* pCmdUI) 
/* ============================================================
	Function :		CReportCreatorView::OnUpdateButtonGrid
	Description :	Update-handler for the UI-element
	Access :		Protected

	Return :		void
	Parameters :	CCmdUI* pCmdUI	-	"CCmdUI" to update.
					
	Usage :			Called from MFC.

   ============================================================*/
{

	pCmdUI->SetCheck( m_editor.IsGridVisible() );

}

void CReportCreatorView::OnButtonMargin() 
/* ============================================================
	Function :		CReportCreatorView::OnButtonMargin
	Description :	Handler for the toolbar button Margin
	Access :		Protected

	Return :		void
	Parameters :	none

	Usage :			Called from MFC.

   ============================================================*/
{

	m_editor.ShowMargin( !m_editor.IsMarginVisible() );

}

void CReportCreatorView::OnUpdateButtonMargin(CCmdUI* pCmdUI) 
/* ============================================================
	Function :		CReportCreatorView::OnUpdateButtonMargin
	Description :	Update-handler for the UI-element
	Access :		Protected

	Return :		void
	Parameters :	CCmdUI* pCmdUI	-	"CCmdUI" to update.
					
	Usage :			Called from MFC.

   ============================================================*/
{
	
	pCmdUI->SetCheck( m_editor.IsMarginVisible() );

}

void CReportCreatorView::OnButtonSnap() 
/* ============================================================
	Function :		CReportCreatorView::OnButtonSnap
	Description :	Handler for the toolbar button Snap
	Access :		Protected

	Return :		void
	Parameters :	none

	Usage :			Called from MFC.

   ============================================================*/
{

	m_editor.SetSnapToGrid( !m_editor.GetSnapToGrid() );

}

void CReportCreatorView::OnUpdateButtonSnap(CCmdUI* pCmdUI) 
/* ============================================================
	Function :		CReportCreatorView::OnUpdateButtonSnap
	Description :	Update-handler for the UI-element
	Access :		Protected

	Return :		void
	Parameters :	CCmdUI* pCmdUI	-	"CCmdUI" to update.
					
	Usage :			Called from MFC.

   ============================================================*/
{

	pCmdUI->SetCheck( m_editor.GetSnapToGrid() );

}

void CReportCreatorView::OnButtonAddBox() 
/* ============================================================
	Function :		CReportCreatorView::OnButtonAddBox
	Description :	Handler for the toolbar button AddBox
	Access :		Protected

	Return :		void
	Parameters :	none

	Usage :			Called from MFC.

   ============================================================*/
{

	m_editor.StartDrawingObject( new CReportEntityBox );

}

void CReportCreatorView::OnButtonAddEllipse() 
/* ============================================================
	Function :		CReportCreatorView::OnButtonAddEllipse
	Description :	Handler for the toolbar button AddEllipse
	Access :		Protected

	Return :		void
	Parameters :	none

	Usage :			Called from MFC.

   ============================================================*/
{

	m_editor.StartDrawingObject( new CReportEntityEllipse );

}

void CReportCreatorView::OnButtonAddField() 
/* ============================================================
	Function :		CReportCreatorView::OnButtonAddField
	Description :	Handler for the toolbar button AddField
	Access :		Protected

	Return :		void
	Parameters :	none

	Usage :			Called from MFC.

   ============================================================*/
{

	m_editor.StartDrawingObject( new CReportEntityField );

}

void CReportCreatorView::OnButtonAddLabel() 
/* ============================================================
	Function :		CReportCreatorView::OnButtonAddLabel
	Description :	Handler for the toolbar button AddLabel
	Access :		Protected

	Return :		void
	Parameters :	none

	Usage :			Called from MFC.

   ============================================================*/
{

	m_editor.StartDrawingObject( new CReportEntityLabel );

}

void CReportCreatorView::OnButtonAddLine() 
/* ============================================================
	Function :		CReportCreatorView::OnButtonAddLine
	Description :	Handler for the toolbar button AddLine
	Access :		Protected

	Return :		void
	Parameters :	none

	Usage :			Called from MFC.

   ============================================================*/
{

	m_editor.StartDrawingObject( new CReportEntityLine );

}

LRESULT CReportCreatorView::OnEditorHScroll( WPARAM pos, LPARAM )
/* ============================================================
	Function :		CReportCreatorView::OnEditorHScroll
	Description :	Handler for the registered message "UWM_HSCROLL"
	Access :		Protected

	Return :		LRESULT		-	Not used
	Parameters :	WPARAM pos	-	New scroll position
					LPARAM	-	
					
	Usage :			Called from MFC. The message is sent when 
					the editor is scrolled horizontally.

   ============================================================*/
{

	m_horzRuler.SetStartPos( pos );
	return 0;

}

LRESULT CReportCreatorView::OnEditorVScroll( WPARAM pos, LPARAM )
/* ============================================================
	Function :		CReportCreatorView::OnEditorVScroll
	Description :	Handler for the registered message "UWM_VSCROLL"
	Access :		Protected

	Return :		LRESULT		-	Not used
	Parameters :	WPARAM pos	-	New scroll position
					LPARAM		-	Not used
					
	Usage :			Called from MFC. The message is sent when 
					the editor is scrolled vertically.

   ============================================================*/
{

	m_vertRuler.SetStartPos( pos );
	return 0;

}

LRESULT CReportCreatorView::OnEditorZoom( WPARAM z, LPARAM )
/* ============================================================
	Function :		CReportCreatorView::OnEditorZoom
	Description :	Handler for the registered message "UWM_ZOOM"
	Access :		Protected

	Return :		LRESULT		-	Not used
	Parameters :	WPARAM	z	-	New zoom value (*100)
					LPARAM		-	Not used
					
	Usage :			Called from MFC. The message is sent when 
					the editor is zoomed.

   ============================================================*/
{

	double zoom = static_cast<double>( z ) / 100;

	m_horzRuler.SetZoom( zoom );
	m_vertRuler.SetZoom( zoom );

	return 0;

}

LRESULT CReportCreatorView::OnEditorMouse( WPARAM z, LPARAM )
/* ============================================================
	Function :		CReportCreatorView::OnEditorMouse
	Description :	Handler for the registered message "UWM_MOUSE"
	Access :		Protected

	Return :		LRESULT		-	Not used
	Parameters :	WPARAM	z	-	New mouse position
					LPARAM		-	Not used
					
	Usage :			Called from MFC. The message is sent when 
					the mouse is moved in the editor.

   ============================================================*/
{

	CPoint* pt = reinterpret_cast< CPoint* >( z );
	if( pt )
	{
		m_horzRuler.SetPointerPos( pt->x );
		m_vertRuler.SetPointerPos( pt->y );
	}
	else
	{
		m_horzRuler.SetPointerPos( -1 );
		m_vertRuler.SetPointerPos( -1 );
	}

	return 0;

}

LRESULT CReportCreatorView::OnRulerMeasurements( WPARAM measurements, LPARAM )
/* ============================================================
	Function :		CReportCreatorView::OnRulerMeasurements
	Description :	Handler for the registered message 
					"UWM_MEASUREMENTS" - sent from the corner 
					control when the measurement settings are 
					changed.
	Access :		Protected

	Return :		LRESULT				-	Not used
	Parameters :	WPARAM measurements	-	New measurement units.
					LPARAM				-	Not used
					
	Usage :			Called from MFC

   ============================================================*/
{

	m_horzRuler.SetMeasurements( measurements );
	m_vertRuler.SetMeasurements( measurements );
	m_cornerBox.SetMeasurements( measurements );

	CReportEntitySettings::GetRESInstance()->SetMeasurementUnits( measurements );

	return 0;

}

void CReportCreatorView::OnEditCopy() 
/* ============================================================
	Function :		CReportCreatorView::OnEditCopy
	Description :	Handler for the Copy command
	Access :		Protected

	Return :		void
	Parameters :	none

	Usage :			Called from MFC

   ============================================================*/
{

	m_editor.Copy();

}

void CReportCreatorView::OnUpdateEditCopy(CCmdUI* pCmdUI) 
/* ============================================================
	Function :		CReportCreatorView::OnUpdateEditCopy
	Description :	Update-handler for the UI-element
	Access :		Protected

	Return :		void
	Parameters :	CCmdUI* pCmdUI	-	"CCmdUI" to update.
					
	Usage :			Called from MFC.

   ============================================================*/
{

	m_editor.UpdateCopy( pCmdUI );

}

void CReportCreatorView::OnEditCut() 
/* ============================================================
	Function :		CReportCreatorView::OnEditCut
	Description :	Handler for the Cut command
	Access :		Protected

	Return :		void
	Parameters :	none

	Usage :			Called from MFC

   ============================================================*/
{

	m_editor.Cut();

}

void CReportCreatorView::OnUpdateEditCut(CCmdUI* pCmdUI) 
/* ============================================================
	Function :		CReportCreatorView::OnUpdateEditCut
	Description :	Update-handler for the UI-element
	Access :		Protected

	Return :		void
	Parameters :	CCmdUI* pCmdUI	-	"CCmdUI" to update.
					
	Usage :			Called from MFC.

   ============================================================*/
{

	m_editor.UpdateCut( pCmdUI );

}

void CReportCreatorView::OnEditPaste() 
/* ============================================================
	Function :		CReportCreatorView::OnEditPaste
	Description :	Handler for the Paste command
	Access :		Protected

	Return :		void
	Parameters :	none

	Usage :			Called from MFC

   ============================================================*/
{

	m_editor.Paste();

}

void CReportCreatorView::OnUpdateEditPaste(CCmdUI* pCmdUI) 
/* ============================================================
	Function :		CReportCreatorView::OnUpdateEditPaste
	Description :	Update-handler for the UI-element
	Access :		Protected

	Return :		void
	Parameters :	CCmdUI* pCmdUI	-	"CCmdUI" to update.
					
	Usage :			Called from MFC.

   ============================================================*/
{

	m_editor.UpdatePaste( pCmdUI );

}

void CReportCreatorView::OnEditUndo() 
/* ============================================================
	Function :		CReportCreatorView::OnEditUndo
	Description :	Handler for the Undo command
	Access :		Protected

	Return :		void
	Parameters :	none

	Usage :			Called from MFC

   ============================================================*/
{

	m_editor.Undo();

}

void CReportCreatorView::OnUpdateEditUndo(CCmdUI* pCmdUI) 
/* ============================================================
	Function :		CReportCreatorView::OnUpdateEditUndo
	Description :	Update-handler for the UI-element
	Access :		Protected

	Return :		void
	Parameters :	CCmdUI* pCmdUI	-	"CCmdUI" to update.
					
	Usage :			Called from MFC.

   ============================================================*/
{

	m_editor.UpdateUndo( pCmdUI );

}

void CReportCreatorView::OnZoomIn() 
/* ============================================================
	Function :		CReportCreatorView::OnZoomIn
	Description :	Handler for the zoom in accelerator
	Access :		Protected

	Return :		void
	Parameters :	none

	Usage :			Called from MFC.

   ============================================================*/
{

	m_editor.SetZoom( m_editor.GetZoom() + m_editor.GetZoomFactor() );

}

void CReportCreatorView::OnZoomOut() 
/* ============================================================
	Function :		CReportCreatorView::OnZoomOut
	Description :	Handler for the zoom out accelerator
	Access :		Protected

	Return :		void
	Parameters :	none

	Usage :			Called from MFC.

   ============================================================*/
{

	m_editor.SetZoom( m_editor.GetZoom() - m_editor.GetZoomFactor() );

}

void CReportCreatorView::OnButtonAlignBottom() 
/* ============================================================
	Function :		CReportCreatorView::OnButtonAlignBottom
	Description :	Handler for the toolbar button AlignBottom
	Access :		Protected

	Return :		void
	Parameters :	none

	Usage :			Called from MFC.

   ============================================================*/
{

	m_editor.BottomAlignSelected();

}

void CReportCreatorView::OnUpdateButtonAlignBottom(CCmdUI* pCmdUI) 
/* ============================================================
	Function :		CReportCreatorView::OnUpdateButtonAlignBottom
	Description :	Update-handler for the UI-element
	Access :		Protected

	Return :		void
	Parameters :	CCmdUI* pCmdUI	-	"CCmdUI" to update.
					
	Usage :			Called from MFC.

   ============================================================*/
{

	pCmdUI->Enable( ( m_editor.GetSelectCount() > 1 ) );

}

void CReportCreatorView::OnButtonAlignLeft() 
/* ============================================================
	Function :		CReportCreatorView::OnButtonAlignLeft
	Description :	Handler for the toolbar button AlignLeft
	Access :		Protected

	Return :		void
	Parameters :	none

	Usage :			Called from MFC.

   ============================================================*/
{

	m_editor.LeftAlignSelected();

}

void CReportCreatorView::OnUpdateButtonAlignLeft(CCmdUI* pCmdUI) 
/* ============================================================
	Function :		CReportCreatorView::OnUpdateButtonAlignLeft
	Description :	Update-handler for the UI-element
	Access :		Protected

	Return :		void
	Parameters :	CCmdUI* pCmdUI	-	"CCmdUI" to update.
					
	Usage :			Called from MFC.

   ============================================================*/
{

	pCmdUI->Enable( ( m_editor.GetSelectCount() > 1 ) );

}

void CReportCreatorView::OnButtonAlignRight() 
/* ============================================================
	Function :		CReportCreatorView::OnButtonAlignRight
	Description :	Handler for the toolbar button AlignRight
	Access :		Protected

	Return :		void
	Parameters :	none

	Usage :			Called from MFC.

   ============================================================*/
{

	m_editor.RightAlignSelected();

}

void CReportCreatorView::OnUpdateButtonAlignRight(CCmdUI* pCmdUI) 
/* ============================================================
	Function :		CReportCreatorView::OnUpdateButtonAlignRight
	Description :	Update-handler for the UI-element
	Access :		Protected

	Return :		void
	Parameters :	CCmdUI* pCmdUI	-	"CCmdUI" to update.
					
	Usage :			Called from MFC.

   ============================================================*/
{

	pCmdUI->Enable( ( m_editor.GetSelectCount() > 1 ) );

}

void CReportCreatorView::OnButtonAlignTop() 
/* ============================================================
	Function :		CReportCreatorView::OnButtonAlignTop
	Description :	Handler for the toolbar button AlignTop
	Access :		Protected

	Return :		void
	Parameters :	none

	Usage :			Called from MFC.

   ============================================================*/
{

	m_editor.TopAlignSelected();

}

void CReportCreatorView::OnUpdateButtonAlignTop(CCmdUI* pCmdUI) 
/* ============================================================
	Function :		CReportCreatorView::OnUpdateButtonAlignTop
	Description :	Update-handler for the UI-element
	Access :		Protected

	Return :		void
	Parameters :	CCmdUI* pCmdUI	-	"CCmdUI" to update.
					
	Usage :			Called from MFC.

   ============================================================*/
{

	pCmdUI->Enable( ( m_editor.GetSelectCount() > 1 ) );

}

void CReportCreatorView::OnButtonSameSize() 
/* ============================================================
	Function :		CReportCreatorView::OnButtonSameSize
	Description :	Handler for the toolbar button SameSize
	Access :		Protected

	Return :		void
	Parameters :	none

	Usage :			Called from MFC.

   ============================================================*/
{

	m_editor.MakeSameSizeSelected();

}

void CReportCreatorView::OnUpdateButtonSameSize(CCmdUI* pCmdUI) 
/* ============================================================
	Function :		CReportCreatorView::OnUpdateButtonSameSize
	Description :	Update-handler for the toolbar button 
					SameSize.
	Access :		Protected

	Return :		void
	Parameters :	CCmdUI* pCmdUI	-	"CCmdUI" to update.
					
	Usage :			Called from MFC.

   ============================================================*/
{

	pCmdUI->Enable( ( m_editor.GetSelectCount() > 1 ) );

}

void CReportCreatorView::OnButtonZoomToFit() 
/* ============================================================
	Function :		CReportCreatorView::OnButtonZoomToFit
	Description :	Handler for the toolbar button ZoomToFit
	Access :		Protected

	Return :		void
	Parameters :	none

	Usage :			Called from MFC.

   ============================================================*/
{

	m_editor.ZoomToFitScreen();

}

void CReportCreatorView::OnButtonProperties() 
/* ============================================================
	Function :		CReportCreatorView::OnButtonProperties
	Description :	Handler for the toolbar button Properties
	Access :		Protected

	Return :		void
	Parameters :	none

	Usage :			Called from MFC.

   ============================================================*/
{

	m_editor.ShowProperties();

}

void CReportCreatorView::OnButtonAddGrid() 
/* ============================================================
	Function :		CReportCreatorView::OnButtonAddGrid
	Description :	Handler for the toolbar button AddGrid
	Access :		Protected

	Return :		void
	Parameters :	none

	Usage :			Called from MFC.

   ============================================================*/
{

	m_editor.StartDrawingObject( new CReportEntityGrid );
	
}

void CReportCreatorView::OnButtonAddPicture() 
/* ============================================================
	Function :		CReportCreatorView::OnButtonAddPicture
	Description :	Handler for the toolbar button AddPicture
	Access :		Protected

	Return :		void
	Parameters :	none

	Usage :			Called from MFC.

   ============================================================*/
{

	m_editor.StartDrawingObject( new CReportEntityPicture );
	
}


void CReportCreatorView::OnDestroy() 
/* ============================================================
	Function :		CReportCreatorView::OnDestroy
	Description :	Handler for the "WM_DESTROY"-message.
	Access :		Protected

	Return :		void
	Parameters :	none

	Usage :			Called from MFC. Saves the editor settings.

   ============================================================*/
{

	SaveSettings();
	CView::OnDestroy();
	
}

void CReportCreatorView::OnDelete() 
/* ============================================================
	Function :		CReportCreatorView::OnDelete
	Description :	Handler for the "ID_DELETE" accelerator
	Access :		Protected

	Return :		void
	Parameters :	none

	Usage :			Called from MFC

   ============================================================*/
{

	m_editor.DeleteAllSelected();
	
}

void CReportCreatorView::OnInsert() 
/* ============================================================
	Function :		CReportCreatorView::OnInsert
	Description :	Handler for the "ID_INSERT" accelerator
	Access :		Protected

	Return :		void
	Parameters :	none

	Usage :			Called from MFC

   ============================================================*/
{

	m_editor.Duplicate();
	
}

