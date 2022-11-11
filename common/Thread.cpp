#include "Thread.h"
#include "log.h"
#include <pthread.h>
CThread::CThread() : m_pId(0)
{

}

CThread::~CThread()
{
    m_pId = 0;
}


int CThread::detach(pthread_t pid)
{
	int ret = pthread_detach(pid);
    if(ret != 0)
    {
        //dosomething... throw..error?
        ERROR("cancel thread failed! pid = %d", pid);
    }
	return ret;
}

int CThread::join(pthread_t pid, void** ret_status)
{
	int ret = pthread_join(pid, ret_status);
	if (ret != 0)
	{
		//dosomething... throw..error?
        ERROR("join thread failed! pid = %d", pid);
	}
	return ret;
}

int CThread::cancel(pthread_t pid)
{
	int ret = pthread_cancel(pid);
	if (ret != 0)
	{
		//dosomething... throw..error?
        ERROR("cancel thread failed! pid = %d", pid);
	}
	return ret;
}

void* CThread::start_fun(void* pObj)
{
    if(!pObj)
    {
        //throw error!
        ERROR("start_fun failed! not found pObj");
        return NULL;
    }
    CThread* pThread = (CThread*)pObj;
    pThread->run();
    return pThread;
}

int CThread::start()
{
	int ret = pthread_create(&m_pId, NULL, start_fun, (void*)this);
	if (ret != 0)
	{
		ERROR("start failed! pid = %d", m_pId);
	}
	return ret;
}

int CThread::run()
{
    INFO(" thread_id =%d start run!", m_pId);
    return 0;
}