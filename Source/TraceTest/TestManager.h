// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TestManager.generated.h"

UENUM()
enum class TestMethod : uint8
{
	LineTrace = 0,
	LineTraceMulti,
	SphereTrace,
	SphereTraceMulti,
	BoxTrace,
	BoxTraceMulti,
	SphereOverlap,
	SphereOverlapComp,
	BoxOverlap,
	CapsuleOverlap
};

DECLARE_MULTICAST_DELEGATE(FOnStartTesterSignature)

UCLASS()
class TRACETEST_API ATestManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATestManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

// Get/Setter
public:
	FORCEINLINE TArray<TEnumAsByte<EObjectTypeQuery>> GetObjectTypeArray() const { return ObjectTypesArray; }
	FORCEINLINE TArray<TObjectPtr<AActor>> GetIgnoreActorArray() const { return IgnoreActorArray; }
	FORCEINLINE const float& GetSweepDistance() { return OverlapDistance; }
	FORCEINLINE const float& GetWeaponLength() { return WeaponLength; }
	FORCEINLINE const float& GetAttackSpeed() { return AttackSpeed; }
	FORCEINLINE const TestMethod& GetFirstMethod() { return FirstMethod; }
	FORCEINLINE const TestMethod& GetSecondMethod() { return SecondMethod; }
	FORCEINLINE const int32& GetLineSpawnCount() { return LineSpawnCount; }
	FORCEINLINE const float& GetSphereRadius() { return SphereRadius; }
	FORCEINLINE const FVector& GetBoxHalfSize() { return BoxHalfSize; }
	FORCEINLINE const FRotator& GetBoxOrientation() { return BoxOrientation; }
	//FORCEINLINE const class UShapeComponent* GetSweepCollision() { return SweepCollision; }
	FORCEINLINE const int32& GetCheckedActorSpawnCount() { return CheckedActorSpawnCount; }

public:
	FORCEINLINE void FailCollide() { FailCount++; }

private:
	void SpawnAllTester();
	void SpawnAllCollideManager();
	void CheckFailNumber();

// Attack Setting Section
private:
	UPROPERTY(EditAnywhere, Category = "AttackSetting")
	float OverlapDistance;

	UPROPERTY(EditAnywhere, Category = "AttackSetting", meta = (ClampMin = "0.001"))
	float WeaponLength;

	//UPROPERTY(EditAnywhere, Category = "AttackSetting")
	float AttackSpeed;

	//UPROPERTY(EditAnywhere, Category = "AttackSetting")
	int32 AttackRepeatCount;

// Test Setting Section
private:
	UPROPERTY(EditAnywhere, Category = "TestSetting")
	TestMethod FirstMethod;

	//UPROPERTY(EditAnywhere, Category = "TestSetting")
	TestMethod SecondMethod;

	//UPROPERTY(EditAnywhere, Category = "TestSetting")
	float TestDelay;

	UPROPERTY(EditAnywhere, Category = "TestSetting")
	float PreDelay;

	UPROPERTY(EditAnywhere, Category = "TestSetting")
	int32 TestActorSpawnCount;

	UPROPERTY(EditAnywhere, Category = "TestSetting")
	int32 CheckedActorSpawnCount;

	UPROPERTY(EditAnywhere, Category = "TestSetting")
	float CheckedActorSpawnDistance;

// Collision Setting Section
private:
	UPROPERTY(EditAnywhere, Category = "LineSetting")
	int32 LineSpawnCount;

	UPROPERTY(EditAnywhere, Category = "SphereSetting")
	float SphereRadius;

	UPROPERTY(EditAnywhere, Category = "BoxSetting")
	FVector BoxHalfSize;

	UPROPERTY(EditAnywhere, Category = "BoxSetting")
	FRotator BoxOrientation;

	//UPROPERTY(EditAnywhere, Category = "SweepSetting")
	//TObjectPtr<class UShapeComponent> SweepCollision;

// Manager Section
private:
	int32 FailCount = 0;
	float CurDelay = 0.f;
	FVector InitPosition;
	FOnStartTesterSignature FirstStart;
	FOnStartTesterSignature SecondStart;

	UPROPERTY()
	TArray<TObjectPtr<class ACollideObject>> CollideManagers;

	UPROPERTY()
	TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypesArray;

	UPROPERTY()
	TArray<TObjectPtr<AActor>> IgnoreActorArray;
};
