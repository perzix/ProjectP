// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/PPNonPlayerCharacter.h"

#include "AbilitySystemComponent.h"
#include "GameplayEffectTypes.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
APPNonPlayerCharacter::APPNonPlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
}

UAbilitySystemComponent* APPNonPlayerCharacter::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

// Called when the game starts or when spawned
void APPNonPlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APPNonPlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APPNonPlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void APPNonPlayerCharacter::SetDead()
{
	//IsDead Tag 설정해줘야할듯?
	GetCharacterMovement()->SetMovementMode(MOVE_None);
	SetActorEnableCollision(false);
	FTimerHandle DeadTimerHandle;
	GetWorld()->GetTimerManager().SetTimer(DeadTimerHandle, FTimerDelegate::CreateLambda(
		[&]()
		{
			Destroy();
		}
	), 0.1f, false);
}

void APPNonPlayerCharacter::SetData(const FNPCData& InNPCData, int InLevel)
{
	if(InNPCData.SkeletalMesh.IsValid())
	{
		GetMesh()->SetSkeletalMesh(InNPCData.SkeletalMesh.Get());
	}
	if(InNPCData.InitStatEffect.IsValid())
	{
		FGameplayEffectContextHandle EffectContextHandle = AbilitySystemComponent->MakeEffectContext();
		EffectContextHandle.AddSourceObject(this);
		FGameplayEffectSpecHandle EffectSpecHandle = AbilitySystemComponent->MakeOutgoingSpec(InNPCData.InitStatEffect.Get(), InLevel, EffectContextHandle);
		if (EffectSpecHandle.IsValid())
		{
			AbilitySystemComponent->BP_ApplyGameplayEffectSpecToSelf(EffectSpecHandle);
		}
	}
	
}

