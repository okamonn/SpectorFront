﻿// Fill out your copyright notice in the Description page of Project Settings.

#include "SpecterFront.h"
#include "BaseEnemy.h"
#include "ActionPhaseController.h"
#include "EnemySpawner.h"
#include "EnemySpawnController.h"


void AEnemySpawner::BeginSpawn(AActionPhaseController* spawnController)
{
	if (spawnEnemyType == nullptr)
		return;

	if (spawnController == nullptr)
		return;

	this->spawnController = spawnController;
	
	isSpawing = true;
	OnBeginSpawn();
}

void AEnemySpawner::FinishSpawn()
{
	if (spawnController == nullptr)
	{
		return;
	}

	spawnController->OnFinishSpawn();

	// 全ての敵の通知先から自身を削除
	for (auto enemy : spawnedEnemies)
	{
		enemy->RemoveObserver(this);
	}

	spawnController->AppendSpawnEnemies(spawnedEnemies);

	isSpawing = false;

	// 自分自身を破棄
	Destroy();
}

void AEnemySpawner::OnEnemyDie_Implementation(ABaseEnemy* enemy)
{
	spawnedEnemies.Remove(enemy);
}

void AEnemySpawner::EnemySpawnRelative(const FVector & relativeLocation)
{
	EnemySpawn(GetActorLocation() + relativeLocation);
}

void AEnemySpawner::EnemySpawn(const FVector & location)
{
	FRotator rotation = GetActorRotation();

	FActorSpawnParameters p;
	p.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	ABaseEnemy* enemy = Cast<ABaseEnemy>(GetWorld()->SpawnActor(spawnEnemyType, &location, &rotation, p));

	if (enemy == nullptr)
	{
		return;
	}

	enemy->SpawnDefaultController();

	FScriptDelegate enemyDieHandler;
	enemyDieHandler.BindUFunction(this, "OnEnemyDie");
	enemy->AddObserver(enemyDieHandler);
	spawnedEnemies.Add(enemy);
}

int32 AEnemySpawner::GetSpawnedEnemyCount()
{
	return spawnedEnemies.Num();
}

void AEnemySpawner::OnBeginSpawn_Implementation()
{
	EnemySpawnRelative(FVector(0.0f, 0.0f, 0.0f));
}
