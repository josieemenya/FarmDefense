// Fill out your copyright notice in the Description page of Project Settings.


#include "PestControl.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"


APestControl::APestControl()
{
    //BehaviorTree = Make
}


void APestControl::OnPossess(APawn* ControlledPawn)
{
   if (BehaviorTree && BehaviorTree->BlackboardAsset)
   {
       RunBehaviorTree(BehaviorTree);
       UE_LOG(LogTemp, Warning, TEXT("Run BehaviorTree"));
       //Blackboard->SetValueAsObject("Target Player", MyPlayer);
   }    
}