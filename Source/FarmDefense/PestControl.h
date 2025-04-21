// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "PestControl.generated.h"

/**
 * 
 */
UCLASS()
class FARMDEFENSE_API APestControl : public AAIController
{
	GENERATED_BODY()

	public:
	APestControl();
	
	virtual void OnPossess(APawn* ControlledPawn) override;

	UPROPERTY(EditAnywhere)
	class UBehaviorTree* BehaviorTree;

	UPROPERTY(EditAnywhere)
	class UBlackboardComponent* BlackboardB;

	TSubclassOf<AActor> MyPlayer;
	
};
