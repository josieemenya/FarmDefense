// Copyright Epic Games, Inc. All Rights Reserved.

#include "FarmDefenseCharacter.h"

#include <ThirdParty/ShaderConductor/ShaderConductor/External/DirectXShaderCompiler/include/dxc/DXIL/DxilConstants.h>

#include "AnalyticsEventAttribute.h"
#include "Engine/LocalPlayer.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/Controller.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Kismet/KismetSystemLibrary.h"
#include "InputActionValue.h"
#include "Animation/AnimSequence.h"
#include "Animation/AnimInstance.h"
#include "EnemyInterface.h"
#include "PlantInterface.h"
#include "WeaponInterface.h"
#include "Components/SkeletalMeshComponent.h"
#include "Sound/SoundBase.h"
#include "Components/SphereComponent.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"

DEFINE_LOG_CATEGORY(LogTemplateCharacter);

//////////////////////////////////////////////////////////////////////////
// AFarmDefenseCharacter

AFarmDefenseCharacter::AFarmDefenseCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
		
	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f); // ...at this rotation rate

	// Note: For faster iteration times these variables, and many more, can be tweaked in the Character Blueprint
	// instead of recompiling to adjust them
	GetCharacterMovement()->JumpZVelocity = 700.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;
	GetCharacterMovement()->BrakingDecelerationFalling = 1500.0f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 400.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named ThirdPersonCharacter (to avoid direct content references in C++)
	Actions = 5; 
	OverlapSphere = CreateDefaultSubobject<USphereComponent>(TEXT("OverlapSphere"));
	OverlapSphere->SetupAttachment(RootComponent);
	OverlapSphere->SetSphereRadius(30.f);
	ContextMenuWidget = nullptr;
	
	this->PlayerStatsInfo = FPlayerInfo(11, 100.f, 32.f, 100.f, 100.f, 0);
	this->PlayerStatsInfo.Stamina = GetMaxStamina_Implementation();
	PlayerStatsInfo = FPlayerInfo(21, 100, 43, 100, 100, 0);
	PlayerStatsInfo.Stamina = GetMaxStamina_Implementation();

	bAttacking = false;

	

	
}

void AFarmDefenseCharacter::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();
	localbool = true;
	if (OverlapSphere)
	{
		OverlapSphere->OnComponentBeginOverlap.AddDynamic(this, &AFarmDefenseCharacter::OnOverlap);
		OverlapSphere->OnComponentEndOverlap.AddDynamic(this, &AFarmDefenseCharacter::EndOverlap);
	}
	UGameplayStatics::GetPlayerController(GetWorld(), 0)->bEnableClickEvents = true;
	isAxeEquipped = EAxeEquippedState::AxeUnequipped;

	//ObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_Pawn));

	FTimerHandle TimerHandle;
	enlarge = false;
	UGameplayStatics::GetPlayerController(GetWorld(), 0)->SetShowMouseCursor(false);
	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = this;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
	AxeTarget = GetWorld()->SpawnActor<AActor>(Axe, this->GetActorLocation(), this->GetActorRotation(), SpawnParams);
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &AFarmDefenseCharacter::EquipAxe, 2.0f, true);
	


}

void AFarmDefenseCharacter::EquipAxe()
{
	if (isAxeEquipped != EAxeEquippedState::AxeEquipped && SkeletalMesh && SkeletalMesh->DoesSocketExist(FName("hand_lSocket")))
	{
		AxeTarget->AttachToComponent(SkeletalMesh, FAttachmentTransformRules::SnapToTargetNotIncludingScale, FName("hand_lSocket"));
		AxeTarget->SetActorEnableCollision(false);
		isAxeEquipped = EAxeEquippedState::AxeEquipped;
		if (AxeTarget->Implements<UWeaponInterface>())
		{
			Damage = IWeaponInterface::Execute_GetWeaponDamage(AxeTarget); 
		}
	}
}


void AFarmDefenseCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	if (NewController == UGameplayStatics::GetPlayerController(GetWorld(), 0))
	{
		
		TheHUD = CreateWidget<UUserWidget>(GetWorld(), TheHUDClass);
		TheHUD->Construct();
		TheHUD->AddToViewport();
	}
}

void AFarmDefenseCharacter::UnPossessed()
{
	Super::UnPossessed();
	TheHUD->RemoveFromParent();
	TheHUD->Destruct();
	// replace remove from parent w/ remove from viewport if it doesn't work, 
}

void AFarmDefenseCharacter::HitDetect()
{
	FVector Start, End;
	if (SkeletalMesh && SkeletalMesh->DoesSocketExist(FName("hand_lSocket")))
	{
		
		Start = SkeletalMesh->GetSocketLocation(FName("hand_lSocket"));
		End = SkeletalMesh->GetSocketLocation(FName("hand_lSocket"));
		float Radius = 50.f;
		ObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_Pawn)); 
		TArray<AActor*> IgnoredActors;
		FHitResult Hit;
		UKismetSystemLibrary::SphereTraceSingleForObjects(GetWorld(), Start, End, Radius, ObjectTypes, false, IgnoredActors, EDrawDebugTrace::Persistent, Hit, true, FColor::MakeRandomColor());
		if (Hit.bBlockingHit && Hit.GetActor() && Hit.GetActor() != this)
		{
			if (Hit.GetActor()->Implements<UEnemyInterface>())
			{
				SetActorScale3D(FVector(5.f, 5.f, 5.f));
				IEnemyInterface::Execute_TakeDamage(Hit.GetActor(), Damage);
			}
		}
	} else
	{
		return; //this->Destroy.AddDynamic(this, &AFarmDefenseCharacter::HitDetect);
	}
}


float AFarmDefenseCharacter::GetTotalWealth_Implementation()
{
	return this->PlayerStatsInfo.TotalWealth;
}

void AFarmDefenseCharacter::AddTotalWealth_Implementation(float MoneyAdded)
{
	this->PlayerStatsInfo.TotalWealth += MoneyAdded;
}

void AFarmDefenseCharacter::TakeAwayWealth_Implementation(float MoneyTakenAway)
{
	this->PlayerStatsInfo.TotalWealth -= MoneyTakenAway;
}

int32 AFarmDefenseCharacter::GetTotalDays_Implementation()
{
	return this->PlayerStatsInfo.TotalDays;
}

/*void AFarmDefenseCharacter::AddToInventory(FPlayerInfo& PlayerStats, AActor* InventoryActor)
{
	if (InventoryActor != nullptr)
	{
		// if size is not over certain size, if actor is not in inventor/has tag stackable; yadda yadda
		PlayerStats.Inventory.Add(InventoryActor);
	}
}*/

void AFarmDefenseCharacter::ChangeInStamina_Implementation(float Cost)
{
	PlayerStatsInfo.Stamina += Cost;
	SetPlayerStatsInfo(PlayerStatsInfo);
	MarkPackageDirty();
	//FString x = FString::FromInt(PlayerStatsInfo.Stamina) + FString::FromInt(this->PlayerStatsInfo.Stamina);
	//GEngine->AddOnScreenDebugMessage(45, 20.f, FColor::MakeRandomColor(), x);
}

void AFarmDefenseCharacter::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
	PlayerStatsInfo = FPlayerInfo(100.f, 100.f, 32.f, 100.f, 100.f, 0);
} 

void AFarmDefenseCharacter::TheNextDay_Implementation()
{
	++this->PlayerStatsInfo.TotalDays;
}

float AFarmDefenseCharacter::GetHealth_Implementation()
{
	return this->PlayerStatsInfo.Health;
}

float AFarmDefenseCharacter::GetMaxHealth_Implementation()
{
	return this->PlayerStatsInfo.MaxHealth;
}

float AFarmDefenseCharacter::GetStamina_Implementation()
{
	return GetPlayerStatsInfo().Stamina;
}

float AFarmDefenseCharacter::GetMaxStamina_Implementation()
{
	return this->PlayerStatsInfo.MaxStamina;
}

void AFarmDefenseCharacter::ChangeInHealth_Implementation(float Change)
{
	(Change > 0)? HealHealth_Implementation(Change) : TakeHealth_Implementation(Change);
}

void AFarmDefenseCharacter::HealHealth_Implementation(float HealPoint)
{
	this->PlayerStatsInfo.Health += HealPoint;
}

void AFarmDefenseCharacter::TakeHealth_Implementation(float DamagePoint)
{
	this->PlayerStatsInfo.Health += DamagePoint;
}

void AFarmDefenseCharacter::Attack(const FInputActionValue& Value)
{
	bool Pressed = Value.Get<bool>();
	if (Pressed)
	{
		
		if (AnimInstanceR)
		{
			SetActorScale3D(FVector(30.f, 30.f, 30.f));
			if (bAttacking)
				return; 
	
			bAttacking = true;
			if (AttackMontage && AnimInstanceR->Montage_IsPlaying(AttackMontage) == false)
			{
				SetActorScale3D(FVector(1.f, 1.f, 1.f));
				AnimInstanceR->Montage_Play(AttackMontage);
				bAttacking = false;
			}
			else SetActorScale3D(FVector(20.f, 20.f, 20.f));
		} else
		{
			SetActorScale3D(FVector(20.f, 20.f, 20.f));
		}
	}
}

//////////////////////////////////////////////////////////////////////////
// Input

void AFarmDefenseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	// Add Input Mapping Context
	if (APlayerController* PlayerController = Cast<APlayerController>(GetController()))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->ClearAllMappings();
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}
	
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent)) {
		
		// Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		// Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AFarmDefenseCharacter::Move);

		// Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AFarmDefenseCharacter::Look);

		EnhancedInputComponent->BindAction(TriggerAction, ETriggerEvent::Triggered, this, &AFarmDefenseCharacter::Trigger);
		EnhancedInputComponent->BindAction(OpenContextMenuAction, ETriggerEvent::Triggered, this, &AFarmDefenseCharacter::OpenContextMenu);
		EnhancedInputComponent->BindAction(AttackEnemies, ETriggerEvent::Triggered, this, &AFarmDefenseCharacter::Attack);
		
		
	}
	else
	{
		UE_LOG(LogTemplateCharacter, Error, TEXT("'%s' Failed to find an Enhanced Input component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
	}
}


void AFarmDefenseCharacter::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
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

void AFarmDefenseCharacter::Look(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add yaw and pitch input to controller
		AddControllerYawInput(LookAxisVector.X); 
		AddControllerPitchInput(LookAxisVector.Y);
	}
}

void AFarmDefenseCharacter::Trigger(const FInputActionValue& Value)
{
	Mesh = GetMesh(); 
	bool Triggered = Value.Get<bool>();
	time = 0; 
	if (Controller != nullptr)
	{
		if(Triggered && GetOverlappingActor())
		{
			if(GetOverlappingActor()->Implements<UInteractInterface>())
			{
				bBeginAnim = true;
				
				if (GetOverlappingActor()->Implements<UPlantInterface>())
				{
					IPlantInterface::Execute_WaterPlant(GetOverlappingActor());
					IInteractInterface::Execute_Action(GetOverlappingActor());
					UGameplayStatics::PlaySoundAtLocation(this, WaterSound, this->GetActorLocation());
					//GEngine->AddOnScreenDebugMessage(12, 20.f, FColor::Red, TEXT("WaterPlant_Implementation"));
				}
			} else return; // change to widget... maybe
		}
	}
}

void AFarmDefenseCharacter::OpenContextMenu(const FInputActionValue& Value)
{
	GEngine->AddOnScreenDebugMessage(10, 12.f, FColor::MakeRandomColor(), TEXT("we acknowlege you??"));
	
	bool Pressed = Value.Get<bool>();

	if (FlipFlop(ContextMenuWidget) && Pressed)
	{
		
		ContextMenuWidget = CreateWidget<UUserWidget>(GetWorld(), ContextMenuWidgetClass);
		ContextMenuWidget->Construct();
		ContextMenuWidget->AddToViewport();
		GEngine->AddOnScreenDebugMessage(10, 12.f, FColor::MakeRandomColor(), TEXT("MadeContextMenu"));
		UGameplayStatics::GetPlayerController(GetWorld(), 0)->SetShowMouseCursor(true);
		//UGameplayStatics::SetGlobalTimeDilation(GetWorld(), 0.f);
		
	} else
	{
		//UGameplayStatics::SetGlobalTimeDilation(GetWorld(), 1.f);
		ContextMenuWidget->RemoveFromViewport();
		ContextMenuWidget->Destruct();
		GEngine->AddOnScreenDebugMessage(10, 12.f, FColor::MakeRandomColor(), TEXT("Killed That Bitch Local Menu"));
		UGameplayStatics::GetPlayerController(GetWorld(), 0)->SetShowMouseCursor(false);
		UGameplayStatics::SetGamePaused(GetWorld(), false);
	}
	
}



//  && OverlappingItem->Implements<UInteractInterface>()
//IInteractInterface::Execute_Action(OverlappingItem); 


void AFarmDefenseCharacter::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AActor* ActorRef = Cast<AActor>(OtherActor);
	
	if (OtherActor == this)
		return;
	
	(ActorRef) ? GEngine->AddOnScreenDebugMessage(1, 10.f, FColor::MakeRandomColor(), ActorRef->GetName()) : GEngine->AddOnScreenDebugMessage(1, 10.f, FColor::MakeRandomColor(), TEXT("OverlappingPlant is invalid")); // if this doesn't print, ensure has aborted function meaning ref isn't valid
	if (ActorRef) {
		SetOverlappingActor(ActorRef);
		UGameplayStatics::GetPlayerController(GetWorld(), 0)->SetShowMouseCursor(true);
	} else {
		GEngine->AddOnScreenDebugMessage(2, 10.f, FColor::MakeRandomColor(), TEXT("No dice")); // if this doesn't print, ensure has aborted function meaning ref isn't valid

	}

}

void AFarmDefenseCharacter::EndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex)
{
	AActor* ActorRef = Cast<AActor>(OtherActor);
	if (OtherActor == this)
		return;
	if (ActorRef) { SetOverlappingActor(nullptr); UGameplayStatics::GetPlayerController(GetWorld(), 0)->SetShowMouseCursor(false);} else UE_LOG(LogTemp, Warning, TEXT("OverlappingPlant is invalid"));
}



void AFarmDefenseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//DrawDebugSphere(GetWorld(), GetMesh()->GetSocketLocation("hand_lSocket"), 10.f, 12, FColor::Red, false, 2.f);
}

void AFarmDefenseCharacter::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
    Super::PostEditChangeProperty(PropertyChangedEvent);

    if (PropertyChangedEvent.Property != nullptr)
    {

        FName PropertyName = PropertyChangedEvent.Property->GetFName();

        if (PropertyName == GET_MEMBER_NAME_CHECKED(AFarmDefenseCharacter, PlayerStatsInfo))
        {
           SetPlayerStatsInfo(PlayerStatsInfo);
           UE_LOG(LogTemp, Warning, TEXT("YourProperty has been changed!"));
        }
    }
}