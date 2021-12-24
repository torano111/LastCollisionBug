// Fill out your copyright notice in the Description page of Project Settings.

#include "BoxMeshProvider.h"
#include "VoxelChunkFunctionLibrary.h"
#include "Modifiers/RuntimeMeshModifierNormals.h"

UBoxMeshProvider::UBoxMeshProvider()
{
	bCreateBox = true;
	Center = FVector::ZeroVector;
	Extents = FVector(50.f);
}

void UBoxMeshProvider::Initialize()
{
	FRuntimeMeshLODProperties LODProperties;
	LODProperties.ScreenSize = 0.f;
	ConfigureLODs({ LODProperties });
	SetupMaterialSlot(0, FName(TEXT("MeshMaterial0")), MeshMaterial);

	FRuntimeMeshSectionProperties InitialSectionProperties;
	InitialSectionProperties.bCastsShadow = true;
	InitialSectionProperties.bIsVisible = true;
	InitialSectionProperties.MaterialSlot = 0;
	InitialSectionProperties.UpdateFrequency = ERuntimeMeshUpdateFrequency::Average;
	CreateSection(0, 0, InitialSectionProperties);

	FRuntimeMeshCollisionSettings InitialSettings;
	InitialSettings.bUseAsyncCooking = true;
	InitialSettings.bUseComplexAsSimple = true;
	SetMeshCollisionSettings(InitialSettings);

	MarkCollisionDirty();
}

bool UBoxMeshProvider::GetSectionMeshForLOD(int32 LODIndex, int32 SectionId, FRuntimeMeshRenderableMeshData& MeshData)
{
	FScopeLock Lock(&SyncRoot);

	if (bCreateBox)
	{
		TArray<FVector> Vertices;
		TArray<int32> Triangles;
		TArray<FVector> Normals;
		TArray<FVector2D> UVs0;
		TArray<FColor> VertexColors;
		TArray<FVector> Tangents;

		FVector2D UVCoord00 = FVector2D(0);
		FVector2D UVCoord11 = FVector2D(1);

		UVoxelChunkFunctionLibrary::ReserveAndAddBox(Center, Extents, Vertices, Triangles, UVs0, UVCoord00, UVCoord11, Normals, Tangents);

		MeshData.Positions.Empty(Vertices.Num());
		MeshData.Positions.Append(Vertices);

		MeshData.Triangles.Empty(Triangles.Num());
		MeshData.Triangles.Append(Triangles);

		MeshData.TexCoords.Empty(UVs0.Num());
		MeshData.TexCoords.FillIn(0, UVs0, 0);

		VertexColors.Init(FColor::White, Vertices.Num());
		MeshData.Colors.Empty(VertexColors.Num());
		MeshData.Colors.Append(VertexColors);

		// Calculates normals and tangents
		// Note that no mesh would be appeared if we don't provide tangents
		URuntimeMeshModifierNormals::CalculateNormalsTangents(MeshData, false);
	}

	MarkCollisionDirty();
	return true;
}

FBoxSphereBounds UBoxMeshProvider::GetBounds()
{
	FScopeLock Lock(&SyncRoot);
	FVector BoundsMin = Center - Extents;
	FVector BoundsMax = Center + Extents;
	return FBoxSphereBounds(FBox(BoundsMin, BoundsMax));
}

FRuntimeMeshCollisionSettings UBoxMeshProvider::GetCollisionSettings()
{
	FScopeLock Lock(&SyncRoot);
	return CollisionSettings;
}

bool UBoxMeshProvider::HasCollisionMesh()
{
	FScopeLock Lock(&SyncRoot);
	return bCreateBox;
}

bool UBoxMeshProvider::GetCollisionMesh(FRuntimeMeshCollisionData& CollisionData)
{
	FScopeLock Lock(&SyncRoot);
	if (bCreateBox)
	{
		TArray<FVector> Vertices;
		TArray<int32> Triangles;
		TArray<FVector> Normals;
		TArray<FVector2D> UVs0;
		TArray<FColor> VertexColors;
		TArray<FVector> Tangents;

		FVector2D UVCoord00 = FVector2D(0);
		FVector2D UVCoord11 = FVector2D(1);

		UVoxelChunkFunctionLibrary::ReserveAndAddBox(Center, Extents, Vertices, Triangles, UVs0, UVCoord00, UVCoord11, Normals, Tangents);

		FRuntimeMeshCollisionVertexStream& CollisionVertices = CollisionData.Vertices;
		FRuntimeMeshCollisionTriangleStream& CollisionTriangles = CollisionData.Triangles;
		CollisionVertices.Empty();
		CollisionVertices.Reserve(Vertices.Num());
		// todo start VertId might not be 0
		for (int VertId = 0; VertId < Vertices.Num(); ++VertId)
		{
			CollisionVertices.Add(Vertices[VertId]);
		}

		CollisionTriangles.Empty();
		CollisionTriangles.Reserve(Triangles.Num());
		for (int TriId = 0; TriId < Triangles.Num(); TriId += 3)
		{
			CollisionTriangles.Add(Triangles[TriId], Triangles[TriId + 1], Triangles[TriId + 2]);
		}

		// Adds collision for a section
		FRuntimeMeshCollisionSourceSectionInfo CollisionSource;
		CollisionSource.StartIndex = 0;
		CollisionSource.EndIndex = Triangles.Num() - 1;
		CollisionSource.SourceProvider = this;
		CollisionSource.SectionId = 0;
		CollisionSource.SourceType = ERuntimeMeshCollisionFaceSourceType::Renderable;
		CollisionData.CollisionSources.Emplace(CollisionSource);
	}
	return true;
}

void UBoxMeshProvider::SetCreateBox(bool bCreate)
{
	FScopeLock Lock(&SyncRoot);
	bCreateBox = bCreate;
}

bool UBoxMeshProvider::GetCreateBox()
{
	FScopeLock Lock(&SyncRoot);
	return bCreateBox;
}

void UBoxMeshProvider::SetMeshMaterial(UMaterialInterface* NewMaterial)
{
	FScopeLock Lock(&SyncRoot);
	MeshMaterial = NewMaterial;
	SetupMaterialSlot(0, FName(TEXT("MeshMaterial0")), MeshMaterial);
}

UMaterialInterface* UBoxMeshProvider::GetMeshMaterial()
{
	FScopeLock Lock(&SyncRoot);
	return MeshMaterial;
}

void UBoxMeshProvider::SetMeshCollisionSettings(FRuntimeMeshCollisionSettings NewSettings)
{
	FScopeLock Lock(&SyncRoot);
	CollisionSettings = NewSettings;
	MarkCollisionDirty();
}

FRuntimeMeshCollisionSettings UBoxMeshProvider::GetMeshCollisionSettings()
{
	FScopeLock Lock(&SyncRoot);
	return CollisionSettings;
}