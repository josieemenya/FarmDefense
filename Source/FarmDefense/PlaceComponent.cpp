// Fill out your copyright notice in the Description page of Project Settings.


#include "PlaceComponent.h"

#include "K2Node_DoOnceMultiInput.h"
#include "Components/StaticMeshComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/Character.h"

// Sets default values for this component's properties
UPlaceComponent::UPlaceComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UPlaceComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UPlaceComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UPlaceComponent::PreviewLoop()
{
	FHitResult Hit;
	FVector StartLocation = CameraComp->GetComponentLocation();
	FVector EndLocation = StartLocation + (CameraComp->GetForwardVector() * 500);
	GetWorld()->LineTraceSingleByChannel(Hit,  StartLocation, EndLocation, ECC_Visibility);
	DrawDebugLine(GetWorld(), StartLocation, EndLocation, FColor::Red);
	if (Hit.bBlockingHit)
	{
		int32 i = 2;
		do
		{
			if (Character)
				Character->AddComponentByClass(MeshRef, true, Transform, false);
		} while (i == 2); // my own do once
		Transform.SetLocation(Hit.Location);
		
		MeshRef->SetWorldTransform(Transform);
	}
}
