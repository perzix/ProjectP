#pragma once

#include "CoreMinimal.h"
#include "FNPCData.generated.h"

class UBehaviorTree;
class UGameplayEffect;

USTRUCT(BlueprintType)
struct PROJECTP_API FNPCData : public FTableRowBase
{
	GENERATED_BODY()


	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FText Name;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSoftClassPtr<class UGameplayEffect> InitStatEffect;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSoftObjectPtr<USkeletalMesh> SkeletalMesh;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSoftObjectPtr<UBehaviorTree> BehaviorTree;
};
