## 작업한 것

1. EnhancedInput 을 이용한 사용자 입력 처리 구현

2. Top view 처리
	tps project 를 top view 로 변경

3. EnemyCharacter class 구현
	1. ~~scenecomponent 를 이용한 눈높이 위치에서 시야 검색
	2. trace line 그리기
	3. 플레이어를 발견할 경우 플레이어를 향해 캐릭터 yaw 회전
	4. visibility 채널 대신, 커스텀 EnemySight trace channel 만들어보기
	5. 타이머 통한 projectile instigator 구현
	6. Blueprint Function Library 로 시야 검사 함수 분리
	7. 1번 구현 대신 LookAtActorComponent 로 시야 검사를 액터컴포넌트로 분리

4. left shift 입력을 통한 걷기 동작 추가

5. Dodgeball projectile 구현
	1. Dodgeball collision object channel 생성 
	2. hit 처리 구현
	3. physical material 적용
	4. movement component 적용
	5. 벽에 부딪힐 때 나는 소리 추가
	6. 플레이어를 타격해서 충돌했을 때 나는 소리 추가
	7. 플레이어를 타격해서 타격 이펙트 추가
	8. 게임 배경음악 추가

6. 게임 배치 오브젝트 구현
	1. wall 구현
	2. 적 탐색, 발사체 투과하는 ghost wall 구현
	3. 게임 클리어 도착 영역, victory box 구현

7. DodgeballCharacter 구현
	1. HealthComponent 구현으로 체력 구현 처리
	2. HealthInterface 로 체력 소진 시 처리를 override 처리

8. UMG 기반 UI 추가
	1. 게임종료시 재시작 버튼 추가
	2. 플레이어 캐릭터 체력 바 추가
	3. 게임 종료시 빠져 나가기 버튼 추가


## 작업할 것

1. 시야에 갑자기 나타날 경우 EnemyCharacter 가 Player 를 향해 한번에 회전하는 것 부자연스러움. 보간으로 회전하도록 변경
2. DodgeballCharacter 가 특정 장애물 뒤에 숨으면, CameraArm 이 땡겨지는 문제 수정, collision 설정으로 수정 가능
3. 빅토리 박스에 터치되어 게임 클리어 되면 게임 클리어 UI 띄우기
4. 닷지볼에 몇 번 맞으면 파괴되는 엄폐물 벽 추가
5. 만들어진 오브젝트를 이용한 간단한 레벨 구성
6. 적 캐릭터 정해진 범위 걸어다니면서 플레이어를 색적하는 기능 추가
	1. 걷기, 멈추기, 되돌기 애니메이션 추가
	2. AI Behavior 통한 상태 기반 구현
7. 보스 스테이지 추가
8. 보스 기능 구현 - 네비 메시 통한 추적 기능, 전용 발사체 기능 추가
9. 플레이어 캐릭터 공격 기능 추가, 일반 캐릭터, 보스 캐릭터 공격 가능