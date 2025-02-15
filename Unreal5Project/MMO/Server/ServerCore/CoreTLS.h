#pragma once
#include <stack>

/*
thread_local은 C++11부터 도입된 스레드별(thread-local) 저장 영역을 가지는 변수 선언을 위한 키워드입니다.
즉, 각 스레드가 독립적으로 해당 변수의 복사본을 가질 수 있도록 보장합니다.

일반적인 전역 변수나 static 변수는 모든 스레드가 공유하지만, thread_local을 사용하면 각 스레드마다 개별적인 값을 유지합니다.
이렇게 하면 멀티스레드 환경에서도 동기화 없이 안전하게 사용할 수 있는 변수를 만들 수 있습니다.
*/

extern thread_local uint32				LThreadId;
extern thread_local uint64				LEndTickCount;

extern thread_local class JobQueue* LCurrentJobQueue;