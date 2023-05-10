// Fill out your copyright notice in the Description page of Project Settings.


#include "TestManager.h"
#include "Tester.h"
#include "CollideObject.h"
#include "Kismet/KismetSystemLibrary.h"

// Sets default values
ATestManager::ATestManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Attack setting default values
	OverlapDistance = 100.f;
	WeaponLength = 400.f;
	AttackSpeed = 1.f;
	AttackRepeatCount = 1;

	// Test setting default values
	TestDelay = 5.f;
	PreDelay = 5.f;
	TestActorSpawnCount = 1000;
	CheckedActorSpawnCount = 5;
	CheckedActorSpawnDistance = 10.f;

	// Collision setting default values
	LineSpawnCount = 1;
	SphereRadius = 10.f;
	BoxHalfSize = FVector(10, 10, 10);
	BoxOrientation = FRotator(0, 0, 0);
	ObjectTypesArray.Emplace(UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_WorldStatic));
	IgnoreActorArray.Empty();

	// Manager setting default values
	InitPosition = FVector(0, 0, 100.f);
}

// Called when the game starts or when spawned
void ATestManager::BeginPlay()
{
	Super::BeginPlay();

	SpawnAllCollideManager();
	SpawnAllTester();

	//FTimerHandle TempTimerHandle;
	//GetWorld()->GetTimerManager().SetTimer(TempTimerHandle, this, &ATestManager::CheckFailNumber, 0.1f, true, PreDelay);
	//CheckFailNumber();
}

// Called every frame
void ATestManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	CurDelay += DeltaTime;

	if (CurDelay > PreDelay)
	{
		FirstStart.Broadcast();
		//PreDelay += 10000;

		CheckFailNumber();
	}
}

void ATestManager::SpawnAllTester()
{
	ensureMsgf(TestActorSpawnCount > 0, TEXT("TestActorSpawnCount must upper than zero"));

	float PositionModifier = -4.5f;
	FVector SpawnPosition = FVector(400, 1000, 0);

	// Setting special tester
	static FActorSpawnParameters Param;
	ATester* FirstTester = GetWorld()->SpawnActor<ATester>(ATester::StaticClass(), InitPosition, FRotator(0), Param);

	FirstTester->SetTestManager(this);
	FirstStart.AddUObject(FirstTester, &ATester::StartFirstLineTrace);
	SecondStart.AddUObject(FirstTester, &ATester::StartSecondLineTrace);
	FirstTester->bDebugDraw = true;

	// Setting tester
	for (int32 Index = 1; Index <= TestActorSpawnCount; Index++)
	{
		FVector RealSpawnPosition = FVector(SpawnPosition.X * PositionModifier, SpawnPosition.Y, InitPosition.Z);
		ATester* Tester = GetWorld()->SpawnActor<ATester>(ATester::StaticClass(), RealSpawnPosition, FRotator(0), Param);

		Tester->SetTestManager(this);
		FirstStart.AddUObject(Tester, &ATester::StartFirstLineTrace);
		SecondStart.AddUObject(Tester, &ATester::StartSecondLineTrace);

		for (int32 Ix = 0; Ix < CollideManagers.Num(); Ix++)
		{
			FVector CollideSpawnPosition = FVector(SpawnPosition.X * PositionModifier, SpawnPosition.Y + 200 + (CheckedActorSpawnDistance * Ix), InitPosition.Z);
			CollideManagers[Ix]->AddInstanceToPosition(CollideSpawnPosition);
		}

		PositionModifier += 1.f;
		if (Index % 10 == 0)
		{
			SpawnPosition += FVector(0, 1000, 0);
			PositionModifier = -4.5f;
		}
	}
}

void ATestManager::SpawnAllCollideManager()
{
	FActorSpawnParameters Params;
	for (int32 Index = 1; Index <= CheckedActorSpawnCount; Index++)
	{
		ACollideObject* CollideManager = GetWorld()->SpawnActor<ACollideObject>(ACollideObject::StaticClass(), FVector(0), FRotator(0), Params);
		CollideManagers.Emplace(CollideManager);
	}
}

void ATestManager::CheckFailNumber()
{
	UE_LOG(LogTemp, Log, TEXT("[Fail Count] %d"), FailCount);
	FailCount = 0;
}
