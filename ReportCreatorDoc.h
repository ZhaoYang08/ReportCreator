// ReportCreatorDoc.h : interface of the CReportCreatorDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_REPORTCREATORDOC_H__7ECF730E_6A23_4FE1_9DF5_56585ABA1836__INCLUDED_)
#define AFX_REPORTCREATORDOC_H__7ECF730E_6A23_4FE1_9DF5_56585ABA1836__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define HINT_SET_SIZE 1

#include "ReportEditor/DiagramEditor/DiagramEntityContainer.h"

class CReportCreatorDoc : public CDocument
{
protected: // create from serialization only
	CReportCreatorDoc();
	DECLARE_DYNCREATE(CReportCreatorDoc)

// Attributes
public:
	
	CDiagramEntityContainer* GetData();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CReportCreatorDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	protected:
	virtual BOOL SaveModified();
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CReportCreatorDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CReportCreatorDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	CDiagramEntityContainer	m_objs;

};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_REPORTCREATORDOC_H__7ECF730E_6A23_4FE1_9DF5_56585ABA1836__INCLUDED_)
