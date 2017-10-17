#include "souistd.h" 
#include <unknown/obj-ref-impl.hpp>
#include "core/SSkinObjBase.h"
namespace SOUI
{

		SOUI_ATTRS_BEGIN(SSkinObjBase)
			ATTR_INT(L"alpha", m_byAlpha, TRUE)   //皮肤透明度
			ATTR_INT(L"enableColorize", m_bEnableColorize, TRUE)
			ATTR_INT(L"scale", m_nScale, FALSE)
			ATTR_STRINGW(L"name", m_strName, FALSE)
		SOUI_ATTRS_END()

		SOUI_CLASS_NAME_EX(SSkinObjBase, L"skinObjBase", Skin)

	    SSkinObjBase::SSkinObjBase() :m_byAlpha(0xFF), m_crColorize(0), m_bEnableColorize(TRUE), m_nScale(100) 
		{
		}
     
		SSkinObjBase::~SSkinObjBase()
		{

		}


		BYTE SSkinObjBase::GetAlpha() const
		{
			return m_byAlpha;
		}

        void SSkinObjBase::SetAlpha(BYTE byAlpha) 
		{
            m_byAlpha = byAlpha;
        }

        void SSkinObjBase::Draw(IRenderTarget *pRT, LPCRECT rcDraw, DWORD dwState,BYTE byAlpha) 
        {
            _Draw(pRT,rcDraw,dwState,byAlpha);
        }

        void SSkinObjBase::Draw(IRenderTarget *pRT, LPCRECT rcDraw, DWORD dwState) 
        {
            Draw(pRT,rcDraw,dwState,GetAlpha());
        }

        SIZE SSkinObjBase::GetSkinSize() 
        {
            SIZE ret = {0, 0};

            return ret;
        }

        BOOL SSkinObjBase::IgnoreState() 
        {
            return TRUE;
        }

        int SSkinObjBase::GetStates() 
        {
            return 1;
        }

		int SSkinObjBase::GetScale() const 
		{
			return m_nScale;
		}

		ISkinObj * SSkinObjBase::Scale(int nScale) 
		{
			ISkinObj * skinObj = SApplication::getSingleton().CreateSkinByName(GetObjectClass());
			if(!skinObj) return NULL;
			_Scale(skinObj,nScale);
			return skinObj;
		}

		LPCWSTR SSkinObjBase::GetName() const  
		{
			return m_strName;
		}
		  
		void SSkinObjBase::_Scale(ISkinObj *pObj, int nScale)
		{
			SSkinObjBase * pSkinObj = sobj_cast<SSkinObjBase>(pObj);
			pSkinObj->m_nScale = nScale;
			pSkinObj->m_byAlpha = m_byAlpha;
			pSkinObj->m_bEnableColorize = m_bEnableColorize;
			pSkinObj->m_crColorize = m_crColorize;
			pSkinObj->m_strName = m_strName;
		}
		 
		 
}//namespace SOUI