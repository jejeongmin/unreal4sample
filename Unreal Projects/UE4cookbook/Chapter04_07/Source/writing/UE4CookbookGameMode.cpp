// Fill out your copyright notice in the Description page of Project Settings.

#include "UE4CookbookGameMode.h"
#include "EngineUtils.h"
#include "SingleInterfaceActor.h"


void AUE4CookbookGameMode::BeginPlay()
{
    FTransform SpawnLocation;
	// Actor 는 SpawnActor 함수를 통해서 생성된다.
    ASingleInterfaceActor* SpawnedActor = GetWorld()->SpawnActor<ASingleInterfaceActor>(ASingleInterfaceActor::StaticClass(), SpawnLocation);
	/*
		UClass 와 연관된 레퍼런스를 얻기 위해 인스턴스에 GetClass() 함수를 사용한다. UClass 레퍼런스가 필요하다.
		객체에 대한 레퍼런스는 리플렉션 데이터의 모든 데이터를 가지고 있기 때문이다.
		리플렉션 데이터는 객체의 모든 UPROPERTY 의 이름과 타입을 포함하고 객체의 상속 관계, 구현하는 모든 인터페이스의 리스트를 가지고 있다.
		결과적으로 UClass 의 ImplementsInterface() 를 호출할 수 있고 객체가 질문하는 UInterface 를 구현하고 있다면 true 를 반환한다.
	*/
    if (SpawnedActor->GetClass()->ImplementsInterface(UMyInterface::StaticClass()))
    {
        GEngine->AddOnScreenDebugMessage(-1, 1, FColor::Red, TEXT("Spawned actor implements interface!"));
    }

	/*
		TActorIterator 는 STL 반복자와 같은 반복자이다.
		TActorIterator 는 관심있는 액터의 타입을 명시한 UClass 인스턴스가 월드 안에서 동작할 것으로 가정한다.
	*/
    for (TActorIterator<AActor> It(GetWorld(), AActor::StaticClass()); It; ++It)
    {
        AActor* Actor = *It;
		/*
			UInterface 가 개발자에게 제공하는 장점 한 가지는 Cast<> 변환을 사용해 다른 종류의 객체의 컬렉션을 같은 객체의 컬렉션처럼
			공통 인터페이스로 다루게 해주는 것이다.
			즉 상속 관계에 있지 않아도 캐스팅이 가능하다.
		*/
        IMyInterface* MyInterfaceInstance = Cast<IMyInterface>(Actor);
        if (MyInterfaceInstance)
        {
            MyInterfaceInstances.Add(MyInterfaceInstance);
        }
    }

    GEngine->AddOnScreenDebugMessage(-1, 1, FColor::Red, FString::Printf(TEXT("%d actors implement the interface"), MyInterfaceInstances.Num()));
}
