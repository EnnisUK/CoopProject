// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Actor.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "TriggerActor.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FSwitchReplicatePhysics, AActor*, OwnerActor);

UCLASS()
class COOPPROJECT_API ATriggerActor : public AActor
{
	GENERATED_BODY()
	

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite ,meta = (AllowPrivateAccess = "true" ,DisplayName = "Mesh"))
	UStaticMeshComponent* M_Mesh;


	
	
public:	
	// Sets default values for this actor's properties
	ATriggerActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	UPROPERTY(BlueprintAssignable)
	FSwitchReplicatePhysics M_SwitchPhysics;

};
