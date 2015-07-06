#include "StdAfx.h"
#include "math.h"
#include "time.h"
#include "Star.h"

CStar::CStar(const CRect& rcClient)
{
	//srand(time(NULL));

	m_nSTEPX = STEP;
	m_nSTEPY = STEP;

	int nR = rand() % 255;
	int nG = rand() % 255;
	int nB = rand() % 255;
	m_clrRgn = RGB( nR, nG, nB );

	//m_nOuterSize = (rand() % 30) + 15;
	//m_nInnerSize = (rand() % 10) + 5;
	m_nOuterSize = 25;
	m_nInnerSize = 14;

	m_nPlace = -1;

	Init( rcClient );
	InitCoordinate( rcClient );
}

CStar::~CStar()
{
}

void CStar::Init(const CRect& rcClient)
{
	MakePt();

	m_nX = rand() % (rcClient.Width() - m_nOuterSize);
	m_nY = rand() % (rcClient.Height() - m_nOuterSize);
}

void CStar::MakePt()
{
	const int nRotate = 60;
	const double PI = 3.14159265358979323846;

	for( int i = 0; i < STARPTCOUNT - 1; i+=2 )
	{
		double dcos = cos( (double)(i * nRotate * PI) / 360.0);
		double dsin = sin( (double)(i * nRotate * PI) / 360.0);

		m_ptStar[i].x = (long)( m_nOuterSize * cos( (double)(i * nRotate * PI) / 360.0) );
		m_ptStar[i].y = (long)( m_nOuterSize * sin( (double)(i * nRotate * PI) / 360.0) );

		m_ptStar[i+1].x = (long)( m_nInnerSize * cos( (double)((i+1) * nRotate * PI) / 360.0) );
		m_ptStar[i+1].y = (long)( m_nInnerSize * sin( (double)((i+1) * nRotate * PI) / 360.0) );
	}
	m_ptStar[ STARPTCOUNT-1 ] = m_ptStar[ 0 ];
}

void CStar::Make(CRgn* pRgn)
{
	if( pRgn )
	{
		pRgn->DeleteObject();
		pRgn->CreatePolygonRgn( m_ptStar, STARPTCOUNT, WINDING );
		pRgn->OffsetRgn( m_nX, m_nY );
		pRgn->GetRgnBox( m_rcRgn );
	}
}

void CStar::Draw(CDC* pDC, CRgn* pRgn)
{
	if( pDC && pRgn )
	{
		CBrush brush;
		brush.CreateSolidBrush( m_clrRgn );
		pDC->FillRgn( pRgn, &brush );
		brush.DeleteObject();
	}
}

void CStar::InitCoordinate(const CRect& rcClient)
{
	ASSERT( !(COORDINATECOUNT % 2) );

	int nHeight = rcClient.Height() / 2;
	int nWidth = rcClient.Width() / ( COORDINATECOUNT / 2 );

	for( int i = 0; i < COORDINATECOUNT; i++ )
	{
		m_rcCoordinate[ i ] = rcClient;

		if( COORDINATECOUNT / 2 > i )
		{
			m_rcCoordinate[i].left = i * nWidth;
			m_rcCoordinate[i].top = rcClient.top;
			m_rcCoordinate[i].right = m_rcCoordinate[i].left + nWidth;
			m_rcCoordinate[i].bottom = nHeight;
		}
		else
		{
			m_rcCoordinate[i].left = ( i - COORDINATECOUNT / 2 ) * nWidth;
			m_rcCoordinate[i].top = nHeight;
			m_rcCoordinate[i].right = m_rcCoordinate[i].left + nWidth;
			m_rcCoordinate[i].bottom = rcClient.bottom;
		}
	}
	SetPlace();
}

void CStar::SetPlace()
{
	for( int i = 0; i < COORDINATECOUNT; i++ )
	{
		if( m_rcCoordinate[i].PtInRect( CPoint( m_nX, m_nY ) ) )
		{
			m_nPlace = i;
			break;
		}
	}
}

void CStar::Draw(CDC* pDC)
{
	if( pDC )
	{
		CRgn rgn;
		Make( &rgn );
		CBrush brush;
		brush.CreateSolidBrush( m_clrRgn );
		pDC->FillRgn( &rgn, &brush );
		brush.DeleteObject();
		rgn.DeleteObject();
	}
}

void CStar::Move(CDC* pDC, CRgn* pRgn, const CRect& rcClient)
{
	if( pDC && pRgn )
	{
		Make( pRgn );

		pDC->SetROP2( R2_NOTXORPEN );
		Draw( pDC, pRgn );

		if( m_nX > (rcClient.Width() - m_nOuterSize) ) m_nSTEPX = -STEP;
		if( m_nX < m_nOuterSize ) m_nSTEPX = STEP;
		if( m_nY > (rcClient.Height() - m_nOuterSize) ) m_nSTEPY = -STEP;
		if( m_nY < m_nOuterSize ) m_nSTEPY = STEP;

		pRgn->OffsetRgn( m_nSTEPX, m_nSTEPY );
		m_nX += m_nSTEPX; m_nY += m_nSTEPY;
		
		Draw( pDC, pRgn );

		SetPlace();
	}
}

void CStar::Bump(CStar* pStar)
{
	if( pStar )
	{
		CRgn rgnCombine, rgnStar, rgnCurrent;
		rgnCombine.CreateRectRgn( 0,0,0,0 );
		pStar->Make( &rgnStar );
		Make( &rgnCurrent );

		int nCombineResult = rgnCombine.CombineRgn( &rgnStar, &rgnCurrent, RGN_AND );
		if( nCombineResult != NULLREGION && nCombineResult != ERROR )
		{
			CRect rcCombine, rcStar;
			rgnStar.GetRgnBox( &rcStar );
			rgnCombine.GetRgnBox( &rcCombine );
			if( m_nSTEPX > 0 && m_nSTEPY > 0 )
			{
				if( abs( rcCombine.right - rcStar.right ) > abs( rcCombine.bottom - rcStar.bottom ) )
					m_nSTEPY = -STEP;
				else
					m_nSTEPX = -STEP;
			}
			else if( m_nSTEPX > 0 && m_nSTEPY < 0 )
			{
				if( abs( rcCombine.top - rcStar.top ) > abs( rcCombine.right - rcStar.right ) )
					m_nSTEPY = STEP;
				else
					m_nSTEPX = -STEP;
			}
			else if( m_nSTEPX < 0 && m_nSTEPY < 0 )
			{
				if( abs( rcCombine.top - rcStar.top ) > abs( rcCombine.left - rcStar.left ) )
					m_nSTEPY = STEP;
				else
					m_nSTEPX = STEP;
			}
			else if( m_nSTEPX < 0 && m_nSTEPY > 0 )
			{
				if( abs( rcCombine.left - rcStar.left ) > abs( rcCombine.bottom - rcStar.bottom ) )
					m_nSTEPX = STEP;
				else
					m_nSTEPY = -STEP;
			}
		}

		rgnCombine.DeleteObject();
		rgnStar.DeleteObject();
		rgnCurrent.DeleteObject();
	}
}

void CStar::Size(const CRect& rcClient)
{
	InitCoordinate( rcClient );
}

void CStar::Invalidate(HWND hWnd)
{
	::InvalidateRect( hWnd, m_rcRgn, TRUE );
}

