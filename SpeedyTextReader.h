/**
 * @note 
 * ��K�͂ȃe�L�X�g�f�[�^��ǂݍ��ޏꍇ��
 * �ȃ������ő���Read���邱�Ƃ�ڎw�����N���X�ł��B
 * ��x�ɑS�t�@�C�����e���m�ۂ���̂ł͂Ȃ��A1���C�����m�ۂ��ď������s�����Ƃŏȃ����������s���Ă��܂�
 *
 * ��Tips
 * ���m�ۃ��������𒴂���s�̕������擾�����Ƃ��ɍĊm�ۂ��s���邽�߁A�\�ߑ傫�Ȑ����w�肷�邱�ƂōĊm�ۂ̉񐔂����炷���Ƃ��o���܂�
 * (�������g�p�ʂƈ��������ɓǍ��ݎ��̃��X�����炵�܂�)
 *
 * ���g�p���@
 * ���̃N���X���p�������N���X��CallbackGetTextLine���I�[�o�[���C�h���A
 * Read��ɌĂ΂�邱�̊֐��Ŏ擾����������ɉ������������s���Ă�������
 * SplitTextLine�ŕ����̕������w�肵�ăp�����[�^���擾������^�ϊ�����ȂǁA�K�X�g�p���Ă�������
 *
 * ���g�p��
 * CSpeedyTextReader *pReader = new CSpeedyTextReader( "***.txt" );
 * pReader->Read();
 * delete pReader;
 * pReader = NULL;
 * 
 */

#include <stdio.h>
#include <tchar.h>
#include <string>

// ���Ǐȃ������e�L�X�g���[�_�[
class CSpeedyTextReader
{
private:

	// ��`�l
	static const int iDefInitialReadLineBufSize;	// ��s�Ǎ��݃o�b�t�@�̏����T�C�Y

public:

	// �R���X�g���N�^�^�f�X�g���N�^
	CSpeedyTextReader( 
		const char *strFilePath,
		const int iLineBufSie = iDefInitialReadLineBufSize
		);											// �R���X�g���N�^
	virtual ~CSpeedyTextReader();					// �f�X�g���N�^

	// ��s�Ǎ��݃o�b�t�@�֘A
	void ClearReadLineBuf();						// ��s�Ǎ��݃o�b�t�@�̃������N���A
	void SetReadLineBufSize( const int iBufSize );	// ��s�Ǎ��݃o�b�t�@�T�C�Y�̃Z�b�g

	// �Ǎ��݊J�n
	// ���t�@�C���̓Ǎ��݂��J�n���܂�
	bool Read();									// �ǂݍ��݊J�n

	// ��s�������ǂݍ��񂾎��ɌĂ΂��R�[���o�b�N�֐�
	// ���p�������̊֐����I�[�o�[���C�h���Ďg�p���܂�
	virtual bool CallbackGetTextLine(				// ��s������̓Ǎ��R�[���o�b�N�֐�
		char *cTextLineBuf,
		const int iTextLineLength,
		const int iTextLineCount
		);

	// ���𔻒蕶��
	inline void SetSplitChar( const char cSplitChar ){ this->m_cSplitChar = cSplitChar; }

	// �p�����[�^�擾
	size_t SplitTextLine( char *cTextLine, const char cSplitChar, char **pcOutParameter );

	// �p�����[�^�擾(�m�ۂ��ăZ�b�g������S�֐�)
	size_t SplitTextLine_Safe( char *cTextLine, const char cSplitChar, const int iSplitMaxCount, char ***pcOutParameter );

	// �s���J�E���g���[�h�̃Z�b�g�t���O
	inline void SetRowsCountMode( const bool bFlag ){ this->m_bRowsCountMode = bFlag; }

private:

	// �����o�ϐ�
	char *m_pFilePath;								// �t�@�C�����p�X

	char *m_pReadLineBuf;							// ��s�Ǎ��݃o�b�t�@
	int  m_iReadLineSize;							// ��s�Ǎ��݃T�C�Y

	int  m_iReadLineRows;							// �s���J�E���g

	char m_cSplitChar;								// ���𔻒蕶��
	int  m_iSplitCount;								// �����J�E���g

	bool m_bRowsCountMode;							// �s���J�E���g���[�h�t���O
};

