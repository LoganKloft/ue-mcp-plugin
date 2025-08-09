// Copyright Epic Games, Inc. All Rights Reserved.

#include "ModelContextProtocol.h"
#include "ModelContextProtocolStyle.h"
#include "ModelContextProtocolCommands.h"
#include "Misc/MessageDialog.h"
#include "ToolMenus.h"

static const FName ModelContextProtocolTabName("ModelContextProtocol");

#define LOCTEXT_NAMESPACE "FModelContextProtocolModule"

void FModelContextProtocolModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
	
	FModelContextProtocolStyle::Initialize();
	FModelContextProtocolStyle::ReloadTextures();

	FModelContextProtocolCommands::Register();
	
	PluginCommands = MakeShareable(new FUICommandList);

	PluginCommands->MapAction(
		FModelContextProtocolCommands::Get().PluginAction,
		FExecuteAction::CreateRaw(this, &FModelContextProtocolModule::PluginButtonClicked),
		FCanExecuteAction());

	UToolMenus::RegisterStartupCallback(FSimpleMulticastDelegate::FDelegate::CreateRaw(this, &FModelContextProtocolModule::RegisterMenus));
}

void FModelContextProtocolModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.

	UToolMenus::UnRegisterStartupCallback(this);

	UToolMenus::UnregisterOwner(this);

	FModelContextProtocolStyle::Shutdown();

	FModelContextProtocolCommands::Unregister();
}

void FModelContextProtocolModule::PluginButtonClicked()
{
	// Put your "OnButtonClicked" stuff here
	FText DialogText = FText::Format(
							LOCTEXT("PluginButtonDialogText", "Add code to {0} in {1} to override this button's actions"),
							FText::FromString(TEXT("FModelContextProtocolModule::PluginButtonClicked()")),
							FText::FromString(TEXT("ModelContextProtocol.cpp"))
					   );
	FMessageDialog::Open(EAppMsgType::Ok, DialogText);
}

void FModelContextProtocolModule::RegisterMenus()
{
	// Owner will be used for cleanup in call to UToolMenus::UnregisterOwner
	FToolMenuOwnerScoped OwnerScoped(this);

	{
		UToolMenu* Menu = UToolMenus::Get()->ExtendMenu("LevelEditor.MainMenu.Window");
		{
			FToolMenuSection& Section = Menu->FindOrAddSection("WindowLayout");
			Section.AddMenuEntryWithCommandList(FModelContextProtocolCommands::Get().PluginAction, PluginCommands);
		}
	}

	{
		UToolMenu* ToolbarMenu = UToolMenus::Get()->ExtendMenu("LevelEditor.LevelEditorToolBar.PlayToolBar");
		{
			FToolMenuSection& Section = ToolbarMenu->FindOrAddSection("PluginTools");
			{
				FToolMenuEntry& Entry = Section.AddEntry(FToolMenuEntry::InitToolBarButton(FModelContextProtocolCommands::Get().PluginAction));
				Entry.SetCommandList(PluginCommands);
			}
		}
	}
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FModelContextProtocolModule, ModelContextProtocol)