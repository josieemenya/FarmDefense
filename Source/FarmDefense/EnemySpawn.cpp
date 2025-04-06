// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemySpawn.h"
#include "BehaviorTree/BehaviorTree.h"



void AEnemySpawn::BeginPlay()
{
    RunBehaviorTree(EnemyTree); 
}
