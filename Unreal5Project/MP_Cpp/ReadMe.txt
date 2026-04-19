Q1.
언리얼 엔진 5.5 에서 3인칭 게임 템플릿으로 프로젝트를 생성한 후, Listen server 모드로 멀티 플레이를 실행했다. 
실행을 종료한 후에 아래와 같은 경고메시지가 나온다. 
Not enough login credentials to launch all PIE instances, change editor settings 
원인은 무엇이고, 수정 방법은 무엇인가?

A1.
이 경고의 원인은 PIE(Play In Editor) 멀티플레이 실행 시 필요한 “PIE 로그인 정보(credential)” 개수가 실행한 인스턴스 수보다 부족하기 때문입니다. 언리얼 에디터에는 아예 FPIELoginInfo 라는 PIE용 로그인 자격 정보 구조체가 있고, PIE 멀티플레이는 서버/클라이언트용 여러 월드를 동시에 띄워 테스트합니다. 그래서 Listen Server + Client처럼 여러 인스턴스를 띄울 때, 에디터가 각 인스턴스에 사용할 로그인 항목을 확인하다가 부족하면 저 경고를 남깁니다.

보통 이 메시지는 프로젝트가 잘못된 것이 아니라 에디터 설정이 비어 있어서 뜨는 경고입니다. 실제로 빈 프로젝트나 3인칭 템플릿에서도 재현되며, 커뮤니티에서는 Editor Preferences에서 login 항목을 찾아 플레이할 인원 수만큼 ID/비밀번호를 추가하면 해결된다고 정리되어 있습니다.

수정 방법은 다음과 같습니다.

Edit → Editor Preferences 로 들어갑니다.
검색창에 login 을 입력합니다.
PIE 관련 로그인 항목에서 플레이어 수만큼 계정을 추가합니다.
예: 2인 테스트면 2개
UserName=Player1 / Password=test
UserName=Player2 / Password=test
다시 Listen Server 모드로 PIE를 실행합니다.

추가로, ini로도 넣을 수 있습니다.

[/Script/UnrealEd.UnrealEdEngine]
PIELogins=(UserName="Player1",Password="test")
PIELogins=(UserName="Player2",Password="test")

이 방식도 실제 사용자들이 사용한 설정 예시로 공유되어 있습니다.


Q2. 
강의 중 steam 세션을 사용하려고 하면

A2. 
백그라운드에서 실제 steam client 를 실행해둬야 합니다.