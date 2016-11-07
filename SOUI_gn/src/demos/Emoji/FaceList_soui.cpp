#include "FaceList_soui.h"
#include <string>
#include <algorithm>

namespace SOUI
{
	CFaceInfo_SOUI::CFaceInfo_SOUI(void)
	{
		m_nId = -1;
		m_nIndex = -1;
		m_strTip = _T("");
		m_strFileName = _T("");
		m_pBitmap = NULL;
		m_bSelectd = false;
	}

	CFaceInfo_SOUI::~CFaceInfo_SOUI(void)
	{
		if (m_pBitmap)
			m_pBitmap->Release();
	}

	CFaceList_SOUI::CFaceList_SOUI(const SStringT& szXmlPath) :
	m_szXmlPath(szXmlPath)
	{
		Reset();
	}

	CFaceList_SOUI::~CFaceList_SOUI(void)
	{
		Reset();
	}

	void CFaceList_SOUI::Reset()
	{
		m_nItemWidth = m_nItemHeight = 0;
		m_nZoomWidth = m_nZoomHeight = 0;
		m_nRow = m_nCol = 0;

		for (int i = 0; i < (int)m_arrFaceInfo.size(); i++)
		{
			CFaceInfo_SOUI * lpFaceInfo = m_arrFaceInfo[i];
			if (lpFaceInfo != NULL)
			{
				delete lpFaceInfo;
			}
		}
		m_arrFaceInfo.clear();
	}

	SStringT GetFileNameWithoutExtension(const SStringT& strPath)
	{
		if (strPath.IsEmpty())
			return _T("");

		SStringT szIndex = strPath;
		for (int nPos = (int)szIndex.GetLength() - 1; nPos >= 0; --nPos)
		{
			TCHAR cChar = szIndex[nPos];
			if (_T('\\') == cChar || _T('/') == cChar)
			{
				szIndex = szIndex.Right(szIndex.GetLength() - nPos - 1);
				break;
			}
		}

		int nPos = szIndex.Find(_T('.'));
		if (nPos != -1)
			szIndex = szIndex.Left(nPos);

		return szIndex;
	}

	BOOL CFaceList_SOUI::LoadConfigFile(SStringT szPath)
{
		pugi::xml_document xmlDoc;
		pugi::xml_node xmlNode, xmlSubNode;

		Reset();

		pugi::xml_parse_result result = xmlDoc.load_file(m_szXmlPath, pugi::parse_default, pugi::encoding_utf8);
		if (result.status != pugi::status_ok)
			return FALSE;

		xmlNode = xmlDoc.child(L"faceconfig");
		if (xmlNode)
		{
			m_nItemWidth = xmlNode.attribute(L"item_width").as_int();
			m_nItemHeight = xmlNode.attribute(L"item_height").as_int();
			m_nZoomWidth = xmlNode.attribute(L"zoom_width").as_int();
			m_nZoomHeight = xmlNode.attribute(L"zoom_height").as_int();
			m_nRow = xmlNode.attribute(L"row").as_int();
			m_nCol = xmlNode.attribute(L"col").as_int();

			xmlSubNode = xmlNode.child(L"face");
			while (xmlSubNode)
			{
				CFaceInfo_SOUI * lpFaceInfo = new CFaceInfo_SOUI;
				if (lpFaceInfo != NULL)
				{
					lpFaceInfo->m_nId = xmlSubNode.attribute(L"id").as_int();
					lpFaceInfo->m_strTip = S_CW2T(xmlSubNode.attribute(L"tip").value());
					lpFaceInfo->m_strFileName = S_CW2T(xmlSubNode.attribute(L"file").value());
					SStringT strIndex = GetFileNameWithoutExtension(lpFaceInfo->m_strFileName);
					lpFaceInfo->m_nIndex = atoi(S_CT2A(strIndex));
					GETRENDERFACTORY->CreateBitmap(&lpFaceInfo->m_pBitmap);
					if (lpFaceInfo->m_nId < 1000)
						lpFaceInfo->m_pBitmap->LoadFromFile(SApplication::getSingleton().GetAppDir() + _T("\\Resource\\") + lpFaceInfo->m_strFileName);
					else
						lpFaceInfo->m_pBitmap->LoadFromFile(szPath + _T("\\") + lpFaceInfo->m_strFileName);
					m_arrFaceInfo.push_back(lpFaceInfo);
				}
				xmlSubNode = xmlSubNode.next_sibling();
			}
		}
		return TRUE;
	}

	CFaceInfo_SOUI * CFaceList_SOUI::GetFaceInfo(int nIndex)
	{
		if (nIndex >= 0 && nIndex < (int)m_arrFaceInfo[nIndex])
			return m_arrFaceInfo[nIndex];
		else
			return NULL;
	}

	CFaceInfo_SOUI * CFaceList_SOUI::GetFaceInfoById(int nFaceId)
	{
		for (int i = 0; i < (int)m_arrFaceInfo.size(); i++)
		{
			CFaceInfo_SOUI * lpFaceInfo = m_arrFaceInfo[i];
			if (lpFaceInfo != NULL && lpFaceInfo->m_nId == nFaceId)
				return lpFaceInfo;
		}

		return NULL;
	}

	CFaceInfo_SOUI * CFaceList_SOUI::GetFaceInfoByIndex(int nFaceIndex)
	{
		for (int i = 0; i < (int)m_arrFaceInfo.size(); i++)
		{
			CFaceInfo_SOUI * lpFaceInfo = m_arrFaceInfo[i];
			if (lpFaceInfo != NULL && lpFaceInfo->m_nIndex == nFaceIndex)
				return lpFaceInfo;
		}

		return NULL;
	}

	CFaceInfo_SOUI * CFaceList_SOUI::GetFaceInfoByTip(SStringT nTip)
	{
		for (int i = 0; i < (int)m_arrFaceInfo.size(); i++)
		{
			CFaceInfo_SOUI * lpFaceInfo = m_arrFaceInfo[i];
			SStringT str = lpFaceInfo->m_strTip;
			if (lpFaceInfo != NULL)
			{
				if (strcmp(S_CT2A(str), S_CT2A(nTip)) == 0)
				{
					return lpFaceInfo;
				}
			}
		}

		return NULL;
	}

	bool CFaceList_SOUI::AddEmoji(std::vector<SStringT> vecNewEmojiPath, SStringT szPath)
	{
		std::vector<SStringT>::iterator it = vecNewEmojiPath.begin();
		while (it != vecNewEmojiPath.end())
		{
			CFaceInfo_SOUI* info = new CFaceInfo_SOUI;
			info->m_nId = m_arrFaceInfo.size() + 1000;
			info->m_strFileName = *it;
			GETRENDERFACTORY->CreateBitmap(&info->m_pBitmap);
			info->m_pBitmap->LoadFromFile(szPath + _T("\\") + info->m_strFileName);

			m_arrFaceInfo.push_back(info);
			++it;
		}

		SaveXml();
		return true;
	}

	SStringT CFaceList_SOUI::GetFileName(SStringT path)
	{
		int pos = path.ReverseFind(_T('\\'));
		return path.Right(path.GetLength() - pos - 1);
	}

	bool CFaceList_SOUI::SaveXml()
	{
		ReSortList();

		pugi::xml_document xmlDoc;
		xmlDoc.load_file(m_szXmlPath, pugi::parse_default, pugi::encoding_utf8);

		pugi::xml_node faceconfig = xmlDoc.child(L"faceconfig");
		if (!faceconfig)
		{
			faceconfig = xmlDoc.append_child(L"faceconfig");
			faceconfig.append_attribute(L"row").set_value(m_nRow);
			faceconfig.append_attribute(L"col").set_value(m_nCol);
			faceconfig.append_attribute(L"item_width").set_value(m_nItemWidth);
			faceconfig.append_attribute(L"item_height").set_value(m_nItemHeight);
			faceconfig.append_attribute(L"zoom_width").set_value(m_nZoomWidth);
			faceconfig.append_attribute(L"zoom_height").set_value(m_nZoomHeight);
		}

		pugi::xml_node del = faceconfig.child(L"face");
		while (del)
		{
			faceconfig.remove_child(del);
			del = faceconfig.child(L"face");
		}

		pugi::xml_node face;
		std::vector<CFaceInfo_SOUI *>::iterator it = m_arrFaceInfo.begin();
		while (it != m_arrFaceInfo.end())
		{
			face = faceconfig.append_child(L"face");
			face.append_attribute(L"id").set_value((*it)->m_nId);
			SStringT path = (*it)->m_strFileName;
			face.append_attribute(L"file").set_value(S_CT2W(path));
			++it;
		}

		xmlDoc.save_file(m_szXmlPath, L"\t", pugi::format_default, pugi::encoding_utf8);
		return true;
	}

	void CFaceList_SOUI::ReSortList()
	{
		for (unsigned int i = 0; i < m_arrFaceInfo.size(); ++i)
		{
			if (m_arrFaceInfo.at(i)->m_nId != (1000 + (int)i))
				m_arrFaceInfo.at(i)->m_nId = (1000 + (int)i);
		}
	}

	bool CFaceList_SOUI::GetDelList(std::vector<int>& veclist)
	{
		std::vector<CFaceInfo_SOUI*>::iterator it = m_arrFaceInfo.begin();
		while (it != m_arrFaceInfo.end())
		{
			if ((*it)->m_bSelectd)
			{
				veclist.push_back((*it)->m_nId);
			}
			++it;
		}
		return true;
	}

	bool CFaceList_SOUI::RemoveFaceVec(std::vector<int> vecDel)
	{
		std::vector<CFaceInfo_SOUI *>::iterator it = m_arrFaceInfo.begin();
		while (it != m_arrFaceInfo.end())
		{
			std::vector<int>::iterator itDel = std::find(vecDel.begin(), vecDel.end(), (*it)->m_nId);
			if (itDel != vecDel.end())
			{
				it = m_arrFaceInfo.erase(it);
			}
			else
			{
				++it;
			}
		}

		SaveXml();
		return true;
	}
}
