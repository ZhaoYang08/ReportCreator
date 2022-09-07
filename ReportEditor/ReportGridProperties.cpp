/* ==========================================================================
	Class :			CReportGridProperties

	Author :		Johan Rosengren, Abstrakt Mekanik AB

	Date :			2004-07-25

	Purpose :		"CReportBoxProperties" is a "CDiagramPropertyDlg"-derived 
					class for setting properties to a "CReportEntityGrid" 
					object

	Description :	This is a Wizard-created dialogbox class.

	Usage :			See "CDiagramPropertyDlg".

   ========================================================================*/

#include "stdafx.h"
#include "ReportGridProperties.h"
#include "ReportEntityGrid.h"
#include "ReportEntitySettings.h"
#include "ColumnDialog.h"
#include "UnitConversion.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

UINT UWM_GRIDMEASUREMENTS = ::RegisterWindowMessage( _T( "REPORT_EDITOR_MEASUREMENT" ) );

/////////////////////////////////////////////////////////////////////////////
// CReportGridProperties dialog


CReportGridProperties::CReportGridProperties(CWnd* pParent /*=NULL*/)
	: CDiagramPropertyDlg(CReportGridProperties::IDD, pParent)
/* ============================================================
	Function :		CReportGridProperties::CReportGridProperties
	Description :	Constructor
	Access :		Public

	Return :		void
	Parameters :	CWnd* pParent	-	Dialog parent
					
	Usage :			

   ============================================================*/
{
	//{{AFX_DATA_INIT(CReportGridProperties)
	m_border = FALSE;
	m_columns = FALSE;
	m_rows = FALSE;
	m_borderThickness = 0;
	m_columnThickness = 0;
	m_rowThickness = 0;
	m_measurements = -1;
	m_name = _T("");
	m_lpi = 6;
	//}}AFX_DATA_INIT

	m_borderColor = RGB( 0, 0, 0 );
	m_columnColor = RGB( 0, 0, 0 );
	m_rowColor = RGB( 0, 0, 0 );

	m_borderStyle = PS_SOLID;
	m_columnStyle = PS_SOLID;
	m_rowStyle = PS_SOLID;

}

void CReportGridProperties::DoDataExchange(CDataExchange* pDX)
/* ============================================================
	Function :		CReportGridProperties::DoDataExchange
	Description :	MFC data exchange handler.
	Access :		Protected

	Return :		void
	Parameters :	CDataExchange* pDX	-	Exchange object
					
	Usage :			Called from MFC.

   ============================================================*/
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CReportGridProperties)
	DDX_Control(pDX, IDC_LIST_COLUMNS, m_ctrlColumnList);
	DDX_Control(pDX, IDC_STATIC_ROW_COLOR, m_ctrlRowColor);
	DDX_Control(pDX, IDC_STATIC_COLUMN_COLOR, m_ctrlColumnColor);
	DDX_Control(pDX, IDC_STATIC_BORDER_COLOR, m_ctrlBorderColor);
	DDX_Control(pDX, IDC_COMBO_ROW_STYLE, m_ctrlRowStyle);
	DDX_Control(pDX, IDC_COMBO_COLUMN_STYLE, m_ctrlColumnStyle);
	DDX_Control(pDX, IDC_COMBO_BORDER_STYLE, m_ctrlBorderStyle);
	DDX_Check(pDX, IDC_CHECK_BORDER, m_border);
	DDX_Check(pDX, IDC_CHECK_COLUMNS, m_columns);
	DDX_Check(pDX, IDC_CHECK_ROWS, m_rows);
	DDX_Text(pDX, IDC_EDIT_BORDER_THICKNESS, m_borderThickness);
	DDX_Text(pDX, IDC_EDIT_COLUMN_THICKNESS, m_columnThickness);
	DDX_Text(pDX, IDC_EDIT_ROW_THICKNESS, m_rowThickness);
	DDX_Text(pDX, IDC_EDIT_LPI, m_lpi);
	DDX_CBIndex(pDX, IDC_COMBO_UNIT_MEASUREMENTS, m_measurements);
	DDX_Text(pDX, IDC_EDIT_NAME, m_name);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CReportGridProperties, CDialog)
	//{{AFX_MSG_MAP(CReportGridProperties)
	ON_BN_CLICKED(IDC_BUTTON_COLUMN_COLOR, OnButtonColumnColor)
	ON_BN_CLICKED(IDC_BUTTON_ROW_COLOR, OnButtonRowColor)
	ON_BN_CLICKED(IDC_BUTTON_BORDER_COLOR, OnButtonBorderColor)
	ON_BN_CLICKED(IDC_BUTTON_DELETE, OnButtonDelete)
	ON_BN_CLICKED(IDC_BUTTON_DOWN, OnButtonDown)
	ON_BN_CLICKED(IDC_BUTTON_UP, OnButtonUp)
	ON_BN_CLICKED(IDC_BUTTON_ADD, OnButtonAdd)
	ON_CBN_SELCHANGE(IDC_COMBO_UNIT_MEASUREMENTS, OnSelchangeComboMeasurements)
	//}}AFX_MSG_MAP

	ON_REGISTERED_MESSAGE(rwm_EXLISTBOX_DBLCLICK, OnListboxDblClick)
	ON_REGISTERED_MESSAGE(rwm_EXLISTBOX_DELETE, OnListboxDelete)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CReportGridProperties message handlers

void CReportGridProperties::OnOK() 
/* ============================================================
	Function :		CReportGridProperties::OnOK
	Description :	Handler for the dialog OK-button.
	Access :		Protected

	Return :		void
	Parameters :	none

	Usage :			Called from MFC.

   ============================================================*/
{
	int max = m_ctrlColumnList.GetCount();
	int zero = 0;
	for( int t = 0 ; t < max ; t++ )
	{
		CColumn* obj = reinterpret_cast< CColumn* >( m_ctrlColumnList.GetItemData( t ) );
		if( obj->GetWidth() == 0 )
			zero++;
	}

	if( zero > 1 )
	{
		AfxMessageBox( IDS_REPORT_ONLY_ONE_ZERO_COLUMN );
		return;
	}

	UpdateData();

	CReportEntityGrid* obj = static_cast< CReportEntityGrid* >( GetEntity() );

	obj->SetBorder( m_border );
	obj->SetBorderColor( m_borderColor );
	obj->SetBorderThickness( m_borderThickness );

	obj->SetColumnLines( m_columns );
	obj->SetColumnLineColor( m_columnColor );
	obj->SetColumnLineThickness( m_columnThickness );

	obj->SetRowLines( m_rows );
	obj->SetRowLineColor( m_rowColor );
	obj->SetRowLineThickness( m_rowThickness );

	int index = m_ctrlColumnStyle.GetCurSel();
	if( index != CB_ERR )
		obj->SetColumnLineStyle( m_ctrlColumnStyle.GetItemData( index ) );

	index = m_ctrlRowStyle.GetCurSel();
	if( index != CB_ERR )
		obj->SetRowLineStyle( m_ctrlRowStyle.GetItemData( index ) );

	index = m_ctrlBorderStyle.GetCurSel();
	if( index != CB_ERR )
		obj->SetBorderStyle( m_ctrlBorderStyle.GetItemData( index ) );

	m_columnarray.Empty();
	max = m_ctrlColumnList.GetCount();
	for( t = 0 ; t < max ; t++ )
	{
		CColumn* obj = reinterpret_cast< CColumn* >( m_ctrlColumnList.GetItemData( t ) );
		m_columnarray.Add( obj );
	}

	obj->m_columns = m_columnarray;

	obj->SetName( m_name );
	obj->SetLPI( m_lpi );

	CReportEntitySettings::GetRESInstance()->SetBorder( m_border );
	CReportEntitySettings::GetRESInstance()->SetBorderColor( m_borderColor );
	CReportEntitySettings::GetRESInstance()->SetBorderThickness( m_borderThickness );
	CReportEntitySettings::GetRESInstance()->SetBorderStyle( m_borderStyle );

	CReportEntitySettings::GetRESInstance()->SetColumn( m_columns );
	CReportEntitySettings::GetRESInstance()->SetColumnColor( m_columnColor );
	CReportEntitySettings::GetRESInstance()->SetColumnThickness( m_columnThickness );
	CReportEntitySettings::GetRESInstance()->SetColumnStyle( m_columnStyle );

	CReportEntitySettings::GetRESInstance()->SetRow( m_rows );
	CReportEntitySettings::GetRESInstance()->SetRowColor( m_rowColor );
	CReportEntitySettings::GetRESInstance()->SetRowThickness( m_rowThickness );
	CReportEntitySettings::GetRESInstance()->SetRowStyle( m_rowStyle );

	GetRedrawWnd()->GetParent()->SendMessage( UWM_GRIDMEASUREMENTS, m_measurements );

	ShowWindow( SW_HIDE );
	Redraw();

}

void CReportGridProperties::OnCancel() 
/* ============================================================
	Function :		CReportGridProperties::OnCancel
	Description :	Handler for the dialog Cancel-button.
	Access :		Protected

	Return :		void
	Parameters :	none

	Usage :			Called from MFC.

   ============================================================*/
{

	ShowWindow( SW_HIDE );

}

void CReportGridProperties::OnButtonColumnColor() 
/* ============================================================
	Function :		CReportGridProperties::OnButtonColumnColor
	Description :	Handler for the dialog button ColumnColor
	Access :		Protected

	Return :		void
	Parameters :	none

	Usage :			Called from MFC.

   ============================================================*/
{

	CColorDialog	dlg( m_columnColor );
	if( dlg.DoModal() == IDOK )
	{

		m_columns = TRUE;
		m_columnColor = dlg.GetColor();
		m_ctrlColumnColor.SetColor( m_columnColor );
		UpdateData( TRUE );

	}
	
}

void CReportGridProperties::OnButtonRowColor() 
/* ============================================================
	Function :		CReportGridProperties::OnButtonRowColor
	Description :	Handler for the dialog button RowColor
	Access :		Protected

	Return :		void
	Parameters :	none

	Usage :			Called from MFC.

   ============================================================*/
{

	CColorDialog	dlg( m_rowColor );
	if( dlg.DoModal() == IDOK )
	{

		m_rows = TRUE;
		m_rowColor = dlg.GetColor();
		m_ctrlRowColor.SetColor( m_rowColor );
		UpdateData( TRUE );

	}

}

void CReportGridProperties::OnButtonBorderColor() 
/* ============================================================
	Function :		CReportGridProperties::OnButtonBorderColor
	Description :	Handler for the dialog button BorderColor
	Access :		Protected

	Return :		void
	Parameters :	none

	Usage :			Called from MFC.

   ============================================================*/
{

	CColorDialog	dlg( m_borderColor );
	if( dlg.DoModal() == IDOK )
	{

		m_border = TRUE;
		m_borderColor = dlg.GetColor();
		m_ctrlBorderColor.SetColor( m_borderColor );
		UpdateData( TRUE );

	}
	
}

void CReportGridProperties::OnButtonDelete() 
/* ============================================================
	Function :		CReportGridProperties::OnButtonDelete
	Description :	Handler for the dialog button Delete
	Access :		Protected

	Return :		void
	Parameters :	none

	Usage :			Called from MFC.

   ============================================================*/
{

	int index = m_ctrlColumnList.GetCurSel();
	if( index != LB_ERR )
	{

		CColumn* obj = reinterpret_cast< CColumn* >( m_ctrlColumnList.GetItemData( index ) );
		m_columnarray.Remove( obj );
		m_ctrlColumnList.DeleteString( index );
		m_ctrlColumnList.SetCurSel( index );
		m_ctrlColumnList.SetFocus();

	}
	
}

void CReportGridProperties::OnButtonDown() 
/* ============================================================
	Function :		CReportGridProperties::OnButtonDown
	Description :	Handler for the dialog button Down
	Access :		Protected

	Return :		void
	Parameters :	none

	Usage :			Called from MFC.

   ============================================================*/
{

	int index = m_ctrlColumnList.GetCurSel();
	if( index != LB_ERR && index < m_ctrlColumnList.GetCount() - 1)
	{

		CColumn* obj1 = reinterpret_cast< CColumn* >( m_ctrlColumnList.GetItemData( index ) );
		CColumn* obj2 = reinterpret_cast< CColumn* >( m_ctrlColumnList.GetItemData( index + 1 ) );
		CString text1;
		CString text2;
		m_ctrlColumnList.GetText( index, text1 );
		m_ctrlColumnList.GetText( index + 1, text2 );

		m_ctrlColumnList.DeleteString( index + 1 );
		m_ctrlColumnList.DeleteString( index );

		m_ctrlColumnList.InsertString( index, text2 );
		m_ctrlColumnList.SetItemData( index, ( DWORD ) obj2 );

		m_ctrlColumnList.InsertString( index + 1, text1 );
		m_ctrlColumnList.SetItemData( index + 1, ( DWORD ) obj1 );

		m_ctrlColumnList.SetCurSel( index + 1 );
		m_ctrlColumnList.SetFocus();

	}
	
}

void CReportGridProperties::OnButtonUp() 
/* ============================================================
	Function :		CReportGridProperties::OnButtonUp
	Description :	Handler for the dialog button Up
	Access :		Protected

	Return :		void
	Parameters :	none

	Usage :			Called from MFC.

   ============================================================*/
{

	int index = m_ctrlColumnList.GetCurSel();
	if( index != LB_ERR && index > 0 )
	{
		CColumn* obj1 = reinterpret_cast< CColumn* >( m_ctrlColumnList.GetItemData( index ) );
		CColumn* obj2 = reinterpret_cast< CColumn* >( m_ctrlColumnList.GetItemData( index - 1 ) );
		CString text1;
		CString text2;
		m_ctrlColumnList.GetText( index, text1 );
		m_ctrlColumnList.GetText( index - 1, text2 );

		m_ctrlColumnList.DeleteString( index );
		m_ctrlColumnList.DeleteString( index - 1 );

		m_ctrlColumnList.InsertString( index - 1, text1 );
		m_ctrlColumnList.SetItemData( index - 1, ( DWORD ) obj1 );

		m_ctrlColumnList.InsertString( index, text2 );
		m_ctrlColumnList.SetItemData( index, ( DWORD ) obj2 );

		m_ctrlColumnList.SetCurSel( index - 1 );
		m_ctrlColumnList.SetFocus();

	}
	
}

void CReportGridProperties::OnButtonAdd() 
/* ============================================================
	Function :		CReportGridProperties::OnButtonAdd
	Description :	Handler for the dialog button Add
	Access :		Protected

	Return :		void
	Parameters :	none

	Usage :			Called from MFC.

   ============================================================*/
{

	UpdateData();
	CColumn* obj = new CColumn;
	CColumnDialog	dlg;
	dlg.m_measurement = m_measurements;
	dlg.m_column = obj;
	if( dlg.DoModal() == IDOK )
	{

		CString text;
		text = GetColumnText( obj );
		int index = m_ctrlColumnList.AddString( text );
		m_ctrlColumnList.SetItemData( index, ( DWORD ) obj );
		m_columnarray.Add( obj );
		m_ctrlColumnList.SetCurSel( index );
		m_ctrlColumnList.SetFocus();

	}
	else
		delete obj;
	
}

BOOL CReportGridProperties::OnInitDialog() 
/* ============================================================
	Function :		CReportGridProperties::OnInitDialog
	Description :	Handler for the "WM_INITDIALOG" messag
	Access :		Protected

	Return :		BOOL	-	Always "TRUE"
	Parameters :	none

	Usage :			Called from MFC

   ============================================================*/
{

	CDialog::OnInitDialog();

	m_measurements = CReportEntitySettings::GetRESInstance()->GetMeasurementUnits();

	m_ctrlBorderColor.SetColor( m_borderColor );
	m_ctrlColumnColor.SetColor( m_columnColor );
	m_ctrlRowColor.SetColor( m_rowColor );

	if( m_ctrlBorderStyle.GetCount() == 0 )
	{
		CString text;

		text.LoadString( IDS_REPORT_LINE_STYLE_1 );
		m_ctrlBorderStyle.SetItemData( m_ctrlBorderStyle.AddString( text ), PS_SOLID );

		text.LoadString( IDS_REPORT_LINE_STYLE_2 );
		m_ctrlBorderStyle.SetItemData( m_ctrlBorderStyle.AddString( text ), PS_DASH );

		text.LoadString( IDS_REPORT_LINE_STYLE_3 );
		m_ctrlBorderStyle.SetItemData( m_ctrlBorderStyle.AddString( text ), PS_DOT );

	}

	if( m_ctrlColumnStyle.GetCount() == 0 )
	{
		CString text;

		text.LoadString( IDS_REPORT_LINE_STYLE_1 );
		m_ctrlColumnStyle.SetItemData( m_ctrlColumnStyle.AddString( text ), PS_SOLID );

		text.LoadString( IDS_REPORT_LINE_STYLE_2 );
		m_ctrlColumnStyle.SetItemData( m_ctrlColumnStyle.AddString( text ), PS_DASH );

		text.LoadString( IDS_REPORT_LINE_STYLE_3 );
		m_ctrlColumnStyle.SetItemData( m_ctrlColumnStyle.AddString( text ), PS_DOT );

	}

	if( m_ctrlRowStyle.GetCount() == 0 )
	{
		CString text;

		text.LoadString( IDS_REPORT_LINE_STYLE_1 );
		m_ctrlRowStyle.SetItemData( m_ctrlRowStyle.AddString( text ), PS_SOLID );

		text.LoadString( IDS_REPORT_LINE_STYLE_2 );
		m_ctrlRowStyle.SetItemData( m_ctrlRowStyle.AddString( text ), PS_DASH );

		text.LoadString( IDS_REPORT_LINE_STYLE_3 );
		m_ctrlRowStyle.SetItemData( m_ctrlRowStyle.AddString( text ), PS_DOT );

	}

	int max = m_ctrlBorderStyle.GetCount();
	for( int t = 0 ; t < max ; t++ )
		if( m_ctrlBorderStyle.GetItemData( t ) == static_cast< DWORD >( m_borderStyle ) )
			m_ctrlBorderStyle.SetCurSel( t );

	max = m_ctrlColumnStyle.GetCount();
	for( t = 0 ; t < max ; t++ )
		if( m_ctrlColumnStyle.GetItemData( t ) == static_cast< DWORD >( m_columnStyle ) )
			m_ctrlColumnStyle.SetCurSel( t );

	max = m_ctrlRowStyle.GetCount();
	for( t = 0 ; t < max ; t++ )
		if( m_ctrlRowStyle.GetItemData( t ) == static_cast< DWORD >( m_rowStyle ) )
			m_ctrlRowStyle.SetCurSel( t );

	m_ctrlColumnList.ResetContent();
	max = m_columnarray.GetSize();
	int index;
	for( t = 0 ; t < max ; t++ )
	{

		CString text;
		text = GetColumnText( m_columnarray.GetAt( t ) );
		index = m_ctrlColumnList.AddString( text );
		m_ctrlColumnList.SetItemData( index, ( DWORD ) m_columnarray.GetAt( t ) );

	}

	return TRUE; 

}

void CReportGridProperties::SetValues()
/* ============================================================
	Function :		CReportGridProperties::SetValues
	Description :	Sets the values of the property dialog
	Access :		Public

	Return :		void
	Parameters :	none

	Usage :			Call to set the property dialog values.

   ============================================================*/
{

	CReportEntityGrid* obj = static_cast< CReportEntityGrid* >( GetEntity() );

	m_borderColor = obj->GetBorderColor();
	if( m_ctrlBorderColor.m_hWnd )
		m_ctrlBorderColor.SetColor( m_borderColor );

	m_columnColor = obj->GetColumnLineColor();
	if( m_ctrlColumnColor.m_hWnd )
		m_ctrlColumnColor.SetColor( m_columnColor );

	m_rowColor = obj->GetRowLineColor();
	if( m_ctrlRowColor.m_hWnd )
		m_ctrlRowColor.SetColor( m_rowColor );

	m_border = obj->GetBorder();
	m_columns = obj->GetColumnLines();
	m_rows = obj->GetRowLines();

	m_borderStyle = obj->GetBorderStyle();
	m_columnStyle = obj->GetColumnLineStyle();
	m_rowStyle = obj->GetRowLineStyle();

	m_name = obj->GetName();
	m_lpi = obj->GetLPI();

	if( m_ctrlBorderStyle.m_hWnd )
	{
		int max = m_ctrlBorderStyle.GetCount();
		for( int t = 0 ; t < max ; t++ )
			if( m_ctrlBorderStyle.GetItemData( t ) == static_cast< DWORD >( m_borderStyle ) )
				m_ctrlBorderStyle.SetCurSel( t );
	}

	if( m_ctrlColumnStyle.m_hWnd )
	{
		int max = m_ctrlColumnStyle.GetCount();
		for( int t = 0 ; t < max ; t++ )
			if( m_ctrlColumnStyle.GetItemData( t ) == static_cast< DWORD >( m_columnStyle ) )
				m_ctrlColumnStyle.SetCurSel( t );
	}

	if( m_ctrlRowStyle.m_hWnd )
	{
		int max = m_ctrlRowStyle.GetCount();
		for( int t = 0 ; t < max ; t++ )
			if( m_ctrlRowStyle.GetItemData( t ) == static_cast< DWORD >( m_rowStyle ) )
				m_ctrlRowStyle.SetCurSel( t );
	}

	m_columnarray = obj->m_columns;

	if( m_ctrlColumnList.m_hWnd )
	{ 
		RefillColumnList();
	}

	m_measurements = CReportEntitySettings::GetRESInstance()->GetMeasurementUnits();
	if( m_ctrlColumnList.m_hWnd )
		UpdateData( FALSE );

}

LRESULT CReportGridProperties::OnListboxDblClick( WPARAM, LPARAM )
/* ============================================================
	Function :		CReportGridProperties::OnListboxDblClick
	Description :	Mapped to the registered message 
					"rwm_EXLISTBOX_DBLCLICK" sent from the 
					"CExListBox" when the user double clicks 
					an entry.
	Access :		Protected

	Return :		LRESULT	-	Not used
	Parameters :	WPARAM	-	Not used
					LPARAM	-	Not used
					
	Usage :			Called from MFC.

   ============================================================*/
{

	UpdateData();
	int index = m_ctrlColumnList.GetCurSel();
	if( index != LB_ERR )
	{
		CColumn* obj = reinterpret_cast< CColumn* >( m_ctrlColumnList.GetItemData( index ) );
		CColumnDialog	dlg;
		dlg.m_measurement = m_measurements;
		dlg.m_column = obj;
		if( dlg.DoModal() == IDOK )
			RefillColumnList();

		m_ctrlColumnList.SetCurSel( index );
		m_ctrlColumnList.SetFocus();
	}

	return 0;

}

LRESULT CReportGridProperties::OnListboxDelete( WPARAM, LPARAM )
/* ============================================================
	Function :		CReportGridProperties::OnListboxDelete
	Description :	Handler for the registered message 
					"rwm_EXLISTBOX_DELETE".
	Access :		Protected

	Return :		LRESULT	-	Not interested
	Parameters :	WPARAM	-	Not interested
					LPARAM	-	Not interested
					
	Usage :			Called from MFC.

   ============================================================*/
{

	OnButtonDelete();
	return 0;

}

CString CReportGridProperties::GetColumnText( CColumn* obj )
/* ============================================================
	Function :		CReportGridProperties::GetColumnText
	Description :	Gets the listbox text for "obj"
	Access :		Private

	Return :		CString			-	Resulting string
	Parameters :	CColumn* obj	-	Column to get text for
					
	Usage :			Call to get the text to put int the listbox 
					for the column object "obj"

   ============================================================*/
{

	CString text;
	CString suffix;

	text = obj->GetName();

	switch( m_measurements )
	{
		case 0:
			suffix.Format( _T( "\t%i" ), obj->GetWidth() );
		break;
		case 1:
			suffix.Format( _T( "\t%.02f" ), CUnitConversion::PixelsToInches( obj->GetWidth() ) );
		break;
		case 2:
			suffix.Format( _T( "\t%.02f" ), CUnitConversion::PixelsToCentimeters( obj->GetWidth() ) );
		break;
	}

	return text + suffix;

}

void CReportGridProperties::OnSelchangeComboMeasurements() 
/* ============================================================
	Function :		CReportGridProperties::OnSelchangeComboMeasurements
	Description :	Handler for selection changes in the 
					measurement combo.
	Access :		Protected

	Return :		void
	Parameters :	none

	Usage :			Called from MFC. Updates the values on 
					screen using the selected measurement.

   ============================================================*/
{

	UpdateData();
	RefillColumnList();

}

void CReportGridProperties::RefillColumnList()
/* ============================================================
	Function :		CReportGridProperties::RefillColumnList
	Description :	Resets the contents of the column listbox.
	Access :		Private

	Return :		void
	Parameters :	none

	Usage :			Call to refill the column listbox from the 
					internal column array.

   ============================================================*/
{

	m_ctrlColumnList.ResetContent();
	int max = m_columnarray.GetSize();
	int index;
	for( int t = 0 ; t < max ; t++ )
	{

		CString text;
		text = GetColumnText( m_columnarray.GetAt( t ) );
		index = m_ctrlColumnList.AddString( text );
		m_ctrlColumnList.SetItemData( index, ( DWORD ) m_columnarray.GetAt( t ) );

	}
}

