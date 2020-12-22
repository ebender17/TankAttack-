// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ToonTankGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKS_API AToonTankGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

private:
	void HandleGameStart();
	void HandleGameOver(bool PlayerWon);

public: 
	void ActorDied(AActor* DeadActor);

protected:
	virtual void BeginPlay() override;
	UFUNCTION(BlueprintImplementableEvent)
	void GameStart();
	UFUNCTION(BlueprintImplementableEvent)
	void GameOver(bool PlayerWon);
	
};
