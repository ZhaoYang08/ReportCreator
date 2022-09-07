// ReportCreator.h : main header file for the REPORTCREATOR application
//

#if !defined(AFX_REPORTCREATOR_H__0645E518_3218_4E47_947B_71A530C6C3E3__INCLUDED_)
#define AFX_REPORTCREATOR_H__0645E518_3218_4E47_947B_71A530C6C3E3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CReportCreatorApp:
// See ReportCreator.cpp for the implementation of this class
//

#include "ReportEditor/DiagramEditor/DiagramClipboardHandler.h"

class CReportCreatorApp : public CWinApp
{
public:
	CReportCreatorApp();

	CDiagramClipboardHandler	m_clip;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CReportCreatorApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CReportCreatorApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

extern CReportCreatorApp theApp;

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_REPORTCREATOR_H__0645E518_3218_4E47_947B_71A530C6C3E3__INCLUDED_)
