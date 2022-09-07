#ifndef _REPORTENTITYSETTINGS_H_
#define _REPORTENTITYSETTINGS_H_

#include "ReportEntityLabel.h"
#include "ReportEntityBox.h"
#include "ReportEntityEllipse.h"
#include "ReportEntityLine.h"
#include "ReportEntityPicture.h"

#include "ReportEntityField.h"
#include "ReportEntityGrid.h"

#include "Column.h"

class CReportEntitySettings
{

public:

    static CReportEntitySettings * GetRESInstance();

	void SetLogFont( LOGFONT& logfont );
	void SetColor( COLORREF color );
	void SetJustification( int justification );

	void GetFontSettings( CReportEntityLabel* obj );
	void GetFontSettings( CReportEntityField* obj );
	void GetFontSettings( CColumn* obj );

	void GetBorderSettings( CReportEntityBox* obj );
	void GetBorderSettings( CReportEntityEllipse* obj );
	void GetBorderSettings( CReportEntityGrid* obj );
	void GetBorderSettings( CReportEntityPicture* obj );

	void GetLineSettings( CReportEntityLine* obj );

	void GetColumnLineSettings( CReportEntityGrid* obj );
	void GetRowLineSettings( CReportEntityGrid* obj );

	void GetFillSettings( CReportEntityBox* obj );
	void GetFillSettings( CReportEntityEllipse* obj );

	void SetLineColor( COLORREF color );
	void SetLineStyle( int style );
	void SetLineThickness( int thickness );
	void SetFill( BOOL fill );
	void SetFillColor( COLORREF color );
	void SetBorder( BOOL border );
	void SetBorderColor( COLORREF color );
	void SetBorderStyle( int style  );
	void SetBorderThickness( int thickness );

	void SetColumn( BOOL border );
	void SetColumnColor( COLORREF color );
	void SetColumnStyle( int style  );
	void SetColumnThickness( int thickness );

	void SetRow( BOOL border );
	void SetRowColor( COLORREF color );
	void SetRowStyle( int style  );
	void SetRowThickness( int thickness );

	void SetMeasurementUnits( int measurementunits );
	int GetMeasurementUnits();

    virtual ~CReportEntitySettings(){};

protected:

    CReportEntitySettings();
    static CReportEntitySettings m_reportEntitySettings;

private:

	LOGFONT		m_lf;
	int			m_justification;
	COLORREF	m_color;

	COLORREF	m_linecolor;
	int			m_linestyle;
	int			m_linethickness;

	BOOL		m_fill;
	COLORREF	m_fillcolor;

	BOOL		m_border;
	COLORREF	m_bordercolor;
	int			m_borderstyle;
	int			m_borderthickness;

	BOOL		m_column;
	COLORREF	m_columncolor;
	int			m_columnstyle;
	int			m_columnthickness;

	BOOL		m_row;
	COLORREF	m_rowcolor;
	int			m_rowstyle;
	int			m_rowthickness;

	int			m_measurementunits;

};

#endif //_REPORTENTITYSETTINGS_H_