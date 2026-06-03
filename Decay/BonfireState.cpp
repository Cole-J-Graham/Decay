#include "BonfireState.h"
#include "ShopState.h"

#include <algorithm>
#include <iostream>
#include <memory>

// Constructors and Destructors
BonfireState::BonfireState(sf::RenderWindow* window, std::stack<State*>* states, const std::string& areaId)
    : State(window, states)
    , areaId(areaId)
{
    this->initUi();
}

// State Functions
void BonfireState::endState()
{
    std::cout << "Leaving BonfireState!~" << "\n";
}

void BonfireState::updateKeybinds()
{
    this->checkForQuit();
}

void BonfireState::update()
{
    this->checkForQuit();
    this->updateMousePositions();
    this->updateKeybinds();

    this->ui.update(this->getMousePosView());

    if (this->ui.button("REST_PARTY").isPressed()) {
        this->restParty();
    }

    if (this->ui.button("SMITH_WEAPON").isPressed()) {
        this->smithWeapon();
    }

    if (this->ui.button("VISIT_SHOP").isPressed()) {
        this->visitShop();
    }

    if (this->ui.button("LEAVE_BONFIRE").isPressed()) {
        this->leaveBonfire();
    }
}

void BonfireState::render(sf::RenderTarget* target)
{
    if (target == nullptr) {
        return;
    }

    if (this->hasBonfireImage) {
        target->draw(this->bonfireSprite);
    }

    this->ui.render(*target);
    this->renderPartyPreview(target);
}

// UI Functions
void BonfireState::initUi()
{
    const bool atCastle = (this->areaId == "castle");
    // ── Colour palette ───────────────────────────────────────────────
    const sf::Color panelBorder(255, 255, 255, 60);
    const sf::Color transparent(sf::Color::Transparent);

    // Buttons: warm ember tones for idle, bright for hover
    const sf::Color btnIdle(90, 55, 30, 160);
    const sf::Color btnHover(200, 130, 60, 255);
    const sf::Color btnActive(50, 28, 10, 200);

    // Danger / leave button
    const sf::Color btnDangerIdle(90, 30, 30, 160);
    const sf::Color btnDangerHover(200, 60, 60, 255);
    const sf::Color btnDangerActive(50, 10, 10, 200);

    // ── Left panel – party preview ───────────────────────────────────
    this->ui.addRectangle("PARTY_PREVIEW_PANEL", std::make_unique<Rectangle>(
        25, 50, 240, 750, transparent, panelBorder, 1.f, false));

    // Header divider
    this->ui.addRectangle("PARTY_HEADER_DIV", std::make_unique<Rectangle>(
        25, 82, 240, 1, sf::Color(255, 255, 255, 40), transparent, 0.f, false));

    this->ui.addText("PARTY_PREVIEW_TITLE", std::make_unique<Text>(
        38, 57, 13, "PARTY", sf::Color(200, 200, 200, 220), false));

    // ── Centre panel – main view ─────────────────────────────────────
    this->ui.addRectangle("MAIN_PANEL", std::make_unique<Rectangle>(
        360, 5, 950, 800, transparent, panelBorder, 1.f, false));

    this->ui.addText("TITLE", std::make_unique<Text>(
        378, 18, 28, "Bonfire", sf::Color(255, 200, 100, 255), false));

    // Thin gold line under the title
    this->ui.addRectangle("TITLE_DIV", std::make_unique<Rectangle>(
        360, 56, 950, 1, sf::Color(255, 200, 100, 60), transparent, 0.f, false));

    // ── Bonfire image – centre panel ─────────────────────────────────
    {
        const std::string imagePath = "Assets/Wallpapers/Bonfires/" + this->areaId + ".jpeg";
        const float imgX = 360.f;
        const float imgY = 60.f;
        const float imgW = 950.f;
        const float imgH = 750.f;

        if (!this->areaId.empty() && this->bonfireTexture.loadFromFile(imagePath)) {
            // Loaded fine — build a raw sprite and draw it via a UiSprite workaround.
            // We own the texture on BonfireState so it stays alive.
            sf::Sprite bonfireSprite(this->bonfireTexture);

            // Scale to fill the centre panel box
            const sf::FloatRect bounds = bonfireSprite.getLocalBounds();
            if (bounds.width > 0.f && bounds.height > 0.f) {
                const float scaleX = imgW / bounds.width;
                const float scaleY = imgH / bounds.height;
                const float scale = std::min(scaleX, scaleY);
                bonfireSprite.setScale(scale, scale);
                const float cx = imgX + (imgW - bounds.width * scale) / 2.f;
                const float cy = imgY + (imgH - bounds.height * scale) / 2.f;
                bonfireSprite.setPosition(cx, cy);
            }

            this->bonfireSprite = bonfireSprite;
            this->hasBonfireImage = true;
        }
        else {
            if (!this->areaId.empty()) {
                std::cerr << "BonfireState: could not load bonfire image: " << imagePath << "\n";
            }
            this->hasBonfireImage = false;
        }
    }

    // ── Message panel ────────────────────────────────────────────────
    this->ui.addRectangle("MESSAGE_PANEL", std::make_unique<Rectangle>(
        360, 820, 950, 180, transparent, panelBorder, 1.f, false));

    // Subtle label above the message text
    this->ui.addText("MESSAGE_LABEL", std::make_unique<Text>(
        378, 828, 11, "LOG", sf::Color(180, 180, 180, 160), false));

    this->ui.addRectangle("MESSAGE_LABEL_DIV", std::make_unique<Rectangle>(
        360, 844, 950, 1, sf::Color(255, 255, 255, 25), transparent, 0.f, false));

    this->ui.addText("MESSAGE", std::make_unique<Text>(
        378, 852, 15, "The bonfire waits quietly.", sf::Color(220, 200, 170, 255), false));

    // ── Right panel – actions ────────────────────────────────────────
    this->ui.addRectangle("ACTION_PANEL", std::make_unique<Rectangle>(
        1320, 50, 290, 260, transparent, panelBorder, 1.f, false));

    this->ui.addText("ACTION_TITLE", std::make_unique<Text>(
        1335, 58, 13, "ACTIONS", sf::Color(200, 200, 200, 220), false));

    this->ui.addRectangle("ACTION_HEADER_DIV", std::make_unique<Rectangle>(
        1320, 80, 290, 1, sf::Color(255, 255, 255, 40), transparent, 0.f, false));

    // Buttons – full width of the panel, evenly spaced, taller (30px)
    const float btnX = 1335.f;
    const float btnW = 260.f;
    const float btnH = 30.f;
    const float btnGap = 12.f;
    float btnY = 92.f;

    this->ui.addButton("REST_PARTY", std::make_unique<Button>(
        btnX, btnY, btnW, btnH, 0.5f, "Rest Party",
        btnIdle, btnHover, btnActive, false));

    btnY += btnH + btnGap;
    this->ui.addButton("SMITH_WEAPON", std::make_unique<Button>(
        btnX, btnY, btnW, btnH, 0.5f, "Smith Weapon",
        btnIdle, btnHover, btnActive, false));

    btnY += btnH + btnGap;
    // Label reads "Investigate Noises" on first castle visit, "Visit Doctor" after.
    // The intro event itself lives in ShopState — BonfireState only needs the flag.
    const std::string shopButtonLabel = (atCastle && !GameFlags::getInstance().has("doctor_intro_played"))
        ? "Investigate Noises"
        : "Visit Doctor";
    this->ui.addButton("VISIT_SHOP", std::make_unique<Button>(
        btnX, btnY, btnW, btnH, 0.5f, shopButtonLabel,
        btnIdle, btnHover, btnActive, !atCastle));  // hidden = !atCastle

    btnY += btnH + btnGap;
    this->ui.addButton("LEAVE_BONFIRE", std::make_unique<Button>(
        btnX, btnY, btnW, btnH, 0.5f, "Leave Bonfire",
        btnDangerIdle, btnDangerHover, btnDangerActive, false));
}

void BonfireState::renderPartyPreview(sf::RenderTarget* target)
{
    if (target == nullptr) {
        return;
    }

    auto& partyMembers = CharacterManager::getInstance().getAllPartyMembers();

    const float panelX = 25.f;
    const float panelY = 50.f;
    const float panelW = 240.f;

    const float slotX = panelX + 12.f;
    const float slotY = panelY + 40.f;   // below the "PARTY" header bar
    const float slotW = panelW - 24.f;
    const float slotH = 212.f;
    const float slotGap = 14.f;

    for (int i = 0; i < static_cast<int>(partyMembers.size()); i++) {
        if (!partyMembers[i]) continue;

        const float sy = slotY + i * (slotH + slotGap);

        // Subtle filled background for the slot
        sf::RectangleShape slotBg(sf::Vector2f(slotW, slotH));
        slotBg.setPosition(slotX, sy);
        slotBg.setFillColor(sf::Color(255, 255, 255, 10));
        target->draw(slotBg);

        // Slot border
        Rectangle slotBorder(slotX, sy, slotW, slotH,
            sf::Color::Transparent, sf::Color(255, 255, 255, 60), 1.f, false);
        slotBorder.render(target);

        // Thin accent bar at the top of each slot (warm ember colour)
        sf::RectangleShape accent(sf::Vector2f(slotW, 3.f));
        accent.setPosition(slotX, sy);
        accent.setFillColor(sf::Color(220, 140, 60, 180));
        target->draw(accent);

        // Character preview (name, sprite, stats) rendered by the character itself
        partyMembers[i]->renderPreview(target, slotX + 12.f, sy + 12.f);
    }
}

// Bonfire Functions
void BonfireState::restParty()
{
    CharacterManager::getInstance().restParty();

    this->ui.text("MESSAGE").setString("The party rests at the bonfire. HP restored.");
    std::cout << "Party rested at bonfire." << "\n";
}

void BonfireState::smithWeapon()
{
    // Temporary message until InventoryManager / smithing stones exist.
    this->ui.text("MESSAGE").setString("Smithing is not wired yet.");
    std::cout << "Smith weapon selected." << "\n";
}

void BonfireState::leaveBonfire()
{
    this->endState();

    if (!this->states->empty()) {
        this->states->pop();
    }
}

void BonfireState::visitShop()
{
    this->states->push(new ShopState(this->window, this->states));
}