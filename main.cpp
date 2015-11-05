#include <stdio.h>
#include <time.h>
#include <Windows.h>
#include <MMSystem.h>

// 速読TextReaderクラス
#include "SpeedyTextReader.h"

// メモリリーク検出用
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>


int main( int argc, char **argv )
{
	// メモリリーク検出
	_CrtSetDbgFlag( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );

	printf("Hello World. \n");

	{
		// CBlockUnitMemory<int> cBM;
	}

	{
		// 計測点開始
		time_t _start = timeGetTime();

		// メイン処理
		CSpeedyTextReader *pReader = new CSpeedyTextReader( "C:\\Natsuki\\068C05.asc", 10000 );

		// pReader->SetRowsCountMode( true );
		bool bResult = pReader->Read();
		
		delete pReader;
		pReader = NULL;

		if ( !bResult )
		{
			printf("read fall! \n");
		}

		// 計測点終了
		time_t _execTime = timeGetTime() - _start;
		printf( "time = %d \n", _execTime );
	}

	// キー待ち処理
	getchar();

	return 0;
}

