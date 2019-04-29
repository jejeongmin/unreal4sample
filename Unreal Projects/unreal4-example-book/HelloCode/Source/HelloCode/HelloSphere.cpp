// Fill out your copyright notice in the Description page of Project Settings.

#include "HelloSphere.h"

#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Materials/Material.h"
#include "ConstructorHelpers.h"
#include "Particles/ParticleSystemComponent.h"
#include "Components/TextRenderComponent.h"

// Sets default values
AHelloSphere::AHelloSphere()
{
	// �� ���Ͱ� Tick()�� �� �����Ӹ��� �θ����� �Ѵ�. 
	// �ʿ� ���ٸ� ���� ����� ���� �� ���� �ִ�.
	PrimaryActorTick.bCanEverTick = true;

	// ��Ʈ ������Ʈ�� ��ħ�� �浹�� �˷��ִ� ��ü ������Ʈ�� �� ���̴�.
	USphereComponent* SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("RootComponent"));
	RootComponent = SphereComponent;

	// ��ü ������Ʈ�� �Ӽ��� �����Ѵ�.
	SphereComponent->InitSphereRadius(220.0f);
	SphereComponent->SetCollisionProfileName(TEXT("OverlapAllDynamic"));

	// ��ü �޽ø� �����ϰ� �����Ѵ�
	UStaticMeshComponent* SphereVisual = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SphereMesh"));
	SphereVisual->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);

	// ConstructorHelpers�� ���� �޽ÿ� ����ƽ �޽� �����ϱ�
	ConstructorHelpers::FObjectFinder<UStaticMesh> SphereVisualAsset(TEXT("/Game/StarterContent/Shapes/Shape_Sphere.Shape_Sphere"));
	ConstructorHelpers::FObjectFinder<UMaterial> SphereMaterial(TEXT("/Game/StarterContent/Materials/M_Metal_Burnished_Steel.M_Metal_Burnished_Steel"));

	// �޽ð� ���������� �����Ǿ��ٸ� �޽� �Ӽ� ���� 
	if (SphereVisualAsset.Succeeded() && SphereMaterial.Succeeded())
	{
		SphereVisual->SetStaticMesh(SphereVisualAsset.Object);
		SphereVisual->SetMaterial(0, SphereMaterial.Object);
		SphereVisual->SetRelativeLocation(FVector(0.0f, 0.0f, -40.0f));
	}

	// ���̾� ��ƼŬ �ý��� �����ϱ�
	UParticleSystemComponent* FireParticles = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("FireParticles"));

	FireParticles->AttachToComponent(SphereVisual, FAttachmentTransformRules::KeepRelativeTransform);
	FireParticles->bAutoActivate = true;

	// ������Ʈ�� ���̾� ��ƼŬ �ý��� �����ϱ�
	ConstructorHelpers::FObjectFinder<UParticleSystem> FireVisual(TEXT("/Game/StarterContent/Particles/P_Fire.P_Fire"));

	if (FireVisual.Succeeded())
	{
		FireParticles->SetTemplate(FireVisual.Object);
	}

	// �ؽ�Ʈ ���� ������Ʈ �ʱ�ȭ
	TextRenderComponent = CreateDefaultSubobject<UTextRenderComponent>(TEXT("Text"));

	TextRenderComponent->AttachToComponent(SphereVisual, FAttachmentTransformRules::KeepRelativeTransform);
	TextRenderComponent->SetRelativeLocation(FVector(0.0f, 0.0f, 110.0f));
	TextRenderComponent->SetHorizontalAlignment(EHTA_Center);
	TextRenderComponent->SetYScale(2.0f);
	TextRenderComponent->SetXScale(2.0f);
	TextRenderComponent->SetVisibility(true);
	TextRenderComponent->SetText(NSLOCTEXT("AnyNs", "Any", "HelloWorld"));

	// ��������Ʈ ���ε�
	OnActorBeginOverlap.AddDynamic(this, &AHelloSphere::MyOnBeginOverlap);
	OnActorEndOverlap.AddDynamic(this, &AHelloSphere::MyOnEndOverlap);
}

// ������ ���۵ǰų� �����Ǿ��� �� ȣ���  
void AHelloSphere::BeginPlay()
{
	Super::BeginPlay();
	
}

// �� ������ ȣ���
void AHelloSphere::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

}

void AHelloSphere::MyOnBeginOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	FString outputString;
	outputString = "Hello " + OtherActor->GetName() + "!";
	TextRenderComponent->SetText(FText::FromString(outputString));
}

void AHelloSphere::MyOnEndOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	TextRenderComponent->SetText(NSLOCTEXT("AnyNs", "Any", "HelloWorld"));
}

