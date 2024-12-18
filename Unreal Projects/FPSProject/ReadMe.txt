## FPSProject

- GEngine->AddOnScreenDebugMessage 를 이용해 디버그 메시지 출력

- 크로스 헤어 출력 기능

- 발사체 구현 ( 컬리전세팅 / ProjectileMovementComponent 세팅 / 충돌처리 )

- 폰 구현 ( 1인칭 카메라 / 1,3인칭 메시 / 이동 / 발사 )



--------------------------------------------------------------------------------------------------------

1. AGameMode

StartPlay();
플레이가 시작되었을 때, 게임 모드에서 액터들의 BeginPlay() 함수를 호출하는 역할.


2. GEngine

GEngine;
전역에 선언되어 있는 엔진 포인터. 사용하기 위해서는 "Engine.h"를 포함해줘야 한다. 
엔진에서 실행되는 경우가 아닐 경우, 값이 유효하지 않을 수 있으니 사용하기 전에 
반드시 GEngine이 유효한 상태인지 체크하고 사용해야한다.

GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("Hello World, this is FPSGameMode!"));
뷰포트에 디버그 메시지를 띄우는데 사용되는 함수


3. FColor

FColor Color;

언리얼 엔진에서 색상으로 표현하는데 사용되는 구조체

FColor::Red;
FColor::Blue;
FColor::Green;
FColor::Black;
FColor::White;
FColor::Cyan;
FColor::Emerald;
FColor::Magenta;
FColor::Orange;
FColor::Purple;
FColor::Silver;
FColor::Transparent;
FColor::Turquoise;
FColor::Yellow;

언리얼 엔진에서는 기본적인 색상을 스태틱으로 미리 만들어서 사용자가 일일이 구조체를 생성해서
색상을 만들 필요가 없게 만들어 두었다.


4. FRotatorMatrix

FRotatorMatrix RotatorMatrix;
행렬에서 이동 행렬을 뺀 순수하게 회전에 대한 행렬이다.

RotatorMatrix.GetScaledAxis(EAxis::X);
행렬의 크기에 의해서 스케일링된 행렬의 축을 가져오는 함수


5. ACharacter

Controller;
캐릭터를 제어하는 컨트롤러에 대한 변수

Controller->GetControlRotation();
컨트롤 회전을 가져오는 함수. 이것은 카메라 방향(예 : 3 인칭보기)과 다를 수 있는 완전한 목표 회전이며 
제어된 Pawn (시각적으로 피치를 두거나 롤하지 않도록 선택할 수 있음)의 회전과 다를 수 있다.

AddControllerYawInput();
캐릭터 클래스에서 기본적으로 지원하는 Yaw 회전 처리 함수. 
이 함수를 마우스 좌우 이동 입력과 바인딩하면 카메라 좌우 회전하는 기능을 만들 수 있다.

AddControllerPitchInput();
캐릭터 클래스에서 기본적으로 지원하는 Pitch 회전 처리 함수.

bPressedJump = true;
캐릭터 클래스에서 기본적으로 지원하는 점프 처리 변수. true가 되면 캐릭터 클래스에서 자동으로 점프를 처리해준다.


6. UCameraComponent

CameraComponent->bUsePawnControlRotation = true;
이 카메라 컴포넌트가 폰의 컨트롤 회전을 따라서 회전할 지를 결정하는 변수


7. USkeletalMeshComponent

USkeletalMeshComponent* SkeletalMeshComponent;
애니메이션을 사용할 수 있는 스켈레탈 메시 애셋의 인스턴스를 만드는데 사용되는 컴포넌트.


SkeletalMeshComponent->SetOnlyOwnerSee(true);
UPrimitiveComponent 클래스에서 상속받은 함수로 이 메시를 소유한 플레이어만 이 메시를 볼 수 있게 하는 함수

SkeletalMeshComponent->bCastDynamicShadow = false;
사전에 계산되지 않은 실시간 그림자를 그려야하는지에 대한 변수. CastShadow가 true일 때만 작동한다.

SkeletalMeshComponent->CastShadow = false;
그림자를 그려야하는지에 대한 변수

SkeletalMeshComponent->SetOwnerNoSee(true);
이 메시를 소유한 플레이어에게만 보이지 않도록 하는 함수


8. UProjectileMovementComponent

UProjectileMovementComponent* ProjectileMovementComponent;
발사체의 이동을 처리해주는 컴포넌트

ProjectileMovementComponent->InitialSpeed = 3000.0f;
발사체의 초기 속도 변수. 이 값이 0이면 Velocity 값을 속도로 사용하고, 0이 아니면 Velocity 값을 무시한다.

ProjectileMovementComponent->MaxSpeed = 3000.0f;
발사체에 허용되는 최대 속력

ProjectileMovementComponent->bRotationFollowsVelocity = true;
이 값이 참이면, 발사체의 회전이 이동 방향에 맞춰 매 프레임 업데이트된다.

ProjectileMovementComponent->bShouldBounce = true;
이 값이 참이면, 간단한 바운스가 시뮬레이션 된다. 접촉 시뮬레이션을 중지하려면 이 값을 false로 설정한다.

ProjectileMovementComponent->Bounciness = 0.3f;
충돌의 법선 방향으로 반발이 발생한 이후에 유지되는 속도의 비율

ProjectileMovementComponent->Velocity;
발사체의 속도


9. AActor

FVector EyeLocation;
FRotator EyeRotation;
GetActorEyesViewPoint(EyeLocation, EyeRotation);
액터의 시점을 가져오는 함수. 이 시점은 액터의 붙은 카메라의 위치와 회전이 아니라 실제 액터의 눈에 해당하는 위치와 회전이다.

InitialLifeSpan = 3.0f;
액터의 수명을 결정하는 변수. 0으로 설정하면 시간이 지나도 소멸하지 않는다. 이 값은 초기 값이기 때문에, 플레이가 시작된 이후에는 수정해서는 안된다.

10. FActorSpawnParameters

FActorSpawnParameters SpawnParams;
액터를 스폰할 때 사용되는 매개변수들을 담는 구조체

SpawnParams.Owner;
이 액터를 생성한 액터. 생성한 액터가 따로 없다면 NULL로 둘 수 있다.


11. UWorld

GetWorld()->SpawnActor<T>(Class, Location, Rotation, SpawnParams);
월드에 액터를 스폰하는 함수이다.


12. UPrimitiveComponent

Target->AddImpulseAtLocation(Impulse, Location);
대상 물체에 충돌 효과를 주는 함수.



