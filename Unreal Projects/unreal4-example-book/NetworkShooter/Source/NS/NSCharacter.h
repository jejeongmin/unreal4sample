// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "NSGameMode.h"
#include "NSCharacter.generated.h"

class UInputComponent;

UCLASS(config=Game)
class ANSCharacter : public ACharacter
{
	GENERATED_BODY()

	/** �� �޽�: 1��Ī �� (��, �ڽŸ� �� �� ����) */
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
		class USkeletalMeshComponent* FP_Mesh;

	/** �� �޽�: 1��Ī �� (�ڽŸ� �� �� ����) */
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
		class USkeletalMeshComponent* FP_Gun;

	/** �� �޽�: 3��Ī �� (�ٸ� ������Ը� ����) */
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
		class USkeletalMeshComponent* TP_Gun;

	/** First person camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class UCameraComponent* FirstPersonCameraComponent;

public:
	ANSCharacter();

public:
	/** �⺻ ȸ����, �ʴ� ��(deg/sec). �ٸ� �����ϸ��� ���� ȸ������ ������ �� �� ����. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
		float BaseTurnRate;

	/** �⺻ �÷��ٺ���/�����ٺ��� ����, �ʴ� ��(deg/sec). �ٸ� �����ϸ��� ���� ȸ������ ������ �� �� ����. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
		float BaseLookUpRate;

	/** �߻��� ������ �÷����� ���� */
	UPROPERTY(EditAnywhere, Category = Gameplay)
		class USoundBase* FireSound;

	/** �ǰ� ���� ������ �÷����� ���� */
	UPROPERTY(EditAnywhere, Category = Gameplay)
		class USoundBase* PainSound;

	/** �� �߻縦 ���� 3��Ī �ִϸ��̼� ��Ÿ�� */
	UPROPERTY(EditAnywhere, Category = Gameplay)
		class UAnimMontage* TP_FireAnimation;

	/** �� �߻縦 ���� 1��Ī �ִϸ��̼� ��Ÿ�� */
	UPROPERTY(EditAnywhere, Category = Gameplay)
		class UAnimMontage* FP_FireAnimation;

	/** �� �߻� ȿ���� ���� 1��Ī ��ƼŬ �ý��� */
	UPROPERTY(EditAnywhere, Category = Gameplay)
		class UParticleSystemComponent* FP_GunShotParticle;

	/** �� �߻� ȿ���� ���� 3��Ī ��ƼŬ �ý��� */
	UPROPERTY(EditAnywhere, Category = Gameplay)
		class UParticleSystemComponent* TP_GunShotParticle;

	/** �Ѿ��� ǥ���� ��ƼŬ �ý��� */
	UPROPERTY(EditAnywhere, Category = Gameplay)
		class UParticleSystemComponent* BulletParticle;

	// http://api.unrealengine.com/KOR/Gameplay/ForceFeedback/
	UPROPERTY(EditAnywhere, Category = Gameplay)
		class UForceFeedbackEffect* HitSuccessFeedback;

	UPROPERTY(Replicated, BlueprintReadWrite, Category = Team)
		ETeam CurrentTeam;

protected:
	class UMaterialInstanceDynamic* DynamicMat;
	class ANSPlayerState* NSPlayerState;

protected:
	void OnFire();
	void MoveForward(float Val);
	void MoveRight(float Val);
	void TurnAtRate(float Rate);
	void LookUpAtRate(float Rate);

	// ���� Ʈ���̽��� �������� �����ϱ� ���� ȣ��ȴ�
	void Fire(const FVector pos, const FVector dir);

	// APawn �������̽�
	virtual void SetupPlayerInputComponent(UInputComponent* InputComponent) override;
	virtual float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

	virtual void BeginPlay();
	virtual void PossessedBy(AController* NewController) override;

public:
	class ANSPlayerState* GetNSPlayerState();
	void SetNSPlayerState(class ANSPlayerState* newPS);
	void Respawn();

	/** Mesh1P ���������Ʈ ��ȯ **/
	FORCEINLINE class USkeletalMeshComponent* GetMesh1P() const { return FP_Mesh; }
	/** FirstPersonCameraComponent ���������Ʈ ��ȯ **/
	FORCEINLINE class UCameraComponent* GetFirstPersonCameraComponent() const { return FirstPersonCameraComponent; }


	/** ���� ���ν��� ȣ�� */
private:
	// �������� fire �׼� ����
	UFUNCTION(Server, Reliable, WithValidation)
		void ServerFire(const FVector pos, const FVector dir);

	// ��� Ŭ���̾�Ʈ�� �߻� ȿ���� �����ϴ� ��Ƽĳ��Ʈ
	UFUNCTION(NetMultiCast, unreliable)
		void MultiCastShootEffects();

	// ����� ��� Ŭ���̾�Ʈ���� ����� �����ϱ� ���� ȣ���
	UFUNCTION(NetMultiCast, unreliable)
		void MultiCastRagdoll();

	// ��Ʈ�� ���� Ŭ���̾�Ʈ���� ������ �ش�
	UFUNCTION(Client, Reliable)
		void PlayPain();

public:
	// �� ���� ����
	UFUNCTION(NetMultiCast, Reliable)
		void SetTeam(ETeam NewTeam);
};

