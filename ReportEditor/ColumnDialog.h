#if !defined(AFX_COLUMNDIALOG_H__78C6D0CC_B685_4D09_B621_1F662028DC57__INCLUDED_)
#define AFX_COLUMNDIALOG_H__78C6D0CC_B685_4D09_B621_1F662028DC57__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ColumnDialog.h : header file
//

#include "Column.h"

/////////////////////////////////////////////////////////////////////////////
// CColumnDialog dialog

class CColumnDialog : public CDialog
{
// Construction
public:
	LOGFONT m_lf;
	COLORREF	m_color;
	CColumn*	m_column;
	CColumnDialog(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CColumnDialog)
	enum { IDD = IDD_DIALOG_COLUMN };
	CString	m_width;
	int		m_justification;
	CString	m_name;
	//}}AFX_DATA

	int	m_measurement;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CColumnDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CColumnDialog)
	afx_msg void OnButtonFont();
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()


};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_COLUMNDIALOG_H__78C6D0CC_B685_4D09_B621_1F662028DC57__INCLUDED_)
