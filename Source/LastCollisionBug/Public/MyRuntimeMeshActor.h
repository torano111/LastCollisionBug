// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "RuntimeMeshActor.h"
#include "BoxMeshProvider.h"
#include "MyRuntimeMeshActor.generated.h"

/**
 *
 */
UCLASS()
class LASTCOLLISIONBUG_API AMyRuntimeMeshActor : public ARuntimeMeshActor
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UMaterialInterface* MeshMaterial;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FRuntimeMeshCollisionSettings CollisionSettings;

	UPROPERTY()
		UBoxMeshProvider* BoxMeshProvider;

public:
	AMyRuntimeMeshActor();

protected:
	/** Overridable native event for when play begins for this actor. */
	virtual void BeginPlay();

public:
	UFUNCTION(BlueprintCallable)
		void MakeBoxMesh();

	UFUNCTION(BlueprintCallable)
		void ClearMesh();
};
