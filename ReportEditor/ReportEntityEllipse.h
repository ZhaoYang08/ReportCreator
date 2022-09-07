#ifndef _CREPORTENTITYELLIPSE_H_B22DB9DB_5DCD_466F_BDEA453EDD6B
#define _CREPORTENTITYELLIPSE_H_B22DB9DB_5DCD_466F_BDEA453EDD6B

///////////////////////////////////////////////////////////
// File :		ReportEntityEllipse.h
// Created :	07/14/04
//

#include "DiagramEditor/DiagramEntity.h"
#include "ReportEllipseProperties.h"

class CReportEntityEllipse : public CDiagramEntity
{
public:
// Construction/destruction
	CReportEntityEllipse();
	virtual ~CReportEntityEllipse();

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

	CReportEllipseProperties	m_dlg;

};
#endif //_CREPORTENTITYELLIPSE_H_B22DB9DB_5DCD_466F_BDEA453EDD6B
