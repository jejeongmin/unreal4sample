-------------------------------------------------------------------------------------------------------
HowTo_VTE

타이머로 카운트다운 출력을 하고 종료되면 폭발 효과를 보여주는 예제

- 카운트다운을 위한 타이머 처리 구현

- 화면에 텍스트를 출력하는 기능 구현

- 위의 카운트 다운 객체를 상속받은 블루프린트 클래스에서 c++ 의 NativeEvent 를
  블루 프린트 이벤트로 받아 폭발 효과를 구현


-------------------------------------------------------------------------------------------------------
이번 섹션에서 배운 것(출처: https://wergia.tistory.com/125?category=807793 [베르의 프로그래밍 노트])

1. CreateDefaultSubobject<T>() (언리얼 엔진 문서)

UObject 클래스를 상속받는 모든 클래스에서 사용가능한 함수이다. 
하위 오브젝트나 컴포넌트를 생성할 때 사용되는 함수로 2번의 UTextRenderComponent를 생성하는 예시와 같이 사용된다. 
이 함수는 T의 포인터(T*) 타입을 반환한다.


2. UTextRenderComponent(언리얼 엔진 문서)

UTextRenderComponent* TextRenderComponent;
설정된 텍스트를 3D 공간 상에 렌더링하는 컴포넌트이다. 
글자 색, 크기, 폰트, 정렬 등을 설정할 수 있으며 액터 등에 컴포넌트로 덧붙여서 사용할 수 있다. 
이 컴포넌트를 사용하기 위해서는 "Engine/Classes/Components/TextRenderComponent.h"를 포함해야 한다.

TextRenderComponent = CreateDefaultSubobject<UTextRenderComponent>(TEXT("TextRenderComponent"));
코드 상에서 UTextRenderComponent를 생성하는 방법은 위와 같다.

TextRenderComponent->SetHorizontalAlignment(EHTA_Center);
렌더링되는 텍스트의 수평 정렬을 설정하는 함수이다. 
정렬 방식은 EHTA_Center, EHTA_Left, EHTA_Right가 있다.

TextRenderComponent->SetWorldSize(100.0f);
렌더링되는 텍스트의 월드에서의 크기를 설정하는 함수이다. 

CountdownText->SetText(FText::FromString(TEXT("GO!")));
렌더링되는 텍스트의 문자열 내용을 설정하는 함수이다.


3. Timer

타이머는 사용자가 정의한 시간마다 사용자가 지정한 동작이 실행되도록 만든다.

1) FTimerHandle (언리얼 엔진 문서)

FTimerHandle TimerHandle;
FTimerHandle은 타이머를 구별할 수 있는 유일한 핸들이다. 
타이머를 생성하는 함수는 타이머를 생성할 때, 타이머의 핸들을 돌려주는데, 
이 핸들을 가지고 있어야 생성한 타이머를 중지시킬 수 있다.


2) GetWorldTimerManager() (언리얼 엔진 문서)

AActor 클래스를 상속받는 모든 클래스에서 호출가능한 함수이다. 
월드 타이머 매니저를 반환한다. 
GetWorldTimerManager()의 호출이 정상적으로 되지 않을 경우 "TimerManager.h"를 포함시키면 된다.

GetWorldTimerManager().SetTimer(TimerHandle, this, &ACountdown::AdvenceTimer, 1.0f, true);
SetTimer() 함수는 타이머를 생성하고 시작시키는 함수로 여러가지 오버로드가 존재하지만 우선은 위의 오버로드 형식만 살펴보자. 
첫 번째 매개변수는 지금 생성되는 타이머의 핸들이다. 위에서 설명했듯이 이 핸들을 가지고 있어야 나중에 타이머를 종료할 수 있다.
두 번째 매개변수는 타이머 함수를 호출하는 오브젝트이다.
세 번째 매개변수는 타이머가 발동할 때마다 호출될 함수이다.
네 번째 매개변수는 타이머가 호출될 시간이다. 만약 값을 1로 두면 1초에 한 번씩 함수가 호출된다.
다섯 번째 매개변수는 타이머의 반복 여부이다. 만약 값이 false라면 타이머는 반복되지 않고 정해진 시간에 한 번만 호출된다.

GetWorldTimerManager().ClearTimer(TimerHandle);
ClearTimer() 함수는 돌아가고 있는 타이머를 중지시키고 해당 핸들을 무효화시키는 함수이다.


-----------------------------------------------------------------------------------------------------
UE 4.19 -> 5.5

주요 변경 사항

Build.cs 파일 업데이트
UTextRenderComponent 의 입력 인자가 FString 에서 FText 로 변경되었다. 관련 형변환 처리들 진행