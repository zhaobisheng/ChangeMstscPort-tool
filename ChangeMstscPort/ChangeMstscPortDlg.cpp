
// ChangeMstscPortDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "ChangeMstscPort.h"
#include "ChangeMstscPortDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CChangeMstscPortDlg 对话框



CChangeMstscPortDlg::CChangeMstscPortDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CChangeMstscPortDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CChangeMstscPortDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CChangeMstscPortDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_CHANGE, &CChangeMstscPortDlg::OnBnClickedButtonChange)
END_MESSAGE_MAP()


// CChangeMstscPortDlg 消息处理程序

BOOL CChangeMstscPortDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	//ShowWindow(SW_MINIMIZE);


	SkinH_Attach();

	::SkinH_AttachEx("skinh.she", NULL);
	ReadRegisterKey();
	// TODO:  在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CChangeMstscPortDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CChangeMstscPortDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CChangeMstscPortDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CChangeMstscPortDlg::OnBnClickedButtonChange()
{

	CString Key_Path = "SYSTEM\\CurrentControlSet\\Control\\Terminal Server\\Wds\\rdpwd\\Tds\\tcp";
	CString Key_Path1 = "SYSTEM\\CurrentControlSet\\Control\\Terminal Server\\WinStations\\RDP-Tcp";
	const char KeyName[] = "PortNumber";
	CString StrPort,OldStrPort;
	GetDlgItem(IDC_EDIT_NEWPORT)->GetWindowTextA(StrPort);
	GetDlgItem(IDC_EDIT_OLDPORT)->GetWindowTextA(OldStrPort);
	
	BOOL flag, flag1;
	flag1 = WriteKeyValue(HKEY_LOCAL_MACHINE, Key_Path1, KeyName, StrPort, REG_DWORD);
	flag = WriteKeyValue(HKEY_LOCAL_MACHINE, Key_Path, KeyName, StrPort, REG_DWORD);

	if (flag && flag1)
	{
		ReadRegisterKey();
		if(IDYES == MessageBox("新端口设置成功!是否10秒后重启生效？", "Bison提示", MB_YESNO))
				 {
					 
					 OnMenuShutdown();
				 }
	
	}
	else{
		flag = WriteKeyValue(HKEY_LOCAL_MACHINE, Key_Path, KeyName, OldStrPort, REG_DWORD);
		flag1 = WriteKeyValue(HKEY_LOCAL_MACHINE, Key_Path1, KeyName, OldStrPort, REG_DWORD);
	}
	ReadRegisterKey();

}

BOOL CChangeMstscPortDlg::WriteKeyValue(HKEY RootPath, CString Key_Path, CString KeyName,CString StrData ,DWORD dwType=REG_DWORD)
{

	HKEY bKey;
	DWORD Data = atoi(StrData);
	int iResult;
	
	iResult = RegOpenKeyEx(RootPath, Key_Path, NULL, KEY_WRITE, &bKey);
	if (iResult != ERROR_SUCCESS) { AfxMessageBox("打开注册表失败，请检查权限..."); return false; }
	if (RegSetValueEx(bKey, KeyName, NULL, dwType, (const BYTE*)&Data, sizeof(DWORD)) != ERROR_SUCCESS)  { AfxMessageBox(" 更改注册表失败，请检查权限..."); return false; }
	RegCloseKey(bKey);
	return true;
}

void CChangeMstscPortDlg::ReadRegisterKey()
{
	CString Str,Str1;
	HKEY TempKey;
	int iResult, iResult1;
	BYTE  Port[64] = { 0 };

	DWORD dwType = REG_DWORD;
	DWORD DataSize;

	LPCTSTR Key_Path = "SYSTEM\\CurrentControlSet\\Control\\Terminal Server\\Wds\\rdpwd\\Tds\\tcp";
	const   char   _szKeyName[] = "PortNumber";

	iResult = RegOpenKeyEx(HKEY_LOCAL_MACHINE, Key_Path, NULL, KEY_READ, &hKey);
	if (iResult != ERROR_SUCCESS){ AfxMessageBox(_T("读取注册表失败，请检查权限..."));  }
	DWORD flag = RegQueryValueEx(hKey, (LPCSTR)_szKeyName, NULL,NULL, (BYTE*)Port, &DataSize);

	int *NowPort=(int *)Port;
	Str.Format("%d", *NowPort);

	RegCloseKey(hKey);
	NowPort = NULL; free(NowPort);

	BYTE  Port1[64] = { 0 };
	CString Key_Path1 = "SYSTEM\\CurrentControlSet\\Control\\Terminal Server\\WinStations\\RDP-Tcp";
	iResult1 = RegOpenKeyEx(HKEY_LOCAL_MACHINE, Key_Path1, NULL, KEY_READ, &TempKey);
	if (iResult1 != ERROR_SUCCESS){ AfxMessageBox(_T("读取注册表失败1，请检查权限...")); }
	DWORD flag1 = RegQueryValueEx(TempKey, (LPCSTR)_szKeyName, NULL, NULL, (BYTE*)Port1, &DataSize);
	 NowPort = (int *)Port1;
	Str1.Format("%d", *NowPort);
	RegCloseKey(TempKey);
	NowPort=NULL;

	if (atoi(Str) == atoi(Str1)){
	GetDlgItem(IDC_EDIT_OLDPORT)->SetWindowTextA(Str);
	}
	else
	{
		GetDlgItem(IDC_EDIT_OLDPORT)->SetWindowTextA("不一致");
	}
	GetDlgItem(IDC_EDIT_OLDPORT)->EnableWindow(false);
	GetDlgItem(IDC_EDIT_NEWPORT)->SetWindowTextA("12345");
}

void CChangeMstscPortDlg::OnMenuShutdown()
{
	
	Sleep(10000);
		HANDLE hToken;
		TOKEN_PRIVILEGES tkp;
		// Get a token for this process.
		if (!OpenProcessToken(GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &hToken))
		{
			AfxMessageBox("OpenProcessToken Error!");
			return;
		}
		// Get the LUID for the shutdown privilege.
		LookupPrivilegeValue(NULL, SE_SHUTDOWN_NAME, &tkp.Privileges[0].Luid);
		tkp.PrivilegeCount = 1; // one privilege to set
		tkp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;
		AdjustTokenPrivileges(hToken, FALSE, &tkp, sizeof(TOKEN_PRIVILEGES), (PTOKEN_PRIVILEGES)NULL, NULL);
		if (GetLastError() != ERROR_SUCCESS)
		{
			AfxMessageBox("重启失败");
			return;
		}

		ExitWindowsEx(EWX_REBOOT | EWX_FORCE, 0);
	//}
}
