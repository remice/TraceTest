// Fill out your copyright notice in the Description page of Project Settings.


#include "Tester.h"
#include "Components/StaticMeshComponent.h"
#include "TestManager.h"
#include "Kismet/KismetSystemLibrary.h"

#define PATH_SPHERE TEXT("/Engine/BasicShapes/Sphere.Sphere")

// Sets default values
ATester::ATester()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));

	ConstructorHelpers::FObjectFinder<UStaticMesh> M_SPHERE(PATH_SPHERE);
	check(M_SPHERE.Succeeded());

	Mesh->SetStaticMesh(M_SPHERE.Object);
	SetRootComponent(Mesh);

	bDebugDraw = false;
}

// Called when the game starts or when spawned
void ATester::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATester::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATester::StartFirstLineTrace()
{
	ensure(IsValid(Manager));

	switch (Manager->GetFirstMethod())
	{
	case TestMethod::LineTrace:
		ExLineTrace();
		break;

	case TestMethod::LineTraceMulti:
		ExLineTraceMulti();
		break;

	case TestMethod::BoxTrace:
		ExBoxTrace();
		break;

	case TestMethod::BoxTraceMulti:
		ExBoxTraceMulti();
		break;

	case TestMethod::SphereTrace:
		ExSphereTrace();
		break;

	case TestMethod::SphereTraceMulti:
		ExSphereTraceMulti();
		break;

	case TestMethod::SweepTrace:
		ExSweepTrace();
		break;

	case TestMethod::SweepTraceMulti:
		ExSweepTraceMulti();
		break;

	default:
		UE_LOG(LogTemp, Warning, TEXT("Method enum is Default"));
		break;
	}
}

void ATester::StartSecondLineTrace()
{
	ensure(IsValid(Manager));

	switch (Manager->GetFirstMethod())
	{
	case TestMethod::LineTrace:
		ExLineTrace();
		break;

	case TestMethod::LineTraceMulti:
		ExLineTraceMulti();
		break;

	case TestMethod::BoxTrace:
		ExBoxTrace();
		break;

	case TestMethod::BoxTraceMulti:
		ExBoxTraceMulti();
		break;

	case TestMethod::SphereTrace:
		ExSphereTrace();
		break;

	case TestMethod::SphereTraceMulti:
		ExSphereTraceMulti();
		break;

	case TestMethod::SweepTrace:
		ExSweepTrace();
		break;

	case TestMethod::SweepTraceMulti:
		ExSweepTraceMulti();
		break;

	default:
		UE_LOG(LogTemp, Warning, TEXT("Method enum is Default"));
		break;
	}
}

void ATester::ExLineTrace()
{
	FHitResult HitResult;
	bool IsCollide;
	if (bDebugDraw)
	{
		IsCollide = UKismetSystemLibrary::LineTraceSingleForObjects(GetWorld(), GetActorLocation(), GetActorLocation() + (FVector(0, 1, 0) * Manager->GetWeaponLength()),
			Manager->GetObjectTypeArray(), true, Manager->GetIgnoreActorArray(), EDrawDebugTrace::ForDuration, HitResult, true);
	}
	else
	{
		IsCollide = UKismetSystemLibrary::LineTraceSingleForObjects(GetWorld(), GetActorLocation(), GetActorLocation() + (FVector(0, 1, 0) * Manager->GetWeaponLength()),
			Manager->GetObjectTypeArray(), true, Manager->GetIgnoreActorArray(), EDrawDebugTrace::None, HitResult, true);
	}

	if (IsCollide == false)
	{
		Manager->FailCollide();
	}
}

void ATester::ExLineTraceMulti()
{
	TArray<FHitResult> HitResult;
	bool IsCollide;
	if (bDebugDraw)
	{
		IsCollide = UKismetSystemLibrary::LineTraceMultiForObjects(GetWorld(), GetActorLocation(), GetActorLocation() + (FVector(0, 1, 0) * Manager->GetWeaponLength()),
			Manager->GetObjectTypeArray(), true, Manager->GetIgnoreActorArray(), EDrawDebugTrace::ForDuration, HitResult, true);
	}
	else
	{
		IsCollide = UKismetSystemLibrary::LineTraceMultiForObjects(GetWorld(), GetActorLocation(), GetActorLocation() + (FVector(0, 1, 0) * Manager->GetWeaponLength()),
			Manager->GetObjectTypeArray(), true, Manager->GetIgnoreActorArray(), EDrawDebugTrace::None, HitResult, true);
	}

	if (IsCollide == false)
	{
		Manager->FailCollide();
		return;
	}

	if (HitResult.Num() != Manager->GetCheckedActorSpawnCount())
	{
		Manager->FailCollide();
	}
}

void ATester::ExBoxTrace()
{
	FHitResult HitResult;
	bool IsCollide;
	if (bDebugDraw)
	{
		IsCollide = UKismetSystemLibrary::BoxTraceSingleForObjects(GetWorld(), GetActorLocation(), GetActorLocation() + (FVector(0, 1, 0) * Manager->GetWeaponLength()),
			Manager->GetBoxHalfSize(), Manager->GetBoxOrientation(),
			Manager->GetObjectTypeArray(), true, Manager->GetIgnoreActorArray(), EDrawDebugTrace::ForDuration, HitResult, true);
	}
	else
	{
		IsCollide = UKismetSystemLibrary::BoxTraceSingleForObjects(GetWorld(), GetActorLocation(), GetActorLocation() + (FVector(0, 1, 0) * Manager->GetWeaponLength()),
			Manager->GetBoxHalfSize(), Manager->GetBoxOrientation(),
			Manager->GetObjectTypeArray(), true, Manager->GetIgnoreActorArray(), EDrawDebugTrace::None, HitResult, true);
	}

	if (IsCollide == false)
	{
		Manager->FailCollide();
	}
}

void ATester::ExBoxTraceMulti()
{
	TArray<FHitResult> HitResult;
	bool IsCollide;
	if (bDebugDraw)
	{
		IsCollide = UKismetSystemLibrary::BoxTraceMultiForObjects(GetWorld(), GetActorLocation(), GetActorLocation() + (FVector(0, 1, 0) * Manager->GetWeaponLength()),
			Manager->GetBoxHalfSize(), Manager->GetBoxOrientation(),
			Manager->GetObjectTypeArray(), true, Manager->GetIgnoreActorArray(), EDrawDebugTrace::ForDuration, HitResult, true);
	}
	else
	{
		IsCollide = UKismetSystemLibrary::BoxTraceMultiForObjects(GetWorld(), GetActorLocation(), GetActorLocation() + (FVector(0, 1, 0) * Manager->GetWeaponLength()),
			Manager->GetBoxHalfSize(), Manager->GetBoxOrientation(),
			Manager->GetObjectTypeArray(), true, Manager->GetIgnoreActorArray(), EDrawDebugTrace::None, HitResult, true);
	}

	if (IsCollide == false)
	{
		Manager->FailCollide();
	}

	if (HitResult.Num() < Manager->GetCheckedActorSpawnCount())
	{
		Manager->FailCollide();
	}
}

void ATester::ExSphereTrace()
{
	FHitResult HitResult;
	bool IsCollide;
	if (bDebugDraw)
	{
		IsCollide = UKismetSystemLibrary::SphereTraceSingleForObjects(GetWorld(), GetActorLocation(), GetActorLocation() + (FVector(0, 1, 0) * Manager->GetWeaponLength()),
			Manager->GetSphereRadius(),
			Manager->GetObjectTypeArray(), true, Manager->GetIgnoreActorArray(), EDrawDebugTrace::ForDuration, HitResult, true);
	}
	else
	{
		IsCollide = UKismetSystemLibrary::SphereTraceSingleForObjects(GetWorld(), GetActorLocation(), GetActorLocation() + (FVector(0, 1, 0) * Manager->GetWeaponLength()),
			Manager->GetSphereRadius(),
			Manager->GetObjectTypeArray(), true, Manager->GetIgnoreActorArray(), EDrawDebugTrace::None, HitResult, true);
	}

	if (IsCollide == false)
	{
		Manager->FailCollide();
	}
}

void ATester::ExSphereTraceMulti()
{
	TArray<FHitResult> HitResult;
	bool IsCollide;
	if (bDebugDraw)
	{
		IsCollide = UKismetSystemLibrary::SphereTraceMultiForObjects(GetWorld(), GetActorLocation(), GetActorLocation() + (FVector(0, 1, 0) * Manager->GetWeaponLength()),
			Manager->GetSphereRadius(),
			Manager->GetObjectTypeArray(), true, Manager->GetIgnoreActorArray(), EDrawDebugTrace::ForDuration, HitResult, true);
	}
	else
	{
		IsCollide = UKismetSystemLibrary::SphereTraceMultiForObjects(GetWorld(), GetActorLocation(), GetActorLocation() + (FVector(0, 1, 0) * Manager->GetWeaponLength()),
			Manager->GetSphereRadius(),
			Manager->GetObjectTypeArray(), true, Manager->GetIgnoreActorArray(), EDrawDebugTrace::None, HitResult, true);
	}

	if (IsCollide == false)
	{
		Manager->FailCollide();
	}

	if (HitResult.Num() < Manager->GetCheckedActorSpawnCount())
	{
		Manager->FailCollide();
	}
}

void ATester::ExSweepTrace()
{
}

void ATester::ExSweepTraceMulti()
{
}
