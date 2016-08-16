#include "souistd.h"
#include "layout/SFlowLayout.h"
#include "core/SwndLayoutBuilder.h"

namespace SOUI
{
	SFlowLayout::SFlowLayout()
	{
		m_iChildPaddLen = 0;
	}
	///--------------------------------SVBox----------------
	void SVBox::UpdateChildrenPosition()
	{
		do 
		{
			// 1.获得子控件的布局空间
			CRect rcLayout =GetChildrenLayoutRect();
			if (rcLayout.IsRectEmpty())
			{
				break;
			}
			// 2.判断容器子控件是不是为空
			if (0==GetChildrenCount())
			{
				break;
			}

			// 3.计算容器可用的大小
			SIZE szAvailable = rcLayout.Size();

			// 4.计算最小的大小 
			int nAdjustNum	= 0;   //  没有设置高度的需自动计算高度的个数
			int nCyFixedLen = 0;   //  总估值高度
			int nEstimateNum = 0;  //  估值高度的个数,包括了nAdjustNum

			CRect rc;
			SWindow *pChild = GetWindow(GSW_FIRSTCHILD);
			while (pChild)
			{
				if (!pChild->IsVisible(FALSE))
				{
					pChild = pChild->GetWindow(GSW_NEXTSIBLING);
					continue;
				}

				// 5. 获得预设的fixsize，像这种竖直布局，一般会设置固定的高度，对应xml的height值
				CSize szMeasure(POS_INIT, POS_INIT);
				CRect rc =pChild->GetWindowRect();// 如设置了高度，会自动赋值
				
				/*
				CRect &rcPadd = pChild->m_pDUIXmlInfo->m_rcPadd;
				if (POS_INIT == szMeasure.cy)
				{
					nAdjustNum++;// 没有设置高度的需自动计算高度的个数
					nCyFixedLen += rcPadd.top + rcPadd.bottom;
				}
				else
				{
					int nMinHeight = pChild->m_pDUIXmlInfo->m_nMinHeight;
					int nMaxHeight = pChild->m_pDUIXmlInfo->m_nMaxHeight;

					if (nMinHeight != -1
						&& szMeasure.cy<nMinHeight)
					{
						szMeasure.cy = nMinHeight;
					}
					if (nMaxHeight != -1
						&& szMeasure.cy>nMaxHeight)
					{
						szMeasure.cy = nMaxHeight;
					}

					nCyFixedLen += szMeasure.cy + rcPadd.top + rcPadd.bottom;
				}
				*/
				nEstimateNum++; 
				pChild = pChild->GetWindow(GSW_NEXTSIBLING);
			}

			// 8.子控件之间的额外距离
			nCyFixedLen += (nEstimateNum-1)*m_iChildPaddLen;

			// 开始摆放子控件
			int ncyAdjustItemLen	= 0;
			if (nAdjustNum>0)
			{
				// 9.判断自动计算高度够不够
				ncyAdjustItemLen = (szAvailable.cy>nCyFixedLen)?((szAvailable.cy-nCyFixedLen)/nAdjustNum):0;
			}

			SIZE szRemain = szAvailable;
			int iAdjustIndex = 0;
			int nCyFixedLenRemain = nCyFixedLen;
			int iPosY = rcLayout.top;
			int iPosX = rcLayout.left;

			pChild =  GetWindow(GSW_FIRSTCHILD);
			while (pChild)
			{
				if (!pChild->IsVisible(FALSE))
				{
					pChild=pChild->GetWindow(GSW_NEXTSIBLING);
					continue;
				}

				 
				int nMinHeight = -1;// pChild->m_pDUIXmlInfo->m_nMinHeight;
				int nMaxHeight = -1;//pChild->m_pDUIXmlInfo->m_nMaxHeight;
				int nMinWidth = -1;//pChild->m_pDUIXmlInfo->m_nMinWidth;
				int nMaxWidth = -1;//pChild->m_pDUIXmlInfo->m_nMaxWidth;
				CRect rcPadd = {0,0,0,0};// pChild->m_pDUIXmlInfo->m_rcPadd;
				szRemain.cy -= rcPadd.top;// 这里先减去top

				// 计算y
				CSize szMeasure(POS_INIT,POS_INIT);//设置最大值
				szMeasure  =pChild->GetDesiredSize(NULL);
				if (POS_INIT == szMeasure.cy)// 没有设置高度的控件
				{
					iAdjustIndex++;
					szMeasure.cy = ncyAdjustItemLen;

					if (iAdjustIndex == nAdjustNum)
					{// 最后一个没有设置高度的控件，因为前面可能有最大最小限制使得cy!=ncyAdjustItemLen
					 // +rcPadd.top是因为前面减了rcPadd.top,而nCyFixedLenRemain中包含了rcPadd.top+rcPadd.bottm
					 // 这只是最后一个没设置高度的控件，不一定是最后的控件，所以要-nCyFixedLenRemain
						szMeasure.cy = szRemain.cy+rcPadd.top-nCyFixedLenRemain;
						szMeasure.cy = szMeasure.cy<=0?0:szMeasure.cy;
					}
					if (nMinHeight!=-1
						&&szMeasure.cy<nMinHeight)
					{
						szMeasure.cy = nMinHeight;
					}
					if (nMaxHeight!=-1
						&&szMeasure.cy>nMaxHeight)
					{
						szMeasure.cy = nMaxHeight;
					}
				}
				else
				{
					if (nMinHeight!=-1
						&&szMeasure.cy<nMinHeight)
					{
						szMeasure.cy = nMinHeight;
					}
					if (nMaxHeight!=-1
						&&szMeasure.cy>nMaxHeight)
					{
						szMeasure.cy = nMaxHeight;
					}
					nCyFixedLenRemain -= szMeasure.cy;
				}

				// 计算x
				szMeasure.cx = pChild->GetWindowRect().Width();
				if (-1 == szMeasure.cx)
				{// 初始默认值-1
					szMeasure.cx = szAvailable.cx-rcPadd.left-rcPadd.right;
				}
				else if (szMeasure.cx<0)
				{
					szMeasure.cx = 0;
				}
				if (nMinWidth!=-1
					&&szMeasure.cx<nMinWidth)
				{
					szMeasure.cx = nMinWidth;
				}
				if (nMaxWidth!=-1
					&&szMeasure.cx>nMaxWidth)
				{
					szMeasure.cx = nMaxWidth;
				}

				//CRect &rcWindow  = rcLayout;// 容器大小
				CRect rcArrange(iPosX+rcPadd.left,iPosY+rcPadd.top,iPosX+rcPadd.left+szMeasure.cx, iPosY+rcPadd.top+szMeasure.cy);
				pChild->Move(&rcArrange);

				pChild=pChild->GetWindow(GSW_NEXTSIBLING);
				iPosY += szMeasure.cy + (NULL == pChild?0:m_iChildPaddLen) + rcPadd.top+rcPadd.bottom;
				szRemain.cy -= szMeasure.cy + (NULL == pChild?0:m_iChildPaddLen) + rcPadd.bottom;// 最前面减去top了
				nCyFixedLenRemain -= (NULL == pChild?0:m_iChildPaddLen) + rcPadd.top+rcPadd.bottom;
			 
			}
		} while (false); 
	}

	///--------------------------------SHBox----------------
	void SHBox::UpdateChildrenPosition()
	{
		do 
		{
			// 1.获得子控件的布局空间
			CRect rcLayout = GetChildrenLayoutRect();
			if (rcLayout.IsRectEmpty())
			{
				break;
			}

			// 3.计算容器可用的大小
			SIZE szAvailable = rcLayout.Size();

			// 4.计算最小的大小
			int nAdjustNum	= 0;   //  没有设置宽度的需自动计算宽度的个数
			int nCxFixedLen = 0;   //  总估值宽度
			int nEstimateNum = 0;  //  估值宽度的个数,包括了nAdjustNum

			SWindow *pChild = GetWindow(GSW_FIRSTCHILD);
			while (pChild)
			{
				if (!pChild->IsVisible(FALSE))
				{
					pChild=pChild->GetWindow(GSW_NEXTSIBLING);
					continue;
				}

			
				// 5. 获得预设的fixsize，像这种水平布局，一般会设置固定的宽度，对应xml的width值
				CSize szMeasure(POS_INIT,POS_INIT); //先设置它的最大值
				szMeasure = pChild->GetDesiredSize(NULL);
				CRect rcPadd = {0,0,0,0};// pChild->m_pDUIXmlInfo->m_rcPadd;
				if (POS_INIT == szMeasure.cx)
				{
					nCxFixedLen += rcPadd.left+rcPadd.right;
					nAdjustNum++;// 没有设置宽度的需自动计算宽度的个数
				}
				else
				{
					int nMinWidth = -1;// pChild->m_pDUIXmlInfo->m_nMinWidth;
					int nMaxWidth = -1;// pChild->m_pDUIXmlInfo->m_nMaxWidth;
					if (nMinWidth!=-1
						&&szMeasure.cx<nMinWidth)
					{
						szMeasure.cx = nMinWidth;
					}
					if (nMaxWidth!=-1
						&&szMeasure.cx>nMaxWidth)
					{
						szMeasure.cx = nMaxWidth;
					}
					nCxFixedLen += szMeasure.cx+rcPadd.left+rcPadd.right;
				}
				
				nEstimateNum++;
				pChild = pChild->GetWindow(GSW_NEXTSIBLING);
			}

			// 8.子控件之间的额外距离
			nCxFixedLen += (nEstimateNum-1)*m_iChildPaddLen;

			// 开始摆放子控件
			int ncxAdjustItemLen	= 0;
			if (nAdjustNum>0)
			{
				// 9.判断自动计算宽度够不够
				ncxAdjustItemLen = (szAvailable.cx>nCxFixedLen)?((szAvailable.cx-nCxFixedLen)/nAdjustNum):0;
			}

			SIZE szRemain = szAvailable;
			int iAdjustIndex = 0;
			int nCxFixedLenRemain = nCxFixedLen;
			int iPosX = rcLayout.left;

			pChild = GetWindow(GSW_FIRSTCHILD);
			while (pChild)
			{
				if (!pChild->IsVisible(FALSE))
				{
					pChild=pChild->GetWindow(GSW_NEXTSIBLING);
					continue;
				}

				int nMinHeight = -1;// pChild->m_pDUIXmlInfo->m_nMinHeight;
				int nMaxHeight = -1;//pChild->m_pDUIXmlInfo->m_nMaxHeight;
				int nMinWidth = -1;//pChild->m_pDUIXmlInfo->m_nMinWidth;
				int nMaxWidth = -1;//pChild->m_pDUIXmlInfo->m_nMaxWidth;
				CRect rcPadd = {0,0,0,0};// pChild->m_pDUIXmlInfo->m_rcPadd;
				szRemain.cx -= rcPadd.left;
				

				// 计算x
				CSize szMeasure(POS_INIT,POS_INIT);//先设置它的最大值
				szMeasure =pChild->GetDesiredSize(NULL);
				if (POS_INIT == szMeasure.cx)// 没有设置宽度的控件
				{
					iAdjustIndex++;
					szMeasure.cx = ncxAdjustItemLen;
					if (iAdjustIndex == nAdjustNum)
					{// 最后一个没有设置宽度的控件，因为前面可能有最大最小限制使得cx!=ncxAdjustItemLen
						szMeasure.cx = szRemain.cx+rcPadd.left-nCxFixedLenRemain;
						szMeasure.cx = szMeasure.cx<=0?0:szMeasure.cx;
					}
					if (nMinWidth!=-1
						&&szMeasure.cx<nMinWidth)
					{
						szMeasure.cx = nMinWidth;
					}
					if (nMaxWidth!=-1
						&&szMeasure.cx>nMaxWidth)
					{
						szMeasure.cx = nMaxWidth;
					}
				}
				else
				{
					if (nMinWidth!=-1
						&&szMeasure.cx<nMinWidth)
					{
						szMeasure.cx = nMinWidth;
					}
					if (nMaxWidth!=-1
						&&szMeasure.cx>nMaxWidth)
					{
						szMeasure.cx = nMaxWidth;
					}
					nCxFixedLenRemain -=szMeasure.cx;
				} 

				// 计算y
				szMeasure.cy = pChild->GetWindowRect().Height();
				if (-1 == szMeasure.cy)
				{
					szMeasure.cy =szAvailable.cy-rcPadd.bottom-rcPadd.top;
				}else if (szMeasure.cy<0)
				{
					szMeasure.cy = 0;
				}
				if (nMinHeight!=-1
					&&szMeasure.cy<nMinHeight)
				{
					szMeasure.cy = nMinHeight;
				}
				if (nMaxHeight!=-1
					&&szMeasure.cy>nMaxHeight)
				{
					szMeasure.cy = nMaxHeight;
				}

				CRect rcWindow = GetWindowRect();// 容器大小
				CRect rcArrange(iPosX+rcPadd.left,rcWindow.top+rcPadd.top,iPosX+rcPadd.left+szMeasure.cx, rcWindow.top+rcPadd.top+szMeasure.cy);
				pChild->Move(&rcArrange);
				pChild=pChild->GetWindow(GSW_NEXTSIBLING);
				iPosX += szMeasure.cx + (NULL == pChild?0:m_iChildPaddLen) + rcPadd.left+rcPadd.right;
				szRemain.cx -= szMeasure.cx + (NULL == pChild?0:m_iChildPaddLen) + rcPadd.right;
				nCxFixedLenRemain -= (NULL == pChild?0:m_iChildPaddLen) + rcPadd.left+rcPadd.right;
				 
			}
		} while (false); 
	}

	/// STableLayout---------------------------------------
	void STableLayout::UpdateChildrenPosition()
	{
		do 
		{
			// 1.获得子控件的布局空间
			CRect rcLayout = GetChildrenLayoutRect();
			if (rcLayout.IsRectEmpty())
			{
				break;
			}

			// 2.判断容器子控件是不是为空
			if (0==GetChildrenCount())
			{
				break;
			}

			if (0 == m_szItem.cx||0==m_szItem.cy)
			{
				break;
			}

			CPoint ptTab(rcLayout.left, rcLayout.top);
			bool bEnd = false;
			SWindow  *pObj = GetWindow(GSW_FIRSTCHILD);
			while (pObj)
			{
				if (!pObj->IsVisible(FALSE))
				{
					pObj=pObj->GetWindow(GSW_NEXTSIBLING);
					continue;
				}

				// 设置
				if (rcLayout.right<ptTab.x+m_szItem.cx)
				{
					ptTab.x = rcLayout.left;
					ptTab.y += m_szItem.cy;// 换行
				}
				if (ptTab.y+m_szItem.cy>rcLayout.bottom)
				{
					bEnd = true;// 结束
				}
				CRect rcArrange;
				if (bEnd)
				{
					rcArrange.SetRectEmpty();// 其余的置空吧
				}
				else
				{
					rcArrange.left = ptTab.x;
					rcArrange.top  = ptTab.y;
					rcArrange.right = rcArrange.left+m_szItem.cx;
					rcArrange.bottom = rcArrange.top+m_szItem.cy;
					ptTab.x += m_szItem.cx + m_iChildPaddLen;
				}
				pObj->Move(&rcArrange);
				pObj=pObj->GetWindow(GSW_NEXTSIBLING);
			}
		} while (false); 
		 
	}

	/// SWrapLayout----------------------------------------
	void SWrapLayout::UpdateChildrenPosition()
	{ 
		do 
		{
			// 1.获得子控件的布局空间
			CRect rcLayout = GetChildrenLayoutRect();
			if (rcLayout.IsRectEmpty())
			{
				break;
			}

			// 2.判断容器子控件是不是为空
			if (0==GetChildrenCount())
			{
				break;
			}

			// 3.计算容器可用的大小
			//SIZE szAvailable = rcLayout.Size();
			if (m_szItem.cx>0)
			{// 也可以为0，这时需要根据设定的m_nColumns来确认
				m_nColumns = rcLayout.Width()/m_szItem.cx;
			}
			if (0 == m_nColumns)
			{
				m_nColumns = 1;
			}

			int cyNeedLen = 0;
			int cxWidth = rcLayout.Width()/m_nColumns;  // Wrap项的宽度

			int cyHeight = m_szItem.cy;
			int iCount   = 0;
			CPoint ptWrap(rcLayout.left, rcLayout.top);
			int iPosX = rcLayout.left;
			SArray<SWindow *> m_ItemArray;
			SWindow *pObj = GetWindow(GSW_FIRSTCHILD);
			while (pObj)
			{
				if (!pObj->IsVisible(FALSE))
				{
					pObj=pObj->GetWindow(GSW_NEXTSIBLING);
					continue;
				}
				m_ItemArray.Add(pObj);
				pObj=pObj->GetWindow(GSW_NEXTSIBLING);
			}

			int nArrayCount = (int)m_ItemArray.GetCount();
			for (int i=0; i<nArrayCount; i++)
			{
				SWindow *&pChild = m_ItemArray[i];
				CRect rcWrapItem(ptWrap.x, ptWrap.y, ptWrap.x+cxWidth, ptWrap.y);
				if (0 == (iCount%m_nColumns))// 一行的最开始,在此计算这行的最大height
				{
					int iIndex = iCount;
					for (int j=i;j<nArrayCount; j++)
					{
						SWindow *&pLineChild = m_ItemArray[j];
						CRect rcPadd = {0,0,0,0};// pLineChild->m_pDUIXmlInfo->m_rcPadd;
						CSize szAvailable(rcWrapItem.right-rcWrapItem.left-rcPadd.left-rcPadd.right,POS_INIT);
						if (iIndex == iCount // 一行的最开始
							||0==(iIndex+1)%m_nColumns// 一行的最后
							)
						{
							szAvailable.cx -= m_iChildPaddLen/2;
						}
						else
						{
							szAvailable.cx -= m_iChildPaddLen;
						}

						int nMinHeight = -1;// pLineChild->m_pDUIXmlInfo->m_nMinHeight;
						int nMaxHeight = -1;//pLineChild->m_pDUIXmlInfo->m_nMaxHeight;
						int nMinWidth = -1;//pLineChild->m_pDUIXmlInfo->m_nMinWidth;
						int nMaxWidth = -1;//pLineChild->m_pDUIXmlInfo->m_nMaxWidth;
						if (nMinWidth!=-1&&
							szAvailable.cx<nMinWidth)
						{
							szAvailable.cx = nMinWidth;
						}
						if (nMaxWidth!=-1&&
							szAvailable.cx>nMaxWidth)
						{
							szAvailable.cx = nMaxWidth;
						}

						CSize szWrap = szAvailable; //先设置最大值
						szWrap  =pLineChild->GetDesiredSize(NULL);
						if (POS_INIT == szWrap.cy)
						{// 子项没有设置高度！,设置成默认字体高度，这个后续重构再改
							CAutoRefPtr<IFont>  pFont = SFontPool::getSingleton().GetFont(FF_DEFAULTFONT);
							
							szWrap.cy = abs(pFont->LogFont()->lfHeight) + 10;
						}
						if (nMinWidth!=-1&&
							szWrap.cx<nMinWidth)
						{
							szWrap.cx = nMinWidth;
						}
						if (nMaxWidth!=-1&&
							szWrap.cx>nMaxWidth)
						{
							szWrap.cx = nMaxWidth;
						}
						if (nMinHeight!=-1&&
							szWrap.cy<nMinHeight)
						{
							szWrap.cy = nMinHeight;
						}
						if (nMaxHeight!=-1&&
							szWrap.cy>nMaxHeight)
						{
							szWrap.cy = nMaxHeight;
						}
						int nHeightTemp = szWrap.cy+rcPadd.top+rcPadd.bottom;
						cyHeight = cyHeight>nHeightTemp?cyHeight:nHeightTemp; // 计算出这一列中最高的项做为一行的height
						if (0==(++iIndex%m_nColumns))
						{
							break;
						}
					}
				}

				CRect rcPadd = {0,0,0,0};// pChild->m_pDUIXmlInfo->m_rcPadd;
				rcWrapItem.left += rcPadd.left + m_iChildPaddLen/2;
				rcWrapItem.right -= rcPadd.right + m_iChildPaddLen/2;
				if (0 == (iCount%m_nColumns))
				{// 一行的最开始
					rcWrapItem.left -= m_iChildPaddLen/2;
				}
				if (0 == (iCount+1)%m_nColumns)
				{// 一行的最后
					rcWrapItem.right += m_iChildPaddLen/2;
				}

				int nMinHeight = -1;// pChild->m_pDUIXmlInfo->m_nMinHeight;
				int nMaxHeight = -1;//pChild->m_pDUIXmlInfo->m_nMaxHeight;
				int nMinWidth  = -1;//pChild->m_pDUIXmlInfo->m_nMinWidth;
				int nMaxWidth  = -1;//pChild->m_pDUIXmlInfo->m_nMaxWidth;
				rcWrapItem.top = ptWrap.y + rcPadd.top;
				rcWrapItem.bottom = ptWrap.y + cyHeight;
				CSize szAvailable(rcWrapItem.right-rcWrapItem.left, rcWrapItem.bottom-rcWrapItem.top);
				CSize szWrap = szAvailable;//先设置它的最大值
				szWrap  =pChild->GetDesiredSize(NULL);
				if (-1!=nMinWidth&&
					szWrap.cx<nMinWidth)
				{
					szWrap.cx = nMinWidth;
				}
				if (-1!=nMaxWidth&&
					szWrap.cx>nMaxWidth)
				{
					szWrap.cx = nMaxWidth;
				}
				if (-1!=nMinHeight&&
					szWrap.cy<nMinHeight)
				{
					szWrap.cy = nMinHeight;
				}
				if (-1!=nMaxHeight&&
					szWrap.cy>nMaxHeight)
				{
					szWrap.cy = nMaxHeight;
				}

				CRect rcArrange;
				rcArrange.left = (rcWrapItem.left+rcWrapItem.right-szWrap.cx)/2;
				rcArrange.top  = (rcWrapItem.top+rcWrapItem.bottom-szWrap.cy)/2;
				rcArrange.right = rcArrange.left + szWrap.cx;
				rcArrange.bottom = rcArrange.top + szWrap.cy;
				pChild->Move(&rcArrange);

				if (0 == (++iCount%m_nColumns))
				{
					ptWrap.x = iPosX;
					ptWrap.y += cyHeight + m_iChildPaddLen;
					cyHeight = m_szItem.cy;
				}
				else
				{
					ptWrap.x += cxWidth;
				}
				cyNeedLen = rcWrapItem.bottom-rcWrapItem.top;
			}

		} while (false); 
	}

	//--------------------------
	SSplitLayout::SSplitLayout()
	{
		m_bVert				= false;
		m_bFirstChange		= true;
		m_iFirstChildWidth  = 20;
		m_iSliderWid		= 1;
		m_iFixWid			= -1;
		m_bDrag				= false;
		m_ClrSlider = RGB(0xff, 0xff, 0xff);
	}
	BOOL SSplitLayout::CreateChildren(pugi::xml_node xmlNode)
	{
		BOOL iErr = FALSE;
		do 
		{
			iErr = __super::CreateChildren(xmlNode);
			if (2!=GetChildrenCount())
			{
				SASSERT_FMTW(0,L"内置splitter仅支持两个子窗口");
				break;
			}
		} while (false);
		return iErr;
	}

	HRESULT SSplitLayout::OnAttrVert(const SStringW& strValue, BOOL bLoading)
	{
		m_bVert = strValue != L"0";
		if (bLoading)
		{
			if (m_bVert)
			{
				SWindow *pChild = GetWindow(GSW_LASTCHILD);
				if (pChild)
					m_iFixWid = pChild->GetWindowRect().Height(); 
			}
			else
			{
				SWindow *pChild = GetWindow(GSW_LASTCHILD);
				if (pChild)
					m_iFixWid = pChild->GetWindowRect().Width();
			}
		}
		else
		{
			 
		}
		return S_FALSE;
	}

	HRESULT SSplitLayout::OnAttrSliderSkin(const SStringW& strValue, BOOL bLoading)
	{ 
		m_pSliderSkin = GETSKIN(strValue);
		if (!bLoading && m_layout.IsFitContent(PD_ALL))
		{
			RequestRelayout();
		}
		return S_FALSE;
	}

	HRESULT SSplitLayout::OnAttrFirstchange(const SStringW& strValue, BOOL bLoading)
	{
		m_bFirstChange = strValue != L"0";
		if (bLoading)
		{
			if (m_bVert)
			{
				SWindow *pChild = GetWindow(GSW_LASTCHILD);
				if (pChild)
					m_iFixWid = pChild->GetWindowRect().Height();
			}
			else
			{
				SWindow *pChild = GetWindow(GSW_LASTCHILD);
				if (pChild)
					m_iFixWid = pChild->GetWindowRect().Width();
			}
		}
		else
		{

		}
		return S_FALSE;
	}

	//
	void SSplitLayout::OnPaint(IRenderTarget *pRT)
	{
		SPainter painter;

		BeforePaint(pRT, painter);

		do
		{
			__super::OnPaint(pRT);
			if (!m_pSliderSkin && m_ClrSlider != RGB(0xFF, 0xFF, 0xFF))
			{
				break;
			}
			CRect rcSlider = GetSliderRect();
			if (m_pSliderSkin)
			{
				m_pSliderSkin->Draw(pRT, rcSlider, 0);
			}
			else if (m_ClrSlider != RGB(0xFF, 0xFF, 0xFF))
			{
				pRT->FillSolidRect(rcSlider, m_ClrSlider);
			}
		} while (false);

		AfterPaint(pRT, painter); 
	}

	void SSplitLayout::OnLButtonDown(UINT nFlags,CPoint pt)
	{
		do 
		{
			__super::OnLButtonDown(nFlags,pt);
			m_bDrag = true;
			m_ptDrag = pt;
		} while (false);
	}

	void SSplitLayout::OnLButtonUp(UINT nFlags,CPoint pt)
	{
		do 
		{
			__super::OnLButtonUp(nFlags,pt);
			m_bDrag = false;
		} while (false);
	}

	void SSplitLayout::OnMouseMove(UINT nFlags,CPoint pt)
	{
		do 
		{
			if (false == m_bDrag)
			{
				__super::OnMouseMove(nFlags,pt);
				break;
			}

			CPoint ptDiff = m_ptDrag;
			m_ptDrag      = pt;
			ptDiff        = m_ptDrag - ptDiff;
			int iDiff     = m_bVert?ptDiff.y:ptDiff.x;
			UpdateDrag(iDiff);	
		} while (false);
	}
	 
	void SSplitLayout::UpdateChildrenPosition()
	{
		do 
		{
			if (2!=GetChildrenCount())
			{
				SASSERT_FMTW(0,L"内置splitter仅支持两个子窗口");
				break;
			} 
			if (m_bVert)// 坚直
			{
				//1.第一次初始化
				if (-1 == m_iFixWid)
				{
					CRect rcFirst = GetWindowRect();
					rcFirst.bottom = rcFirst.top+m_iFirstChildWidth;
					if (GetWindowRect().bottom - rcFirst.bottom<m_iSliderWid)//1.1.剩余高度不足，补足
					{
						rcFirst.bottom = GetWindowRect().bottom - m_iSliderWid;
					}

					SWindow *pFirstChild = GetWindow(GSW_FIRSTCHILD);
					if (pFirstChild)
						pFirstChild->Move(&rcFirst);

					CRect rcSecond = GetWindowRect();
					rcSecond.top = rcFirst.bottom+m_iSliderWid;
					
					SWindow *pLastChild = GetWindow(GSW_LASTCHILD);
					if (pLastChild)
						pLastChild->Move(&rcSecond); 

					UpdateFixWidth();
				} 
				else//2.已初始化
				{
					CRect rcFirst = GetWindowRect();
					if (m_bFirstChange)
					{
						rcFirst.bottom -= m_iFixWid+m_iSliderWid;
					}
					else
					{
						rcFirst.bottom = rcFirst.top+m_iFixWid;
					}

					SWindow *pFirstChild = GetWindow(GSW_FIRSTCHILD);
					if (pFirstChild)
						pFirstChild->Move(&rcFirst);

					CRect rcSecond = GetWindowRect();
					rcSecond.top = rcFirst.bottom+m_iSliderWid;

					SWindow *pLastChild = GetWindow(GSW_LASTCHILD);
					if (pLastChild)
						pLastChild->Move(&rcSecond); 
				}
			}
			else
			{
				//1.第一次初始化
				if (-1 == m_iFixWid)
				{
					CRect rcFirst = GetWindowRect();
					rcFirst.right = rcFirst.left+m_iFirstChildWidth;
					if (GetWindowRect().right - rcFirst.right<m_iSliderWid)//1.1.剩余高度不足，补足
					{
						rcFirst.right = GetWindowRect().right - m_iSliderWid;
					}


					SWindow *pFirstChild = GetWindow(GSW_FIRSTCHILD);
					if (pFirstChild)
						pFirstChild->Move(&rcFirst);

					CRect rcSecond = GetWindowRect();
					rcSecond.left = rcFirst.right+m_iSliderWid;

					SWindow *pLastChild = GetWindow(GSW_LASTCHILD);
					if (pLastChild)
						pLastChild->Move(&rcSecond); 

					UpdateFixWidth();
				}
				else//2.已初始化
				{
					CRect rcFirst = GetWindowRect();
					if (m_bFirstChange)
					{
						rcFirst.right -= m_iFixWid+m_iSliderWid;
					}
					else
					{
						rcFirst.right = rcFirst.left+m_iFixWid;
					}

					SWindow *pFirstChild = GetWindow(GSW_FIRSTCHILD);
					if (pFirstChild)
						pFirstChild->Move(&rcFirst);
					 
					CRect rcSecond = GetWindowRect();
					rcSecond.left = rcFirst.right+m_iSliderWid;


					SWindow *pLastChild = GetWindow(GSW_LASTCHILD);
					if (pLastChild)
						pLastChild->Move(&rcSecond); 
				}
			}
		} while (false); 
	}

	BOOL SSplitLayout::OnSetCursor(const CPoint &pt)
	{
		::SetCursor(::LoadCursor(NULL,m_bVert?IDC_SIZENS:IDC_SIZEWE));
		return 0;
	}

	///
	BOOL SSplitLayout::UpdateFixWidth()
	{
		if (m_bFirstChange)// 固定大小为第二个窗口
		{
			if (m_bVert)
			{
				SWindow *pChild = GetWindow(GSW_LASTCHILD);
				if (pChild)
					m_iFixWid = pChild->GetWindowRect().Height();
			}
			else
			{
				SWindow *pChild = GetWindow(GSW_LASTCHILD);
				if (pChild)
					m_iFixWid = pChild->GetWindowRect().Width(); 
			}
		}
		else
		{
			if (m_bVert)
			{ 
				SWindow *pChild = GetWindow(GSW_FIRSTCHILD);
				if (pChild)
					m_iFixWid = pChild->GetWindowRect().Height(); 
			}
			else
			{
				SWindow *pChild = GetWindow(GSW_FIRSTCHILD);
				if (pChild)
					m_iFixWid = pChild->GetWindowRect().Width(); 
			}
		}
		if (0>m_iFixWid)
		{
			SASSERT_FMTW(0, L"固定的m_iFixWid大小竟然小于0！");
		}
		return TRUE;
	}

	void SSplitLayout::UpdateDrag(int iDiff)
	{
		do 
		{
			if (m_bFirstChange)
			{
				m_iFixWid -= iDiff; 
			}
			else
			{
				m_iFixWid += iDiff;
			}
			if (m_iFixWid<0)
			{
				m_iFixWid = 0;
			}
			int nlimit = m_bVert ? GetWindowRect().Height() - m_iSliderWid : GetWindowRect().Width() - m_iSliderWid;
			if (m_iFixWid>nlimit)
			{
				m_iFixWid = nlimit;
			}
			UpdateChildrenPosition();
			Invalidate();
		} while (false);
	}

	CRect SSplitLayout::GetSliderRect()
	{
		CRect rcSlider;
		do 
		{
			CRect rcFirstWnd;
			SWindow *pFirstChild = GetWindow(GSW_FIRSTCHILD);
			if (pFirstChild)
				rcFirstWnd = pFirstChild->GetWindowRect();

			if (m_bVert)// 竖直
			{
				rcSlider = GetWindowRect();
				rcSlider.top = rcFirstWnd.bottom;
				rcSlider.bottom = rcSlider.top+m_iSliderWid;
			}
			else// 水平
			{
				rcSlider = GetWindowRect();
				rcSlider.left = rcFirstWnd.right;
				rcSlider.right = rcSlider.left+m_iSliderWid;
			}
		} while (false);
		return rcSlider;
	}

	 
}//namespace SOUI