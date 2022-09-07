#ifndef _CREPORTENTITYPICTURE_H_C3863707_6C7A_43F6_B33FFC4BE4D5
#define _CREPORTENTITYPICTURE_H_C3863707_6C7A_43F6_B33FFC4BE4D5

///////////////////////////////////////////////////////////
// File :		ReportEntityPicture.h
// Created :	07/14/04
//

#include "DiagramEditor/DiagramEntity.h"
#include "ReportPictureProperties.h"

class CReportEntityPicture : public CDiagramEntity
{
public:
// Construction/destruction
	CReportEntityPicture();
	virtual ~CReportEntityPicture();

	virtual CDiagramEntity* Clone();
	virtual void Copy( CDiagramEntity * obj );
	virtual BOOL	FromString( const CString& str );
	virtual CString	GetString() const;
	static CDiagramEntity* CreateFromString( const CString & str );

	virtual void			Draw( CDC* dc, CRect rect );

// Operations
	BOOL GetBorder() const;
	void SetBorder( BOOL value );
	int GetBorderThickness() const;
	void SetBorderThickness( int value );
	int GetBorderStyle() const;
	void SetBorderStyle( int value );
	COLORREF GetBorderColor() const;
	void SetBorderColor( COLORREF value );
	void SetFilename( const CString& filename );
	CString GetFilename() const;

	void AdjustSize();

// Attributes

private:
	BOOL m_border;
	int m_borderThickness;
	int m_borderStyle;
	COLORREF m_borderColor;
	BOOL m_fill;
	COLORREF m_fillColor;

	CString m_filename;
	HBITMAP m_bitmap;

	CReportPictureProperties	m_dlg;

};
#endif //_CREPORTENTITYPICTURE_H_C3863707_6C7A_43F6_B33FFC4BE4D5
