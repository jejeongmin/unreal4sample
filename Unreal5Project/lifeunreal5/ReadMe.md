��������  ���� ��尡 �����ϸ� ���� �⺻�� �Ǵ� ���� ��� Ŭ������ GameModeBase �̸�, ���⿡ ��Ʈ��ũ ���� ����� �� ���� ����ϰ� �ִ� GameMode Ŭ������ �ֽ��ϴ�.

c++ class ���� �۾��� ������, �ش� class �� ��� ���� BluePrint class �� ������� �ʴ� �𸮾� ���װ� �幰�� ���� �� �ִ�.
�� ��� �����͸� �ٽ� �Ѱų� �ϸ�, ���ƿ��� ��쵵 ������, ���δ� BluePrint class �� �����ϰ�, �ٽ� ������ؾ� �ϴ� ��쵵 �ִ�.
�׷� �� �ʱⰪ�� Blue print class ���� �Ǿ� �ִٸ�, �Ź� �����ϴ� ���� ���ŷο� ���̴�.
�̷� ���� c++ class �� �����ڿ��� �ʱ�ȭ�� �Ǿ� ������, ȿ������ ���̴�. 
-> �׷��� �̷��� ¯������ ������ blue print class �� �ٽ� �����ؾ� �ȴٰ�? �׳� Rebuild all �ϰ� Editor �Ѹ� �� �� ������.. �ش� ��Ȳ ����� üũ�غ��߰ڴ�.

c++ �ҽ� �ڵ带 �������� �� �𸮾� �𸮾� ��� ������ ��� ������ �м��Ͽ� Ŭ������ ��Ÿ ������ UClass ��� Ư���� Ŭ������ �����մϴ�.
��Ÿ ������ �뷫 �𸮾� ������Ʈ�� ���� ���� ������ � �Ӽ�(��� ����) �� �Լ����� �ִ����� ��Ÿ���ϴ�.
�� ������ ��Ÿ�� �ÿ� Ư�� Ŭ������ �˻��ϰ� �� Ŭ������ �Ӽ��̳� ��� �Լ��� ȣ���ϴ� �� Ȱ��� �� �ֽ��ϴ�.
Java �� C# ���� ���� Ȱ���ϴ� ���÷��� ����� c++ ���� ����� �� �ְ� �ϱ� ���� �𸮾󿡼� �����ϴ� ���¶�� �� �� �ֽ��ϴ�.

�������� �Ϸ�ǰ� �𸮾� �����͸� �����Ű�� UObject �� ��� �޴� �𸮾� ������Ʈ�� �����ڿ��� �ν��Ͻ��� �����ϴµ�
�̸� Ŭ���� �⺻ ��ü, �ٿ��� 'CDO'(Class Default Object) ��� ��Ī�մϴ�.
CDO�� �𸮾������Ʈ�� �⺻������ �����ϴµ� ���˴ϴ�.

�������ڸ� c++ Ŭ������ �������ϸ�  ���� �𸮾� ������Ʈ�� ������ ���� UClass �� ��������� �𸮾� �����͸� �����ϸ� ������ �ڵ带 �����Ͽ�
Ŭ���� �⺻ ��ü CDO �ν��Ͻ��� �����մϴ�. ��, ǥ�� c++�ʹ� �ٸ��� �𸮾� �������� �����ڴ� �ν��Ͻ��� �ʱ�ȭ�� CDO�� ����� ���� ������ �ֽ��ϴ�.

���������� �ν��Ͻ��� ������ �� �Ź� �ʱ�ȭ ��Ű�� �ʰ� �� CDO �� �����Ͽ� �����մϴ�.
�������Ʈ�� ���� ���� �����ڿ� ������ �θ� �𸮾� �������� CDO ������ �̿��Ͽ� �������Ʈ�� ����ϴ�.

LineTraceSingleBy �� �����ϴ� �Լ��� ������ ���� �� ó�� ���� ��ü�� ��ȯ�ϴ� �Լ��Դϴ�.
LineTraceMultiBy �� �����ϴ� �Լ��� ���ο� �浹�� ��� ��ü�� TArray ���·� ��ȯ�մϴ�.

�츮�� ������ �Լ����� ������Ʈ�� ����� �� ����� CreateDefaultSubobject() �� ���ڷ� �־��� ���ڿ� ���� GetDefaultSubobjectByName() �Լ��� ã�� ���Դϴ�.
���� CreateDefaultSubojbect() �Լ� �ȿ� ���� ���ڿ��� ���� ������ �ٸ� ������Ʈ�� ������ �ȵ˴ϴ�. �ݵ�� ������ ���ڿ� �̾�� �մϴ�.



# PostEditChangeProperty ��� ����

`PostEditChangeProperty`�� �𸮾� �����Ϳ��� �Ӽ� ���� ������ �� ȣ��Ǵ� �Լ���, Ư�� �Ӽ��� ���� �ٲ���� �� �׿� ���� **��ó�� �۾�**�� ������ �� �ְ� ���ݴϴ�. �ַ� �����Ϳ��� �ǽð� �ǵ���� �����ϰų�, ���õ� �Ӽ� ���� ����ȭ�ϰų�, �����Ϳ����� �۵��ϴ� Ư�� ������ ������ �� �����մϴ�. ���� �� ���� ���� ��� ���ø� �Ұ��մϴ�.

---

## 1. �Ӽ� �� ����ȭ

`PostEditChangeProperty`�� Ȱ���ϸ� Ư�� �Ӽ��� ����Ǿ��� �� �ٸ� ���� �Ӽ� ���� ����ȭ�� �� �ֽ��ϴ�. ���� ���, ĳ������ `MaxHealth`�� ����Ǿ��� �� `CurrentHealth`�� `MaxHealth`�� ���߾� �ڵ����� ������ �� �ֽ��ϴ�.

```cpp
void AMyCharacter::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
    Super::PostEditChangeProperty(PropertyChangedEvent);

    FName PropertyName = (PropertyChangedEvent.Property != nullptr) ? PropertyChangedEvent.Property->GetFName() : NAME_None;

    if (PropertyName == GET_MEMBER_NAME_CHECKED(AMyCharacter, MaxHealth))
    {
        CurrentHealth = MaxHealth;
    }
}
```

---

## 2. �Ӽ� ���� ��ȿ�� �˻� �� ����

�����Ϳ��� �Ӽ� ���� ���Ƿ� �����ϴ� ����, �������� ���� �ʰų� �ý��ۿ� ������ �� �� �ִ� ���� �Էµ� �� �ֽ��ϴ�. `PostEditChangeProperty`���� ��ȿ�� �˻縦 ���� ��� ���� ���� ���� �ԷµǾ��� �� �����ϰų� ��� ǥ���� �� �ֽ��ϴ�.

```cpp
void AMyActor::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
    Super::PostEditChangeProperty(PropertyChangedEvent);

    FName PropertyName = (PropertyChangedEvent.Property != nullptr) ? PropertyChangedEvent.Property->GetFName() : NAME_None;

    if (PropertyName == GET_MEMBER_NAME_CHECKED(AMyActor, Speed))
    {
        if (Speed < 0.f)
        {
            Speed = 0.f;
            UE_LOG(LogTemp, Warning, TEXT("Speed cannot be negative. Resetting to 0."));
        }
    }
}
```

---

## 3. �����Ϳ��� �ð��� �ǵ�� ����

���� ���, ������Ʈ�� ũ�⳪ ������ ����Ǿ��� �� �ǽð����� ��鿡 �ݿ��� �����Ϳ��� �ð����� �ǵ���� ������ �� �ֽ��ϴ�. �̸� ���� ��Ƽ��Ʈ�� �����̳ʰ� �ٷ� ����� Ȯ���� �� �ֽ��ϴ�.

```cpp
void AMyVisualActor::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
    Super::PostEditChangeProperty(PropertyChangedEvent);

    FName PropertyName = (PropertyChangedEvent.Property != nullptr) ? PropertyChangedEvent.Property->GetFName() : NAME_None;

    if (PropertyName == GET_MEMBER_NAME_CHECKED(AMyVisualActor, Color))
    {
        // �޽��� ������ �ǽð� ������Ʈ
        UpdateMeshColor(Color);
    }
}
```

---

## 4. ���� ������Ʈ ������Ʈ

�����Ϳ��� Ư�� �Ӽ��� ������ ��, ���õ� �ٸ� ������Ʈ�� ������Ʈ���� ������ ���ľ� �ϴ� ��찡 �ֽ��ϴ�. ���� ���, `LightIntensity` �Ӽ��� ����Ǹ� ������Ʈ�� ����� ����Ʈ ������Ʈ�� ���⵵ �Բ� ������Ʈ�ϴ� ����Դϴ�.

```cpp
void AMyLightActor::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
    Super::PostEditChangeProperty(PropertyChangedEvent);

    FName PropertyName = (PropertyChangedEvent.Property != nullptr) ? PropertyChangedEvent.Property->GetFName() : NAME_None;

    if (PropertyName == GET_MEMBER_NAME_CHECKED(AMyLightActor, LightIntensity))
    {
        MyLightComponent->SetIntensity(LightIntensity);
    }
}
```

---

## 5. UI ���� ���� �� �ʱ�ȭ �۾� ����

UI�� ǥ�õǴ� ���� ����� �� Ư�� �ʱ�ȭ �۾��� �������ִ� �͵� ���� ��� ����Դϴ�. ���� ���, �Ӽ� ���� ������ ������ ���� ĳ�ó� �ùķ��̼� ���¸� �ʱ�ȭ�� �� �ֽ��ϴ�.

```cpp
void AMySimulationActor::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
    Super::PostEditChangeProperty(PropertyChangedEvent);

    FName PropertyName = (PropertyChangedEvent.Property != nullptr) ? PropertyChangedEvent.Property->GetFName() : NAME_None;

    if (PropertyName == GET_MEMBER_NAME_CHECKED(AMySimulationActor, SimulationSpeed))
    {
        ResetSimulationState();
    }
}
```

---

��ó�� `PostEditChangeProperty`�� �����Ϳ��� �������̰� ȿ������ ��ũ�÷ο츦 �����ϴ� �� ������ �������, �Ӽ� ���� �� �ڵ�ȭ �۾��� ������ �ϰ����� �����ϰų�, �ǽð����� �ǵ���� �����ϴ� �� �ַ� Ȱ��˴ϴ�.




# �� ������ ���� �ǹ�

ĳ������ �����¿� �̵� ������ �����ϴ� �������� ������ �ǹ̸� ��¤���.
�� ������ ����(dot product)�� ���� ���� ���⼺�� ũ�⸦ ����� **��Į�� ��**�� ����ϸ�, ������ ���� �ǹ̸� �����ϴ�:

---

## 1. �� ������ ���� ����
- ���� ���� **���**�� ���, �� ���Ͱ� ���� **������ ����**�� ����ŵ�ϴ�.
- ���� ���� **0**�� ���, �� ���ʹ� ���� **����**�Դϴ�.
- ���� ���� **����**�� ���, �� ���Ͱ� **�ݴ� ����**�� ����ŵ�ϴ�.

---

## 2. ������ ũ��� ���� �ݿ�
- �� ������ ������ �� ������ ũ��� **������ ����**�� ���� ������ �����մϴ�.
- �������δ� ������ ���� ǥ���˴ϴ�:
  \[
  ec{A} \cdot ec{B} = |ec{A}| |ec{B}| \cos(	heta)
  \]
  ���⼭ \( 	heta \)�� �� ���� ������ �����Դϴ�.

---

## 3. ����
- ���� \(ec{A}\)�� ���� \(ec{B}\)�� �������� �󸶳� �����Ǵ��� ��Ÿ���� ���̱⵵ �մϴ�.

---


# ����ü �ִϸ��̼� �и��� ���� ��Ÿ�� ���

��ü�� ����, ��ü�� �̵� �ִϸ��̼��� ����ϴ� ���, [Layerd blend per bone] ��带 Ȱ���Ѵ�.
Ư�� bone �� �������� bone pose �� blend pose �� ��� �ִϸ��̼� �����ϴ� ����̴�.

ũ�� Section �� Notify ������� ������ �� �ִ�.
Section �� Track ����ó�� �ִϸ��̼� �������� Ư�� ��ġ�� ��Ÿ���� �����̸� �̸� �̿��� Ư�� ���� ���� �� ���� ���� �ݺ� ���� ������ ó���� �� �ֽ��ϴ�.


# CameraShake ���

## 1. Sequence Camera Shake Pattern
- �������� �̿��ϴ� ����� �ִϸ����Ͱ� ���� ������ ��ư��� ǥ���ϴµ� ������ ��

## 2. Wave Oscillator Camera Shake Pattern
- sine �� ���·� ī�޶� ����.
- 
## 3. Composite Camera Shake Pattern

## 4. Perlin Noise Camera Shake Pattern



# �ϳ��� �ִϸ��̼� ��Ÿ�� ���Ͽ� ���� ���� ������ �ʿ��� ����

�ϳ��� �ִϸ��̼� ��Ÿ�� ���Ͽ� ���� ���� ������ ����ϴ� ������ �پ��� �ִϸ��̼��� **���ÿ�, �׸��� ���������� ����**�ϱ� �����Դϴ�. �ַ� ������ ���� ��Ȳ���� �����ϰ� ���˴ϴ�:

---

## 1. ��ü ������ �ִϸ��̼� �и�
���� ���, ĳ���Ͱ� �޸��鼭 ��ü�� ���� �ִϸ��̼��� ����ϰ� ��ü�� ��� �޸��� �ִϸ��̼��� ����ϵ��� �ϴ� ����Դϴ�. ��ü�� ��ü�� �и��Ͽ� ���� �ٸ� �ִϸ��̼��� ������ �� �ֽ��ϴ�.

---

## 2. �پ��� ��Ȳ������ �ִϸ��̼� ó��
��Ÿ�� ���Ͽ� ���� ������ �����, ��Ȳ�� ���� ������ �ִϸ��̼��� �����ؼ� ����� �� �ֽ��ϴ�. ���� ���, **���� �� ����**, **�޸��� �� ��ȣ�ۿ�**�� ���� ���� ������ �ս��� ������ �� �ֽ��ϴ�.

---

## 3. �ִϸ��̼� �켱���� �� ���� ����
���� ������ ����ϸ� �ִϸ��̼� ���� �켱������ �����ϰų� ������ ���� �ڿ������� ��ȯ�� ������ �� �ֽ��ϴ�. ���Ը��� ���� �Ķ���͸� �ٸ��� �����Ͽ� �ִϸ��̼��� ���� �����ϰ� ������ �� �ֽ��ϴ�.

---

�̸� ���� **��Ȳ�� ����**�� **�ڿ������� ������**�� ���ÿ� �޼��� �� �־�, ������ �ִϸ��̼��� �ʿ��� ĳ���� ������ �ʼ����Դϴ�.


# �׺���̼�

���� ���� ��û ū ����� ��, �ָ� �ִ� ���� Ÿ���� ã�Ƽ� ����, �ִ��� ��η� �ٷ� �̵��ϴ� ���� ���ڿ������� �� �ִ�.
�̷� �� AI �� ������ �� �ִ� ������ (��)������ �� ������ �ش� ���� �ȿ� Ÿ���� ���� �� �̵��ϵ��� ó���� �� �ִ�.
�� �ڿ������� ���� �� ���Ƽ� ���� ����� ������ �� ����Ѵ�.


# UMG

## Anchor

UI�� ��� ��Ҵ� ���̾��Ű���� �θ� �������� ��ġ�ϰ� �˴ϴ�. �� �� �θ��� ��� �������� ��ġ�ϴ����� ���� ������ ��Ŀ�Դϴ�.

## ����

�ڽ� ������ ���� ������ 3���� Ÿ������ �з� �����մϴ�.

1. �ټ��� �ڽ��� ���� �� �ִ� ���� ( canvas panel, horizontal box ��)
2. �� ���� �ڽ��� ���� �� �ִ� ����(Button ��)
3. �ڽ��� ���� �� ���� ����(Text, Progress bar ��)

��ġ�� ���� ��ġ�� ����� Overlap �� Ȱ���ؼ� ������ �� �� ��ġ�� ���ֽ��ϴ�.

Apperance blur strength �� 3���� �����ϸ� �̹����� �ѿ��� ����� ���Դϴ�.
UMG �� ���̾��Ű���� �ϴܿ� ��ġ�� ���� ���� �տ� �ִ� ������ �νĵ˴ϴ�.
�̹��������� Z-order �Ӽ��� �̿��ϸ� ���̾��Ű�� ������ �����ϰ� �տ� �ִ� ������ �νĵǸ� �����ϰ� ���̰� �˴ϴ�.

# ����Ÿ�� �̿��� �̴ϸ� ����

# blur ó�� �̿��� UI ���� ���� ȿ�� ����