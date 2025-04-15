----------------------------------------------------------------------------------------------------
HowTo_UMG

- PlayerController 에서 UI 입력을 위한 입력 모드로 변경 구현

- UserWidget 을 블루프린트 함수 호출로 변경할 수 있는 GameMode 객체를 c++ 로 구현

- 위의 GameMode 를 블루프린트 클래스로 다시 재상속 받은 객체 구현

- Slate 를 이용한 GameMenu 클래스 구현

- 블루프린트 호출을 통해 Button Click, Input Validator 구현


----------------------------------------------------------------------------------------------------
이번 섹션에서 배운 것(출처: https://wergia.tistory.com/131?category=807793 [베르의 프로그래밍 노트])


1. 언리얼 모듈 종속성

언리얼 엔진의 기능은 다수의 모듈로 나누어져 있고, 그 중에 필요한 모듈을 묶어서 사용하는 방식이다. 
이번 섹션 처음 부분에 build.cs파일에서 모듈 종속성을 구성할 때도 보았겠지만, 
기본적으로 언리얼은 Core, CoreUObject, Engine, InputCore 모듈을 사용하고 있었고, 
UI와 관련된 기능을 사용하기 위해서 UMG 모듈과 Slate, SlateCore 모듈을 구성에 추가해주었다.

추후의 일이지만, 언리얼 엔진을 커스터마이징하고자 할 때, 새롭게 추가하는 기능을 이러한 모듈로 만들어 덧붙이게 될 것이다.


2. TSubClassOf<T>

UClass 타입 안정성을 보장하는 템플릿 클래스. 
TSubClassOf에 전달된 인수가 템플릿 인자로 받은 타입과 일치하거나 
템플릿 인자로 받은 타입을 상속받은 타입인지를 런타임 중에 확인하도록 도와주는 클래스이다.


3. UUserWidget

UUserWidget* UserWidget;
Widget Blueprint를 통해서 확장할 수 있는 사용자 위젯.

UserWidget->AddToViewport();
유저 위젯을 뷰 포트에 추가하는 함수.

UserWidget->RemoveToViewport();
유저 위젯을 뷰 포트에서 제거하는 함수.


4. AActor::GetWorld()

GetWorld();
UWorld 객체를 가져오는 함수. UWorld는 액터나 컴포넌트들을 포함하는 맵이나 샌드박스의 최상위 객체이다.


5. CreateWidge()

CreateWidge(GetWorld(), newWidget);
위젯을 생성하는 함수


6. APlayerController::SetInputMode()

SetInputMode(FInputModeGameAndUI());
플레이어 컨트롤러의 입력 모드를 설정하는 함수. Game 입력만 받을지, UI 입력만 받을지, 아니면 둘 다 받을지를 정할 수 있다.


7. UPROPERTY()

UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UMG_Game")

클래스의 멤버 변수에 붙이는 매크로. 에디터의 노출 수준을 정할 수 있다.
EditAnywhere는 에디터 디테일 패널에 노출이 가능하다.
BlueprintReadOnly는 블루프린트에서 수정을 불가능하고 읽기만 가능하다.
Category는 블루프린트에서 불러올 때, 카테고리를 분류해서 찾기 쉽게 만들어준다.


8. UFUNCTION()

UFUNCTION(BlueprintCallable, Category = "UMG_Game")
함수에 붙이는 매크로.
BlueprintCallable은 블루프린트에서 호출만 가능하다는 의미이다.



