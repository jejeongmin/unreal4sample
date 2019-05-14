용량 문제로 Content 폴더에 StarterContent, AnimStarterPack 는 제외하고 올렸습니다.
프로젝트 정상 실행을 위해 스타터컨텐츠팩을 해당 폴더에 추가해야 합니다.

기본 설정으로 테스트하려고 하면 제대로 되지 않는다.
플레이 버튼 옆의 삼각형을 누르고 고급 설정으로 들어가자. 그러면 레벨 에디터 > 플레이 설정 화면이 나온다.
Multiplayer Options 로 가서 단일 프로세스 사용 항목의 체크를 해제하고 Play As Client 로 설정해야 여러 클라이언트를 개별적으로 실행할 수 있다.
이제 테스트를 수행하면 제대로 될 것이다.

## NS
- Listen Server 기반의 멀티 플레이 구현
- GameState / PlayerState 리플레케이션 구현
- Spawn point 구현
- hit line 표시