// Fill out your copyright notice in the Description page of Project Settings.


#include "ToonTankGameModeBase.h"
#include "ToonTanks/Pawn/PawnTank.h"
#include "ToonTanks/Pawn/PawnTurret.h"
#include "ToonTanks/PlayerControllers/PlayerControllerBase.h"
#include "Kismet/GameplayStatics.h"

void AToonTankGameModeBase::BeginPlay()
{
	//Get references and game win/lose conditions.

	//Call HandleGameStart() to initialize the start countdown, turret activation, pawn check etc. 

	Super::BeginPlay();

	HandleGameStart();
}

void AToonTankGameModeBase::ActorDied(AActor* DeadActor)
{
	// Check what type of Actor died. If Turret, tally. If Player -> go to lose condition. 
	if (DeadActor == PlayerTank)
	{
		PlayerTank->HandleDestruction();
		HandleGameOver(false); 

		if (PlayerControllerRef)
		{
			PlayerControllerRef->SetPlayerEnabledState(false);
		}
	}
	else if (APawnTurret* DestroyedTurret = Cast<APawnTurret>(DeadActor)) 
	{
		DestroyedTurret->HandleDestruction(); 
		if (--TargetTurrets == 0)
		{
			HandleGameOver(true); 
		}
	}
}

void AToonTankGameModeBase::HandleGameStart()
{
	//Initialize the start countdown, turret activation, pawn check etc. 
	TargetTurrets = GetTargetTurretCount();
	PlayerTank = Cast<APawnTank>(UGameplayStatics::GetPlayerPawn(this, 0));
	PlayerControllerRef = Cast<APlayerControllerBase>(UGameplayStatics::GetPlayerController(this, 0));

	//Call Blueprint version GameStart()
	GameStart();

	if (PlayerControllerRef)
	{
		PlayerControllerRef->SetPlayerEnabledState(false);

		FTimerHandle PlayerEnableHandle; 
		FTimerDelegate PlayerEnableDelegate = FTimerDelegate::CreateUObject(PlayerControllerRef, &APlayerControllerBase::SetPlayerEnabledState, true);
		GetWorld()->GetTimerManager().SetTimer(PlayerEnableHandle, PlayerEnableDelegate, StartDelay, false);
	}
}

void AToonTankGameModeBase::HandleGameOver(bool PlayerWon) 
{
	//Call blueprint version GameOver(bool)
	GameOver(PlayerWon);

}

int32 AToonTankGameModeBase::GetTargetTurretCount()
{
	TArray<AActor*> TurretActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), APawnTurret::StaticClass(), TurretActors);
	return TurretActors.Num();
}