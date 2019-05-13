visual studio 의 여러 버전이 설치된 컴퓨터에서 특정 VS 를 지우면 UE4 솔루션 빌드할 때
특정 라이브러리가 지워져서 빌드가 안되는 경우가 있네.
Windows OS 종류별로 설치해줘야 하는 SDK 가 달라지는 경우도 있고.

https://answers.unrealengine.com/questions/260186/unrealbuildtool-exception-systemiofilenotfoundexce.html


Unreal 4의 현재 버그라고 하는데 uproject 로부터 generating visual studio solution 을 할 때
project root 에서 Saved/Logs 폴더를 UnrealBuildTool 이 생성하지 못하는 에러가 있다.

previledge 문제로 보이는데 UnrealBuildTool 이나 탐색기를 관리자 권한으로 실행해도 동일한 문제가 나와서
그냥 수동으로 Saved/Logs 폴더를 생성해줬다.

- NewObject 를 통한 UObject 객체 생성
- 레벨에 배치된 BP_Warrior 객체의 블루프린트 함수 구현을 통한 이름 출력