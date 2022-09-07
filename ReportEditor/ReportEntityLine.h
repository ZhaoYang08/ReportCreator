#ifndef _CREPORTENTITYLINE_H_9D35E8C_89C8_4D2A_B89FB0442EAF
#define _CREPORTENTITYLINE_H_9D35E8C_89C8_4D2A_B89FB0442EAF

///////////////////////////////////////////////////////////
// File :		ReportEntityLine.h
// Created :	07/14/04
//

#include "DiagramEditor/DiagramLine.h"
#include "ReportLineProperties.h"

class CReportEntityLine : public CDiagramLine
{
public:
// Construction/destruction
	CReportEntityLine();
	virtual ~CReportEntityLine();

	virtual CDiagramEntity* Clone();
	virtual void Copy( CDiagramEntity * obj );
	virtual BOOL	FromString( const CString& str );
	virtual CString	GetString() const;
	static CDiagramEntity* CreateFromString( const CString & str );

	virtual void			Draw( CDC* dc, CRect rect );

// Operations
	int GetBorderThickness() const;
	void SetBorderThickness( int value );
	int GetBorderStyle() const;
	void SetBorderStyle( int value );
	COLORREF GetBorderColor() const;
	void SetBorderColor( COLORREF value );


// Attributes

private:
	int m_borderThickness;
	int m_borderStyle;
	COLORREF m_borderColor;

	CReportLineProperties	m_dlg;

};
#endif //_CREPORTENTITYLINE_H_9D35E8C_89C8_4D2A_B89FB0442EAF
