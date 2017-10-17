
#include "SSkinImgFrame3.h"
#include <souicoll.h>

namespace SOUI
{
    typedef SMap<SStringW,IBitmap *> IMGPOOL;
    static IMGPOOL s_imgPool;
    

	SOUI_CLASS_NAME(SSkinImgFrame3, L"imgframe3")
	
	SOUI_ATTRS_BEGIN(SSkinImgFrame3)
		ATTR_CUSTOM(L"src", OnAttrSrc)
		/* offcut-left/right/top/bottom 因为组合图往往子图之间有空白 */
		/* 这里定义对应的子图图片切割掉上下左右多少，防止切割出来的图片有无用的边沿   */
		ATTR_RECT(L"offcut", m_offset, FALSE)
	SOUI_ATTRS_END()


    SSkinImgFrame3::SSkinImgFrame3(void)
    {
    }

    SSkinImgFrame3::~SSkinImgFrame3(void)
    {
        if(GetImage())
        {
            if(GetImage()->Release() == 0)
            {
                s_imgPool.RemoveKey(m_strImgKey);
            }
        }
    }

    LRESULT SSkinImgFrame3::OnAttrSrc(const SStringW & strValue,BOOL bLoading)
    {
        int iPos = strValue.Find(L'{');
        if(iPos==-1) return E_FAIL;
        m_strImgKey = strValue.Left(iPos);
        SStringW strRgn = strValue.Right(strValue.GetLength()-iPos);
        if(swscanf(strRgn,L"{%d,%d,%d,%d}",&m_rcImg.left,&m_rcImg.top,&m_rcImg.right,&m_rcImg.bottom)!=4)
        {
            CPoint pt;
            CSize sz;
            if(swscanf(strRgn,L"{%d,%d,@%d,@%d}",&pt.x,&pt.y,&sz.cx,&sz.cy)!=4)
                return E_FAIL;
            m_rcImg = CRect(pt,sz);
        }
        
        IMGPOOL::CPair * p = s_imgPool.Lookup(m_strImgKey);
        if(p)
        {
            SSkinImgFrame::SetImage(p->m_value);
            p->m_value->AddRef();
        }else
        {
            IBitmap *pImg=LOADIMAGE2(m_strImgKey);
            if(!pImg) return E_FAIL;
            s_imgPool[m_strImgKey]=pImg;
            SSkinImgFrame::SetImage(pImg);
        }
        return S_OK;
    }

    SIZE SSkinImgFrame3::GetSkinSize()
    {
        CSize szImg = m_rcImg.Size();
        if(IsVertical()) szImg.cy /= GetStates();
        else szImg.cx /= GetStates();
        return szImg;
    }

    void SSkinImgFrame3::_Draw(IRenderTarget *pRT, LPCRECT rcDraw, DWORD dwState,BYTE byAlpha)
    {
        if(!GetImage()) return;
        
        CRect rcSrc = CRect(m_rcImg.TopLeft(),GetSkinSize());
		if(m_bVertical) 
			OffsetRect(&rcSrc,0, dwState * rcSrc.Height());
		else
			OffsetRect(&rcSrc, dwState * rcSrc.Width(), 0);
        rcSrc.DeflateRect(m_offset);
        pRT->DrawBitmap9Patch(rcDraw,GetImage(),&rcSrc,&m_rcMargin,IsTile()?EM_TILE:EM_STRETCH,byAlpha);
    }

}
