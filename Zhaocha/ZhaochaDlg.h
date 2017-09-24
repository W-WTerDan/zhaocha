
// ZhaochaDlg.h : ͷ�ļ�
//

#pragma once


// CZhaochaDlg �Ի���
class CZhaochaDlg : public CDialogEx
{
// ����
public:
	CZhaochaDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_ZHAOCHA_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
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
	int mLeftX, mLeftY; // ��һ��ͼƬ���Ͻ�λ�ã�����ڸ����ڣ�
	int mRightX, mRightY; // �ڶ���ͼƬ�����Ͻ�λ�ã�����ڸ����ڣ�
	int mWidth; // ͼƬ���
	int mHeight; // ͼƬ�߶�
	afx_msg void OnClose();
	void Destroy();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	void ClickDifference(CPoint point);
	bool ComparePixel(COLORREF left, COLORREF right);
};
