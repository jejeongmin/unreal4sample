// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "HybridSphere.generated.h"

UCLASS(BlueprintType)
class HELLOCODE_API AHybridSphere : public AActor
{
	GENERATED_BODY()

public:
	// �� ������ �Ӽ� �⺻���� ������
	AHybridSphere();

	// ������ ���۵ǰų� �����Ǿ��� �� ȣ��� 
	virtual void BeginPlay() override;

	// �� ������ ȣ���
	virtual void Tick(float DeltaSeconds) override;

	// ������ ����
	UFUNCTION(BlueprintNativeEvent)
	void MyOnBeginOverlap(AActor* OverlappedActor, AActor* OtherActor);
	virtual void MyOnBeginOverlap_Implementation(AActor* OverlappedActor, AActor* OtherActor);

	// ������ ���� ����
	UFUNCTION(BlueprintNativeEvent)
	void MyOnEndOverlap(AActor* OverlappedActor, AActor* OtherActor);
	virtual void MyOnEndOverlap_Implementation(AActor* OverlappedActor, AActor* OtherActor);

protected:
	UPROPERTY(Category = "Components", EditAnywhere)
		class USphereComponent* Sphere;

	UPROPERTY(Category = "Components", EditAnywhere)
		class UStaticMeshComponent* Mesh;

	UPROPERTY(Category = "Components", EditAnywhere, BlueprintReadOnly)
		class UTextRenderComponent* Text;

	UPROPERTY(Category = "Components", EditAnywhere)
		class UParticleSystemComponent* Particles;
};
