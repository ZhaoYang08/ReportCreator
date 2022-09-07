#ifndef _CREPORTENTITYGRID_H_C3863707_6C7A_43F6_B33FFC4BE4D5
#define _CREPORTENTITYGRID_H_C3863707_6C7A_43F6_B33FFC4BE4D5

///////////////////////////////////////////////////////////
// File :		ReportEntityGrid.h
// Created :	07/14/04
//

#include "DiagramEditor/DiagramEntity.h"
#include "ReportGridProperties.h"
#include "ColumnContainer.h"

class CReportEntityGrid : public CDiagramEntity
{
	friend class CReportGridProperties;

public:
// Construction/destruction
	CReportEntityGrid();
	virtual ~CReportEntityGrid();

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

	BOOL GetColumnLines() const;
	void SetColumnLines( BOOL value );
	int GetColumnLineThickness() const;
	void SetColumnLineThickness( int value );
	int GetColumnLineStyle() const;
	void SetColumnLineStyle( int value );
	COLORREF GetColumnLineColor() const;
	void SetColumnLineColor( COLORREF value );

	BOOL GetRowLines() const;
	void SetRowLines( BOOL value );
	int GetRowLineThickness() const;
	void SetRowLineThickness( int value );
	int GetRowLineStyle() const;
	void SetRowLineStyle( int value );
	COLORREF GetRowLineColor() const;
	void SetRowLineColor( COLORREF value );
	int GetLPI() const;
	void SetLPI( int value );

// Attributes

private:
	BOOL		m_border;
	int			m_borderThickness;
	int			m_borderStyle;
	COLORREF	m_borderColor;

	BOOL		m_columnLines;
	int			m_columnThickness;
	int			m_columnStyle;
	COLORREF	m_columnColor;

	BOOL		m_rowLines;
	int			m_rowThickness;
	int			m_rowStyle;
	COLORREF	m_rowColor;

	int			m_lpi;

	CReportGridProperties	m_dlg;

	CColumnContainer	m_columns;

	CFont* GetColumnFont( CColumn* obj );


};

#endif //_CREPORTENTITYGRID_H_C3863707_6C7A_43F6_B33FFC4BE4D5
