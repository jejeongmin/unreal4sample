#pragma once

#define OUT

#define NAMESPACE_BEGIN(name)	namespace name {
#define NAMESPACE_END			}

/*---------------
	  Lock
---------------*/

#define USE_MANY_LOCKS(count)	mutex _locks[count];
#define USE_LOCK				USE_MANY_LOCKS(1)
#define	WRITE_LOCK_IDX(idx)		lock_guard<mutex> lockGuard_##idx(_locks[idx]);
#define WRITE_LOCK				WRITE_LOCK_IDX(0)

/*---------------
	  Crash
---------------*/

#define CRASH(cause)						\
{											\
	uint32* crash = nullptr;				\
	__analysis_assume(crash != nullptr);	\
	*crash = 0xDEADBEEF;					\
}

#define ASSERT_CRASH(expr)			\
{									\
	if (!(expr))					\
	{								\
		CRASH("ASSERT_CRASH");		\
		__analysis_assume(expr);	\
	}								\
}

/*
* __analysis_assume(expression)는 Microsoft Visual Studio의 정적 분석 도구를 위한 힌트를 제공하는 **비표준 확장(Compiler intrinsic)**입니다.
컴파일러에게 특정 조건(expression)이 항상 참(true)이라고 가정하도록 지시합니다.

주로 **정적 분석기(Static Analyzer)**가 코드 흐름을 더 정확하게 분석하도록 도와줍니다.
실제 실행에는 영향을 주지 않으며, 오직 정적 분석에서만 사용됩니다.
컴파일 타임에서만 적용되며, 런타임 동작에는 전혀 영향을 미치지 않습니다.

별로 장점도 없는 것 같은데 왜 쓰는거야?
*/