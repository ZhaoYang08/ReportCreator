#if !defined(AFX_PICTUREPREVIEW_H__965AAFF9_02F8_4D41_BBCA_10BD908FBDFD__INCLUDED_)
#define AFX_PICTUREPREVIEW_H__965AAFF9_02F8_4D41_BBCA_10BD908FBDFD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PicturePreview.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPicturePreview window

class CPicturePreview : public CStatic
{
// Construction
public:
	CPicturePreview();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPicturePreview)
	//}}AFX_VIRTUAL

// Implementation
public:
	CString GetFilename() const;
	void SetFilename( const CString& filename );
	virtual ~CPicturePreview();

	// Generated message map functions
protected:
	//{{AFX_MSG(CPicturePreview)
	afx_msg void OnPaint();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	CString m_filename;
	HBITMAP m_bitmap;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PICTUREPREVIEW_H__965AAFF9_02F8_4D41_BBCA_10BD908FBDFD__INCLUDED_)
