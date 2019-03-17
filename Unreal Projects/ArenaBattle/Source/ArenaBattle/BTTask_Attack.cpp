// Fill out your copyright notice in the Description page of Project Settings.

#include "BTTask_Attack.h"
#include "ABAIController.h"
#include "ABCharacter.h"

UBTTask_Attack::UBTTask_Attack()
{
	bNotifyTick = true;
	IsAttacking = false;
}

/*
	chapter 12

	ĳ������ ��������Ʈ ������ �Ϸ�Ǹ� �½�ũ���� ���� �Լ��� �ش� ��������Ʈ�� ����ϰ� Tick �Լ� �������� �̸� �ľ���
	FinishLatentTask �Լ��� ȣ�������ν� �½�ũ�� �����ϵ��� �����Ѵ�.
*/
EBTNodeResult::Type UBTTask_Attack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

	auto character = Cast<ABCharacter>(OwnerComp.GetAIOwner()->GetPawn());
	if (nullptr == character)
		return EBTNodeResult::Failed;

	character->Attack();
	IsAttacking = true;
	character->OnAttackEnd.AddLambda([this]() -> void {
		IsAttacking = false;
	});

	return EBTNodeResult::InProgress;
}

void UBTTask_Attack::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);
	if (!IsAttacking)
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}
}
