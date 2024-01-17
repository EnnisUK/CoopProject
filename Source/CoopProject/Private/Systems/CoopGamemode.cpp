// Fill out your copyright notice in the Description page of Project Settings.


#include "Systems/CoopGamemode.h"
#include "UObject/ConstructorHelpers.h"
#include "Systems/CharacterController.h"



ACoopGameMode::ACoopGameMode()
{
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/bp_MainCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}

	PlayerControllerClass = ACharacterController::StaticClass();
}


