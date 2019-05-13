## Chapter08

- editor moudule 개발
- UENUM 사용 예시
- Sliding Door 구현
- PostEditChangeProperty 사용 예시
- SweepSingleByChannel 을 이용한 line tracing 예시
- King 이 죽으면, 주변의 Peasants 들이 도망가는 예시


에디터 모듈을 따로 분리해두면 결과적으로 엔진이 에디터 모드에서 실행될 때만 로드돼 에디터 전용 코드를 내부에 둘 수 있는 새로운 모듈을 만드는 게 좋다.

에디터 모듈에서 변경된 코드는 런타임 모듈의 코드와 동일한 방식으로 핫-리로드를 지원하지 않는다.
생성된 헤더 파일의 변경 사항을 언급하는 컴파일 오류가 발생하면 편집기를 닫고 IDE 에서 다시 리빌드한다.

책에는 아래와 같이 프로젝트 파일이 되어 있는데 왜 코드에서는 같지도 않을 뿐더러 안돌아가는 거냐? 짜증난다.
책과 예제가 아예 내용이 안맞다니.

{
	"FileVersion": 3,
	"EngineAssociation": "4.19",
	"Category": "",
	"Description": "",
	"Modules": [
    {
      "Name": "Chapter8",
      "Type": "Runtime",
      "LoadingPhase": "Default"
    },
    {
			"Name": "UE4CookbookEditor",
			"Type": "Editor",
      "LoadingPhase": "PostEngineInit",
      "AdditionalDependencies": [
        "Engine",
        "CoreUObject"
      ]
		}
	]
}

위 모듈이 예제에서 동작하지 않아, 이후 코드 작성은 테스트할 수가 없다.
주로 에디터에서 UI 적인 요소를 추가하는 거라서 작업할 이슈가 별로 없을 것 같긴 하다만..
그래도 나중에 이 문제 찬찬히 봐서 해결한 후에 하나씩 기능 완성하고 주석 달아두자.

- 새 툴바에 버튼 만들기
- 새 메뉴에 엔트리 만들기
- 새 에디터 창 만들기
- 새 에셋 타입 만들기
- 에셋에 대한 사용자 정의 ContextMenu 만들기
- 새 콘솔 명령 만들기 ( 이건 UE3 때보다 훨씬 까다롭게 변했네 )
- 블루프린트에서 새로운 그래프 핀 비주얼라이저 만들기
- 사용자 정의 세부 정보 패널을 사용해 타입 검사하기


