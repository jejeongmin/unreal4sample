// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Attributes/LyraAttributeSet.h"
#include "AbilitySystemComponent.h"
#include "LyraHealthSet.generated.h"

/**
 * 
 */
UCLASS()
class LYRACLONEGAME_API ULyraHealthSet : public ULyraAttributeSet
{
	GENERATED_BODY()
	
public:
	ULyraHealthSet();

	/**
	* 앞서 LyraAttributeSet에서 정의했던, ATTRIBUTE_ACCESSORS를 통해, 아래 정의함 멤벼변수와 똑같이 이름을 설정한다
	* - ATTRIBUTE_ACCESSORS의 Macro의 정의부분을 한번 실펴보자
	*/
	ATTRIBUTE_ACCESSORS(ULyraHealthSet, Health);
	ATTRIBUTE_ACCESSORS(ULyraHealthSet, MaxHealth);
	ATTRIBUTE_ACCESSORS(ULyraHealthSet, Healing);

	/** 현재 체력 */
	UPROPERTY(BlueprintReadOnly, Category = "Lyra|Health")
	FGameplayAttributeData Health;

	/** 체력 최대치 */
	UPROPERTY(BlueprintReadOnly, Category = "Lyra|Health")
	FGameplayAttributeData MaxHealth;

	/** 체력 회복치 */
	UPROPERTY(BlueprintReadOnly, Category = "Lyra|Health")
	FGameplayAttributeData Healing;
};
