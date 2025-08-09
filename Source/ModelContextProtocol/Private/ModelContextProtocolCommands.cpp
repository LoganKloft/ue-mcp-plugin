// Copyright Epic Games, Inc. All Rights Reserved.

#include "ModelContextProtocolCommands.h"

#define LOCTEXT_NAMESPACE "FModelContextProtocolModule"

void FModelContextProtocolCommands::RegisterCommands()
{
	UI_COMMAND(PluginAction, "ModelContextProtocol", "Execute ModelContextProtocol action", EUserInterfaceActionType::Button, FInputChord());
}

#undef LOCTEXT_NAMESPACE
