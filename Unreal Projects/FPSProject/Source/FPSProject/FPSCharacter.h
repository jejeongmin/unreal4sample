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

	// ���� �̵� ó��
	UFUNCTION()
		void MoveForward(float Value);

	// �¿� �̵� ó��
	UFUNCTION()
		void MoveRight(float Value);

	// Ű�� ������ ���� �÷��׸� �����մϴ�.
	UFUNCTION()
		void StartJump();

	// Ű�� ���� ���� �÷��׸� ����ϴ�.
	UFUNCTION()
		void StopJump();

	// �߻� ó��
	UFUNCTION()
		void Fire();

	// FPS ī�޶�
	UPROPERTY(VisibleAnywhere)
		UCameraComponent* FPSCameraComponent;

	// ����Ī �޽� (��), ���� �÷��̾�Ը� ���Դϴ�.
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
		USkeletalMeshComponent* FPSMesh;

	// ī�޶� ��ġ������ �ѱ� ������
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		FVector MuzzleOffset;

	// ������ų ������Ÿ�� Ŭ����, EditDefaultsOnly �����ڴ� ������Ÿ�� Ŭ������ ��������Ʈ�� �� �ν��Ͻ� �󿡼��� �ƴ϶� ��������Ʈ�� ����Ʈ�θ� ������ �� �ִٴ� ���Դϴ�.
	UPROPERTY(EditDefaultsOnly, Category = Projectile)
		TSubclassOf<class AFPSProjectile> ProjectileClass;

};