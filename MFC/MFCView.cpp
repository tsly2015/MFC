
// MFCView.cpp : implementation of the CMFCView class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "MFC.h"
#endif

#include "MFCDoc.h"
#include "MFCView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMFCView

IMPLEMENT_DYNCREATE(CMFCView, CView)

BEGIN_MESSAGE_MAP(CMFCView, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_CREATE()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
END_MESSAGE_MAP()

// CMFCView construction/destruction

CMFCView::CMFCView()
{
	// TODO: add construction code here
	m_ptOrigin = 0;
	m_ptOld = 0;
	m_bDraw = FALSE;
}

CMFCView::~CMFCView()
{
}

BOOL CMFCView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CMFCView drawing

void CMFCView::OnDraw(CDC* /*pDC*/)
{
	CMFCDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: add draw code for native data here
}


// CMFCView printing

BOOL CMFCView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CMFCView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CMFCView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}


// CMFCView diagnostics

#ifdef _DEBUG
void CMFCView::AssertValid() const
{
	CView::AssertValid();
}

void CMFCView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMFCDoc* CMFCView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMFCDoc)));
	return (CMFCDoc*)m_pDocument;
}
#endif //_DEBUG


// CMFCView message handlers


int CMFCView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  Add your specialized creation code here
	m_btn.Create(L"Text", WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON, CRect(100, 0, 150, 50), this, 123); //this -> GetParent() 

	return 0;
}


void CMFCView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	// MessageBox(L"View Clicked");
	m_ptOrigin = m_ptOld = point;
	m_bDraw = TRUE;

	CView::OnLButtonDown(nFlags, point);
}


void CMFCView::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	//HDC hdc;
	//hdc = ::GetDC(m_hWnd);
	//MoveToEx(hdc, m_ptOrigin.x, m_ptOrigin.y, NULL);
	//LineTo(hdc, point.x, point.y);
	//::ReleaseDC(m_hWnd, hdc);

	//CDC *pDC = GetDC();
	//pDC->MoveTo(m_ptOrigin);
	//pDC->LineTo(point);
	//ReleaseDC(pDC);

	//CClientDC dc(this); //GetParent()
	//dc.MoveTo(m_ptOrigin);
	//dc.LineTo(point);

	//CWindowDC dc(this); //GetParent(), GetDesktopWindow()
	//dc.MoveTo(m_ptOrigin);
	//dc.LineTo(point);

	//CPen pen(PS_SOLID, 1, RGB(255, 0, 0));
	//CClientDC dc(this);
	//CPen *pOldPen = dc.SelectObject(&pen);
	//dc.MoveTo(m_ptOrigin);
	//dc.LineTo(point);
	//dc.SelectObject(pOldPen);

	//CBrush brush(RGB(255, 0, 0));
	//CClientDC dc(this);
	//dc.FillRect(CRect(m_ptOrigin, point), &brush);

	//CBitmap bitmap;
	//bitmap.LoadBitmapW(IDB_BITMAP1);
	//CBrush brush(&bitmap);
	//CClientDC dc(this);
	//dc.FillRect(CRect(m_ptOrigin,point), &brush);

	//CClientDC dc(this);
	//CBrush* pBrush = CBrush::FromHandle((HBRUSH)GetStockObject(NULL_BRUSH));
	//CBrush* pOldBrush = dc.SelectObject(pBrush);
	//dc.Rectangle(CRect(m_ptOrigin, point));
	//dc.SelectObject(pOldBrush);

	m_bDraw = FALSE;

	CView::OnLButtonUp(nFlags, point);
}


void CMFCView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	CClientDC dc(this);
	CPen pen(PS_SOLID, 1, RGB(255, 0, 0));
	CPen* pOldPen = dc.SelectObject(&pen);
	if (m_bDraw == TRUE)
	{
		//dc.SetROP2(R2_BLACK);
		dc.MoveTo(m_ptOrigin);
		//dc.LineTo(point);
		dc.LineTo(m_ptOld);
		dc.MoveTo(m_ptOld); //dc.MoveTo(m_ptOrigin);
		dc.LineTo(point);
		//m_ptOrigin = point;
		m_ptOld = point;
	}
	dc.SelectObject(pOldPen);
	CView::OnMouseMove(nFlags, point);
}
