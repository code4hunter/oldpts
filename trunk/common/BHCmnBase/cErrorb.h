#if !defined(AFX_cErrorb_H__B0419ACA_D198_11D3_AE4F_00E029031C67__INCLUDED_)
#define AFX_cErrorb_H__B0419ACA_D198_11D3_AE4F_00E029031C67__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class cErrorb  
{
protected:
	char d_text[ 1000 ];

public:
	cErrorb( const char *pText );
	cErrorb();
	virtual ~cErrorb();


  const char *Text()
  {
    return (const char *)d_text;
  }
};

#endif // !defined(AFX_CERROR_H__B0419ACA_D198_11D3_AE4F_00E029031C67__INCLUDED_)
