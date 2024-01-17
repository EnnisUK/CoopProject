// Fill out your copyright notice in the Description page of Project Settings.


#include "Systems/CharacterController.h"
#include "Blueprint/WidgetBlueprintLibrary.h"

void ACharacterController::BeginPlay()
{
	Super::BeginPlay();

	this->SetShowMouseCursor(false);
	UWidgetBlueprintLibrary::SetInputMode_GameOnly(this);
	
}
