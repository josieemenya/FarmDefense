// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerControls.h"

#include "Engine/Engine.h"
#include "GameFramework/Character.h"
#include "GameFramework/SpectatorPawn.h"
#include "Kismet/GameplayStatics.h"
#include "Tests/AutomationCommon.h"

void APlayerControls::BeginPlay()
{
    UGameplayStatics::GetAllActorsOfClass( this, CharacterCLass, Actore);
    for (auto c : Actore)
    {
        if (ACharacter* actor = Cast<ACharacter>(c))
        {
            PlayerPawns.Add(actor); 
        } if (ASpectatorPawn* Spectator = Cast<ASpectatorPawn>(c))
        {
            Pawns.Add(Spectator);
        }
    }
}

void APlayerControls::Tick(float delta)
{
    for (auto p : Pawns){}
    for (auto p : PlayerPawns)
    {
        FString TFuckYou = p->GetName();
        GEngine->AddOnScreenDebugMessage(1, 0.1, FColor::MakeRandomColor(), TFuckYou);
    }
}
