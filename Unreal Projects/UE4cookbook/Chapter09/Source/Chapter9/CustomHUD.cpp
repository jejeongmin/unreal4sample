// Fill out your copyright notice in the Description page of Project Settings.

#include "CustomHUD.h"
#include "Engine/Canvas.h"


void ACustomHUD::DrawHUD()
{
	Super::DrawHUD();

	Canvas->DrawText(GEngine->GetSmallFont(), TEXT("Test string to be printed to screen"), 10, 10);
	FCanvasBoxItem ProgressBar(FVector2D(5, 25), FVector2D(50, 5));
	Canvas->DrawItem(ProgressBar);
	// 원본 코드는 위의 progressBar 와 같은 좌표에 아래 푸른 사각형을 덮어씌워서 Y 좌표를 변경해서 겹치지 않도록 수정했다.
	DrawRect(FLinearColor::Blue, 5, 45, 100, 5);
}
