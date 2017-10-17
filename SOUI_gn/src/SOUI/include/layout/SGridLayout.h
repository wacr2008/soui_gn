#pragma once

#include "interface/slayout-i.h"
#include "SGridLayoutParamStruct.h"

namespace SOUI
{

	// Int = %d StringA
	#define ATTR_GRIDGRAVITY(attribname, varname, allredraw)       \
        if (0 == strAttribName.CompareNoCase(attribname))          \
        {                                                          \
		    varname=SGridLayoutParam::parseGridGravity(strValue);  \
		    hRet = allredraw ? S_OK : S_FALSE;                     \
        }                                                          \
        else                                                       \


	class SGridLayoutParam : public SObjectImpl<TObjRefImpl<ILayoutParam>>
		, protected SGridLayoutParamStruct
	{
		SOUI_CLASS_NAME_DECL(SGridLayoutParam,L"GridLayoutParam")

		friend class SGridLayout;
	public:

		static GridGravity parseGridGravity(const SStringW & strValue);

		SGridLayoutParam();

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

	};

	class SOUI_EXP SGridLayout: public SObjectImpl<TObjRefImpl<ILayout>>
	{
		SOUI_CLASS_NAME_DECL_EX(SGridLayout,L"gridLayout",Layout)
	public:
		SGridLayout(void);
		~SGridLayout(void) override;

		bool IsParamAcceptable(ILayoutParam *pLayoutParam) const override;

		void LayoutChildren(SWindow * pParent) override;

		ILayoutParam * CreateLayoutParam() const override;

		CSize MeasureChildren(SWindow * pParent,int nWidth,int nHeight) const override;


		SOUI_ATTRS_DECL() 
	protected:

		int m_nCols;				/**<行数 */
		int m_nRows;				/**<列数 */
		SLayoutSize m_xInterval;	/**<水平间距 */
		SLayoutSize m_yInterval;	/**<垂直间距 */

		GridGravity m_GravityX;		/**<水平排列方式 */
		GridGravity m_GravityY;		/**<垂直排列方式 */

	};

}
