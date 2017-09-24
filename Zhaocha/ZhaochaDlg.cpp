
// ZhaochaDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Zhaocha.h"
#include "ZhaochaDlg.h"
#include "afxdialogex.h"

#include <Windows.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框



// CZhaochaDlg 对话框



CZhaochaDlg::CZhaochaDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CZhaochaDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CZhaochaDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CZhaochaDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_GET, &CZhaochaDlg::OnBnClickedGet)
	ON_BN_CLICKED(IDC_GET, &CZhaochaDlg::OnBnClickedGet)
//	ON_WM_LBUTTONDBLCLK()
	ON_BN_CLICKED(IDC_BEGIN, &CZhaochaDlg::OnBnClickedBegin)
	ON_WM_CLOSE()
//	ON_WM_RBUTTONUP()
	ON_WM_RBUTTONDOWN()
	ON_WM_LBUTTONDBLCLK()
END_MESSAGE_MAP()


// CZhaochaDlg 消息处理程序

BOOL CZhaochaDlg::OnInitDialog()
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

	// TODO:  在此添加额外的初始化代码
	hMainWnd = NULL;
	GetDlgItem(IDC_GET)->EnableWindow(FALSE);
	mLeftX = 6;
	mLeftY = 200;
	mRightX = 515;
	mRightY = 200;
	mWidth = 502;
	mHeight = 450;
	CString setStr;
	setStr.Format(_T("%d"), mLeftX);
	SetDlgItemText(IDC_LEFTX, setStr);
	setStr.Format(_T("%d"), mLeftY);
	SetDlgItemText(IDC_LEFTY, setStr);
	setStr.Format(_T("%d"), mRightX);
	SetDlgItemText(IDC_RIGHTX, setStr);
	setStr.Format(_T("%d"), mRightY);
	SetDlgItemText(IDC_RIGHTY, setStr);
	setStr.Format(_T("%d"), mWidth);
	SetDlgItemText(IDC_WIDTH, setStr);
	setStr.Format(_T("%d"), mHeight);
	SetDlgItemText(IDC_HEIGHT, setStr);
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CZhaochaDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CZhaochaDlg::OnPaint()
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
HCURSOR CZhaochaDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

bool CZhaochaDlg::ComparePixel(COLORREF left, COLORREF right) {
	long value = ((left & 0xFF) >> 4) - ((right & 0xFF) >> 4);
	bool low = abs(value) <= 1;
	value = ((left & 0xFF00) >> 12) - ((right & 0xFF00) >> 12);
	bool middle = abs(value) <= 1;
	value = ((left & 0xFF0000) >> 20) - ((right & 0xFF0000) >> 20);
	bool high = abs(value) <= 1;
	return low && middle && high;
}

void CZhaochaDlg::OnBnClickedGet()
{
	// TODO:  在此添加控件通知处理程序代码

	int delta = mRightX - mLeftX;
	
	BitBlt(hMemDc, 0, 0, delta * 2, mHeight, hDc, mLeftX, mLeftY, SRCCOPY);

	for (int i = 0; i < mWidth; i++) {
		for (int j = 0; j < mHeight; j++) {
			COLORREF left = GetPixel(hMemDc, i, j);
			COLORREF right = GetPixel(hMemDc, i + delta, j);
			bool isEqual = ComparePixel(left, right);
			if (!isEqual)
			{
				SetPixel(hMemDc, i, j, 0x00FF);
			}
		}
	}
	
	CWnd *pWnd = GetDlgItem(IDC_STATIC);
	CDC *pOutDC = pWnd->GetDC();
	BitBlt(pOutDC->m_hDC, 0, 0, mWidth, mHeight, hMemDc, 0, 0, SRCCOPY);
	ReleaseDC(pOutDC);
	return;

}


void CZhaochaDlg::OnBnClickedBegin()
{
	// TODO:  在此添加控件通知处理程序代码
	if (hMainWnd == NULL || hDc == NULL)
		Destroy();
	if ((hMainWnd = ::FindWindow(NULL, L"大家来找茬")) == NULL) { //
		//
		hMainWnd = NULL;
		goto error;
	}
	//GetDC && GetWindowDC
	if ((hDc = ::GetDC(hMainWnd)) == NULL) {
		goto error;
	}
	{
		CString tmp;
		GetDlgItemText(IDC_LEFTX, tmp);
		mLeftX = _ttoi(tmp);
		GetDlgItemText(IDC_LEFTY, tmp);
		mLeftY = _ttoi(tmp);
		GetDlgItemText(IDC_RIGHTX, tmp);
		mRightX = _ttoi(tmp);
		GetDlgItemText(IDC_RIGHTY, tmp);
		mRightY = _ttoi(tmp);
		GetDlgItemText(IDC_WIDTH, tmp);
		mWidth = _ttoi(tmp);
		GetDlgItemText(IDC_HEIGHT, tmp);
		mHeight = _ttoi(tmp);
		if (mLeftX >= mRightX || mHeight <= 0 || mWidth <= 0)
		{
			goto error_paramters;
		}
		if (mLeftY != mRightY)
		{
			tmp.Format(_T("%d"), mLeftY);
			SetDlgItemText(IDC_RIGHTY, tmp);
		}
	}
	if ((hMemDc = CreateCompatibleDC(hDc)) == NULL) {
		goto error;
	}

	if ((hBp = CreateCompatibleBitmap(hDc, (mRightX - mLeftX) * 2, mHeight)) == NULL) {
		goto error;
	}

	if (SelectObject(hMemDc, hBp) == NULL) {
		goto error;
	}

	GetDlgItem(IDC_GET)->EnableWindow();
	return;
error:
	MessageBox(TEXT("请先打开游戏!"));
	return;
error_paramters:
	MessageBox(TEXT("参数有误，请重新输入!"));

}


void CZhaochaDlg::OnClose()
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值
	Destroy();
	CDialogEx::OnClose();
}


void CZhaochaDlg::Destroy()
{
	if (hBp)	DeleteObject(hBp);
	if (hMemDc)	DeleteDC(hMemDc);
	if (hDc)
		::ReleaseDC(NULL, hDc);
}


BOOL CZhaochaDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO:  在此添加专用代码和/或调用基类
	if (pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_ESCAPE) return TRUE;
	return CDialogEx::PreTranslateMessage(pMsg);
}


void CZhaochaDlg::ClickDifference(CPoint point)
{
	int x, y;
	x = point.x - 13;
	y = point.y - 13;

	DWORD lParam = ((y + mLeftY) << 16) + x + mLeftX;
	::SendMessage(hMainWnd, WM_LBUTTONDOWN, MK_LBUTTON, lParam);
	::SendMessage(hMainWnd, WM_LBUTTONUP, MK_LBUTTON, lParam);

	// 另外一种方式实现点击
	/*RECT rect = { 0 };
	::GetWindowRect(hMainWnd, &rect);
	x = rect.left + point.x - 13 + mLeftX;
	if (x < 0) x += 510;
	y = rect.top + point.y - 13 + mLeftY;

	POINT prevP;
	GetCursorPos(&prevP);
	SetCursorPos(x, y);
	Sleep(100);
	mouse_event(MOUSEEVENTF_ABSOLUTE | MOUSEEVENTF_LEFTDOWN, x, y, 0, GetMessageExtraInfo());
	mouse_event(MOUSEEVENTF_ABSOLUTE | MOUSEEVENTF_LEFTUP, x, y, 0, GetMessageExtraInfo());
	SetCursorPos(prevP.x, prevP.y);*/
}

void CZhaochaDlg::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值
	ClickDifference(point);
	CDialogEx::OnRButtonDown(nFlags, point);
}


void CZhaochaDlg::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值

	ClickDifference(point);
	CDialogEx::OnLButtonDblClk(nFlags, point);
}

