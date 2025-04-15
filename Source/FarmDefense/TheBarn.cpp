// Fill out your copyright notice in the Description page of Project Settings.


#include "TheBarn.h"
#include "Components/StaticMeshComponent.h"
#include "Blueprint/UserWidget.h"

// Sets default values
ATheBarn::ATheBarn()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	GetBarnStats = FBarnStats(100, 100, 200);
	BarnMesh = CreateDefaultSubobject<UStaticMeshComponent>("BarnMesh");
	BarnMesh->SetupAttachment(GetRootComponent());
	HealthBar = CreateWidget<UUserWidget>(GetWorld(), HealthBarClass, TEXT("Health"));
	

}

// Called when the game starts or when spawned
void ATheBarn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATheBarn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

int32 ATheBarn::GetHealth_Implementation(const FBarnStats& Stats)
{
	return Stats.Health;
}

bool ATheBarn::CanAttack_Implementation(float Range, const FBarnStats& Stats)
{
	return (Range <= Stats.AttackRange);
}

