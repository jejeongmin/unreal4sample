c++ 이 아닌 블루프린트 로직만으로 간단한 FPS 샘플 구현

아래 데이터는 git 에 올리지 않았음
예제로부터 다운로드 하던가, 게임스타터 팩에서 복사해올 것
Content / StarterContent 


[언리얼 엔진 4 블루프린트 비주얼 스크립팅] 브렌든 스웰 저, 문기영 역

위 책의 예제 소스인데 3년전 엔진 버전으로 제작된 소스여서 빌드 안되는 문제를
unreal 4 ver 2.21 기준으로 수정했다.

수정 내역

  - 지원되지 않아 컴파일이 안되는 블루프린트 로직 대체
  - Pawn 으 BeginPlay 로부터 Blackboard 를 얻어오는 로직에서 null 참조 오류 발생
    이유는 AIController 의 BeginPlay 에서 Run Behavior tree 를 하는데
    Pawn 의 BeginPlay 가 먼저 구동되어, behavior tree 의 초기화가 진행되지 않았음
    Controller 에서 Pawn 의 로직이 구현되도록 수정

3년 전에 작성한 책에 대한 요약
-------------------------------------

http://www.unrealengine.com
http://www.acornpub.co.kr/book/unreal4-blueprint

1장. 블루프린트를 이용한 오브젝트 상호작용

- 툴팁 화면에서 Ctrl+Alt 를 누르면 더 자세한 설명이 확대되어 나온다.
- 블루프린트에서 EventHit 는 다른 액터와 부딪힐 때 시그널된다.
- 블루프린트 노드를 검색할 때 원하는 게 나오지 않으면 검색창에서 context sensitive 를 끄고 검색해보면 된다.
- 기본적으로 월드에 배치되는 액터들은 static 이다. 상호작용이 없는 것들은 정적이어야 하며, 이것으로 속도 향상을 얻을 수 있다.
- 블루프린트를 만들 때 여러 노드를 묶어서 주석을 남길 수 있다. 여러 노드를 선택한 후 우클릭을 하면 [Create comment from selection]이 있다. 이것을 선택하면 된다.
- 블루프린트에서 Transform 을 분리하기 위해 Break Transform 을 적용하면 Transform 을 [location, rotation, scale] 로 분리할 수 있다.
- 블루프린트에서 두 개의 액션을 번걸아가면서 사용하고 싶을 때, FlipFlop 을 활용한다.

2장. 플레이어의 능력 향상

- 빨간색 트리거 노드들은 매 프레임 호출된다.
- unreal editor 의 project setting > input 에서 DefaultInput.ini 설정 파일에 들어 있는 내용에 대한 GUI 편집이 가능하다. 완전 편함.
- timeline 노드를 이용해 뭔가를 부드럽게 전환시킬 수 있다.
- projectile 속성에서 initial speed, max speed 를 변환하면 발사체의 속도가 변환된다.
- projectile 속성에서 shoud bounce 속성을 토글해서 발사체의 튕김 여부를 수정할 수 있다.
- component 의 마지막에 inheried 라고 표시된 것은 컴포넌트의 기능이 블루프린트가 아닌 c++ 에 정의되어 있다는 뜻이다.

3장. UI 화면 만들기

- UMG 에디터는 MFC 와 같은 일반적인 GUI 에디터와 비슷함.
- ui control 을 배치할 때, 스크린 크기와 비율은 다를 수 있기 때문에 UI 는 이러한 변화에 맞게 상대적으로 변해야 한다.  anchor 는 캔버스 위에서 위치를 스크린 크기에 상대적으로 조절한다.
- 변수와 ui 컨트롤의 연결은 UMG 에디터에서 한다. 실제 변수를 블루프린트나 코드에서 변경하면 자동으로 값이 ui 컨트롤에 반영된다.

4장. 제약조건과 게임 플레이 목적 만들기

- 커스텀 이벤트는 다른 이벤트에 연결된 블루프린트를 호출할 수 있게 해준다.
- Clear Timer 의 대안으로 Pause Timer 를 사용할 수도 있다. 타이머를 멈추는 것도 거의 같은 동작을 한다. 하지만 Pause Timer 의 경우 내부적인 시간을 기억하고 있기 때문에 다시 타이머가 시작됐을 때 기억해놓았던 시간부터 타이머가 돌아간다. 예를 들어, 10초 반복을 가진 타이머가있고 5초에 Pause Timer 를 이용해 멈추었다고 생각해보자. 그리고 이후에 다시 타이머를 시작하면 10초의 반복을 가졌음에도 불구하고 이전에 5초가 이미 지난 상태에서 타이머를 멈추고 재시작했기 때문에 나머지 5초가 지나면 바로 타이머가 액션을 수행한다. 이러한 차이점을 알고 용도에 맞게 사용하자.

5장. 움직이는 적 AI 만들기

레벨에 배치된 스태틱 오브젝트를 움직이면 라이팅이 다시 빌드될 필요가 있다.
이것은 스태틱 오브젝트의 라이트 정보가 변경되었기 때문이다.
게임 엔진 용어로 '구워졌다'라고 말한다.
레벨을 모두 수정했다면 Build 버튼을 눌러서 새로운 오브젝트 위치를 이용해 라이팅 정보를 리빌드할 수 있다.
또한 스태틱 오브젝트가 포함된 LightmassImportanceVolume 의 크기도 바꾸어 플레이 공간 모두가 똑같이 라이트 효과를 받게 해야 한다.

navigation mesh volume 을 잘 배치하고, P 를 누르면, 초록색으로 표시되는 NavMesh 표시를 켜고 끌 수 있다.

여러분이 사용할 2개의 기본적인 분기 노드 타입은 셀렉터(Selector) 와 시퀀스( Sequence ) 다. 셀렉터 노드는 아래쪽으로 연결된 모든 노드를 실행한다. 아래쪽으로 연결된 노드들은 자식(Children) 이라고 하며, 왼쪽에서 시작해 오른쪽으로 실행한다. 이때 실행된 자식이 성공적으로 실행됐다면 그곳에서 실행을 멈추고 다음 노드를 실행하지 않는다. 예를 들어 셀렉터가 3개의 자식을 갖고 있고 가장 오른쪽에 있는 노드가 실행되려면 앞서 있던 2개의 자식이 실행에 실패해야 한다. 그래야만 3번째 노드가 실행된다. 시퀀스 노드는 반대다. 이것은 모든 자식을 왼쪽에서 오른쪽으로 실행하며, 하나의 자식이라도 실패하면 바로 실행을 멈추고 시퀀스를 중단한다.

두 시퀀스노드의 오른쪽 상단을 보면 작은 원 안에 숫자가 적혀 있을 것이다. 이것은 노드의 실행 순서를 의미한다. 왼쪽에서 오른쪽으로 실행됐을 때 첫 번째 노드는 0의 값을 갖는다.

행동트리에서 decorator 노드는 시퀀스의 위쪽에 추가되고 시퀀스가 트리거되기 이전에 조건을 체크하는 용도로 사용된다.

6장. AI 적 업그레이드

행동트리에서 Task 는 BTTask_BlueprintBase 를 선택해 사용자가 직접 정의할 수 있다

PawnSensing 컴포넌트를 이용해 적에게 보는 능력 뿐 아니라 소리를 듣는 능력도 부여할 수 있다.

레벨 블루프린트를 수정하기 위해 레벨에디터 툴바에 있는 blueprint 버튼을 클릭한 후 open level blueprint 옵션을 선택한다.

레벨 블루프린트는 다른 블루프린트로부터 데이터를 얻을 때 캐스팅을 이용한다. 하지만 역으로 다른 블루프린트에서 레벨 블루 프린트에 있는 데이터를 얻는 방법은 쉽지 않다. 결과적으로 다른 블루 프린트에 의해 영향력을 행사하는 변수들, 예를 들어 CurrentEneryCount 같은 변수는 레벨 블루프린트 내부가 아닌 다른 블루 프린트에 생성하는 것이 좋다. 

7장.  게임상태 추적과 게임 다듬기

디버깅을 위해 PrintString 노드 같은 로그 출력을 이용하면 편하다...
음 근데 원래 kismet 에는 각 노드에 로그를 출력하는 기능이 있었는데, 지금은 없나?

일시 정지 메뉴를 Esc 에 바인딩해서 에디터 상에서는 현재 창을 닫아버리는 경우가 있다.
이럴 때는 키바인딩을 다른 키로 임시로 바꾸던가, Play 할 때, Standalone game 옵션을 선택해서 실행하면 된다.

8장. 빌드와 배포

그래픽스 설정은 Engine Scalability Setting 에서 진행

목표로 하는 플랫폼에서 우리의 게임이 어떻게 보이게 되는지 결정하는 설정들은 레벨 에디터 툴바에서 Setting 버튼을 누르고, Project Setting 을 클릭해서 지정한다.

게임 패키징을 하려면 메인 메뉴에서 File > Package Project 를 선택하면 된다.

언리얼 엔진 최신 뉴스/FAQ/포럼
https://docs.unrealengine.com/latest/INT/
https://answers.unrealengine.com/
https://forums.unrealengine.com/




unreal4-blueprint-shootergame
-------------------------------------
## AmmoPickup
- 장탄수 증가
- 사운드 효과

## CylinderTarget
- 첫번째 타격에 색상 변경
- 두번째 타격에 파괴
- 게임 클리어 체크

## FirstPersonHUD
- 크로스헤어 그리기

## FirstPersonProjectile
- 피격객체가 피직스 시뮬레이션 적용을 받는 경우 임펄스 주기
- 피직스 시뮬레이션 적용을 받지 않는다면 Damage 주기

## FirstPersonCharacter

- 캐릭터 이동 구현
- 캐릭터 시점 회전 구현
- 총 발사 구현
- 점프 구현
- 스프린트 구현
- 저격 줌 인/아웃 구현
- 플레이어 피격 구현
- 시간에 따른 플레이어 HP 회복 구현
- save system 구현
- escape 버튼 구현
- 라운드 결과 처리 구현(종료/진행)

## FirstPerson_AnimBlueprint

- Idle, Run, Jump 애님 그래프 구현


## Target, MovingTarget

- 피격시, 빨간 색으로 머터리얼 교체 구현

## HUD

- 남은 탄환, HP 등 UI 출력에 필요한 정보를 반환하는 함수 구현

## LoseMenu

- 게임 재시작, 종료 구현


## PauseMenu

- 게임 재개, 초기화 구현

## RoundTransition

- 다음 라운드 시작 구현

## FirstPersonExampleMap

- 주기적으로 적 캐릭터 스폰 로직 구현

## EnemyCharacter

- 현재 Patrol 포인트를 결정
- 피격 처리, 게임 결과 처리

## EnemyController

- Behavior tree 초기화
- BlackBoard 의 변수들을 연산

## EnemyBehavior

- Can See -> Attack -> MoveTo -> Damage Player
- Heard Sound -> Investigate Sound -> MoveTo
- Wander -> Get Next Wander Point -> MoveTo