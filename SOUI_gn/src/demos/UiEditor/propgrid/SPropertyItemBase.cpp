﻿
#include "SPropertyItemBase.h"
#include "SPropertyGrid.h"


namespace SOUI
{
	SOUI_CLASS_NAME(SPropertyItemBase, L"propitembase")

	SOUI_ATTRS_BEGIN(SPropertyItemBase)
		ATTR_STRINGW(L"name", m_strName, FALSE)
		ATTR_STRINGW(L"name2", m_strName2, FALSE)
		ATTR_INT(L"id", m_nID, FALSE)
		ATTR_STRINGT(L"description", m_strDescription, FALSE)
		ATTR_INT(L"readOnly", m_bReadOnly, FALSE)
		ATTR_CUSTOM(L"expanded", OnAttrExpanded)
	SOUI_ATTRS_END()

    int SPropertyItemBase::GetLevel() const
    {
        int iLevel = 0;
        IPropertyItem *pParent=GetParent();
        while(pParent)
        {
            iLevel ++;
            pParent = pParent->GetParent();
        }
        return iLevel;
    }

    BOOL SPropertyItemBase::IsExpand() const
    {
        return m_bExpanded;
    }

    void SPropertyItemBase::Expand( BOOL bExpend )
    {
        m_bExpanded = bExpend;
        GetOwner()->OnItemExpanded(this);
    }

    IPropertyItem * SPropertyItemBase::GetParent() const
    {
        return m_pParent;
    }

    void SPropertyItemBase::SetParent( IPropertyItem * pParent )
    {
        m_pParent = pParent;
    }


    IPropertyItem * SPropertyItemBase::GetItem( PROPITEMTYPE type) const
    {
        switch (type)
        {
        case GPI_PARENT:
            return GetParent();
            break;
        case GPI_FIRSTCHILD:
            if(m_childs.IsEmpty()) return NULL;
            else return m_childs.GetHead();
            break;
        case GPI_LASTCHILD:
            if(m_childs.IsEmpty()) return NULL;
            else return m_childs.GetTail();
            break;
        case GPI_NEXTSIBLING:
            {
                SPropertyItemBase * pParent = (SPropertyItemBase*)GetParent();
                if(!pParent) return NULL;

                SPOSITION pos = pParent->m_childs.Find((IPropertyItemPtr)this);
                SASSERT(pos);
                pParent->m_childs.GetNext(pos);
                if(!pos) return NULL;
                return pParent->m_childs.GetAt(pos);
            }
            break;
        case GPI_PREVSIBLINIG:
            {
                SPropertyItemBase * pParent = (SPropertyItemBase*)GetParent();
                if(!pParent) return NULL;
                SPOSITION pos = pParent->m_childs.Find((IPropertyItemPtr)this);
                SASSERT(pos);
                pParent->m_childs.GetPrev(pos);
                if(!pos) return NULL;
                return pParent->m_childs.GetAt(pos);
            }
            break;
        }
        return NULL;
    }

    SPropertyGrid * SPropertyItemBase::GetOwner() const
    {
        return m_pOwner;
    }

    BOOL SPropertyItemBase::InsertChild( IPropertyItem * pChild,IPropertyItem * pInsertAfter/*=IC_LAST*/ )
    {
		SPropertyGrid* grid = GetOwner();
        if(pInsertAfter == IC_LAST)
		{
			if (!(pChild->GetName2().IsEmpty()))
			{
				grid->AddGridItem(pChild);
			}
			
			m_childs.InsertAfter(NULL,pChild);
		}
        else if(pInsertAfter == IC_FIRST)
		{
			if (!(pChild->GetName2().IsEmpty()))
			{
				grid->AddGridItem(pChild);
			}
			m_childs.InsertBefore(NULL,pChild);
		}
        else
        {
            SPOSITION pos = m_childs.Find(pInsertAfter);
            if(!pos) return FALSE;

			if (!(pChild->GetName2().IsEmpty()))
			{
				grid->AddGridItem(pChild);
			}
            m_childs.InsertAfter(pos,pChild);            
        }
        pChild->SetParent(this);
        pChild->AddRef();
        return TRUE;
    }

    int SPropertyItemBase::ChildrenCount() const
    {
        return m_childs.GetCount();
    }

    BOOL SPropertyItemBase::RemoveChild( IPropertyItem * pChild )
    {
        SPOSITION pos = m_childs.Find(pChild);
        if(!pos) return FALSE;
		SPropertyGrid* grid = GetOwner();
		if (!(pChild->GetName2().IsEmpty()))
		{
			grid->RemoveGridItem(pChild);
		}
        m_childs.RemoveAt(pos);
        pChild->Release();
        return TRUE;
    }

    SPropertyItemBase::~SPropertyItemBase()
    {
        SPOSITION pos = m_childs.GetHeadPosition();
        while(pos)
        {
            IPropertyItemPtr pChild = m_childs.GetNext(pos);
            pChild->Release();
        }
		SPropertyGrid* grid = GetOwner();
		grid->RemoveAllGridItem();
        m_childs.RemoveAll();

    }

    BOOL SPropertyItemBase::InitFromXml( pugi::xml_node xmlNode )
    {
        SObject::InitFromXml(xmlNode);
        pugi::xml_node xmlProp=xmlNode.first_child();
        while(xmlProp)
        {
            IPropertyItem * pItem = SPropItemMap::CreatePropItem(xmlProp.name(),GetOwner());
            if(pItem)
            {
                SPropertyItemBase *pItem2 = static_cast<SPropertyItemBase*>(pItem);
                if(pItem2)
                {
                    pItem2->InitFromXml(xmlProp);
                    InsertChild(pItem2);
                    pItem2->Release();
                }
            }
            xmlProp = xmlProp.next_sibling();
        }
        return TRUE;
    }

    HRESULT SPropertyItemBase::OnAttrExpanded( const SStringW & strValue,BOOL bLoading )
    {
        BOOL bExpanded = strValue!=L"0";
        if(!bLoading) Expand(bExpanded);
        else m_bExpanded = bExpanded;
        return S_FALSE;
    }

    void SPropertyItemBase::OnValueChanged()
    {
        GetOwner()->OnItemValueChanged(this);
        if(GetParent()) GetParent()->OnChildValueChanged(this);
    }

}

