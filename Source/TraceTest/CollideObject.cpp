// Fill out your copyright notice in the Description page of Project Settings.


#include "CollideObject.h"
#include "Components/InstancedStaticMeshComponent.h"

#define PATH_SPHERE TEXT("/Engine/BasicShapes/Sphere.Sphere")

// Sets default values
ACollideObject::ACollideObject()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ConstructorHelpers::FObjectFinder<UStaticMesh> M_SPHERE(PATH_SPHERE);
	check(M_SPHERE.Succeeded());

	// Setup default instancedStaticMesh setting
	InstancedStaticMeshes = CreateDefaultSubobject<UInstancedStaticMeshComponent>(TEXT("NAME_InstancedStaticMesh"));
	InstancedStaticMeshes->CastShadow = false;
	InstancedStaticMeshes->SetCollisionProfileName(TEXT("OverlapAll"));
	InstancedStaticMeshes->SetGenerateOverlapEvents(false);
	InstancedStaticMeshes->bMultiBodyOverlap = false;
	InstancedStaticMeshes->SetCanEverAffectNavigation(false);
	InstancedStaticMeshes->SetStaticMesh(M_SPHERE.Object);

	SetRootComponent(InstancedStaticMeshes);
}

// Called when the game starts or when spawned
void ACollideObject::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACollideObject::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACollideObject::AddInstanceToPosition(FVector SpawnPosition)
{
	if (InstancedStaticMeshes->GetStaticMesh() == nullptr)
	{
		return;
	}

	FRotator SpawnRot = FRotator(0);
	FVector SpawnScale = FVector(1, 1, 1);

	FTransform3d SpawnTrans(SpawnRot, SpawnPosition, SpawnScale);
	InstancedStaticMeshes->AddInstance(SpawnTrans, true);
}

