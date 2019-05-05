#pragma once
#include "CoreMinimal.h"
#include "MyInterface.generated.h"

/**
	UInterface 는 여러 개의 클래스들 사이에서 다형성을 나타낼 수 있도록 한 쌍의 클래스로 이루어진다.
	UInterface 는 언리얼의 클래스 마법사 안에 표시되지 않기 때문에, Visual Studio 를 통해 클래스를 수동으로 추가해야 한다.
	Interface 에서 UObject 에 해당하는 기반 클래스는 UInterface 이다.
*/
UINTERFACE()
class WRITING_API UMyInterface : public UInterface
{
        GENERATED_BODY()
};

/** */
class WRITING_API IMyInterface
{
        GENERATED_BODY()
    public:
        virtual FString GetTestName();
};