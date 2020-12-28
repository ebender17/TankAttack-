// Fill out your copyright notice in the Description page of Project Settings.


#include "PawnTank.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"

APawnTank::APawnTank()
{
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm")); 
	SpringArm->SetupAttachment(RootComponent); 

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera")); 
	Camera->SetupAttachment(SpringArm);
}

// Called when the game starts or when spawned
void APawnTank::BeginPlay()
{
	Super::BeginPlay();

	PlayerControllerRef = Cast<APlayerController>(GetController());

}

// Called every frame
void APawnTank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	Rotate();
	Move();

	if (PlayerControllerRef)
	{
		//Grabbing location tank turret needs to rotate to 
		FHitResult TraceHitResult;
		PlayerControllerRef->GetHitResultUnderCursor(ECC_Visibility, false, TraceHitResult);
		FVector HitLocation = TraceHitResult.ImpactPoint;

		RotateTurret(HitLocation);
	}
}

// Called to bind functionality to input
void APawnTank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis("MoveForward", this, &APawnTank::CalculateMoveInput);
	PlayerInputComponent->BindAxis("Turn", this, &APawnTank::CalculateRotateInput);
	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &APawnTank::Fire);

}

void APawnTank::HandleDestruction()
{
	Super::HandleDestruction();

	bIsPlayerAlive = false;

	SetActorHiddenInGame(true);
	SetActorTickEnabled(false);
}

bool APawnTank::GetIsPlayerAlive()
{
	return bIsPlayerAlive;

}

void APawnTank::CalculateMoveInput(float Value)
{
	//Only moving on x axis 
	MoveDirection = FVector(Value * MoveSpeed * GetWorld()->DeltaTimeSeconds, 0, 0);
}

void APawnTank::CalculateRotateInput(float Value)
{
	float RotateAmount = Value * RotateSpeed * GetWorld()->DeltaTimeSeconds;
	FRotator Rotation = FRotator(0, RotateAmount, 0);
	RotationDirection = FQuat(Rotation);

}

void APawnTank::Move()
{
	//Sweep option asks whether collision should be checked whether moving
	//Set to true here
	AddActorLocalOffset(MoveDirection, true);
}

void APawnTank::Rotate()
{
	//Set sweep option to true again to avoid weird glitches
	AddActorLocalRotation(RotationDirection, true);

}