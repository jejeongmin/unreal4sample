// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "./Engine/Classes/Camera/CameraComponent.h"
#include "FPSProjectile.h"
#include "FPSCharacter.generated.h"

UCLASS()
class FPSPROJECT_API AFPSCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AFPSCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// 전후 이동 처리
	UFUNCTION()
		void MoveForward(float Value);

	// 좌우 이동 처리
	UFUNCTION()
		void MoveRight(float Value);

	// 키를 누르면 점프 플래그를 설정합니다.
	UFUNCTION()
		void StartJump();

	// 키를 떼면 점프 플래그를 지웁니다.
	UFUNCTION()
		void StopJump();

	// 발사 처리
	UFUNCTION()
		void Fire();

	// FPS 카메라
	UPROPERTY(VisibleAnywhere)
		UCameraComponent* FPSCameraComponent;

	// 일인칭 메시 (팔), 소유 플레이어에게만 보입니다.
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
		USkeletalMeshComponent* FPSMesh;

	// 카메라 위치에서의 총구 오프셋
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		FVector MuzzleOffset;

	// 스폰시킬 프로젝타일 클래스, EditDefaultsOnly 지정자는 프로젝타일 클래스를 블루프린트의 각 인스턴스 상에서가 아니라 블루프린트의 디폴트로만 설정할 수 있다는 뜻입니다.
	UPROPERTY(EditDefaultsOnly, Category = Projectile)
		TSubclassOf<class AFPSProjectile> ProjectileClass;

};
