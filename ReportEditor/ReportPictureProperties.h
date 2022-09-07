#if !defined(AFX_REPORTPICTUREPROPERTIES_H__0CF90F37_2701_475E_AFDF_509A6DCA4320__INCLUDED_)
#define AFX_REPORTPICTUREPROPERTIES_H__0CF90F37_2701_475E_AFDF_509A6DCA4320__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ReportPictureProperties.h : header file
//

#include "PicturePreview.h"
#include "../resource.h"
#include "DiagramEditor/DiagramPropertyDlg.h"
#include "ColorStatic.h"

/////////////////////////////////////////////////////////////////////////////
// CReportPictureProperties dialog

class CReportPictureProperties : public CDiagramPropertyDlg
{
// Construction
public:
	CReportPictureProperties(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CReportPictureProperties)
	enum { IDD = IDD_REPORT_DIALOG_PICTURE_PROPERTIES };
	CPicturePreview	m_preview;
	CString m_filename;
	CComboBox	m_ctrlBorderStyle;
	CColorStatic	m_ctrlBorderColor;
	int		m_borderThickness;
	BOOL	m_border;
	CString m_name;
	//}}AFX_DATA

	virtual void SetValues();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CReportPictureProperties)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CReportPictureProperties)
	virtual void OnOK();
	virtual void OnCancel();
	afx_msg void OnButtonBrowse();
	virtual BOOL OnInitDialog();
	afx_msg void OnButtonBorderColor();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	COLORREF	m_borderColor;
	int			m_borderStyle;

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_REPORTPICTUREPROPERTIES_H__0CF90F37_2701_475E_AFDF_509A6DCA4320__INCLUDED_)
