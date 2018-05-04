#pragma once

#include "SComboBase.h"
#include "SListView.h"

namespace SOUI
{
    class SOUI_EXP SComboView : public SComboBase
    {
        SOUI_CLASS_NAME_DECL(SComboView,L"comboview")
    public:
        SComboView(void);
        ~SComboView(void) override;

        BOOL SetCurSel(int iSel) override;

        /**
        * SComboView::GetCurSel
        * @brief    获取选中索引
        * @return   返回int -- 选中索引
        * 
        * Describe  获取选中索引
        */ 
        int GetCurSel() const override;

        /**
        * SComboView::GetCount
        * @brief    获取下拉项个数
        * @return   返回int
        * 
        * Describe  获取下拉项个数
        */ 
        int  GetCount() const override;

        /**
        * SComboView::GetLBText
        * @brief    获取文本
        * @param    int iItem -- 索引值
        *
        * Describe  获取文本
        */
        SStringT GetLBText(int iItem,BOOL bRawText=FALSE) override;
        
        /**
        * SComboView::GetListBox
        * @brief    获取下拉列表指针
        * @param    返回SListBox * 
        *
        * Describe  获取下拉列表指针
        */
        SListView * GetListView();

    protected:
        /**
        * SComboView::FireEvent
        * @brief    通知消息
        * @param    EventArgs &evt -- 事件对象 
        * 
        * Describe  此函数是消息响应函数
        */ 
        BOOL FireEvent(EventArgs &evt) override;

        virtual void OnScaleChanged(int nScale);

        /**
        * SComboView::CreateListBox
        * @brief    创建下拉列表
        * @param    返回BOOL TRUE -- 成功 FALSE -- 失败
        *
        * Describe  创建下拉列表
        */
        BOOL CreateListBox(pugi::xml_node xmlNode) override;

        /**
        * SComboView::GetListBoxHeight
        * @brief    获取下拉列表高度
        * @param    返回int
        *
        * Describe  获取下拉列表高度
        */
        int  GetListBoxHeight() override;

        /**
        * SComboView::OnCreateDropDown
        * @brief    下拉列表事件
        * @param    SDropDownWnd *pDropDown -- 下拉列表指针
        *
        * Describe  下拉列表事件
        */
        void OnCreateDropDown(SDropDownWnd *pDropDown) override;

        /**
        * SComboView::OnDestroyDropDown
        * @brief    下拉列表关闭事件
        * @param    SDropDownWnd *pDropDown -- 下拉列表指针
        * @param    UINT uCode -- 消息码
        *
        * Describe  获取下拉列表指针
        */
        void OnDestroyDropDown(SDropDownWnd *pDropDown) override;

        /**
        * SComboView::OnSelChanged
        * @brief    下拉列表selected事件
        *
        * Describe  下拉列表selected事件
        */
        void OnSelChanged() override;

    protected:

        SListView *m_pListBox;  /**< SListBox指针 */
    };

}
