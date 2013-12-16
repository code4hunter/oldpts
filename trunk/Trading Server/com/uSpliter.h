//---------------------------------------------------------------------------

#ifndef uSpliterH
#define uSpliterH

#include <string>
#include <vector>
//---------------------------------------------------------------------------

class spliter
{
protected:
	std::vector<std::string>  _list;

public:
	spliter(const char * text,const int length, const char c);
	spliter(const std::string &text, const char c );
	const std::string & at(unsigned int pos) const;
	const std::string & operator[](unsigned int pos) const;
	unsigned int size( void );
};

#endif
