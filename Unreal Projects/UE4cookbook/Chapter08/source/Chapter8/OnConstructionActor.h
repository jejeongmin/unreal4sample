// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine/StaticMeshActor.h"
#include "OnConstructionActor.generated.h"

/**
 * 
 */
UCLASS()
class CHAPTER8_API AOnConstructionActor : public AStaticMeshActor
{
	GENERATED_BODY()

public:

		AOnConstructionActor();

		/*
			�������Ʈ���� Construction Script �� ������ ����Ʈ���� �巡�׵ǰų� ���� ���� �гο� ���� �Էµ� ����� ��쿡��
			����� ��ü���� property �� ����� ������ ����Ǵ� �̺�Ʈ �׷����̴�.

			Construction scripts �� �̿��ϸ� �ش� ��ü�� �� ��ġ�� ������� '�����'�ǰų� ����ڰ� ������ �ɼ��� �������
			���Ե� ������Ʈ�� ������ �� �ִ�.

			�𸮾� �������� C++ �ڵ��� �� ���� ������ OnConstruction �Լ��̴�.

			�� C++ class actor �� �����Ϳ��� �̵��ϴ� ��쿡�� OnConstruction �� ������� �ʴ´�.
			������ AActor::PostEditorMove �Լ� ������ ���� �� �� �ִµ�
			Ŭ������ blueprint ����� ��쿡�� construction scripts �� OnConstruction �� �ٽ� �������� �� �� ���� ���̴�.
		*/
		virtual void OnConstruction(const FTransform& Transform) override;
		UPROPERTY(EditAnywhere)
			bool ShowStaticMesh;
};
