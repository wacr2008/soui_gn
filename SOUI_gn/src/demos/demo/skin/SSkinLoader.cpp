#include "SSkinLoader.h"
#include "res.mgr\SResProvider.h"

using namespace SOUI;

template<>
SSkinLoader * SSingleton<SSkinLoader>::ms_Singleton = NULL;

SSkinLoader::SSkinLoader(SApplication* theApp):m_pResProvider(NULL),m_theApp(theApp)
{
	m_privateSkinPool = new SSkinPool();
	GETSKINPOOLMGR->PushSkinPool(m_privateSkinPool);
}


SSkinLoader::~SSkinLoader()
{	
}
