
// FTPDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "FTP.h"
#include "FTPDlg.h"
#include "afxdialogex.h"
#include <Afxinet.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
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


// CFTPDlg �Ի���



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



// CFTPDlg ��Ϣ�������

BOOL CFTPDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
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

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	// TODO: Add extra initialization here
	m_strFtp = _T("");      // ��ʼ������������
	m_strName = _T("");     // ��ʼ����¼�û���
	m_strPwd = _T("");      //  ��ʼ����¼����
	UpdateData(FALSE);      //���½���

	return TRUE;            // ���ǽ��������õ��ؼ������򷵻� TRUE
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
		// ���ڻ��Ƶ��豸������
		CPaintDC dc(this); 

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//��ʾ��
HCURSOR CFTPDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CFTPDlg::OnQuery()
{
	CInternetSession* pSession;       //����Ự����ָ�����
	CFtpConnection* pConnection;      //�������Ӷ���ָ�����
	CFtpFileFind* pFileFind;          //�����ļ���ѯ����ָ�����
	CString strFileName;
	BOOL bContinue;

	pConnection = NULL;      //��ʼ��
	pFileFind = NULL;

	UpdateData(TRUE);       // ����û��ĵ�ǰ���루�����������û����Ϳ��
	while (m_listFile.GetCount() != 0) m_listFile.DeleteString(0);  // ����б�������

	pSession = new CInternetSession(          // ����Internet�Ự�����
		AfxGetAppName(), 1, PRE_CONFIG_INTERNET_ACCESS);
	try
	{  // ��ͼ������ָ��FTP������������
		pConnection =
			pSession->GetFtpConnection(m_strFtp, m_strName, m_strPwd);
	}
	catch (CInternetException* e) {
		e->Delete();                          // �޷��������ӣ����д�����
		pConnection = NULL;
	}

	if (pConnection != NULL)
	{// ����CFtpFileFind�������캯������CFtpConnection�����ָ��
		pFileFind = new CFtpFileFind(pConnection);
		bContinue = pFileFind->FindFile(_T("*"));  // ���ҷ������ϵ�ǰĿ¼�������ļ�
		if (!bContinue)   // ���һ���ļ����Ҳ�������������
		{
			pFileFind->Close();
			pFileFind = NULL;
		}

		while (bContinue)  // �ҵ��˵�һ���ļ����������������ļ�
		{
			strFileName = pFileFind->GetFileName();  // ����ҵ����ļ����ļ���
													 // ����ҵ����Ƿ�Ŀ¼����Ŀ¼������������
			if (pFileFind->IsDirectory())  strFileName = "[ + strFileName + ]";
			// ���ҵ����ļ���Ŀ¼����ʾ���б���С�
			m_listFile.AddString(strFileName);
			bContinue = pFileFind->FindNextFile();    // ������һ���ļ�
		}

		if (pFileFind != NULL)
		{
			pFileFind->Close();   // ������ѯ
			pFileFind = NULL;
		}
	}
	delete pFileFind;              // ɾ���ļ���ѯ����
	if (pConnection != NULL)
	{
		pConnection->Close();
		delete pConnection;      // ɾ��FTP���Ӷ���
	}
	delete pSession;             // ɾ��Internet �Ự���� 

	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CDialogEx::OnOK();
}


void CFTPDlg::OnDownload()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//��õ�ǰ����
	UpdateData(TRUE);
	int nSel = m_listFile.GetCurSel();
	CString strSourceName;

	//����û����б���е�ѡ��
	nSel = m_listFile.GetCurSel();
	m_listFile.GetText(nSel, strSourceName);

	if (strSourceName.GetAt(0) != '[')
	{
		//ѡ������ļ�
		CString strDestName;
		CFileDialog dlg(FALSE, L"", L"*.*");   //������һ���ļ��Ի���������
		if (dlg.DoModal() == IDOK)        //�����ļ��Ի���
		{
			//��������ļ��ڱ��ػ��ϴ洢��·��������
			strDestName = dlg.GetPathName();

			//���ú��������ļ�
			if (Download(strSourceName, strDestName))
				AfxMessageBox(_T("���سɹ���"), MB_OK | MB_ICONINFORMATION);
			else
				AfxMessageBox(_T("����ʧ�ܣ�"), MB_OK | MB_ICONSTOP);
		}
		else {
			AfxMessageBox(_T("��д���ļ�����"), MB_OK | MB_ICONSTOP);
		}
	}
	else {
		//ѡ�����Ŀ¼
		AfxMessageBox(_T("��������Ŀ¼!\n����ѡ!"), MB_OK | MB_ICONSTOP);
	}

	//�������ذ�ť
	m_btnDownload.EnableWindow(FALSE);

	//�����ѯ���ϴ���ť
	m_btnUpload.EnableWindow(TRUE);
	m_btnQuery.EnableWindow(TRUE);

	//��������������ı��ͱ༭��ؼ�
	m_editFtp.EnableWindow(TRUE);
	m_editName.EnableWindow(TRUE);
	m_editPwd.EnableWindow(TRUE);
	m_staFtp.EnableWindow(TRUE);
	m_staName.EnableWindow(TRUE);
	m_staPwd.EnableWindow(TRUE);

}


void CFTPDlg::OnUpload()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//��õ�ǰ����
	UpdateData(TRUE);

	//��������������ı���ؼ�
	m_editFtp.EnableWindow(FALSE);            //���������������ı���
	m_editName.EnableWindow(FALSE);          //��¼�ͻ��������ı���
	m_editPwd.EnableWindow(FALSE);            //���������ı���
	m_staFtp.EnableWindow(FALSE);
	m_staName.EnableWindow(FALSE);
	m_staPwd.EnableWindow(FALSE);

	//���ò�ѯ��ť
	m_btnQuery.EnableWindow(FALSE);

	CString strSourceName;
	CString strDestName;
	CFileDialog dlg(TRUE, L"", L"*.*");       //�����ı��Ի���������
	if (dlg.DoModal() == IDOK)
	{
		//��ô��ϴ��ı��ػ��ļ�·�����ļ���
		strSourceName = dlg.GetPathName();
		strDestName = dlg.GetFileName();

		//����Upload�����ϴ��ļ�
		if (Upload(strSourceName, strDestName))
			AfxMessageBox(_T("�ϴ��ɹ���"), MB_OK | MB_ICONINFORMATION);
		else
			AfxMessageBox(_T("�ϴ�ʧ�ܣ�"), MB_OK | MB_ICONSTOP);
	}
	else {
		//�ļ�ѡ���д���
		AfxMessageBox(_T("��ѡ���ļ���"), MB_OK | MB_ICONSTOP);
	}

	//�����ѯ��ť
	m_btnQuery.EnableWindow(TRUE);

	//��������������ı���ؼ�
	m_editFtp.EnableWindow(TRUE);
	m_editName.EnableWindow(TRUE);
	m_editPwd.EnableWindow(TRUE);
	m_staFtp.EnableWindow(TRUE);
	m_staName.EnableWindow(TRUE);
	m_staPwd.EnableWindow(TRUE);

}


void CFTPDlg::OnSelchangeListFile()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	// ��������������ı���ؼ�
	m_editFtp.EnableWindow(FALSE);          //���������������ı���
	m_editName.EnableWindow(FALSE);        //��¼�û��������ı��� 
	m_editPwd.EnableWindow(FALSE);          //���������ı���
	m_staFtp.EnableWindow(FALSE);
	m_staName.EnableWindow(FALSE);
	m_staPwd.EnableWindow(FALSE);

	//���ò�ѯ���ϴ���ť
	m_btnUpload.EnableWindow(FALSE);      //�ϴ���ť
	m_btnQuery.EnableWindow(FALSE);        //��ѯ��ť

										   //�������ذ�ť
	m_btnDownload.EnableWindow(TRUE);

}

BOOL CFTPDlg::Download(CString strSName, CString strDName)
{
	CInternetSession* pSession;      //����Ự�������ָ��
	CFtpConnection* pConnection;    //�������Ӷ������ָ��

	pConnection = NULL;

	//����Internet�Ự����
	pSession = new CInternetSession(AfxGetAppName(), 1,
		PRE_CONFIG_INTERNET_ACCESS);

	try
	{
		//����FTP����
		pConnection = pSession->GetFtpConnection(m_strFtp, m_strName, m_strPwd);
	}
	catch (CInternetException* e)
	{
		//������
		e->Delete();
		pConnection = NULL;
		return FALSE;
	}

	if (pConnection != NULL)
	{
		//�����ļ�
		if (!pConnection->GetFile(strSName, strDName))
		{
			//�����ļ�����
			pConnection->Close();
			delete pConnection;
			delete pSession;
			return FALSE;
		}
	}

	//�������
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

	//����Internet�Ự
	pSession = new CInternetSession(AfxGetAppName(), 1,
		PRE_CONFIG_INTERNET_ACCESS);

	try
	{
		//����FTP����
		pConnection = pSession->GetFtpConnection(m_strFtp,
			m_strName, m_strPwd);
	}
	catch (CInternetException* e)
	{
		//������
		e->Delete();
		pConnection = NULL;
		return FALSE;
	}

	if (pConnection != NULL)
	{
		//�ϴ��ļ�
		if (!pConnection->PutFile(strSName, strDName))
		{
			//�ϴ��ļ�����
			pConnection->Close();
			delete pConnection;
			delete pSession;
			return FALSE;
		}
	}

	//�������
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}
