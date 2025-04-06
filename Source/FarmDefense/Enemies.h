// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "EnemyInterface.h"
#include "Enemies.generated.h"

UCLASS()
class FARMDEFENSE_API AEnemies : public ACharacter, public  IEnemyInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AEnemies();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditAnywhere)
	FEnemyStats enemy_stats;

	UFUNCTION(BlueprintPure)
	float GetHealth() { return enemy_stats.Health; } 

};
