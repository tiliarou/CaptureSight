#include <string>
#include <stratosphere.hpp>
#include <csight/core>
#include <ui/PokemonSprite.hpp>
#include <ui/PokemonSummaryLayout.hpp>
#include <csight/core>
#include <utils/Settings.hpp>
#include <utils/I18N.hpp>

extern Settings gsets;
extern std::shared_ptr<I18N> i18n;

PokemonSummaryLayout::PokemonSummaryLayout() : Layout::Layout() {
  std::string instructions = i18n->Translate("More detail (X), Go back (B)\nRaid Searcher (Y)");
  this->instructionsTextBlock = pu::ui::elm::TextBlock::New(700, 620, instructions, 25);
  this->instructionsTextBlock->SetColor(gsets.GetTheme().text.light);
  this->spriteImage = pu::ui::elm::Image::New(0, 0, "");
  this->speciesBackgroundRectangle = pu::ui::elm::Rectangle::New(0, 0, 1280, 274, gsets.GetTheme().background.light, 50);
  this->titleTextBlock = pu::ui::elm::TextBlock::New(700, 55, "", 50);
  this->titleTextBlock->SetColor(gsets.GetTheme().text.light);
  this->speciesNameTextBlock = pu::ui::elm::TextBlock::New(300, 55, "", 40);
  this->speciesNameTextBlock->SetColor(gsets.GetTheme().text.light);
  this->ivTextBlock = pu::ui::elm::TextBlock::New(300, 150, "", 25);
  this->ivTextBlock->SetColor(gsets.GetTheme().text.light);
  this->evTextBlock = pu::ui::elm::TextBlock::New(300, 200, "", 25);
  this->evTextBlock->SetColor(gsets.GetTheme().text.light);
  this->shinyInfoTextBlock = pu::ui::elm::TextBlock::New(100, 420, "", 25);
  this->shinyInfoTextBlock->SetColor(gsets.GetTheme().text.light);
  this->moveTextBlock = pu::ui::elm::TextBlock::New(100, 470, "", 25);
  this->moveTextBlock->SetColor(gsets.GetTheme().text.light);
  this->natureTextBlock = pu::ui::elm::TextBlock::New(100, 520, "", 25);
  this->natureTextBlock->SetColor(gsets.GetTheme().text.light);
  this->mintedNatureTextBlock = pu::ui::elm::TextBlock::New(100, 570, "", 25);
  this->mintedNatureTextBlock->SetColor(gsets.GetTheme().text.light);
  this->abilityTextBlock = pu::ui::elm::TextBlock::New(100, 620, "", 25);
  this->abilityTextBlock->SetColor(gsets.GetTheme().text.light);
  this->pidEcTextBlock = pu::ui::elm::TextBlock::New(700, 420, "", 25);
  this->pidEcTextBlock->SetColor(gsets.GetTheme().text.light);
  this->friendshipTextBlock = pu::ui::elm::TextBlock::New(700, 520, "", 25);
  this->friendshipTextBlock->SetColor(gsets.GetTheme().text.light);

  this->Add(this->instructionsTextBlock);
  this->Add(this->speciesBackgroundRectangle);
  this->Add(this->spriteImage);
  this->Add(this->speciesNameTextBlock);
  this->Add(this->ivTextBlock);
  this->Add(this->evTextBlock);
  this->Add(this->titleTextBlock);
  this->Add(this->shinyInfoTextBlock);
  this->Add(this->moveTextBlock);
  this->Add(this->natureTextBlock);
  this->Add(this->mintedNatureTextBlock);
  this->Add(this->abilityTextBlock);
  this->Add(this->friendshipTextBlock);
  this->Add(this->pidEcTextBlock);
}

void PokemonSummaryLayout::UpdateValues(std::string title, std::shared_ptr<csight::PK8> pkm, bool isShowingExtraDetail) {
  std::string moves = i18n->Translate("moves", pkm->GetMoveString(0));
  std::string species = i18n->Translate("species", pkm->GetSpeciesString());
  std::string nature = i18n->Translate("Nature") + ": " + i18n->Translate("natures", pkm->GetNatureString());
  std::string mintedNature = i18n->Translate("Minted Nature") + ": " + i18n->Translate("natures", pkm->GetMintedNatureString());
  std::string ability = i18n->Translate("Ability") + ": " + i18n->Translate("abilities", pkm->GetAbilityString());
  std::string shinyTranslationKey = pkm->GetIsShiny() ? "Shiny" : "Not Shiny";
  std::string formattedIVs = i18n->Translate("IVs") + ": " + csight::utils::joinNums(pkm->GetIVs(), "/");
  std::string formattedEVs = i18n->Translate("EVs") + ": " + csight::utils::joinNums(pkm->GetEVs(), "/");
  std::string shiny = i18n->Translate("PSV") + " " + std::to_string(pkm->GetPSV()) + ", " + i18n->Translate("TSV") + " " +
                      std::to_string(pkm->GetTSV()) + ", " + i18n->Translate(shinyTranslationKey);
  std::string pidEc = i18n->Translate("PID") + ": " + csight::utils::convertNumToHexString(pkm->GetPID()) + ", " + i18n->Translate("EC") + ": " +
                      csight::utils::convertNumToHexString(pkm->GetEncryptionConstant());
  std::string friendshipTranslationKey = pkm->GetIsEgg() ? "Egg cycles" : "Friendship";
  std::string friendship = i18n->Translate(friendshipTranslationKey) + ": " + std::to_string(pkm->GetCurrentFriendship());

  for (u8 i = 1; i < 4; i++) {
    moves += ", " + i18n->Translate("moves", pkm->GetMoveString(i));
  }

  setPokemonSprite(this->spriteImage, 4, pkm->GetSpecies(), pkm->GetIsEgg());
  this->speciesNameTextBlock->SetText(species);
  this->ivTextBlock->SetText(formattedIVs);
  this->evTextBlock->SetText(formattedEVs);
  this->titleTextBlock->SetText(title);
  this->shinyInfoTextBlock->SetText(shiny);
  this->moveTextBlock->SetText(moves);
  this->natureTextBlock->SetText(nature);
  this->mintedNatureTextBlock->SetText(mintedNature);
  this->abilityTextBlock->SetText(ability);
  this->friendshipTextBlock->SetText(friendship);
  this->pidEcTextBlock->SetText(isShowingExtraDetail ? pidEc : "");
}