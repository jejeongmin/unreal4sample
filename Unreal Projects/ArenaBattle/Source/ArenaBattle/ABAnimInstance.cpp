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

	���� �����Ϳ� �ִ� �ν��Ͻ��� �����͸� �����ϰ� �������

	1) ���� tick �Լ����� �ִ� �ν��Ͻ��� CurrentPawnSpeed �� ���ų�
	2) �ִ� �ν��Ͻ��� tick ���� ���� �ӵ� ������ ������ �� �̸� CurrentPawnSpeed �� ������Ʈ �ϴ� ����� �ִ�.

	������ ����� ���� ����̴�.

	�ִϸ��̼� ������ ���� ������ �и��� �� �ְ�,
	�ִϸ��̼��� �ʿ� ���� ���� �ڵ忡�� �������� �����ϱ� �����̴�.
*/
void UABAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	/*
		chapter 7

		���� ������ ƽ���� �Է� �ý��� > ���� ���� > �ִϸ��̼� �ý��� ������ ������ �����Ѵ�.
		�̴� �÷��̾��� ������ �Է°��� ���� �� �װ��� �ؼ��� ���� �����̰� �����, ���� ���� �����Ӱ� �´� �ִϸ��̼��� �����Ű�� ���� �ڿ������� �����̴�.

		���� �ִϸ��̼ǿ� �ռ� ����Ǵ� ���� ���� �ܰ迡�� ���� �����ϴ� ����� ���ȴٸ� �� �ڿ� ����Ǵ� �ִϸ��̼� ���������� �� �̻� ��ȿ���� ���� �� ��ü�� �����ϰ� �� ���̴�.
		�׷��� �ִϸ��̼� �ý����� ���� ������ ������ ���� �� ��ü�� ��ȿ������ �����ؾ� �Ѵ�.
		
		�̸� �˻��ϴ� ����� TryGetPawnOwner �̴�.
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