

#include "SpeedyTextReader.h"

using namespace std;

/**
 * ��`�֘A
 */
// ��s�Ǎ��݃o�b�t�@�̏����T�C�Y
const int CSpeedyTextReader::iDefInitialReadLineBufSize = 1000;

/**
 * �R���X�g���N�^
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
	// �t�@�C���p�X���̊m��
	size_t iFilePathSize = strlen( strFilePath );	

	this->m_pFilePath = new char[ iFilePathSize + 1 ];
	strcpy_s( this->m_pFilePath, iFilePathSize + 1, strFilePath );

	// ��s�ǂݍ��݃o�b�t�@�̃������m��
	this->SetReadLineBufSize( iLineBufSize );
}

/**
 * �f�X�g���N�^
 */
CSpeedyTextReader::~CSpeedyTextReader()
{
	// �t�@�C�����m�ە����̃��������
	if ( this->m_pFilePath != NULL )
	{
		delete[] this->m_pFilePath;
		this->m_pFilePath = NULL;
	}

	// ��s�ǂݍ��݃o�b�t�@�����̃��������
	this->ClearReadLineBuf();
}

/**
 * ��s�Ǎ��݃o�b�t�@�̃������N���A
 */
void CSpeedyTextReader::ClearReadLineBuf()
{
	// ��s�ǂݍ��݃o�b�t�@�����̃��������
	if ( this->m_pReadLineBuf != NULL )
	{
		delete[] this->m_pReadLineBuf;
		this->m_pReadLineBuf = NULL;
	}
}

/**
 * ��s�Ǎ��݃o�b�t�@�T�C�Y�̃Z�b�g
 */
void CSpeedyTextReader::SetReadLineBufSize( const int iBufSize )
{
	// ��s�ǂݍ��݃o�b�t�@�����̃��������
	this->ClearReadLineBuf();

	// ��s�Ǎ��݃o�b�t�@�T�C�Y�̃Z�b�g
	this->m_iReadLineSize = iBufSize;

	// ��s�ǂݍ��݃o�b�t�@�̃������m��
	this->m_pReadLineBuf = new char[ iBufSize ];
	memset( this->m_pReadLineBuf, NULL, iBufSize );
}

/**
 * �Ǎ��݊J�n���\�b�h
 */
bool CSpeedyTextReader::Read()
{
	bool bResult = true;

	// �s�ԍ��̃��Z�b�g
	this->m_iReadLineRows = 0;

	// �t�@�C���I�[�v��
	register FILE *fp;

	if ( fopen_s( &fp, this->m_pFilePath, "r" ) != NULL )
	{
		bResult = false;
		return bResult;
	}

	// �t�@�C���Ǎ�
	register int iCharIndex = 0;

	register char cTmp;
	while( ( cTmp = fgetc( fp ) ) != EOF )
	{
		// �ΏۊO������continue����
		if ( cTmp == '\r' ) continue;

		// ������╶���œ���̕����łȂ����Ă���ꍇ�͊i�[���Ȃ�
		if ( iCharIndex > 1 && ( cTmp == ' ' || cTmp == ',' ) )
		{
			if ( cTmp == this->m_pReadLineBuf[ iCharIndex-1 ] )
			{
				continue;
			}
		}

		// ���s�����񎞂̏���
		if ( iCharIndex > 1 && ( cTmp == '\n' || cTmp == '\r' ) )
		{
			// �s�ԍ��̃C���N�������g
			++this->m_iReadLineRows;

			// �ꕶ���ȏ�i�[���Ă���ꍇ
			if ( iCharIndex > 0 )
			{
				// �R�[���o�b�N�֐��̌Ăяo��
				this->CallbackGetTextLine( this->m_pReadLineBuf, iCharIndex, this->m_iReadLineRows );

				// ��s������o�b�t�@�̃N���A
				memset( this->m_pReadLineBuf, NULL, this->m_iReadLineSize );
				iCharIndex = 0;

				// �ȍ~�̏������s�킸�J��Ԃ�
				continue;
			}
		}

		// �s���J�E���g���[�h�̏ꍇ�͕������i�[�����ɓǂݑ�����
		if ( this->m_bRowsCountMode )
		{
			continue;
		}

		// ������̊i�[
		this->m_pReadLineBuf[ iCharIndex ] = cTmp;

		// �C���f�b�N�X�̃C���N�������g
		++iCharIndex;

		// ��s���̊m�ۃo�b�t�@������C���f�b�N�X�ɓ˓�����ꍇ
		if ( iCharIndex >= ( this->m_iReadLineSize - 1 ) )
		{
			// ������̈ꎞ�m��
			const int iOldLineSize = this->m_iReadLineSize;
			char *cTmpLineStr = new char[ this->m_iReadLineSize ];
			memset( cTmpLineStr, NULL, this->m_iReadLineSize );
			strcpy_s( this->m_pReadLineBuf, this->m_iReadLineSize, cTmpLineStr );

			// ��s�o�b�t�@�m�ۂ̏�����
			// �����݂�2�{�̃o�b�t�@���m�ۂ���
			this->ClearReadLineBuf();
			this->SetReadLineBufSize( this->m_iReadLineSize * 2 );

			// �m�ۂ���������̃R�s�[
			strcpy_s( cTmpLineStr, iOldLineSize, this->m_pReadLineBuf );

			// �������̉��
			delete[] cTmpLineStr;
			cTmpLineStr;
		}
	}

	// �t�@�C���N���[�Y
	fclose( fp );

	return bResult;
}

/**
 * ��s������̓Ǎ��R�[���o�b�N�֐�
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
	// �p�����[�^��������
	char **pcParam = new char*[ 10 ];
	this->SplitTextLine( cTextLineBuf, ' ', pcParam );

	// �e�X�g�L�q
	printf( "%s\n", pcParam[0] );
	printf( "%s\n", pcParam[1] );

	// �������̉��
	delete pcParam;
	pcParam = NULL;
#endif

#if 0
	// �p�����[�^��������
	char **pcParam = NULL;
	register size_t iSplitCount = this->SplitTextLine_Safe( cTextLineBuf, ' ', iTextLineLength, &pcParam );

	// �e�X�g�L�q
	if ( iSplitCount >= 2 )
	{
		printf( "%s\n", pcParam[0] );
		printf( "%s\n", pcParam[1] );
	}

	// �������̉��
	delete pcParam;
	pcParam = NULL;
#endif

	return bResult;
}

// �p�����[�^�擾
size_t CSpeedyTextReader::SplitTextLine( 
	char *cTextLine, 
	const char cSplitChar,
	char **pcOutParameter
	)
{
	register size_t iResult = -1;

	// �����_�J�E���g�̎擾
	register int iSplitIndex = 0;

	register size_t iIndex = 0;
	const size_t iLength = strlen( cTextLine );

	// ��������0�̏ꍇ
	if ( iLength <= 0 ) 
	{
		return iSplitIndex;
	}

	// ��납��for�ł܂킷(������=0���ȗ��ł��邽��)
//	while( iIndex < iLength )
	register size_t iLoopIndex = 0;
	for ( iLoopIndex = ( iLength - 1 ); iLoopIndex > 0; --iLoopIndex )
	{
		iIndex = ( iLength - 1 ) - iLoopIndex;

		// �����_�̎擾
		if ( iIndex == 0 )
		{
			// �p�����[�^�ӏ��̃|�C���^�Z�b�g
			pcOutParameter[ iSplitIndex ] = &( cTextLine[ iIndex ] );
			++iSplitIndex;
			++iIndex;

			// �������ĊJ����
			continue;
		}
		else if ( cTextLine[ iIndex ] == cSplitChar ) 
		{
			// �����������I�[�����ɒu��������
			cTextLine[ iIndex ] = '\0';

			// �p�����[�^�ӏ��̃|�C���^�Z�b�g
			++iIndex;
			pcOutParameter[ iSplitIndex ] = &( cTextLine[ iIndex ] );
			++iSplitIndex;

			// �������ĊJ����
			continue;
		}

		// �����_�ȊO
		// �C���f�b�N�X�̃C���N�������g
		++iIndex;
	}

	// �����_������Ԃ�
	iResult = iIndex;

	return iResult;
}

/**
 * �p�����[�^�擾(�m�ۂ��ăZ�b�g������S�֐�)
 * �p�����[�^�m�۔z����擾���ɕ����񐔊m��(�ő啪����)���Ă���s���܂��B
 * ��
 * ���S�ȕ��ᑬ�ł��B
 */
size_t CSpeedyTextReader::SplitTextLine_Safe( 
	char *cTextLine, 
	const char cSplitChar,
	const int iSplitMaxCount,
	char ***pcOutParameter
	)
{
	// ���������
	if ( *pcOutParameter )
	{
		delete *pcOutParameter;
		*pcOutParameter = NULL;
	}

	// �������m��
	*pcOutParameter = new char*[ iSplitMaxCount ];

	// �p�����[�^�擾�Ƒ�����Ԃ�
	return this->SplitTextLine( cTextLine, cSplitChar, *pcOutParameter );
}

