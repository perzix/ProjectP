// Fill out your copyright notice in the Description page of Project Settings.


#include "PPPlayerState.h"
#include "AbilitySystemComponent.h"
APPPlayerState::APPPlayerState()
{
	AbilitySystemComponent = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	//AbilitySystemComponent->SetIsReplicated(true);
}

UAbilitySystemComponent* APPPlayerState::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}
