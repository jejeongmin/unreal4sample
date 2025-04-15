----------------------------------------------------------------------------------------------------
HowTo_UMG

- PlayerController ���� UI �Է��� ���� �Է� ���� ���� ����

- UserWidget �� �������Ʈ �Լ� ȣ��� ������ �� �ִ� GameMode ��ü�� c++ �� ����

- ���� GameMode �� �������Ʈ Ŭ������ �ٽ� ���� ���� ��ü ����

- Slate �� �̿��� GameMenu Ŭ���� ����

- �������Ʈ ȣ���� ���� Button Click, Input Validator ����


----------------------------------------------------------------------------------------------------
�̹� ���ǿ��� ��� ��(��ó: https://wergia.tistory.com/131?category=807793 [������ ���α׷��� ��Ʈ])


1. �𸮾� ��� ���Ӽ�

�𸮾� ������ ����� �ټ��� ���� �������� �ְ�, �� �߿� �ʿ��� ����� ��� ����ϴ� ����̴�. 
�̹� ���� ó�� �κп� build.cs���Ͽ��� ��� ���Ӽ��� ������ ���� ���Ұ�����, 
�⺻������ �𸮾��� Core, CoreUObject, Engine, InputCore ����� ����ϰ� �־���, 
UI�� ���õ� ����� ����ϱ� ���ؼ� UMG ���� Slate, SlateCore ����� ������ �߰����־���.

������ ��������, �𸮾� ������ Ŀ���͸���¡�ϰ��� �� ��, ���Ӱ� �߰��ϴ� ����� �̷��� ���� ����� �����̰� �� ���̴�.


2. TSubClassOf<T>

UClass Ÿ�� �������� �����ϴ� ���ø� Ŭ����. 
TSubClassOf�� ���޵� �μ��� ���ø� ���ڷ� ���� Ÿ�԰� ��ġ�ϰų� 
���ø� ���ڷ� ���� Ÿ���� ��ӹ��� Ÿ�������� ��Ÿ�� �߿� Ȯ���ϵ��� �����ִ� Ŭ�����̴�.


3. UUserWidget

UUserWidget* UserWidget;
Widget Blueprint�� ���ؼ� Ȯ���� �� �ִ� ����� ����.

UserWidget->AddToViewport();
���� ������ �� ��Ʈ�� �߰��ϴ� �Լ�.

UserWidget->RemoveToViewport();
���� ������ �� ��Ʈ���� �����ϴ� �Լ�.


4. AActor::GetWorld()

GetWorld();
UWorld ��ü�� �������� �Լ�. UWorld�� ���ͳ� ������Ʈ���� �����ϴ� ���̳� ����ڽ��� �ֻ��� ��ü�̴�.


5. CreateWidge()

CreateWidge(GetWorld(), newWidget);
������ �����ϴ� �Լ�


6. APlayerController::SetInputMode()

SetInputMode(FInputModeGameAndUI());
�÷��̾� ��Ʈ�ѷ��� �Է� ��带 �����ϴ� �Լ�. Game �Է¸� ������, UI �Է¸� ������, �ƴϸ� �� �� �������� ���� �� �ִ�.


7. UPROPERTY()

UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UMG_Game")

Ŭ������ ��� ������ ���̴� ��ũ��. �������� ���� ������ ���� �� �ִ�.
EditAnywhere�� ������ ������ �гο� ������ �����ϴ�.
BlueprintReadOnly�� �������Ʈ���� ������ �Ұ����ϰ� �б⸸ �����ϴ�.
Category�� �������Ʈ���� �ҷ��� ��, ī�װ��� �з��ؼ� ã�� ���� ������ش�.


8. UFUNCTION()

UFUNCTION(BlueprintCallable, Category = "UMG_Game")
�Լ��� ���̴� ��ũ��.
BlueprintCallable�� �������Ʈ���� ȣ�⸸ �����ϴٴ� �ǹ��̴�.



