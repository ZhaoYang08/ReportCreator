#ifndef _REPORTENTITYLABEL_H_
#define _REPORTENTITYLABEL_H_

#include "DiagramEditor/DiagramEntity.h"
#include "ReportLabelProperties.h"

class CReportEntityLabel : public CDiagramEntity
{
public:
	CReportEntityLabel();
	~CReportEntityLabel();

	virtual	CDiagramEntity* Clone();
	virtual void	Copy( CDiagramEntity* obj );
	virtual BOOL	FromString( const CString& str );
	virtual CString	GetString() const;
	static CDiagramEntity* CreateFromString( const CString & str );

	virtual void			Draw( CDC* dc, CRect rect );

	CString GetFontName() const;
	void SetFontName( CString value );
	int GetFontSize() const;
	void SetFontSize( int value );
	BOOL GetFontBold() const;
	void SetFontBold( BOOL value );
	BOOL GetFontItalic() const;
	void SetFontItalic( BOOL value );
	BOOL GetFontUnderline() const;
	void SetFontUnderline( BOOL value );
	BOOL GetFontStrikeout() const;
	void SetFontStrikeout( BOOL value );
	COLORREF GetFontColor() const;
	void SetFontColor( COLORREF value );
	void SetJustification( int justification );
	int GetJustification() const;
	void SetFontCharset( int charset );
	int GetFontCharset() const;

private:

	CString		m_fontName;
	int			m_fontSize;
	BOOL		m_fontBold;
	BOOL		m_fontItalic;
	BOOL		m_fontUnderline;
	BOOL		m_fontStrikeout;
	COLORREF	m_fontColor;
	int			m_justification;
	int			m_charset;

	CReportLabelProperties	m_dlg;

};

#endif //_REPORTENTITYLABEL_H_