#pragma once

#include "interface/slayout-i.h"
#include "SLinearLayoutParamStruct.h"

namespace SOUI
{

	class SOUI_EXP SLinearLayoutParam : public SObjectImpl<TObjRefImpl<ILayoutParam>>
							 , protected SLinearLayoutParamStruct
    {
        SOUI_CLASS_NAME_DECL(SLinearLayoutParam,L"LinearLayoutParam")

		friend class SLinearLayout;
    public:
		SLinearLayoutParam();

        bool IsMatchParent(ORIENTATION orientation) const override;
		bool IsWrapContent(ORIENTATION orientation) const override;

        bool IsSpecifiedSize(ORIENTATION orientation) const override;

        SLayoutSize GetSpecifiedSize(ORIENTATION orientation) const override;

		void Clear() override;

		void SetMatchParent(ORIENTATION orientation) override;

		void SetWrapContent(ORIENTATION orientation) override;

		void SetSpecifiedSize(ORIENTATION orientation, const SLayoutSize& layoutSize) override;

		void * GetRawData() override;

        SOUI_ATTRS_DECL() 


	protected:
        HRESULT OnAttrSize(const SStringW & strValue,BOOL bLoading);
		HRESULT OnAttrWidth(const SStringW & strValue,BOOL bLoading);
		HRESULT OnAttrHeight(const SStringW & strValue,BOOL bLoading);
		HRESULT OnAttrExtend(const SStringW & strValue,BOOL bLoading);

    };

    class SOUI_EXP SLinearLayout : public SObjectImpl<TObjRefImpl<ILayout>>
    {
		SOUI_CLASS_NAME_DECL_EX(SLinearLayout,L"linearLayout",Layout)
    public:
        SLinearLayout(void);
        ~SLinearLayout(void) override;

        void LayoutChildren(SWindow * pParent) override;
        ILayoutParam * CreateLayoutParam() const override;
		CSize MeasureChildren(SWindow * pParent,int nWidth,int nHeight) const override;
		bool IsParamAcceptable(ILayoutParam *pLayoutParam) const override;

        
        SOUI_ATTRS_DECL() 


	protected:
		ORIENTATION m_orientation;
        Gravity     m_gravity;
    };

	class SVBox : public SLinearLayout
	{
		SOUI_CLASS_NAME_DECL(SVBox,L"vbox")

	public:
		SVBox(){m_orientation = Vert;}
	};

	class SHBox : public SLinearLayout
	{
		SOUI_CLASS_NAME_DECL(SHBox,L"hbox")

	public:
		SHBox(){m_orientation = Horz;}
	};
}

