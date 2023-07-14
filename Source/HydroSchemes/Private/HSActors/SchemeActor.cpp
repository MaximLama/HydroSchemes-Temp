// HydroSchemes Simulator. All rights reserved.


#include "HSActors/SchemeActor.h"
#include "Inventory/InventoryElement.h"

DEFINE_LOG_CATEGORY_STATIC(LogSchemeActor, All, All)

// Sets default values
ASchemeActor::ASchemeActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	SceneComponent = CreateDefaultSubobject<USceneComponent>("SceneComponent");
	RootComponent = SceneComponent;
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("StaticMeshComponent");
	StaticMeshComponent->SetupAttachment(RootComponent);
}

void ASchemeActor::PickUpItem(FInventoryElement& InventoryElement)
{
	UE_LOG(LogSchemeActor, Display, TEXT("ClassName - %s"), *ActorName.ToString());
	InventoryElement.ElementClass = GetClass();
	InventoryElement.ElementName = ActorName;
	Destroy();
}

// Called when the game starts or when spawned
void ASchemeActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASchemeActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

