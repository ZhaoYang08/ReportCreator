#if !defined(AFX_REPORTFIELDPROPERTIES_H__CCB51690_71C2_4FF0_9A06_6055EBAAF76F__INCLUDED_)
#define AFX_REPORTFIELDPROPERTIES_H__CCB51690_71C2_4FF0_9A06_6055EBAAF76F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ReportFieldProperties.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CReportFieldProperties dialog

#include "DiagramEditor/DiagramPropertyDlg.h"
#include "../resource.h"

class CReportFieldProperties : public CDiagramPropertyDlg
{
// Construction
public:
	CReportFieldProperties(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CReportFieldProperties)
	enum { IDD = IDD_REPORT_DIALOG_LABEL_PROPERTIES };
	CString	m_contents;
	int		m_justification;
	//}}AFX_DATA

	virtual void SetValues();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CReportFieldProperties)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CReportFieldProperties)
	virtual void OnOK();
	virtual void OnCancel();
	afx_msg void OnButtonFont();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:

	LOGFONT		m_lf;
	COLORREF	m_color;

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_REPORTFIELDPROPERTIES_H__CCB51690_71C2_4FF0_9A06_6055EBAAF76F__INCLUDED_)
