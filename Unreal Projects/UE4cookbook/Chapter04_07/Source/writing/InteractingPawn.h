// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/DefaultPawn.h"
#include "InteractingPawn.generated.h"

/**
	TryInteract 는 모든 폰이 가진 일반적인 컨트롤러를 캐스팅해 PlayerController 의 참조를 얻어온다.
	PlayerCameraManager 는 PlayerController 를 찾아서 플레이어 카메라의 현재 위치와 회전을 접근할 수 있다.
	카메라의 위치를 사용해 카메라 위치에서 World::SweepSingleByObjectType 를 통해서 얻은 전방 방향으로 100 유닛의 시작과 끝점을 만든다.
	이 함수는 많은 파라메터를 취한다. 어떤 객체가 충돌 검출을 통해 충돌했을 때 정보를 함수가 반환하도록 허락받은 HitResult 는 변수다.
	CollisionObjectQueryParams 은 동적이거나 정적, 또는 모두 중에 흥미있는 것을 명시할 수 있도록 해준다.
	MakeSphere 함수 안에 Shape 을 전달해 구형 충돌 검출을 달성한다.
	구형충돌 검출은 직선 형태보다 객체를 실린더 모양으로 정의해 이상하게 판정된다고 인식하게 되는것을 줄여줄 수 있다.
	플레이어들이 당신의 객체를 정확하게 보지 못할 수 있으므로, 구의 반경을 적당하게 조절할 수 있다.
	마지막 파라미터는 SweepSingleByObjectType 인데, 충돌 검출의 이름을 지정하는 구조체로 복잡한 충돌 지오메트리와 충돌하는 경우를 지정할 수 있고
	가장 중요한 것은 추적을 할 때 무시되기 원하는 오브젝트를 지정할 수 있게 해준다.
	HitResult 가 추적이 완료된 후에 액터를 포함한다면 해당 액터가 인터페이스 구현을 했는지 체크할 수 있고
	가장 중요한 것은 추적을 할 때 무시되기 원하는 오브젝트를 지정할 수 있게 해준다.
 */
UCLASS()
class WRITING_API AInteractingPawn : public ADefaultPawn
{
        GENERATED_BODY()
    public:


        void TryInteract();

    private:
        virtual void SetupPlayerInputComponent(UInputComponent* InInputComponent) override;

};
