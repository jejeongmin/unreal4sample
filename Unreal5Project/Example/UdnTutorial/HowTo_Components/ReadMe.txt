; 스타트업 컨텐츠 패키지를 필요로 함
; 용량 문제로 git 에는 올리지 않음
StarterContent
-----------------------------------------------------------------------------------------------------

HowTo_Components

Pawn Movement Component 를 이용해 Pawn 이동을 처리하는 예제

Pawn 에 Camera 가 Attach 된 SpringArm 을 붙여서 조작하는 기능을 주석을 통해 자세히 설명했다.
StaticMeshComponent, Particle 등을 editor 가 아닌, 코드 상에서 직접 Attach 했다.
Particle 효과 on / off 구현했다.
PawnMovementComponent 를 재정의해 물체에 부딪히면 부드럽게 지나가도록 처리했다.
Default Pawn Movement 에서 지원하지는 않는 중력 적용을 간단히 구현했다.


-----------------------------------------------------------------------------------------------------
Pawn 클래스에는 GetMovementComponent() 라는 함수가 있는데 이것은 엔진의 다른 클래스들이 현재 Pawn이 사용중인 
Pawn Movement Component에 접근할 수 있도록 하는데 사용된다. 
이 함수가 커스터마이징한 CollidingPawnMovementComponent를 반환하도록 하려면 이 함수를 덮어씌워야 한다. 


이번 섹션에서 배운 것(출처: https://wergia.tistory.com/129?category=807793 [베르의 프로그래밍 노트])


1. UParticleSystemComponent

UParticleSystemComponent* ParticleSystemComponent;
액터에 파티클 시스템을 덧붙일 수 있는 컴포넌트

ParticleSystemComponent->bAutoActivate = true;
파티클 시스템이 생성되자마자 자동으로 켜질지에 대한 변수

ParticleSystemComponent->SetTemplate(ParticleAsset.Object);
파티클 시스템 컴포넌트의 파티클을 설정하는 함수

ParticleSystemComponent->ToggleActive();
파티클을 켜고 끄는 함수


2. USphereComponent

USphereComponent* SphereComponent;
액터에 구형 충돌 물리 효과를 줄 수 있는 컴포넌트

SphereComponent->InitSphereRadius(40.0f);
스피어 컴포넌트의 반지름은 설정하는 함수

SphereComponent->SetCollisionProfileName(TEXT("Pawn"));
콜리전의 프로필을 설정하는 함수. 
[프로젝트 세팅>엔진>콜리전] 하단에 Preset을 열어보면 각 콜리전 프로필마다 어떤 물리 설정을 가지고 있는지 확인할 수 있다.


3. UStaticMeshComponent

UStaticMeshComponent* StaticMeshComponent;
월드에 렌더링되는 스태틱 메시를 가진 컴포넌트

StaticMeshComponent->SetStaticMesh(SphereVisualAsset.Object);
스태틱 메시 컴포넌트의 스태틱 메시를 설정하는 함수


4. ConstructorHelpers::FObjectFinder<T>

static ConstructorHelpers::FObjectFinder<T> Asset(TEXT("AssetPath"));
프로젝트에서 필요한 콘텐츠나 리소스, 에셋을 불러오는데 쓰이는 구조체


Asset.Succeeded();
에셋을 불러오는데 성공했는지를 반환하는 함수

Asset.Object;
불러온 에셋을 담고 있는 변수


5. USpringArmComponent

USpringArmComponent* SpringArmComponent;
부모 오브젝트와 자식 오브젝트 사이에 일정한 거리를 유지하게 도와주는 컴포넌트. 
충돌이 있는 경우라면 유연하게 부모와 자식 사이의 거리를 좁혔다가 충돌이 사라지면 다시 원래대로 돌아가게하는 기능을 제공한다.

SpringArmComponent->TargetArmLength = 400.0f;
아무런 충돌이 없을 때, 스프링 암의 자연적인 거리를 정할 수 있는 변수

SpringArmComponent->bEnableCameraLag = true;
true인 경우, 카메라가 목표 위치보다 뒤떨어져서 따라가도록 한다.

SpringArmComponent->CameraLagSpeed = 3.0f;
bEnableCameraLag가 true인 경우, 카메라가 목표 위치에 도달하는 속도를 제어한다.


6. UPawnMovementComponent

Pawn의 움직임을 업데이트하는데 사용되는 컴포넌트

PawnOwner;
이 컴포넌트를 소유하고 있는 폰

UMovementComponent::UpdatedComponent;
UPawnMovementComponent의 부모 클래스인 UMovementComponent 클래스에 속하는 변수로 이 무브먼트 컴포넌트가 이동시키고 업데이트 해야할 컴포넌트

UMovementComponent::ShouldSkipUpdate(DeltaTime);
이동된 컴포넌트가 이동할 수 없거나 렌더링되지 않은 경우인지를 판별하여 알려주는 함수

ConsumeInputVector();
대기중인 입력을 반환하고 다시 0으로 설정하는 함수

SafeMoveUpdatedComponent(DesiredMovementThisFrame, UpdatedComponent->GetComponentRotation(), true, Hit);
언리얼 엔진 피직스를 이용해서 입체 장애물을 피해서 폰 무브먼트 컴포넌트를 이동시키는 함수

SlideAlongSurface(DesiredMovementThisFrame, 1.0f - Hit.Time, Hit.Normal, Hit);
컴포넌트가 이동하다가 충돌이 발생했을 때, 제자리에 멈추는 대신 충돌체의 표면을 타고 미끄러지듯이 이동하도록 도와주는 함수

AddInputVector(Vector);
매개변수로 받은 벡터를 누적 입력에 더하는 함수


7. FVector

FVector Vector;
언리얼 엔진에서 3D 상의 위치나, 속도를 나타내는데 쓰이는 구조체


Vector.GetClampedToMaxSize(Value);
길이가 Value인 이 벡터의 복사본을 만들어서 반환하는 함수


Vector.IsNearlyZero();
지정된 허용오차 내에서 벡터의 길이가 0에 근접하는지 확인하는 함수


8. FHitResult

FHitResult Hit;
충돌에 대한 정보를 담고 있는 구조체

Hit.Time;
Hit가 발생했을 때, TraceStart와 TraceEnd 사이의 충돌이 발생한 시간을 의미한다. (0.0~1.0)

Hit.Normal
충돌이 발생한 오브젝트의 월드 공간 상의 법선 방향

Hit.IsValidBlockingHit();
막히는 충돌이 발생했을 때 true를 반환하는 함수


9. AActor

GetActorRotation();
액터의 현재 회전을 반환하는 함수

SetActorRotation(FRotator());
액터의 회전을 설정하는 함수


-----------------------------------------------------------------------------------------------------
UE 4.19 -> 5.5

주요 변경 사항

Build.cs 파일 업데이트
EnhancedInput 시스템으로 변경