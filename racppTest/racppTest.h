
// racppTest.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CracppTestApp:
// �йش����ʵ�֣������ racppTest.cpp
//

class CracppTestApp : public CWinApp
{
public:
	CracppTestApp();

// ��д
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance(); // return app exit code

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CracppTestApp theApp;