// HydroSchemes Simulator. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Inventory/InventoryElement.h"
#include "InventoryInteractInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UInventoryInteractInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class HYDROSCHEMES_API IInventoryInteractInterface
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void AddToUIInventory(FInventoryElement InventoryElement);
};
