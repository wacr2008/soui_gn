#pragma once

#include <vector>

namespace SOUI
{

	class CFaceInfo_SOUI
	{
	public:
		CFaceInfo_SOUI(void);
		~CFaceInfo_SOUI(void);
		void ChangeSelectStatus()
		{
			m_bSelectd = !m_bSelectd;
		}

	public:
		int m_nId;
		int m_nIndex;
		SStringT m_strTip;
		SStringT m_strFileName;
		IBitmap* m_pBitmap;
		bool m_bSelectd;
	};

	class CFaceList_SOUI
	{
	public:
		CFaceList_SOUI(const SStringT& szXmlPath);
		~CFaceList_SOUI(void);

	public:
		void Reset();
		BOOL LoadConfigFile(SStringT szPath = _T(""));
		CFaceInfo_SOUI * GetFaceInfo(int nIndex);
		CFaceInfo_SOUI * GetFaceInfoById(int nFaceId);
		CFaceInfo_SOUI * GetFaceInfoByIndex(int nFaceIndex);
		CFaceInfo_SOUI * GetFaceInfoByTip(SStringT nTip);
		bool RemoveFaceVec(std::vector<int> vecDel);
		bool AddEmoji(std::vector<SStringT> vecNewEmojiPath, SStringT szPath);
		SStringT GetFileName(SStringT path);
		bool SaveXml();
		void ReSortList();
		bool GetDelList(std::vector<int>& veclist);

	public:
		std::vector<CFaceInfo_SOUI *> m_arrFaceInfo;

	private:
		int m_nItemWidth, m_nItemHeight;
		int m_nZoomWidth, m_nZoomHeight;
		int m_nRow, m_nCol;
		SStringT m_szXmlPath;
	};
}