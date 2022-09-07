#if !defined(AFX_REPORTGRIDPROPERTIES_H__EC5D8AF8_EE76_40A1_A2D6_15F1657CCBBC__INCLUDED_)
#define AFX_REPORTGRIDPROPERTIES_H__EC5D8AF8_EE76_40A1_A2D6_15F1657CCBBC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ReportGridProperties.h : header file
//

#include "..\resource.h"
#include "ColorStatic.h"
#include "DiagramEditor/DiagramPropertyDlg.h"
#include "ColumnContainer.h"
#include "ExListBox.h"

/////////////////////////////////////////////////////////////////////////////
// ReportGridProperties dialog

class CReportGridProperties : public CDiagramPropertyDlg
{
// Construction
public:
	CReportGridProperties(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CReportGridProperties)
	enum { IDD = IDD_REPORT_DIALOG_GRID_PROPERTIES };
	CExListBox	m_ctrlColumnList;
	CColorStatic	m_ctrlRowColor;
	CColorStatic	m_ctrlColumnColor;
	CColorStatic	m_ctrlBorderColor;
	CComboBox	m_ctrlRowStyle;
	CComboBox	m_ctrlColumnStyle;
	CComboBox	m_ctrlBorderStyle;
	BOOL	m_border;
	BOOL	m_columns;
	BOOL	m_rows;
	int		m_borderThickness;
	int		m_columnThickness;
	int		m_rowThickness;
	int		m_measurements;
	int		m_lpi;
	CString	m_name;
	//}}AFX_DATA


	virtual void SetValues();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CReportGridProperties)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CReportGridProperties)
	virtual void OnOK();
	virtual void OnCancel();
	afx_msg void OnButtonColumnColor();
	afx_msg void OnButtonRowColor();
	afx_msg void OnButtonBorderColor();
	afx_msg void OnButtonDelete();
	afx_msg void OnButtonDown();
	afx_msg void OnButtonUp();
	afx_msg void OnButtonAdd();
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeComboMeasurements();
	//}}AFX_MSG

	LRESULT OnListboxDblClick( WPARAM, LPARAM );
	LRESULT OnListboxDelete( WPARAM, LPARAM );

	DECLARE_MESSAGE_MAP()
private:

	CString				GetColumnText( CColumn* obj );
	void				RefillColumnList();

	COLORREF			m_borderColor;
	COLORREF			m_columnColor;
	COLORREF			m_rowColor;
	int					m_borderStyle;
	int					m_columnStyle;
	int					m_rowStyle;

	CColumnContainer	m_columnarray;
	
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_REPORTGRIDPROPERTIES_H__EC5D8AF8_EE76_40A1_A2D6_15F1657CCBBC__INCLUDED_)
