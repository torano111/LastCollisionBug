// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyProceduralMeshComponent.h"
#include "PMCTestActor.generated.h"

UCLASS()
class LASTCOLLISIONBUG_API APMCTestActor : public AActor
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		UMyProceduralMeshComponent* Mesh;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Sets default values for this actor's properties
	APMCTestActor();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
		void CalculateBoxMesh(const FVector& InCenter, const FVector& InExtents, TArray<FVector>& OutVertices, TArray<int32>& OutTriangles, TArray<FVector>& OutNormals, TArray<FVector2D>& OutUV0, TArray<FVector2D>& OutUV1, TArray<FVector2D>& OutUV2, TArray<FVector2D>& OutUV3, TArray<FLinearColor>& OutVertexColors, TArray<FProcMeshTangent>& OutTangents);

	UFUNCTION(BlueprintCallable)
		void ConvertTangents(const TArray<FVector>& InSource, bool bFlipTangentY, TArray<FProcMeshTangent>& OutResult);
};
