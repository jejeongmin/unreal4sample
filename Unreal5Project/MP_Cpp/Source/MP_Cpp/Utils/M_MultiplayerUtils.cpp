// Fill out your copyright notice in the Description page of Project Settings.


#include "Utils/M_MultiplayerUtils.h"
#include "M_MultiplayerUtils.h"

void UM_MultiplayerUtils::PrintLocalNetRole(AActor* Actor)
{
	switch (Actor->GetLocalRole())
	{
	case ROLE_None:
		UE_LOG(LogTemp, Warning, TEXT("Actor [%s] Local Role: None"), *Actor->GetName());
		break;
	case ROLE_Authority:
		UE_LOG(LogTemp, Warning, TEXT("Actor [%s] Local Role: Authority"), *Actor->GetName());
		break;
	case ROLE_AutonomousProxy:
		UE_LOG(LogTemp, Warning, TEXT("Actor [%s] Local Role: Autonomous Proxy"), *Actor->GetName());
		break;
	case ROLE_SimulatedProxy:
		UE_LOG(LogTemp, Warning, TEXT("Actor [%s] Local Role: Simulated Proxy"), *Actor->GetName());
		break;
	default:
		UE_LOG(LogTemp, Warning, TEXT("Actor [%s] Local Role: Unknown"), *Actor->GetName());
		break;
	}
}

void UM_MultiplayerUtils::PrintRemoteNetRole(AActor* Actor)
{
	switch (Actor->GetRemoteRole())
	{
	case ROLE_None:
		UE_LOG(LogTemp, Warning, TEXT("Actor [%s] Remote Role: None"), *Actor->GetName());
		break;
	case ROLE_Authority:
		UE_LOG(LogTemp, Warning, TEXT("Actor [%s] Remote Role: Authority"), *Actor->GetName());
		break;
	case ROLE_AutonomousProxy:
		UE_LOG(LogTemp, Warning, TEXT("Actor [%s] Remote Role: Autonomous Proxy"), *Actor->GetName());
		break;
	case ROLE_SimulatedProxy:
		UE_LOG(LogTemp, Warning, TEXT("Actor [%s] Remote Role: Simulated Proxy"), *Actor->GetName());
		break;
	default:
		UE_LOG(LogTemp, Warning, TEXT("Actor [%s] Remote Role: Unknown"), *Actor->GetName());
		break;
	}
}

void UM_MultiplayerUtils::PrintRole(AActor* Actor)
{
	if (Actor->HasAuthority())
	{
		UE_LOG(LogTemp, Warning, TEXT("Actor [%s] has authority"), *Actor->GetName());
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Actor [%s] does not have authority"), *Actor->GetName());
	}

	switch (Actor->GetLocalRole())
	{
	case ROLE_None:
		UE_LOG(LogTemp, Warning, TEXT("Actor [%s] Local Role: None"), *Actor->GetName());
		break;
	case ROLE_Authority:
		UE_LOG(LogTemp, Warning, TEXT("Actor [%s] Local Role: Authority"), *Actor->GetName());
		break;
	case ROLE_AutonomousProxy:
		UE_LOG(LogTemp, Warning, TEXT("Actor [%s] Local Role: Autonomous Proxy"), *Actor->GetName());
		break;
	case ROLE_SimulatedProxy:
		UE_LOG(LogTemp, Warning, TEXT("Actor [%s] Local Role: Simulated Proxy"), *Actor->GetName());
		break;
	default:
		UE_LOG(LogTemp, Warning, TEXT("Actor [%s] Local Role: Unknown"), *Actor->GetName());
		break;
	}

	switch (Actor->GetRemoteRole())
	{
	case ROLE_None:
		UE_LOG(LogTemp, Warning, TEXT("Actor [%s] Remote Role: None"), *Actor->GetName());
		break;
	case ROLE_Authority:
		UE_LOG(LogTemp, Warning, TEXT("Actor [%s] Remote Role: Authority"), *Actor->GetName());
		break;
	case ROLE_AutonomousProxy:
		UE_LOG(LogTemp, Warning, TEXT("Actor [%s] Remote Role: Autonomous Proxy"), *Actor->GetName());
		break;
	case ROLE_SimulatedProxy:
		UE_LOG(LogTemp, Warning, TEXT("Actor [%s] Remote Role: Simulated Proxy"), *Actor->GetName());
		break;
	default:
		UE_LOG(LogTemp, Warning, TEXT("Actor [%s] Remote Role: Unknown"), *Actor->GetName());
		break;
	}
}
