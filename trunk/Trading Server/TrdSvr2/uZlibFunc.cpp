//---------------------------------------------------------------------------

#include <ZLib.hpp>

#pragma hdrstop

#include "uZlibFunc.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)

// return out buffer ,you need free the buffer,result is sizeof(out buffer)
int zlib_compress( const void * in,const int size ,void **out)
{
	*out= NULL;
	TMemoryStream* dest = new TMemoryStream();
	TCompressionStream * cs = new TCompressionStream(Zlib::clDefault,dest);

	cs->Write(in,size);

	delete cs;

	int ret = 0;
	if( dest->Size > 0 )
	{
		*out = new char[dest->Size+sizeof(int)*2];
		dest->Position = 0;
		int * p = (int*)(*out);
		p[0] = dest->Size+sizeof(int);
		p[1] = size;
		ret = dest->Read( p+2 ,dest->Size);
	}

	delete dest;
	return ret+sizeof(int)*2;
}

int zlib_compress3( const void * in,const int size ,void *out,int& out_buffer_len)
{
	TMemoryStream* dest = new TMemoryStream();
	TCompressionStream * cs = new TCompressionStream(Zlib::clDefault,dest);

	cs->Write(in,size);

	delete cs;

	int ret = 0;
	if( dest->Size > 0 )
	{
		if (out_buffer_len<dest->Size+sizeof(int)*2) {
			delete[] out;
			out_buffer_len= dest->Size+sizeof(int)*2;
			out = new char[out_buffer_len];
		}
		dest->Position = 0;
		int * p = (int*)(out);
		p[0] = dest->Size+sizeof(int);
		p[1] = size;
		ret = dest->Read( p+2 ,dest->Size);
	}

	delete dest;
	return ret+sizeof(int)*2;
}

int zlib_decompress( const void *in,const int size,void **out)
{
	*out= NULL;

	TMemoryStream *source = new TMemoryStream();
	TDecompressionStream *ds = new TDecompressionStream(source);
	int *p = (int*)(in);
	int orgLen = p[0];

	source->Write(p+1,size-sizeof(int));

	int ret  = 0;
	if( orgLen >0 )
	{
		*out =new char[orgLen];
		ret = ds->Read(*out,orgLen);
	}

	delete source;
	delete ds;

	return ret;
}

int zlib_compress2( const void * in,const int size ,void *out,int out_size)
{
	TMemoryStream* dest = new TMemoryStream();
	TCompressionStream * cs = new TCompressionStream(Zlib::clDefault,dest);

	cs->Write(in,size);
	delete cs;

	int ret = 0;
	if( dest->Size > 0 && dest->Size+sizeof(int)*2 <=out_size )
	{
		dest->Position = 0;
		int * p = (int*)(out);
		p[0] = dest->Size+sizeof(int);
		p[1] = size;
		ret = dest->Read( p+2 ,dest->Size);
	}
	delete dest;
	return ret+sizeof(int)*2;
}

int zlib_decompress2( const void *in,const int size,void *out,int out_size)
{
	TMemoryStream *source = new TMemoryStream();
	TDecompressionStream *ds = new TDecompressionStream(source);
	int ret  = 0;
	
	try
	{
		int *p = (int*)(in);
		int orgLen = p[0];

		source->Write(p+1,size-sizeof(int));

		if(orgLen>0 && orgLen <= out_size )
		{
			ret = ds->Read(out,out_size);
		}
	}
	catch(...)
	{
	}
	delete source;
	delete ds;
	return ret;
}

int zlib_decompress3( const void *in,const int size,void *out,int out_size,int org_len)
{
	TMemoryStream *source = new TMemoryStream();
	TDecompressionStream *ds = new TDecompressionStream(source);
    int ret  = 0;

	try
	{
		source->Write(in,size);

		if(org_len>0 && org_len <= out_size )
		{
			ret = ds->Read(out,out_size);
		}
	}
	catch(...)
	{
	}
	
	delete source;
	delete ds;

	return ret;
}
