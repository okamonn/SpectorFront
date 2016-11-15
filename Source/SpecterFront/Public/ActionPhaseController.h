// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "EnemySpawner.h"
#include "ActionPhaseController.generated.h"

UCLASS()
class SPECTERFRONT_API AActionPhaseController : public AEnemySpawner
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AActionPhaseController();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaSeconds) override;

public: // UFUNCTION
	// アクションフェーズ終了時に呼び出す
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "EnemySpawn")
		void Finish();

public: // UPROPERTY

};
