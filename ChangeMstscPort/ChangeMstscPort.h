
// ChangeMstscPort.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CChangeMstscPortApp: 
// �йش����ʵ�֣������ ChangeMstscPort.cpp
//

class CChangeMstscPortApp : public CWinApp
{
public:
	CChangeMstscPortApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CChangeMstscPortApp theApp;