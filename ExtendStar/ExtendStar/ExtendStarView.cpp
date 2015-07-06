
// ExtendStarView.cpp : implementation of the CExtendStarView class
//

#include "stdafx.h"
#include <math.h>
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "ExtendStar.h"
#endif

#include "ExtendStarDoc.h"
#include "ExtendStarView.h"
#include "DlgStarSetting.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define MOVESTAR 1000

// CExtendStarView

IMPLEMENT_DYNCREATE(CExtendStarView, CView)

BEGIN_MESSAGE_MAP(CExtendStarView, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_COMMAND(ID_SET_STARSETTING, OnStarSetting)
	ON_WM_DESTROY()
	ON_WM_TIMER()
	ON_WM_SIZE()
END_MESSAGE_MAP()

// CExtendStarView construction/destruction

CExtendStarView::CExtendStarView()
{
	m_mapCoordinate.RemoveAll();
}

CExtendStarView::~CExtendStarView()
{
}

BOOL CExtendStarView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CExtendStarView drawing

void CExtendStarView::OnDraw(CDC* pDC)
{
	CExtendStarDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	DrawStar( pDC );

	// TODO: add draw code for native data here
}


// CExtendStarView printing

BOOL CExtendStarView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CExtendStarView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CExtendStarView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

void CExtendStarView::OnStarSetting()
{
	CDlgStarSetting dlg( m_listStar.GetCount(), this );
	if( dlg.DoModal() == IDOK )
	{
		DestoryStar();
		Invalidate();

		InitStar( dlg.GetCount() );
	}
}


// CExtendStarView diagnostics

#ifdef _DEBUG
void CExtendStarView::AssertValid() const
{
	CView::AssertValid();
}

void CExtendStarView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CExtendStarDoc* CExtendStarView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CExtendStarDoc)));
	return (CExtendStarDoc*)m_pDocument;
}

void CExtendStarView::InitStar(const int& nCount)
{
	MakeStar( nCount );

	SetTimer( MOVESTAR, 50, NULL );
}

void CExtendStarView::DestoryStar()
{
	KillTimer( MOVESTAR );

	DeleteStar();
	DeleteCoordinate();
}

void CExtendStarView::DrawStar(CDC* pDC)
{
	if( pDC )
	{
		POSITION pos = m_listStar.GetHeadPosition();
		while( pos )
		{
			CStar* pStar = m_listStar.GetNext( pos );
			if( pStar ) pStar->Draw( pDC );
		}
	}
}

#endif //_DEBUG


// CExtendStarView message handlers


void CExtendStarView::OnInitialUpdate()
{
	CView::OnInitialUpdate();

	InitStar( 30 );
}

void CExtendStarView::OnDestroy()
{
	DestoryStar();

	CView::OnDestroy();
}

void CExtendStarView::OnTimer(UINT_PTR nIDEvent)
{
	switch( nIDEvent )
	{
		case MOVESTAR :
			{
				CClientDC dc( this );
				CRect rc; GetClientRect( &rc );
				POSITION pos = m_listStar.GetHeadPosition();
				while( pos )
				{
					CStar* pStar = m_listStar.GetNext( pos );
					if( pStar )
					{
						BumpCheck( pStar );
						DeleteCoordinate( pStar );

						pStar->Move( &dc, &m_rgnStar, rc );
						pStar->Invalidate( GetSafeHwnd() );

						SetCoordinate( pStar );
					}
				}
			}
			break;
	}

	CView::OnTimer(nIDEvent);
}

void CExtendStarView::DeleteStar()
{
	POSITION pos = m_listStar.GetHeadPosition();
	while( pos )
	{
		CStar* pStar = m_listStar.GetNext( pos );
		if( pStar ) delete pStar;
	}
	m_listStar.RemoveAll();
}

void CExtendStarView::DeleteCoordinate()
{
	POSITION pos = m_mapCoordinate.GetStartPosition();
	while( pos )
	{
		WORD wKey = 0; CPtrArray* pArrStar = NULL;
		m_mapCoordinate.GetNextAssoc( pos, wKey, (void*&)pArrStar );
		if( pArrStar )
		{
			pArrStar->RemoveAll();
			delete pArrStar;
		}
		pArrStar = NULL;
	}
	m_mapCoordinate.RemoveAll();
}

void CExtendStarView::DeleteCoordinate(CStar* pMovingStar)
{
	if( pMovingStar )
	{
		CPtrArray* pArrStar = NULL;
		WORD wKey = pMovingStar->GetPlace();
		if( m_mapCoordinate.Lookup( wKey, (void*&)pArrStar ) )
		{
			int nCount = pArrStar->GetCount();
			for( int i = 0; i < nCount; i++ )
			{
				CStar* pStar = (CStar*)pArrStar->GetAt( i );
				if( pMovingStar == pStar )
				{
					pArrStar->RemoveAt( i );
					break;
				}
			}
		}
	}
}

void CExtendStarView::SetCoordinate(CStar* pStar)
{
	if( pStar )
	{
		CPtrArray* pArrStar = NULL;
		WORD wKey = pStar->GetPlace();
		if( !m_mapCoordinate.Lookup( wKey, (void*&)pArrStar) )
		{
			pArrStar = new CPtrArray;
			m_mapCoordinate.SetAt( wKey, pArrStar );
		}
		pArrStar->Add( pStar );
	}
}

void CExtendStarView::MakeStar(const int& nCount)
{
	CRect rc;
	GetClientRect( &rc );

	for( int i = 0; i < nCount; i++ )
	{
		CStar* pStar = new CStar( rc );
		m_listStar.AddTail( pStar );
		SetCoordinate( pStar );
	}
}

void CExtendStarView::BumpCheck(CStar* pMovingStar)
{
	if( pMovingStar )
	{
		CPtrArray* pArrStar = NULL;
		WORD wKey = pMovingStar->GetPlace();
		if( m_mapCoordinate.Lookup( wKey, (void*&)pArrStar ) )
		{
			int nCount = pArrStar->GetCount();
			for( int i = 0; i < nCount; i++ )
			{
				CStar* pStar = (CStar*)pArrStar->GetAt( i );
				if( pMovingStar != pStar ) pMovingStar->Bump( pStar );
			}
		}
	}
}

void CExtendStarView::OnSize(UINT nType, int cx, int cy)
{
	CRect rc;
	GetClientRect( &rc );

	POSITION pos = m_listStar.GetHeadPosition();
	while( pos )
	{
		CStar* pStar = m_listStar.GetNext( pos );
		if( pStar )
		{
			pStar->Size( rc );
			DeleteCoordinate( pStar );
			SetCoordinate( pStar );
		}
	}

	CView::OnSize(nType, cx, cy);
}

