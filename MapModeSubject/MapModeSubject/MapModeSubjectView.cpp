
// MapModeSubjectView.cpp : implementation of the CMapModeSubjectView class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "MapModeSubject.h"
#endif

#include "MapModeSubjectDoc.h"
#include "MapModeSubjectView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMapModeSubjectView

IMPLEMENT_DYNCREATE(CMapModeSubjectView, CView)

BEGIN_MESSAGE_MAP(CMapModeSubjectView, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_SIZE()
END_MESSAGE_MAP()

// CMapModeSubjectView construction/destruction

CMapModeSubjectView::CMapModeSubjectView()
{
	// TODO: add construction code here
}

CMapModeSubjectView::~CMapModeSubjectView()
{
}

BOOL CMapModeSubjectView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CMapModeSubjectView drawing

void CMapModeSubjectView::OnDraw(CDC* pDC)
{
	CMapModeSubjectDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	DrawFigure( pDC );
}


// CMapModeSubjectView printing

BOOL CMapModeSubjectView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CMapModeSubjectView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CMapModeSubjectView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}


// CMapModeSubjectView diagnostics

#ifdef _DEBUG
void CMapModeSubjectView::AssertValid() const
{
	CView::AssertValid();
}

void CMapModeSubjectView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMapModeSubjectDoc* CMapModeSubjectView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMapModeSubjectDoc)));
	return (CMapModeSubjectDoc*)m_pDocument;
}
#endif //_DEBUG

void CMapModeSubjectView::DrawFigure(CDC* pDC)
{
	if( pDC )
	{
		CRect rc; GetClientRect( &rc );
		//pDC->SetMapMode( MM_ISOTROPIC );
		pDC->SetMapMode( MM_ANISOTROPIC );
		pDC->SetWindowExt( m_rc.Width(), m_rc.Height() );
		pDC->SetViewportExt( rc.Width(), rc.Height() );

		rc = CRect( 100, 100, 300, 300 );
		pDC->Rectangle( &rc );

		rc = CRect( 300, 300, 500, 500 );
		pDC->Ellipse( &rc );

		pDC->MoveTo( 400, 100 );
		pDC->LineTo( 600, 100 );
		pDC->LineTo( 500, 300 );
		pDC->LineTo( 400, 100 );
	}
}


// CMapModeSubjectView message handlers


void CMapModeSubjectView::OnSize(UINT nType, int cx, int cy)
{
	CClientDC dc( this );

	Invalidate();

	//CView::OnSize(nType, cx, cy);
}



void CMapModeSubjectView::OnInitialUpdate()
{
	CView::OnInitialUpdate();

	GetClientRect( &m_rc );
}

