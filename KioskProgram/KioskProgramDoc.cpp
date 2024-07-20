// KioskProgramDoc.cpp : implementation of the CKioskProgramDoc class

#include "pch.h"
#include "framework.h"

#ifndef SHARED_HANDLERS
#include "KioskProgram.h"
#endif

#include "KioskProgramDoc.h"

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CKioskProgramDoc

IMPLEMENT_DYNCREATE(CKioskProgramDoc, CDocument)

BEGIN_MESSAGE_MAP(CKioskProgramDoc, CDocument)
END_MESSAGE_MAP()


// CKioskProgramDoc construction/destruction

CKioskProgramDoc::CKioskProgramDoc() noexcept
{
}

CKioskProgramDoc::~CKioskProgramDoc()
{
}

BOOL CKioskProgramDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	return TRUE;
}


// CKioskProgramDoc serialization

void CKioskProgramDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
	}
	else
	{
	}
}


#ifdef SHARED_HANDLERS

// Support for thumbnails
void CKioskProgramDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// Modify this code to draw the document's data
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// Support for Search Handlers
void CKioskProgramDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// Set search contents from document's data.
	// The content parts should be separated by ";"

	// For example:  strSearchContent = _T("point;rectangle;circle;ole object;");
	SetSearchContent(strSearchContent);
}

void CKioskProgramDoc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = nullptr;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != nullptr)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS


// CKioskProgramDoc diagnostics

#ifdef _DEBUG
void CKioskProgramDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CKioskProgramDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CKioskProgramDoc commands

