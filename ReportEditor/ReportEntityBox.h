#ifndef _CREPORTENTITYBOX_H_C3863707_6C7A_43F6_B33FFC4BE4D5
#define _CREPORTENTITYBOX_H_C3863707_6C7A_43F6_B33FFC4BE4D5

///////////////////////////////////////////////////////////
// File :		ReportEntityBox.h
// Created :	07/14/04
//

#include "DiagramEditor/DiagramEntity.h"
#include "ReportBoxProperties.h"

class CReportEntityBox : public CDiagramEntity
{
public:
// Construction/destruction
	CReportEntityBox();
	virtual ~CReportEntityBox();

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
	BOOL GetFill() const;
	void SetFill( BOOL value );
	COLORREF GetFillColor() const;
	void SetFillColor( COLORREF value );

// Attributes

private:
	BOOL m_border;
	int m_borderThickness;
	int m_borderStyle;
	COLORREF m_borderColor;
	BOOL m_fill;
	COLORREF m_fillColor;

	CReportBoxProperties	m_dlg;

};
#endif //_CREPORTENTITYBOX_H_C3863707_6C7A_43F6_B33FFC4BE4D5
