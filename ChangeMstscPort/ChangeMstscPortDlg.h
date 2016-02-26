
// ChangeMstscPortDlg.h : 头文件
//

#pragma once


// CChangeMstscPortDlg 对话框
class CChangeMstscPortDlg : public CDialogEx
{
// 构造
public:
	CChangeMstscPortDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_CHANGEMSTSCPORT_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;
	HKEY hKey;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnMenuShutdown();
	afx_msg void ReadRegisterKey();
	afx_msg void OnBnClickedButtonChange();
	afx_msg BOOL WriteKeyValue(HKEY RootPath, CString Key_Path, CString KeyName, CString Data, DWORD dwType);
};
