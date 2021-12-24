// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "RuntimeMeshProvider.h"
#include "BoxMeshProvider.generated.h"

/**
 * 
 */
UCLASS()
class LASTCOLLISIONBUG_API UBoxMeshProvider : public URuntimeMeshProvider
{
	GENERATED_BODY()
	
protected:
	FCriticalSection SyncRoot;
	bool bCreateBox;
	FVector Center;
	FVector Extents;

	FRuntimeMeshCollisionSettings CollisionSettings;

	UPROPERTY()
	UMaterialInterface* MeshMaterial;

public:
	UBoxMeshProvider();

	///// URuntimeMeshProvider Interface
	virtual bool IsThreadSafe() override { return true; };
	virtual void Initialize() override;
	virtual bool GetSectionMeshForLOD(int32 LODIndex, int32 SectionId, FRuntimeMeshRenderableMeshData& MeshData) override;
	virtual FBoxSphereBounds GetBounds() override;
	virtual FRuntimeMeshCollisionSettings GetCollisionSettings() override;

	// IInterface_CollisionDataProvider::ContainsPhysicsTriMeshData 
	virtual bool HasCollisionMesh() override;
	virtual bool GetCollisionMesh(FRuntimeMeshCollisionData& CollisionData) override;
	///// End of URuntimeMeshProvider Interface

public:
	UFUNCTION(BlueprintCallable)
		void SetCreateBox(bool bCreate);

	UFUNCTION(BlueprintCallable)
		bool GetCreateBox();

	UFUNCTION(BlueprintCallable)
		void SetMeshMaterial(UMaterialInterface* NewMaterial);

	UFUNCTION(BlueprintCallable)
		UMaterialInterface* GetMeshMaterial();

	UFUNCTION(BlueprintCallable)
		void SetMeshCollisionSettings(FRuntimeMeshCollisionSettings NewSettings);

	UFUNCTION(BlueprintCallable)
		FRuntimeMeshCollisionSettings GetMeshCollisionSettings();
};
