// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine/StaticMeshActor.h"
#include "OnConstructionActor.generated.h"

/**
 * 
 */
UCLASS()
class CHAPTER8_API AOnConstructionActor : public AStaticMeshActor
{
	GENERATED_BODY()

public:

		AOnConstructionActor();

		/*
			블루프린트에서 Construction Script 는 에디터 뷰포트에서 드래그되거나 세부 정보 패널에 직접 입력돼 변경된 경우에도
			연결된 객체에서 property 가 변경될 때마다 실행되는 이벤트 그래프이다.

			Construction scripts 를 이용하면 해당 객체가 새 위치를 기반으로 '재빌드'되거나 사용자가 선택한 옵션을 기반으로
			포함된 컴포넌트를 변경할 수 있다.

			언리얼 엔진에서 C++ 코딩할 때 같은 개념은 OnConstruction 함수이다.

			단 C++ class actor 를 에디터에서 이동하는 경우에는 OnConstruction 이 실행되지 않는다.
			이유는 AActor::PostEditorMove 함수 구현을 보면 알 수 있는데
			클래스가 blueprint 기반일 경우에만 construction scripts 와 OnConstruction 을 다시 실행함을 알 수 있을 것이다.
		*/
		virtual void OnConstruction(const FTransform& Transform) override;
		UPROPERTY(EditAnywhere)
			bool ShowStaticMesh;
};
