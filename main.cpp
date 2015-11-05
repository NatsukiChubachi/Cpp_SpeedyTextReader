#include <stdio.h>
#include <time.h>
#include <Windows.h>
#include <MMSystem.h>

// ����TextReader�N���X
#include "SpeedyTextReader.h"

// ���������[�N���o�p
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>


int main( int argc, char **argv )
{
	// ���������[�N���o
	_CrtSetDbgFlag( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );

	printf("Hello World. \n");

	{
		// CBlockUnitMemory<int> cBM;
	}

	{
		// �v���_�J�n
		time_t _start = timeGetTime();

		// ���C������
		CSpeedyTextReader *pReader = new CSpeedyTextReader( "C:\\Natsuki\\068C05.asc", 10000 );

		// pReader->SetRowsCountMode( true );
		bool bResult = pReader->Read();
		
		delete pReader;
		pReader = NULL;

		if ( !bResult )
		{
			printf("read fall! \n");
		}

		// �v���_�I��
		time_t _execTime = timeGetTime() - _start;
		printf( "time = %d \n", _execTime );
	}

	// �L�[�҂�����
	getchar();

	return 0;
}

