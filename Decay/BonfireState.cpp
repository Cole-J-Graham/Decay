#include "BonfireState.h"
#include "ShopState.h"
#include "CompanionConversationManager.h"

#include <algorithm>
#include <iostream>
#include <memory>

// ── Constants ─────────────────────────────────────────────────────────────

static constexpr float kMessageDuration = 3.f;

// Panel geometry — keep in sync with initUi()
static constexpr float kMainPanelX = 440.f;
static constexpr float kMainPanelW = 950.f;
static constexpr float kMainPanelY = 60.f;   // below title bar
static constexpr float kMainPanelH = 750.f;

// ── Constructors ──────────────────────────────────────────────────────────

BonfireState::BonfireState(sf::RenderWindow* window, std::stack<State*>* states,
    const std::string& areaId, MusicPlayer* musicPlayer)
    : State(window, states)
    , areaId(areaId)
    , musicPlayer(musicPlayer)
{
    this->initUi();
    CompanionConversationManager::getInstance().onBonfireEntered();
}

// ── State Functions ───────────────────────────────────────────────────────

void BonfireState::endState()
{
    std::cout << "Leaving BonfireState!~\n";
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

    // Timed message reset
    if (messageTimerActive)
    {
        if (messageClock.getElapsedTime().asSeconds() >= messageDisplayTime)
        {
            this->ui.text("MESSAGE").setString("The bonfire waits quietly.");
            messageTimerActive = false;
        }
    }

    // Conversation active — lock all other controls
    if (isConversationActive())
    {
        updateConversation(this->getMousePosView());
        return;
    }

    this->ui.update(this->getMousePosView());

    if (this->ui.button("REST_PARTY").isPressed())    this->restParty();
    if (this->ui.button("SMITH_WEAPON").isPressed())  this->smithWeapon();
    if (this->ui.button("VISIT_SHOP").isPressed())    this->visitShop();
    if (this->ui.button("LEAVE_BONFIRE").isPressed()) this->leaveBonfire();

    this->updatePartyPreview(this->getMousePosView());
}

void BonfireState::render(sf::RenderTarget* target)
{
    if (target == nullptr) return;

    if (this->hasBonfireImage)
        target->draw(this->bonfireSprite);

    this->ui.render(*target);
    this->renderPartyPreview(target);

    if (isConversationActive())
        renderConversation(target);
}

// ── Slot geometry ─────────────────────────────────────────────────────────

sf::FloatRect BonfireState::getPartySlotRect(int index) const
{
    const float y = kSlotStartY + index * (kSlotH + kSlotGap);
    return sf::FloatRect(kSlotX, y, kSlotW, kSlotH);
}

// ── Party preview ─────────────────────────────────────────────────────────

void BonfireState::updatePartyPreview(const sf::Vector2f& mousePos)
{
    if (!sf::Mouse::isButtonPressed(sf::Mouse::Left)) return;

    const auto& partyMembers = CharacterManager::getInstance().getAllPartyMembers();

    for (int i = 0; i < static_cast<int>(partyMembers.size()); ++i)
    {
        if (!partyMembers[i]) continue;

        if (getPartySlotRect(i).contains(mousePos))
        {
            const std::string& id = partyMembers[i]->getId();

            if (CompanionConversationManager::getInstance().hasPending(id))
            {
                const std::string path =
                    CompanionConversationManager::getInstance().popNext(id);
                if (!path.empty())
                {
                    startConversation(path);
                    return;
                }
            }

            // Nothing queued — timed message
            this->ui.text("MESSAGE").setString(
                "It looks like they don't feel like talking...");
            messageClock.restart();
            messageDisplayTime = kMessageDuration;
            messageTimerActive = true;
            return;
        }
    }
}

void BonfireState::renderPartyPreview(sf::RenderTarget* target)
{
    if (target == nullptr) return;

    const auto& partyMembers = CharacterManager::getInstance().getAllPartyMembers();
    static sf::Clock pulseClock;

    for (int i = 0; i < static_cast<int>(partyMembers.size()); i++)
    {
        if (!partyMembers[i]) continue;

        const sf::FloatRect rect = getPartySlotRect(i);
        const float sx = rect.left, sy = rect.top;
        const float sw = rect.width, sh = rect.height;

        sf::RectangleShape slotBg(sf::Vector2f(sw, sh));
        slotBg.setPosition(sx, sy);
        slotBg.setFillColor(sf::Color(255, 255, 255, 10));
        target->draw(slotBg);

        Rectangle slotBorder(sx, sy, sw, sh,
            sf::Color::Transparent, sf::Color(255, 255, 255, 60), 1.f, false);
        slotBorder.render(target);

        const std::string& id = partyMembers[i]->getId();
        const bool pending = CompanionConversationManager::getInstance().hasPending(id);

        sf::RectangleShape accent(sf::Vector2f(sw, 3.f));
        accent.setPosition(sx, sy);
        accent.setFillColor(pending
            ? sf::Color(255, 200, 60, 255)
            : sf::Color(220, 140, 60, 180));
        target->draw(accent);

        if (pending)
        {
            // Pulse: smooth sine wave between 0 and 1
            const float pulse = (std::sin(pulseClock.getElapsedTime().asSeconds() * 4.f) + 1.f) / 2.f;

            // Slot border glows bright gold when pending
            Rectangle slotBorder(sx, sy, sw, sh,
                sf::Color::Transparent,
                sf::Color(255, 200, 60, static_cast<sf::Uint8>(120 + 135 * pulse)),
                2.f, false);
            slotBorder.render(target);

            // Accent bar pulses between orange and bright gold
            sf::RectangleShape accent(sf::Vector2f(sw, 4.f));
            accent.setPosition(sx, sy);
            accent.setFillColor(sf::Color(255, static_cast<sf::Uint8>(160 + 40 * pulse), 60, 255));
            target->draw(accent);

            // Badge — pulses in size
            const float badgeSize = 14.f + 4.f * pulse;
            sf::RectangleShape badge(sf::Vector2f(badgeSize, badgeSize));
            badge.setPosition(sx + sw - badgeSize - 4.f, sy + 4.f);
            badge.setFillColor(sf::Color(255, 200, 60, 220));
            target->draw(badge);

            Text pendingText(sx + sw - badgeSize, sy + 4.f, 12, "!", sf::Color(20, 20, 20, 255), false);
            pendingText.render(target);

            // Hover tooltip — "Click to talk"
            const sf::FloatRect slotRect(sx, sy, sw, sh);
            // mousePos isn't in scope here, so pass it through or use a stored member
        }
        else
        {
            // Non-pending accent bar — dimmer, static
            sf::RectangleShape accent(sf::Vector2f(sw, 3.f));
            accent.setPosition(sx, sy);
            accent.setFillColor(sf::Color(220, 140, 60, 180));
            target->draw(accent);
        }

        partyMembers[i]->renderPreview(target, sx + 12.f, sy + 12.f);
    }
}

// ── Conversation ──────────────────────────────────────────────────────────

void BonfireState::startConversation(const std::string& filePath)
{
    const std::string prefix = "Assets/Events/";
    std::string areaName;

    if (filePath.rfind(prefix, 0) == 0)
    {
        const std::string relative = filePath.substr(prefix.size());
        const auto lastSlash = relative.rfind('/');
        areaName = (lastSlash != std::string::npos)
            ? relative.substr(0, lastSlash)
            : relative;
    }

    // Direct-file constructor — plays exactly this file, no directory scan
    activeConversation = std::make_unique<EventManager>(
        areaName, filePath, true /*directFile*/, "" /*completionTrigger*/, true /*suppressPortrait*/);

    messageTimerActive = false;
    this->ui.text("MESSAGE").setString("");

    std::cout << "BonfireState: starting companion conversation: " << filePath << "\n";
}

void BonfireState::updateConversation(const sf::Vector2f& mousePos)
{
    if (!activeConversation) return;

    activeConversation->update(mousePos);

    if (activeConversation->hasFinished())
    {
        activeConversation.reset();
        this->ui.text("MESSAGE").setString("The bonfire waits quietly.");
        std::cout << "BonfireState: companion conversation finished.\n";
    }
}

void BonfireState::renderConversation(sf::RenderTarget* target)
{
    if (!activeConversation) return;
    activeConversation->render(target);
}

bool BonfireState::isConversationActive() const
{
    return activeConversation != nullptr;
}

// ── UI Functions ──────────────────────────────────────────────────────────

void BonfireState::initUi()
{
    const bool atCastle = (this->areaId == "castle");

    const sf::Color panelBorder(255, 255, 255, 60);
    const sf::Color transparent(sf::Color::Transparent);

    const sf::Color btnIdle(90, 55, 30, 160);
    const sf::Color btnHover(200, 130, 60, 255);
    const sf::Color btnActive(50, 28, 10, 200);

    const sf::Color btnDangerIdle(90, 30, 30, 160);
    const sf::Color btnDangerHover(200, 60, 60, 255);
    const sf::Color btnDangerActive(50, 10, 10, 200);

    // ── Left panel – party preview ────────────────────────────────────
    this->ui.addRectangle("PARTY_PREVIEW_PANEL", std::make_unique<Rectangle>(
        105, 50, 240, 750, transparent, panelBorder, 1.f, false));
    this->ui.addRectangle("PARTY_HEADER_DIV", std::make_unique<Rectangle>(
        105, 82, 240, 1, sf::Color(255, 255, 255, 40), transparent, 0.f, false));
    this->ui.addText("PARTY_PREVIEW_TITLE", std::make_unique<Text>(
        118, 57, 13, "PARTY", sf::Color(200, 200, 200, 220), false));

    // ── Centre panel – main view ──────────────────────────────────────
    this->ui.addRectangle("MAIN_PANEL", std::make_unique<Rectangle>(
        kMainPanelX, 5, kMainPanelW, 800, transparent, panelBorder, 1.f, false));

    this->ui.addText("TITLE", std::make_unique<Text>(
        kMainPanelX + 18.f, 18, 28, "Bonfire", sf::Color(255, 200, 100, 255), false));

    this->ui.addRectangle("TITLE_DIV", std::make_unique<Rectangle>(
        kMainPanelX, 56, kMainPanelW, 1, sf::Color(255, 200, 100, 60), transparent, 0.f, false));

    // ── Bonfire image — properly centred inside the main panel ────────
    {
        const std::string imagePath = "Assets/Wallpapers/Bonfires/" + this->areaId + ".jpeg";

        if (!this->areaId.empty() && this->bonfireTexture.loadFromFile(imagePath))
        {
            sf::Sprite sprite(this->bonfireTexture);
            const sf::FloatRect bounds = sprite.getLocalBounds();

            if (bounds.width > 0.f && bounds.height > 0.f)
            {
                // Scale to fit inside the panel box while preserving aspect ratio
                const float scaleX = kMainPanelW / bounds.width;
                const float scaleY = kMainPanelH / bounds.height;
                const float scale = std::min(scaleX, scaleY);

                const float scaledW = bounds.width * scale;
                const float scaledH = bounds.height * scale;

                // Centre horizontally and vertically within the panel
                const float cx = kMainPanelX + (kMainPanelW - scaledW) / 2.f;
                const float cy = kMainPanelY + (kMainPanelH - scaledH) / 2.f;

                sprite.setScale(scale, scale);
                sprite.setPosition(cx, cy);
            }

            this->bonfireSprite = sprite;
            this->hasBonfireImage = true;
        }
        else
        {
            if (!this->areaId.empty())
                std::cerr << "BonfireState: could not load bonfire image: " << imagePath << "\n";
            this->hasBonfireImage = false;
        }
    }

    // ── Message panel — spans the full width of the main panel ───────
    // x=360, w=950, y=820, h=180
    this->ui.addRectangle("MESSAGE_PANEL", std::make_unique<Rectangle>(
        kMainPanelX, 820, kMainPanelW, 180, transparent, panelBorder, 1.f, false));

    this->ui.addText("MESSAGE_LABEL", std::make_unique<Text>(
        kMainPanelX + 18.f, 828, 11, "LOG", sf::Color(180, 180, 180, 160), false));

    this->ui.addRectangle("MESSAGE_LABEL_DIV", std::make_unique<Rectangle>(
        kMainPanelX, 844, kMainPanelW, 1, sf::Color(255, 255, 255, 25), transparent, 0.f, false));

    // Message text — inset 18px from panel left, wraps to ~900px wide
    this->ui.addText("MESSAGE", std::make_unique<Text>(
        kMainPanelX + 18.f, 852, 15, "The bonfire waits quietly.",
        sf::Color(220, 200, 170, 255), false));

    // ── Right panel – actions ─────────────────────────────────────────
    this->ui.addRectangle("ACTION_PANEL", std::make_unique<Rectangle>(
        1400, 50, 290, 260, transparent, panelBorder, 1.f, false));
    this->ui.addText("ACTION_TITLE", std::make_unique<Text>(
        1415, 58, 13, "ACTIONS", sf::Color(200, 200, 200, 220), false));
    this->ui.addRectangle("ACTION_HEADER_DIV", std::make_unique<Rectangle>(
        1400, 80, 290, 1, sf::Color(255, 255, 255, 40), transparent, 0.f, false));

    const float btnX = 1410.f, btnW = 260.f, btnH = 30.f, btnGap = 12.f;
    float btnY = 92.f;

    this->ui.addButton("REST_PARTY", std::make_unique<Button>(
        btnX, btnY, btnW, btnH, 0.5f, "Rest Party",
        btnIdle, btnHover, btnActive, false));

    btnY += btnH + btnGap;
    this->ui.addButton("SMITH_WEAPON", std::make_unique<Button>(
        btnX, btnY, btnW, btnH, 0.5f, "Smith Weapon",
        btnIdle, btnHover, btnActive, false));

    btnY += btnH + btnGap;
    const std::string shopLabel = (atCastle && !GameFlags::getInstance().has("doctor_intro_played"))
        ? "Investigate Noises" : "Visit Doctor";
    this->ui.addButton("VISIT_SHOP", std::make_unique<Button>(
        btnX, btnY, btnW, btnH, 0.5f, shopLabel,
        btnIdle, btnHover, btnActive, !atCastle));

    btnY += btnH + btnGap;
    this->ui.addButton("LEAVE_BONFIRE", std::make_unique<Button>(
        btnX, btnY, btnW, btnH, 0.5f, "Leave Bonfire",
        btnDangerIdle, btnDangerHover, btnDangerActive, false));
}

// ── Bonfire Functions ─────────────────────────────────────────────────────

void BonfireState::restParty()
{
    CharacterManager::getInstance().restParty();
    this->ui.text("MESSAGE").setString("The party rests at the bonfire. HP restored.");
    std::cout << "Party rested at bonfire.\n";
}

void BonfireState::smithWeapon()
{
    this->ui.text("MESSAGE").setString("Smithing is not wired yet.");
    std::cout << "Smith weapon selected.\n";
}

void BonfireState::leaveBonfire()
{
    this->endState();
    if (!this->states->empty())
        this->states->pop();
}

void BonfireState::visitShop()
{
    this->states->push(new ShopState(this->window, this->states));
}