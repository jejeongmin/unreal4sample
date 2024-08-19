언리얼 아카데미 내용 요약
=============


언리얼 엔진 소개
-------------
Bookmark 기능으로 뷰에서 원하는 앵글을 지정할 수 있음
Location / Rotation / Scale 그리드 크기를 각각 지정할 수 있음
액터를 선택하고 'F'를 누르면 뷰 화면 중앙으로 이동함
아웃라이너에서 계층 구조를 형성하면 그 액터에 실제 계층 구조가 형성됨
Tool 에 왠만한 기능은 다 있네.. 뭔가 노가다한다는 느낌이 들면 꼭 기능을 찾아보자.
아웃라이너에서 액터/액터그룹을 바로 블루프린트 클래스로 변환할 수 있다.
그러면 액터/액터그룹에 대한 재활용이 편리하다.
디테일뷰에서 디버깅을 위해 플레이 중 변경되는 property 에 대해 볼 수 있다.
디테일 패널은 여러 개를 동시에 열 수 있다. 이를 활용해 손쉬운 property 비교 가능 
컨텐츠 브라우저도 최대 4개까지 동시에 열 수 있다.
컨텐츠 브라우저에서 표시되는 폴더에 색을 입힐 수도 있네
컨텐츠 브라우저의 'Add New'에서 Contents 도 추가할 수 있다.
앞으로는 컨텐츠 추가 때문에 프로젝트 새로 생성하는 일 안해도 되겠네.
Developer 폴더는 최종 컨텐츠에 포함되지 않는 개발/테스트용 임시 컨텐츠를 넣어두는 용도이다.
Colllection 은 컨텐츠 브라우저에 의해 관리되는 에셋들에 대한 바로가기/즐겨찾기 링크 모음 정도로 이해하면된다.
컨텐츠 브라우저에 표시되는 썸네일도 바로 즉시 그 자리에서 설정이 가능하네.
썸네일 화면 즉시 바로 실시간 화면으로 변동된다.
에디터 설정에서 언어 설정 변경 가능
에디터가 포커스를 잃었을 때 CPU 점유율을 낮추는 기능도 있네.
블루프린터 에디터, 애니메이션 에디터, UMG 에디터 등 각 에디터별로 설정이 모두 가능하다.
프로젝트 세팅에서 supported platform 을 선택해서 체크할 수 있다.
프로젝트 세팅의 플랫폼>Windows 에서 스플래시 스크린, 아이콘 등을 설정할 수 있다.


블루프린트 핵심 개념
-------------
블루프린트 컴파일은 길어야 1초가 넘지 않음. 나름 장점
Level blueprint 는 one per level 이다.
blueprint 를 native c++ class 로 작성해주는 툴도 있음
블루프린트 클래스를 먼저 만들고 컴포넌트를 추가하는 식으로 완성할 수도 있지만 반대로 레벨에 액터들을 하나 이상 선택해서 완성된 액터로부터 블루프린트 클래스를 만들어 낼 수도 있다.
컴포넌트의 이름은 적절히 리네이밍, _SM(Static Mesh 의 약자) 처럼 postfix 로 한다.
컴포넌트를 조합할 때 SceanRoot 를 사용하기도 하고, BillBoard 를 Root 로 사용하기도 한다.
어떤 컴포넌트도 루트가 될 수 있다. DefaultSceanRoot 로 드래그하면 그게 Root 가 된다.
블루프린트 에디터의 컴포넌트 창에서 컴포넌트를 선택하면 그 컴포넌트에 대해 정의된 인벤트 그래프를 details 에서 확인할 수 있다. 물론 이벤트 그래프 탭으로 가서 직접 확인해도 된다.
construction script 에서 변수 옆에 눈 모양을 끄면 에디터에서
변경할 수 없게 된다.
여러 블루프린트 노드를 선택한 후 C 키를 누르면 코멘트 박스가 그 노드들을 감싸게 된다.
블루프린트 노드 로직 여러 개를 선택한 후 우측 클릭으로 Collapsed Function 하면 바로 그 로직 구간을 함수로 만들어버리네.
마찬가지로 Collapsed Macro 로 가능
Collapsed Node 로 단지 캡슐화해서 가릴 수도 있음
매크로와 함수의 차이는 매크로는 입력이 필요 없다는 것이다.
함수에는 입력이 있다.
레벨블루 프린트는 레벨에 관련된 것이므로 뷰포트가 없다.
블루프린트 클래스를 상속 받으면, 부모의 BeginPlay 등도 명시적으로 호출해줘야 한다. 물론 필요한 경우에 한해서.
블루프린트는 이벤트 기반의 작업에는 어울리나 매번 호출되어야 하는 tick 기반 작업에는 성능상의 이유로 어울리지 않는다.
Cast 해서 유효한 Target 일 경우에만 동작하게 하는 건 C++ 코드에서나 블루프린트에서나 둘다 유효하다.
두 블루프린트가 상호 참조하는 경우 Circular 가 성립해 로딩 과정에서
무한 루프가 발생하게 되므로 주의할 것.


라이팅 기초
-------------
Sky Light 가 예전의 Ambient Light 와 비슷하다. Atmosphere 분위기 등을 살릴 때 쓰기도 한다.
Baking Light 하는 게 단지 실시간/비실시간 등 성능의 문제 뿐 아니라 품질의 차이도 있구나.
당연히 시간을 더 들인 Baking Light 가 더 고품질의 그래픽을 가능하게 한다.
Global illumination, 반사광 등은 Baking Light 를 통해서만 효율적인 수행이 가능하다.
라이트 매스는 언리얼4에서 Swarm Agent 라는 프로그램을 통해 수행이 가능하다.

Lightmass Importance Volume 으로 공간을 수동 설정하면, 그 공간 내(약간의 오차를 가지고 걸친 부분까지)의
라이트매스 품질을 향상 시킨다. 보통 인게임 플레이 영역이나 카메라 컷씬에 노출되는 영역에 적용한다.
Lightmass Portal 은 SkyLight 가 존재하는 상황에서 중세 교회와 같이 실내에 빛이 충분히 들어오지 못하는 경우,
창문 영역에 맞춰서 설정해주게 되면, 외부에서 유입되는 반사광을 더 증폭해서 내부의 빛이 충분히 유입될 수 있도록 해준다.
단 실내에 충분한 라이트가 있거나, 외부에 SkyLight 가 없는 경우에는 눈에 보이는 효과가 없거나 미미하다.

LightMap 은 엔진이 자동생성해서 텍스쳐에 최종반영(multiply 를 통해)하는 일종의 후보정 텍스쳐이다.
메시에는 light map 저장을 위한 별도 UV 채널이 필요한데, static mesh 에디터에서 기본 자동 생성되며,
해상도 설정등 품질 설정이 가능하다.
3D Max 등 편집 툴에서도 라이트맵 채널 추가가 가능하다.
95% 이상, 위의 방법으로 생성된 라이트맵 UV 채널을 그대로 사용한다.
하지만 저 UV 채널을 열어보면 공백도 많고, 모델에 대한 UV 매핑도 정확하진 않다.
더 높은 라이팅 품질을 위해 UV 채널을 직접 편집해서 쓰는 경우도 드물지만 없진 않다.

Volumetric LightMass 는
Lightmass Importance Volume 내에 미리 Baking 된 Light 정보를 3D Grid(너비 조정이 가능한)에
미리 저장하여, 런타임에 동적 라이팅에 반영하기 위한 기능이다.
예를 들어보자.
그림자 진 벽 아래에 새 한마리가 날아들었다. 이 새에는 미리 구워진 그림자를 적용할 수 없다.
이 그림자 정보를 새에 반영하기 위해 새로부터 가장 가까운 그리드 노드에 저장된
라이트 정보 - 이 라이트 정보는 라이트 구울 때 미리 연산되어 저장됨 - 를 반영해 새에 라이트를 반영할 수 있다.

폭발할 때 Light 를 Spawn 해서 폭발광 효과를 만들기도 함.
Dynamic Light 는 반사광을 지원하지 않음

Stationary light 는 static light 와  movable light 가 섞인 형태로 램프갓이 좋은 활용 사례이다. 

Stationary light 는 여러 개 배치할 수 없다. 텍스쳐에 shadow map 을 저장하기 위한
컬러 채널의 개수가 한정되어 있기 때문이다.

## Outdoor light 개발
CSM ( Cascade Shadow Map )
directional light 에 의해 생성
말 그대로 다수의 그림자를 계단식으로 처리하기 때문이다.
보통 퀄리티가 다른 3개의 맵을 생성해서 거리별로 사용

## DFS( Distance Field Shdow)
distance field 라는 메시로부터 그림자를 그리기 위한 
지오메트리가 아닌 별도 정보를 생성해서 활용해 퍼포먼스를 높인다.
그러나 지오메트리로부터 한번에 정적인 DF 정보를 생성하기 때문에
움직이는 배경(나무가지)에 대한 그림자 생성이 실시간으로 되지 않는다.
대신 CSM 에 비해 빠르다.
light 의 source radius /  length 를 수정하면 형광등과 같이 긴 형태의
light 도 설정할 수 있다

## IES 는 spot light 에서만 가능한 설정이다.
light 를 원하는 형태로 projection 할 때 사용한다.
쉽게 은유하면, spot light 에 어떤 유리판 보호대가 씌워져 있어
빛이 그 유리판 보호대를 투과해 나타나는 모양을 설정한다.
이는 IES 에서 설정하는 texture 의 마스킹을 활용하는 형태로 설정되는데
이 texture 는 UE4 editor 에서 제작할 수 없고, 인터넷에서 찾아볼 수 있는
많은 무료툴로 설정한다.

그래서 위 두 방법을 혼용하여, 낮은 차수의 CSM 을 만들어 근거리에서 그림자를 
생성하고, 먼거리에서는 DF 를 이용해 원경의 그림자를 만들어 낸다.

## DFAO(Distance Field Ambient Occlusion)
Sky Light 를 이용해 생성한다.
distance field mesh 를 사용해 가짜 반사광인 Ambient Occlusion 을 만든다.
그러나 distance field 의 정밀도가 떨어지기 때문에 결과가 반드시 좋지는 않다.

sky light 는 반사광이 잘 나와야해서 주로 static light 로 설정한다.
보통 directional light 는 stationary 로 설정한다.

light function 은 light 와 material 을 blend 해서 material 에 세팅된다.
이 material 을 light property 의 light function 에 포함시켜 해당 light 에
대해 마스킹된 일종의 빛샘 효과를 만들어낸다.

예제에서는 물결에 산란된 빛이 수영자 바닥에서 비치는 효과를 보여준다.
이를 응용해 지면에 드리워진 구름의 그림자를 표현하기도 한다.

## Reflection
SSR ( Screen Space Reflection )
화면에 이미 렌더링 정보를 이용하여 material 에 reflection 을 투사해준다.
실시간 반영(누가 지나가면 reflection 에 그대로 반영)이 된다는 큰 장점이 있다. 단점은 노이즈가 좀 있는 편이고, 화면에 이미 렌더링 정보를 이용하여 2차 활용하는 것이기 때문에 시야각에 따라 화면에 렌더링 된 정보가 없다면 reflection 되는 것도 없다는 것이다.

## Reflection Capture
SSR 의 단점을 상쇄하기 위해 Reflection Capture 를 혼용해 사용한다.
Reflection Capture 는 Reflection Actor(Sphere/Box) 를 배치하면 해당 actor 에서 360도 전방위로 화면을 캡쳐하여 Reflection source를 만들어내고,
그를 활용하여 reflection 을 보여준다.
reflection 소스의 해상도는 project setting 에서 결정할 수 있으며,
런타임 메모리와 trade off 관계에 있다.
단점으로는 이미 정적으로 캡쳐해 둔 이미지를 쓰기 때문에 환경에 대한 실시간 반영이 안된다는 점이다.
위 두 방법을 혼용해 사용하는데 두 reflection 이 blend 되는 순간에는 SSR 처리 우선 순위가 더 높다.

## Planar Reflection
작은 2차원 평면 반사에 적합하며, 거울에 전형적으로 이용된다.
property 에서 실시간 반영 여부 설정이 가능하나 성능상의 이유로 안하는 것이 좋다.
project setting 에서 global clip plane 설정을 켜야 한다. 

## Render target capture
CCTV 같은 거 구현할 때 좋다.
Scene capture cube 등을 이용해 캡쳐할 카메라를 캡쳐하고
Texture target 을 설정해서 특정 텍스쳐에 실시간 캡쳐 정보를 렌더링한다.
그리고 이 texture 를 특정 material 에 투사하여 캡쳐를 적용한다.

매우 밝은 물체나 반사성이 높은 물체에는 reflection capture 를 
sphere 형태로 배치하고, 물표면, 서울 등에는 planar reflection 을 배치한다.

## Atmospheric Fog
레벨 전체에 대해 적용된다.
수평선을 만들 때 사용된다.
Directional light 에 기반해 해의 위치가 표시되며, 해의 방향(각도)에 따라
day light 가 구현된다.(노을)

## Exponential Height Fog
역시 레벨 전체 활용되며, Sun 이 표시되나 위의 것에 비하면
구름에 가린 것처럼 희미하게 표시된다.
고도에 따라 Fog 농도가 달라지게 할 수 있다.
이를 활용해 높은 첨탑이 있는 레벨 등에서는 지면에 깔린
안개를 표현할 수 있다.

## Light Shape occlusion
안개에서 나무가지 등에 가려진 부분을 어둡게(검은 빛)으로 표시함으로써 안개의 존재감을 표현

## Light Shape Bloom
위와 반대로 가려지지 않은 부분을 빛으로 더 밝게 표시함으로써 안개의 존재감을 표현

## Volumetric Fog
Exponential Fog 의 property 에서 적용 가능하며,
빛이 안개 입자에 비춰지도록 하는 정도를 조정
ex) 어두운 방안에서 TV 에서 나오는 빛
       차량의 head light
       가을 저녁의 안개조명


실시간 렌더링 기초
-------------
오클루전이랑 어떤 것이 보이고 안보이는지를 결정하는 것입니다.
그래픽 엔진의 Scalabilty 란?
1. 다양한 device 에 대한 contents resize 지원
2. 필요에 의해 렌더링 품질과 성능을 실시간 trade off 하는 것이다.
   예를 들면 아래의 명령이다. 실시간으로 그림자의 품질의 설정한다.
   >r.shadowquality [0-5]
3. deferred rendering & forward rendering 교차 지원
   deferred 가 UE4의 기본 설정이며, 좀더 고사양/고품질 렌더링에 어울린다.
   단점은 안티앨리어싱이 취약하다는 것이다. TAA(Temporal Anti-Alasing) 지원.
   GBuffer 사용 ( 포워드 렌더링은 사용하지 않음 )
   forward 는 대부분의 저사양 게임이나 제약이 있는 환경에 이용된다.

| 명령 | 의미 |
|---|---|
| >stat fps | 초당 프레임과 ms 를 화면에 출력합니다 |
| >t.maxfps 600 | 이는 초당 fps 30 or 60 의 제한을 없애줍니다. 세부적인 최적화의 효과를 없애려면 위 제한을 없애줘야 합니다. 물론 600 보다 훨씬 더 큰 값을 써도 무방합니다.|
| >stat unit | frame, game, draw, gpu 등 더 세부적인 단위 별로 ms 를 표시, 중요한 것은 game vs gpu |
| >stat rhi | 최적화를 위해 메모리와 관련된 세부적인 사항을 화면에 표시 |
| >stat scenerendering | 최적화를 위해 프로세싱과 관련된 세부적인 사항을 화면에 표시 |
| >stat gpu | 위와 같은 stat 관련된 사항들은 명령어가 아니라 뷰포트 최상단 좌측에 있는 dropdown 버튼을 통해 개별적으로 활성화할 수 있다. |
| >stat none | 위의 것들을 다 off 함 |


## https://renderdoc.org/
RenderingDoc 은 별도의 외부 프로그램으로 그래픽카드로부터 데이터를 직접 캡쳐해서 실제 화면의 렌더링에 들어가는 비용과
처리 과정을 확인할 수 있다. 최적화에 자주 활용된다.

픽셀 쉐이더의 경우 말그대로 화면의 픽셀에 후처리를 가하는 면적이 퍼포먼스에 영향을 주게 된다.
특히 반투명 처리에 경우 픽셀 쉐이더 처리를 필요로 하는데, 반투명 처리를 해야 하는 Plane 에 가까이 갈 수록 프레임이 떨어진다.
카메라를 줌해서 가까이 가면 다른 오브젝트들이 컬링되어 출력한 내용이 적어지는데 왜 느려지는가 의문이 들긴 했는데
화면 전체 영역에 대해 반투명 처리를 해야 하므로 픽셀 쉐이더가 처리해야 할 양이 많아져서 그런 것이다.
처리해야 할 객체의 양, material 의 양이 많아질 경우 draw call 이 증가하게 된다.
객체 단위로 drawcall, material 단위로 drawcall 이 발생한다.
객체가 많아지면 drawcall 이 증가하고, 한 객체를 그리기 위해 처리해야 할 material 이 많아져도 draw call 이 증가한다.

dynamic light 보다 dynamic shadow 가 성능에 더 큰 영향을 끼치게 된다.
shadow 는 결국 polygon 을 사용해 그리게 되는데, 높은 해상도의 모델에 대해 dynamic shadow 를 적용하게 되면
polygon 을 과도하게 소모하여 성능에 좋지 않은 영향을 준다


머티리얼 핵심 기초
-------------
texture 의 가로x세로 크기는 반드시 2^n 이어야 한다.
크기가 맞지 않아도 UE4 에 import 가능하긴 하나, mip map 이 형성되지 않는다.

texture format 은 UE4 editor content browser 에서 texture import 를 통해 열리는
Dialog 에서 확장자를 보면 상당히 많은 종료의 format 을 지원하는 것을 알 수 있다.
psd 는 편이성 때문에 지원되며, tga 는 미압축이며 알파채널을 지원한다.
bmp 는 알다시피 알파채널을 지원하지 않는다.
jpeg 와 같은 압축 포맷을 권장하지 않는다.

UE4 texture 의 기본 압축 포맷은 DXT or BC 이다.
texture property 의 Compression Settings 에서 볼 수 있다.
UE4 게임을 개발한다면 이 압축 포맷을 건드릴 일은 없다.
대개 Details 에서 Format 의 내용이 길다면 비압축 포맷이다.

material editor 에서 메인 노드는 material 에 대한 입력 그 자체이다.
content browser 의 texture 를 material editor 로 drag&drop 하면 texture node 가 생긴다.

PBR 은 주변 모든 것이 약간씩 빛을 반사한다고 가정한다.
Base Color 를 기반으로 Metallic / Roughness / Specular 등으로 
빛의 음영 및 상호작용을 조절해 PBR 을 구현한다.

나무의 결이나 목재 손상 부분은 roughness 값을 크게 주어, 반사를 적게 하게 한다.

material 표현식에서 자주 사용하는 것은 몇 안된다.
texture sample : texture 그 자체
constant : 보통 gray scale / brightness 을 지정
constant vector : rgb color 를 지정
tex coord(texture coordinate) : texture uv 를 지정
panner : uv 를 시간에 따라 변화시켜 텍스쳐를 표면위로 움직인다.
multiply : 두 개를 섞는다.
lerp ( linear interpolate ) :  선형 보간

emissive color : 방출광인데 constant 3 vector 를 쓰되, RGB 값을 1 이상의 값으로 입력하면 빛이 방출되는 효과를 줄 수 있다.
color picker 에서 선택하면 1 이상의 값은 입력할 수 없으므로 property editor 창에서 직접 값을 입력하자.
emissive light 는 TV, 램프, 캠프파이어 불 등에 활용한다.

world position offset 은 실제 world 에서의 vertex offset 을 뜻한다.
여기에 Constant vector 3 를 연결해주면 RGB 의 의미가 아니라 xyz 의 
의미를 가지게 된다.
vertex shader 의 기능을 material editor 에서 활용할 수 있게 해주는 것이다.

흔들리는 커튼을 예제로 world position offset 예제를 구성했다.
그런데 커튼 상단의 고정된 부분의 움직임을 억제하기 위해, 
새로운 texture sample 을 masking하기 보단 vertex color 로 커튼 상단은 검은색으로 자고 아래 쪽은 하얀색에 가깝게 주어 움직임에 대한 가중치 마스크로 활용했다.

world position offset 은 나무나 풀같은 초목에 많이 사용된다.
물표면도 world position offset 을 활용하기 좋다.

위와 같은 소소한 애니메이션에는 좋으나 충돌처리가 필요한 경우에는 사용하면 안된다.
최적화 관점에서 빛을 받지 않고 발산하기만 하는 머터리얼(TV 스크린, 불 등)은 material 의 detail 설정에서 shading model 을 unlit 으로 하는 게 좋다.

blend mode 를 사용하면 opacity mask 가 활성화된다.
mask 를 이용해 렌더링 하면 알파를 이용한 경계가 선명해진다.
이는 분명 반투명에 비해 최적화에 유리하다.

opacity 를 이용한 transparency 를 처리할 때
Screen Space 를 check 하고
Lighting mode 를 [Surface ForwardShading] 으로 해야
Metalic / Specular / Roughness 등을 설정할 수 있다.


머터리얼 제작 워크 플로우
-------------

Material Function는 자주 사용하는 매터리얼 노드들을 그룹화해서 재활용하는 것이다.
블루프린트에서의 함수, 매크로와 크게 다르지 않다.

Material Function은 컨텐츠 브라우저에서 새로 생성하면 되는데, prefix 는 MF_ 를 사용한다.

Material Function 의 Details 에서 Expose to Library 를 체크하면 우측의 함수 목록에
추가되어 쉽게 사용할 수 있다.

숙련된 개발자는 복잡한 구현을 Material Function 으로 노출하고, 비숙련 개발자는 이를 활용함으로서 작업 파이프라인을 효율적으로 구성할 수 있다.

Material Instance 는 상속개념을 구현한 것이다.
부모 Material 을 Master Material 이라고 한다.

Material Instance 에는 Details 에 조정 가능한 property 가 없는데, 이는 Master Material 에서 조정을 원하는 노드를 Parameter 로 만들면 된다. 일종의 interface 기능이라고 할 수 있다.

Material Instance 에서 자주 사용될 수 있는 노드로 Static Switch Parameter 가 있다.
블루프린트의 branch 와 비슷한 건데, 예를 들면 표면의 젖은 상태를 선택적으로 표시할 때,
혹시 Normal / Detail Normal 을 선택적으로 표시할 때 등등 활용할 수 있다.

어떤 노드는 Parameter 화 할 수 없는 것도 있다. 예를 들면 Texture Coord.
왜 그런지는 알 수 없고, 이를 우회하는 방법은 중간에 Multiply 를 넣고 곱하는 상수 값을
Parameter 화 하면 된다. 좋은 팁이네.

Material Instance 는 성능도 약~간 좋으며, 무엇보다 변경해도 쉐이더 컴파일을 발생시키지 않는다. 적극 활용할 것.

Material Paramenter Collection 은 파라메터 셋을 일종의 전역변수 객체로 만들어 사용하는 것으로 파라메터의 접근 범위를 크게 확장시킨 겁니다.

가끔 float4 를 float3 에 넣을 때 타입 오류 등이 날 수 있는데, 이럴 땐 mask 노드를 사용해 불필요한 값을 걸러주면 된다.

wind, wetness  등 월드 전체에 걸쳐 적용되어야 하는 material parameter 에 쓰기 좋다.

material layer 는 material function 으로 구현한다.
material function 은 결곽 output result 값 하나 밖에 반환하지 않는데
이를 커버하기 위해 MakeMaterialAttribute 라는 노드를 생성해
그것을 material main node 로 활용하고 그를 통해 output result 로 연결한다.

material layer 는 material function, material instance 처럼 작업 파이프라인의 효율 측면에서 좋다. 효율 뿐 아니라 전체적인 그래픽 스타일의 일관성 유지에도 좋다. 그것은 성능에도 분명히 영향을 미친다.

material layer 는 merge map 을 이용하는데 merge 맵은 하나의 텍스쳐에서
RGB 각 3채널을 이용해 material 이 적용될 마스크를 각각 구성한다.


블루프린트를 사용한 대화식 머티리얼 교체
-------------
블루프린트에서 Ctrl 누르고 핀을 옮길 수 있다.
material parameter collection 과 material instance 를 이용해서 벽과 커튼의 material base color 를 변경하는 예제이다.

블루프린트에서 색상을 선택할 때는 색상창에서 우클릭하면 복사 가능한
메뉴가 있으니 활용할 것

새로운 걸 배우기 보다는 기존에 배웠던 블루프린트, UI, 매터리얼의 개념들을 이용해 작은 레벨을 변화시키는 튜터리얼 정도이다.
영어 원어민이 아닌데, 오히려 그렇기 때문에 또박또박 발음해서 알아듣기 편하네.

UI 를 애니메이션 시키는 게 재밌네.
애니메이션을 추가하면, 여타 애니메이션 툴처럼 타임라인이 나온다.
details 창의 render transform 의 각 정보에 label 에 표시된 십자 모양을 누르면 그 값이 타임라인에 키프레임으로 잡힌다.
이를 이용해 좀 쉽게 애니메이션을 구성할 수 있다.

애니메이션 재생은 블루프린트를 이용해 할 수 있다.

node 의 dropdown 관련 pin 을 역으로 드래그해서 select 라고 치면 조건 별로 해당 dropdown 목록을 선택할 수 있게 하는 기능이 있다.

material collection 은 일종의 전역 변수로 모두 접근 된다는 장점도 있고,
전역 변수를 바꾸면 모두 한번에 바꿀 수 있다
material parameter 는 그 장점을 정확히 반대로 가진다.
상황에 맞게 응용할 것.


포스트 프로세싱 기초
-------------
post processing 은 UE4 에서는 default 로 enable 상태이다.
pp volume 을 이용해 영향을 받는 구간을 설정할 수 있고,
infinite extend 를 설정해서 레벨의 전체 구간에 적용할 수도 있다.

상당히 많은 pp 효과가 있는데 그 중 기본에 해당하는 것들은 다음과 같다.
각 효과에도 비용 대비 효과를 조절할 수 있는 세부 옵션들이 있다.
일부 효과 옵션들은 현세대 컴퓨터에서는 인게임 플레이에서 사용하기에는 무척 비싼 옵션이기 때문에 시네마틱 장면이나 비게임 애플리케이션 렌더링에만 활용하기도 한다.

- color grading
- contrast
- bloom 
   bloom 에는 intensity, threshold 와 같은 설정이 있는데, material 의 
   emissive 값에 반응해 밝기를 조절한다.
- dof
- tone mapper
- Lens exposure
- Lens Flares
- Image Effect > Grain Jitter 옛날 TV 수상기처럼 지글거리는 느낌.
- Image Effect > Vignette 모서리를 좀더 어둡게 해주는 기능, 공포 분위기
- Image Effect > Chromatic Aberration - 총기에 맞았을 때 눈에 촛점 안맞는 효과 줄 때?

스크린스페이스 라는 말은 이미 렌더링이 끝난 이미지에 추가로 적용된다는 뜻입니다.

World Setting 에 있는 Ambient Occlusion
Sky Light 의 detail 에 있는 Ambient Occlusion
Post Processing 의 Ambient Occlusion
위 세가지는 모두 다른 개념이다.

PostProcess Volume 의 크기를 조절할 때는 Transform 의 Scale 을 조정하지 말고 Brush 의 Shape 를 조정하라.
PP 에 사용할 머터리얼의 detail 에서 domain 을 PostProcessing 으로 지정해야 한다.

물속 효과를 구현하기 위해 PP 의 material 에 화면 왜곡효과를 위한 노멀맵 텍스쳐를 섞고, 거기에 엷은 파란색 vector 3 를 또 섞어준다.
PP material 은 emissive color 연결된다.


글로벌 일루미네이션
-------------
언리얼의 GI 는
정적 GI - Bake LightMaps
동적 GI - Light Propagation volume

actor 의 details 에 있는 mobility [ static | stationary | movable ] 값으로 엔진은 해당 액터의 LightMaps 생성여부를 판단한다.

각 static mash 에는 UV 채널이 2개 존재한다 [ texture / lightmap ]

lightmass 계산을 분산해서 하는게 바로 swarm agent 이다.

lightmap 퀄리티를 확인하기 위해 viewport 수정할 것
-  lightmap only
- show > lighting features > screen space ambient occlusion off 
- Exposure setting 상수 값 설정
- show > Post Processing > bloom off

위 설정을 한 후 lightmap 개선을 하는 것에는 여러 방법이 있으나, 그 중 가장 효과가 크고 먼저 시도해야 할 두 방법이 있다.

1. lightmap importance volume
lightmass 가 집중해서 연산할 영역을 결정한다.
해당 영역에 대해 비주얼 퀄리티 개선 뿐 아니라 lightmap baking 하는 시간도
단축하는 효과가 있다.

2. lightmass portal
실내 환경에서 외부 노출되는 창, 문 등에 배치하면 그 곳으로
광선, 광자가 집중되게 해준다.
역시 비주얼 퀄리티 개선, 굽기 시간 단축하는 효과가 있다.

lightmap 을 baking 하기 전에 light quality setting [ product / high / medium / preview ] 세팅하면 lightmap quality 를 지정할 수 있다.

이외에 월드세팅에서 퀄리티에 영향을 주는 주요 팩터들
indirect lighting quality
num sky lighting bounce
static lighting level scale

material 의 emissive 를 강하게 적용하는 것으로 lighting 에 영향을 줄 수 있다.
actor 의 detail 에서 use emmisve for static lighting 를 체크해야 함
위 기능은 설정이 간편한데 비해 화면에 사실성을 크게 높여준다.

동적 GI 는 당연히 실행 퍼포먼스는 더 큰 반면, 퀄리티는 떨어진다.
이걸 커려면  config / consolevariables.ini 에
r.LightPropagationVolume = 1을 추가해준다.

맵(umap) 파일 중 BuildData 라는문자열이 붙은 게 미리 구워진 lightingmap 정보이다. 해당 파일을 지우면 라이트 맵 정보가 없어진다.
동적 GI 를 쓰려면 directional light 를 movable 로 하고
해당 direction light 의 속성 중 dynamic indirect lighting 을 켜야 한다.

dynamic GI 에 대한 그래픽 품질 설정 자체는 actor 중
post process volume 을 찾아서 속성에서
Light propagation volume 관련된 정보를 조절하면 된다.