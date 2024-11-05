레벨마다  게임 모드가 존재하며 가장 기본이 되는 게임 모드 클래스는 GameModeBase 이며, 여기에 네트워크 관련 기능을 더 많이 담당하고 있는 GameMode 클래스가 있습니다.

c++ class 에서 작업한 내용이, 해당 class 를 상속 받은 BluePrint class 에 적용되지 않는 언리얼 버그가 드물게 있을 수 있다.
이 경우 에디터를 다시 켜거나 하면, 돌아오는 경우도 있지만, 때로는 BluePrint class 를 삭제하고, 다시 재생성해야 하는 경우도 있다.
그럴 때 초기값이 Blue print class 설정 되어 있다면, 매번 설정하는 것이 번거로울 것이다.
이럴 때는 c++ class 의 생성자에서 초기화가 되어 있으면, 효율적일 것이다. 
-> 그런데 이렇게 짱무식한 이유로 blue print class 를 다시 생성해야 된다고? 그냥 Rebuild all 하고 Editor 켜면 될 것 같은데.. 해당 상황 생기면 체크해봐야겠다.

c++ 소스 코드를 컴파일할 때 언리얼 언리얼 헤더 툴에서 헤더 파일을 분석하여 클래스의 메타 정보를 UClass 라는 특별한 클래스에 저장합니다.
메타 정보는 대략 언리얼 프로젝트의 계층 구조 정보와 어떤 속성(멤버 변수) 및 함수들이 있는지를 나타냅니다.
이 정보는 런타임 시에 특정 클래스를 검색하고 그 클래스의 속성이나 멤버 함수를 호출하는 데 활용될 수 있습니다.
Java 나 C# 같은 언어에서 활용하는 리플렉션 기능을 c++ 에서 사용할 수 있게 하기 위해 언리얼에서 제공하는 형태라고 볼 수 있습니다.

컴파일이 완료되고 언리얼 에디터를 실행시키면 UObject 를 상속 받는 언리얼 오브젝트의 생성자에서 인스턴스를 생성하는데
이를 클래스 기본 객체, 줄여서 'CDO'(Class Default Object) 라고 지칭합니다.
CDO는 언리얼오브젝트의 기본설정을 세팅하는데 사용됩니다.

정리하자면 c++ 클래스를 컴파일하면  먼저 언리얼 오브젝트의 정보를 담은 UClass 가 만들어지고 언리얼 에디터를 실행하면 생성자 코드를 실행하여
클래스 기본 객체 CDO 인스턴스를 생성합니다. 즉, 표준 c++와는 다르게 언리얼 엔진에서 생성자는 인스턴스를 초기화해 CDO를 만들기 위한 목적이 있습니다.

엔진에서는 인스턴스를 생성할 때 매번 초기화 시키지 않고 이 CDO 를 복제하여 생성합니다.
블루프린트의 설정 값을 생성자에 지정해 두면 언리얼 엔진에서 CDO 정보를 이용하여 블루프린트를 만듭니다.

LineTraceSingleBy 로 시작하는 함수는 라인을 쏴서 맨 처음 맞은 물체를 반환하는 함수입니다.
LineTraceMultiBy 로 시작하는 함수는 라인에 충돌한 모든 물체를 TArray 형태로 반환합니다.

우리가 생성자 함수에서 컴포넌트를 등록할 때 사용한 CreateDefaultSubobject() 에 인자로 넣어준 문자열 값을 GetDefaultSubobjectByName() 함수가 찾는 것입니다.
따라서 CreateDefaultSubojbect() 함수 안에 들어가는 문자열은 액터 내부의 다른 컴포넌트와 같으면 안됩니다. 반드시 유일한 문자열 이어야 합니다.



# PostEditChangeProperty 사용 예시

`PostEditChangeProperty`는 언리얼 에디터에서 속성 값이 수정된 후 호출되는 함수로, 특정 속성의 값이 바뀌었을 때 그에 따른 **후처리 작업**을 수행할 수 있게 해줍니다. 주로 에디터에서 실시간 피드백을 제공하거나, 관련된 속성 값을 동기화하거나, 에디터에서만 작동하는 특정 로직을 실행할 때 유용합니다. 여기 몇 가지 좋은 사용 예시를 소개합니다.

---

## 1. 속성 간 동기화

`PostEditChangeProperty`를 활용하면 특정 속성이 변경되었을 때 다른 관련 속성 값을 동기화할 수 있습니다. 예를 들어, 캐릭터의 `MaxHealth`가 변경되었을 때 `CurrentHealth`를 `MaxHealth`에 맞추어 자동으로 변경할 수 있습니다.

```cpp
void AMyCharacter::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
    Super::PostEditChangeProperty(PropertyChangedEvent);

    FName PropertyName = (PropertyChangedEvent.Property != nullptr) ? PropertyChangedEvent.Property->GetFName() : NAME_None;

    if (PropertyName == GET_MEMBER_NAME_CHECKED(AMyCharacter, MaxHealth))
    {
        CurrentHealth = MaxHealth;
    }
}
```

---

## 2. 속성 값의 유효성 검사 및 제한

에디터에서 속성 값을 임의로 변경하다 보면, 논리적으로 맞지 않거나 시스템에 영향을 줄 수 있는 값이 입력될 수 있습니다. `PostEditChangeProperty`에서 유효성 검사를 통해 허용 범위 밖의 값이 입력되었을 때 수정하거나 경고를 표시할 수 있습니다.

```cpp
void AMyActor::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
    Super::PostEditChangeProperty(PropertyChangedEvent);

    FName PropertyName = (PropertyChangedEvent.Property != nullptr) ? PropertyChangedEvent.Property->GetFName() : NAME_None;

    if (PropertyName == GET_MEMBER_NAME_CHECKED(AMyActor, Speed))
    {
        if (Speed < 0.f)
        {
            Speed = 0.f;
            UE_LOG(LogTemp, Warning, TEXT("Speed cannot be negative. Resetting to 0."));
        }
    }
}
```

---

## 3. 에디터에서 시각적 피드백 제공

예를 들어, 오브젝트의 크기나 색상이 변경되었을 때 실시간으로 장면에 반영해 에디터에서 시각적인 피드백을 제공할 수 있습니다. 이를 통해 아티스트나 디자이너가 바로 결과를 확인할 수 있습니다.

```cpp
void AMyVisualActor::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
    Super::PostEditChangeProperty(PropertyChangedEvent);

    FName PropertyName = (PropertyChangedEvent.Property != nullptr) ? PropertyChangedEvent.Property->GetFName() : NAME_None;

    if (PropertyName == GET_MEMBER_NAME_CHECKED(AMyVisualActor, Color))
    {
        // 메쉬의 색상을 실시간 업데이트
        UpdateMeshColor(Color);
    }
}
```

---

## 4. 관련 오브젝트 업데이트

에디터에서 특정 속성을 변경할 때, 관련된 다른 오브젝트나 컴포넌트에도 영향을 미쳐야 하는 경우가 있습니다. 예를 들어, `LightIntensity` 속성이 변경되면 오브젝트에 연결된 라이트 컴포넌트의 세기도 함께 업데이트하는 경우입니다.

```cpp
void AMyLightActor::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
    Super::PostEditChangeProperty(PropertyChangedEvent);

    FName PropertyName = (PropertyChangedEvent.Property != nullptr) ? PropertyChangedEvent.Property->GetFName() : NAME_None;

    if (PropertyName == GET_MEMBER_NAME_CHECKED(AMyLightActor, LightIntensity))
    {
        MyLightComponent->SetIntensity(LightIntensity);
    }
}
```

---

## 5. UI 설정 변경 시 초기화 작업 수행

UI에 표시되는 값이 변경될 때 특정 초기화 작업을 수행해주는 것도 좋은 사용 사례입니다. 예를 들어, 속성 값을 변경할 때마다 내부 캐시나 시뮬레이션 상태를 초기화할 수 있습니다.

```cpp
void AMySimulationActor::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
    Super::PostEditChangeProperty(PropertyChangedEvent);

    FName PropertyName = (PropertyChangedEvent.Property != nullptr) ? PropertyChangedEvent.Property->GetFName() : NAME_None;

    if (PropertyName == GET_MEMBER_NAME_CHECKED(AMySimulationActor, SimulationSpeed))
    {
        ResetSimulationState();
    }
}
```

---

이처럼 `PostEditChangeProperty`는 에디터에서 직관적이고 효율적인 워크플로우를 구성하는 데 유용한 기능으로, 속성 변경 후 자동화 작업을 정의해 일관성을 유지하거나, 실시간으로 피드백을 제공하는 데 주로 활용됩니다.




# 두 벡터의 내적 의미

캐리터의 전후좌우 이동 방향을 구현하는 과정에서 내적의 의미를 되짚어본다.
두 벡터의 내적(dot product)은 벡터 간의 방향성과 크기를 고려한 **스칼라 값**을 계산하며, 다음과 같은 의미를 가집니다:

---

## 1. 두 벡터의 방향 관계
- 내적 값이 **양수**일 경우, 두 벡터가 서로 **유사한 방향**을 가리킵니다.
- 내적 값이 **0**일 경우, 두 벡터는 서로 **수직**입니다.
- 내적 값이 **음수**일 경우, 두 벡터가 **반대 방향**을 가리킵니다.

---

## 2. 벡터의 크기와 각도 반영
- 두 벡터의 내적은 두 벡터의 크기와 **사이의 각도**에 대한 정보를 포함합니다.
- 수식으로는 다음과 같이 표현됩니다:
  \[
  ec{A} \cdot ec{B} = |ec{A}| |ec{B}| \cos(	heta)
  \]
  여기서 \( 	heta \)는 두 벡터 사이의 각도입니다.

---

## 3. 투영
- 벡터 \(ec{A}\)가 벡터 \(ec{B}\)의 방향으로 얼마나 투영되는지 나타내는 값이기도 합니다.

---


# 상하체 애니메이션 분리를 위한 몽타주 사용

상체는 공격, 하체는 이동 애니메이션을 재생하는 경우, [Layerd blend per bone] 노드를 활용한다.
특정 bone 을 기준으로 bone pose 와 blend pose 를 섞어서 애니메이션 블렌드하는 기능이다.

크게 Section 과 Notify 기능으로 나눠볼 수 있다.
Section 은 Track 개념처럼 애니메이션 시퀀스의 특정 위치를 나타내는 정보이며 이를 이용해 특정 섹션 실행 및 섹션 구간 반복 등의 내용을 처리할 수 있습니다.


# CameraShake 기능

## 1. Sequence Camera Shake Pattern
- 시퀀스를 이용하는 방법이 애니메이터가 직접 느낌을 잡아가며 표현하는데 도움이 됨

## 2. Wave Oscillator Camera Shake Pattern
- sine 파 형태로 카메라를 흔든다.
- 
## 3. Composite Camera Shake Pattern

## 4. Perlin Noise Camera Shake Pattern



# 하나의 애니메이션 몽타주 파일에 여러 개의 슬롯이 필요한 이유

하나의 애니메이션 몽타주 파일에 여러 개의 슬롯을 사용하는 이유는 다양한 애니메이션을 **동시에, 그리고 독립적으로 제어**하기 위함입니다. 주로 다음과 같은 상황에서 유용하게 사용됩니다:

---

## 1. 신체 부위별 애니메이션 분리
예를 들어, 캐릭터가 달리면서 상체는 공격 애니메이션을 재생하고 하체는 계속 달리는 애니메이션을 재생하도록 하는 경우입니다. 상체와 하체를 분리하여 각각 다른 애니메이션을 적용할 수 있습니다.

---

## 2. 다양한 상황에서의 애니메이션 처리
몽타주 파일에 여러 슬롯을 만들면, 상황에 따라 적절한 애니메이션을 선택해서 재생할 수 있습니다. 예를 들어, **점프 중 공격**, **달리는 중 상호작용**과 같은 복합 동작을 손쉽게 구성할 수 있습니다.

---

## 3. 애니메이션 우선순위 및 블렌딩 설정
여러 슬롯을 사용하면 애니메이션 간의 우선순위를 설정하거나 블렌딩을 통해 자연스러운 전환을 구현할 수 있습니다. 슬롯마다 블렌딩 파라미터를 다르게 설정하여 애니메이션을 더욱 세밀하게 조정할 수 있습니다.

---

이를 통해 **상황별 제어**와 **자연스러운 움직임**을 동시에 달성할 수 있어, 복잡한 애니메이션이 필요한 캐릭터 구현에 필수적입니다.


# 네비게이션

만약 맵이 엄청 큰 경우일 때, 멀리 있는 적이 타깃을 찾아서 최적, 최단의 경로로 바로 이동하는 것은 부자연스러울 수 있다.
이럴 때 AI 가 가져올 수 있는 영역을 (한)정해줄 수 있으면 해당 영역 안에 타깃이 있을 때 이동하도록 처리할 수 있다.
즉 자연스럽게 맵을 좀 돌아서 오는 기능을 구현할 때 사용한다.


# UMG

## Anchor

UI의 모든 요소는 하이어라키에서 부모를 기준으로 위치하게 됩니다. 이 때 부모의 어디를 기준으로 배치하는지에 대한 세팅이 앵커입니다.

## 위젯

자식 개수에 따라 위젯을 3가지 타입으로 분류 가능합니다.

1. 다수의 자식을 가질 수 있는 위젯 ( canvas panel, horizontal box 등)
2. 한 개의 자식을 가질 수 있는 위젯(Button 등)
3. 자식을 가질 수 없는 위젯(Text, Progress bar 등)

위치가 서로 겹치는 경우라면 Overlap 을 활용해서 위젯을 두 개 배치할 수있습니다.

Apperance blur strength 를 3으로 설정하면 이미지가 뿌옇게 흐려질 것입니다.
UMG 는 하이어라키에서 하단에 위치한 것이 제일 앞에 있는 것으로 인식됩니다.
이미지슬롯의 Z-order 속성을 이용하면 하이어라키의 순서를 무시하고 앞에 있는 것으로 인식되며 선명하게 보이게 됩니다.

# 렌터타겟 이용한 미니맵 구현

# blur 처리 이용한 UI 무기 변경 효과 구현