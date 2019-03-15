// Fill out your copyright notice in the Description page of Project Settings.

#include "ABAnimInstance.h"


UABAnimInstance::UABAnimInstance()
{
	CurrentPawnSpeed = 0.0f;
	IsInAir = false;
	IsDead = false;
	
	static ConstructorHelpers::FObjectFinder<UAnimMontage> ATTACK_MONTAGE(TEXT("/Game/Animations/SK_Mannequin_Skeleton_Montage.SK_Mannequin_Skeleton_Montage"));

	if (ATTACK_MONTAGE.Succeeded())
	{
		AttackMontage = ATTACK_MONTAGE.Object;
	}
}

/*
	chapter 7

	폰의 데이터와 애님 인스턴스의 데이터를 동일하게 만들려면

	1) 폰의 tick 함수에서 애님 인스턴스의 CurrentPawnSpeed 에 쓰거나
	2) 애님 인스턴스의 tick 에서 폰의 속도 정보를 가져온 후 이를 CurrentPawnSpeed 에 업데이트 하는 방법이 있다.

	후자의 방법이 좋은 방법이다.

	애니메이션 로직과 폰의 로직을 분리할 수 있고,
	애니메이션이 필요 없는 서버 코드에도 문제없이 동작하기 때문이다.
*/
void UABAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	/*
		chapter 7

		게임 엔진은 틱마다 입력 시스템 > 게임 로직 > 애니메이션 시스템 순으로 로직을 실행한다.
		이는 플레이어의 의지인 입력값을 받은 후 그것을 해석해 폰을 움직이게 만들고, 폰의 최종 움직임과 맞는 애니메이션을 재생시키는 것이 자연스럽기 때문이다.

		만일 애니메이션에 앞서 실행되는 게임 로직 단계에서 폰을 제거하는 명령을 내렸다면 그 뒤에 실행되는 애니메이션 로직에서는 더 이상 유효하지 않은 폰 객체를 참조하게 될 것이다.
		그래서 애니메이션 시스템은 폰에 접근할 때마다 먼저 폰 객체가 유효한지를 점검해야 한다.
		
		이를 검사하는 명령이 TryGetPawnOwner 이다.
	*/
	auto Pawn = TryGetPawnOwner();
	if (!::IsValid(Pawn))
		return;

	if (!IsDead)
	{
		CurrentPawnSpeed = Pawn->GetVelocity().Size();
		auto Character = Cast<ACharacter>(Pawn);
		if (Character)
		{
			IsInAir = Character->GetMovementComponent()->IsFalling();
		}
	}
}

void UABAnimInstance::PlayAttackMontage()
{
	ABCHECK(!IsDead);
	Montage_Play(AttackMontage, 1.0f);
}

void UABAnimInstance::AnimNotify_AttackHitCheck()
{
	OnAttackHitCheck.Broadcast();
}

void UABAnimInstance::AnimNotify_NextAttackCheck()
{
	OnNextAttackCheck.Broadcast();
}

void UABAnimInstance::JumpToAttackMontageSection(int32 NewSection)
{
	ABCHECK(!IsDead);
	ABCHECK(Montage_IsPlaying(AttackMontage));
	Montage_JumpToSection(GetAttackMontageSectionName(NewSection), AttackMontage);
}

FName UABAnimInstance::GetAttackMontageSectionName(int32 Section)
{
	ABCHECK(FMath::IsWithinInclusive<int32>(Section, 1, 4), NAME_None);
	return FName(*FString::Printf(TEXT("Attack%d"), Section));
}