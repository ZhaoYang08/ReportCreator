#ifndef _CCOLUMN_H_B68FFBBA_AE9_43AE_B99B93E38FF5
#define _CCOLUMN_H_B68FFBBA_AE9_43AE_B99B93E38FF5

///////////////////////////////////////////////////////////
// File :		Column.h
// Created :	07/18/04
//

class CColumn : public CObject
{
// Construction/destruction
public:
	CColumn();
	virtual ~CColumn();

	CColumn* Clone();
	void FromString( const CString& str );
	CString GetString() const;

// Operations
	CString GetName() const;
	void SetName( CString value );
	int GetWidth() const;
	void SetWidth( int value );
	CString GetFontName() const;
	void SetFontName( CString value );
	int GetFontSize() const;
	void SetFontSize( int value );
	BOOL GetFontItalic() const;
	void SetFontItalic( BOOL value );
	BOOL GetFontUnderline() const;
	void SetFontUnderline( BOOL value );
	BOOL GetFontBold() const;
	void SetFontBold( BOOL value );
	BOOL GetFontStrikeout() const;
	void SetFontStrikeout( BOOL value );
	COLORREF GetFontColor() const;
	void SetFontColor( COLORREF value );
	int GetJustification() const;
	void SetJustification( int value );
	int GetFontCharset() const;
	void SetFontCharset( int value );

// Attributes

private:
	CString m_name;
	int m_width;
	CString m_fontName;
	int m_fontSize;
	BOOL m_fontItalic;
	BOOL m_fontUnderline;
	BOOL m_fontBold;
	BOOL m_fontStrikeOut;
	COLORREF m_fontColor;
	int m_justification;
	int m_charset;

};

#endif //_CCOLUMN_H_B68FFBBA_AE9_43AE_B99B93E38FF5
