//////////////////////////////////////////////////////////////////////////
// @file: SRWLock.h
// @description: wraper srwlock

#include <process.h>
namespace MultiThreads
{
	namespace detail
	{
#define THREADID_NULL 0
		typedef unsigned long                 threadID;
		typedef unsigned __int64 UINT_PTR, *  PUINT_PTR;
		typedef unsigned int uint32;
		enum eLOCK_TYPE
		{
			eLockType_CRITICAL_SECTION,
			eLockType_SRW,
			eLockType_MUTEX
		};


		//////////////////////////////////////////////////////////////////////////
		//////////////////////////////////////////////////////////////////////////
		//! From winnt.h.
		// Since we are not allowed to include windows.h while being included from platform.h and there seems to be no good way to include the
		// required windows headers directly; without including a lot of other header, define a 1:1 copy of the required primitives defined in winnt.h.
		//////////////////////////////////////////////////////////////////////////

		// 临界区
		//////////////////////////////////////////////////////////////////////////
		struct MT_CRITICAL_SECTION // From winnt.h
		{
			void*          DebugInfo;
			long           LockCount;
			long           RecursionCount;
			void*          OwningThread;
			void*          LockSemaphore;
			unsigned long* SpinCount;  //!< Force size on 64-bit systems when packed.
		};

		// 读写锁
		//////////////////////////////////////////////////////////////////////////
		struct MT_SRWLOCK // From winnt.h
		{
			MT_SRWLOCK();
			void* SRWLock_;
		};

		// 条件变量
		//////////////////////////////////////////////////////////////////////////
		struct MT_Condition_Variable // From winnt.h
		{
			MT_Condition_Variable();
			void* condVar_;
		};

		// wrapper SRWLock
		class MTLock_SRWLock
		{
		public:
			static const eLOCK_TYPE s_value = eLockType_SRW;
			friend class MTConditionVariable;
		public:
			//MTLock_SRWLock() = default;
			void Lock();
			void UnLock();
			bool TryLock();

			void LockShared();
			void UnLockShared();
			bool TryLockShared();

		private:
			MTLock_SRWLock(const MTLock_SRWLock&) = delete;
			MTLock_SRWLock& operator=(const MTLock_SRWLock&) = delete;

		private:
			MT_SRWLOCK m_lock;
		};

		// 递归读写锁
		//////////////////////////////////////////////////////////////////////////
		// SRW Lock (Slim Reader/Writer Lock)
		// Faster + lighter than CriticalSection. Also only enters into kernel mode if contended.
		// Cannot be shared between processes.
		class MTLock_SRWLock_Recursive
		{
		public:
			static const eLOCK_TYPE s_value = eLockType_SRW;
			friend class MTConditionVariable;

		public:
			MTLock_SRWLock_Recursive():m_recurseCounter(0),m_exclusiveOwningThreadId(THREADID_NULL){}

			void Lock();
			void UnLock();
			bool TryLock();

			// Deprecated

#ifdef _DEBUG
			bool IsLocked()
			{
				return m_exclusiveOwningThreadId == GetCurrentThreadId();
			}
#endif 

		private:
			MTLock_SRWLock m_lock;
			unsigned int m_recurseCounter;

			// Due to its semantics, this member can be accessed in an unprotected manner,
			// but only for comparison with the current tid.
			threadID        m_exclusiveOwningThreadId;
		};

		//////////////////////////////////////////////////////////////////////////
		// Critical section
		// Faster then WinMutex as it only enters into kernel mode if contended.
		// Cannot be shared between processes.
		class MTLock_CriticalSection
		{

		public:
			static const eLOCK_TYPE s_value = eLockType_CRITICAL_SECTION;
			friend class MT_Condition_Variable;

		public:
			MTLock_CriticalSection();
			~MTLock_CriticalSection();

			void Lock();
			void Unlock();
			bool TryLock();

#ifdef _DEBUG
			bool IsLocked()
			{
				return m_lock.RecursionCount > 0 && (UINT_PTR)m_lock.OwningThread == GetCurrentThreadId();
			}
#endif 

		private:
			MTLock_CriticalSection(const MTLock_CriticalSection&) = delete;
			MTLock_CriticalSection& operator=(const MTLock_CriticalSection&) = delete;

		private:
			MT_CRITICAL_SECTION m_lock;
		};

		//////////////////////////////////////////////////////////////////////////
		// WinMutex: (slow)
		// Calls into kernel even when not contended.
		// A named mutex can be shared between different processes.
		class MTLock_WinMutex
		{
		public:
			static const eLOCK_TYPE s_value = eLockType_MUTEX;

			MTLock_WinMutex();
			~MTLock_WinMutex();

			void Lock();
			void Unlock();
			bool TryLock();
#ifdef _DEBUG
			//! Deprecated: do not use this function - its return value might already be wrong the moment it is returned.
			bool IsLocked()
			{
				if (TryLock())
				{
					Unlock();
					return true;
				}
				else
				{
					return false;
				}
			}
#endif
		private:
			MTLock_WinMutex(const MTLock_WinMutex&) = delete;
			MTLock_WinMutex& operator=(const MTLock_WinMutex&) = delete;

		private:
			void* m_lock;
		};
	}
}

//////////////////////////////////////////////////////////////////////////
/////////////////////////    DEFINE LOCKS    /////////////////////////////
//////////////////////////////////////////////////////////////////////////

enum MTLockType
{
	MTLOCK_FAST      = 1,  //!< A fast potentially (non-recursive) mutex.
	MTLOCK_RECURSIVE = 2,  //!< A recursive mutex.
};

//! Primitive locks and conditions.
//! Primitive locks are represented by instance of class CryLockT<Type>.
template<MTLockType Type> class MTLockT
{
	/* Unsupported lock type. */
};


template<> class MTLockT<MTLOCK_RECURSIVE> : public MultiThreads::detail::MTLock_SRWLock_Recursive
{

};

template<> class MTLockT<MTLOCK_FAST> : public MultiThreads::detail::MTLock_SRWLock
{
};


typedef MultiThreads::detail::MTLock_SRWLock_Recursive	MTMutex;
typedef MultiThreads::detail::MTLock_SRWLock			MTMutexFast; // Not recursive

//////////////////////////////////////////////////////////////////////////
// Typedefs.
//////////////////////////////////////////////////////////////////////////
typedef MTLockT<MTLOCK_RECURSIVE> MTCriticalSection;
typedef MTLockT<MTLOCK_FAST>      MTCriticalSectionNonRecursive;

//////////////////////////////////////////////////////////////////////////
//! MTEvent represent a synchronization event.
class MTEvent
{
public:
	MTEvent();
	~MTEvent();

	//! Reset the event to the unsignalled state.
	void Reset();

	//! Set the event to the signalled state.
	void Set();

	//! Access a HANDLE to wait on.
	void* GetHandle() const { return m_handle; };

	//! Wait indefinitely for the object to become signalled.
	void Wait() const;

	//! Wait, with a time limit, for the object to become signalled.
	bool Wait(const uint32 timeoutMillis) const;

private:
	MTEvent(const MTEvent&);
	MTEvent& operator=(const MTEvent&);

private:
	void* m_handle;
};
typedef MTEvent CryEventTimed;


//////////////////////////////////////////////////////////////////////////
class MTConditionVariable
{
public:
	MTConditionVariable() = default;
	void Wait(MTMutex& lock);
	void Wait(MTMutexFast& lock);
	bool TimedWait(MTMutex& lock, uint32 millis);
	bool TimedWait(MTMutexFast& lock, uint32 millis);
	void NotifySingle();
	void Notify();

private:
	MTConditionVariable(const MTConditionVariable&);
	MTConditionVariable& operator=(const MTConditionVariable&);

private:
	MultiThreads::detail::MT_Condition_Variable m_condVar;
};


//////////////////////////////////////////////////////////////////////////
//! AutoCriticalSection implements a helper class to automatically.
//! lock critical section in constructor and release on destructor.
template<class LockClass> class MTAutoLock
{
public:
	MTAutoLock() = delete;
	MTAutoLock(const MTAutoLock<LockClass>&) = delete;
	MTAutoLock<LockClass>& operator=(const MTAutoLock<LockClass>&) = delete;

	MTAutoLock(LockClass& Lock) : m_pLock(&Lock) { m_pLock->Lock(); }
	MTAutoLock(const LockClass& Lock) : m_pLock(const_cast<LockClass*>(&Lock)) { m_pLock->Lock(); }
	~MTAutoLock() { m_pLock->Unlock(); }
private:
	LockClass* m_pLock;
};


//! CryOptionalAutoLock implements a helper class to automatically.
//! Lock critical section (if needed) in constructor and release on destructor.
template<class LockClass> class MTOptionalAutoLock
{

private:
	LockClass*	m_lock;
	bool		m_bLockAcquired;

	MTOptionalAutoLock();
	MTOptionalAutoLock(const MTOptionalAutoLock&) = delete;
	MTOptionalAutoLock<LockClass>& operator = (const MTOptionalAutoLock<LockClass>&) = delete;

public:
	MTOptionalAutoLock(LockClass& lock, bool aquireLock): m_lock(&Lock), m_bLockAcquired(false)
	{
		if(aquireLock)
		{
			Acquire();
		}
	}

	~MTOptionalAutoLock()
	{
		Release();
	}

	void Release()
	{
		if (m_bLockAcquired)
		{
			m_lock->Unlock();
			m_bLockAcquired = false;
		}
	}

	void Acquire()
	{
		if (!m_bLockAcquired)
		{
			m_lock->Lock();
			m_bLockAcquired = true;
		}
	}
};

//! Auto critical section is the most commonly used type of auto lock.
typedef MTAutoLock<MTCriticalSection>             MTAutoCriticalSection;
typedef MTAutoLock<MTCriticalSectionNonRecursive> MTAutoCriticalSectionNoRecursive;

#define AUTO_LOCK_T(Type, lock) PREFAST_SUPPRESS_WARNING(6246); MTAutoLock<Type> __AutoLock(lock)
#define AUTO_LOCK(lock)         AUTO_LOCK_T(MTCriticalSection, lock)
#define AUTO_LOCK_CS(csLock)    MTAutoCriticalSection __AL__ ## csLock(csLock)
