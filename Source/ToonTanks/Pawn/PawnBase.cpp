// Fill out your copyright notice in the Description page of Project Settings.


#include "PawnBase.h"
#include "Components/CapsuleComponent.h"

// Sets default values
APawnBase::APawnBase()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CapsuleComp = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule Collider"));
	RootComponent = CapsuleComp;

	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Base Mesh")); 
	BaseMesh->SetupAttachment(RootComponent); //Need to establish relationship between Capsule Comp and Base Mesh, Base Mesh gets information from capsule comp

	TurretMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Turret Mesh"));
	TurretMesh->SetupAttachment(BaseMesh);

	ProjectileSpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("Projectile Spawn Point")); 
	ProjectileSpawnPoint->SetupAttachment(TurretMesh); 
}

void APawnBase::RotateTurret(FVector Target)
{
	//Update TurretMesh rotation to face towards the Target passed in from Child Classes. 
	FVector TargetClean = FVector(Target.X, Target.Y, TurretMesh->GetComponentLocation().Z);
	FVector StartLocation = TurretMesh->GetComponentLocation();

	FRotator TurretRotation = FVector(TargetClean - StartLocation).Rotation();
	TurretMesh->SetWorldRotation(TurretRotation);

}

void APawnBase::Fire()
{
	UE_LOG(LogTemp, Warning, TEXT("Fire Condition Success"));
}

void APawnBase::HandleDestruction()
{

}

