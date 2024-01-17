// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "MainSaveGame.generated.h"

/**
 * 
 */
UCLASS()
class COOPPROJECT_API UMainSaveGame : public USaveGame
{
	GENERATED_BODY()

public:
	//Variables

	UMainSaveGame();

	UPROPERTY(EditAnywhere)
	float M_MasterVolume;

	
};
