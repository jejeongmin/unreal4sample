// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "PostEditChangePropertyActor.generated.h"

UCLASS()
class CHAPTER8_API APostEditChangePropertyActor : public AStaticMeshActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APostEditChangePropertyActor();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	UPROPERTY(EditAnywhere)
		bool ShowStaticMesh;

	/*
		�����̳ʰ� ������ ��ġ�� ������ property �� �����ϸ� ������ �ùķ��̼��ϰų� ����� �� �� �ƴ�
		��� �ð������� ����� ����� ǥ���ϴ� ���� �߿��ϴ�.

		���� ���� �г��� ����� ��������� �����ϸ� ���� ���� property �� ������ �� �ִ� Ŭ������ �ν��Ͻ���
		�����ϴ� PostEditChangeProperty ��� Ư�� �̺�Ʈ�� �߻��Ѵ�.
	*/
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;


	

};
