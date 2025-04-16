; ��ŸƮ�� ������ ��Ű���� �ʿ�� ��
; �뷮 ������ git ���� �ø��� ����
StarterContent
-----------------------------------------------------------------------------------------------------

HowTo_Components

Pawn Movement Component �� �̿��� Pawn �̵��� ó���ϴ� ����

Pawn �� Camera �� Attach �� SpringArm �� �ٿ��� �����ϴ� ����� �ּ��� ���� �ڼ��� �����ߴ�.
StaticMeshComponent, Particle ���� editor �� �ƴ�, �ڵ� �󿡼� ���� Attach �ߴ�.
Particle ȿ�� on / off �����ߴ�.
PawnMovementComponent �� �������� ��ü�� �ε����� �ε巴�� ���������� ó���ߴ�.
Default Pawn Movement ���� ���������� �ʴ� �߷� ������ ������ �����ߴ�.


-----------------------------------------------------------------------------------------------------
Pawn Ŭ�������� GetMovementComponent() ��� �Լ��� �ִµ� �̰��� ������ �ٸ� Ŭ�������� ���� Pawn�� ������� 
Pawn Movement Component�� ������ �� �ֵ��� �ϴµ� ���ȴ�. 
�� �Լ��� Ŀ���͸���¡�� CollidingPawnMovementComponent�� ��ȯ�ϵ��� �Ϸ��� �� �Լ��� ������� �Ѵ�. 


�̹� ���ǿ��� ��� ��(��ó: https://wergia.tistory.com/129?category=807793 [������ ���α׷��� ��Ʈ])


1. UParticleSystemComponent

UParticleSystemComponent* ParticleSystemComponent;
���Ϳ� ��ƼŬ �ý����� ������ �� �ִ� ������Ʈ

ParticleSystemComponent->bAutoActivate = true;
��ƼŬ �ý����� �������ڸ��� �ڵ����� �������� ���� ����

ParticleSystemComponent->SetTemplate(ParticleAsset.Object);
��ƼŬ �ý��� ������Ʈ�� ��ƼŬ�� �����ϴ� �Լ�

ParticleSystemComponent->ToggleActive();
��ƼŬ�� �Ѱ� ���� �Լ�


2. USphereComponent

USphereComponent* SphereComponent;
���Ϳ� ���� �浹 ���� ȿ���� �� �� �ִ� ������Ʈ

SphereComponent->InitSphereRadius(40.0f);
���Ǿ� ������Ʈ�� �������� �����ϴ� �Լ�

SphereComponent->SetCollisionProfileName(TEXT("Pawn"));
�ݸ����� �������� �����ϴ� �Լ�. 
[������Ʈ ����>����>�ݸ���] �ϴܿ� Preset�� ����� �� �ݸ��� �����ʸ��� � ���� ������ ������ �ִ��� Ȯ���� �� �ִ�.


3. UStaticMeshComponent

UStaticMeshComponent* StaticMeshComponent;
���忡 �������Ǵ� ����ƽ �޽ø� ���� ������Ʈ

StaticMeshComponent->SetStaticMesh(SphereVisualAsset.Object);
����ƽ �޽� ������Ʈ�� ����ƽ �޽ø� �����ϴ� �Լ�


4. ConstructorHelpers::FObjectFinder<T>

static ConstructorHelpers::FObjectFinder<T> Asset(TEXT("AssetPath"));
������Ʈ���� �ʿ��� �������� ���ҽ�, ������ �ҷ����µ� ���̴� ����ü


Asset.Succeeded();
������ �ҷ����µ� �����ߴ����� ��ȯ�ϴ� �Լ�

Asset.Object;
�ҷ��� ������ ��� �ִ� ����


5. USpringArmComponent

USpringArmComponent* SpringArmComponent;
�θ� ������Ʈ�� �ڽ� ������Ʈ ���̿� ������ �Ÿ��� �����ϰ� �����ִ� ������Ʈ. 
�浹�� �ִ� ����� �����ϰ� �θ�� �ڽ� ������ �Ÿ��� �����ٰ� �浹�� ������� �ٽ� ������� ���ư����ϴ� ����� �����Ѵ�.

SpringArmComponent->TargetArmLength = 400.0f;
�ƹ��� �浹�� ���� ��, ������ ���� �ڿ����� �Ÿ��� ���� �� �ִ� ����

SpringArmComponent->bEnableCameraLag = true;
true�� ���, ī�޶� ��ǥ ��ġ���� �ڶ������� ���󰡵��� �Ѵ�.

SpringArmComponent->CameraLagSpeed = 3.0f;
bEnableCameraLag�� true�� ���, ī�޶� ��ǥ ��ġ�� �����ϴ� �ӵ��� �����Ѵ�.


6. UPawnMovementComponent

Pawn�� �������� ������Ʈ�ϴµ� ���Ǵ� ������Ʈ

PawnOwner;
�� ������Ʈ�� �����ϰ� �ִ� ��

UMovementComponent::UpdatedComponent;
UPawnMovementComponent�� �θ� Ŭ������ UMovementComponent Ŭ������ ���ϴ� ������ �� �����Ʈ ������Ʈ�� �̵���Ű�� ������Ʈ �ؾ��� ������Ʈ

UMovementComponent::ShouldSkipUpdate(DeltaTime);
�̵��� ������Ʈ�� �̵��� �� ���ų� ���������� ���� ��������� �Ǻ��Ͽ� �˷��ִ� �Լ�

ConsumeInputVector();
������� �Է��� ��ȯ�ϰ� �ٽ� 0���� �����ϴ� �Լ�

SafeMoveUpdatedComponent(DesiredMovementThisFrame, UpdatedComponent->GetComponentRotation(), true, Hit);
�𸮾� ���� �������� �̿��ؼ� ��ü ��ֹ��� ���ؼ� �� �����Ʈ ������Ʈ�� �̵���Ű�� �Լ�

SlideAlongSurface(DesiredMovementThisFrame, 1.0f - Hit.Time, Hit.Normal, Hit);
������Ʈ�� �̵��ϴٰ� �浹�� �߻����� ��, ���ڸ��� ���ߴ� ��� �浹ü�� ǥ���� Ÿ�� �̲��������� �̵��ϵ��� �����ִ� �Լ�

AddInputVector(Vector);
�Ű������� ���� ���͸� ���� �Է¿� ���ϴ� �Լ�


7. FVector

FVector Vector;
�𸮾� �������� 3D ���� ��ġ��, �ӵ��� ��Ÿ���µ� ���̴� ����ü


Vector.GetClampedToMaxSize(Value);
���̰� Value�� �� ������ ���纻�� ���� ��ȯ�ϴ� �Լ�


Vector.IsNearlyZero();
������ ������ ������ ������ ���̰� 0�� �����ϴ��� Ȯ���ϴ� �Լ�


8. FHitResult

FHitResult Hit;
�浹�� ���� ������ ��� �ִ� ����ü

Hit.Time;
Hit�� �߻����� ��, TraceStart�� TraceEnd ������ �浹�� �߻��� �ð��� �ǹ��Ѵ�. (0.0~1.0)

Hit.Normal
�浹�� �߻��� ������Ʈ�� ���� ���� ���� ���� ����

Hit.IsValidBlockingHit();
������ �浹�� �߻����� �� true�� ��ȯ�ϴ� �Լ�


9. AActor

GetActorRotation();
������ ���� ȸ���� ��ȯ�ϴ� �Լ�

SetActorRotation(FRotator());
������ ȸ���� �����ϴ� �Լ�


-----------------------------------------------------------------------------------------------------
UE 4.19 -> 5.5

�ֿ� ���� ����

Build.cs ���� ������Ʈ
EnhancedInput �ý������� ����