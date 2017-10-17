#include "activex/SAxUtil.h"
 
HRESULT MinimumIDispatchImpl::GetTypeInfoCount(UINT *pctinfo)
{
    *pctinfo = 0;
     return S_OK;
}


HRESULT MinimumIDispatchImpl::GetTypeInfo(UINT /*iTInfo*/, LCID /*lcid*/, ITypeInfo** /*ppTInfo*/)
{
    return E_NOTIMPL;
}

 
HRESULT MinimumIDispatchImpl::GetIDsOfNames(REFIID /*riid*/, LPOLESTR* /*rgszNames*/,
                             UINT /*cNames*/, LCID /*lcid*/, DISPID* /*rgDispId*/)
{
    return E_NOTIMPL;
}

HRESULT MinimumIDispatchImpl::Invoke(DISPID /*dispIdMember*/, REFIID /*riid*/, LCID /*lcid*/, WORD /*wFlags*/,
                      DISPPARAMS* /*pDispParams*/, VARIANT* /*pVarResult*/, EXCEPINFO* /*pExcepInfo*/,
                      UINT* /*puArgErr*/)
{
    // check 'OleCtl.h' for list of DISPID_*
        return E_NOTIMPL;
}

      