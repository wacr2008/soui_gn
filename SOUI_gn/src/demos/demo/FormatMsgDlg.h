#pragma once

namespace SOUI
{
    class CFormatMsgDlg : public SHostDialog
    {
    public:
        CFormatMsgDlg(void);
        ~CFormatMsgDlg(void);

        void OnOK();

        SStringT m_strMsg;  //消息XML
        int      m_nRepeat; //重复次数

        EVENT_MAP_DECL()

    };

}
