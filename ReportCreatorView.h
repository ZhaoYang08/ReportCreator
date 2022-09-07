// ReportCreatorView.h : interface of the CReportCreatorView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_REPORTCREATORVIEW_H__FD25583C_8991_4117_853F_4264E9678998__INCLUDED_)
#define AFX_REPORTCREATORVIEW_H__FD25583C_8991_4117_853F_4264E9678998__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ReportEditor/ReportEditor.h"
#include "HorzRuler.h"
#include "VertRuler.h"
#include "CornerBox.h"

class CReportCreatorView : public CView
{
protected: // create from serialization only
	CReportCreatorView();
	DECLARE_DYNCREATE(CReportCreatorView)

// Attributes
public:
	CReportCreatorDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CReportCreatorView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void OnInitialUpdate();
	protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CReportCreatorView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CReportCreatorView)
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnButtonSettings();
	afx_msg void OnButtonGrid();
	afx_msg void OnUpdateButtonGrid(CCmdUI* pCmdUI);
	afx_msg void OnButtonMargin();
	afx_msg void OnUpdateButtonMargin(CCmdUI* pCmdUI);
	afx_msg void OnButtonSnap();
	afx_msg void OnUpdateButtonSnap(CCmdUI* pCmdUI);
	afx_msg void OnButtonAddBox();
	afx_msg void OnButtonAddEllipse();
	afx_msg void OnButtonAddField();
	afx_msg void OnButtonAddLabel();
	afx_msg void OnButtonAddLine();
	afx_msg void OnEditCopy();
	afx_msg void OnUpdateEditCopy(CCmdUI* pCmdUI);
	afx_msg void OnEditCut();
	afx_msg void OnUpdateEditCut(CCmdUI* pCmdUI);
	afx_msg void OnEditPaste();
	afx_msg void OnUpdateEditPaste(CCmdUI* pCmdUI);
	afx_msg void OnEditUndo();
	afx_msg void OnUpdateEditUndo(CCmdUI* pCmdUI);
	afx_msg void OnZoomIn();
	afx_msg void OnZoomOut();
	afx_msg void OnButtonAlignBottom();
	afx_msg void OnUpdateButtonAlignBottom(CCmdUI* pCmdUI);
	afx_msg void OnButtonAlignLeft();
	afx_msg void OnUpdateButtonAlignLeft(CCmdUI* pCmdUI);
	afx_msg void OnButtonAlignRight();
	afx_msg void OnUpdateButtonAlignRight(CCmdUI* pCmdUI);
	afx_msg void OnButtonAlignTop();
	afx_msg void OnUpdateButtonAlignTop(CCmdUI* pCmdUI);
	afx_msg void OnButtonSameSize();
	afx_msg void OnUpdateButtonSameSize(CCmdUI* pCmdUI);
	afx_msg void OnButtonZoomToFit();
	afx_msg void OnButtonProperties();
	afx_msg void OnButtonAddGrid();
	afx_msg void OnButtonAddPicture();
	afx_msg void OnDestroy();
	afx_msg void OnDelete();
	afx_msg void OnInsert();
	//}}AFX_MSG

	LRESULT OnEditorHScroll( WPARAM, LPARAM );
	LRESULT OnEditorVScroll( WPARAM, LPARAM );
	LRESULT OnEditorZoom( WPARAM, LPARAM );
	LRESULT OnEditorMouse( WPARAM z, LPARAM );
	LRESULT OnRulerMeasurements( WPARAM, LPARAM );

	DECLARE_MESSAGE_MAP()

private:

	// Private data
	CReportEditor	m_editor;
	CHorzRuler		m_horzRuler;
	CVertRuler		m_vertRuler;
	CCornerBox		m_cornerBox;

	int				m_screenResolutionX;

	void			SaveSettings();

};

#ifndef _DEBUG  // debug version in ReportCreatorView.cpp
inline CReportCreatorDoc* CReportCreatorView::GetDocument()
   { return (CReportCreatorDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_REPORTCREATORVIEW_H__FD25583C_8991_4117_853F_4264E9678998__INCLUDED_)
