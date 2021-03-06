#ifndef __GPU_BLAST_MULTI_GPU_UTILS_H__
#define __GPU_BLAST_MULTI_GPU_UTILS_H__

#include <algo/blast/gpu_blast/thread_work_queue.hpp>
//
#include <map>
#include <queue>
#include <string>

#ifdef WIN32
#include <windows.h>
#else
#include <pthread.h>
#endif

using namespace std;


class GpuObject
{
public:
	GpuObject(){};
	~GpuObject(){};
	virtual void CreateData(){};
protected:
	
private:
};

class ThreadLock;

struct GpuData 
{
	GpuObject* m_global;
	GpuObject* m_local;
	//void*		m_pairs;
	//cudaStream_t stream;
};

typedef map<int, GpuData*> GPUDataMapType;
typedef pair<int, GpuData*>	GPUDataMapPairType;

typedef map<unsigned long, int> ThreadGPUMapType;
typedef pair<unsigned long, int> ThreadGPUMapPairType;

class GpuBlastMultiGPUsUtils
{
	GpuBlastMultiGPUsUtils();
	~GpuBlastMultiGPUsUtils();

	GpuBlastMultiGPUsUtils(const GpuBlastMultiGPUsUtils&);
	GpuBlastMultiGPUsUtils& operator =(GpuBlastMultiGPUsUtils);

public:

	static GpuBlastMultiGPUsUtils & instance()
	{
		static GpuBlastMultiGPUsUtils s;
		return s;
	}

	int InitGPUs(bool use_gpu, int gpu_id);
	void ReleaseGPUs();

	void ThreadFetchGPU(int & gpu_id);
	void ThreadReplaceGPU();

	GpuData* GetCurrentThreadGPUData();
protected:
	
private:
	int i_GPU_N;
	queue<int> q_gpu_ids;
	ThreadGPUMapType mt_GPU;

	bool b_useGpu;
	GPUDataMapType m_GpuData;
	ThreadLock mt_lock;

	int i_num_limited;
};

extern GpuBlastMultiGPUsUtils& BlastMGPUUtil;


#endif //__GPU_BLAST_MULTI_GPU_UTILS_H__