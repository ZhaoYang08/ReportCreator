/* ==========================================================================
	Class :			CReportCreatorDoc

	Author :		Johan Rosengren, Abstrakt Mekanik AB

	Date :			2004-07-25

	Purpose :		"CReportCreatorDoc" derives from "CDocument" and is the 
					document class of the application.

	Description :	The class is automatically created by MSVC++

	Usage :			Created from MFC

   ========================================================================*/

#include "stdafx.h"
#include <locale.h>

#include "ReportCreator.h"
#include "ReportCreatorDoc.h"

#include "ReportEditor/ReportControlFactory.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#pragma warning( disable : 4706 )

/////////////////////////////////////////////////////////////////////////////
// CReportCreatorDoc

IMPLEMENT_DYNCREATE(CReportCreatorDoc, CDocument)

BEGIN_MESSAGE_MAP(CReportCreatorDoc, CDocument)
	//{{AFX_MSG_MAP(CReportCreatorDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CReportCreatorDoc construction/destruction

CReportCreatorDoc::CReportCreatorDoc()
/* ============================================================
	Function :		CReportCreatorDoc::CReportCreatorDoc
	Description :	Constructor
	Access :		Public

	Return :		void
	Parameters :	none

	Usage :			

   ============================================================*/
{

	m_objs.SetClipboardHandler( &( theApp.m_clip ) );

}

CReportCreatorDoc::~CReportCreatorDoc()
/* ============================================================
	Function :		CReportCreatorDoc::~CReportCreatorDoc
	Description :	Destructor
	Access :		Public

	Return :		void
	Parameters :	none

	Usage :			

   ============================================================*/
{
}

BOOL CReportCreatorDoc::OnNewDocument()
/* ============================================================
	Function :		CReportCreatorDoc::OnNewDocument
	Description :	Called as soon as a new document is created/loaded.
	Access :		Public

	Return :		BOOL	-	"TRUE" if loaded/created ok.
	Parameters :	none

	Usage :			Overridden to clear the data container.

   ============================================================*/
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	m_objs.Clear();

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CReportCreatorDoc serialization

void CReportCreatorDoc::Serialize(CArchive& ar)
/* ============================================================
	Function :		CReportCreatorDoc::Serialize
	Description :	Called when a documnet is saved/loaded from 
					file.
	Access :		Public

	Return :		void
	Parameters :	CArchive& ar	-	Archive to save/load 
										from.
					
	Usage :			Overridden to save/load to the data 
					container.

   ============================================================*/
{

	// Save old locale and set locale for decimal-point character to "C"
	CString oldLocale = _tsetlocale(LC_NUMERIC, NULL);
	_tsetlocale(LC_NUMERIC, "C"); 

	// Saving and loading to/from a text file
	if (ar.IsStoring())
	{
		ar.WriteString( m_objs.GetString() + _T( "\r\n" ) );
		int count = 0;
		CDiagramEntity* obj;
		while( ( obj = m_objs.GetAt( count++ ) ) )
			ar.WriteString( obj->GetString() + _T( "\r\n" ) );

		m_objs.SetModified( FALSE );
	}
	else
	{

		m_objs.Clear();
		CString str;
		while(ar.ReadString( str ) )
		{

			if( !m_objs.FromString( str ) )
			{
				CDiagramEntity* obj = CReportControlFactory::CreateFromString( str );
				if( obj )
					m_objs.Add( obj );
			}
		}

		m_objs.SetModified( FALSE );
	}

	// restore old LC_NUMERIC locale
	_tsetlocale(LC_NUMERIC, oldLocale); 

}

/////////////////////////////////////////////////////////////////////////////
// CReportCreatorDoc diagnostics

#ifdef _DEBUG
void CReportCreatorDoc::AssertValid() const
/* ============================================================
	Function :		CReportCreatorDoc::AssertValid
	Description :	Checks the object validity
	Access :		Public

	Return :		void
	Parameters :	none

	Usage :			Debug function

   ============================================================*/
{
	CDocument::AssertValid();
}

void CReportCreatorDoc::Dump(CDumpContext& dc) const
/* ============================================================
	Function :		CReportCreatorDoc::Dump
	Description :	Dumps object data
	Access :		Public

	Return :		void
	Parameters :	CDumpContext& dc	-	Dump context
					
	Usage :			Debug function

   ============================================================*/
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CReportCreatorDoc commands

BOOL CReportCreatorDoc::SaveModified() 
/* ============================================================
	Function :		CReportCreatorDoc::SaveModified
	Description :	Called to see if the Data changed, save?-
					dialog should be displayed.
	Access :		Public

	Return :		BOOL	-	Not interested
	Parameters :	none

	Usage :			Overridden to set the dirty-flag from the 
					container.

   ============================================================*/
{

	SetModifiedFlag( m_objs.IsModified() );
	return CDocument::SaveModified();

}

CDiagramEntityContainer* CReportCreatorDoc::GetData()
/* ============================================================
	Function :		CReportCreatorDoc::GetData
	Description :	Gets a pointer to the data container.
	Access :		Public

	Return :		CDiagramEntityContainer*	-	Data container
	Parameters :	none

	Usage :			Call to access the data container.

   ============================================================*/
{

	return &m_objs;

}

#pragma warning( default : 4706 )
