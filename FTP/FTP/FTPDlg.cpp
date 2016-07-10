
// FTPDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "FTP.h"
#include "FTPDlg.h"
#include "afxdialogex.h"
#include <Afxinet.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CFTPDlg 对话框



CFTPDlg::CFTPDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_FTP_DIALOG, pParent)
	, m_strFtp(_T(""))
	, m_strName(_T(""))
	, m_strPwd(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CFTPDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_FTP, m_strFtp);
	DDX_Control(pDX, IDC_EDIT_FTP, m_editFtp);
	DDX_Text(pDX, IDC_EDIT_NAME, m_strName);
	DDX_Control(pDX, IDC_EDIT_NAME, m_editName);
	DDX_Text(pDX, IDC_EDIT_PWD, m_strPwd);
	DDX_Control(pDX, IDC_EDIT_PWD, m_editPwd);
	DDX_Control(pDX, IDC_STATIC_FTP, m_staFtp);
	DDX_Control(pDX, IDC_STATIC_NAME, m_staName);
	DDX_Control(pDX, IDC_STATIC_PWD, m_staPwd);
	DDX_Control(pDX, IDOK, m_btnQuery);
	DDX_Control(pDX, IDC_DOWNLOAD, m_btnDownload);
	DDX_Control(pDX, IDC_UPLOAD, m_btnUpload);
	DDX_Control(pDX, IDC_LIST_FILE, m_listFile);
}

BEGIN_MESSAGE_MAP(CFTPDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CFTPDlg::OnQuery)
	//ON_BN_CLICKED(IDC_DOWNLOAD, &CFTPDlg::OnDownload)
	//ON_BN_CLICKED(IDC_UPLOAD, &CFTPDlg::OnUpload)
	//ON_LBN_SELCHANGE(IDC_LIST_FILE, &CFTPDlg::OnSelchangeListFile)
	ON_LBN_SELCHANGE(IDC_LIST_FILE, &CFTPDlg::OnLbnSelchangeListFile)
END_MESSAGE_MAP()



// CFTPDlg 消息处理程序

BOOL CFTPDlg::OnInitDialog()
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

	// TODO: 在此添加额外的初始化代码
	// TODO: Add extra initialization here
	m_strFtp = _T("");      // 初始化服务器域名
	m_strName = _T("");     // 初始化登录用户名
	m_strPwd = _T("");      //  初始化登录口令
	UpdateData(FALSE);      //更新界面

	return TRUE;            // 除非将焦点设置到控件，否则返回 TRUE
}

void CFTPDlg::OnSysCommand(UINT nID, LPARAM lParam)
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


void CFTPDlg::OnPaint()
{
	if (IsIconic())
	{
		// 用于绘制的设备上下文
		CPaintDC dc(this); 

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

//显示。
HCURSOR CFTPDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CFTPDlg::OnQuery()
{
	CInternetSession* pSession;       //定义会话对象指针变量
	CFtpConnection* pConnection;      //定义连接对象指针变量
	CFtpFileFind* pFileFind;          //定义文件查询对象指针变量
	CString strFileName;
	BOOL bContinue;

	pConnection = NULL;      //初始化
	pFileFind = NULL;

	UpdateData(TRUE);       // 获得用户的当前输入（服务器名，用户名和口令）
	while (m_listFile.GetCount() != 0) m_listFile.DeleteString(0);  // 清除列表框的内容

	pSession = new CInternetSession(          // 创建Internet会话类对象
		AfxGetAppName(), 1, PRE_CONFIG_INTERNET_ACCESS);
	try
	{  // 试图建立与指定FTP服务器的连接
		pConnection =
			pSession->GetFtpConnection(m_strFtp, m_strName, m_strPwd);
	}
	catch (CInternetException* e) {
		e->Delete();                          // 无法建立连接，进行错误处理
		pConnection = NULL;
	}

	if (pConnection != NULL)
	{// 创建CFtpFileFind对象，向构造函数传递CFtpConnection对象的指针
		pFileFind = new CFtpFileFind(pConnection);
		bContinue = pFileFind->FindFile(_T("*"));  // 查找服务器上当前目录的任意文件
		if (!bContinue)   // 如果一个文件都找不到，结束查找
		{
			pFileFind->Close();
			pFileFind = NULL;
		}

		while (bContinue)  // 找到了第一个文件，继续找其它的文件
		{
			strFileName = pFileFind->GetFileName();  // 获得找到的文件的文件名
													 // 如果找到的是否目录，将目录名放在括弧中
			if (pFileFind->IsDirectory())  strFileName = "[ + strFileName + ]";
			// 将找到的文件或目录名显示在列表框中。
			m_listFile.AddString(strFileName);
			bContinue = pFileFind->FindNextFile();    // 查找下一个文件
		}

		if (pFileFind != NULL)
		{
			pFileFind->Close();   // 结束查询
			pFileFind = NULL;
		}
	}
	delete pFileFind;              // 删除文件查询对象
	if (pConnection != NULL)
	{
		pConnection->Close();
		delete pConnection;      // 删除FTP连接对象
	}
	delete pSession;             // 删除Internet 会话对象 

	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnOK();
}


void CFTPDlg::OnDownload()
{
	// TODO: 在此添加控件通知处理程序代码
	//获得当前输入
	UpdateData(TRUE);
	int nSel = m_listFile.GetCurSel();
	CString strSourceName;

	//获得用户在列表框中的选择
	nSel = m_listFile.GetCurSel();
	m_listFile.GetText(nSel, strSourceName);

	if (strSourceName.GetAt(0) != '[')
	{
		//选择的是文件
		CString strDestName;
		CFileDialog dlg(FALSE, L"", L"*.*");   //定义了一个文件对话框对象变量
		if (dlg.DoModal() == IDOK)        //激活文件对话框
		{
			//获得下载文件在本地机上存储的路径和名称
			strDestName = dlg.GetPathName();

			//调用函数下载文件
			if (Download(strSourceName, strDestName))
				AfxMessageBox(_T("下载成功！"), MB_OK | MB_ICONINFORMATION);
			else
				AfxMessageBox(_T("下载失败！"), MB_OK | MB_ICONSTOP);
		}
		else {
			AfxMessageBox(_T("请写入文件名！"), MB_OK | MB_ICONSTOP);
		}
	}
	else {
		//选择的是目录
		AfxMessageBox(_T("不能下载目录!\n请重选!"), MB_OK | MB_ICONSTOP);
	}

	//禁用下载按钮
	m_btnDownload.EnableWindow(FALSE);

	//激活查询和上传按钮
	m_btnUpload.EnableWindow(TRUE);
	m_btnQuery.EnableWindow(TRUE);

	//激活用来输入的文本和编辑框控件
	m_editFtp.EnableWindow(TRUE);
	m_editName.EnableWindow(TRUE);
	m_editPwd.EnableWindow(TRUE);
	m_staFtp.EnableWindow(TRUE);
	m_staName.EnableWindow(TRUE);
	m_staPwd.EnableWindow(TRUE);

}


void CFTPDlg::OnUpload()
{
	// TODO: 在此添加控件通知处理程序代码
	//获得当前输入
	UpdateData(TRUE);

	//禁用用于输入的文本框控件
	m_editFtp.EnableWindow(FALSE);            //服务器域名输入文本框
	m_editName.EnableWindow(FALSE);          //登录客户名输入文本框
	m_editPwd.EnableWindow(FALSE);            //口令输入文本框
	m_staFtp.EnableWindow(FALSE);
	m_staName.EnableWindow(FALSE);
	m_staPwd.EnableWindow(FALSE);

	//禁用查询按钮
	m_btnQuery.EnableWindow(FALSE);

	CString strSourceName;
	CString strDestName;
	CFileDialog dlg(TRUE, L"", L"*.*");       //定义文本对话框对象变量
	if (dlg.DoModal() == IDOK)
	{
		//获得待上传的本地机文件路径和文件名
		strSourceName = dlg.GetPathName();
		strDestName = dlg.GetFileName();

		//调用Upload函数上传文件
		if (Upload(strSourceName, strDestName))
			AfxMessageBox(_T("上传成功！"), MB_OK | MB_ICONINFORMATION);
		else
			AfxMessageBox(_T("上传失败！"), MB_OK | MB_ICONSTOP);
	}
	else {
		//文件选择有错误
		AfxMessageBox(_T("请选择文件！"), MB_OK | MB_ICONSTOP);
	}

	//激活查询按钮
	m_btnQuery.EnableWindow(TRUE);

	//激活用于输入的文本框控件
	m_editFtp.EnableWindow(TRUE);
	m_editName.EnableWindow(TRUE);
	m_editPwd.EnableWindow(TRUE);
	m_staFtp.EnableWindow(TRUE);
	m_staName.EnableWindow(TRUE);
	m_staPwd.EnableWindow(TRUE);

}


void CFTPDlg::OnSelchangeListFile()
{
	// TODO: 在此添加控件通知处理程序代码
	// 禁用用来输入的文本框控件
	m_editFtp.EnableWindow(FALSE);          //服务器域名输入文本框
	m_editName.EnableWindow(FALSE);        //登录用户名输入文本框 
	m_editPwd.EnableWindow(FALSE);          //口令输入文本框
	m_staFtp.EnableWindow(FALSE);
	m_staName.EnableWindow(FALSE);
	m_staPwd.EnableWindow(FALSE);

	//禁用查询和上传按钮
	m_btnUpload.EnableWindow(FALSE);      //上传按钮
	m_btnQuery.EnableWindow(FALSE);        //查询按钮

										   //激活下载按钮
	m_btnDownload.EnableWindow(TRUE);

}

BOOL CFTPDlg::Download(CString strSName, CString strDName)
{
	CInternetSession* pSession;      //定义会话对象变量指针
	CFtpConnection* pConnection;    //定义连接对象变量指针

	pConnection = NULL;

	//创建Internet会话对象
	pSession = new CInternetSession(AfxGetAppName(), 1,
		PRE_CONFIG_INTERNET_ACCESS);

	try
	{
		//建立FTP连接
		pConnection = pSession->GetFtpConnection(m_strFtp, m_strName, m_strPwd);
	}
	catch (CInternetException* e)
	{
		//错误处理
		e->Delete();
		pConnection = NULL;
		return FALSE;
	}

	if (pConnection != NULL)
	{
		//下载文件
		if (!pConnection->GetFile(strSName, strDName))
		{
			//下载文件错误
			pConnection->Close();
			delete pConnection;
			delete pSession;
			return FALSE;
		}
	}

	//清除对象
	if (pConnection != NULL)
	{
		pConnection->Close();
		delete pConnection;
	}
	delete pSession;

	return TRUE;

}
BOOL CFTPDlg::Upload(CString strSName, CString strDName)
{
	CInternetSession* pSession;
	CFtpConnection* pConnection;

	pConnection = NULL;

	//创建Internet会话
	pSession = new CInternetSession(AfxGetAppName(), 1,
		PRE_CONFIG_INTERNET_ACCESS);

	try
	{
		//建立FTP连接
		pConnection = pSession->GetFtpConnection(m_strFtp,
			m_strName, m_strPwd);
	}
	catch (CInternetException* e)
	{
		//错误处理
		e->Delete();
		pConnection = NULL;
		return FALSE;
	}

	if (pConnection != NULL)
	{
		//上传文件
		if (!pConnection->PutFile(strSName, strDName))
		{
			//上传文件错误
			pConnection->Close();
			delete pConnection;
			delete pSession;
			return FALSE;
		}
	}

	//清除对象
	if (pConnection != NULL)
	{
		pConnection->Close();
		delete pConnection;
	}

	delete pSession;

	return TRUE;

}



void CFTPDlg::OnLbnSelchangeListFile()
{
	// TODO: 在此添加控件通知处理程序代码
}
