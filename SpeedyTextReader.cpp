

#include "SpeedyTextReader.h"

using namespace std;

/**
 * 定義関連
 */
// 一行読込みバッファの初期サイズ
const int CSpeedyTextReader::iDefInitialReadLineBufSize = 1000;

/**
 * コンストラクタ
 */
CSpeedyTextReader::CSpeedyTextReader( const char *strFilePath, const int iLineBufSize )
	: m_pFilePath( NULL )
	, m_pReadLineBuf( NULL )
	, m_iReadLineSize( 0 )
	, m_iReadLineRows( 0 )
	, m_cSplitChar( ',' )
	, m_iSplitCount( 0 )
	, m_bRowsCountMode( false )
{
	// ファイルパス名の確保
	size_t iFilePathSize = strlen( strFilePath );	

	this->m_pFilePath = new char[ iFilePathSize + 1 ];
	strcpy_s( this->m_pFilePath, iFilePathSize + 1, strFilePath );

	// 一行読み込みバッファのメモリ確保
	this->SetReadLineBufSize( iLineBufSize );
}

/**
 * デストラクタ
 */
CSpeedyTextReader::~CSpeedyTextReader()
{
	// ファイル名確保部分のメモリ解放
	if ( this->m_pFilePath != NULL )
	{
		delete[] this->m_pFilePath;
		this->m_pFilePath = NULL;
	}

	// 一行読み込みバッファ部分のメモリ解放
	this->ClearReadLineBuf();
}

/**
 * 一行読込みバッファのメモリクリア
 */
void CSpeedyTextReader::ClearReadLineBuf()
{
	// 一行読み込みバッファ部分のメモリ解放
	if ( this->m_pReadLineBuf != NULL )
	{
		delete[] this->m_pReadLineBuf;
		this->m_pReadLineBuf = NULL;
	}
}

/**
 * 一行読込みバッファサイズのセット
 */
void CSpeedyTextReader::SetReadLineBufSize( const int iBufSize )
{
	// 一行読み込みバッファ部分のメモリ解放
	this->ClearReadLineBuf();

	// 一行読込みバッファサイズのセット
	this->m_iReadLineSize = iBufSize;

	// 一行読み込みバッファのメモリ確保
	this->m_pReadLineBuf = new char[ iBufSize ];
	memset( this->m_pReadLineBuf, NULL, iBufSize );
}

/**
 * 読込み開始メソッド
 */
bool CSpeedyTextReader::Read()
{
	bool bResult = true;

	// 行番号のリセット
	this->m_iReadLineRows = 0;

	// ファイルオープン
	register FILE *fp;

	if ( fopen_s( &fp, this->m_pFilePath, "r" ) != NULL )
	{
		bResult = false;
		return bResult;
	}

	// ファイル読込
	register int iCharIndex = 0;

	register char cTmp;
	while( ( cTmp = fgetc( fp ) ) != EOF )
	{
		// 対象外文字のcontinue処理
		if ( cTmp == '\r' ) continue;

		// 分割候補文字で同一の文字でつながっている場合は格納しない
		if ( iCharIndex > 1 && ( cTmp == ' ' || cTmp == ',' ) )
		{
			if ( cTmp == this->m_pReadLineBuf[ iCharIndex-1 ] )
			{
				continue;
			}
		}

		// 改行文字列時の処理
		if ( iCharIndex > 1 && ( cTmp == '\n' || cTmp == '\r' ) )
		{
			// 行番号のインクリメント
			++this->m_iReadLineRows;

			// 一文字以上格納している場合
			if ( iCharIndex > 0 )
			{
				// コールバック関数の呼び出し
				this->CallbackGetTextLine( this->m_pReadLineBuf, iCharIndex, this->m_iReadLineRows );

				// 一行文字列バッファのクリア
				memset( this->m_pReadLineBuf, NULL, this->m_iReadLineSize );
				iCharIndex = 0;

				// 以降の処理を行わず繰り返し
				continue;
			}
		}

		// 行数カウントモードの場合は文字を格納せずに読み続ける
		if ( this->m_bRowsCountMode )
		{
			continue;
		}

		// 文字列の格納
		this->m_pReadLineBuf[ iCharIndex ] = cTmp;

		// インデックスのインクリメント
		++iCharIndex;

		// 一行分の確保バッファを上回るインデックスに突入する場合
		if ( iCharIndex >= ( this->m_iReadLineSize - 1 ) )
		{
			// 文字列の一時確保
			const int iOldLineSize = this->m_iReadLineSize;
			char *cTmpLineStr = new char[ this->m_iReadLineSize ];
			memset( cTmpLineStr, NULL, this->m_iReadLineSize );
			strcpy_s( this->m_pReadLineBuf, this->m_iReadLineSize, cTmpLineStr );

			// 一行バッファ確保の初期化
			// ※現在の2倍のバッファを確保する
			this->ClearReadLineBuf();
			this->SetReadLineBufSize( this->m_iReadLineSize * 2 );

			// 確保した文字列のコピー
			strcpy_s( cTmpLineStr, iOldLineSize, this->m_pReadLineBuf );

			// メモリの解放
			delete[] cTmpLineStr;
			cTmpLineStr;
		}
	}

	// ファイルクローズ
	fclose( fp );

	return bResult;
}

/**
 * 一行文字列の読込コールバック関数
 */
bool CSpeedyTextReader::CallbackGetTextLine(
	char *cTextLineBuf,
	const int iTextLineLength,
	const int iTextLineCount
	)
{
	register bool bResult = true;

#if 0
	printf( cTextLineBuf );
	printf("\n");
#endif

#if 0
	// パラメータ分割処理
	char **pcParam = new char*[ 10 ];
	this->SplitTextLine( cTextLineBuf, ' ', pcParam );

	// テスト記述
	printf( "%s\n", pcParam[0] );
	printf( "%s\n", pcParam[1] );

	// メモリの解放
	delete pcParam;
	pcParam = NULL;
#endif

#if 0
	// パラメータ分割処理
	char **pcParam = NULL;
	register size_t iSplitCount = this->SplitTextLine_Safe( cTextLineBuf, ' ', iTextLineLength, &pcParam );

	// テスト記述
	if ( iSplitCount >= 2 )
	{
		printf( "%s\n", pcParam[0] );
		printf( "%s\n", pcParam[1] );
	}

	// メモリの解放
	delete pcParam;
	pcParam = NULL;
#endif

	return bResult;
}

// パラメータ取得
size_t CSpeedyTextReader::SplitTextLine( 
	char *cTextLine, 
	const char cSplitChar,
	char **pcOutParameter
	)
{
	register size_t iResult = -1;

	// 分割点カウントの取得
	register int iSplitIndex = 0;

	register size_t iIndex = 0;
	const size_t iLength = strlen( cTextLine );

	// 文字数が0の場合
	if ( iLength <= 0 ) 
	{
		return iSplitIndex;
	}

	// 後ろからforでまわす(条件式=0を省略できるため)
//	while( iIndex < iLength )
	register size_t iLoopIndex = 0;
	for ( iLoopIndex = ( iLength - 1 ); iLoopIndex > 0; --iLoopIndex )
	{
		iIndex = ( iLength - 1 ) - iLoopIndex;

		// 分割点の取得
		if ( iIndex == 0 )
		{
			// パラメータ箇所のポインタセット
			pcOutParameter[ iSplitIndex ] = &( cTextLine[ iIndex ] );
			++iSplitIndex;
			++iIndex;

			// 処理を再開する
			continue;
		}
		else if ( cTextLine[ iIndex ] == cSplitChar ) 
		{
			// 分割文字を終端文字に置き換える
			cTextLine[ iIndex ] = '\0';

			// パラメータ箇所のポインタセット
			++iIndex;
			pcOutParameter[ iSplitIndex ] = &( cTextLine[ iIndex ] );
			++iSplitIndex;

			// 処理を再開する
			continue;
		}

		// 分割点以外
		// インデックスのインクリメント
		++iIndex;
	}

	// 分割点総数を返す
	iResult = iIndex;

	return iResult;
}

/**
 * パラメータ取得(確保してセットする安全関数)
 * パラメータ確保配列を取得時に文字列数確保(最大分割数)してから行います。
 * ※
 * 安全な分低速です。
 */
size_t CSpeedyTextReader::SplitTextLine_Safe( 
	char *cTextLine, 
	const char cSplitChar,
	const int iSplitMaxCount,
	char ***pcOutParameter
	)
{
	// メモリ解放
	if ( *pcOutParameter )
	{
		delete *pcOutParameter;
		*pcOutParameter = NULL;
	}

	// メモリ確保
	*pcOutParameter = new char*[ iSplitMaxCount ];

	// パラメータ取得と総数を返す
	return this->SplitTextLine( cTextLine, cSplitChar, *pcOutParameter );
}

