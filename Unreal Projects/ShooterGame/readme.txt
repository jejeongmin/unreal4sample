http://api.unrealengine.com/KOR/Resources/SampleGames/ShooterGame/index.html

[Content] 폴더 내용은 UDN 에서 다운로드 받을 것


game client 로 실행하려면 패키지를 쿠킹해야 한다.


HostGame, FindGame, JoinGame 할 수 있는 네트워크 예제 구현이 잘 되어 있다.
지정한 아이피와 포트로 DS 를 호스팅 하고, 조인 역시 가능하다.

https://forums.unrealengine.com/community/community-content-tools-and-tutorials/384-defualt-server-ports
https://forums.unrealengine.com/development-discussion/c-gameplay-programming/37282-server-port

yeah just add ?port=1234 
here is a list with the start paramters 
https://docs.unrealengine.com/en-us/Programming/Basics/CommandLineArguments#serveroptions

https://forums.unrealengine.com/development-discussion/c-gameplay-programming/22980-multiple-dedicated-servers-on-one-system
DS 가 가볍다고 이야기하는데 UE4 에서 DS 가 정말 가볍나? 이거 얘네들이 안띄워보고 하는 이야기 같은데... 2019.04.01


https://wiki.unrealengine.com/Dedicated_Server_Guide_(Windows_%26_Linux)
DS 에서 physics 를 on/off 할 수 있었네? 언리얼3 에도 이게 있나?
한다면 성능에 미치는 영향은 어느 정도일까? 2019.04.01

## ShooterGame

'jejeongmin' 이라는 키워드로 검색하면 코드 작성 및 분석 구간 검색 가능

- 캐릭터 조정
  - 기본 이동
  - 카메라 회전
  - 점프
  - 스프린트

- 무기
  - 발사
  - 재장전
  - 줌인/아웃
  - 무기 교체
  - 총기 트레일

- 아이템
  - 총탄
  - 회복아이템

- 레벨
  - 레벨 블루프린트 분석
  - 레벨 구성 분석
  - 원경 분석

- HUD
  - 플레이 타임
  - Kills
  - 트로피
  - HP
  - 장전탄환수
  - 스코어보드

- GameMode
  - FFA
  - TDM

- 멀티플레이
  - 게임 매칭 처리
  - 멀티 플레이 이동
  - 멀티 플레이 발사 / 피격
  - TPS 캐릭터 외형, 애니메이션 동기화

- UDN 관련 토픽 리딩
- 위키에 정리

