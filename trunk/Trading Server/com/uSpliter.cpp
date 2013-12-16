//---------------------------------------------------------------------------


#pragma hdrstop

#include "uSpliter.h"

//---------------------------------------------------------------------------
spliter::spliter(const char * text,const int length, const char c)
{
	const int MAX_TEXT =  10240;
	char item[MAX_TEXT];
	int pos = 0;

	for( int i=0; i<=length; i++ )
	{
		if( i == length || text[i] == c )
		{
			item[pos++] = '\0';
			pos = 0;
			_list.push_back(item);
		}
		else
		{
			if( (pos+1) < MAX_TEXT )
			{
				item[pos++] = text[i];
      }
    }
  }
}

spliter::spliter(const std::string &text, const char c )
{
	spliter(text.c_str(),text.length(),c);
}

const std::string & spliter::at(unsigned int pos) const
{
	if( pos< _list.size() )
	{
		return _list.at(pos);
	}
	else
	{
  	throw std::out_of_range("Index out of range.");
  }
}

const std::string & spliter::operator[](unsigned int pos) const
{
	return at(pos);
}

unsigned int spliter::size( void )
{
	return _list.size();
}
