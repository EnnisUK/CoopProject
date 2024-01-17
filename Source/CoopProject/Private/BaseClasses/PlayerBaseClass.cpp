// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseClasses/PlayerBaseClass.h"

#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Engine/StaticMeshActor.h"
#include "Particles/ParticleSystem.h"
#include "Systems/MainGameInstance.h"
#include "Kismet/GameplayStatics.h"


// Sets default values
APlayerBaseClass::APlayerBaseClass()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    M_SpringArm = CreateDefaultSubobject<USpringArmComponent>("SpringArm");
    M_SpringArm->SetupAttachment(RootComponent);

    M_Camera = CreateDefaultSubobject<UCameraComponent>("Camera");
    M_Camera->SetupAttachment(M_SpringArm);
	M_Camera->bUsePawnControlRotation = false;

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f);

}

// Called when the game starts or when spawned
void APlayerBaseClass::BeginPlay()
{
	Super::BeginPlay();


	

	if (APlayerController* PC = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PC->GetLocalPlayer()))
		{
			Subsystem->ClearAllMappings();
			Subsystem->AddMappingContext(M_PlayerMappingContext, 0);
		}
		
	}

}

void APlayerBaseClass::Move(const FInputActionValue& Value)
{
    if (Controller != nullptr)
    {
        const FVector2D MoveValue = Value.Get<FVector2D>();
        const FRotator MovementRotation(0, Controller->GetControlRotation().Yaw, 0);

        // Forward/Backward direction
        if (MoveValue.Y != 0.f)
        {
            // Get forward vector
            const FVector Direction = MovementRotation.RotateVector(FVector::ForwardVector);

            AddMovementInput(Direction, MoveValue.Y);
        }

        // Right/Left direction
        if (MoveValue.X != 0.f)
        {
            // Get right vector
            const FVector Direction = MovementRotation.RotateVector(FVector::RightVector);

            AddMovementInput(Direction, MoveValue.X);
        }
    }
}

void APlayerBaseClass::Look(const FInputActionValue& Value)
{
    // input is a Vector2D
    const FVector2D LookAxisVector = Value.Get<FVector2D>();

    if (Controller != nullptr)
    {
        AddControllerYawInput(LookAxisVector.X);
        AddControllerPitchInput(LookAxisVector.Y);
    }
}

void APlayerBaseClass::ServerRPC_StartSprint_Implementation()
{
	GetCharacterMovement()->MaxWalkSpeed = 1200;
}

void APlayerBaseClass::ServerRPC_EndSprint_Implementation()
{
	GetCharacterMovement()->MaxWalkSpeed = 700;
}

void APlayerBaseClass::Sprint()
{
	

	if (bIsSprinting == false)
	{
		bIsSprinting = true;
		GetCharacterMovement()->MaxWalkSpeed = 1200;
		ServerRPC_StartSprint();
		GEngine->AddOnScreenDebugMessage(-1,2,FColor::Red,TEXT("StartedSprint"));
	}
	else
	{
		bIsSprinting = false;
		GetCharacterMovement()->MaxWalkSpeed = 700;
		ServerRPC_EndSprint();
		GEngine->AddOnScreenDebugMessage(-1,2,FColor::Red,TEXT("EndedSprint"));
	}
}






// Called every frame
void APlayerBaseClass::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APlayerBaseClass::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent);
	
	EnhancedInputComponent->BindAction(M_MoveAction, ETriggerEvent::Triggered, this, &APlayerBaseClass::Move);
    EnhancedInputComponent->BindAction(M_LookAction, ETriggerEvent::Triggered, this, &APlayerBaseClass::Look);
    EnhancedInputComponent->BindAction(M_JumpAction, ETriggerEvent::Triggered, this, &ACharacter::Jump);
	EnhancedInputComponent->BindAction(M_JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);
	EnhancedInputComponent->BindAction(M_SprintAction, ETriggerEvent::Triggered, this, &APlayerBaseClass::Sprint);
  

}

