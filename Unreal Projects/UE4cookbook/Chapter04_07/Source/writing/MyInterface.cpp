#include "MyInterface.h"

/*
	GetTestName() 은 기본 구현을 만들어야 한다. 이것 없이는 컴파일 단계에서 링크를 할 때 실패하게 된다.
	기본 구현은 unimplemented() 를 사용하면, 해당 라인의 코드가 실행될 때 debug assert 를 발생시킬 것이다.

	이것보다는 차라리 이걸 순수가상함수로 만들어서 compile 단계에서 error 를 발생시키는 것이 더 낫지 않을까?
*/
FString IMyInterface::GetTestName()
{
    unimplemented();
    return FString();
}