#if !defined(AFX_REPORTBOXPROPERTIES_H__41B4B91F_86F8_4392_BAC9_29169E84A68A__INCLUDED_)
#define AFX_REPORTBOXPROPERTIES_H__41B4B91F_86F8_4392_BAC9_29169E84A68A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ReportBoxProperties.h : header file
//

#include "ColorStatic.h"
#include "DiagramEditor/DiagramPropertyDlg.h"
#include "../resource.h"

/////////////////////////////////////////////////////////////////////////////
// CReportBoxProperties dialog

class CReportBoxProperties : public CDiagramPropertyDlg
{
// Construction
public:
	CReportBoxProperties(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CReportBoxProperties)
	enum { IDD = IDD_REPORT_DIALOG_BOX_PROPERTIES };
	CComboBox	m_ctrlBorderStyle;
	CColorStatic	m_ctrlFillColor;
	CColorStatic	m_ctrlBorderColor;
	int		m_borderThickness;
	BOOL	m_fill;
	BOOL	m_border;
	CString m_name;
	//}}AFX_DATA

	virtual void SetValues();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CReportBoxProperties)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CReportBoxProperties)
	virtual void OnOK();
	virtual void OnCancel();
	virtual BOOL OnInitDialog();
	afx_msg void OnButtonFillColor();
	afx_msg void OnButtonBorderColor();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	COLORREF	m_borderColor;
	COLORREF	m_fillColor;

	int			m_borderStyle;

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_REPORTBOXPROPERTIES_H__41B4B91F_86F8_4392_BAC9_29169E84A68A__INCLUDED_)
