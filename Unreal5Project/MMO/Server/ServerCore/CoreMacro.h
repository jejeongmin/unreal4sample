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
* __analysis_assume(expression)�� Microsoft Visual Studio�� ���� �м� ������ ���� ��Ʈ�� �����ϴ� **��ǥ�� Ȯ��(Compiler intrinsic)**�Դϴ�.
�����Ϸ����� Ư�� ����(expression)�� �׻� ��(true)�̶�� �����ϵ��� �����մϴ�.

�ַ� **���� �м���(Static Analyzer)**�� �ڵ� �帧�� �� ��Ȯ�ϰ� �м��ϵ��� �����ݴϴ�.
���� ���࿡�� ������ ���� ������, ���� ���� �м������� ���˴ϴ�.
������ Ÿ�ӿ����� ����Ǹ�, ��Ÿ�� ���ۿ��� ���� ������ ��ġ�� �ʽ��ϴ�.

���� ������ ���� �� ������ �� ���°ž�?
*/