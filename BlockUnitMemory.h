
template <class TYPE> 
class CBlockUnitMemory
{
private:

	// ��`
	static const int m_iDefBlockUnitSize;	// �u���b�N�P�ʂ̃T�C�Y

public:

	// �R���X�g���N�^�^�f�X�g���N�^
	CBlockUnitMemory();
	~CBlockUnitMemory();
/*
	// �u���b�N�P�ʌ���
	void SetBlockUnitSize( const int iBlockSize ){ this->m_iBlockUnitSize = iBlockSize; }

	// �������m��
	bool AllocMemory( const int iMemorySize );

	// ���������
	void ClearMemory();

	// �������A�N�Z�X
	TYPE &GetAt( const int iIndex );
*/
private:

	// �����o�ϐ�
	int m_iBlockUnitSize;					// 1�u���b�N�̃������T�C�Y
	int m_iBlockCount;						// �m�ۃ������̃u���b�N��

	TYPE **m_pBuffer;						// �o�b�t�@
};
