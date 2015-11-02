
template <class TYPE> 
class CBlockUnitMemory
{
private:

	// 定義
	static const int m_iDefBlockUnitSize;	// ブロック単位のサイズ

public:

	// コンストラクタ／デストラクタ
	CBlockUnitMemory();
	~CBlockUnitMemory();
/*
	// ブロック単位決定
	void SetBlockUnitSize( const int iBlockSize ){ this->m_iBlockUnitSize = iBlockSize; }

	// メモリ確保
	bool AllocMemory( const int iMemorySize );

	// メモリ解放
	void ClearMemory();

	// メモリアクセス
	TYPE &GetAt( const int iIndex );
*/
private:

	// メンバ変数
	int m_iBlockUnitSize;					// 1ブロックのメモリサイズ
	int m_iBlockCount;						// 確保メモリのブロック数

	TYPE **m_pBuffer;						// バッファ
};
