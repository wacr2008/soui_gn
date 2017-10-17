﻿#pragma once

#include "STreeList.h"

namespace SOUI
{
    class SFolderTreeCtrl : public SMCTreeCtrl
    {
        SOUI_CLASS_NAME_DECL(SFolderTreeCtrl,L"foldertreectrl")
        
        struct FILEITEMINFO
        {
            BOOL    bFolder;//文件夹标志
            __int64 nSize;  //总文件夹大小
            float   percent;//占上级文件夹的百分比
        };
        
        struct SORTINFO
        {
            enum{
                BYNAME,
                BYSIZE,
            } mode;
            BOOL bAscend;   //升序
        };
        
        struct SORTCTX
        {
            SFolderTreeCtrl *pTree;
            SORTINFO si;
        };
        friend class SFolderTreeList;
    public:
        SFolderTreeCtrl();
        ~SFolderTreeCtrl();
        
        HSTREEITEM InsertItem(LPCTSTR pszFileName,BOOL bFolder,__int64 fileSize,HSTREEITEM hParent);
        void UpdateTreeItemPercent(HSTREEITEM hItem);
        FILEITEMINFO * GetFileInfo(HSTREEITEM hItem);
        void SortChildren(HSTREEITEM hItem,SORTINFO si);
        
    protected:
        static int _cdecl SortChildrenCB(void* pCtx,const void *phItem1,const void *phItem2);
        
        virtual void DrawTreeItem(IRenderTarget *pRT, CRect & rc,HSTREEITEM hItem);
        virtual void DrawListItem(IRenderTarget *pRT, CRect & rc,HSTREEITEM hItem);
        virtual void OnNodeFree(LPTVITEM & pItemData);
        virtual void OnInsertItem(LPTVITEM & pItemData);
        virtual void ItemLayout();

        virtual void OnFinalRelease();
        
    protected:
        SOUI_ATTRS_DECL()
        
        ISkinObj    *m_pSkinPerBkgnd,*m_pSkinPerFrgnd;
        HIMAGELIST   m_hIconList;
    };
    
    class SFolderTreeList : public STreeList
    {
    SOUI_CLASS_NAME_DECL(SFolderTreeList,L"foldertreelist")
    public:
        SFolderTreeList(void);
        ~SFolderTreeList(void);
                
        SFolderTreeCtrl * GetFolderTreeCtrl() { return m_pFolderTreectrl;}
    protected:
            /**
        * SListCtrl::OnHeaderClick
        * @brief    列表头单击事件 -- 
        * @param    EventArgs *pEvt
        *
        * Describe  列表头单击事件
        */
        bool            OnHeaderClick(EventArgs *pEvt);

    protected:
        virtual BOOL CreateChildren(pugi::xml_node xmlNode);
        virtual SMCTreeCtrl * CreateMcTreeCtrl();

        SFolderTreeCtrl::SORTINFO m_si;
        SFolderTreeCtrl * m_pFolderTreectrl;
    };
}

