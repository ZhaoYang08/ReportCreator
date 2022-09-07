#ifndef _CCOLUMNCONTAINER_H_D29D7BB0_4C92_4A6A_966E49ABCDED
#define _CCOLUMNCONTAINER_H_D29D7BB0_4C92_4A6A_966E49ABCDED

///////////////////////////////////////////////////////////
// File :		ColumnContainer.h
// Created :	07/18/04
//

#include "Column.h"

class CColumnContainer
{
public:
// Construction/destruction
	CColumnContainer();
	virtual ~CColumnContainer();

	void FromString( const CString& str );
	CString GetString() const;

// Operations
	int GetSize() const;
	CColumn* GetAt( int index ) const;
	void RemoveAt( int index );
	void RemoveAll();
	void Add( CColumn * obj );
	void Remove( CColumn* obj );
	void Empty();

	CColumnContainer& operator =( const CColumnContainer& );

// Attributes

private:
	CObArray	m_arr;


};
#endif //_CCOLUMNCONTAINER_H_D29D7BB0_4C92_4A6A_966E49ABCDED
