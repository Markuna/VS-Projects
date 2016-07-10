
// FTPDlg.h : 头文件
//

#pragma once
#include "afxwin.h"
#include "Afxinet.h"


// CFTPDlg 对话框
class CFTPDlg : public CDialogEx
{
// 构造
public:
	CFTPDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_FTP_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CString m_strFtp;
	CEdit m_editFtp;
	CString m_strName;
	CEdit m_editName;
	CString m_strPwd;
	CEdit m_editPwd;
	CStatic m_staFtp;
	CStatic m_staName;
	CStatic m_staPwd;
	CButton m_btnQuery;
	CButton m_btnDownload;
	CButton m_btnUpload;
	CListBox m_listFile;
	afx_msg void OnQuery();
	afx_msg void OnDownload();
	afx_msg void OnUpload();
	afx_msg void OnSelchangeListFile();

	BOOL CFTPDlg::Download(CString strSName, CString strDName);
	BOOL CFTPDlg::Upload(CString strSName, CString strDName);
	afx_msg void OnLbnSelchangeListFile();
};
