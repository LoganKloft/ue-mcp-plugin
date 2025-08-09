// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "Framework/Commands/Commands.h"
#include "ModelContextProtocolStyle.h"

class FModelContextProtocolCommands : public TCommands<FModelContextProtocolCommands>
{
public:

	FModelContextProtocolCommands()
		: TCommands<FModelContextProtocolCommands>(TEXT("ModelContextProtocol"), NSLOCTEXT("Contexts", "ModelContextProtocol", "ModelContextProtocol Plugin"), NAME_None, FModelContextProtocolStyle::GetStyleSetName())
	{
	}

	// TCommands<> interface
	virtual void RegisterCommands() override;

public:
	TSharedPtr< FUICommandInfo > PluginAction;
};
