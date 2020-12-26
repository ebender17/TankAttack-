// Fill out your copyright notice in the Description page of Project Settings.


#include "ToonTankGameModeBase.h"
#include "ToonTanks/Pawn/PawnTank.h"
#include "ToonTanks/Pawn/PawnTurret.h"
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

	//Call Blueprint version GameStart()
	GameStart();
}

void AToonTankGameModeBase::HandleGameOver(bool PlayerWon) 
{
	//See if the player has destroyed all the turrets, show win result. 
	// else if turret destroyed player, show lose result. 
	//Call blueprint version GameOver(bool)
	GameOver(PlayerWon);

}

int32 AToonTankGameModeBase::GetTargetTurretCount()
{
	TArray<AActor*> TurretActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), APawnTurret::StaticClass(), TurretActors);
	return TurretActors.Num();
}