// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "EnemySpawn.generated.h"

/**
 * 
 */
UCLASS()
class FARMDEFENSE_API AEnemySpawn : public AAIController
{
	GENERATED_BODY()

	protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
	class UBehaviorTree* EnemyTree;
	
};
