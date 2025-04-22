// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Controller.h"
#include "PlayerControls.generated.h"

/**
 * 
 */
UCLASS()
class FARMDEFENSE_API APlayerControls : public AController
{
	GENERATED_BODY()

protected:

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;


	public:
	
	UPROPERTY(EditAnywhere)
	ACharacter* PlayerPawn;

	UPROPERTY(EditAnywhere)
	TSubclassOf<AActor> CharacterCLass;

	UPROPERTY(EditAnywhere)
	class ASpectatorPawn* BuilderPawn;

	UPROPERTY(EditAnywhere)
	TSubclassOf<ASpectatorPawn> PawnClass;

	TArray<AActor*> Actore;
	TArray<ACharacter*> PlayerPawns;
	TArray<ASpectatorPawn*> Pawns;
	
};
