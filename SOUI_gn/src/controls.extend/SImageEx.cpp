
#include "SImageEx.h"
#include "SSkinMutiFrameImg.h"

using namespace SOUI;

SOUI_CLASS_NAME(SImageEx, L"imgex")

SOUI_ATTRS_BEGIN(SImageEx)
	ATTR_CUSTOM(L"src", OnSrc)
SOUI_ATTRS_END()

SImageEx::SImageEx()
{
}

SImageEx::~SImageEx()
{
}

HRESULT SImageEx::OnSrc(const SStringW& strValue, BOOL bLoading)
{
	SSkinAni *pSkin = (SSkinAni*)SApplication::getSingleton().CreateSkinByName(SSkinMutiFrameImg::GetClassName());
	if(!pSkin) return FALSE;
	if(0==pSkin->LoadFromFile(strValue))
	{
		pSkin->Release();
		return FALSE;
	}

	pSkin->SetAttribute(L"filterLevel", L"high");
	m_pBgSkin = pSkin;
	return TRUE;
}
