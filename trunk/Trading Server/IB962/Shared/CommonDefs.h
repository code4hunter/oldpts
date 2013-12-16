#ifndef common_defs_h_INCLUDED
#define common_defs_h_INCLUDED

typedef long TickerId;
typedef long OrderId;

enum faDataType { GROUPS=1, PROFILES, ALIASES } ;

inline const char* faDataTypeStr ( faDataType pFaDataType )
{
	switch (pFaDataType) {
		case GROUPS:
			return "GROUPS" ;
		case PROFILES:
			return "PROFILES" ;
		case ALIASES:
			return "ALIASES" ;
	}
	return 0 ;
}

#endif /* common_defs_h_INCLUDED */
