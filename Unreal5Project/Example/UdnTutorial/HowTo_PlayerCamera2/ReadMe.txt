; 스타트업 컨텐츠 패키지를 필요로 함
; 용량 문제로 git 에는 올리지 않음
StarterContent


HowTo_PlayerCamera2
-----------------------------------------------------------------------------------------------------
Pawn 에 Camera 가 Attach 된 SpringArm 을 붙여서 조작하는 예제.

Input 을 통한 Pawn 이동, Pawn 에 부착된 StaticMesh 의 확대/축소 (Scale)기능 구현



-----------------------------------------------------------------------------------------------------
축 입력 매핑에 대한 동작을 구현할 때, FMath::Clamp()함수를 사용했는데 이것은 입력된 값이 -1.0과 1.0 사이를 벗어나지 않도록 만들어 준다. 
전 파트에서 우리가 축 매핑을 추가할 때, MoveX의 입력을 W와 S만을 추가했는데 만약 다른 입력 방식도 사용하기 위해서
위쪽 화살표와 아래쪽 화살표로도 MoveX 입력을 받도록 만들었을 때,
만약 Clamp로 입력의 범위를 제한하지 않았다면 W와 위쪽 화살표를 동시에 누른다면 캐릭터가 두 배의 속도로 빠르게 움직이는 버그가 발생할 것이다


-----------------------------------------------------------------------------------------------------
이번 섹션에서 배운 것(출처: https://wergia.tistory.com/127?category=807793 [베르의 프로그래밍 노트])


1. Pawn(언리얼 엔진 문서)

Pawn 클래스는 플레이어나 AI가 컨트롤할 수 있는 모든 액터의 베이스 클래스다.


2. APawn::AutoPossessPlayer

레벨이 시작되거나 폰이 생성되었을 때, 플레이어 컨트롤러가 있다면 어떤 플레이어 컨트롤러가 자동으로 이 폰을 소유해야 되는지에 대한 변수다.


3. USceneComponent


USceneComponent* RootComponent;
USceneComponent* SubComponent;

USceneComponent는 트랜스폼을 가지고 있고 다른 컴포넌트를 이 컴포넌트에 덧붙이는(Attachment) 것을 지원하지만
충돌 같은 물리적 효과를 지원하지 않고 렌더링 기능이 없다. 계층 구조에서 더미로 활용하기 좋다.

SubComponent->SetupAttachment(RootComponent);

SetupAttachment() 함수는 컴포넌트를 다른 컴포넌트의 아래 계층으로 붙이는데 사용된다. 
위의 예시 코드에 따르면 SubComponent는 계층적으로 자식 컴포넌트가 되고 RootComponent는 부모 컴포넌트가 되는 것이다.

SubComponent->SetRelativeLocation(FVector(-250.0f, 0.0f, 250.0f));
SetRelativeLocation() 함수는 현재 컴포넌트가 상위 계층의 컴포넌트나 오브젝트로부터 얼마나 떨어진 위치에 있을지 정한다.

SubComponent->SetRelativeRotation(FRotator(-45.0f, 0.0f, 0.0f));
SetRelativeRotation() 함수는 현재 컴포넌트가 부모를 기준으로 얼마나 회전된 상태인지 정한다.

SubComponent->GetComponentScale();
GetComponentScale() 함수는 월드 스페이스에서의 컴포넌트 크기를 가져온다.

SubComponent->SetWorldScale3D(FVector(0.0f, 0.0f, 0.0f));
SetWorldScale3D() 함수는 월드 스페이스에서의 컴포넌트 크기를 수정한다.


4. UCameraComponent

액터에 덧붙일 수 있는 카메라 컴포넌트이다.


5. UStaticMeshComponent

엑터에 덧붙일 수 있는 스태틱 메시 컴포넌트이다. 월드에 렌더링된다.


6. AActor::InputComponent

입력이 활성화된 액터에 대한 입력을 처리하는 컴포넌트이다.

InputComponent->BindAction("Action", IE_Pressed, this, &AMyActor::ActionProcess);
액션 매핑에 처리 함수를 바인딩하는 함수다.

첫 번째 매개변수는 바인딩할 액션 매핑의 이름이다.

두 번째 매개변수는 처리할 키 이벤트다. 
기본적으로 사용되는 이벤트는 키가 눌렸을 때를 뜻하는 IE_Pressed와 눌린 키가 떼졌을 때를 뜻하는 IE_Released가 있다.


세 번째 매개변수는 입력을 바인딩하는 오브젝트이다.

네 번째 매개변수는 입력이 들어왔을 때 입력을 처리하는 함수이다.


InputComponent->BindAxis("Axis", this, &AMyPawn::AxisProcess);

축 매핑에 처리 함수를 바인딩하는 함수다.

첫 번째 매개변수는 바인딩할 축 매핑의 이름이다.

두 번째 매개변수는 입력을 바인딩하는 오브젝트이다.

세 번째 매개변수는 입력이 들어왔을 때 입력을 처리하는 함수이다.


7. AActor::GetActorLocation()

GetActorLocation();
액터의 월드 스페이스 상의 위치를 가져오는 함수이다.


8. AActor::SetActorLocation()

SetActorLocation(FVector(0.0f, 0.0f, 0.0f));
액터의 월드 스페이스 상의 위치를 정하는 함수이다.



9. FMath::Clamp()


FMath 클래스는 수학적인 기능들을 제공한다.

FMath::Clamp(Value, Min, Max);

Clamp() 함수는 Value의 값이 Min보다 값이 작으면 Min 값을, Max보다 크면 Max 값을 돌려주고, 
그 사잇값이라면 Value를 돌려주는 함수이다. 값이 특정한 범위를 벗어나면 안되는 경우에 사용하면 좋다.


-----------------------------------------------------------------------------------------------------
UE 4.19 -> 5.5

주요 변경 사항

Build.cs 파일 업데이트
이건 Project Setting 에 기존 PlayerInput Action Mapping 정보가 이미 설정되어 있어서 일부러 EnhancedInput 시스템으로 변경하지 않았음