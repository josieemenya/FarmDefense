// Fill out your copyright notice in the Description page of Project Settings.


#include "PlaceComponent.h"

#include "K2Node_DoOnceMultiInput.h"
#include "ShaderCompiler.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SceneComponent.h"
#include "Materials/Material.h"
#include "Camera/CameraComponent.h"
#include "Landscape.h"

#include "Kismet/GameplayStatics.h"

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
	//Character = UGameplayStatics::GetActorOfClass(APawn, NULL);
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
	if (Character, MeshRef, NewMesh, PerfectMaterial, BadMaterial){
		CameraComp = Cast<UCameraComponent>(Character->GetComponentByClass(UCameraComponent::StaticClass()));
		FHitResult Hit;
		if (CameraComp){	
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
					Mesh = NewObject<UStaticMeshComponent>(MeshRef);
					Mesh->SetStaticMesh(NewMesh);
				} while (i == 2); // my own do once
				Transform.SetLocation(Hit.Location);

		
		
				Mesh->SetWorldTransform(Transform);
				TArray<AActor*> Overlaps;
				Mesh->GetOverlappingActors(Overlaps);
		
				if ((Overlaps.Num() == 0 && CanBuild(Overlaps)) || CanBuild(Overlaps))
					Mesh->SetMaterial(0, PerfectMaterial);
				else
					Mesh->SetMaterial(0, BadMaterial);
			}
		}
	}
}

bool UPlaceComponent::CanBuild(TArray<AActor*> GetOverlaps)
{
	for (auto c : GetOverlaps)
		if (!(c->IsA(TheGround)))
			return false;
	return true;
}
