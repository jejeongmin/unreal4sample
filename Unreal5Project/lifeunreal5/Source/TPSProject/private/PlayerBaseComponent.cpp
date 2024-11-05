// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerBaseComponent.h"

UPlayerBaseComponent::UPlayerBaseComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

	// InitializeComponent() �� ȣ��Ǳ� ���ؼ��� �����ڿ��� bWantsInitializeComponent �� true �� �����Ǿ� �־�� �Ѵ�.
	bWantsInitializeComponent = true;
}


void UPlayerBaseComponent::InitializeComponent()
{
	Super::InitializeComponent();
	me = Cast<ATPSPlayer>(GetOwner());
	moveComp = me->GetCharacterMovement();
	// ��������Ʈ�� ó�� �Լ� ���
	me->onInputBindingDelegate.AddUObject(this, &UPlayerBaseComponent::SetupInputBinding);
}

void UPlayerBaseComponent::BeginPlay()
{
	Super::BeginPlay();
}

