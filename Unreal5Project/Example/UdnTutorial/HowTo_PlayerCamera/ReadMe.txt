; 스타트업 컨텐츠 패키지를 필요로 함
; 용량 문제로 git 에는 올리지 않음
StarterContent


HowTo_PlayerCamera
--------------------------------------------------------------------
Pawn 에 Camera 가 Attach 된 SpringArm 을 붙여서 조작하는 예제.

Input 을 통한 Pawn 이동, Camera Yaw, Pitch 회전, ZoomIn/Out 구현



--------------------------------------------------------------------
이번 섹션에서 배운 것(출처: https://wergia.tistory.com/130?category=807793 [베르의 프로그래밍 노트])

1. USceneComponent

SetRelativeLocationAndRotation(FVector(), FRotator());
루트 오브젝트로부터의 위치와 회전을 동시에 설정할 수 있는 함수.


2. FVector2D

FVector2D Vector2D;
FVector의 2D 버전 구조체. FVector는 3차원 상의 X, Y, Z 좌표를 가지지만 FVector2D는 2차원 상의 X, Y 좌표만을 가진다.


3. UCameraComponent

UCameraComponent* CameraComponent;
CameraComponent->FieldOfView = 60.0f;
원근감 모드(Projection Mode)에서의 수평 시야각을 Field of view라고 한다. 
수평 시야각이 넓어지면 물체가 확대되어서 보이기 때문에 주로 FPS게임에서 저격 소총의 줌 효과에 주로 사용된다.


4. FMath::Lerp()

FMath::Lerp(ValueA, ValueB, Factor);

선형 보간 함수이다. 
ValueA와 ValueB 사이의 Factor(0.0~1.0)값의 위치에 해당 하는 값을 구해준다.
ex) ValueA = 0, ValueB = 2일 때, Factor = 0.5이면 1을 돌려준다.


5. AActor

GetActorForwardVector();
액터의 Forward 방향을 구하는 함수

GetActorRightVector();
액터의 Right 방향으로 구하는 함수

-----------------------------------------------------------------------------------------------------
UE 4.19 -> 5.5

주요 변경 사항

Build.cs 파일 업데이트
이건 Project Setting 에 기존 PlayerInput Action Mapping 정보가 이미 설정되어 있어서 일부러 EnhancedInput 시스템으로 변경하지 않았음