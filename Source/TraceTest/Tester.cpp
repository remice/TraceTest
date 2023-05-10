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

	case TestMethod::SphereOverlap:
		ExSphereOverlap();
		break;

	case TestMethod::SphereOverlapComp:
		ExSphereOverlapComponents();
		break;

	case TestMethod::BoxOverlap:
		ExBoxOverlap();
		break;

	case TestMethod::CapsuleOverlap:
		ExCapsuleOverlap();
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

	case TestMethod::SphereOverlap:
		ExSphereOverlap();
		break;

	case TestMethod::SphereOverlapComp:
		ExSphereOverlapComponents();
		break;

	case TestMethod::BoxOverlap:
		ExBoxOverlap();
		break;

	case TestMethod::CapsuleOverlap:
		ExCapsuleOverlap();
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
	for (int32 Index = 0; Index < Manager->GetLineSpawnCount(); Index++)
	{
		FVector TraceLocation = GetActorLocation() + FVector(0, 0, 1) * Index;
		if (bDebugDraw)
		{
			IsCollide = UKismetSystemLibrary::LineTraceSingleForObjects(GetWorld(), TraceLocation, TraceLocation + (FVector(0, 1, 0) * Manager->GetWeaponLength()),
				Manager->GetObjectTypeArray(), true, Manager->GetIgnoreActorArray(), EDrawDebugTrace::ForDuration, HitResult, true);
		}
		else
		{
			IsCollide = UKismetSystemLibrary::LineTraceSingleForObjects(GetWorld(), TraceLocation, TraceLocation + (FVector(0, 1, 0) * Manager->GetWeaponLength()),
				Manager->GetObjectTypeArray(), true, Manager->GetIgnoreActorArray(), EDrawDebugTrace::None, HitResult, true);
		}

		if (IsCollide == false && bDebugDraw == false)
		{
			Manager->FailCollide();
		}
	}
}

void ATester::ExLineTraceMulti()
{
	TArray<FHitResult> HitResult;
	bool IsCollide;
	for (int32 Index = 0; Index < Manager->GetLineSpawnCount(); Index++)
	{
		FVector TraceLocation = GetActorLocation() + FVector(0, 0, 1) * Index;
		if (bDebugDraw)
		{
			IsCollide = UKismetSystemLibrary::LineTraceMultiForObjects(GetWorld(), TraceLocation, TraceLocation + (FVector(0, 1, 0) * Manager->GetWeaponLength()),
				Manager->GetObjectTypeArray(), true, Manager->GetIgnoreActorArray(), EDrawDebugTrace::ForDuration, HitResult, true);
		}
		else
		{
			IsCollide = UKismetSystemLibrary::LineTraceMultiForObjects(GetWorld(), TraceLocation, TraceLocation + (FVector(0, 1, 0) * Manager->GetWeaponLength()),
				Manager->GetObjectTypeArray(), true, Manager->GetIgnoreActorArray(), EDrawDebugTrace::None, HitResult, true);
		}

		if (IsCollide == false && bDebugDraw == false)
		{
			Manager->FailCollide();
		}

		if (HitResult.Num() != Manager->GetCheckedActorSpawnCount() && bDebugDraw == false)
		{
			Manager->FailCollide();
		}
	}
}

void ATester::ExBoxTrace()
{
	FHitResult HitResult;
	bool IsCollide;

	for (int32 Index = 0; Index < Manager->GetLineSpawnCount(); Index++)
	{
		FVector TraceLocation = GetActorLocation() + FVector(0, 0, 1) * Index;
		if (bDebugDraw)
		{
			IsCollide = UKismetSystemLibrary::BoxTraceSingleForObjects(GetWorld(), TraceLocation, TraceLocation + (FVector(0, 1, 0) * Manager->GetWeaponLength()),
				Manager->GetBoxHalfSize(), Manager->GetBoxOrientation(),
				Manager->GetObjectTypeArray(), true, Manager->GetIgnoreActorArray(), EDrawDebugTrace::ForDuration, HitResult, true);
		}
		else
		{
			IsCollide = UKismetSystemLibrary::BoxTraceSingleForObjects(GetWorld(), TraceLocation, TraceLocation + (FVector(0, 1, 0) * Manager->GetWeaponLength()),
				Manager->GetBoxHalfSize(), Manager->GetBoxOrientation(),
				Manager->GetObjectTypeArray(), true, Manager->GetIgnoreActorArray(), EDrawDebugTrace::None, HitResult, true);
		}

		if (IsCollide == false && bDebugDraw == false)
		{
			Manager->FailCollide();
		}
	}
}

void ATester::ExBoxTraceMulti()
{
	TArray<FHitResult> HitResult;
	bool IsCollide;
	for (int32 Index = 0; Index < Manager->GetLineSpawnCount(); Index++)
	{
		FVector TraceLocation = GetActorLocation() + FVector(0, 0, 1) * Index;
		if (bDebugDraw)
		{
			IsCollide = UKismetSystemLibrary::BoxTraceMultiForObjects(GetWorld(), TraceLocation, TraceLocation + (FVector(0, 1, 0) * Manager->GetWeaponLength()),
				Manager->GetBoxHalfSize(), Manager->GetBoxOrientation(),
				Manager->GetObjectTypeArray(), true, Manager->GetIgnoreActorArray(), EDrawDebugTrace::ForDuration, HitResult, true);
		}
		else
		{
			IsCollide = UKismetSystemLibrary::BoxTraceMultiForObjects(GetWorld(), TraceLocation, TraceLocation + (FVector(0, 1, 0) * Manager->GetWeaponLength()),
				Manager->GetBoxHalfSize(), Manager->GetBoxOrientation(),
				Manager->GetObjectTypeArray(), true, Manager->GetIgnoreActorArray(), EDrawDebugTrace::None, HitResult, true);
		}

		if (IsCollide == false && bDebugDraw == false)
		{
			Manager->FailCollide();
		}

		if (HitResult.Num() < Manager->GetCheckedActorSpawnCount() && bDebugDraw == false)
		{
			Manager->FailCollide();
		}
	}
}

void ATester::ExSphereTrace()
{
	FHitResult HitResult;
	bool IsCollide;
	for (int32 Index = 0; Index < Manager->GetLineSpawnCount(); Index++)
	{
		FVector TraceLocation = GetActorLocation() + FVector(0, 0, 1) * Index;
		if (bDebugDraw)
		{
			IsCollide = UKismetSystemLibrary::SphereTraceSingleForObjects(GetWorld(), TraceLocation, TraceLocation + (FVector(0, 1, 0) * Manager->GetWeaponLength()),
				Manager->GetSphereRadius(),
				Manager->GetObjectTypeArray(), true, Manager->GetIgnoreActorArray(), EDrawDebugTrace::ForDuration, HitResult, true);
		}
		else
		{
			IsCollide = UKismetSystemLibrary::SphereTraceSingleForObjects(GetWorld(), TraceLocation, TraceLocation + (FVector(0, 1, 0) * Manager->GetWeaponLength()),
				Manager->GetSphereRadius(),
				Manager->GetObjectTypeArray(), true, Manager->GetIgnoreActorArray(), EDrawDebugTrace::None, HitResult, true);
		}

		if (IsCollide == false && bDebugDraw == false)
		{
			Manager->FailCollide();
		}
	}
}

void ATester::ExSphereTraceMulti()
{
	TArray<FHitResult> HitResult;
	bool IsCollide;
	for (int32 Index = 0; Index < Manager->GetLineSpawnCount(); Index++)
	{
		FVector TraceLocation = GetActorLocation() + FVector(0, 0, 1) * Index;
		if (bDebugDraw)
		{
			IsCollide = UKismetSystemLibrary::SphereTraceMultiForObjects(GetWorld(), TraceLocation, TraceLocation + (FVector(0, 1, 0) * Manager->GetWeaponLength()),
				Manager->GetSphereRadius(),
				Manager->GetObjectTypeArray(), true, Manager->GetIgnoreActorArray(), EDrawDebugTrace::ForDuration, HitResult, true);
		}
		else
		{
			IsCollide = UKismetSystemLibrary::SphereTraceMultiForObjects(GetWorld(), TraceLocation, TraceLocation + (FVector(0, 1, 0) * Manager->GetWeaponLength()),
				Manager->GetSphereRadius(),
				Manager->GetObjectTypeArray(), true, Manager->GetIgnoreActorArray(), EDrawDebugTrace::None, HitResult, true);
		}

		if (IsCollide == false && bDebugDraw == false)
		{
			Manager->FailCollide();
		}

		if (HitResult.Num() < Manager->GetCheckedActorSpawnCount() && bDebugDraw == false)
		{
			Manager->FailCollide();
		}
	}
}

void ATester::ExSphereOverlap()
{
	TArray<UPrimitiveComponent*> HitResult;
	bool IsCollide;
	for (int32 Index = 0; Index < Manager->GetLineSpawnCount(); Index++)
	{
		FVector TraceLocation = GetActorLocation() + FVector(0, 0, 1) * Index;
		IsCollide = UKismetSystemLibrary::SphereOverlapComponents(GetWorld(), TraceLocation + (FVector(0, 1, 0) * Manager->GetWeaponLength()),
			Manager->GetSphereRadius(),
			Manager->GetObjectTypeArray(), NULL, Manager->GetIgnoreActorArray(), HitResult);

		if (IsCollide == false && bDebugDraw == false)
		{
			Manager->FailCollide();
		}

		if (HitResult.Num() < Manager->GetCheckedActorSpawnCount() && bDebugDraw == false)
		{
			Manager->FailCollide();
		}
	}
}

void ATester::ExSphereOverlapComponents()
{
	TArray<UPrimitiveComponent*> HitResult;
	bool IsCollide;
	for (int32 Index = 0; Index < Manager->GetLineSpawnCount(); Index++)
	{
		FVector TraceLocation = GetActorLocation() + FVector(0, 0, 1) * Index;
		IsCollide = UKismetSystemLibrary::SphereOverlapComponents(GetWorld(), TraceLocation + (FVector(0, 1, 0) * Manager->GetSweepDistance()),
			Manager->GetSphereRadius(),
			Manager->GetObjectTypeArray(), NULL, Manager->GetIgnoreActorArray(), HitResult);

		if (IsCollide == false && bDebugDraw == false)
		{
			Manager->FailCollide();
		}

		if (HitResult.Num() < Manager->GetCheckedActorSpawnCount() && bDebugDraw == false)
		{
			Manager->FailCollide();
		}
	}
}

void ATester::ExBoxOverlap()
{
	TArray<FOverlapResult> Overlaps;
	bool IsCollide;

	FCollisionObjectQueryParams CollisionQueryParam;
	for (auto Iter = Manager->GetObjectTypeArray().CreateConstIterator(); Iter; ++Iter)
	{
		const ECollisionChannel& Channel = UCollisionProfile::Get()->ConvertToCollisionChannel(false, *Iter);
		CollisionQueryParam.AddObjectTypesToQuery(Channel);
	}

	for (int32 Index = 0; Index < Manager->GetLineSpawnCount(); Index++)
	{
		FVector TraceLocation = GetActorLocation() + FVector(0, 0, 1) * Index;

		IsCollide = GetWorld()->OverlapMultiByObjectType(Overlaps, TraceLocation + (FVector(0, 1, 0) * Manager->GetSweepDistance()), FQuat::Identity, CollisionQueryParam, FCollisionShape::MakeBox(Manager->GetBoxHalfSize() + FVector(0, Manager->GetSweepDistance(), 0)));

		if (IsCollide == false && bDebugDraw == false)
		{
			Manager->FailCollide();
		}

		if (Overlaps.Num() < Manager->GetCheckedActorSpawnCount() && bDebugDraw == false)
		{
			Manager->FailCollide();
		}
	}
}

void ATester::ExCapsuleOverlap()
{
	TArray<UPrimitiveComponent*> HitResult;
	bool IsCollide;
	for (int32 Index = 0; Index < Manager->GetLineSpawnCount(); Index++)
	{
		FVector TraceLocation = GetActorLocation() + FVector(0, 0, 1) * Index;
		IsCollide = UKismetSystemLibrary::CapsuleOverlapComponents(GetWorld(), TraceLocation + (FVector(0, 1, 0) * Manager->GetSweepDistance()),
			Manager->GetSphereRadius(), Manager->GetSweepDistance(),
			Manager->GetObjectTypeArray(), NULL, Manager->GetIgnoreActorArray(), HitResult);

		if (IsCollide == false && bDebugDraw == false)
		{
			Manager->FailCollide();
		}

		if (HitResult.Num() < Manager->GetCheckedActorSpawnCount() && bDebugDraw == false)
		{
			Manager->FailCollide();
		}
	}
}
