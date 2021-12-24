// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "VoxelChunkFunctionLibrary.generated.h"

UENUM(BlueprintType)
enum class EBoxFaceSide : uint8
{
	Front,	// +X direction
	Back,	// -X direction
	Up,    // +Z direction
	Down,	// -Z direction
	Right,    // +Y direction
	Left,	// -Y direction
};

UCLASS()
class LASTCOLLISIONBUG_API UVoxelChunkFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

private:
	const static int FaceVertexLength = 4;
	const static int FaceTriangleLength = 6;	// 2 triangles

public:
	UFUNCTION(BlueprintPure, Category = "ChunkMeshFunctionLibrary")
		static bool GetBoxFaceSideFromIndices(const FIntVector& InIndices, EBoxFaceSide& OutBoxFaceSide);

	UFUNCTION(BlueprintCallable, Category = "ChunkMeshFunctionLibrary")
		static int GetFaceVertexLength();

	UFUNCTION(BlueprintCallable, Category = "ChunkMeshFunctionLibrary")
		static int GetFaceTriangleLength();

	UFUNCTION(BlueprintCallable, Category = "ChunkMeshFunctionLibrary")
		static void ReserveVerticesForFaces(int NumFace, TArray<FVector>& Vertices);

	UFUNCTION(BlueprintCallable, Category = "ChunkMeshFunctionLibrary")
		static void ReserveTrianglesForFaces(int NumFace, TArray<int32>& Triangles);

	UFUNCTION(BlueprintCallable, Category = "ChunkMeshFunctionLibrary")
		static void ReserveUVForFaces(int NumFace, TArray<FVector2D>& UV0);

	UFUNCTION(BlueprintCallable, Category = "ChunkMeshFunctionLibrary")
		static void ReserveNormalsForFaces(int NumFace, TArray<FVector>& Normals);

	UFUNCTION(BlueprintCallable, Category = "ChunkMeshFunctionLibrary")
		static void ReserveTangentsForFaces(int NumFace, TArray<FVector>& Tangents);

	UFUNCTION(BlueprintCallable, Category = "ChunkMeshFunctionLibrary")
		static void ReserveMeshForFaces(int NumFace, TArray<FVector>& Vertices, TArray<int32>& Triangles, TArray<FVector2D>& UV0, TArray<FVector>& Normals, TArray<FVector>& Tangents);

	UFUNCTION(BlueprintCallable, Category = "ChunkMeshFunctionLibrary")
		static void AddVerticesForBoxFace(EBoxFaceSide FaceSide, FVector Center, FVector Extents, TArray<FVector>& Vertices);

	UFUNCTION(BlueprintCallable, Category = "ChunkMeshFunctionLibrary")
		static void AddTrianglesForBoxFace(EBoxFaceSide FaceSide, int StartIndex, TArray<int32>& Triangles);

	UFUNCTION(BlueprintCallable, Category = "ChunkMeshFunctionLibrary")
		static void AddUVForBoxFace(EBoxFaceSide FaceSide, TArray<FVector2D>& UV0, FVector2D UVCoord00, FVector2D UVCoord11);

	UFUNCTION(BlueprintCallable, Category = "ChunkMeshFunctionLibrary")
		static void AddNormalsForBoxFace(EBoxFaceSide FaceSide, TArray<FVector>& Normals);

	UFUNCTION(BlueprintCallable, Category = "ChunkMeshFunctionLibrary")
		static void AddTangentsForBoxFace(EBoxFaceSide FaceSide, TArray<FVector>& Tangents);

	UFUNCTION(BlueprintCallable, Category = "ChunkMeshFunctionLibrary")
		static void AddMeshForBoxFace(EBoxFaceSide FaceSide, FVector Center, FVector Extents, TArray<FVector>& Vertices, TArray<int32>& Triangles, TArray<FVector2D>& UV0, FVector2D UVCoord00, FVector2D UVCoord11, TArray<FVector>& Normals, TArray<FVector>& Tangents);

	UFUNCTION(BlueprintCallable, Category = "ChunkMeshFunctionLibrary")
		static void ReserveAndAddMeshForBoxFace(EBoxFaceSide FaceSide, FVector Center, FVector Extents, TArray<FVector>& Vertices, TArray<int32>& Triangles, TArray<FVector2D>& UV0, FVector2D UVCoord00, FVector2D UVCoord11, TArray<FVector>& Normals, TArray<FVector>& Tangents);

	UFUNCTION(BlueprintCallable, Category = "ChunkMeshFunctionLibrary")
		static void AddBox(FVector Center, FVector Extents, TArray<FVector>& Vertices, TArray<int32>& Triangles, TArray<FVector2D>& UV0, FVector2D UVCoord00, FVector2D UVCoord11, TArray<FVector>& Normals, TArray<FVector>& Tangents);

	UFUNCTION(BlueprintCallable, Category = "ChunkMeshFunctionLibrary")
		static void ReserveAndAddBox(FVector Center, FVector Extents, TArray<FVector>& Vertices, TArray<int32>& Triangles, TArray<FVector2D>& UV0, FVector2D UVCoord00, FVector2D UVCoord11, TArray<FVector>& Normals, TArray<FVector>& Tangents);
};
