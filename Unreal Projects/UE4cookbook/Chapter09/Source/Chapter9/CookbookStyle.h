#pragma once
#include "SlateBasics.h"
#include "SlateExtras.h"

/*
	여러 Slate 위젯에서 공유될 수 있는 스타일을 만드려면 스타일을 가지고 있는 영역 안에서 스타일을 유지할 객체를 만들어야 한다.
	이를 위해서 에픽에선 FSlateStyleSet 클래스를 제공한다. CSS 와 비슷한 개념이다.
	이 FSlateStyleSet 은 프로그램 전체에 걸쳐 일관되게 적용되어야 하나, 싱글턴 객체가 아니므로 사용할 FSlateStyleSet 를 전역적으로 관리할
	싱글턴 객체가 유용할 수 있다. 이 예제에서는 이 역할을 FCookbookStyle 객체가 담당한다.
*/
class FCookbookStyle
{

public:

	static void Initialize();

	static void Shutdown();

	static void ReloadTextures();

	static const ISlateStyle& Get();

	static FName GetStyleSetName();

private:

	static TSharedRef< class FSlateStyleSet > Create();

private:

	static TSharedPtr< class FSlateStyleSet > CookbookStyleInstance;
};