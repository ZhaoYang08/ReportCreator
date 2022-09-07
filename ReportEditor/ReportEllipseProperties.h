#if !defined(AFX_REPORTELLIPSEPROPERTIES_H__CBCE86A4_028D_4F62_80FC_3BB81E6B127E__INCLUDED_)
#define AFX_REPORTELLIPSEPROPERTIES_H__CBCE86A4_028D_4F62_80FC_3BB81E6B127E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ReportEllipseProperties.h : header file
//

#include "ColorStatic.h"
#include "DiagramEditor/DiagramPropertyDlg.h"
#include "../resource.h"

/////////////////////////////////////////////////////////////////////////////
// CReportEllipseProperties dialog

class CReportEllipseProperties : public CDiagramPropertyDlg
{
// Construction
public:
	CReportEllipseProperties(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CReportEllipseProperties)
	enum { IDD = IDD_REPORT_DIALOG_ELLIPSE_PROPERTIES };
	CColorStatic	m_ctrlFillColor;
	CColorStatic	m_ctrlBorderColor;
	BOOL	m_border;
	BOOL	m_fill;
	CComboBox	m_ctrlBorderStyle;
	int		m_borderThickness;
	CString m_name;
	//}}AFX_DATA

	virtual void SetValues();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CReportEllipseProperties)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CReportEllipseProperties)
	virtual void OnOK();
	virtual void OnCancel();
	virtual BOOL OnInitDialog();
	afx_msg void OnButtonBorderColor();
	afx_msg void OnButtonFillColor();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	COLORREF	m_borderColor;
	COLORREF	m_fillColor;
	int			m_borderStyle;

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_REPORTELLIPSEPROPERTIES_H__CBCE86A4_028D_4F62_80FC_3BB81E6B127E__INCLUDED_)
