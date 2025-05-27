이득우의 언리얼 C++ 게임 개발의 정석 예제

1. 언리얼 에셋 스토어에서 아래 리소스 다운로드 받을 것

InfinityBladeGrassLands
InfinityBladeWarriors
InfinityBladeWeapons


2. 스켈레톤 메시 에셋은 github 에 있는 것으로 덮어씌울 것

오른손에 무기 소켓 위치, 회전 조정

\Content\InfinityBladeWarriors\Character\CompleteCharacters\SK_Mannequin_Skeleton.uasset


## ArenaBattle

- 디아블로 스타일의 핵&슬래쉬 게임 모작

- plugin module 로 게임 모듈과 CharacterSetting 을 분리해서 구현
- UPROPERTY(config) 선언을 통한 config 파일 데이터 연동
- 4방향 게이트에 배치된 Trigger 터치를 통한 무한던전 생성
- AI BehaviorTree 구현을 통한 적 AI 구현
- Anim-Notify 를 이용한 컴보공격 입력 구현
- 웨폰 아이템 구현
- GameInstance 를 활용한 Save/Load
- 캐릭터 선택화면 구현
- 데이터테이블 에셋을 이용한 테이블 관리
- 디버깅용 공격 판정 실린더 출력 기능

## 할 일

점프했을 때는 공격하지 않게 수정 ( 완료 )
죽으면 차차 가라앉다가 없어지도록 수정 ( 완료 )
적이 죽었는데도, 탐지 하는 스피어가 계속 그려진다. ( 죽으면 StopAI 시켜버림, AI Node 중 Detect Node 에서 DrawSphere 하지 않게 됨)
문이 부드럽게 닫히도록 수정 ( 코파일럿한테 시키기만 했는데 코드 다 짜주네.. 코드 정리할 필요는 좀 있어 보이지만, 동작에 큰 문제 없음. )
컴보 공격을 하면 앞으로 이동하도록 수정




