// Fill out your copyright notice in the Description page of Project Settings.


#include "AxeWeapon.h"
#include "Components/StaticMeshComponent.h"
#include "Components/CapsuleComponent.h"

// Sets default values
AAxeWeapon::AAxeWeapon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Axe = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Weapon"));
	Axe->SetupAttachment(GetRootComponent());
	Axe->SetWorldScale3D(FVector(50, 50, 50));

	TriggerCapsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule"));
	TriggerCapsule->SetupAttachment(GetRootComponent());
	

}

// Called when the game starts or when spawned
void AAxeWeapon::BeginPlay()
{
	Super::BeginPlay();
	if (TriggerCapsule)
	{
		TriggerCapsule->OnComponentBeginOverlap.AddDynamic(this, &AAxeWeapon::OnBeginOverlap);
		TriggerCapsule->OnComponentEndOverlap.AddDynamic(this, &AAxeWeapon::OnEndOverlap);
	}
}

// Called every frame
void AAxeWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AAxeWeapon::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	GEngine->AddOnScreenDebugMessage(222, 13.f, FColor::MakeRandomColor(), TEXT("freak you"));
	if (OtherActor == this)
		return;
	if (OtherActor && OtherActor != this)
		OverlappedActor = OtherActor;
	if (OtherActor->ActorHasTag(FName("QuinnCharacter")))
		GEngine->AddOnScreenDebugMessage(222, 13.f, FColor::MakeRandomColor(), TEXT("Hello World"));
	else
		GEngine->AddOnScreenDebugMessage(222, 13.f, FColor::MakeRandomColor(), TEXT("Goodbye World"));
}

void AAxeWeapon::OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex)
{
	if(OtherActor && OtherActor != this)
		OverlappedActor = nullptr;
	
}
