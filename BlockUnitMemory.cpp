
#include "BlockUnitMemory.h"

// 定義
template<class TYPE>
const int CBlockUnitMemory<TYPE>::m_iDefBlockUnitSize = 100000;	// ブロック単位のサイズ

// コンストラクタ
template<class TYPE>
CBlockUnitMemory<TYPE>::CBlockUnitMemory()
	: m_iBlockUnitSize( m_iDefBlockUnitSize )
	, m_iBlockCount( 0 )
	, m_pBuffer( NULL )
{
}

// デストラクタ
template<class TYPE>
CBlockUnitMemory<TYPE>::~CBlockUnitMemory()
{
	// メモリ解放
	this->ClearMemory();
}
/*
// メモリ確保
template<class TYPE>
bool CBlockUnitMemory<TYPE>::AllocMemory( const int iMemorySize )
{
	bool bResult = true;

	// 一旦解放する
	this->ClearMemory();

	// 確保ブロック数の決定
	this->m_iBlockCount = ( iMemorySize / this->m_iBlockUnitSize ) + 1;

	// ブロック数の確保開始
	this->m_pBuffer = new TYPE*[ this->m_iBlockCount ];

	// ブロック単位の確保
	int iIndex = 0;
	for ( int i = this->m_iBlockCount - 1; i > 0; --i )
	{
		iIndex = (this->m_iBlockCount - 1) - i;
		this->m_pBuffer[ iIndex ] = new TYPE[ this->m_iBlockSize ];
	}

	return bResult;
}

// メモリ解放
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

// メモリアクセス
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