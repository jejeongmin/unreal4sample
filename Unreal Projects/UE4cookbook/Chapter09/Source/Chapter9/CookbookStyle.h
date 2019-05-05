#pragma once
#include "SlateBasics.h"
#include "SlateExtras.h"

/*
	���� Slate �������� ������ �� �ִ� ��Ÿ���� ������� ��Ÿ���� ������ �ִ� ���� �ȿ��� ��Ÿ���� ������ ��ü�� ������ �Ѵ�.
	�̸� ���ؼ� ���ȿ��� FSlateStyleSet Ŭ������ �����Ѵ�. CSS �� ����� �����̴�.
	�� FSlateStyleSet �� ���α׷� ��ü�� ���� �ϰ��ǰ� ����Ǿ�� �ϳ�, �̱��� ��ü�� �ƴϹǷ� ����� FSlateStyleSet �� ���������� ������
	�̱��� ��ü�� ������ �� �ִ�. �� ���������� �� ������ FCookbookStyle ��ü�� ����Ѵ�.
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