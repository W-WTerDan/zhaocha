
// ZhaochaDlg.h : 头文件
//

#pragma once


// CZhaochaDlg 对话框
class CZhaochaDlg : public CDialogEx
{
// 构造
public:
	CZhaochaDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_ZHAOCHA_DIALOG };

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
	afx_msg void OnBnClickedGet();
	afx_msg void OnBnClickedBegin();
	HWND hMainWnd;
	HDC hDc, hMemDc;
	HBITMAP hBp;
	int mLeftX, mLeftY; // 第一张图片左上角位置（相对于父窗口）
	int mRightX, mRightY; // 第二张图片的左上角位置（相对于父窗口）
	int mWidth; // 图片宽度
	int mHeight; // 图片高度
	afx_msg void OnClose();
	void Destroy();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	void ClickDifference(CPoint point);
	bool ComparePixel(COLORREF left, COLORREF right);
};
