#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyInterface.h"
#include "SingleInterfaceActor.generated.h"

/*
	SingleInterfaceActor 가 UObject 의 2개의 복사본을 상속받지 않기 위해 IMyInterface 에서 상속 받는다.
*/
UCLASS()
class WRITING_API ASingleInterfaceActor : public AActor, public IMyInterface
{
        GENERATED_BODY()
    public:
        virtual FString GetTestName() override;
};