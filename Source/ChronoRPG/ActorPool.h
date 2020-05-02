// Copyright 2020. All rights reserved. A game prototype by CodingRook.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ActorPool.generated.h"


UCLASS( ClassGroup=(Custom), Blueprintable, meta=(BlueprintSpawnableComponent) )
class CHRONORPG_API UActorPool : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UActorPool();

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable, Category = "Actor Pools")
	AActor* CheckOut();

	UFUNCTION(BlueprintCallable, Category = "Actor Pools")
	void CheckIn(AActor* ActorToCheckIn);

	//void Add(AActor* ActorToAdd); // To consider whether I need both "Add" and "CheckIn"

	UFUNCTION(BlueprintCallable, Category = "Actor Pools")
	int PoolSize() const { return Pool.Num(); }

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:
	TArray<AActor*> Pool;

		
};
