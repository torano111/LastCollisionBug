// Fill out your copyright notice in the Description page of Project Settings.


#include "VoxelChunkFunctionLibrary.h"
#include "Math/UnrealMath.h"

bool UVoxelChunkFunctionLibrary::GetBoxFaceSideFromIndices(const FIntVector& InIndices, EBoxFaceSide& OutBoxFaceSide)
{
	if (InIndices == FIntVector(1, 0, 0))
	{
		OutBoxFaceSide = EBoxFaceSide::Front;
		return true;
	}
	else if (InIndices == FIntVector(-1, 0, 0))
	{
		OutBoxFaceSide = EBoxFaceSide::Back;
		return true;
	}
	else if (InIndices == FIntVector(0, 1, 0))
	{
		OutBoxFaceSide = EBoxFaceSide::Right;
		return true;
	}
	else if (InIndices == FIntVector(0, -1, 0))
	{
		OutBoxFaceSide = EBoxFaceSide::Left;
		return true;
	}
	else if (InIndices == FIntVector(0, 0, 1))
	{
		OutBoxFaceSide = EBoxFaceSide::Up;
		return true;
	}
	else if (InIndices == FIntVector(0, 0, -1))
	{
		OutBoxFaceSide = EBoxFaceSide::Down;
		return true;
	}
	return false;
}

int UVoxelChunkFunctionLibrary::GetFaceVertexLength()
{
	return FaceVertexLength;
}

int UVoxelChunkFunctionLibrary::GetFaceTriangleLength()
{
	return FaceTriangleLength;
}

void UVoxelChunkFunctionLibrary::ReserveVerticesForFaces(int NumFace, TArray<FVector>& Vertices)
{
	if (NumFace <= 0)
	{
		return;
	}

	Vertices.Reserve(Vertices.Num() + FaceVertexLength * NumFace);
}

void UVoxelChunkFunctionLibrary::ReserveTrianglesForFaces(int NumFace, TArray<int32>& Triangles)
{
	if (NumFace <= 0)
	{
		return;
	}

	Triangles.Reserve(Triangles.Num() + FaceTriangleLength * NumFace);
}

void UVoxelChunkFunctionLibrary::ReserveUVForFaces(int NumFace, TArray<FVector2D>& UV0)
{
	if (NumFace <= 0)
	{
		return;
	}

	UV0.Reserve(UV0.Num() + FaceVertexLength * NumFace);
}

void UVoxelChunkFunctionLibrary::ReserveNormalsForFaces(int NumFace, TArray<FVector>& Normals)
{
	if (NumFace <= 0)
	{
		return;
	}

	Normals.Reserve(Normals.Num() + FaceVertexLength * NumFace);
}

void UVoxelChunkFunctionLibrary::ReserveTangentsForFaces(int NumFace, TArray<FVector>& Tangents)
{
	if (NumFace <= 0)
	{
		return;
	}

	Tangents.Reserve(Tangents.Num() + FaceVertexLength * NumFace);
}

void UVoxelChunkFunctionLibrary::ReserveMeshForFaces(int NumFace, TArray<FVector>& Vertices, TArray<int32>& Triangles, TArray<FVector2D>& UV0, TArray<FVector>& Normals, TArray<FVector>& Tangents)
{
	ReserveVerticesForFaces(NumFace, Vertices);
	ReserveTrianglesForFaces(NumFace, Triangles);
	ReserveUVForFaces(NumFace, UV0);
	ReserveNormalsForFaces(NumFace, Normals);
	ReserveTangentsForFaces(NumFace, Tangents);
}


void UVoxelChunkFunctionLibrary::AddVerticesForBoxFace(EBoxFaceSide FaceSide, FVector Center, FVector Extents, TArray<FVector>& Vertices)
{
	switch (FaceSide)
	{
	case EBoxFaceSide::Front:
		Vertices.Emplace(Center + FVector(Extents.X, Extents.Y, Extents.Z));
		Vertices.Emplace(Center + FVector(Extents.X, Extents.Y, -Extents.Z));
		Vertices.Emplace(Center + FVector(Extents.X, -Extents.Y, Extents.Z));
		Vertices.Emplace(Center + FVector(Extents.X, -Extents.Y, -Extents.Z));
		break;
	case EBoxFaceSide::Back:
		Vertices.Emplace(Center + FVector(-Extents.X, -Extents.Y, Extents.Z));
		Vertices.Emplace(Center + FVector(-Extents.X, -Extents.Y, -Extents.Z));
		Vertices.Emplace(Center + FVector(-Extents.X, Extents.Y, Extents.Z));
		Vertices.Emplace(Center + FVector(-Extents.X, Extents.Y, -Extents.Z));
		break;
	case EBoxFaceSide::Up:
		Vertices.Emplace(Center + FVector(Extents.X, -Extents.Y, Extents.Z));
		Vertices.Emplace(Center + FVector(-Extents.X, -Extents.Y, Extents.Z));
		Vertices.Emplace(Center + FVector(Extents.X, Extents.Y, Extents.Z));
		Vertices.Emplace(Center + FVector(-Extents.X, Extents.Y, Extents.Z));
		break;
	case EBoxFaceSide::Down:
		Vertices.Emplace(Center + FVector(Extents.X, Extents.Y, -Extents.Z));
		Vertices.Emplace(Center + FVector(-Extents.X, Extents.Y, -Extents.Z));
		Vertices.Emplace(Center + FVector(Extents.X, -Extents.Y, -Extents.Z));
		Vertices.Emplace(Center + FVector(-Extents.X, -Extents.Y, -Extents.Z));
		break;
	case EBoxFaceSide::Right:
		Vertices.Emplace(Center + FVector(-Extents.X, Extents.Y, Extents.Z));
		Vertices.Emplace(Center + FVector(-Extents.X, Extents.Y, -Extents.Z));
		Vertices.Emplace(Center + FVector(Extents.X, Extents.Y, Extents.Z));
		Vertices.Emplace(Center + FVector(Extents.X, Extents.Y, -Extents.Z));
		break;
	case EBoxFaceSide::Left:
		Vertices.Emplace(Center + FVector(Extents.X, -Extents.Y, Extents.Z));
		Vertices.Emplace(Center + FVector(Extents.X, -Extents.Y, -Extents.Z));
		Vertices.Emplace(Center + FVector(-Extents.X, -Extents.Y, Extents.Z));
		Vertices.Emplace(Center + FVector(-Extents.X, -Extents.Y, -Extents.Z));
		break;
	}
}


void UVoxelChunkFunctionLibrary::AddTrianglesForBoxFace(EBoxFaceSide FaceSide, int StartIndex, TArray<int32>& Triangles)
{
	switch (FaceSide)
	{
	case EBoxFaceSide::Front:
	case EBoxFaceSide::Back:
	case EBoxFaceSide::Up:
	case EBoxFaceSide::Down:
	case EBoxFaceSide::Right:
	case EBoxFaceSide::Left:
		// up side triangle
		Triangles.Emplace(StartIndex);
		Triangles.Emplace(StartIndex + 1);
		Triangles.Emplace(StartIndex + 2);

		// down side triangle
		Triangles.Emplace(StartIndex + 3);
		Triangles.Emplace(StartIndex + 2);
		Triangles.Emplace(StartIndex + 1);
		break;
	}
}

void UVoxelChunkFunctionLibrary::AddUVForBoxFace(EBoxFaceSide FaceSide, TArray<FVector2D>& UV0, FVector2D UVCoord00, FVector2D UVCoord11)
{
	switch (FaceSide)
	{
	case EBoxFaceSide::Front:
	case EBoxFaceSide::Back:
	case EBoxFaceSide::Up:
	case EBoxFaceSide::Down:
	case EBoxFaceSide::Right:
	case EBoxFaceSide::Left:
		UV0.Emplace(FVector2D(UVCoord00.X, UVCoord00.Y));
		UV0.Emplace(FVector2D(UVCoord00.X, UVCoord11.Y));
		UV0.Emplace(FVector2D(UVCoord11.X, UVCoord00.Y));
		UV0.Emplace(FVector2D(UVCoord11.X, UVCoord11.Y));
		break;
	}
}

void UVoxelChunkFunctionLibrary::AddNormalsForBoxFace(EBoxFaceSide FaceSide, TArray<FVector>& Normals)
{
	FVector N;
	switch (FaceSide)
	{
	case EBoxFaceSide::Front:
		N = FVector::ForwardVector;
		break;
	case EBoxFaceSide::Back:
		N = FVector::BackwardVector;
		break;
	case EBoxFaceSide::Up:
		N = FVector::UpVector;
		break;
	case EBoxFaceSide::Down:
		N = FVector::DownVector;
		break;
	case EBoxFaceSide::Right:
		N = FVector::RightVector;
		break;
	case EBoxFaceSide::Left:
		N = FVector::LeftVector;
		break;
	}

	for (int i = 0; i < FaceVertexLength; i++)
	{
		Normals.Emplace(N);
	}
}

void UVoxelChunkFunctionLibrary::AddTangentsForBoxFace(EBoxFaceSide FaceSide, TArray<FVector>& Tangents)
{
	FVector T;
	switch (FaceSide)
	{
	case EBoxFaceSide::Front:
		T = FVector::LeftVector;
		break;
	case EBoxFaceSide::Back:
		T = FVector::RightVector;
		break;
	case EBoxFaceSide::Up:
		T = FVector::RightVector;
		break;
	case EBoxFaceSide::Down:
		T = FVector::LeftVector;
		break;
	case EBoxFaceSide::Right:
		T = FVector::ForwardVector;
		break;
	case EBoxFaceSide::Left:
		T = FVector::BackwardVector;
		break;
	}

	for (int i = 0; i < FaceVertexLength; i++)
	{
		Tangents.Emplace(T);
	}
}

void UVoxelChunkFunctionLibrary::AddMeshForBoxFace(EBoxFaceSide FaceSide, FVector Center, FVector Extents, TArray<FVector>& Vertices, TArray<int32>& Triangles, TArray<FVector2D>& UV0, FVector2D UVCoord00, FVector2D UVCoord11, TArray<FVector>& Normals, TArray<FVector>& Tangents)
{
	int NumVertices = Vertices.Num();
	AddVerticesForBoxFace(FaceSide, Center, Extents, Vertices);
	AddTrianglesForBoxFace(FaceSide, NumVertices, Triangles);
	AddUVForBoxFace(FaceSide, UV0, UVCoord00, UVCoord11);
	AddNormalsForBoxFace(FaceSide, Normals);
	AddTangentsForBoxFace(FaceSide, Tangents);
}

void UVoxelChunkFunctionLibrary::ReserveAndAddMeshForBoxFace(EBoxFaceSide FaceSide, FVector Center, FVector Extents, TArray<FVector>& Vertices, TArray<int32>& Triangles, TArray<FVector2D>& UV0, FVector2D UVCoord00, FVector2D UVCoord11, TArray<FVector>& Normals, TArray<FVector>& Tangents)
{
	ReserveMeshForFaces(1, Vertices, Triangles, UV0, Normals, Tangents);
	AddMeshForBoxFace(FaceSide, Center, Extents, Vertices, Triangles, UV0, UVCoord00, UVCoord11, Normals, Tangents);
}

void UVoxelChunkFunctionLibrary::AddBox(FVector Center, FVector Extents, TArray<FVector>& Vertices, TArray<int32>& Triangles, TArray<FVector2D>& UV0, FVector2D UVCoord00, FVector2D UVCoord11, TArray<FVector>& Normals, TArray<FVector>& Tangents)
{
	AddMeshForBoxFace(EBoxFaceSide::Front, Center, Extents, Vertices, Triangles, UV0, UVCoord00, UVCoord11, Normals, Tangents);
	AddMeshForBoxFace(EBoxFaceSide::Back, Center, Extents, Vertices, Triangles, UV0, UVCoord00, UVCoord11, Normals, Tangents);
	AddMeshForBoxFace(EBoxFaceSide::Up, Center, Extents, Vertices, Triangles, UV0, UVCoord00, UVCoord11, Normals, Tangents);
	AddMeshForBoxFace(EBoxFaceSide::Down, Center, Extents, Vertices, Triangles, UV0, UVCoord00, UVCoord11, Normals, Tangents);
	AddMeshForBoxFace(EBoxFaceSide::Right, Center, Extents, Vertices, Triangles, UV0, UVCoord00, UVCoord11, Normals, Tangents);
	AddMeshForBoxFace(EBoxFaceSide::Left, Center, Extents, Vertices, Triangles, UV0, UVCoord00, UVCoord11, Normals, Tangents);
}

void UVoxelChunkFunctionLibrary::ReserveAndAddBox(FVector Center, FVector Extents, TArray<FVector>& Vertices, TArray<int32>& Triangles, TArray<FVector2D>& UV0, FVector2D UVCoord00, FVector2D UVCoord11, TArray<FVector>& Normals, TArray<FVector>& Tangents)
{
	ReserveMeshForFaces(6, Vertices, Triangles, UV0, Normals, Tangents);
	AddBox(Center, Extents, Vertices, Triangles, UV0, UVCoord00, UVCoord11, Normals, Tangents);
}
