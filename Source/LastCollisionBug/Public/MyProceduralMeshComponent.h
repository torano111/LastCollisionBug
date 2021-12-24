// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ProceduralMeshComponent.h"
#include "MyProceduralMeshComponent.generated.h"

/**
 *
 */
UCLASS()
class LASTCOLLISIONBUG_API UMyProceduralMeshComponent : public UProceduralMeshComponent
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
		bool bAlwaysCookPhysics = true;

	//~ Begin Interface_CollisionDataProvider Interface
	virtual bool ContainsPhysicsTriMeshData(bool InUseAllTriData) const override;
	//~ End Interface_CollisionDataProvider Interface
};
