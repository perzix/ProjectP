// Fill out your copyright notice in the Description page of Project Settings.


#include "PPPlayerState.h"
#include "AbilitySystemComponent.h"
#include "Attribute/PPCharacterAttributeSet.h"

APPPlayerState::APPPlayerState()
{
	AbilitySystemComponent = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	AttributeSet = CreateDefaultSubobject<UPPCharacterAttributeSet>(TEXT("AttributeSet"));
	//AbilitySystemComponent->SetIsReplicated(true);
}

UAbilitySystemComponent* APPPlayerState::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}
