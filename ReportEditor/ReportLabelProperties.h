#if !defined(AFX_REPORTLABELPROPERTIES_H__CCB51690_71C2_4FF0_9A06_6055EBAAF76F__INCLUDED_)
#define AFX_REPORTLABELPROPERTIES_H__CCB51690_71C2_4FF0_9A06_6055EBAAF76F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ReportLabelProperties.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CReportLabelProperties dialog

#include "DiagramEditor/DiagramPropertyDlg.h"
#include "../resource.h"

class CReportLabelProperties : public CDiagramPropertyDlg
{
// Construction
public:
	CReportLabelProperties(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CReportLabelProperties)
	enum { IDD = IDD_REPORT_DIALOG_LABEL_PROPERTIES };
	CString	m_contents;
	int		m_justification;
	CString m_name;
	//}}AFX_DATA

	virtual void SetValues();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CReportLabelProperties)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CReportLabelProperties)
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

#endif // !defined(AFX_REPORTLABELPROPERTIES_H__CCB51690_71C2_4FF0_9A06_6055EBAAF76F__INCLUDED_)
