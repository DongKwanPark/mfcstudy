
// MapModeSubjectView.h : interface of the CMapModeSubjectView class
//

#pragma once


class CMapModeSubjectView : public CView
{
protected: // create from serialization only
	CMapModeSubjectView();
	DECLARE_DYNCREATE(CMapModeSubjectView)

// Attributes
public:
	CMapModeSubjectDoc* GetDocument() const;

	CRect m_rc;
	void DrawFigure(CDC* pDC);

// Operations
public:

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
	virtual ~CMapModeSubjectView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnSize(UINT nType, int cx, int cy);
	virtual void OnInitialUpdate();
};

#ifndef _DEBUG  // debug version in MapModeSubjectView.cpp
inline CMapModeSubjectDoc* CMapModeSubjectView::GetDocument() const
   { return reinterpret_cast<CMapModeSubjectDoc*>(m_pDocument); }
#endif

