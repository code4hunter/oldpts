#ifndef _VERSINFO_
#define _VERSINFO_

class VersionInfo
{
public:

	VersionInfo (const char * const inFilename );
	~VersionInfo();

	bool hasInfo () const
	{return theVersionInfo!=0 ;}

	unsigned short majorVersion () const;
	unsigned short minorVersion () const;
	unsigned short build () const;
	unsigned short subBuild () const;

	unsigned short productMajorVersion () const;
	unsigned short productMinorVersion () const;
	unsigned short productBuild () const;
	unsigned short productSubBuild () const;

	unsigned long fileFlagsMask() const;
	unsigned long fileFlags() const;
	unsigned long fileOS() const;
	unsigned long fileType() const;
	unsigned long fileSubType() const;

protected:
private:

	void * theVersionInfo;
	void * theFixedInfo;
}; // end VersionInfo class declaration

#endif
