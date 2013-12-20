// readfile.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <fstream>
#include <string>
#include <iostream>
#include <vector>
#include <list>
#include <windows.h>

typedef std::vector<std::string> LINE;
void on_tick(const LINE &tick)
{
	static double sumofprice = 0;
	static int count = 0;
	if( tick[0].find("IF") == 0 )
	{
		int t = atoi(tick[30].c_str());

		if( t>= 91500 && t<= 151500 )
		{
			double price = atof(tick[6].c_str());
			if( price >0.0001)
			{
				sumofprice += price;
				count ++;
			}
		}
	}
};

int _tmain(int argc, _TCHAR* argv[])
{
	std::string filename = "2013-01-04.txt";
	DWORD oldtick = ::GetTickCount();
	std::ifstream is (filename.c_str(), std::ifstream::binary);
	if (is) 
	{
		// get length of file:
		is.seekg (0, is.end);
		int length = is.tellg();
		is.seekg (0, is.beg);

		char * buffer = new char [length];

		std::cout << "Reading " << length << " characters... " << std::endl;
		// read data as a block:
		is.read (buffer,length);

		if (is)
			std::cout << "all characters read successfully." << std::endl;
		else
			std::cout << "error: only " << is.gcount() << " could be read" << std::endl;
		is.close();

		// ...buffer contains the entire file...
		int idx = 0;

		std::string field;
		LINE line;
		for( int i=0; i<length; i++ )
		{
			switch( buffer[i] )
			{
			case ' ':
				line.push_back(field);
				field.clear();
				idx++;
				break;
			case '\n':
				//do some backtest
				on_tick(line);
				line.clear();
				break;
			case '\r':
				break;
			default:
				field.push_back(buffer[i]);
			}
		}

		delete[] buffer;
	}
	
	DWORD second = (::GetTickCount() - oldtick)/1000;
	std::cout << "Total seconds:" << second << std::endl;
	system("pause");
	return 0;
}

