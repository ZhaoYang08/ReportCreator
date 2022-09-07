/* ==========================================================================
	Class :			CChildFrm

	Author :		Johan Rosengren, Abstrakt Mekanik AB

	Date :			2004-07-25

	Purpose :		"CChildFrm" is derived from "CMDIChildWnd" and is an 
					MFC-class for MDI-children.

	Description :	Standard Wizard-created class.

	Usage :			Created by MFC.

   ========================================================================*/

#include "stdafx.h"
#include "ReportCreator.h"

#include "ChildFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CChildFrame

IMPLEMENT_DYNCREATE(CChildFrame, CMDIChildWnd)

BEGIN_MESSAGE_MAP(CChildFrame, CMDIChildWnd)
	//{{AFX_MSG_MAP(CChildFrame)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CChildFrame construction/destruction

CChildFrame::CChildFrame()
/* ============================================================
	Function :		CChildFrame::CChildFrame
	Description :	Constructor
	Access :		Public

	Return :		void
	Parameters :	none

	Usage :			

   ============================================================*/
{
}

CChildFrame::~CChildFrame()
/* ============================================================
	Function :		CChildFrame::~CChildFrame
	Description :	Destructor
	Access :		Public

	Return :		void
	Parameters :	none

	Usage :			

   ============================================================*/
{
}

BOOL CChildFrame::PreCreateWindow(CREATESTRUCT& cs)
/* ============================================================
	Function :		CChildFrame::PreCreateWindow
	Description :	Called before the window is created
	Access :		Public

	Return :		BOOL				-	"TRUE" if created ok
	Parameters :	CREATESTRUCT& cs	-	Creation parameters
					
	Usage :			Called from MFC

   ============================================================*/
{
	if( !CMDIChildWnd::PreCreateWindow(cs) )
		return FALSE;

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CChildFrame diagnostics

#ifdef _DEBUG
void CChildFrame::AssertValid() const
/* ============================================================
	Function :		CChildFrame::AssertValid
	Description :	Asserts the object being valid
	Access :		Public

	Return :		void
	Parameters :	none

	Usage :			Debug function

   ============================================================*/
{
	CMDIChildWnd::AssertValid();
}

void CChildFrame::Dump(CDumpContext& dc) const
/* ============================================================
	Function :		CChildFrame::Dump
	Description :	Dumps object data
	Access :		Public

	Return :		void
	Parameters :	CDumpContext& dc	-	Dump context
					
	Usage :			Debug function

   ============================================================*/
{
	CMDIChildWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CChildFrame message handlers
