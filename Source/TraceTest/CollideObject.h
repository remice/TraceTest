// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CollideObject.generated.h"

UCLASS()
class TRACETEST_API ACollideObject : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACollideObject();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	void AddInstanceToPosition(FVector SpawnPosition);

private:
	UPROPERTY(EditAnywhere, Category = "Pattern")
	TObjectPtr<class UInstancedStaticMeshComponent> InstancedStaticMeshes;

};
