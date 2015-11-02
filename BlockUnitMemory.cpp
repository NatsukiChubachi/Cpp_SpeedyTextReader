
#include "BlockUnitMemory.h"

// ��`
template<class TYPE>
const int CBlockUnitMemory<TYPE>::m_iDefBlockUnitSize = 100000;	// �u���b�N�P�ʂ̃T�C�Y

// �R���X�g���N�^
template<class TYPE>
CBlockUnitMemory<TYPE>::CBlockUnitMemory()
	: m_iBlockUnitSize( m_iDefBlockUnitSize )
	, m_iBlockCount( 0 )
	, m_pBuffer( NULL )
{
}

// �f�X�g���N�^
template<class TYPE>
CBlockUnitMemory<TYPE>::~CBlockUnitMemory()
{
	// ���������
	this->ClearMemory();
}
/*
// �������m��
template<class TYPE>
bool CBlockUnitMemory<TYPE>::AllocMemory( const int iMemorySize )
{
	bool bResult = true;

	// ��U�������
	this->ClearMemory();

	// �m�ۃu���b�N���̌���
	this->m_iBlockCount = ( iMemorySize / this->m_iBlockUnitSize ) + 1;

	// �u���b�N���̊m�ۊJ�n
	this->m_pBuffer = new TYPE*[ this->m_iBlockCount ];

	// �u���b�N�P�ʂ̊m��
	int iIndex = 0;
	for ( int i = this->m_iBlockCount - 1; i > 0; --i )
	{
		iIndex = (this->m_iBlockCount - 1) - i;
		this->m_pBuffer[ iIndex ] = new TYPE[ this->m_iBlockSize ];
	}

	return bResult;
}

// ���������
template<class TYPE>
void CBlockUnitMemory<TYPE>::ClearMemory()
{
	if ( this->m_pBuffer )
	{
		for ( int i = this->m_iBlockCount - 1; i > 0; --i )
		{
			delete[] this->m_pBuffer[ index ];
		}

		delete[] this->m_pBuffer;
		this->m_pBuffer = NULL;
	}
}

// �������A�N�Z�X
template<class TYPE>
TYPE &CBlockUnitMemory<TYPE>::GetAt( const int iIndex )
{
	const int iAccessBlock = iIndex / this->m_iBlockUnitSize;
	const int iAccessIndex = iIndex % this->m_iBlockUnitSize;

	if ( this->m_pBuffer )
	{
		return this->m_pBuffer[ iAccessBlock ][ iAccessIndex ];
	}

	return NULL;
}
*/