// Fill out your copyright notice in the Description page of Project Settings.


#include "MyRuntimeMeshActor.h"

AMyRuntimeMeshActor::AMyRuntimeMeshActor() : Super()
{
	CollisionSettings.bUseAsyncCooking = true;
	CollisionSettings.bUseComplexAsSimple = true;
}

void AMyRuntimeMeshActor::BeginPlay()
{
	Super::BeginPlay();

	if (URuntimeMeshComponent* RMC = GetRuntimeMeshComponent())
	{
		if (BoxMeshProvider == nullptr)
		{
			BoxMeshProvider = NewObject<UBoxMeshProvider>(this, FName(TEXT("BoxMeshProvider")));
			RMC->Initialize(BoxMeshProvider);

			BoxMeshProvider->SetMeshMaterial(MeshMaterial);
			BoxMeshProvider->SetMeshCollisionSettings(CollisionSettings);
			BoxMeshProvider->SetCreateBox(true);
			BoxMeshProvider->MarkAllLODsDirty();
		}
	}
}

void AMyRuntimeMeshActor::MakeBoxMesh()
{
	if (BoxMeshProvider)
	{
		BoxMeshProvider->SetCreateBox(true);
		BoxMeshProvider->MarkAllLODsDirty();
	}
}

void AMyRuntimeMeshActor::ClearMesh()
{
	if (BoxMeshProvider)
	{
		BoxMeshProvider->SetCreateBox(false);
		BoxMeshProvider->MarkAllLODsDirty();
	}
}
