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

6. 게임 배치 오브젝트 구현
	1. wall 구현
	2. 적 탐색, 발사체 투과하는 ghost wall 구현
	3. 게임 클리어 도착 영역, victory box 구현

7. DodgeballCharacter 구현
	1. HealthComponent 구현으로 체력 구현 처리
	1. HealthInterface 로 체력 소진 시 처리를 override 처리

## 작업할 것

1. 시야에 갑자기 나타날 경우 EnemyCharacter 가 Player 를 향해 한번에 회전하는 것 부자연스러움. 보간으로 회전하도록 변경

2. DodgeballCharacter 가 특정 장애물 뒤에 숨으면, CameraArm 이 땡겨지는 문제 수정, collision 설정으로 수정 가능