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

	/** 폰 메시: 1인칭 뷰 (팔, 자신만 볼 수 있음) */
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
		class USkeletalMeshComponent* FP_Mesh;

	/** 건 메시: 1인칭 뷰 (자신만 볼 수 있음) */
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
		class USkeletalMeshComponent* FP_Gun;

	/** 건 메시: 3인칭 뷰 (다른 사람에게만 보임) */
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
		class USkeletalMeshComponent* TP_Gun;

	/** First person camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class UCameraComponent* FirstPersonCameraComponent;

public:
	ANSCharacter();

public:
	/** 기본 회전율, 초당 도(deg/sec). 다른 스케일링은 최종 회전율에 영향을 줄 수 있음. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
		float BaseTurnRate;

	/** 기본 올려다보기/내려다보기 비율, 초당 도(deg/sec). 다른 스케일링은 최종 회전율에 영향을 줄 수 있음. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
		float BaseLookUpRate;

	/** 발사할 때마다 플레이할 사운드 */
	UPROPERTY(EditAnywhere, Category = Gameplay)
		class USoundBase* FireSound;

	/** 피격 당할 때마다 플레이할 사운드 */
	UPROPERTY(EditAnywhere, Category = Gameplay)
		class USoundBase* PainSound;

	/** 총 발사를 위한 3인칭 애니메이션 몽타주 */
	UPROPERTY(EditAnywhere, Category = Gameplay)
		class UAnimMontage* TP_FireAnimation;

	/** 총 발사를 위한 1인칭 애니메이션 몽타주 */
	UPROPERTY(EditAnywhere, Category = Gameplay)
		class UAnimMontage* FP_FireAnimation;

	/** 총 발사 효과를 위한 1인칭 파티클 시스템 */
	UPROPERTY(EditAnywhere, Category = Gameplay)
		class UParticleSystemComponent* FP_GunShotParticle;

	/** 총 발사 효과를 위한 3인칭 파티클 시스템 */
	UPROPERTY(EditAnywhere, Category = Gameplay)
		class UParticleSystemComponent* TP_GunShotParticle;

	/** 총알을 표현할 파티클 시스템 */
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

	// 레이 트레이스를 서버에서 수행하기 위해 호출된다
	void Fire(const FVector pos, const FVector dir);

	// APawn 인터페이스
	virtual void SetupPlayerInputComponent(UInputComponent* InputComponent) override;
	virtual float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

	virtual void BeginPlay();
	virtual void PossessedBy(AController* NewController) override;

public:
	class ANSPlayerState* GetNSPlayerState();
	void SetNSPlayerState(class ANSPlayerState* newPS);
	void Respawn();

	/** Mesh1P 서브오브젝트 반환 **/
	FORCEINLINE class USkeletalMeshComponent* GetMesh1P() const { return FP_Mesh; }
	/** FirstPersonCameraComponent 서브오브젝트 반환 **/
	FORCEINLINE class UCameraComponent* GetFirstPersonCameraComponent() const { return FirstPersonCameraComponent; }


	/** 원격 프로시져 호출 */
private:
	// 서버에서 fire 액션 수행
	UFUNCTION(Server, Reliable, WithValidation)
		void ServerFire(const FVector pos, const FVector dir);

	// 모든 클라이언트가 발사 효과를 실행하는 멀티캐스트
	UFUNCTION(NetMultiCast, unreliable)
		void MultiCastShootEffects();

	// 사망시 모든 클라이언트에게 사망을 전달하기 위해 호출됨
	UFUNCTION(NetMultiCast, unreliable)
		void MultiCastRagdoll();

	// 히트시 소유 클라이언트에게 고통을 준다
	UFUNCTION(Client, Reliable)
		void PlayPain();

public:
	// 팀 색상 설정
	UFUNCTION(NetMultiCast, Reliable)
		void SetTeam(ETeam NewTeam);
};

