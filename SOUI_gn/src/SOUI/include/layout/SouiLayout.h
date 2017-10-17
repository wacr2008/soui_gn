#pragma once
#include "interface/slayout-i.h"
#include "SouiLayoutParamStruct.h"

namespace SOUI{



	class SOUI_EXP SouiLayoutParam: public SObjectImpl<TObjRefImpl<ILayoutParam>>
						 , protected SouiLayoutParamStruct
	{
		SOUI_CLASS_NAME_DECL(SouiLayoutParam,L"SouiLayoutParam")

		friend class SouiLayout;
	public:
		SouiLayoutParam();

		bool IsMatchParent(ORIENTATION orientation) const override;

		bool IsSpecifiedSize(ORIENTATION orientation) const override;

		bool IsWrapContent(ORIENTATION orientation) const override;

		SLayoutSize  GetSpecifiedSize(ORIENTATION orientation) const override;

		void Clear() override;

		void SetMatchParent(ORIENTATION orientation) override;

		void SetWrapContent(ORIENTATION orientation) override;

		void SetSpecifiedSize(ORIENTATION orientation, const SLayoutSize& layoutSize) override;

		void * GetRawData() override;
	public:
		bool IsOffsetRequired(ORIENTATION orientation) const;
        int  GetExtraSize(ORIENTATION orientation,int nScale) const;
	protected:
		HRESULT OnAttrWidth(const SStringW & strValue,BOOL bLoading);

		HRESULT OnAttrHeight(const SStringW & strValue,BOOL bLoading);

		HRESULT OnAttrSize(const SStringW & strValue,BOOL bLoading);

		HRESULT OnAttrPos(const SStringW & strValue,BOOL bLoading);

		HRESULT OnAttrOffset(const SStringW & strValue,BOOL bLoading);

		SOUI_ATTRS_DECL() 

    protected:
        //将字符串描述的坐标转换成POSITION_ITEM
        BOOL StrPos2ItemPos(const SStringW &strPos,POS_INFO & posItem);

        //解析在pos中定义的前两个位置
        BOOL ParsePosition12(const SStringW & pos1, const SStringW &pos2);

        //解析在pos中定义的后两个位置
        BOOL ParsePosition34(const SStringW & pos3, const SStringW &pos4);


	};

	class SOUI_EXP SouiLayout: public SObjectImpl<TObjRefImpl<ILayout>>
	{
		SOUI_CLASS_NAME_DECL_EX(SouiLayout,L"SouiLayout",Layout)

	public:
		SouiLayout(void);
		~SouiLayout(void) override;

        bool IsParamAcceptable(ILayoutParam *pLayoutParam) const override;

        void LayoutChildren(SWindow * pParent) override;

        ILayoutParam * CreateLayoutParam() const override;

        CSize MeasureChildren(SWindow * pParent,int nWidth,int nHeight) const override;
    protected:
        struct WndPos{
            SWindow *pWnd;
            CRect    rc;
			bool     bWaitOffsetX;
			bool	 bWaitOffsetY;
        };

        void CalcPositionEx(SList<WndPos> *pListChildren,int nWidth,int nHeight) const;
        int CalcPostion(SList<WndPos> *pListChildren,int nWidth,int nHeight) const;

		int PositionItem2Value(SList<WndPos> *pLstChilds,SPOSITION position,const POS_INFO &pos , int nMax,BOOL bX,int nScale) const;
        
        int CalcChildLeft(SWindow *pWindow,SouiLayoutParam *pParam);
        int CalcChildRight(SWindow *pWindow,SouiLayoutParam *pParam);
        int CalcChildTop(SWindow *pWindow,SouiLayoutParam *pParam);
        int CalcChildBottom(SWindow *pWindow,SouiLayoutParam *pParam);


        BOOL IsWaitingPos( int nPos ) const;
		SWindow * GetRefSibling(SWindow *pCurWnd,int uCode);
        CRect GetWindowLayoutRect(SWindow *pWindow);
    };


}
