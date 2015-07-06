
// ExtendStarView.h : interface of the CExtendStarView class
//

#pragma once

#include "Star.h"

class CExtendStarView : public CView
{
protected: // create from serialization only
	CExtendStarView();
	DECLARE_DYNCREATE(CExtendStarView)

// Attributes
public:
	CExtendStarDoc* GetDocument() const;

private:
	CRgn m_rgnStar;
	CMapWordToPtr m_mapCoordinate;
	CList< CStar*, CStar* > m_listStar;

// Operations
public:

private:
	void InitStar(const int& nCount);
	void DestoryStar();

	void DrawStar(CDC* pDC);
	void DeleteStar();
	void DeleteCoordinate();

	void DeleteCoordinate(CStar* pMovingStar);
	void SetCoordinate(CStar* pStar);
	void MakeStar(const int& nCount);
	void BumpCheck(CStar* pMovingStar);
	
// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// Implementation
public:
	virtual ~CExtendStarView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
public:
	virtual void OnInitialUpdate();
	afx_msg void OnDestroy();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnStarSetting();
};

#ifndef _DEBUG  // debug version in ExtendStarView.cpp
inline CExtendStarDoc* CExtendStarView::GetDocument() const
   { return reinterpret_cast<CExtendStarDoc*>(m_pDocument); }
#endif

