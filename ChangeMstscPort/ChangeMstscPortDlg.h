
// ChangeMstscPortDlg.h : ͷ�ļ�
//

#pragma once


// CChangeMstscPortDlg �Ի���
class CChangeMstscPortDlg : public CDialogEx
{
// ����
public:
	CChangeMstscPortDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_CHANGEMSTSCPORT_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;
	HKEY hKey;

	// ���ɵ���Ϣӳ�亯��
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
