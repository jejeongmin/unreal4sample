// Fill out your copyright notice in the Description page of Project Settings.
#include "MP_LANMenu.h"
#include "Components/Button.h"
#include "Components/EditableTextBox.h"
#include <Kismet/GameplayStatics.h>

void UMP_LANMenu::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	SetUIOnlyInputMode(true);

	if (Button_Host)
	{
		Button_Host->OnClicked.AddDynamic(this, &UMP_LANMenu::HostButtonClicked);
	}
	if (Button_Join)
	{
		Button_Join->OnClicked.AddDynamic(this, &ThisClass::JoinButtonClicked);
	}
}

void UMP_LANMenu::HostButtonClicked()
{
	SetUIOnlyInputMode(false);

	UGameplayStatics::OpenLevelBySoftObjectPtr(this, HostingLevel, true, TEXT("Listen"));
}

void UMP_LANMenu::JoinButtonClicked()
{
	SetUIOnlyInputMode(false);

	const FString IpAddress = TextBox_IpAddress->GetText().ToString();
	UGameplayStatics::OpenLevel(this, FName(*IpAddress));
}

void UMP_LANMenu::SetUIOnlyInputMode(bool bShowMouseCursor)
{
	FInputModeUIOnly InputModeData;
	if (APlayerController* PC = GetOwningPlayer())
	{
		PC->SetInputMode(InputModeData);
		PC->SetShowMouseCursor(bShowMouseCursor);
	}
}