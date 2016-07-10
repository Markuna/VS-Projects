
// 计算器Dlg.cpp : 实现文件
//

#include "stdafx.h"
#include "计算器.h"
#include "计算器Dlg.h"
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


// C计算器Dlg 对话框



C计算器Dlg::C计算器Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_MY_DIALOG, pParent)
	, m_value(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void C计算器Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_value);
}

BEGIN_MESSAGE_MAP(C计算器Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &C计算器Dlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON9, &C计算器Dlg::OnBnClickedButton9)
	ON_BN_CLICKED(IDC_BUTTON8, &C计算器Dlg::OnBnClickedButton8)
	ON_BN_CLICKED(IDC_BUTTON2, &C计算器Dlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &C计算器Dlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &C计算器Dlg::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON7, &C计算器Dlg::OnBnClickedButton7)
	ON_BN_CLICKED(IDC_BUTTON5, &C计算器Dlg::OnBnClickedButton5)
	ON_BN_CLICKED(IDC_BUTTON6, &C计算器Dlg::OnBnClickedButton6)
	ON_BN_CLICKED(IDC_BUTTON10, &C计算器Dlg::OnBnClickedButton10)
	ON_BN_CLICKED(IDC_BUTTON19, &C计算器Dlg::OnBnClickedButton19)
	ON_BN_CLICKED(IDC_BUTTON14, &C计算器Dlg::OnBnClickedButton14)
	ON_BN_CLICKED(IDC_BUTTON17, &C计算器Dlg::OnBnClickedButton17)
	ON_BN_CLICKED(IDC_BUTTON15, &C计算器Dlg::OnBnClickedButton15)
	ON_BN_CLICKED(IDC_BUTTON16, &C计算器Dlg::OnBnClickedButton16)
	ON_BN_CLICKED(IDC_BUTTON18, &C计算器Dlg::OnBnClickedButton18)
	ON_BN_CLICKED(IDC_BUTTON11, &C计算器Dlg::OnBnClickedButton11)
	ON_BN_CLICKED(IDC_BUTTON13, &C计算器Dlg::OnBnClickedButton13)
	ON_BN_CLICKED(IDC_BUTTON12, &C计算器Dlg::OnBnClickedButton12)
END_MESSAGE_MAP()


// C计算器Dlg 消息处理程序

BOOL C计算器Dlg::OnInitDialog()
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

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void C计算器Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void C计算器Dlg::OnPaint()
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
HCURSOR C计算器Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

//键入数字
int num;
//存储全局数
int i = 0;
int i2 = 0;//再次键入数字是清零用判断
int i3 = 0;//运算数字对应    + -> 1        - -> 2        * -> 3          / -> 4
int i4 = 0;//实现不同运算符交替按
int firstnum;//	全局上一个存贮数字
int click = 0;//重复点击>2，重复运算等于

void doubleclick();

//运算判断清零用
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

// 数字键 1
void C计算器Dlg::OnBnClickedButton1()
{
	UpdateData(true);
	num = _wtol(m_value);
	checknumi();
	num = 10 * num + 1;
	m_value.Format(_T("%d"), num);
	UpdateData(false);
}

// 数字键 2
void C计算器Dlg::OnBnClickedButton9()
{
	UpdateData(true);
	num = _wtol(m_value);
	checknumi();
	num = 10 * num + 2;
	m_value.Format(_T("%d"), num);
	UpdateData(false);
}

// 数字键 3
void C计算器Dlg::OnBnClickedButton8()
{
	UpdateData(true);
	num = _wtol(m_value);
	checknumi();
	num = 10 * num + 3;
	m_value.Format(_T("%d"), num);
	UpdateData(false);
}

// 数字键 4
void C计算器Dlg::OnBnClickedButton2()
{
	UpdateData(true);
	num = _wtol(m_value);
	checknumi();
	num = 10 * num + 4;
	m_value.Format(_T("%d"), num);
	UpdateData(false);
}

// 数字键 5
void C计算器Dlg::OnBnClickedButton3()
{
	UpdateData(true);
	num = _wtol(m_value);
	checknumi();
	num = 10 * num + 5;
	m_value.Format(_T("%d"), num);
	UpdateData(false);
}

// 数字键 6
void C计算器Dlg::OnBnClickedButton4()
{
	UpdateData(true);
	num = _wtol(m_value);
	checknumi();
	num = 10 * num + 6;
	m_value.Format(_T("%d"), num);
	UpdateData(false);
}

// 数字键 7
void C计算器Dlg::OnBnClickedButton7()
{
	UpdateData(true);
	num = _wtol(m_value);
	checknumi();
	num = 10 * num + 7;
	m_value.Format(_T("%d"), num);
	UpdateData(false);
}

// 数字键 8
void C计算器Dlg::OnBnClickedButton5()
{
	UpdateData(true);
	num = _wtol(m_value);
	checknumi();
	num = 10 * num + 8;
	m_value.Format(_T("%d"), num);
	UpdateData(false);
}

// 数字键 9
void C计算器Dlg::OnBnClickedButton6()
{
	UpdateData(true);
	num = _wtol(m_value);
	checknumi();
	num = 10 * num + 9;
	m_value.Format(_T("%d"), num);
	UpdateData(false);
}

// 数字键 0
void C计算器Dlg::OnBnClickedButton10()
{
	UpdateData(true);
	num = _wtol(m_value);
	checknumi();
	num = 10 * num + 0;
	m_value.Format(_T("%d"), num);
	UpdateData(false);
}

// 删除 Del
void C计算器Dlg::OnBnClickedButton19()
{

	UpdateData(true);
	num = _wtol(m_value);
	num = num / 10;
	m_value.Format(_T("%d"), num);
	UpdateData(false);
}

// 置零按钮 C
void C计算器Dlg::OnBnClickedButton14()
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


//置零当前按钮 CE
void C计算器Dlg::OnBnClickedButton13()
{
	UpdateData(true);
	num = 0;
	m_value.Format(_T("%d"), num);
	UpdateData(false);
}


//加法运算
void C计算器Dlg::OnBnClickedButton15()
{
	UpdateData(true);
	if (i == 0)//第一次按下
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
	i = 1;//表示不是第一次按
	i2 = 1;
	UpdateData(false);
}

//减法运算
void C计算器Dlg::OnBnClickedButton16()
{
	UpdateData(true);
	if (i == 0)//第一次按下
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
	i = 1;//表示不是第一次按
	i2 = 1;
	UpdateData(false);
}

// 乘法运算
void C计算器Dlg::OnBnClickedButton17()
{
	UpdateData(true);
	if (i == 0)//第一次按下
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
	i = 1;//表示不是第一次按
	i2 = 1;
	UpdateData(false);
}

//除法运算
void C计算器Dlg::OnBnClickedButton18()
{
	UpdateData(true);
	if (i == 0)//第一次按下
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
	i = 1;//表示不是第一次按
	i2 = 1;
	UpdateData(false);
}

//等于运算
void C计算器Dlg::OnBnClickedButton11()
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



//正负号添加
void C计算器Dlg::OnBnClickedButton12()
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
		//C计算器Dlg::OnBnClickedButton11();
	}
}