// Copyright Epic Games, Inc. All Rights Reserved.

#include "ProjectPCharacter.h"

#include "AbilitySystemComponent.h"
#include "Attribute/PPCharacterAttributeSet.h"
#include "UObject/ConstructorHelpers.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/SpringArmComponent.h"
#include "Materials/Material.h"
#include "Engine/World.h"
#include "Player/PPPlayerState.h"

UAbilitySystemComponent* AProjectPCharacter::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

AProjectPCharacter::AProjectPCharacter()
{
	AbilitySystemComponent = nullptr;
	// Set size for player capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// Don't rotate character to camera direction
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Rotate character to moving direction
	GetCharacterMovement()->RotationRate = FRotator(0.f, 640.f, 0.f);
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;

	// Create a camera boom...
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->SetUsingAbsoluteRotation(true); // Don't want arm to rotate when character does
	CameraBoom->TargetArmLength = 800.f;
	CameraBoom->SetRelativeRotation(FRotator(-60.f, 0.f, 0.f));
	CameraBoom->bDoCollisionTest = false; // Don't want to pull camera in when it collides with level

	// Create a camera...
	TopDownCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("TopDownCamera"));
	TopDownCameraComponent->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	TopDownCameraComponent->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	// Activate ticking in order to update the cursor every frame.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;
}

void AProjectPCharacter::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);
}

void AProjectPCharacter::BeginPlay()
{
	Super::BeginPlay();

}

void AProjectPCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	APPPlayerState* PPPlayerState = GetPlayerState<APPPlayerState>();
	if (PPPlayerState == nullptr)
	{
		return;
	}
	AbilitySystemComponent = PPPlayerState->GetAbilitySystemComponent();
	AbilitySystemComponent->InitAbilityActorInfo(PPPlayerState, this);
	for (TSubclassOf<UGameplayAbility> StartAbility : StartAbilities)
	{
		FGameplayAbilitySpec StartSpec(StartAbility);
		AbilitySystemComponent->GiveAbility(StartSpec);
	}
	FGameplayEffectContextHandle EffectContextHandle = AbilitySystemComponent->MakeEffectContext();
	EffectContextHandle.AddSourceObject(this);
	FGameplayEffectSpecHandle EffectSpecHandle = AbilitySystemComponent->MakeOutgoingSpec(InitStatEffect, Level, EffectContextHandle);
	if (EffectSpecHandle.IsValid())
	{
		AbilitySystemComponent->BP_ApplyGameplayEffectSpecToSelf(EffectSpecHandle);
	}
}

void AProjectPCharacter::AddMovementInput(FVector WorldDirection, float ScaleValue, bool bForce)
{
	if(AbilitySystemComponent == nullptr)
	{
		return;
	}
	float MoveSpeed = ScaleValue;
	const UPPCharacterAttributeSet* AttributeSet = AbilitySystemComponent->GetSet<UPPCharacterAttributeSet>();
	if(AttributeSet == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("[AProjectPCharacter::AddMovementInput] AttributeSet is nullptr"));
	}
	else
	{
		MoveSpeed *= AttributeSet->GetMoveSpeed();
		UE_LOG(LogTemp, Log, TEXT("CurrentMoveSpeed : %f"), MoveSpeed);
	}
	Super::AddMovementInput(WorldDirection, MoveSpeed, bForce);
}


