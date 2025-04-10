// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BehaviorTree.h"
#include "EnemyBehaviourT.generated.h"

/**
 * 
 */
UCLASS()
class FARMDEFENSE_API UEnemyBehaviourT : public UBehaviorTree
{
	GENERATED_BODY()

	public:
	UPROPERTY(EditAnywhere)
	TObjectPtr<UBlackboardData> MyBlackboard;

	UPROPERTY(EditAnywhere)
	TObjectPtr<class UEdGraph> MyGraph;

	UPROPERTY(EditAnywhere)
	TObjectPtr<class UBTCompositeNode> Root;
	
};
