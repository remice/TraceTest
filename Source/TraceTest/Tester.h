// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Tester.generated.h"

UCLASS()
class TRACETEST_API ATester : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATester();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

// Get/Setter
public:
	FORCEINLINE void SetTestManager(class ATestManager* InTestManager) { Manager = InTestManager; };

public:
	UFUNCTION()
	void StartFirstLineTrace();

	UFUNCTION()
	void StartSecondLineTrace();

public:
	UPROPERTY()
	uint8 bDebugDraw : 1;

private:
	void ExLineTrace();
	void ExLineTraceMulti();
	void ExBoxTrace();
	void ExBoxTraceMulti();
	void ExSphereTrace();
	void ExSphereTraceMulti();
	void ExSweepTrace();
	void ExSweepTraceMulti();

private:
	UPROPERTY()
	TObjectPtr<class UStaticMeshComponent> Mesh;

	UPROPERTY()
	TObjectPtr<class ATestManager> Manager;
};
