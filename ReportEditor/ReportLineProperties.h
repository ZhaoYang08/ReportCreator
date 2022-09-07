#if !defined(AFX_REPORTLINEPROPERTIES_H__5296DFB9_BAF5_4D6F_B01A_7B15548A9D44__INCLUDED_)
#define AFX_REPORTLINEPROPERTIES_H__5296DFB9_BAF5_4D6F_B01A_7B15548A9D44__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ReportLineProperties.h : header file
//

#include "ColorStatic.h"
#include "DiagramEditor/DiagramPropertyDlg.h"
#include "../resource.h"

/////////////////////////////////////////////////////////////////////////////
// CReportLineProperties dialog

class CReportLineProperties : public CDiagramPropertyDlg
{
// Construction
public:
	CReportLineProperties(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CReportLineProperties)
	enum { IDD = IDD_REPORT_DIALOG_LINE_PROPERTIES };
	CColorStatic	m_ctrlColor;
	CComboBox	m_ctrlStyle;
	int		m_thickness;
	CString m_name;
	//}}AFX_DATA

	virtual void SetValues();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CReportLineProperties)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CReportLineProperties)
	virtual void OnOK();
	virtual void OnCancel();
	virtual BOOL OnInitDialog();
	afx_msg void OnButtonColor();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	COLORREF	m_color;
	int			m_lineStyle;

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_REPORTLINEPROPERTIES_H__5296DFB9_BAF5_4D6F_B01A_7B15548A9D44__INCLUDED_)
