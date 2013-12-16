//---------------------------------------------------------------------------

#ifndef uZlibFuncH
#define uZlibFuncH


int zlib_compress( const void * in,const int size ,void **out);
int zlib_decompress( const void *in,const int size,void **out);

int zlib_compress2( const void * in,const int size ,void *out,int out_size);
int zlib_decompress2( const void *in,const int size,void *out,int out_size);
int zlib_decompress3( const void *in,const int size,void *out,int out_size,int org_len);

int zlib_compress3( const void * in,const int size ,void *out,int &out_buffer_len);
//---------------------------------------------------------------------------
#endif
