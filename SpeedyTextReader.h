/**
 * @note 
 * 大規模なテキストデータを読み込む場合に
 * 省メモリで早くReadすることを目指したクラスです。
 * 一度に全ファイル内容を確保するのではなく、1ラインずつ確保して処理を行うことで省メモリ化を行っています
 *
 * ※Tips
 * 現確保メモリ数を超える行の文字を取得したときに再確保が行われるため、予め大きな数を指定することで再確保の回数を減らすことが出来ます
 * (メモリ使用量と引き換えに読込み時のロスを減らします)
 *
 * ※使用方法
 * このクラスを継承したクラスでCallbackGetTextLineをオーバーライドし、
 * Read後に呼ばれるこの関数で取得した文字列に沿った処理を行ってください
 * SplitTextLineで分割の文字を指定してパラメータを取得した後型変換するなど、適宜使用してください
 *
 * ※使用例
 * CSpeedyTextReader *pReader = new CSpeedyTextReader( "***.txt" );
 * pReader->Read();
 * delete pReader;
 * pReader = NULL;
 * 
 */

#include <stdio.h>
#include <tchar.h>
#include <string>

// 速読省メモリテキストリーダー
class CSpeedyTextReader
{
private:

	// 定義値
	static const int iDefInitialReadLineBufSize;	// 一行読込みバッファの初期サイズ

public:

	// コンストラクタ／デストラクタ
	CSpeedyTextReader( 
		const char *strFilePath,
		const int iLineBufSie = iDefInitialReadLineBufSize
		);											// コンストラクタ
	virtual ~CSpeedyTextReader();					// デストラクタ

	// 一行読込みバッファ関連
	void ClearReadLineBuf();						// 一行読込みバッファのメモリクリア
	void SetReadLineBufSize( const int iBufSize );	// 一行読込みバッファサイズのセット

	// 読込み開始
	// ※ファイルの読込みを開始します
	bool Read();									// 読み込み開始

	// 一行文字列を読み込んだ時に呼ばれるコールバック関数
	// ※継承時この関数をオーバーライドして使用します
	virtual bool CallbackGetTextLine(				// 一行文字列の読込コールバック関数
		char *cTextLineBuf,
		const int iTextLineLength,
		const int iTextLineCount
		);

	// 分解判定文字
	inline void SetSplitChar( const char cSplitChar ){ this->m_cSplitChar = cSplitChar; }

	// パラメータ取得
	size_t SplitTextLine( char *cTextLine, const char cSplitChar, char **pcOutParameter );

	// パラメータ取得(確保してセットする安全関数)
	size_t SplitTextLine_Safe( char *cTextLine, const char cSplitChar, const int iSplitMaxCount, char ***pcOutParameter );

	// 行数カウントモードのセットフラグ
	inline void SetRowsCountMode( const bool bFlag ){ this->m_bRowsCountMode = bFlag; }

private:

	// メンバ変数
	char *m_pFilePath;								// ファイル名パス

	char *m_pReadLineBuf;							// 一行読込みバッファ
	int  m_iReadLineSize;							// 一行読込みサイズ

	int  m_iReadLineRows;							// 行数カウント

	char m_cSplitChar;								// 分解判定文字
	int  m_iSplitCount;								// 分解カウント

	bool m_bRowsCountMode;							// 行数カウントモードフラグ
};

