// Fill out your copyright notice in the Description page of Project Settings.


#include "ToonTankGameModeBase.h"


void AToonTankGameModeBase::BeginPlay()
{
	//Get references and game win/lose conditions.

	//Call HandleGameStart() to initialize the start countdown, turret activation, pawn check etc. 

}

void AToonTankGameModeBase::ActorDied(AActor* DeadActor)
{
	// Check what type of Actor died. If Turret, tally. If Player -> go to lose condition. 
}

void AToonTankGameModeBase::HandleGameStart()
{
	//Initialize the start countdown, turret activation, pawn check etc. 
	//Call Blueprint version GameStart()
}

void AToonTankGameModeBase::HandleGameOver(bool PlayerWon) 
{
	//See if the player has destroyed all the turrets, show win result. 
	// else if turret destroyed player, show lose result. 
	//Call blueprint version GameOver(bool)

}
