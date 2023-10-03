// Fill out your copyright notice in the Description page of Project Settings.


#include "ShootToKillProjectile.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/SphereComponent.h"
#include "ShootToKillPlayerCharacter.h"
#include "ShootToKillEnemyRiflemenCharacter.h"

// Sets default values
AShootToKillProjectile::AShootToKillProjectile()
{
    // Creates sphere for the projectile. NOTE: change this later.
    CollisionComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
    CollisionComp->InitSphereRadius(5.0f);
    CollisionComp->BodyInstance.SetCollisionProfileName("Projectile");
    CollisionComp->OnComponentHit.AddDynamic(this, &AShootToKillProjectile::OnHit);

    // Players can't walk on it
    CollisionComp->SetWalkableSlopeOverride(FWalkableSlopeOverride(WalkableSlope_Unwalkable, 0.f));
    CollisionComp->CanCharacterStepUpOn = ECB_No;

    // Creates root component
    RootComponent = CollisionComp;

    // Uses ProjectileMovementComponent to govern this projectile's movement
    ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileComp"));
    ProjectileMovement->UpdatedComponent = CollisionComp;
    ProjectileMovement->InitialSpeed = 6000.f;
    ProjectileMovement->MaxSpeed = 6000.f;
    ProjectileMovement->bRotationFollowsVelocity = true;
    ProjectileMovement->bShouldBounce = true;

    // Creates a life span of 3 seconds
    InitialLifeSpan = 3.0f;
}

void AShootToKillProjectile::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
    AShootToKillEnemyRiflemenCharacter* EnemyCharacter = Cast<AShootToKillEnemyRiflemenCharacter>(OtherActor);
    AShootToKillPlayerCharacter* PlayerCharacter = Cast<AShootToKillPlayerCharacter>(OtherActor);

    if (OtherActor == EnemyCharacter)
    {
        EnemyCharacter->Hitpoints = EnemyCharacter->Hitpoints - 20;

        Destroy();

        if (EnemyCharacter->Hitpoints <= 0)
        {
            EnemyCharacter->Destroy();
        }
    }
    else if(OtherActor == PlayerCharacter)
    {
        PlayerCharacter->Hitpoints = PlayerCharacter->Hitpoints - 20;

        Destroy();

        if (PlayerCharacter->Hitpoints <= 0)
        {
            PlayerCharacter->OnDeathTimerFinished();
        }
    }
    else if ((OtherActor != nullptr) && (OtherActor != this) && (OtherComp != nullptr) && OtherComp->IsSimulatingPhysics())
    {
        OtherComp->AddImpulseAtLocation(GetVelocity() * 100.0f, GetActorLocation());

        Destroy();
    }
}

