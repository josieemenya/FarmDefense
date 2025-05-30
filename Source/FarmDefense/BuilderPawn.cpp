// Fill out your copyright notice in the Description page of Project Settings.


#include "BuilderPawn.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/Controller.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "FarmDefenseCharacter.h"
#include "Kismet/KismetSystemLibrary.h"
#include "InputActionValue.h"
#include "K2Node_SpawnActorFromClass.h"
#include "Animation/AnimSequence.h"

#include "Components/SkeletalMeshComponent.h"
#include "Components/SphereComponent.h"
#include "Blueprint/UserWidget.h"
#include "Engine/Level.h"
#include "GameFramework/GameModeBase.h"
#include "Kismet/GameplayStatics.h"



void ABuilderPawn::BeginPlay()
{
	Super::BeginPlay();
	GEngine->AddOnScreenDebugMessage(1, 5, FColor::Red, "BeginPlay");
	
}

void ABuilderPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ABuilderPawn::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	//Super::SetupPlayerInputComponent(PlayerInputComponent);
	if (APlayerController* PlayerController = Cast<APlayerController>(GetController()))
		if (UEnhancedInputLocalPlayerSubsystem* PawnSubsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			PawnSubsystem->ClearAllMappings();
			PawnSubsystem->AddMappingContext(BuilderMapping, 1);
		}
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(IA_Build, ETriggerEvent::Triggered, this, &ABuilderPawn::Build);
		EnhancedInputComponent->BindAction(IA_Look, ETriggerEvent::Triggered, this, &ABuilderPawn::Look);
		EnhancedInputComponent->BindAction(IA_Move, ETriggerEvent::Triggered, this, &ABuilderPawn::Move);
		
	}
	
}

void ABuilderPawn::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
	if (EEndPlayReason::Destroyed)
	{
		
		if (Cast<ACharacter>(Character) == nullptr)
		{
			GetWorld()->SpawnActor<ACharacter>(Character);
			UGameplayStatics::GetPlayerController(GetWorld(), 0)->Possess(Cast<ACharacter>(Character));
		}
		else
			UGameplayStatics::GetPlayerController(GetWorld(), 0)->Possess(Cast<ACharacter>(Character));
	} else if (EEndPlayReason::Quit)
		UE_LOG(LogTemp, Display, TEXT("End Play Quit"));
}

ABuilderPawn::ABuilderPawn()
{
	Camera = CreateDefaultSubobject<UCameraComponent>(FName("Camera"));
	Camera->SetupAttachment(GetRootComponent());
	Peabody = Cast<ACharacter>(Character);
}

void ABuilderPawn::Buildable(bool bCanBuild, FTransform SpawnTransform, TSubclassOf<AActor> SpawnableBuildClass)
{
	if (bCanBuild) // if mode is in build mode && is not overlapping any actors or static meshes
	{
		//SpawnTransform.SetLocation(FVector(SpawnTransform.GetLocation().X, SpawnTransform.GetLocation().Y, SpawnTransform.GetLocation().Z + 20));  
		FActorSpawnParameters SpawnParameters;
		SpawnParameters.Owner = this;
		SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
		AActor* BuildActor =  GetWorld()->SpawnActor<AActor>(SpawnableBuildClass, SpawnTransform, SpawnParameters);
		GEngine->AddOnScreenDebugMessage(101000, 50.f, FColor::Red, "built bby");
	} else
	{
		GEngine->AddOnScreenDebugMessage(101000, 50.f, FColor::Red, "friiiiiick");
	}
}


void ABuilderPawn::Build(const FInputActionValue& Value)
{
	//GEngine->AddOnScreenDebugMessage(1, 5, FColor::Red, "Build");
}

void ABuilderPawn::Move(const FInputActionValue& Value)
{
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	
		// get right vector 
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		// add movement 
		AddMovementInput(ForwardDirection, MovementVector.Y);
		AddMovementInput(RightDirection, MovementVector.X);
	}
}

void ABuilderPawn::Look(const FInputActionValue& Value)
{
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add yaw and pitch input to controller
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	} else
		UE_LOG(LogTemp, Display, TEXT("Look Up Look"));
}


