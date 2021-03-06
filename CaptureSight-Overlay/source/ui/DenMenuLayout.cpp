#include <tesla.hpp>
#include <csight/core>
#include <ui/DenMenuLayout.hpp>
#include <ui/RaidSearchLayout.hpp>

DenMenuLayout::DenMenuLayout(std::vector<std::shared_ptr<csight::raid::Den>> dens, std::string title) {
  this->dens = dens;
  this->title = title;
}

tsl::Element* DenMenuLayout::createUI() {
  auto rootFrame = new tsl::element::Frame();
  auto denList = new tsl::element::List();
  auto titleBlock = new tsl::element::CustomDrawer(
      100, FB_WIDTH, 200, FB_WIDTH,
      std::bind(&DenMenuLayout::AddTitleBlock, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));

  for (u32 i = 0; i < this->dens.size(); i++) {
    auto den = this->dens[i];
    std::string shineTypeText = den->GetShineType() == csight::shiny::Square ? " ■ " : " ★ ";
    auto speciesText = den->GetPKM()->GetSpeciesString();
    auto title = "Id: " + std::to_string(den->GetDenId()) + shineTypeText + std::to_string(den->GetShinyFrame()) + " " + speciesText;
    auto listItem = new tsl::element::ListItem(title);
    listItem->setClickListener(std::bind(&DenMenuLayout::OnClickDen, this, den, std::placeholders::_1));
    denList->addItem(listItem);
  }

  rootFrame->addElement(titleBlock);
  rootFrame->addElement(denList);

  return rootFrame;
}

void DenMenuLayout::AddTitleBlock(u16 x, u16 y, tsl::Screen* screen) {
  screen->drawString(this->title.c_str(), false, 20, 100, 20, tsl::a(0xFFFF));
}

bool DenMenuLayout::OnClickDen(std::shared_ptr<csight::raid::Den> den, s64 keys) {
  if (keys == KEY_A) {
    this->changeTo(new RaidSearchLayout(den->GetSeed(), 5));

    return true;
  }

  return false;
}
