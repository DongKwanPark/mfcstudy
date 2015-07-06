#pragma once

#define STEP				10
#define STARPTCOUNT			13
#define COORDINATECOUNT		6

class CStar
{
public:
	CStar(const CRect& rcClient);
	virtual ~CStar();

public:
	void Draw(CDC* pDC);
	void Move(CDC* pDC, CRgn* pRgn, const CRect& rcClient);
	void Bump(CStar* pStar);
	void Size(const CRect& rcClient);
	void Invalidate(HWND hWnd);

	CRect& GetRect() { return m_rcRgn; }
	int GetPlace() { return m_nPlace; }

private:
	void Init(const CRect& rcClient);
	void MakePt();
	void Make(CRgn* pRgn);
	void Draw(CDC* pDC, CRgn* pRgn);

	void InitCoordinate(const CRect& rcClient);
	void SetPlace();

private:
	int m_nSTEPX;
	int m_nSTEPY;
	int m_nX, m_nY;
	int m_nOuterSize;
	int m_nInnerSize;
	int m_nPlace;
	CRect m_rcCoordinate[ COORDINATECOUNT ];

	CRect m_rcRgn;
	COLORREF m_clrRgn;
	CPoint m_ptStar[ STARPTCOUNT ];
};

