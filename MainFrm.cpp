/* ==========================================================================
	Class :			CMainFrm

	Author :		Johan Rosengren, Abstrakt Mekanik AB

	Date :			2004-07-25

	Purpose :		"CMainFrm" is the main window class of the application.

	Description :	The class is automatically created by MSVC++

	Usage :			Created by MFC.

   ========================================================================*/

#include "stdafx.h"
#include "ReportCreator.h"

#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNAMIC(CMainFrame, CMDIFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CMDIFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

/////////////////////////////////////////////////////////////////////////////
// CMainFrame construction/destruction

CMainFrame::CMainFrame()
/* ============================================================
	Function :		CMainFrame::CMainFrame
	Description :	Constructor
	Access :		Public

	Return :		void
	Parameters :	none

	Usage :			

   ============================================================*/
{
}

CMainFrame::~CMainFrame()
/* ============================================================
	Function :		CMainFrame::~CMainFrame
	Description :	Destructor
	Access :		Public

	Return :		void
	Parameters :	none

	Usage :			

   ============================================================*/
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
/* ============================================================
	Function :		CMainFrame::OnCreate
	Description :	Called when creating the main window.
	Access :		Protected

	Return :		int								-	-1 if fail
	Parameters :	LPCREATESTRUCT lpCreateStruct	-	Creation 
														parameters
					
	Usage :			Called from MFC

   ============================================================*/
{
	if (CMDIFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP
		| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}

	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
		  sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}

	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndToolBar);

	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
/* ============================================================
	Function :		CMainFrame::PreCreateWindow
	Description :	Called before the main window is created
	Access :		Public

	Return :		BOOL				-	"TRUE" if OK.
	Parameters :	CREATESTRUCT& cs	-	Creation parameters
					
	Usage :			Called from MFC

   ============================================================*/
{
	if( !CMDIFrameWnd::PreCreateWindow(cs) )
		return FALSE;

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
/* ============================================================
	Function :		CMainFrame::AssertValid
	Description :	Checks if the object is valid
	Access :		Public

	Return :		void
	Parameters :	none

	Usage :			Debug function

   ============================================================*/
{
	CMDIFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
/* ============================================================
	Function :		CMainFrame::Dump
	Description :	Dumps object data
	Access :		Public

	Return :		void
	Parameters :	CDumpContext& dc	-	Dump context
					
	Usage :			Debug function

   ============================================================*/
{
	CMDIFrameWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers

