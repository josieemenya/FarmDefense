// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemySpawn.h"
#include "BehaviorTree/BehaviorTree.h"




void AEnemySpawn::BeginPlay()
{
	GEngine->AddOnScreenDebugMessage(18, 10.f, FColor::MakeRandomColor(), TEXT("work!! omfg"));
	RunBehaviorTree(EnemyTree);
}

void AEnemySpawn::OnPossess(APawn* ControlledPawn)
{
	
	(EnemyTree)? GEngine->AddOnScreenDebugMessage(14, 10.f, FColor::MakeRandomColor(), TEXT("WeRun")) : GEngine->AddOnScreenDebugMessage(4, 10.f, FColor::MakeRandomColor(), TEXT("We Fall"));
	
	//MoveToActor(Player, 100.f);

}
