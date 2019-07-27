#ifndef __INIFILE__H__
#define __INIFILE__H__
#include <windows.h>
#include <tchar.h>
//#include "STD.h"

char * ltrim(char *str) {
	char *s = str;
	while (*s == ' ') s++;
	//strcpy(str, s); //自己修改 sizeof
	strcpy_s(str,sizeof(str), s); //自己修改 sizeof
	return str;
}

char *rtrim(char *str) {
	char *s = str + strlen(str) - 1;
	while (s - str >= 0 && (*s == ' ' || *s == '\n')) s--;
	s++;
	*s = 0;
	return str;
}

char * alltrim(char *str)
{
	ltrim(str);
	rtrim(str);
	return str;
}



class CIniFile
{
protected:
	TCHAR	m_szFileName[500];
	WCHAR	m_wszFileName[500];

public:
	CIniFile(LPCTSTR  FileName)		{ lstrcpyn(m_szFileName, FileName, sizeof(m_szFileName) ); m_wszFileName[0] = 0; }
	virtual ~CIniFile() {};

public:
	/*
	LPTSTR	ReadString(LPCTSTR Section, LPCTSTR Name, LPCTSTR Default, LPTSTR out, DWORD size)
	{
		GetPrivateProfileString(Section, Name, Default, out, size, m_szFileName);
 
		//STD::
			alltrim(out);
		return out;
	}

	WCHAR*	ReadWString(WCHAR* Section, WCHAR* Name, WCHAR* Default, WCHAR* out, DWORD size)
	{
		if (m_wszFileName[0] == 0)
		{
			STD::ConvertToUnicode(m_wszFileName, dim(m_wszFileName), m_szFileName);
		}
		GetPrivateProfileStringW(Section, Name, Default, out, size, m_wszFileName);
		return out;
	}	*/
	int		ReadInt(LPCTSTR Section, LPCTSTR Name, int Default)
	{
		return GetPrivateProfileInt(Section, Name, Default, m_szFileName);
	}
	int		ReadInteger(LPCTSTR Section, LPCTSTR Name, int Default)
	{
		return ReadInt(Section, Name, Default);
	}

	/*
	bool	ReadBool(LPCTSTR Section, LPCTSTR Name, bool Default)
	{
		char str[50];
		ReadString(Section, Name, "", str, dim(str));
		if (str[0] == 0)
		{
			return Default;
		}
		///else if (stricmp_s(str, "yes") == 0)
		else if (stricmp(str, "yes") == 0)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	*/

public:
	BOOL	WriteString(LPCTSTR Section, LPCTSTR Name, LPCTSTR Value)
	{
		return WritePrivateProfileString(Section, Name, Value, m_szFileName);
	}
	BOOL	WriteInt(LPCTSTR Section, LPCTSTR Name, int Value)
	{
		TCHAR			tempbuf[256];

		_sntprintf_s(tempbuf,256,256,_T("%d"),Value);
		return WritePrivateProfileString(Section, Name, tempbuf, m_szFileName);
	}
};
//--------------------------------------------------------------------------------------------------------------------------------
#endif
//--------------------------------------------------------------------------------------------------------------------------------