
// ������Dlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "������.h"
#include "������Dlg.h"
#include "afxdialogex.h"


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


// C������Dlg �Ի���



C������Dlg::C������Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_MY_DIALOG, pParent)
	, m_value(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void C������Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_value);
}

BEGIN_MESSAGE_MAP(C������Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &C������Dlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON9, &C������Dlg::OnBnClickedButton9)
	ON_BN_CLICKED(IDC_BUTTON8, &C������Dlg::OnBnClickedButton8)
	ON_BN_CLICKED(IDC_BUTTON2, &C������Dlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &C������Dlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &C������Dlg::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON7, &C������Dlg::OnBnClickedButton7)
	ON_BN_CLICKED(IDC_BUTTON5, &C������Dlg::OnBnClickedButton5)
	ON_BN_CLICKED(IDC_BUTTON6, &C������Dlg::OnBnClickedButton6)
	ON_BN_CLICKED(IDC_BUTTON10, &C������Dlg::OnBnClickedButton10)
	ON_BN_CLICKED(IDC_BUTTON19, &C������Dlg::OnBnClickedButton19)
	ON_BN_CLICKED(IDC_BUTTON14, &C������Dlg::OnBnClickedButton14)
	ON_BN_CLICKED(IDC_BUTTON17, &C������Dlg::OnBnClickedButton17)
	ON_BN_CLICKED(IDC_BUTTON15, &C������Dlg::OnBnClickedButton15)
	ON_BN_CLICKED(IDC_BUTTON16, &C������Dlg::OnBnClickedButton16)
	ON_BN_CLICKED(IDC_BUTTON18, &C������Dlg::OnBnClickedButton18)
	ON_BN_CLICKED(IDC_BUTTON11, &C������Dlg::OnBnClickedButton11)
	ON_BN_CLICKED(IDC_BUTTON13, &C������Dlg::OnBnClickedButton13)
	ON_BN_CLICKED(IDC_BUTTON12, &C������Dlg::OnBnClickedButton12)
END_MESSAGE_MAP()


// C������Dlg ��Ϣ�������

BOOL C������Dlg::OnInitDialog()
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

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void C������Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void C������Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

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

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR C������Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

//��������
int num;
//�洢ȫ����
int i = 0;
int i2 = 0;//�ٴμ����������������ж�
int i3 = 0;//�������ֶ�Ӧ    + -> 1        - -> 2        * -> 3          / -> 4
int i4 = 0;//ʵ�ֲ�ͬ��������水
int firstnum;//	ȫ����һ����������
int click = 0;//�ظ����>2���ظ��������

void doubleclick();

//�����ж�������
void checknumi()
{
	if (i2 == 1)
	{
		firstnum = num;
		num = 0;
	}
	i2 = 0;
	i4 = 0;
}

// ���ּ� 1
void C������Dlg::OnBnClickedButton1()
{
	UpdateData(true);
	num = _wtol(m_value);
	checknumi();
	num = 10 * num + 1;
	m_value.Format(_T("%d"), num);
	UpdateData(false);
}

// ���ּ� 2
void C������Dlg::OnBnClickedButton9()
{
	UpdateData(true);
	num = _wtol(m_value);
	checknumi();
	num = 10 * num + 2;
	m_value.Format(_T("%d"), num);
	UpdateData(false);
}

// ���ּ� 3
void C������Dlg::OnBnClickedButton8()
{
	UpdateData(true);
	num = _wtol(m_value);
	checknumi();
	num = 10 * num + 3;
	m_value.Format(_T("%d"), num);
	UpdateData(false);
}

// ���ּ� 4
void C������Dlg::OnBnClickedButton2()
{
	UpdateData(true);
	num = _wtol(m_value);
	checknumi();
	num = 10 * num + 4;
	m_value.Format(_T("%d"), num);
	UpdateData(false);
}

// ���ּ� 5
void C������Dlg::OnBnClickedButton3()
{
	UpdateData(true);
	num = _wtol(m_value);
	checknumi();
	num = 10 * num + 5;
	m_value.Format(_T("%d"), num);
	UpdateData(false);
}

// ���ּ� 6
void C������Dlg::OnBnClickedButton4()
{
	UpdateData(true);
	num = _wtol(m_value);
	checknumi();
	num = 10 * num + 6;
	m_value.Format(_T("%d"), num);
	UpdateData(false);
}

// ���ּ� 7
void C������Dlg::OnBnClickedButton7()
{
	UpdateData(true);
	num = _wtol(m_value);
	checknumi();
	num = 10 * num + 7;
	m_value.Format(_T("%d"), num);
	UpdateData(false);
}

// ���ּ� 8
void C������Dlg::OnBnClickedButton5()
{
	UpdateData(true);
	num = _wtol(m_value);
	checknumi();
	num = 10 * num + 8;
	m_value.Format(_T("%d"), num);
	UpdateData(false);
}

// ���ּ� 9
void C������Dlg::OnBnClickedButton6()
{
	UpdateData(true);
	num = _wtol(m_value);
	checknumi();
	num = 10 * num + 9;
	m_value.Format(_T("%d"), num);
	UpdateData(false);
}

// ���ּ� 0
void C������Dlg::OnBnClickedButton10()
{
	UpdateData(true);
	num = _wtol(m_value);
	checknumi();
	num = 10 * num + 0;
	m_value.Format(_T("%d"), num);
	UpdateData(false);
}

// ɾ�� Del
void C������Dlg::OnBnClickedButton19()
{

	UpdateData(true);
	num = _wtol(m_value);
	num = num / 10;
	m_value.Format(_T("%d"), num);
	UpdateData(false);
}

// ���㰴ť C
void C������Dlg::OnBnClickedButton14()
{

	UpdateData(true);
	num = 0;
	i = 0;
	i2 = 0;
	i3 = 0;
	i4 = 0;
	firstnum = 0;
	m_value.Format(_T("%d"), num);
	UpdateData(false);
}


//���㵱ǰ��ť CE
void C������Dlg::OnBnClickedButton13()
{
	UpdateData(true);
	num = 0;
	m_value.Format(_T("%d"), num);
	UpdateData(false);
}


//�ӷ�����
void C������Dlg::OnBnClickedButton15()
{
	UpdateData(true);
	if (i == 0)//��һ�ΰ���
	{
		i3 = 1;
	}
	else
	{
		if (i4 == 0)
		{
			switch (i3)
			{
			case 1:
				firstnum = firstnum + num;
				break;
			case 2:
				firstnum = firstnum - num;
				i3 = 1;
				break;
			case 3:
				firstnum = firstnum*num;
				i3 = 1;
				break;
			case 4:
				firstnum = firstnum / num;
				i3 = 1;
				break;
			case 0:
				break;
			default:
				break;
			}
			m_value.Format(_T("%d"), firstnum);
			i4 = 1;
	   }
		else
		{
			i3 = 1;
		}

	}
	i = 1;//��ʾ���ǵ�һ�ΰ�
	i2 = 1;
	UpdateData(false);
}

//��������
void C������Dlg::OnBnClickedButton16()
{
	UpdateData(true);
	if (i == 0)//��һ�ΰ���
	{
		i3 = 2;
	}
	else
	{
		if (i4 == 0)
		{
			switch (i3)
			{
			case 1:
				firstnum = firstnum + num;
				i3 = 2;
				break;
			case 2:
				firstnum = firstnum - num;
				break;
			case 3:
				firstnum = firstnum*num;
				i3 = 2;
				break;
			case 4:
				firstnum = firstnum / num;
				i3 = 2;
				break;
			case 0:
				break;
			default:
				break;
			}
			m_value.Format(_T("%d"), firstnum);
			i4 = 1;
		}
		else
		{
			i3 = 2;
		}
	}
	i = 1;//��ʾ���ǵ�һ�ΰ�
	i2 = 1;
	UpdateData(false);
}

// �˷�����
void C������Dlg::OnBnClickedButton17()
{
	UpdateData(true);
	if (i == 0)//��һ�ΰ���
	{
		i3 = 3;
	}
	else
	{
		if (i4 == 0)
		{
			switch (i3)
			{
			case 1:
				firstnum = firstnum + num;
				i3 = 3;
				break;
			case 2:
				firstnum = firstnum - num;
				i3 = 3;
				break;
			case 3:
				firstnum = firstnum*num;
				break;
			case 4:
				firstnum = firstnum / num;
				i3 = 3;
				break;
			case 0:
				break;
			default:
				break;
			}
			m_value.Format(_T("%d"), firstnum);
			i4 = 1;
		}
		else
		{
			i3 = 3;
		}
	}
	i = 1;//��ʾ���ǵ�һ�ΰ�
	i2 = 1;
	UpdateData(false);
}

//��������
void C������Dlg::OnBnClickedButton18()
{
	UpdateData(true);
	if (i == 0)//��һ�ΰ���
	{
		i3 = 4;
	}
	else
	{
		if (i4 == 0)
		{
			switch (i3)
			{
			case 1:
				firstnum = firstnum + num;
				i3 = 4;
				break;
			case 2:
				firstnum = firstnum - num;
				i3 = 4;
				break;
			case 3:
				firstnum = firstnum*num;
				i3 = 4;
				break;
			case 4:
				firstnum = firstnum / num;
				break;
			case 0:
				break;
			default:
				break;
			}
			m_value.Format(_T("%d"), firstnum);
			i4 = 1;
		}
		else
		{
			i3 = 4;
		}
	}
	i = 1;//��ʾ���ǵ�һ�ΰ�
	i2 = 1;
	UpdateData(false);
}

//��������
void C������Dlg::OnBnClickedButton11()
{
	UpdateData(true);
	switch (i3)
	{
	case 1:
		firstnum = firstnum + num;
		break;
	case 2:
		firstnum = firstnum - num;
		break;
	case 3:
		firstnum = firstnum*num;
		break;
	case 4:
		firstnum = firstnum / num;
		break;
	case 0:
		break;
	default:
		break;
	}
	m_value.Format(_T("%d"), firstnum);
	i = 0;//
	i2 = 1;
	i4 = 1;
	UpdateData(false);
}



//���������
void C������Dlg::OnBnClickedButton12()
{
	UpdateData(true);
	num = _wtol(m_value);
	checknumi();
	num = 0 - num;
	m_value.Format(_T("%d"), num);
	UpdateData(false);
}

void doubleclick()
{
	if (click>2)
	{
		//C������Dlg::OnBnClickedButton11();
	}
}