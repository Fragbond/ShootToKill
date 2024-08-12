// Fill out your copyright notice in the Description page of Project Settings.


#include "ShootToKillProjectile.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/SphereComponent.h"
#include "ShootToKillPlayerCharacter.h"
#include "ShootToKillEnemyRiflemenCharacter.h"
#include "STKSquadLeaderCharacter.h"

// Sets default values
AShootToKillProjectile::AShootToKillProjectile()
{
    // Creates sphere for the projectile.
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
}

void AShootToKillProjectile::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
   AShootToKillEnemyRiflemenCharacter* EnemyCharacter = Cast<AShootToKillEnemyRiflemenCharacter>(OtherActor);
   AShootToKillPlayerCharacter* PlayerCharacter = Cast<AShootToKillPlayerCharacter>(OtherActor);
   ASTKSquadLeaderCharacter* SquadLeaderCharacter = Cast<ASTKSquadLeaderCharacter>(OtherActor);

   if (OtherActor == EnemyCharacter)
   {
       EnemyCharacter->Hitpoints = EnemyCharacter->Hitpoints - 25;

       Destroy();

       if (EnemyCharacter->Hitpoints <= 0)
       {
           EnemyCharacter->IsDead = true;
       }
   }
   else if (OtherActor == SquadLeaderCharacter)
   {
       SquadLeaderCharacter->Hitpoints = SquadLeaderCharacter->Hitpoints - 25;

       Destroy();

       if (SquadLeaderCharacter->Hitpoints <= 0)
       {
           SquadLeaderCharacter->IsDead = true;
       }
   }
   else if(OtherActor == PlayerCharacter)
   {
    
        PlayerCharacter->Hitpoints = PlayerCharacter->Hitpoints - 25;

        Destroy();

        if (PlayerCharacter->Hitpoints <= 0)
        {
            PlayerCharacter->OnDeathTimerFinished();
        }
   }
    else if ((OtherActor != nullptr))
    {
        Destroy();
    }
}

