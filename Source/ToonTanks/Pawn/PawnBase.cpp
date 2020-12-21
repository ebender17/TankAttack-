// Fill out your copyright notice in the Description page of Project Settings.


#include "PawnBase.h"
#include "Components/CapsuleComponent.h"
#include "ToonTanks/Actors/ProjectileBase.h"

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
	//Get ProjectileSpawnPoint Location && Rotation -> Spawn Projectile class at location firing towards rotation 
	if (ProjectileClass)
	{
		FVector SpawnLocation = ProjectileSpawnPoint->GetComponentLocation();
		FRotator SpawnRotation = ProjectileSpawnPoint->GetComponentRotation();

		AProjectileBase* TempProjectile = GetWorld()->SpawnActor<AProjectileBase>(ProjectileClass, SpawnLocation, SpawnRotation);
		//Set to use later, if owner of projectile is actor who fired it, it will not cause damage
		TempProjectile->SetOwner(this);
	}
}

void APawnBase::HandleDestruction()
{

}

