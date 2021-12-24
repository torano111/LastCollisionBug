// Fill out your copyright notice in the Description page of Project Settings.

#include "PMCTestActor.h"
#include "VoxelChunkFunctionLibrary.h"

// Sets default values
APMCTestActor::APMCTestActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UMyProceduralMeshComponent>(FName(TEXT("ProceduralMesh")));
	RootComponent = Mesh;
	Mesh->bUseAsyncCooking = true;
}

// Called when the game starts or when spawned
void APMCTestActor::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void APMCTestActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APMCTestActor::CalculateBoxMesh(const FVector& InCenter, const FVector& InExtents, TArray<FVector>& OutVertices, TArray<int32>& OutTriangles, TArray<FVector>& OutNormals, TArray<FVector2D>& OutUV0, TArray<FVector2D>& OutUV1, TArray<FVector2D>& OutUV2, TArray<FVector2D>& OutUV3, TArray<FLinearColor>& OutVertexColors, TArray<FProcMeshTangent>& OutTangents)
{
	const FVector2D UVCoord00(0, 0);
	const FVector2D UVCoord11(1, 1);
	TArray<FVector> Tangents;
	UVoxelChunkFunctionLibrary::ReserveAndAddBox(InCenter, InExtents, OutVertices, OutTriangles, OutUV0, UVCoord00, UVCoord11, OutNormals, Tangents);
	ConvertTangents(Tangents, true, OutTangents);

	OutVertexColors.Init(FLinearColor::White, OutVertices.Num());

	// No UV1, 2, 3
	OutUV1.Empty();
	OutUV2.Empty();
	OutUV3.Empty();
}

void APMCTestActor::ConvertTangents(const TArray<FVector>& InSource, bool bFlipTangentY, TArray<FProcMeshTangent>& OutResult)
{
	if (InSource.Num() > 0)
	{
		OutResult.Empty();
		OutResult.Reserve(InSource.Num());
		for (const FVector& Tangent : InSource)
		{
			FProcMeshTangent NewTangent(Tangent, bFlipTangentY);
			OutResult.Add(NewTangent);
		}
	}
}

