/* ==========================================================================
	File :			ColumnContainer.cpp
	
	Class :			CColumnContainer

	Date :			07/18/04

	Purpose :		"CColumnContainer" is a container class for "CColumn". 

	Description :	The class keeps instances of "CColumn" in a "CObArray", 
					"m_arr". The class releases memory automatically.

	Usage :			Use to handle "CColumn"s in a grid object.

   ========================================================================*/

#include "stdafx.h"
#include "ColumnContainer.h"
#include "Column.h"
#include "DiagramEditor/Tokenizer.h"

////////////////////////////////////////////////////////////////////
// Public functions
//
CColumnContainer::CColumnContainer()
/* ============================================================
	Function :		CColumnContainer::CColumnContainer
	Description :	Constructor.
	Access :		Public
					
	Return :		void
	Parameters :	none

	Usage :			

   ============================================================*/
{
}

CColumnContainer::~CColumnContainer()
/* ============================================================
	Function :		CColumnContainer::~CColumnContainer
	Description :	Destructor.
	Access :		Public
					
	Return :		void
	Parameters :	none

	Usage :			

   ============================================================*/
{

	RemoveAll();

}

int CColumnContainer::GetSize() const
/* ============================================================
	Function :		CColumnContainer::GetSize
	Description :	Gets the number of columns in this 
					container.
	Access :		Public
					
	Return :		int		-	Number of columns in the array
	Parameters :	none

	Usage :			Call to get the number of columns in the 
					container.

   ============================================================*/
{

	int	result;
	result = m_arr.GetSize();
	return result;

}

CColumn* CColumnContainer::GetAt( int index ) const
/* ============================================================
	Function :		CColumnContainer::GetAt
	Description :	Gets the object at "index"
	Access :		Public
					
	Return :		CColumn*	-	Resulting column
	Parameters :	int index	-	Index to get object from

	Usage :			Call to get the column at "index"

   ============================================================*/
{

	CColumn*	result;
	result = static_cast< CColumn* >( m_arr.GetAt( index ) );
	return result;

}

void CColumnContainer::RemoveAt( int index )
/* ============================================================
	Function :		CColumnContainer::RemoveAt
	Description :	Removes the column at "index".
	Access :		Public
					
	Return :		void
	Parameters :	int index	-	Index to remove column from

	Usage :			Call to remove a column. Will also free 
					memory.

   ============================================================*/
{

	delete static_cast< CColumn* >( m_arr[ index ] );
	m_arr.RemoveAt( index );

}

void CColumnContainer::RemoveAll()
/* ============================================================
	Function :		CColumnContainer::RemoveAll()
	Description :	Remove all columns
	Access :		Public
					
	Return :		void
	Parameters :	none

	Usage :			Will also free memory.

   ============================================================*/
{

	while( GetSize() )
		RemoveAt( 0 );

}

void CColumnContainer::Add( CColumn * obj )
/* ============================================================
	Function :		CColumnContainer::Add
	Description :	Add a column to the end of the container.
	Access :		Public
					
	Return :		void
	Parameters :	CColumn * obj	-	Object to add

	Usage :			Call to add a new column. The container 
					takes ownership of the memory.

   ============================================================*/
{

	m_arr.Add( obj );

}

void CColumnContainer::Remove( CColumn* obj )
/* ============================================================
	Function :		CColumnContainer::Remove
	Description :	Removes "obj" from the container.
	Access :		Public

	Return :		void
	Parameters :	CColumn* obj	-	The object to remove.
					
	Usage :			Call to remove "obj" from the container. 
					The memory is released.

   ============================================================*/
{
	CColumn* test;
	int max = GetSize();
	for( int t = 0 ; t < max ; t++ )
	{
		test = GetAt( t );
		if( test == obj )
		{
			RemoveAt( t );
			return;
		}
	}
}

CColumnContainer& CColumnContainer::operator=( const CColumnContainer& arr )
/* ============================================================
	Function :		CColumnContainer::operator=
	Description :	Copies "arr" into this object.
	Access :		Public

	Return :		CColumnContainer&
	Parameters :	const CColumnContainer& arr	-	Array to copy from
					
	Usage :			Call to copy an array.

   ============================================================*/
{

	RemoveAll();

	for( int t = 0 ; t < arr.GetSize() ; t++ )
		Add( arr.GetAt( t )->Clone() );

	return *this; 


}

void CColumnContainer::Empty()
/* ============================================================
	Function :		CColumnContainer::Empty
	Description :	Removes all objects from the container 
					without deleting them.
	Access :		Public

	Return :		void
	Parameters :	none

	Usage :			Call to empty the array without deleting 
					the data, such as when data is shared 
					among several containers.

   ============================================================*/
{

	m_arr.RemoveAll();

}

void CColumnContainer::FromString( const CString& str )
/* ============================================================
	Function :		CColumnContainer::FromString
	Description :	Creates columns from "str".
	Access :		Public

	Return :		void
	Parameters :	const CString& str	-	String containing string 
											representations of columns
					
	Usage :			Call to load columns from file.

   ============================================================*/
{

	RemoveAll();

	CTokenizer tok( str, _T( "|" ) );

	int max = tok.GetSize();
	for( int t = 0 ; t < max ; t++ )
	{

		CColumn* obj = new CColumn;
		CString data;
		tok.GetAt( t, data );
		obj->FromString( data );
		Add( obj );

	}

}

CString CColumnContainer::GetString() const
/* ============================================================
	Function :		CColumnContainer::GetString
	Description :	Gets the columns of the container as a string.
	Access :		Public

	Return :		CString	-	Resulting string
	Parameters :	none

	Usage :			Call to save the columns to file.

   ============================================================*/
{

	CString result;
	
	int max = GetSize();
	for( int t = 0 ; t < max ; t++ )
	{
		CColumn* obj = GetAt( t );
		result += obj->GetString();
		if( t < max - 1 )
			result += _T( "|" );

	}

	return result;
}
