; 스타트업 컨텐츠 패키지를 필요로 함
; 용량 문제로 git 에는 올리지 않음
StarterContent


HowTo_AutoCamera
----------------
둥둥 떠 다니는 카메라 액터와
카메라를 관리하는 CameraDirector 를 만들어
여러 Camera 로 시점 이동 구현 ( SetViewTarget / SetViewTargetBlend )

CameraDirector 는 필요한 카메라 관리에 필요한 속성들을 UPROPERTY 로 관리해
에디터에서 편집할 수 있도록 했다.

CameraDirector 는 화면에 렌더링되지는 않지만,
월드 상에 배치되어야 CameraDirector 의 속성 편집을 통해 원하는 기능을
활용할 수 있기 때문에 Actor 를 상속 받는다.