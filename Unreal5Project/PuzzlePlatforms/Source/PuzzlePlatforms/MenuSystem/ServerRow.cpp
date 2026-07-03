// Fill out your copyright notice in the Description page of Project Settings.


#include "MenuSystem/ServerRow.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "MainMenu.h"

bool UServerRow::Initialize()
{
    if (!Super::Initialize())
        return false;

    if (RowButton)
    {
        RowButton->OnHovered.AddDynamic(this, &UServerRow::OnRowHovered);
        RowButton->OnUnhovered.AddDynamic(this, &UServerRow::OnRowUnhovered);
    }

    return true;
}

void UServerRow::Setup(class UMainMenu* InParent, uint32 InIndex)
{
	Parent = InParent;
	Index = InIndex;
	RowButton->OnClicked.AddDynamic(this, &UServerRow::OnClicked);
}

void UServerRow::OnClicked()
{
	Parent->SelectIndex(Index);
}

void UServerRow::OnRowHovered()
{
	ServerName->SetColorAndOpacity(FSlateColor(FLinearColor::Green));
}

void UServerRow::OnRowUnhovered()
{
	// 선택된 상태가 아닐 때만 흰색으로 복원
	if (!bIsSelected)
	{
		ServerName->SetColorAndOpacity(FSlateColor(FLinearColor::White));
	}
	else
	{
		// 선택된 상태면 노란색 유지
		ServerName->SetColorAndOpacity(FSlateColor(FLinearColor::Yellow));
	}
}

void UServerRow::SetSelected(bool bSelected)
{
	bIsSelected = bSelected;

	// 선택 상태에 따라 시각적 변경
	if (ServerName)
	{
		if (bSelected)
		{
			// 선택된 스타일 적용
			ServerName->SetColorAndOpacity(FSlateColor(FLinearColor::Yellow));
		}
		else
		{
			// 기본 스타일로 복원
			ServerName->SetColorAndOpacity(FSlateColor(FLinearColor::White));
		}
	}
}